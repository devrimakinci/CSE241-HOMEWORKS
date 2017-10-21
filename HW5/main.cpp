/* 
 * Dosya Ismi:   main.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 13 Kasim 2016
 * 
 */

#include "requiredIncs.h"

int main(int argc, char** argv){
    //////////////////////////////////////////////////////////////////////////
    //command line parameters
    const char* filename = argv[1];
    int option = atoi(argv[2]);
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    //Testing class CPUProgram
    //op []
    CPUProgram myCPUProgram(option);
    
    myCPUProgram.ReadFile(filename);
    
    cout << myCPUProgram[1] << endl;
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    
    //op +
    CPUProgram otherProg(option);
    otherProg = myCPUProgram + "MOV R1, 100";
    cout << otherProg[otherProg.size() - 1] << endl;
    
    //op +=
    myCPUProgram += "MOV R2, #50";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
     
    //op + <<
    CPUProgram myOtherCPUProgram(option);
    myOtherCPUProgram.ReadFile(filename);
    
    --myOtherCPUProgram;
    cout << (myCPUProgram + myOtherCPUProgram) << endl;
    
    //op COMP --
    cout << (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
    
    cout << myOtherCPUProgram-- << endl;
    cout << myOtherCPUProgram[myOtherCPUProgram.size() -1] << endl;
    
    cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
    
    //op ()
    cout << myCPUProgram(1, 3) << endl;
    //error check
    cout << myCPUProgram[myCPUProgram.size()] << endl;
    
    myCPUProgram += "";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    
    cout << myCPUProgram (-3,4) << endl;
    //////////////////////////////////////////////////////////////////////////
    return 0;
}