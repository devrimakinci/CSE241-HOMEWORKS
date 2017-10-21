all: hw1

hw1: hw1.o
	g++ hw1.o -o hw1

hw1.o: hw1.cpp
	g++ -c hw1.cpp

run1:
	./hw1 test.txt 0
	
run2:
	./hw1 test.txt 1 

clean:
	rm *.o hw1
