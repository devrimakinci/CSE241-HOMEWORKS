/* 
 * Dosya Ismi: Memory.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 31 Ekim 2016 
 */
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

using namespace std;

const int MEMORY_SIZE = 50; //Maksimum memory sayisi

class Memory {
public:
    Memory(); //No parameter constructor
    Memory(int opt); //Constructor
    int getMem (int address) const;//Memory'deki adresin gosterdigi degeri alir.
    int getOption () const ; //Programin calisma secenegini alir.
    void setOption (int opt);//Programin calisma secenegini set eder.(0,1,2)
    void setMem (int adress, int value);
    //Verilen index ve degere gore memory'deki adresin gosterdigi degeri set eder.
    void setMem (int value=0);
    //Memory'deki adreslerin gosterdigi tum degerleri sifira set eder.
    void printAll() const ;
    //Memory'deki adresin gosterdigi tum degerleri ekrana basar.
private:
    unsigned int memory[MEMORY_SIZE]; //Memory'i tutacak unsigned integer array 
    int option; //Programin calisma secenegi
};

#endif /* MEMORY_H */