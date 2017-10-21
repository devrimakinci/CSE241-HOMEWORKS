/* 
 * Dosya Ismi: main.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 31 Ekim 2016 
 */

#include <iostream>
#include "CPU.h"
#include "CPUProgram.h"
#include "Parse.h"
#include "Memory.h"
#include "Computer.h"

using namespace std; //String kullanimi icin

int main(int argc, char** argv) {
    CPU temp; //Stringi integer'a cevirmek icin 
    int option = temp.convertFromStringToInt(argv[2]);
    const char* filename = argv[1];
    //Testing class Memory
    Memory myMemory(option);
    myMemory.setMem(0, 100);
    myMemory.setMem(2,35);
    cout << myMemory.getMem(0) << endl; 
    cout << myMemory.getMem(2) << endl; 
    myMemory.printAll();
    
    //Testing class CPU 
    CPU myCPU(option);
    myCPU.execute("MOV #0, R1", myMemory); 
    myCPU.execute("MOV R1, #1", myMemory);
    myCPU.execute("ADD R1, 10", myMemory);
    myCPU.execute("MOV #2, R2", myMemory);
    myCPU.execute("SUB R1, R2", myMemory);
    myCPU.print();
    myMemory.printAll();
    
    //Testing class CPUProgram 
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename); 
    for (int i=1; i<=myCPUProgram.size(); i++)
        cout << myCPUProgram.getLine(i) << endl; 
    
    //Testing class Computer
    Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
    Computer myComputer2(option); 
    myComputer2.setCPU(myComputer1.getCPU());
    myComputer2.setCPUProgram(myComputer1.getCPUProgram());
    myComputer2.setMemory(myComputer1.getMemory() ); 
    myComputer2.execute();
    return 0;
}
