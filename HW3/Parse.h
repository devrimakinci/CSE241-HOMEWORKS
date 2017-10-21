/* 
 * Dosya Ismi: Parse.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 22 Ekim 2016 Cumartesi
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
private:
    string instruction; //Instructionlarin tutuldugu string
    string reg1; //Dosyadaki ilk registeri veya sabit sayiyi tutacak olan string
    string reg2;//Dosyadaki ikinci registeri veya sabit sayiyi tutacak olan string
};

#endif /* PARSE_H */

