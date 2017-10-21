/* 
 * Dosya Ismi: Parse.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih:22 Ekim 2016 Cumartesi
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
    int i=0,indexOfSpace,numberOfSpaces=0; // Bosluk sayisi
    indexOfSpace = str.find_first_of(' '); //İlk boslugun indeksi
    while (str[i] != '\0'){ //Bosluk sayisinin bulunmasi
        if (str[i] == ' ')
            numberOfSpaces++;
        i++;
    }
    if (str.size() == numberOfSpaces+INS_SIZE)
        return reg1 = str;
    if (indexOfSpace == -1)
        return reg1 = str;
    reg1 = str.substr (indexOfSpace);
    removeFirstSpaces (reg1); //Bosluklarin silinmesi
/*---------------Stringin icindeki yorumlarin ayiklanmasi---------------------*/    
    for (i=0; (reg1[i]!= ' ' && reg1[i]!= ','); i++){
        ;
    }
/*----------------------------------------------------------------------------*/
    reg1 = reg1.substr(0,i);
    return reg1;  
}
string Parse::findRegisterTwo(string &str){
    int i=0,indexOfSpace,numberOfSpaces=0;//Bosluk sayisi
    indexOfSpace = str.find_first_of(' ');//İlk boslugun indeksi
    while (str[i] != '\0'){ //Bosluk sayisinin bulunmasi
        if (str[i] == ' ')
            numberOfSpaces++;
        i++;
    }
    if (str.size() == numberOfSpaces+INS_SIZE)
        return reg2 = str;
    if (indexOfSpace == -1)
        return reg2 = str;
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
    return reg2;  
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