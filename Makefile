CC		= gcc
CFLAGS	= -Wall -O2 # compiler warnings + optimize

TARGET	= main

all:
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c -lm
