all: hw3

hw3: main.o CPUProgram.o CPU.o Parse.o
	g++ main.o CPUProgram.o CPU.o Parse.o -o hw3

main.o: main.cpp
	g++ -c -std=c++11 main.cpp
	
CPUProgram.o: CPUProgram.cpp
	g++ -c -std=c++11 CPUProgram.cpp
	
CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp
	
Parse.o: Parse.cpp
	g++ -c -std=c++11 Parse.cpp
	
clean:
	rm *.o hw3
