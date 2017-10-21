/* 
 * Dosya Ismi: CPUProgram.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 31 Ekim 2016 
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
#include "Parse.h"

using namespace std; //String kullanimi icin

const int SIZE=200; //Maksimum satir sayisi

class CPUProgram {
public:
    CPUProgram (string fileName); //Constructor
    CPUProgram (int opt); //Constructor 
    CPUProgram (); // No parameter constructor
    string getLine (int line); //Verilen satirdaki komut satirini alir.
    void ReadFile (string nameOfLife);//Dosyayi okur.
    int size ();//Dosyadaki satir sayisini bulur.
    void setSize (int totalLines); //Satir sayisini set eder.
    void setLine (int index, string line); //Komut satirini set eder.
    void setOption (int opt);//Programin calisma secenegini set eder(0,1 veya 2)
    int getOption() const ;//Programin calisma secenegini alir.
private:
    string commandLine[SIZE]; //Komut satiri
    int fileSize=0; //Dosyadaki satir sayisi
    int option; //Programin calisma secenegi
};

#endif /* CPUPROGRAM_H */