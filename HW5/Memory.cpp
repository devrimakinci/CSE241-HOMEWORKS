/* 
 * Dosya Ismi: Memory.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 13 Kasim 2016
 */
#include "Memory.h"

Memory::Memory() {
    setMem();
}
Memory::Memory(int opt){
    setOption(opt);
    setMem();
}
int Memory::getMem(int address) const {
    return memory[address];
}
void Memory::setMem(int value){
    for (int i=0; i<MEMORY_SIZE; i++)
        setMem (i,value);
}
void Memory::setMem(int address, int value) {
    memory[address] = value;
}
void Memory::printAll() const {
    cout << "Memory Values:" << endl;
    for (int j=0; j<10; j++){
        for (int i=0; i<5; i++){
            cout << "[" << (i*10)+j << "]" << "->"; 
            cout.width(3);
            cout << getMem((i*10)+j) << "  ";
        }
        cout << endl;
    }
}
void Memory::setOption(int opt){
    option = opt;
}
int Memory::getOption() const {
    return option;
}