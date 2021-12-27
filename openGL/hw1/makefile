SOURCES=hw1.cpp
OBJECTS=hw1.o
HEADER=hw1.h
CC=g++
CFLAGS=-lGL -lGLU -lGLEW -lglut

# Compile hw1
hw1:
	$(CC) $(SOURCES) $(CFLAGS) -o hw1
 
# Remove the program hw1 
clean:
	rm -fR *o hw1
# Remove then compile hw1
demo: clean hw1 