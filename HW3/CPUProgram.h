/* 
 * Dosya Ismi: CPUProgram.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 22 Ekim 2016 Cumartesi
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
    string getLine (int line); //Verilen satirdaki komut satirini alir.
    void readFile (string nameOfLife);//Dosyayi okur.
    int size (string filename);//Dosyadaki satir sayisini bulur.
private:
    string commandLine[SIZE]; //Komut satiri
};

#endif /* CPUPROGRAM_H */