all: mscheme.o object.o procedures.o
	g++ -o micro-scheme mscheme.o object.o procedures.o

mscheme.o: mscheme.cpp
	g++ -c mscheme.cpp -o mscheme.o

object.o: object.cpp
	g++ -c object.cpp -o object.o

procedures.o: procedures.cpp
	g++ -c procedures.cpp -o procedures.o

clean:
	rm *.o micro-scheme