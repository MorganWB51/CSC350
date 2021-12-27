SOURCES=hw3.cpp Matrix.cpp Vector3.cpp ShapeData.cpp ShapeGenerator.cpp
OBJECTS=hw3.o
HEADER=hw3.h Matrix.h Vector3.h ShapeData.h ShapeGenerator.h
CC=g++
CFLAGS=-lGL -lGLU -lGLEW -lglut

# Compile hw3
hw3:
	$(CC) $(SOURCES) $(CFLAGS) -o hw3
 
# Remove the program hw1 
clean:
	rm -fR *o hw3
 
# Remove then compile hw1
demo: clean hw3

# Copile tests
