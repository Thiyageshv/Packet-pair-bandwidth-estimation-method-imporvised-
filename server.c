/********************************************************
*  Program: Bandwidth Estimation			*
*							*
*  Summary:						*
*	This file contains the server code		*
*							*
*********************************************************/


/* NOTE : THE PACKETS ARRIVE IN PAIRS . SEQUENCE NUMBERS GO FROM 1 to 10 or 1 to 5. EVERY SEQUENCE NUMBER HAS TWO PACKETS WHICH ARE TO BE RECEIVED. THE PACKETS CAN ALSO BE REORDERED . THERE ARE PROVISIONS IN THE CODE TO HANDLE REORDERING . HOWEVER REORDERING OUTPUT HAS NOT BEEN TESTED. CAN TEST USING NETEM */

#include "defs.h"

int quit = 0;	/* CNT-C exit flag */

#define RESET 0
#define HEX 16
#define MSZ_BEGIN 5
#define SEQ_BEGIN 5
#define BSZ_BEGIN 9
#define MAX_WAIT 30
#define HEADER_SIZE 28

#define TO_Mbits(x) (x*8/1048576)

struct Client {
	int cmd;
	char sessionID[ID_LEN+1];
	unsigned int msgSize;
	unsigned int seq;
	unsigned int burstSize;
	unsigned int burstCnt;
	unsigned int numRecv;
	double bandwidth;
};

/* SIGINT handler */
void CNT_C_Code() 
{ 
	printf("CNT-C Interrupt, exiting...\n");
	quit = 1; 
}

/* SIGALRM handler */
void alarmHandler() { }	

