/* 
 * Dosya Ismi: Computer.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 13 Kasim 2016
 */

#include "Computer.h"

Computer::Computer(CPU& cpuOb, CPUProgram& myProgOb, Memory& myMemoryOb, int opt){
    setCPU(cpuOb);
    setCPUProgram(myProgOb);
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
void Computer::setCPUProgram(CPUProgram& otherCPUProgram){
    mainProg.setVectorSize(otherCPUProgram.size());
    for (int i=0; i<otherCPUProgram.size(); i++)
        mainProg.setLine(i,otherCPUProgram.getLine(i));
    mainProg.setSize(otherCPUProgram.size());
    mainProg.setOption(otherCPUProgram.getOption());
}
void Computer::setMemory(const Memory& otherMemory){
    for (int i=0; i<MEMORY_SIZE; i++)
        mainMemory.setMem(i,otherMemory.getMem(i));
    mainMemory.setOption(otherMemory.getOption());
}
void Computer::setOption(int opt){
    option = opt;
}
int Computer::getOption(){
    return option;
}
CPU& Computer::getCPU(){
    return mainCPU;
}
Memory& Computer::getMemory(){
    return mainMemory;
}
CPUProgram& Computer::getCPUProgram(){
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