/* 
 * Dosya Ismi: CPU.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 20 Ekim 2016 Perşembe
 */

#ifndef CPU_H
#define CPU_H

#include <iostream>
#include <string>
#include "Parse.h"
#include "CPUProgram.h"

using namespace std; //String kullanimi icin

const int REGISTER_SIZE=5; //Register sayisi

class CPU {
public:
    CPU(int value, int line, string instr); //Constructor
    void setReg (int value); //Butun registerlar'i sifira set eder.
    void setReg (int index, int value); //Verilen index ve degere gore register'i set eder.
    void setPC (int line); // Program counter'i set eder
    void setInstr (string instruction); //Halt instruction'in kontrolu icin instruction set eder.
    void setOption (int opt);//Programin calisma secenegini set eder (0 veya 1)
    string getInstr () const ;//Halt instruction'in kontrolu icin instruction'i alir.
    int getReg (int index) const ;//Verilen index'e gore registerin degerini alir.
    int getPC () const ;//Program counter'i alir.
    int getOption() const ;//Programin calisma secenegini alir.
    bool halted ();//Programin calisip calismadigini kontrol eder.
    void execute (string line); // Bir komut satiri alarak programi calistirir.
    void print () const ;//Her bir registeri ve program counter'i ekrana basar.
    //Verilen uc stringi birlestirir.
    string concatString (string str,string str2,string str3,string command);
    //Registerin degerinin bir register'a kopyalar veya sabit bir sayiyi
    //register'a kopyalar.
    bool move (string str, string str2);
    bool print(string str);//Registerin veya sabit bir sayinin degerini ekrana basar.
    //Verilen iki register'i birbirinden cikarir veya sabit bir sayiyi 
    //register'dan cikarir.
    bool substraction(string str, string str2);
    //Verilen iki register'i birbirine ekler veya verilen register'a sabit 
    //bir sayiyi ekler. 
    bool add (string str, string str2);
    //1-)Eger verilen register'in degeri sifirsa gosterilen satira atlar.
    //2-)Gosterilen satira direkt olarak atlar.
    int jump(string str, string str2);
    //Register'in hangisi oldugunu belirler.
    int identifyRegister (string str) const;
    //Instruction'in hangisi oldugunu belirler.
    int identifyInstructions(string str) const ;
    int convertFromStringToInt(string str);//Verilen stringi int tipine cevirir.
private:
    int regis[REGISTER_SIZE]; //Registerlari tutacak array
    int PC; //Program Counter
    string instr; //Programin calisip calismadigini kontrol edecek string
    int option; //Programin calisma opsiyonlari
    //Sabit degiskenler
    const int R1=0, R2=1, R3=2, R4=3, R5=4,NOT_REGISTER=-1;
    const int MOV=1,PRN=2,SUB=3,ADD=4,JMP=5,HLT=6,NOT_INSTRUCTIONS=0;
    const int NOT_NUMBER=-1, ASCII_ZERO_CH=48, NOT_JUMP=-1;
};
#endif /* CPU_H */