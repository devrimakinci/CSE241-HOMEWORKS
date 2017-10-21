/* 
 * Dosya Ismi: Computer.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 13 Kasim 2016
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

class Computer {
public:
    Computer(CPU &cpuOb, CPUProgram &myProgOb, Memory &myMemoryOb, int opt); //Constructor
    Computer (int opt); //Constructor
    void execute();//Programi calistirir.
    void setCPU(const CPU &otherCPU);//CPU objesi set eder
    void setCPUProgram (CPUProgram &otherCPUProgram);//CPUProgram objesi set eder.
    void setMemory (const Memory &otherMemory);//Memory objesi set eder.
    void setOption (int opt); //Programin calisma secenegini set eder.(0,1,2)
    CPU& getCPU ();//CPU objesi alir.
    CPUProgram& getCPUProgram ();//CPUProgram objesi alir.
    Memory& getMemory (); //Memory objesi alir.
    int getOption ();//Programin calisma secenegini alir.
private:
    CPU mainCPU; //CPU objesi
    CPUProgram mainProg;//CPUProgram objesi
    Memory mainMemory;//Memory objesi
    int option; //Programin calisma secenegi
};

#endif /* COMPUTER_H */