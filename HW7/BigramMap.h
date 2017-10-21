/* 
 * Dosya Ismi: BigramMap.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 21 Aralik 2016
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H

#include "Bigram.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

template <class T>

class BigramMap:public Bigram<T> {
public:
    BigramMap(int type);//Constructor
    void readFile (string fileName);//Dosyadan verileri okur.
    int numGrams();//Toplam ikili sayisini bulur.
    int numOfGrams(T firstElement,T secondElement);
    //Verilen ikilinin veri dizisi icinde kac tane oldugunu bulur.
    int searchDot (const string str,char target)const;
    //Dosyanin icinde nokta karakterini arar.
    void setPair (T* fileData);//Dosyanin icindeki tum ikilileri set eder.
    pair <T,T>maxGrams();//Veri dizisi icinde en cok tekrar eden ikilinin sayisini bulur.
    ostream& print (ostream& out);//Ikililerin sayisinin azalan gore ekrana basar.
    virtual ~BigramMap();//Destructor
private:
    T *data;//Verileri tutan degisken
    map <int,int>myMap;//Tekrar eden ikililerin sayisini tutacak olan map
    pair <T,T> *myPair;//Dosyanin icindeki ikilileri tutacak olan pair
    int dataType;//Veri tipi
    int size=0;//Dosyadaki eleman sayisi
};

#endif /* BIGRAMMAP_H */
