/* 
 * Dosya Ismi: myException.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 21 Aralik 2016
 */

#include "myException.h"

myException::myException(){
}

myException::myException(int dataType){
    type = dataType;
}
myException::~myException() {
}

const char* myException::what() const noexcept {
    if (type == 1)
        return "Invalid file. There are string or double data types in file!\n";
    else if (type == 2)
        return "Invalid file. There are integer or double data types in file!\n";
    else if (type == 3)
        return "Invalid file. There are integer or string data types in file!\n";
    else if (type == -1)
        return "First line of file is empty!\n";
    return "File could not open!\n";
}
