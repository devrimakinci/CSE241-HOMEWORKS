/* 
 * Dosya Ismi: BigramDyn.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 21 Aralik 2016
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include "Bigram.h"
#include "myException.h"
#include <iostream>
#include <fstream>

using namespace std;

template <class T>

class BigramDyn:public Bigram<T> {
public:
    BigramDyn(int type);//Constructor
    void readFile (string fileName);//Dosyadan verileri okur.
    int numGrams();//Toplam ikili sayisini bulur.
    int numOfGrams(T firstElement,T secondElement);
    //Verilen ikilinin veri dizisi icinde kac tane oldugunu bulur.
    pair <T,T>maxGrams();//Veri dizisi icinde en cok tekrar eden ikilinin sayisini bulur.
    int getSize()const;//Dosyanin icindeki toplam eleman sayisini verir
    int searchDot (const string str,char target)const;
    //Dosyanin icinde nokta karakterini arar.
    void setPair (T* fileData);//Dosyanin icindeki tum ikilileri set eder.
    ostream& print (ostream& out);//Ikililerin sayisinin azalan gore ekrana basar.
    virtual ~BigramDyn();//Destructor
private:
    T *data;//Verileri tutan degisken
    int *freq;//Tekrar eden ikilileri tutar
    int dataType;//Veri tipi
    pair <T,T> *myPair;//Dosyanin icindeki ikilileri tutacak olan pair
    int size=0;//Dosyadaki eleman sayisi
};

#endif /* BIGRAMDYN_H */
