SOURCES=final.cpp Matrix.cpp Vector3.cpp ShapeData.cpp ShapeGenerator.cpp component.cpp
OBJECTS=final.o
HEADER=final.h Matrix.h Vector3.h ShapeData.h ShapeGenerator.h component.h
CC=g++
CFLAGS=-lGL -lGLU -lGLEW -lglut

# Compile final
final:
	$(CC) $(SOURCES) $(CFLAGS) -o final
 
# Remove the program final
clean:
	rm -fR *o final
 
# Remove then compile final
demo: clean final

# Copile tests
