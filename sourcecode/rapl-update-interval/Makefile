OBJS	= main.o
SOURCE	= main.c
HEADER	= 
OUT	= main.exe
CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

$(OBJS): $(SOURCE)
	$(CC) $(FLAGS) $(SOURCE)
run:
	./$(OUT)
clean:
	rm -f $(OBJS) $(OUT)