SOURCES=hw2.cpp Matrix.cpp
OBJECTS=hw2.o
HEADER=hw2.h Matrix.h
CC=g++
CFLAGS=-lGL -lGLU -lGLEW -lglut

# Compile hw2
hw2:
	$(CC) $(SOURCES) $(CFLAGS) -o hw2
 
# Remove the program hw1 
clean:
	rm -fR *o hw2
# Remove then compile hw1
demo: clean hw2