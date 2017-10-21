/* 
 * Dosya Ismi: Parse.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 31 Ekim 2016 
 */

#ifndef PARSE_H
#define PARSE_H

#include <string>

using namespace std; // String kullanimi icin

const int INS_SIZE=3; //Instructionlarin karakter sayisi

class Parse {
public:
    //Verilen stringin basindaki boslukari siler.
    void removeFirstSpaces (string &str);
    //Verilen string icinden instruction'in bulunmas,
    string findInstructions (string &str);
    //Verilen stringi buyuk harfe cevirir.
    string upperCaseSensitivity (string &str);
    //Verilen string icinden register veya sayiyi bulur.
    string findRegister (string &str);  
    //Verilen register icinden register veya sayiyi bulur.
    string findRegisterTwo (string &str);
    string getInstruction () const; //Bulunan instruction'i alir.
    string getRegister () const; //Bulunan registeri veya sayiyi alir.
    string getRegister2 () const;//Bulunan register veya sayiyi alir.
    int getIndex () const;//Registerin indexini alir.
    int getIndex2 () const;//Registerin indexini alir.
    int getConstant () const;//Sabit sayinin degerini alir.
    int getConstant2 () const; //Sabit sayinin degerini alir.
    int getAdres () const;//Memory'deki adresin indexini alir.
    int convertFromStringToInt(string str);//Verilen stringi int tipine cevirir.    
private:
    string instruction; //Instructionlarin tutuldugu string
    string reg1; //Dosyadaki ilk registeri veya sabit sayiyi tutacak olan string
    string reg2;//Dosyadaki ikinci registeri veya sabit sayiyi tutacak olan string
    int index; //Dosyadaki ilk registerin indeksini tutacak degisken
    int index2;//Dosyadaki ikinci registerin indeksini tutacak degisken
    int constant;//Dosyadaki sabit sayiyi tutacak degisken
    int constant2;//Dosyadaki sabit sayiyi tutacak degisken
    int indexAdres;//Dosyadaki adresin indeksini tutacak degisken
    //Sabit Degiskenler
    const int NOT_NUMBER=-1, ASCII_ZERO_CH=48, DECIMAL=10;
    
};

#endif /* PARSE_H */

