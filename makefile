CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=llist.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=test.exe

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o core *~
