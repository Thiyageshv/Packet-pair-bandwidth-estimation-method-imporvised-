include Make.defines

PROGS =	 client server

OPTIONS = -DUNIX  -DUSE_SIGACTION -DANSI

LIBS += -lrt

COBJECTS =	functions.o 
CSOURCES =	functions.c 

CPLUSOBJECTS = 

COMMONSOURCES =

CPLUSSOURCES =

all:	${PROGS}


client:	client.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(COMMONSOURCES) $(SOURCES)
		${CC} ${LINKOPTIONS}  $@ client.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


server:	server.o $(CPLUSOBJECTS) $(COBJECTS)
		${CC} ${LINKOPTIONS} $@ server.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


.cc.o:	$(HEADERS)
	$(CPLUS) $(CPLUSFLAGS) $(OPTIONS) $<

.c.o:	$(HEADERS)
	$(CC) $(CFLAGS) $(OPTIONS) $<



backup:
	rm -f *.tar.gz
	tar -cvzf hw1.tar.gz *

clean:
		rm -f ${PROGS} ${CLEANFILES} *.tar.gz

depend:
		makedepend client.c server.c  $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)
#		mkdep $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)

# DO NOT DELETE

client.o: defs.h /usr/include/stdio.h /usr/include/features.h
client.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
client.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
client.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
client.o: /usr/include/bits/typesizes.h /usr/include/libio.h
client.o: /usr/include/_G_config.h /usr/include/wchar.h
client.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
client.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
client.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
client.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
client.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
client.o: /usr/include/sys/types.h /usr/include/time.h
client.o: /usr/include/sys/select.h /usr/include/bits/select.h
client.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
client.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
client.o: /usr/include/alloca.h /usr/include/errno.h
client.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
client.o: /usr/include/asm/errno.h /usr/include/asm-generic/errno.h
client.o: /usr/include/asm-generic/errno-base.h /usr/include/string.h
client.o: /usr/include/netinet/in.h /usr/include/stdint.h
client.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
client.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
client.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
client.o: /usr/include/asm-generic/socket.h /usr/include/asm/sockios.h
client.o: /usr/include/asm-generic/sockios.h /usr/include/bits/in.h
client.o: /usr/include/arpa/inet.h /usr/include/netdb.h
client.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
client.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
client.o: /usr/include/bits/confname.h /usr/include/getopt.h
client.o: /usr/include/ctype.h /usr/include/signal.h
client.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
client.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
client.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
client.o: /usr/include/bits/sigthread.h /usr/include/fcntl.h
client.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
server.o: defs.h /usr/include/stdio.h /usr/include/features.h
server.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
server.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
server.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
server.o: /usr/include/bits/typesizes.h /usr/include/libio.h
server.o: /usr/include/_G_config.h /usr/include/wchar.h
server.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
server.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
server.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
server.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
server.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
server.o: /usr/include/sys/types.h /usr/include/time.h
server.o: /usr/include/sys/select.h /usr/include/bits/select.h
server.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
server.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
server.o: /usr/include/alloca.h /usr/include/errno.h
server.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
server.o: /usr/include/asm/errno.h /usr/include/asm-generic/errno.h
server.o: /usr/include/asm-generic/errno-base.h /usr/include/string.h
server.o: /usr/include/netinet/in.h /usr/include/stdint.h
server.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
server.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
server.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
server.o: /usr/include/asm-generic/socket.h /usr/include/asm/sockios.h
server.o: /usr/include/asm-generic/sockios.h /usr/include/bits/in.h
server.o: /usr/include/arpa/inet.h /usr/include/netdb.h
server.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
server.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
server.o: /usr/include/bits/confname.h /usr/include/getopt.h
server.o: /usr/include/ctype.h /usr/include/signal.h
server.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
server.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
server.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
server.o: /usr/include/bits/sigthread.h /usr/include/fcntl.h
server.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
functions.o: defs.h /usr/include/stdio.h /usr/include/features.h
functions.o: /usr/include/bits/predefs.h /usr/include/sys/cdefs.h
functions.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
functions.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
functions.o: /usr/include/bits/typesizes.h /usr/include/libio.h
functions.o: /usr/include/_G_config.h /usr/include/wchar.h
functions.o: /usr/include/bits/wchar.h /usr/include/xlocale.h
functions.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
functions.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
functions.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
functions.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
functions.o: /usr/include/sys/types.h /usr/include/time.h
functions.o: /usr/include/sys/select.h /usr/include/bits/select.h
functions.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
functions.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
functions.o: /usr/include/alloca.h /usr/include/errno.h
functions.o: /usr/include/bits/errno.h /usr/include/linux/errno.h
functions.o: /usr/include/asm/errno.h /usr/include/asm-generic/errno.h
functions.o: /usr/include/asm-generic/errno-base.h /usr/include/string.h
functions.o: /usr/include/netinet/in.h /usr/include/stdint.h
functions.o: /usr/include/sys/socket.h /usr/include/sys/uio.h
functions.o: /usr/include/bits/uio.h /usr/include/bits/socket.h
functions.o: /usr/include/bits/sockaddr.h /usr/include/asm/socket.h
functions.o: /usr/include/asm-generic/socket.h /usr/include/asm/sockios.h
functions.o: /usr/include/asm-generic/sockios.h /usr/include/bits/in.h
functions.o: /usr/include/arpa/inet.h /usr/include/netdb.h
functions.o: /usr/include/rpc/netdb.h /usr/include/bits/netdb.h
functions.o: /usr/include/unistd.h /usr/include/bits/posix_opt.h
functions.o: /usr/include/bits/confname.h /usr/include/getopt.h
functions.o: /usr/include/ctype.h /usr/include/signal.h
functions.o: /usr/include/bits/signum.h /usr/include/bits/siginfo.h
functions.o: /usr/include/bits/sigaction.h /usr/include/bits/sigcontext.h
functions.o: /usr/include/bits/sigstack.h /usr/include/sys/ucontext.h
functions.o: /usr/include/bits/sigthread.h /usr/include/fcntl.h
functions.o: /usr/include/bits/fcntl.h /usr/include/bits/stat.h
