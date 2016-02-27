CC = g++
ifeq ($(shell sw_vers 2>/dev/null | grep Mac | awk '{ print $$2}'),Mac)
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -I./include/ -I/usr/X11/include -DOSX
	LDFLAGS = -framework GLUT -framework OpenGL \
    	-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
    	-lGL -lGLU -lm -lstdc++
else
	CFLAGS = -g -DGL_GLEXT_PROTOTYPES -Iglut-3.7.6-bin
	LDFLAGS = -lglut -lGLU
endif
	
RM = /bin/rm -f
CLASSES = as1Files/Sphere.o as1Files/Light.o
all: main 
main: as1Files/as1.o $(CLASSES)
	$(CC) $(CFLAGS) -o as1 as1Files/as1.o $(CLASSES) $(LDFLAGS) 
as1Files/as1.o: as1Files/as1.cpp
	$(CC) $(CFLAGS) -c as1Files/as1.cpp -o as1Files/as1.o

as1Files/Sphere.o: as1Files/Sphere.cpp
	$(CC) $(CFLAGS) -c as1Files/Sphere.cpp -o as1Files/Sphere.o

as1Files/Light.o: as1Files/Light.cpp
	$(CC) $(CFLAGS) -c as1Files/Light.cpp -o as1Files/Light.o

clean: 
	$(RM) as1Files/*.o as1
r: clean all


