CC=gcc
CFLAGS=-I.
DEPS = cbmp.h
$(warning A top-level warning ${DEPS})
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: encode decode tcpserver tcpclient

encode: cbmp.o encode.o
	$(CC) -o encode encode.c cbmp.o
	
decode: cbmp.o decode.o
	$(CC) -o decode decode.c cbmp.o

tcpserver:
	cd server && make

tcpclient:
	cd client && make	

clean :
	rm -fr *.o encode decode
	rm -fr server/*.o server/tcp_server server/bg_got.bmp
	rm -fr client/*.o client/tcp_client