/* 
 * Dosya Ismi: Computer.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 26 Kasim 2016
 */

#include "Computer.h"
using namespace Program;

Computer::Computer(CPU& cpuOb, CPUProgramDyn& myProgOb, Memory& myMemoryOb, int opt){
    setCPU(cpuOb);
    setCPUProgramDyn(myProgOb);
    setMemory(myMemoryOb);
    setOption(opt);
}
Computer::Computer(int opt){
    setOption (opt);
}
void Computer::setCPU(const CPU& otherCPU){
    for (int i=0; i<REGISTER_SIZE; i++)
        mainCPU.setReg(i,otherCPU.getReg(i));
    mainCPU.setPC(otherCPU.getPC()); 
    mainCPU.setInstr(otherCPU.getInstr());   
    mainCPU.setOption(otherCPU.getOption());
}
void Computer::setCPUProgramDyn(const CPUProgramDyn& otherCPUProgramDyn){
    mainProg = otherCPUProgramDyn;
    for (int i=0; i<otherCPUProgramDyn.size(); i++)
        mainProg.setLine(i,otherCPUProgramDyn.getLine(i));
    mainProg.setSize(otherCPUProgramDyn.size());
    mainProg.setOption(otherCPUProgramDyn.getOption());
}
void Computer::setMemory(const Memory& otherMemory){
    for (int i=0; i<MEMORY_SIZE; i++)
        mainMemory.setMem(i,otherMemory.getMem(i));
    mainMemory.setOption(otherMemory.getOption());
}
void Computer::setOption(int opt){
    option = opt;
}
int Computer::getOption()const{
    return option;
}
const CPU& Computer::getCPU()const{
    return mainCPU;
}
const Memory& Computer::getMemory()const{
    return mainMemory;
}
const CPUProgramDyn& Computer::getCPUProgramDyn()const{
    return mainProg;
}
void Computer::execute() {
    mainCPU.setOption(getOption());
    mainCPU.setPC(0);
    while (!mainCPU.halted()){ //Programin bitip bitmediginin kontrol edilmesi
        //Program counterin tuttugu satirin alinmasi
        string instruction = mainProg.getLine(mainCPU.getPC());
        //Alinan satiri uygun olarak calistirmasi
        mainCPU.execute(instruction,mainMemory);
    }
}