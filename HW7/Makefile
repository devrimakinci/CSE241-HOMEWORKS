all: exe

exe: _mainTester.o BigramMap.o BigramDyn.o myException.o
	g++ _mainTester.o BigramMap.o BigramDyn.o myException.o -o exe

_mainTester.o :_mainTester.cpp
	g++ -c -std=c++11 _mainTester.cpp
	
BigramMap.o:BigramMap.cpp
	g++ -c -std=c++11 BigramMap.cpp
	
BigramDyn.o:BigramDyn.cpp
	g++ -c -std=c++11 BigramDyn.cpp
	
myException.o:myException.cpp
	g++ -c -std=c++11 myException.cpp
	
clean:
	rm *.o exe
