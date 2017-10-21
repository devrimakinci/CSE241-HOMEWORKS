/* 
 * Dosya Ismi: Parse.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 31 Ekim 2016 
 */

#include "Parse.h"

void Parse::removeFirstSpaces(string &str){
    int numberOfSpaces=0; //Bosluk sayisi
    //Bosluk ve tab karakterinin sayisinin bulunmasi
    while (str[numberOfSpaces] == ' ' || str[numberOfSpaces] == '\t')
        numberOfSpaces++;
    str.erase(0,numberOfSpaces); //Bosluklarin silinmesi
}
string Parse::findInstructions(string &str){
    int idx,i=0,numberOfSpaces=0;//Bosluk sayisi
    idx = str.find_first_of(' '); //İlk boslugun indeksi
    while (str[i] != '\0') {//Bosluk sayisinin bulunmasi
        if (str[i] == ' ' || str[i] == '\t')
            numberOfSpaces++;
        i++;
    }
    if (str.size() == numberOfSpaces+INS_SIZE){
        instruction = str.substr(0,idx);
        return instruction;
    }
    if (idx == -1){
        idx = str.find_first_of('\t'); //İlk tab karakterinin bulunamasi
        if (idx == -1){
            if (str.size() == INS_SIZE)
                return instruction = str;
/*----------------Stringin icindeki yorumlarin silinmesi----------------------*/
            for (i=0; str[i]!=';'; i++){
                ;
            }
            instruction = str.erase(i);
            return instruction; 
        }
        instruction = str.substr(0,idx); //Instructionin ayiklanmasi
        return instruction;
/*----------------------------------------------------------------------------*/
    }
    instruction = str.substr(0,idx); //Instructionin ayiklanmasi
    return instruction;
}
string Parse::upperCaseSensitivity (string &str){
    for (int j=0; j<str.size(); j++){ //Kucuk harfleri buyuk harfe cevirmesi
            if (str[j] >= 'a' && str[j] <= 'z')
       		str[j] += 'A' - 'a';
    }
    return str;
}
string Parse::findRegister(string &str){
    int i=0,indexOfSpace,indexOfR,indexOfSharp;
    indexOfSpace = str.find_first_of(' '); //İlk boslugun indeksi
    reg1 = str.substr (indexOfSpace);
    removeFirstSpaces (reg1); //Bosluklarin silinmesi
/*---------------Stringin icindeki yorumlarin ayiklanmasi---------------------*/    
    for (i=0; ((reg1[i]!= ' ' && reg1[i]!= ',') &&reg1[i]!=';'); i++){
        ;
    }
/*----------------------------------------------------------------------------*/
    reg1 = reg1.substr(0,i);
    indexOfR = reg1.find_first_of('R');//ilk R harfinin indeksi
    if (indexOfR == -1){
        indexOfR = reg1.find_first_of('r');//ilk r harfinin indeksi
        if (indexOfR == -1){   
            indexOfSharp = reg1.find_first_of('#');//ilk # karakterinin indeksi
            if (indexOfSharp == -1){
                //Integer tipine cevrilmesi
                constant = convertFromStringToInt (reg1);
                return reg1;
            }
            else{
                reg1 = reg1.substr(1);
                //Integer tipine cevrilmesi
                indexAdres = convertFromStringToInt (reg1);
                reg1.insert(0,1,'#');//Stringe # karakteri eklenmesi
                return reg1;
            }
        }
        else{
            reg1 = reg1.substr(1);
            //Integer tipine cevrilmesi
            index = convertFromStringToInt (reg1);
            reg1.insert(0,1,'R'); //Stringe R harfinin eklenmesi
            return reg1;
        }
    }
    reg1 = reg1.substr(1);
    //Integer tipine cevrilmesi
    index = convertFromStringToInt (reg1);
    reg1.insert(0,1,'R');//Stringe R harfinin eklenmesi
    return reg1;
}
string Parse::findRegisterTwo(string &str){
    int i=0,indexOfSpace,indexOfR,indexOfSharp;//Bosluk sayisi
    indexOfSpace = str.find_first_of(' ');//İlk boslugun indeksi
    reg2 = str.substr (indexOfSpace);
    removeFirstSpaces (reg2); //Bosluklarin silinmesi
    indexOfSpace= reg2.find_first_of(' '); //İlk boslugun indeksi
    if (indexOfSpace == -1)
        return reg2;
    reg2 = reg2.substr (indexOfSpace);
    removeFirstSpaces (reg2); //Bosluklarin silinmesi
/*---------------Stringin icindeki yorumlarin ayiklanmasi---------------------*/    
    for (i=0; (reg2[i]== ' ' || reg2[i]== ','); i++){
        ;
    }
    reg2 = reg2.substr(i);
/*----------------------------------------------------------------------------*/    
    indexOfSpace = reg2.find_first_of(' '); //İlk boslugun indeksi
    reg2 = reg2.substr(0,indexOfSpace);
    indexOfR = reg2.find_first_of('R');//ilk R harfinin indeksi    
    if (indexOfR == -1){
        indexOfR = reg2.find_first_of('r');//ilk r harfinin indeksi
        if (indexOfR == -1){   
            indexOfSharp = reg2.find_first_of('#');//ilk # karakterinin indeksi
            if (indexOfSharp == -1){
                //Integer tipine cevrilmesi
                constant2 = convertFromStringToInt (reg2);
                return reg2;
            }
            else{
                reg2 = reg2.substr(1);
                //Integer tipine cevrilmesi
                indexAdres = convertFromStringToInt (reg2);
                reg2.insert(0,1,'#');//Stringe # karakterinin eklenmesi
                return reg2;
            }
        }
        else{
            reg2 = reg2.substr(1);
            //Integer tipine cevrilmesi
            index2 = convertFromStringToInt (reg2);
            reg2.insert(0,1,'R');//Stringe R harfinin eklenmesi
            return reg2;
        }
    }
    reg2 = reg2.substr(1);
    //Integer tipine cevrilmesi
    index2 = convertFromStringToInt (reg2);
    reg2.insert(0,1,'R');//Stringe R harfinin eklenmesi
    return reg2;  
}
int Parse::convertFromStringToInt(string str) {
    int i=0,sum=0;
    if (str[i] == '\0')
        return NOT_NUMBER;
    else{
        for (i=0; str[i]!='\0'; i++){ //Stringi integer tipine cevirme
            if (str[i] >= '0' && str[i] <= '9')
                sum = (sum * DECIMAL) + str[i] - ASCII_ZERO_CH;
            else
                return NOT_NUMBER;
        }
    }
    return sum;
}
string Parse::getInstruction() const {
    return instruction;
}
string Parse::getRegister() const {
    return reg1;
}
string Parse::getRegister2() const {
    return reg2;
}
int Parse::getIndex() const {
    return index-1;
}
int Parse::getIndex2() const {
    return index2-1;
}
int Parse::getConstant() const {
    return constant;
}
int Parse::getConstant2() const {
    return constant2;
}
int Parse::getAdres() const {
    return indexAdres;
}
