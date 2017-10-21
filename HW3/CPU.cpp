/* 
 * Dosya Ismi: CPU.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 20 Ekim 2016 Perşembe
 */

#include "CPU.h"

using namespace std; //String kullanimi icin

CPU::CPU(int value, int line, string instr) {
    setReg(value);
    setPC(line);
    setInstr(instr);
}
bool CPU::halted(){
    if (getInstr().compare("HLT") == 0)
        return true;
    else
        return false;
}
void CPU::setReg(int value){
    for (int i=0; i<REGISTER_SIZE; i++)
        regis[i] = value;
}
void CPU::setReg(int index,int value){
    regis[index] = value;
}
void CPU::setPC(int line){
    PC = line;
}
void CPU::setInstr(string instruction){
    instr = instruction;
}
void CPU::setOption(int opt){
    option = opt;
}
int CPU::getOption() const {
    return option;
}
int CPU::getPC() const {
    return PC;
}
string CPU::getInstr() const {
    return instr;
}
int CPU::getReg(int index) const {
    return regis[index];
}
void CPU::print() const {
    for (int i=0; i<REGISTER_SIZE; i++)
        cout << "R" << i+1 << "=" << getReg(i) << " ";
    cout << "PC=" << getPC() << endl; 
 }
string CPU::concatString (string str,string str2,string str3,string command){
    //String birlestirme islemi
    Parse obj;
    str = obj.upperCaseSensitivity (str);
    str2 = obj.upperCaseSensitivity (str2);
    str3 = obj.upperCaseSensitivity (str3);
    if ((str3[0] == 'R') || (str3[0]>='0' && str3[0]<='9')){
        command.append(str+" "+str2+","+str3);
        return command;
    }
    else if (((str2[0]=='R')||(str2[0]>='0'&&str2[0]<='9'))){
        command.append(str+" "+str2);
        return command;
    }
    else{
        command.append(str);
        return command;
    }
}
void CPU::execute(string line){
    Parse ob;
    string statement="";
    ob.removeFirstSpaces (line); //Bosluklarin silinmesi
    ob.upperCaseSensitivity(line);//Butun satiri buyuk harfe cevirmesi
    ob.findInstructions(line); //Satirin icinden instruction'i bulmasi
    ob.findRegister(line);//Satirin icinden register veya sayi bulmasi
    ob.findRegisterTwo(line);//Satirin icinden register veya sayi bulmasi
    string instruction = ob.getInstruction();
    string register1 = ob.getRegister();
    string register2 = ob.getRegister2();
//Programin calisip calismadigini kontrol etmek icin instrucrion'in set edilmesi
    setInstr (instruction); 
    if (getOption() == 0){ //Option-0 olmasi durumunda
        if (identifyInstructions(instruction) == MOV){
            if (!move(register1,register2)){ //Move fonksiyonun cagrilmasi
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
            else 
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
        }
        else if (identifyInstructions (instruction) == PRN){
            if (!print(register1)) //Print fonk cagrilmasi
                setInstr("HLT"); //Programin durdurulmasi
            else
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
        }
        else if (identifyInstructions(instruction) == SUB){
            if (!substraction(register1,register2)){//Subs. fonk. cagrilmasi
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
            else
                setPC(getPC() + 1); //Program counter'in arttirilmasi
        }
        else if (identifyInstructions(instruction) == ADD){
            if (!add(register1,register2)){ // Add fonksiyonun cagrilmasi
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            else
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
        }
        else if (identifyInstructions(instruction) == JMP){
            if (jump(register1,register2) == NOT_JUMP){ //Jump fonk. cagrilmasi
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            else if (getPC() == jump(register1,register2))//Jump fonk.cagrilmasi
                setPC(getPC() + 1); // Program Counter'in arttirilmasi
            else
                setPC (jump(register1,register2)); //Jump fonk. cagrilmasi
        }
        else if (identifyInstructions(instruction) == HLT){
   //Halt instructionin yaninda herhangi bir register oldugunda yapilacak islem
            if(((identifyRegister(register1)==R1||identifyRegister(register1)==R2))
            ||(identifyRegister(register1)==R3||identifyRegister(register1)==R4)
            ||identifyRegister(register1)==R5)
                cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                <<"->Unknown typing format."<<endl;
    //Halt instructionin yaninda herhangi bir sayi oldugunda yapilacak islem                
            else if (convertFromStringToInt(register1)!=NOT_NUMBER)                 
                    cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                    <<"->Unknown typing format."<<endl; 
            setInstr ("HLT"); //Programin durdurulmasi
        }
        else{ //Yanlis bir instruction oldugunda yapilacak islemler
            cerr <<"Syntax Error: Line-"<<getPC() //Hata Mesaji
            << "->Invalid Instruction" << endl;
            setInstr ("HLT"); // Programin durdurulmasi
        }
    }
    else if (getOption() == 1){
        // String birlestirme islemi
        statement=concatString(instruction,register1,register2,statement);
        if (identifyInstructions(instruction) == MOV){
            if (!move(register1,register2)){ //Move fonksiyonun cagrilmasi
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << "-";;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions (instruction) == PRN){
            if (!print(register1)) //Print fonksiyonun cagrilmasi
                setInstr("HLT"); //Programin durdurulmasi
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << "-";
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions(instruction) == SUB){
            if (!substraction(register1,register2)){//Subs. fonk. cagrilmasi
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); //Programin durdurullmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << "-";;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions(instruction) == ADD){
            if (!add(register1,register2)){ //Add fonkiyonun cagrilmasi
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << "-";;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions(instruction) == JMP){
            if (jump(register1,register2) == NOT_JUMP){ //Jump fonk. cagrilmasi
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
            else if (getPC() == jump(register1,register2)){//Jmp fonk.cagrilmasi
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
                cout << statement << "-";;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << "-";;
                print();
                setPC (jump(register1,register2)); //Jump fonk. cagrilmasi
            }
        }
        else if (identifyInstructions(instruction) == HLT){
    //Halt instructionin yaninda herhangi bir register oldugunda yapilacak islem
            if(((identifyRegister(register1)==R1||identifyRegister(register1)==R2))
            ||(identifyRegister(register1)==R3||identifyRegister(register1)==R4)
            ||identifyRegister(register1)==R5)
                cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                <<"->Unknown typing format."<<endl;
    //Halt instructionin yaninda herhangi bir sayi oldugunda yapilacak islem                
            else if (convertFromStringToInt(register1)!=NOT_NUMBER)                 
                    cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                    <<"->Unknown typing format."<<endl; 
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << "-";;
                print();
            }
            setInstr ("HLT"); // Programin durdurulmasi
        }
        else{ //Yanlis bir instruction oldugunda yapilacak islemler
            cerr <<"Syntax Error: Line-"<<getPC() //Hata Mesaji
            << "->Invalid Instruction" << endl;
            setInstr ("HLT"); // Programin sonlanmasi
        }
        statement.erase(0); //Birlestirilen stringi icini temizleme
    }
}
bool CPU::move(string str, string str2) {
    int value; //sabit sayiyi tutan degisken
    if (identifyRegister (str) == R1){
        if (identifyRegister (str2) == R1){
            setReg(R1,getReg(R1));//Reg-1'deki degeri Reg-1'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg(R1,getReg(R2));//Reg-2'deki degeri Reg-1'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg(R1,getReg(R3));//Reg-3'deki degeri Reg-1'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg(R1,getReg(R4));//Reg-4'deki degeri Reg-1'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg(R1,getReg(R5));//Reg-5'deki degeri Reg-1'e kopyalama
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg(R1,value);//Sayiyi Reg-1'e kopyalama
                return true;
            }       
        }
    }
    else if (identifyRegister (str) == R2){
        if (identifyRegister (str2) == R1){
            setReg(R2,getReg(R1));//Reg-1'deki degeri Reg-2'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg(R2,getReg(R2));//Reg-2'deki degeri Reg-2'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg(R2,getReg(R3));//Reg-3'deki degeri Reg-2'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg(R2,getReg(R4));//Reg-4'deki degeri Reg-2'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg(R2,getReg(R5));//Reg-5'deki degeri Reg-2'e kopyalama
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg(R2,value);//Sayiyi Reg-2'e kopyalama
                return true;
            }
        }
    }
    else if (identifyRegister (str) == R3){
        if (identifyRegister (str2) == R1){
            setReg(R3,getReg(R1));//Reg-1'deki degeri Reg-3'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg(R3,getReg(R2));//Reg-2'deki degeri Reg-3'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg(R3,getReg(R3));//Reg-3'deki degeri Reg-3'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg(R3,getReg(R4));//Reg-4'deki degeri Reg-3'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg(R3,getReg(R5));//Reg-5'deki degeri Reg-3'e kopyalama
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg(R3,value);//Sayiyi Reg-3'e kopyalama
                return true;
            }
        }
    }    
    else if (identifyRegister (str) == R4){
        if (identifyRegister (str2) == R1){
            setReg(R4,getReg(R1));//Reg-1'deki degeri Reg-4'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg(R4,getReg(R2));//Reg-2'deki degeri Reg-4'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg(R4,getReg(R3));//Reg-3'deki degeri Reg-4'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg(R4,getReg(R4));//Reg-4'deki degeri Reg-4'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg(R4,getReg(R5));//Reg-5'deki degeri Reg-4'e kopyalama
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg(R4,value);//Sayiyi Reg-4'e kopyalama
                return true;
            }
        }
    }
    else if (identifyRegister (str) == R5){
        if (identifyRegister (str2) == R1){
            setReg(R5,getReg(R1));//Reg-1'deki degeri Reg-5'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg(R5,getReg(R2));//Reg-2'deki degeri Reg-5'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg(R5,getReg(R3));//Reg-3'deki degeri Reg-5'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg(R5,getReg(R4));//Reg-4'deki degeri Reg-5'e kopyalama
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg(R5,getReg(R5));//Reg-5'deki degeri Reg-5'e kopyalama
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg(R5,value);//Sayiyi Reg-5'e kopyalama
                return true;
            }
        }
    }
    return false;
}
bool CPU::print(string str){
    int value;
    if (identifyRegister (str) == R1){
        cout << "R1=" <<getReg(R1) << endl;//Reg-1'in degerinin ekrana basilmasi
        return true;
    }
    else if (identifyRegister (str) == R2){
        cout << "R2=" <<getReg(R2) << endl;//Reg-2'in degerinin ekrana basilmasi  
        return true;
    }
    else if (identifyRegister (str) == R3){
        cout << "R3=" <<getReg(R3) << endl;//Reg-3'un degerinin ekrana basilmasi
        return true;
    }
    else if (identifyRegister (str) == R4){
        cout << "R4=" <<getReg(R4) << endl;//Reg-4'un degerinin ekrana basilmasi
        return true;
    }
    else if (identifyRegister (str) == R5){
        cout << "R5=" <<getReg(R5) << endl;//Reg-5'in degerinin ekrana basilmasi
        return true;
    }
    else if (identifyRegister (str) == NOT_REGISTER){
        value = convertFromStringToInt (str);
        if (value != NOT_NUMBER){
            cout << "VALUE=" << value << endl;//Sabit sayinin ekrana basilmasi
            return true;
        }
        else{
            cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
            << "->It must be register or constant in this line." << endl;
            return false;
        }
    }
    else{
        cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
        << "->It must be register or constant in this line." << endl;
        return false;
    }
}
bool CPU::substraction(string str, string str2){
    int value;// sabit sayiyi tutan degisken
    if (identifyRegister (str) == R1){
        if (identifyRegister (str2) == R1){
            setReg (R1, getReg(R1) - getReg(R1)); //Reg-1'den Reg-1 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R1, getReg(R1) - getReg(R2));//Reg-1'den Reg-2 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R1, getReg(R1) - getReg(R3));//Reg-1'den Reg-3 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R1, getReg(R1) - getReg(R4));//Reg-1'den Reg-4 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R1, getReg(R1) - getReg(R5));//Reg-1'den Reg-5 cikarilmasi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R1, getReg(R1) - value);//Reg-1'den sayinin cikarilmasi
                return true;
            }
        }
    }
    else if (identifyRegister (str) == R2){
        if (identifyRegister (str2) == R1){
            setReg (R2, getReg(R2) - getReg(R1));//Reg-2'den Reg-1 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R2, getReg(R2) - getReg(R2));//Reg-2'den Reg-2 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R2, getReg(R2) - getReg(R3));//Reg-2'den Reg-3 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R2, getReg(R2) - getReg(R4));//Reg-2'den Reg-4 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R2, getReg(R2) - getReg(R5));//Reg-2'den Reg-5 cikarilmasi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//İnteger tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R2, getReg(R2) - value);//Reg-2'den sayinin cikarilmasi
                return true;
            }
        }
    }
    else if (identifyRegister (str) == R3){
        if (identifyRegister (str2) == R1){
            setReg (R3, getReg(R3) - getReg(R1));//Reg-3'den Reg-1 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R3, getReg(R3) - getReg(R2));//Reg-3'den Reg-2 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R3, getReg(R3) - getReg(R3));//Reg-3'den Reg-3 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R3, getReg(R3) - getReg(R4));//Reg-3'den Reg-4 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R3, getReg(R3) - getReg(R5));//Reg-3'den Reg-5 cikarilmasi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//İnteger tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R3, getReg(R3) - value);//Reg-3'den sayinin cikarilmasi
                return true;
            }
        }
    }    
    else if (identifyRegister (str) == R4){
        if (identifyRegister (str2) == R1){
            setReg (R4, getReg(R4) - getReg(R1));//Reg-4'den Reg-1 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R4, getReg(R4) - getReg(R2));//Reg-4'den Reg-2 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R4, getReg(R4) - getReg(R3));//Reg-4'den Reg-3 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R4, getReg(R4) - getReg(R4));//Reg-4'den Reg-4 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R4, getReg(R4) - getReg(R5));//Reg-4'den Reg-5 cikarilmasi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R4, getReg(R4) - value);//Reg-4'den sayinin cikarilmasi
                return true;
            }
        }
    }
    else if (identifyRegister (str) == R5) {
        if (identifyRegister (str2) == R1){
            setReg (R5, getReg(R5) - getReg(R1));//Reg-5'den Reg-1 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R5, getReg(R5) - getReg(R2));//Reg-5'den Reg-2 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R5, getReg(R5) - getReg(R3));//Reg-5'den Reg-3 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R5, getReg(R5) - getReg(R4));//Reg-5'den Reg-4 cikarilmasi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R5, getReg(R5) - getReg(R5));//Reg-5'den Reg-5 cikarilmasi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R5, getReg(R5) - value);//Reg-5'den sayinin cikarilmasi
                return true;
            }
        }
    }
    return false;
}
bool CPU::add (string str, string str2){
        int value;// sabit sayiyi tutan degisken
    if (identifyRegister (str) == R1){
        if (identifyRegister (str2) == R1){
            setReg (R1, getReg(R1) + getReg(R1));//Reg-1'e Reg-1 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R1, getReg(R1) + getReg(R2));//Reg-1'e Reg-2 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R1, getReg(R1) + getReg(R3));//Reg-1'e Reg-3 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R1, getReg(R1) + getReg(R4));//Reg-1'e Reg-4 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R1, getReg(R1) + getReg(R5));//Reg-1'e Reg-5 eklenmesi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R1, getReg(R1) + value);//Reg-1'e sayi eklenmesi
                return true;
            }
        }
    }
    else if (identifyRegister (str) == R2){
        if (identifyRegister (str2) == R1){
            setReg (R2, getReg(R2) + getReg(R1));//Reg-2'e Reg-1 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R2, getReg(R2) + getReg(R2));//Reg-2'e Reg-2 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R2, getReg(R2) + getReg(R3));//Reg-2'e Reg-3 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R2, getReg(R2) + getReg(R4));//Reg-2'e Reg-4 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R2, getReg(R2) + getReg(R5));//Reg-2'e Reg-5 eklenmesi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R2, getReg(R2) + value);//Reg-2'e sayi eklenmesi
                return true;
            }
        }
    }
    else if (identifyRegister (str) == R3){
        if (identifyRegister (str2) == R1){
            setReg (R3, getReg(R3) + getReg(R1));//Reg-3'e Reg-1 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R3, getReg(R3) + getReg(R2));//Reg-3'e Reg-2 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R3, getReg(R3) + getReg(R3));//Reg-3'e Reg-3 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R3, getReg(R3) + getReg(R4));//Reg-3'e Reg-4 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R3, getReg(R3) + getReg(R5));//Reg-3'e Reg-5 eklenmesi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R3, getReg(R3) + value);//Reg-3'e sayi eklenmesi
                return true;
            }
        }
    }    
    else if (identifyRegister (str) == R4){
        if (identifyRegister (str2) == R1){
            setReg (R4, getReg(R4) + getReg(R1));//Reg-4'e Reg-1 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R4, getReg(R4) + getReg(R2));//Reg-4'e Reg-2 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R4, getReg(R4) + getReg(R3));//Reg-4'e Reg-3 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R4, getReg(R4) + getReg(R4));//Reg-4'e Reg-4 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R4, getReg(R4) + getReg(R5));//Reg-4'e Reg-5 eklenmesi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R4, getReg(R4) + value);//Reg-4'e sayi eklenmesi
                return true;
            }
        }
    }
    else if (identifyRegister (str) == R5) {
        if (identifyRegister (str2) == R1){
            setReg (R5, getReg(R5) + getReg(R1));//Reg-5'e Reg-1 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R2){
            setReg (R5, getReg(R5) + getReg(R2));//Reg-5'e Reg-2 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R3){
            setReg (R5, getReg(R5) + getReg(R3));//Reg-5'e Reg-3 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R4){
            setReg (R5, getReg(R5) + getReg(R4));//Reg-5'e Reg-4 eklenmesi
            return true;
        }
        else if (identifyRegister (str2) == R5){
            setReg (R5, getReg(R5) + getReg(R5));//Reg-5'e Reg-5 eklenmesi
            return true;
        }
        else{
            value = convertFromStringToInt (str2);//Integer tipine cevirme
            if (value != NOT_NUMBER){
                setReg (R5, getReg(R5) + value);//Reg-5'e sayi eklenmesi
                return true;
            }
        }
    }
    return false;
}
int CPU::jump(string str, string str2){
    int value; //sabit sayiyi tutan degisken
    if (identifyRegister (str) == R1){
        value = convertFromStringToInt (str2);//Integer tipine cevirme
        if (value != NOT_NUMBER){
            if (getReg(R1) == 0) //R1 sifirsa gosterilen satira atlamasi
                return value;
        }
        else
            return NOT_JUMP;
    }
    else if (identifyRegister (str) == R2){
        value = convertFromStringToInt (str2);//Integer tipine cevirme
        if (value != NOT_NUMBER){
            if (getReg(R2) == 0)//R2 sifirsa gosterilen satira atlamasi
                return value;
        }
        else
            return NOT_JUMP;
    }
    else if (identifyRegister (str) == R3){
        value = convertFromStringToInt (str2);//Integer tipine cevirme
        if (value != NOT_NUMBER){
            if (getReg(R3) == 0)//R3 sifirsa gosterilen satira atlamasi
                return value;
        }
        else
            return NOT_JUMP;
    }
    else if (identifyRegister (str) == R4){
        value = convertFromStringToInt (str2);//Integer tipine cevirme
        if (value != NOT_NUMBER){
            if (getReg(R4) == 0)//R4 sifirsa gosterilen satira atlamasi
                return value;
        }
        else
            return NOT_JUMP;
    }
    else if (identifyRegister (str) == R5){
        value = convertFromStringToInt (str2);//Integer tipine cevirme
        if (value != NOT_NUMBER){
            if (getReg(R5) == 0)//R5 sifirsa gosterilen satira atlamasi
                return value;
        }
        else
            return NOT_JUMP;
    }
    else{ //Gosterilen satira direkt atlama 
        value = convertFromStringToInt (str);//Integer tipine cevirme
        if (value != NOT_NUMBER)
            return value;
        else 
            return NOT_JUMP;
    }
    return getPC();
}
int CPU::identifyInstructions(string str) const {
/*---------------------Instructionlarin belirlenmesi--------------------------*/
    if (str.compare("MOV") == 0)
        return MOV;
    else if (str.compare("PRN") == 0)
        return PRN;
    else if (str.compare("SUB") == 0)
        return SUB;
    else if (str.compare("ADD") == 0)
        return ADD;
    else if (str.compare("JMP") == 0)
        return JMP;
    else if (str.compare("HLT") == 0)
        return HLT;
    else
        return NOT_INSTRUCTIONS;
/*----------------------------------------------------------------------------*/
}
int CPU::identifyRegister(string str) const {
/*---------------------Registerlarin belirlenmesi-----------------------------*/
    if ((str.compare("R1") && str.compare("r1"))== 0)
        return R1;
    else if ((str.compare("R2") && str.compare("r2")) == 0)
        return R2;
    else if ((str.compare("R3") && str.compare("r3")) == 0)
        return R3;
    else if ((str.compare("R4") && str.compare("r4")) == 0)
        return R4;
    else if ((str.compare("R5") && str.compare("r5")) == 0)
        return R5;
    else 
        return NOT_REGISTER;
/*----------------------------------------------------------------------------*/
}
int CPU::convertFromStringToInt(string str) {
    int i=0,sum=0;
    if (str[i] == '\0')
        return NOT_NUMBER;
    else{
        for (i=0; str[i]!='\0'; i++){ //Stringi integer tipine cevirme
            if (str[i] >= '0' && str[i] <= '9')
                sum = (sum * 10) + str[i] - ASCII_ZERO_CH;
            else
                return NOT_NUMBER;
        }
    }
    return sum;
}