int main()
{
	int sock;				/* Socket */
	struct sockaddr_in serverAddr;		/* Local address */
	struct sockaddr_in clientAddr;		/* Client address */
	struct sockaddr_in dupClAddr;		/* Temporary address */
	unsigned int addrLen;			/* Client address length */
	unsigned int serverPort;		/* Local port */
	struct sigaction sa_int;		/* For SIGINT */
	struct sigaction sa_alrm;		/* For SIGALRM */
	int cmd = RESET;			/* Server commands */
	char buffer[MIN_MSG_LEN];		/* Receive buffer */
	char results[RESULT_LEN];		/* Results buffer */
	char *msg = NULL;			/* Client message */
	struct Client cl;			/* Current client */
	int recvlen;				/* Received message length */
	int seq;				/* Sequence number */
	struct timespec ts1;			/* time structure */
	struct timespec ts2;			/* time structure */
	struct timespec *ts = NULL;		/* Switch pointer */
	int swtch = 0;				/* Switch flag for timespecs */
	int cnt = 0;
	char temp[ID_LEN+1];
        int countpair=0;
        int prevseq;
        struct pkt
         {
            int seqno;
            struct timespec ts0;
         }obj[10];
         int flag[11];
         int i=0;
        for(i=0;i<11;i++)
        flag[i]=0;
	
	/* Invalid invocation of the program */
	/*if (argc != 2) {
		printf("Syntax: %s <port number>\n", argv[0]);
		exit(1);
	}*/
	
	serverPort =5555;

	/* create datagram socket */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
		DieWithError("socket() failed");
         // fcntl(sock,F_SETFL,O_NONBLOCK);

        int optval = 1;
        setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    
	
	/* build local address struct */
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("192.168.56.101"); // htonl(INADDR_ANY);
	serverAddr.sin_port = htons(serverPort);
	
	/* bind to local address */
	printf("Server: binding to port %d\n", serverPort);
	if (bind(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0) {
		close(sock);
		DieWithError("bind() failed");
	}
	
	/* assign handler and initialize set to all signals */
	sa_int.sa_handler = CNT_C_Code;
	sa_alrm.sa_handler = alarmHandler;	
	if (sigfillset(&sa_int.sa_mask) < 0 || sigfillset(&sa_alrm.sa_mask) < 0) {
        	close(sock);
		DieWithError("sigfillset() failed");
	}

	/* set the handler */
	sa_int.sa_flags = sa_alrm.sa_flags = 0;
        if (sigaction(SIGINT, &sa_int, 0) < 0 || sigaction(SIGALRM, &sa_alrm, 0) < 0) {
        	close(sock);
		DieWithError("sigaction() failed");
	}

	addrLen = sizeof(struct sockaddr_in);

	/* Run until CNT-C */
  //	for ( ; !quit; )

  repeat:
       {

		if (cmd == RESET) {
			/* reset session id */
			memset(&cl, 0, sizeof(cl));
			errno = swtch = cnt = 0;
			ts = &ts1;

			printf("Waiting for Client...\n");

			/* get the first message from client */
			recvfrom(sock, buffer, MIN_MSG_LEN, 0, (struct sockaddr *) &clientAddr, &addrLen);
                        printf("first message : %s\n",buffer);  
			if (errno == EINTR)  exit(0);     //continue;

			memcpy(&dupClAddr, &clientAddr, addrLen);
			cl.cmd = buffer[0]-'0';		/* get the client command */
		}

		/* Received START_MSG, send START_ACK */
		if (cl.cmd == START_MSG) {

			getFromMsg(cl.sessionID, buffer, SID_BEGIN, ID_LEN);	/* retrieve session ID */

			getFromMsg(temp, buffer, MSZ_BEGIN, ID_LEN);		/* retrieve message size */
			cl.msgSize = strtol(temp, NULL, HEX);

			getFromMsg(temp, buffer, BSZ_BEGIN, ID_LEN);		/* retrieve burst size */
			cl.burstSize = strtol(temp, NULL, HEX);

			if (!msg) msg = (char *) calloc(cl.msgSize+1, sizeof(char));

			printf("\n");
			printf("Serving client with session ID: %s\n", cl.sessionID);
			
			/* set sending buffer to START_ACK */
			cmd = START_ACK;
			*msg = cmd + '0';
			strcpy(msg+SID_BEGIN, cl.sessionID);

			/* send START_ACK to client */
			printf("=== Received START_MSG, sending START_ACK...\n");
			sendto(sock, msg, strlen(msg)+1, 0, (struct sockaddr *) &clientAddr, addrLen);
		}

		if (cmd == START_ACK) {
			int once = 1;
                       cl.seq=1;
                       prevseq=0;
			/* accept client bursts */			
			for ( ; ; ) 
                         {

				alarm(MAX_WAIT);	/* wait till client sends next message, used when client crashes */

				recvlen = recvfrom(sock, msg, cl.msgSize+1, 0, (struct sockaddr*) &dupClAddr,&addrLen);
                               //printf("received length %d \n",recvlen);
                                //printf( "strmsg %d \n",strlen(msg));
                                printf("received message %s \n" ,msg);
                                //printf("cl.msgsize %d \n",cl.msgSize);
				clock_gettime(CLOCK_REALTIME, ts);		/* get time */
				
				if (errno == EINTR) {
					if (!quit) {
						free(msg);
						msg = NULL;
						cl.cmd = cmd = RESET;
						printf("Server Timeout: Resetting...\n\n");
					}
					break;
				}
				alarm(0);

				//if (strlen(msg) != cl.msgSize)		/* damaged packet */
					//continue;

				/* wrong client */
				if (memcmp(&dupClAddr, &clientAddr, addrLen) || strncmp(cl.sessionID, msg+SID_BEGIN, ID_LEN))
					break;

				if ((cl.cmd = *msg-'0') == START_MSG)		/* client did not receive START_ACK */
					break;

				if (cl.cmd == DONE) {				/* Client done bursting */
					cmd = RESULTS_MSG;
					break;
				}

				++cl.numRecv;
				//ts = ((swtch = 1-swtch)) ? &ts2 : &ts1;		/* switch time pointer */
                             
                                 //ignore once flags ->used for testing purpose

				getFromMsg(temp, msg, SEQ_BEGIN, ID_LEN);	/* get sequence number */
				seq = strtol(temp, NULL, HEX);
                                if(flag[seq]==0)
                                 {
                                        ts=&ts1;     // if this is the first packet of the sequence store time in ts1
                                 }
                                 else if(flag[seq]==1)
                                 { 
                                         ts=&ts2;  // if this is the second part of the sequence store time in ts2
                                         swtch=0;
                                 }
                                
                               // printf("cl.seq %d \n " , cl.seq);
                                
				/* change in sequence */
                                
                               // countpair++;
				if (seq != cl.seq && flag[seq]==0) {   //if there is a change in the order of the sequence . cl.seq contains the sequence number which is being expected . if the current se
								      //does not match cl.seq it means packets have been reordered
					
                                        once = 0;
					//prevseq = cl.seq;
                                        // store the details of the reordered packet so that they can be used later when the other part of the packet pair arrives.                            

                                        obj[seq].seqno=seq;         
					*ts = obj[seq].ts0;
                                         flag[seq]=1;
					//swtch = 0;
                                         printf("is this loop being entered ? \n");
                                         printf("=== Receiving from burst #%d...\n",  seq); // cl.seq   
                              
			       }
 
                              



                               else if(seq!=prevseq && seq==prevseq+1 && flag[seq]==0 )   // if there is a change in sequence  , i.e the FIRST packet of the next sequence number occurs
                                {
                                        once = 1;
					prevseq = seq;                // prevseq contains the value of the sequence no. that preceeded the correct sequence number (cl.seq) -1 = prevseq
					//ts = &ts1;
					//swtch = 0;
					
                                      
                                        flag[seq]=1;

					printf("=== Receiving from burst #%d...\n",  seq); // cl.seq   

 
                                }
				else {
					/* this block has the code to receive the second packet of the ongoing seuence number or reordered sequence number */
                                        
					if (flag[seq]==1 && seq==cl.seq)  // if other packet of the correct and expected sequence number arrives, seq==cl.seq implies packet has expcted seqno //  
                                        
                                                  
                                            
                                                      
                                     {                
                                                      once=0;
                                                      ++cl.burstCnt;
                                                     //  printf("burstCnt %d \n" ,cl.burstCnt);
                                                      flag[seq]=2; // indicates that both the packets have been received
                                                                    //wait for the next sequence number
                                                    // from here it goes to the "calcuating average bandwidth part "   
                                                   
                                      }




					


                                         else if(seq!=cl.seq && flag[seq]==1)  /* If the other packet of the reordered sequence number arrives , get the stored time of the first packet , assign ts2 to the 
                                                   				  arrival  time of this packet(2nd paccket) */
                                          {  
                                            obj[seq].ts0=ts1;   // ts0 has the time of arrival of first packet , which had arrived before 
                                            ts=&ts2;            // time of the new packet
                                            swtch=0;
                                            flag[seq]=2;       // both the parts of the reordered sequence number packet has arrived. 
                                            ++cl.burstCnt;
                                             // from here it goes to the "calcuating average bandwidth part "   
                                             printf("is this loop being entered - packets are reordered then \n");
                                        }

                                     

					/* calculate average bandwidth */
				         
                                        cl.bandwidth *= cnt++;
                                        printf("%d \n" , cnt);
					cl.bandwidth += ((double) cl.msgSize+1+HEADER_SIZE) / 
							((swtch) ? getTimeDiff(ts2, ts1) : getTimeDiff(ts1, ts2)); // header size of UDP packet is 28 . Hence it is also included along with main packet 
					cl.bandwidth /= (double) cnt;
                                        if(flag[cl.seq]==2)  // if the both packets of expected sequence number have arrived , wait for the next seq number
                                        cl.seq+=1;
				}

				/* not retrieving data from message */
			}
		}

		if (cmd == RESULTS_MSG) {
			float totExpected = cl.burstSize * (cl.burstCnt);
                        printf("total expected %d \n",totExpected);
                        printf( "bandwidth %f \n",TO_Mbits(cl.bandwidth));

			/* create results */
			results[0] = cmd + '0';
			sprintf(results+SID_BEGIN, "%s:%f:%.2f:%u:%u", cl.sessionID, TO_Mbits(cl.bandwidth),
					((totExpected-cl.numRecv)/totExpected)*100, cl.numRecv, cl.burstCnt);

			printf("\n");
			printf("=== Received DONE, sending RESULTS_MSG...\n");
			sendto(sock, results, RESULT_LEN, 0, (struct sockaddr *) &dupClAddr, addrLen);

			alarm(MAX_WAIT);
			recvfrom(sock, msg, cl.msgSize+1, 0, (struct sockaddr *) &dupClAddr, &addrLen);

			if (errno == EINTR) {
				if (!quit) {
					free(msg);
					msg = NULL;
					cmd = RESET;
					printf("Server Timeout: Resetting...\n\n");
				}
				exit(0);//continue; REPLACE WITH GOTO LB LATER
			}
                       else
                       exit(0);
			alarm(0);

			/* wrong client */
			if (memcmp(&dupClAddr, &clientAddr, addrLen) || strncmp(cl.sessionID, msg+SID_BEGIN, ID_LEN))	
				exit(0);//continue;  goto repeat;

			if (*msg-'0' == DONE)			/* client did not receive RESULTS_MSG */
			   exit(0);	// continue;  REPLACE WITH GOTO LB LATER

			if (*msg-'0' == DONE_ACK) {		/* received DONE_ACK from client */

				printf("=== Received DONE_ACK.\n\n");
				
				free(msg);
				msg = NULL;
				cmd = RESET;
			}
		}
	}

	if (msg) free(msg);
	close(sock);
	return 0;
}

