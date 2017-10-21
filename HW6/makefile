all: exe

exe: _mainTester.o CPUProgramDyn.o CPU.o Parse.o Memory.o Computer.o
	g++ _mainTester.o CPUProgramDyn.o CPU.o Parse.o Memory.o Computer.o -o exe

_mainTester.o :_mainTester.cpp
	g++ -c -std=c++11 _mainTester.cpp
	
CPUProgramDyn.o: CPUProgramDyn.cpp
	g++ -c -std=c++11 CPUProgramDyn.cpp
	
CPU.o: CPU.cpp
	g++ -c -std=c++11 CPU.cpp
	
Parse.o: Parse.cpp
	g++ -c -std=c++11 Parse.cpp

Memory.o: Memory.cpp
	g++ -c -std=c++11 Memory.cpp
	
Computer.o: Computer.cpp
	g++ -c -std=c++11 Computer.cpp
	
clean:
	rm *.o exe
