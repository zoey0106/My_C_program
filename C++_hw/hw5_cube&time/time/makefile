all : main.o time.h time.o
	g++ main.o time.o -o main
main.o: main.cpp time.h
	g++ -c main.cpp -o main.o
time.o : time.cpp time.h
	g++ -c time.cpp -o time.o
clean:
	rm *.o
	rm main.out