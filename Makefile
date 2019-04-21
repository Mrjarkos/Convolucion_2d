
all: main
	
main: main.o Matrix.o
	g++ -o main main.o Matrix.o  -lncurses  -lrt

main.o: main.cpp
	g++ -c main.cpp 

Matrix.o: Matrix.cpp
	g++ -c Matrix.cpp
	
run: main
	./main

.PHONY: clean

clean:
	rm -f main *.o
