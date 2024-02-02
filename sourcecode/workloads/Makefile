CC = icx
CFLAGS = -O2 -fopenmp -lm -qmkl

all: busywait idle compute addpd matmul memoryread mulpd sqrt memorywrite memorycopy

busywait:
	$(CC) $(CFLAGS) main.c -o busywait.exe -DWORKLOAD=0

idle:
	$(CC) $(CFLAGS) main.c -o idle.exe -DWORKLOAD=1

compute:
	$(CC) $(CFLAGS) main.c -o compute.exe -DWORKLOAD=2

addpd:
	$(CC) $(CFLAGS) main.c -o addpd.exe -DWORKLOAD=3

matmul:
	$(CC) $(CFLAGS) main.c -o matmul.exe -DWORKLOAD=4

memoryread:
	$(CC) $(CFLAGS) main.c -o memoryread.exe -DWORKLOAD=5

mulpd:
	$(CC) $(CFLAGS) main.c -o mulpd.exe -DWORKLOAD=6

sqrt:
	$(CC) $(CFLAGS) main.c -o sqrt.exe -DWORKLOAD=7

memorywrite:
	$(CC) $(CFLAGS) main.c -o memorywrite.exe -DWORKLOAD=8

memorycopy:
	$(CC) $(CFLAGS) main.c -o memorycopy.exe -DWORKLOAD=9

run-all:
	for x in *.exe; do; "./$x"; done

clean:
	rm -f *.exe *.o
