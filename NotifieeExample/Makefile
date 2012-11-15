CC = g++
CPPFLAGS = -Wall -g

OBJECTS = QueueReactor.o

default:	example

example: example.o $(OBJECTS)
	 $(CC) $(CPPFLAGS) -o example example.o $(OBJECTS)
	 @echo

clean:
	 @rm -f example.o $(OBJECTS) example *~

QueueReactor.o: QueueReactor.h QueueReactor.cpp