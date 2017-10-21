/* 
 * Dosya Ismi: Bigram.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 21 Aralik 2016
 */

#ifndef BIGRAM_H
#define BIGRAM_H

#include "myException.h"
#include <string>
#include <iostream>

using std::string;
using std::ostream;
using std::pair;
using std::cout;

template<class T>

class Bigram {
public:
    Bigram()=default;//Constructor
    Bigram(const Bigram<T>& orig)=delete;
    virtual void readFile(string fileName)=0;//Dosyadan verileri okur.
    virtual int numGrams()=0;//Toplam ikili sayisini bulur.
    virtual int numOfGrams(T firstElement,T secondElement)=0;
    //Verilen ikilinin veri dizisi icinde kac tane oldugunu bulur.
    virtual pair<T,T> maxGrams()=0;
    //Veri dizisi icinde en cok tekrar eden ikilinin sayisini bulur.
    virtual ostream& print(ostream& out)=0;
    //Ikililerin sayisinin azalan gore ekrana basar.
    friend ostream& operator<< (ostream& output, Bigram<T>& other){return other.print(output);}
    //Operator (<<)overloading
    virtual ~Bigram()=default;//Destructor
};

#endif /* BIGRAM_H */
