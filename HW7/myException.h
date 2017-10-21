/* 
 * Dosya Ismi: myException.h
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 21 Aralik 2016
 */

#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>

using std::cout;
using std::exception;

class myException:public exception {
public:
    myException();
    myException(int dataType);
    const char* what() const noexcept;
    virtual ~myException();
private:
    int type=0;
};

#endif /* MYEXCEPTION_H */
