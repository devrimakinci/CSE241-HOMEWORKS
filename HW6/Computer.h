/* 
 * Dosya Ismi: Computer.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 26 Kasim 2016
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgramDyn.h"
#include "Memory.h"
using namespace Program;

class Computer {
public:
    Computer(CPU &cpuOb, CPUProgramDyn &myProgOb, Memory &myMemoryOb, int opt); //Constructor
    Computer (int opt); //Constructor
    void execute();//Programi calistirir.
    void setCPU(const CPU &otherCPU);//CPU objesi set eder
    void setCPUProgramDyn (const CPUProgramDyn &otherCPUProgramDyn);//CPUProgramDyn objesi set eder.
    void setMemory (const Memory &otherMemory);//Memory objesi set eder.
    void setOption (int opt); //Programin calisma secenegini set eder.(0,1,2)
    const CPU& getCPU ()const;//CPU objesi alir.
    const CPUProgramDyn& getCPUProgramDyn ()const;//CPUProgramDyn objesi alir.
    const Memory& getMemory ()const;//Memory objesi alir.
    int getOption ()const;//Programin calisma secenegini alir.
private:
    CPU mainCPU; //CPU objesi
    CPUProgramDyn mainProg;//CPUProgramDyn objesi
    Memory mainMemory;//Memory objesi
    int option; //Programin calisma secenegi
};

#endif /* COMPUTER_H */