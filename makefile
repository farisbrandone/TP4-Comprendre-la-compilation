# Makefile for evaluation of expressions with handle extern library
CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lm
LIB_DIR = ./
TARGET = calculatrice
OBJ = calculatrice.o main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIB_DIR) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
