
all: main
	
main: main.o Matrix.o
	g++ -o main main.o Matrix.o  -lncurses  -lrt -w -lpthread -lm 

main.o: main.cpp
	g++ -c main.cpp  -w 

Matrix.o: Matrix.cpp
	g++ -c Matrix.cpp -w
	
run: main
	./main

.PHONY: clean

clean:
	rm -f main *.o
