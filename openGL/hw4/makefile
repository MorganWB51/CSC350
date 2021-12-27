SOURCES=hw4.cpp Matrix.cpp Vector3.cpp ShapeData.cpp ShapeGenerator.cpp
OBJECTS=hw3.o
HEADER=hw4.h Matrix.h Vector3.h ShapeData.h ShapeGenerator.h
CC=g++
CFLAGS=-lGL -lGLU -lGLEW -lglut

# Compile hw4
hw4:
	$(CC) $(SOURCES) $(CFLAGS) -o hw4
 
# Remove the program hw4
clean:
	rm -fR *o hw4
 
# Remove then compile hw4
demo: clean hw4

# Copile tests
