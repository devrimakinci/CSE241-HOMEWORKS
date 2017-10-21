all: hw2

hw2: main.o
	g++ main.o -o hw2

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

clean:
	rm *.o hw2
