
The packet paor bandwidth estimation method probes a pair of packet across a bottleneck link and then mesures the RTT time it takes to compute the bandwidth of the network. In this , i am working towards probing in diffferent scenarios such as packet loss , bit error etcc.  Also to give correct results we probe a series of pairs and take an average over the bandwidth estimation method. 
Need to test it with a link emulator. Will update changes soon. 
Building Instructions:

	Execute the following commands in a terminal 
	
	Compile:
	$ make clean
	$ make depend
	$ make
	
        These two executables are created after compiling
	    -> client
	    -> server


Execute:

    -> Server code syntax:
		
	./server 
		
    -> Client code syntax:

	./client 


NOTE : if server and client are going to be executed in two different systems , run the above commands in both the systems. Also change the ip address to the ip address of the server system in client.c code file.


