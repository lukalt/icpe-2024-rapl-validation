OBJS	= sample-rapl.o
SOURCE	= sample-rapl.c
HEADER	=
OUT	= sample-rapl.exe
CC	 = gcc
FLAGS	 = -g -c -Wall -fno-lto -fPIC
LFLAGS	 = -lm -fno-lto

PY_CFLAGS  := $(shell python3-config --cflags)
PY_LDFLAGS := $(shell python3-config --embed --ldflags)

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(PY_LDFLAGS) $(PY_CFLAGS) -DTOGGLE_GPIO

$(OBJS): $(SOURCE)
	$(CC) $(FLAGS) $(PY_CFLAGS) $(SOURCE) -std=c17 -DTOGGLE_GPIO

clean:
	rm -f $(OBJS) $(OUT)

run: $(OUT)
	./$(OUT)
