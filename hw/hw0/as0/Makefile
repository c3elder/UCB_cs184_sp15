CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Ias0Files/glut-3.7.6-bin
	LDFLAGS = -lglut -lGL
endif

RM = /bin/rm -f 

# MAKE ALL
all: main

# Compile example
main: as0Files/as0.o 
	$(CC) $(CFLAGS) -o as0 as0Files/as0.o as0Files/Spiff.o as0Files/Maze.o as0Files/Line.o $(LDFLAGS)
as0Files/as0.o: as0Files/as0.cpp as0Files/Spiff.o as0Files/Maze.o
	$(CC) $(CFLAGS) -c as0Files/as0.cpp -o as0Files/as0.o

# Compile Spiff
as0Files/Spiff.o: as0Files/Spiff.cpp
	$(CC) $(CFLAGS) -c as0Files/Spiff.cpp -o as0Files/Spiff.o

# Compile Maze
as0Files/Maze.o: as0Files/Maze.cpp as0Files/Line.o
	$(CC) $(CFLAGS) -c as0Files/Maze.cpp -o as0Files/Maze.o

# Compile Line
as0Files/Line.o: as0Files/Line.cpp
	$(CC) $(CFLAGS) -c as0Files/Line.cpp -o as0Files/Line.o

# Clean up files
clean: 
	$(RM) *.o as0Files/*.o as0
 

