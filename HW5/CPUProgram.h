/* 
 * Dosya Ismi: CPUProgram.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 13 Kasim 2016
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include "Parse.h"

using namespace std; //String kullanimi icin

class CPUProgram {
public:
    CPUProgram (string fileName); //Constructor
    CPUProgram (int opt); //Constructor 
    CPUProgram (); // No parameter constructor
    string getLine (int line) const ; //Verilen satirdaki komut satirini alir.
    void ReadFile (string nameOfLife);//Dosyayi okur.
    int size () const ;//Dosyadaki satir sayisini bulur.
    void setSize (int totalLines); //Satir sayisini set eder.
    void setLine (int index, string line); //Komut satirini set eder.
    void setOption (int opt);//Programin calisma secenegini set eder(0,1 veya 2)
    void setVectorSize (int sizeOfFile); //Vectorun sizeni ayarlar.
    int getOption() const ;//Programin calisma secenegini alir.
    CPUProgram operator+ (const string instr);
    //Verilen stringi programin son satirina ekler.
    CPUProgram& operator+= (const string instr);
    //Verilen stringi programin son satirina ekler.
    CPUProgram operator+ (const CPUProgram& otherProg);
    //Verilen programin satirlarini programa ekler.
    string operator[] (int index);//Index operatoru
    //Karsilastirma operatorlerinin overload
    bool operator== (const CPUProgram &otherProgram)const ;
    bool operator!= (const CPUProgram &otherProgram)const ;
    bool operator<= (const CPUProgram &otherProgram)const ;
    bool operator>= (const CPUProgram &otherProgram)const ;
    bool operator< (const CPUProgram &otherProgram)const ;
    bool operator> (const CPUProgram &otherProgram)const ;
    ////////////////////////////////////////////////////////////////////////////
    CPUProgram& operator--(); //Prefix
    CPUProgram operator--(int); //Postfix
    CPUProgram operator() (int index1,int index2);
    //Verilen satirlar arasinda yeni bir program olusturur.
    friend ostream& operator<< (ostream& out , const CPUProgram& otherProg);
    //Programi ekrana yazdirmak icin '<<' overload edilmesi
private:
    vector <string> commandLine; //Komut satiri
    int fileSize=0; //Dosyadaki satir sayisi
    int option; //Programin calisma secenegi
    //Sabit degiskenler
};

#endif /* CPUPROGRAM_H */