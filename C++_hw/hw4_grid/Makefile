all : main.o Grid.h Grid.o
	g++ main.o Grid.o -o main
main.o: main.cpp Grid.h
	g++ -c main.cpp -o main.o
Grid.o : Grid.cpp Grid.h
	g++ -c Grid.cpp -o Grid.o
clean:
	del *.o
	del main.out