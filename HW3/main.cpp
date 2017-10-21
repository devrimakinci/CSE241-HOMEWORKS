/* 
 * Dosya Ismi: main.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 20 Ekim 2016 Perşembe
 */

#include <iostream>
#include "CPU.h"
#include "CPUProgram.h"
#include "Parse.h"

using namespace std; //String kullanimi icin

int main(int argc, char** argv) {
    CPUProgram myProg(argv[1]); //Dosyanin okunmasi icin cagrilan constructor
    //Registerlara ve program countera baslangic degerlerinin verilmesi 
    //icin cagrilan constructor
    CPU myCPU (0,1,"");
    if (*argv[2] == '0'){ //Option-0 olmasi durumunda
        myCPU.setOption(0);
        while (!myCPU.halted()){ //Programin bitip bitmediginin kontrol edilmesi
            //Program counterin tuttugu satirin alinmasi
            string instruction = myProg.getLine(myCPU.getPC());
            myCPU.execute(instruction);//Alinan satiri uygun olarak calistirmasi
        }
        myCPU.print();
    }
    else if (*argv[2] == '1'){//Option-0 olmasi durumunda
        myCPU.setOption(1);
        while (!myCPU.halted()){//Programin bitip bitmediginin kontrol edilmesi
            //Program counterin tuttugu satirin alinmasi
            string instruction = myProg.getLine(myCPU.getPC());
            myCPU.execute(instruction);//Alinan satiri uygun olarak calistirmasi
        }
    }
    else{// Programa yanlis bir parametre verilmesi durumunda yapilacak islem
        cout <<"Error: Invalid Parameters."<<endl; // Hata mesaji
    }
    return 0;
}