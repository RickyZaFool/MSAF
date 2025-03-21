CC         = g++ 
CFLAGS     = --std=c++11 -g -Wall
CFLAGSROOT = `root-config --cflags`
LIBSROOT   = `root-config --glibs`

all: Main

GridClass.o: grid_class.cpp
	$(CC) $(CFLAGS) -c grid_class.cpp  $(CFLAGSROOT)
Main: Main.cpp GridClass.o
	$(CC) $(CFLAGS) -o Main Main.cpp GridClass.o $(CFLAGSROOT) $(LIBSROOT)
clean:
	rm *.o