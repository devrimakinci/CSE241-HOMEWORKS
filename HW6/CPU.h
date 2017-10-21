/* 
 * Dosya Ismi: CPU.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 26 Kasim 2016
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include "Parse.h"
#include "CPUProgramDyn.h"
#include "Memory.h"

using namespace std; //String kullanimi icin

const int REGISTER_SIZE=5; //Register sayisi

class CPU {
public:
    CPU(int value, int line, string instr); //Constructor
    CPU(int opt); //Constructor
    CPU(); //No parameter constructor
    void setReg (int value); //Butun registerlar'i sifira set eder.
    void setReg (int index, int value);
    //Verilen index ve degere gore register'i set eder.
    void setPC (int line); // Program counter'i set eder
    void setInstr (string instruction);
    //Halt instruction'in kontrolu icin instruction set eder.
    void setOption (int opt);//Programin calisma secenegini set eder (0 veya 1)
    string getInstr () const ;
    //Halt instruction'in kontrolu icin instruction'i alir.
    int getReg (int index) const ;
    //Verilen index'e gore registerin degerini alir.
    int getPC () const ;//Program counter'i alir.
    int getOption() const ;//Programin calisma secenegini alir.
    bool halted ();//Programin calisip calismadigini kontrol eder.
    void execute (string line,Memory& mainMemory);
    //Bir komut satiri alarak programi calistirir.
    void print () const ;//Her bir registeri ve program counter'i ekrana basar.
    string concatString (string str,string str2,string str3,string command);
    //Verilen uc stringi birlestirir.
    bool move(string str,string str2,Memory& mem,const Parse& obj);
    //Registera registerin icindeki degeri kopyalar,
    //Registera sabit bir sayiyi kopyalar,
    //Memory'deki adresin gosterdigi degeri register'a, register'in 
    //icindeki degeri memory'nin adresine veya memory'deki adresin icerisine
    //sabit bir sayiyi kopyalar.
    void print(string str,Memory& mem,const Parse &obj);
    //Registerin degerini ekrana basar,
    //Memory'deki adresin gosterdigi degeri ekrana basar veya
    //Sabit bir sayiyi ekrana basar.
    bool substraction(string str,string str2,Memory& mem,const Parse& obj);
    //Iki registeri birbirinden cikarir,
    //Registerin icerisindeki degeri sabit bir sayidan cikarir, veya
    //Registerin icerisindeki degeri memory'deki adresin gosterdigi 
    //degerden cikarir.
    bool add(string str,string str2,Memory& mem,const Parse& obj);
    //Iki registeri toplar, ve topladigi registera yazar,
    //Registerin icerisindeki degeri sabit bir sayi ile toplar ve topladıgı
    //registera yazar veya
    //Registerin icerisindeki degeri memory'deki adresin gosterdigi 
    //degerle toplar ve registera yazar.
    int jump(string str,string str2,const Parse& obj);
    //Eger verilen register'in degeri sifir olursa gosterilen satira atlar, veya
    //gosterilen satira direkt olarak atlar.
    int jpnInstr (string str,string str2,const Parse& obj);
    //Eger verilen register sifir veya kucukse gosterilen satira atlar.
    int identifyRegister (string str) const;
    //Register'in hangisi oldugunu belirler.
    int identifyInstructions(string str) const ;
    //Instruction'in hangisi oldugunu belirler.
    int convertFromStringToInt(string str);//Verilen stringi int tipine cevirir.
private:
    int regis[REGISTER_SIZE]; //Registerlari tutacak array
    int PC; //Program Counter
    string instr; //Programin calisip calismadigini kontrol edecek string
    int option; //Programin calisma opsiyonlari
    //Sabit degiskenler
    const int REGISTER=0,CONSTANT=1,ADDRESS=2,NOT=-1;
    const int MOV=1,PRN=2,SUB=3,ADD=4,JMP=5,HLT=6,JPN=7,NOT_INSTRUCTIONS=0;
    const int NOT_NUMBER=-1, ASCII_ZERO_CH=48,DECIMAL=10, NOT_JUMP=-1;
};
#endif /* CPU_H */