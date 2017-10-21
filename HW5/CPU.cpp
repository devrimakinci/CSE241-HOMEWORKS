/* 
 * Dosya Ismi: CPU.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 13 Kasim 2016
 */

#include "CPU.h"

using namespace std; //String kullanimi icin

CPU::CPU(int value, int line, string instr) {
    setReg(value);
    setPC(line);
    setInstr(instr);
}
CPU::CPU(int opt) {
    setOption(opt);
    setReg(0);
    setPC(1);
    setInstr("");
}
CPU::CPU(){}
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
    cout << "Register Values:" << endl;
    for (int i=0; i<REGISTER_SIZE; i++)
        cout << "[" << i << "]" << "->" << getReg(i) << endl;
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
void CPU::execute(string line, Memory& mainMemory){
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
            //Move fonksiyonun cagrilmasi
            if (!move(register1,register2,mainMemory,ob)){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register, address or constant in this line." 
                << endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
            else 
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
        }
        else if (identifyInstructions (instruction) == PRN){
            print(register1,mainMemory,ob); //Print fonk cagrilmasi
            setPC(getPC() + 1); //Program Counter'in arttirilmasi
        }
        else if (identifyInstructions(instruction) == SUB){
            //Substraction fonksiyonun cagrilmasi
            if (!substraction(register1,register2,mainMemory,ob)){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register,address or constant in this line." 
                << endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
            else
                setPC(getPC() + 1); //Program counter'in arttirilmasi
        }
        else if (identifyInstructions(instruction) == ADD){
            // Add fonksiyonun cagrilmasi
            if (!add(register1,register2,mainMemory,ob)){ 
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register,address or constant in this line." 
                << endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            else
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
        }
        else if (identifyInstructions(instruction) == JMP){
            //Jump fonksiyonun cagrilmasi
            if (jump(register1,register2,ob) == NOT_JUMP){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            //Jump fonk.cagrilmasi
            else if (getPC() == jump(register1,register2,ob))
                setPC(getPC() + 1); // Program Counter'in arttirilmasi
            else
                setPC (jump(register1,register2,ob)); //Jump fonk. cagrilmasi
        }
        else if (identifyInstructions(instruction) == JPN){
            //Jpn fonksiyonun cagrilmasi
            if (jpnInstr(register1,register2,ob) == NOT_JUMP){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            //Jpn fonksiyonun cagrilmasi
            else if (getPC() == jpnInstr(register1,register2,ob))
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            else
                setPC (jpnInstr(register1,register2,ob)); //Jpn fonk. cagrilmasi
        }
        else if (identifyInstructions(instruction) == HLT){
            //Halt instructionin yaninda herhangi bir register veya adres 
            //oldugunda yapilacak islem
            if (identifyRegister(register1) == REGISTER ||
                identifyRegister(register1) == ADDRESS)
                cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                <<"->Unknown typing format."<<endl;
    //Halt instructionin yaninda herhangi bir sayi oldugunda yapilacak islem                
            else if (convertFromStringToInt(register1)!=NOT_NUMBER)                 
                    cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                    <<"->Unknown typing format."<<endl; 
            else{
                print();
                mainMemory.printAll();
            }
            setInstr ("HLT"); //Programin durdurulmasi
        }
        else{ //Yanlis bir instruction oldugunda yapilacak islemler
            cerr <<"Syntax Error: Line-"<<getPC() //Hata Mesaji
            << "->Invalid Instruction" << endl;
            setInstr ("HLT"); // Programin durdurulmasi
        }
    }
    else if (getOption() == 1){
        //String birlestirme islemi
        statement=concatString(instruction,register1,register2,statement);
        if (identifyInstructions(instruction) == MOV){
            //Move fonksiyonun cagrilmasi
            if (!move(register1,register2,mainMemory,ob)){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register, address or constant in this line." 
                << endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions (instruction) == PRN){
            print(register1,mainMemory,ob); //Print fonk cagrilmasi
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            cout << statement << endl;
            print();
            setPC(getPC() + 1); //Program Counter'in arttirilmasi
        }
        else if (identifyInstructions(instruction) == SUB){
            //Substraction fonksiyonun cagrilmasi
            if (!substraction(register1,register2,mainMemory,ob)){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register,address or constant in this line." 
                << endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions(instruction) == ADD){
            // Add fonksiyonun cagrilmasi
            if (!add(register1,register2,mainMemory,ob)){ 
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register,address or constant in this line." 
                << endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions(instruction) == JMP){
            //Jump fonksiyonun cagrilmasi
            if (jump(register1,register2,ob) == NOT_JUMP){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            //Jump fonksiyonun cagrilmasi
            else if (getPC() == jump(register1,register2,ob)){
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
                cout << statement << endl;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                setPC (jump(register1,register2,ob)); //Jump fonk. cagrilmasi
            }
        }
        else if (identifyInstructions(instruction) == JPN){
            //Jpn fonksiyonun cagrilmasi
            if (jpnInstr(register1,register2,ob) == NOT_JUMP){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            //Jpn fonksiyonun cagrilmasi
            else if (getPC() == jpnInstr(register1,register2,ob)){
                cout << statement << endl;
                print();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
            else{
                cout << statement << endl;
                print();
                setPC (jpnInstr(register1,register2,ob)); //Jpn fonk. cagrilmasi
            }
        }
        else if (identifyInstructions(instruction) == HLT){
            //Halt instructionin yaninda herhangi bir register veya adres 
            //oldugunda yapilacak islem
            if (identifyRegister(register1) == REGISTER ||
                identifyRegister(register1) == ADDRESS)
                cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                <<"->Unknown typing format."<<endl;
    //Halt instructionin yaninda herhangi bir sayi oldugunda yapilacak islem                
            else if (convertFromStringToInt(register1)!=NOT_NUMBER)                 
                    cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                    <<"->Unknown typing format."<<endl; 
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                mainMemory.printAll();
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
    else if (getOption() == 2){
        //String birlestirme islemi
        statement=concatString(instruction,register1,register2,statement);
        if (identifyInstructions(instruction) == MOV){
            //Move fonksiyonun cagrilmasi
            if (!move(register1,register2,mainMemory,ob)){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register, address or constant in this line." 
                << endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                mainMemory.printAll();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions (instruction) == PRN){
            print(register1,mainMemory,ob); //Print fonk cagrilmasi
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            cout << statement << endl;
            print();
            mainMemory.printAll();
            setPC(getPC() + 1); //Program Counter'in arttirilmasi
        }
        else if (identifyInstructions(instruction) == SUB){
            //Substraction fonksiyonun cagrilmasi
            if (!substraction(register1,register2,mainMemory,ob)){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register,address or constant in this line." 
                << endl;
                setInstr("HLT"); //Programin durdurulmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                mainMemory.printAll();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions(instruction) == ADD){
            // Add fonksiyonun cagrilmasi
            if (!add(register1,register2,mainMemory,ob)){ 
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register,address or constant in this line." 
                << endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                mainMemory.printAll();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
        }
        else if (identifyInstructions(instruction) == JMP){
            //Jump fonksiyonun cagrilmasi
            if (jump(register1,register2,ob) == NOT_JUMP){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            //Jump fonksiyonun cagrilmasi
            else if (getPC() == jump(register1,register2,ob)){
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
                cout << statement << endl;
                print();
                mainMemory.printAll();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                mainMemory.printAll();
                setPC (jump(register1,register2,ob)); //Jump fonk. cagrilmasi
            }
        }
        else if (identifyInstructions(instruction) == JPN){
            //Jpn fonksiyonun cagrilmasi
            if (jpnInstr(register1,register2,ob) == NOT_JUMP){
                cerr << "Syntax Error: Line-" << getPC() //Hata mesaji
                << "->It must be register or constant in this line." <<endl;
                setInstr("HLT"); // Programin durdurulmasi
            }
            //Jpn fonksiyonun cagrilmasi
            else if (getPC() == jpnInstr(register1,register2,ob)){
                cout << statement << endl;
                print();
                mainMemory.printAll();
                setPC(getPC() + 1); //Program Counter'in arttirilmasi
            }
            else{
                cout << statement << endl;
                print();
                mainMemory.printAll();
                setPC (jpnInstr(register1,register2,ob)); //Jpn fonk. cagrilmasi
            }
        }
        else if (identifyInstructions(instruction) == HLT){
            //Halt instructionin yaninda herhangi bir register veya adres 
            //oldugunda yapilacak islem
            if (identifyRegister(register1) == REGISTER ||
                identifyRegister(register1) == ADDRESS)
                cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                <<"->Unknown typing format."<<endl;
    //Halt instructionin yaninda herhangi bir sayi oldugunda yapilacak islem                
            else if (convertFromStringToInt(register1)!=NOT_NUMBER)                 
                    cerr << "Syntax Error:Line-"<<getPC() //Hata Mesaji
                    <<"->Unknown typing format."<<endl; 
    //Her bir registerin tuttugu degeri ve PC'nin tuttugu satiri ekrana basacak.
            else{
                cout << statement << endl;
                print();
                mainMemory.printAll();
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
    else{
        cerr << "Invalid parameters" << endl;
        setInstr("HLT");
    }
}
bool CPU::move(string str, string str2, Memory &mem, const Parse& obj){
    if (identifyRegister(str) == REGISTER && identifyRegister(str2)==REGISTER){
        if (obj.getIndex()< REGISTER_SIZE && obj.getIndex2() < REGISTER_SIZE){
            //Register'a register'daki degerinin kopyalanmasi
            setReg (obj.getIndex(),getReg(obj.getIndex2()));
            return true;
        }
        else
            return false;
    }
    else if (identifyRegister(str)==REGISTER&&identifyRegister(str2)==ADDRESS){
        if (obj.getIndex()<REGISTER_SIZE&&(obj.getAdres()>=0&&obj.getAdres()<=49)){
            //Registerin tuttugu degeri memory'deki gosterilen adrese yazma
            mem.setMem(obj.getAdres(),getReg(obj.getIndex()));
            return true;
        }
        else
            return false;
    }
    else if (identifyRegister(str)==ADDRESS&&identifyRegister(str2)==REGISTER){
        if ((obj.getAdres()>=0&&obj.getAdres()<=49)&&obj.getIndex2()<REGISTER_SIZE){
            //Memory'deki gosterilen adresin degerini registera kopyalanmasi
            setReg(obj.getIndex2(),mem.getMem(obj.getAdres()));
            return true;
        }
        else
            return false;
    }
    else if (identifyRegister(str)==REGISTER&&identifyRegister(str2)==CONSTANT){
        if (obj.getIndex()< REGISTER_SIZE && obj.getConstant2() >=0){
            //Register'a sabit sayini kopyalanmasi
            setReg(obj.getIndex(),obj.getConstant2());
            return true;
        }
        else if (obj.getConstant() < 0) //Sayinin eksi olmasi durumunda
            return false;
    }
    else if (identifyRegister(str)==ADDRESS&&identifyRegister(str2)==CONSTANT){
        if ((obj.getAdres()>=0&&obj.getAdres()<=49)&&obj.getConstant2()>=0){
           //Memory'deki gosterilen adresin degerine sabit bir sayi kopyalanmasi
            mem.setMem(obj.getAdres(),obj.getConstant2());
            return true;
        }
        else 
            return false;
    }
    return false;
}
void CPU::print(string str,Memory &mem,const Parse &obj){
    if (identifyRegister(str) == REGISTER){
        if (obj.getIndex()>=0 && obj.getIndex()<=4)
            //Register'in degerini ekrana basma
            cout << "R" << obj.getIndex() << "=" <<getReg(obj.getIndex())<<endl;
        else{
            cerr << "Sytanx Error: Line-" << getPC() << "->It must be register "
            << "and registers must be like R1,R2,R3,R4,R5" << endl;
            setInstr("HLT"); //Programin durdurulmasi
        }
    }
    else if (identifyRegister(str) == CONSTANT){
        if (obj.getConstant()>=0)
            cout << "Value=" << obj.getConstant() << endl;
        else{
            cerr << "Sytanx Error: Line-" << getPC() 
            << "->Number can not be negative" << endl;
            setInstr("HLT"); //Programin durdurulmasi
        }
    }
    else if (identifyRegister(str) == ADDRESS){
        if (obj.getAdres()>=0 && obj.getAdres()<=49)
            cout << "Value of address=" << mem.getMem(obj.getAdres()) << endl;
        else{
            cerr << "Sytanx Error: Line-" << getPC() << "->Invalid Address"
            << " Address must be (0-49)" << endl;
            setInstr("HLT"); //Programin durdurulmasi
        }
    }
    else{
        cerr << "Sytanx Error: Line-" << getPC() << "It must be register,"
        << "address or number." << endl;
        setInstr("HLT"); //Programin durdurulmasi
    }
}
bool CPU::substraction(string str, string str2, Memory &mem, const Parse& obj){
    if (identifyRegister(str) == REGISTER && identifyRegister(str2)==REGISTER){
        if (obj.getIndex()< REGISTER_SIZE && obj.getIndex2() < REGISTER_SIZE){
            //Registerlarin birbirinden cikarilmasi
            setReg(obj.getIndex(),getReg(obj.getIndex()) - getReg(obj.getIndex2()));
            return true;
        }
        else
            return false;
    }
    else if (identifyRegister(str)==REGISTER&&identifyRegister(str2)==CONSTANT){
        if (obj.getIndex()<REGISTER_SIZE && obj.getConstant2()>=0){
            //Register'in sayidan cikarilmasi
            setReg (obj.getIndex(),getReg(obj.getIndex()) - obj.getConstant2());
            return true;
        }
        else 
            return false;
    }
    else if (identifyRegister(str)==REGISTER&&identifyRegister(str2)==ADDRESS){
        if(obj.getIndex()<REGISTER_SIZE&&(obj.getAdres()>=0&&obj.getAdres()<=49)){
            //Registerin memory'deki adresin gosterdigi degerden cikarilmasi
            setReg (obj.getIndex(),getReg(obj.getIndex()) - mem.getMem(obj.getAdres()));
            return true;
        }
        else
            return false;
    }
    return false;
}
bool CPU::add(string str, string str2, Memory &mem, const Parse& obj){
    if (identifyRegister(str) == REGISTER && identifyRegister(str2)==REGISTER){
        if (obj.getIndex()< REGISTER_SIZE && obj.getIndex2() < REGISTER_SIZE){
            //Registerlarin birbirinden cikarilmasi
            setReg(obj.getIndex(),getReg(obj.getIndex()) + getReg(obj.getIndex2()));
            return true;
        }
        else
            return false;
    }
    else if (identifyRegister(str)==REGISTER&&identifyRegister(str2)==CONSTANT){
        if (obj.getIndex()<REGISTER_SIZE && obj.getConstant2()>=0){
            //Register'in sayidan cikarilmasi
            setReg (obj.getIndex(),getReg(obj.getIndex()) + obj.getConstant2());
            return true;
        }
        else 
            return false;
    }
    else if (identifyRegister(str)==REGISTER&&identifyRegister(str2)==ADDRESS){
        if(obj.getIndex()<REGISTER_SIZE&&(obj.getAdres()>=0&&obj.getAdres()<=49)){
            //Registerin memory'deki adresin gosterdigi degerden cikarilmasi
            setReg (obj.getIndex(),getReg(obj.getIndex()) + mem.getMem(obj.getAdres()));
            return true;
        }
        else
            return false;
    }
    return false;
}
int CPU::jump(string str,string str2,const Parse& obj){
    if (identifyRegister(str)==REGISTER&&identifyRegister(str2)==CONSTANT){
        if (obj.getIndex()<REGISTER_SIZE && obj.getConstant2()>0){
           if (getReg(obj.getIndex()) == 0)//Register'in degeri sifirsa
                return obj.getConstant2()-1;//Gosterilen satira atlamasi
            else
                return getPC();
        }
    }
    else if (identifyRegister(str) == CONSTANT && identifyRegister(str2)== NOT){
        if (obj.getConstant() > 0)
            return obj.getConstant()-1; //Gosterilen satira atlanmasi
    }
    else
        return NOT_JUMP;
}
int CPU::jpnInstr(string str,string str2,const Parse& obj){
    if (identifyRegister(str)==REGISTER&&identifyRegister(str2)==CONSTANT){
        if (obj.getIndex()<REGISTER_SIZE && obj.getConstant2()>0){
            if (getReg(obj.getIndex()) <= 0)//Register'in degeri sifir veya kucukse
                return obj.getConstant2()-1;
            else
                return getPC();
        }
    }
    else
        return NOT_JUMP;
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
    else if (str.compare("JPN") == 0)
        return JPN;
    else if (str.compare("HLT") == 0)
        return HLT;
    else
        return NOT_INSTRUCTIONS;
/*----------------------------------------------------------------------------*/
}
int CPU::identifyRegister(string str) const {
    int i=0;
    if (str[i] == 'R' || str[i] == 'r') //Registerin belirlenmesi
        return REGISTER;
    else if (str[i]>='0' && str[i]<='9') //Sayinin belirlenmesi
        return CONSTANT;
    else if (str[i] == '#') //Adresin belirlenmesi
        return ADDRESS;
    else
        return NOT;
}
int CPU::convertFromStringToInt(string str) {
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