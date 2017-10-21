/* 
 * Dosya Ismi: CPUProgramDyn.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 26 Kasim 2016
 */

#ifndef CPUPROGRAM_H
#define CPUPROGRAM_H

#include <iostream>
#include <string>
#include <fstream>
#include "Parse.h"

using namespace std; //String kullanimi icin
namespace Program{
    class CPUProgramDyn {
    public:
        CPUProgramDyn (string fileName); //Constructor
        CPUProgramDyn (int opt); //Constructor 
        CPUProgramDyn (); // No parameter constructor
        CPUProgramDyn (const CPUProgramDyn &otherProgram); //Copy Constructor
        ~CPUProgramDyn(); //Destructor
        string getLine (int line) const ; //Verilen satirdaki komut satirini alir.
        void ReadFile (string nameOfLife);//Dosyayi okur.
        int size () const ;//Dosyadaki satir sayisini bulur.
        void setSize (int totalLines); //Satir sayisini set eder.
        void setLine (int index, string line); //Komut satirini set eder.
        void setOption (int opt);//Programin calisma secenegini set eder(0,1 veya 2)
        string* reallocDyn (int size);//Dinamik arrayin boyutunu ayarlar.
        int getOption() const ;//Programin calisma secenegini alir.
        CPUProgramDyn operator+ (const string instr);
        //Verilen stringi programin son satirina ekler.
        const CPUProgramDyn& operator+= (const string instr);
        //Verilen stringi programin son satirina ekler.
        const CPUProgramDyn operator+ (const CPUProgramDyn& otherProg);
        //Verilen programin satirlarini programa ekler.
        string operator[] (int index);//Index operatoru
        //Karsilastirma operatorlerinin overload
        bool operator== (const CPUProgramDyn &otherProgram)const ;
        bool operator!= (const CPUProgramDyn &otherProgram)const ;
        bool operator<= (const CPUProgramDyn &otherProgram)const ;
        bool operator>= (const CPUProgramDyn &otherProgram)const ;
        bool operator< (const CPUProgramDyn &otherProgram)const ;
        bool operator> (const CPUProgramDyn &otherProgram)const ;
        CPUProgramDyn& operator--(); //Prefix
        CPUProgramDyn operator--(int); //Postfix
        const CPUProgramDyn operator() (int index1,int index2);
        //Verilen satirlar arasinda yeni bir program olusturur.
        CPUProgramDyn& operator= (const CPUProgramDyn &otherProgram);
        //Atama operatorunun overload edilmesi
        friend ostream& operator<< (ostream& out , const CPUProgramDyn& otherProg);
        //Programi ekrana yazdirmak icin '<<' overload edilmesi
    private:
        string *commandLine; //Komut satirlarini gosterecek pointer
        int fileSize=0; //Dosyadaki satir sayisi
        int option; //Programin calisma secenegi
        //Sabit degiskenler
    };
}

#endif /* CPUPROGRAM_H */