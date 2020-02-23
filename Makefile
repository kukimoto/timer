CC=gcc
CFLAGS=-I./
ALL:timer.o timerFunc.o
	$(CC) $(CFLAGS) -o timer timer.o timerFunc.o -lrt
timer.o:timer.c
	$(CC) $(CFLAGS) -o $@ -c $<
timerFunc.o:timerFunc.c
	$(CC) $(CFLAGS) -o $@ -c $<
timerFunc.o:timerFunc.h
clean:
	rm timer timer.o timerFunc.o
