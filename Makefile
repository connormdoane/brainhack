CC = gcc
CFLAGS = -g -Wall -Wextra -std=c11
TARGET = brainhack
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean

