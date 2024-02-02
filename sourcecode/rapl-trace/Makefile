OBJS	= main.o
SOURCE	= main.c
HEADER	=
OUT	= main.out
CC	 = gcc
FLAGS	 = -g -c -Wall -fno-lto
LFLAGS	 = -lm -fno-lto
PY_CFLAGS  = `python3-config --cflags`
PY_LDFLAGS = `python3-config --ldflags`

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(PY_CFLAGS) $(LFLAGS) ${PY_LDFLAGS} -DTOGGLE_GPIO

main.o: main.c
	$(CC) $(FLAGS) $(PY_CFLAGS) main.c -std=c17 -DTOGGLE_GPIO

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
