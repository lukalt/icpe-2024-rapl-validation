CC = gcc
CFLAGS = -O2 -fopenmp

all: stream_c.exe

stream_c.exe: stream.c
	$(CC) $(CFLAGS) stream.c -o stream_c.exe -DSTREAM_ARRAY_SIZE=100000000 -m64

stream_c_small.exe: stream.c
	$(CC) $(CFLAGS) stream.c -o stream_c.exe -DSTREAM_ARRAY_SIZE=1000000000 -m64

clean:
	rm -f stream_c.exe *.o