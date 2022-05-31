all: bj.cpp cls_func.o
	g++ -g bj.cpp cls_func.o -o bj

cls_func.o: cls_func.cpp cls_func.h
	g++ -c cls_func.cpp	 
clean:
	del *.o
	del *.out