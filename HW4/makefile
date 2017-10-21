all: hw4

hw4: main.o CPUProgram.o CPU.o Parse.o Memory.o Computer.o
	g++ main.o CPUProgram.o CPU.o Parse.o Memory.o Computer.o -o hw4

main.o: main.cpp
	g++ -c -std=c++11 main.cpp
	
CPUProgram.o: CPUProgram.cpp
	g++ -c -std=c++11 CPUProgram.cpp
	
CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp
	
Parse.o: Parse.cpp
	g++ -c -std=c++11 Parse.cpp

Memory.o: Memory.cpp
	g++ -c -std=c++11 Memory.cpp
	
Computer.o: Computer.cpp
	g++ -c -std=c++11 Computer.cpp
	
clean:
	rm *.o hw4
