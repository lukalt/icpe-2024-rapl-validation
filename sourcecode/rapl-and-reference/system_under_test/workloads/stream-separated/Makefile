CC = gcc
CFLAGS = -O2 -fopenmp

all: copy scale add triad copy_small scale_small add_small triad_small

copy:
	$(CC) $(CFLAGS) stream.c -o stream_copy.exe -DBENCHMARK=0 -DSTREAM_ARRAY_SIZE=100000000 -m64

scale:
	$(CC) $(CFLAGS) stream.c -o stream_scale.exe -DBENCHMARK=1 -DSTREAM_ARRAY_SIZE=100000000 -m64

add:
	$(CC) $(CFLAGS) stream.c -o stream_add.exe -DBENCHMARK=2 -DSTREAM_ARRAY_SIZE=100000000 -m64

triad:
	$(CC) $(CFLAGS) stream.c -o stream_triad.exe -DBENCHMARK=3 -DSTREAM_ARRAY_SIZE=100000000 -m64

copy_small:
	$(CC) $(CFLAGS) stream.c -o stream_copy_small.exe -DBENCHMARK=0 -DSTREAM_ARRAY_SIZE=10000000 -m64

scale_small:
	$(CC) $(CFLAGS) stream.c -o stream_scale_small.exe -DBENCHMARK=1 -DSTREAM_ARRAY_SIZE=10000000 -m64

add_small:
	$(CC) $(CFLAGS) stream.c -o stream_add_small.exe -DBENCHMARK=2 -DSTREAM_ARRAY_SIZE=10000000 -m64

triad_small:
	$(CC) $(CFLAGS) stream.c -o stream_triad_small.exe -DBENCHMARK=3 -DSTREAM_ARRAY_SIZE=10000000 -m64

clean:
	rm -f stream_*.exe *.o

