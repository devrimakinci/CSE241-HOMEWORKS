/* 
 * Dosya İsmi:   main.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 01 Ekim 2016
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string findRegister (string str[], int index);
//Bu fonksiyon her bir satirdaki birinci registeri veya sabit sayiyi bulur ve
//return eder.
string findRegisterTwo (string str[], int index);
//Bu fonksiyon her bir satirdaki ikinci registeri veya sabit sayiyi bulur ve
//return eder.
void removeFirstSpaces (string str[], int index);
//Bu fonksiyon her bir satirin basindaki bosluklari bulur ve bosluklari siler.
string upperCaseSensitivity (string str);
//Bu fonksiyon stringin icindeki her bir kucuk harfi buyuk harfe cevirir.
string findInstructions (string str[], int index);
//Bu fonksiyon her bir satirdaki instructionlari bulur ve return eder.
int identifyInstructions (string str[], int index);
//Bu fonksiyon hangi instructionin hangisine denk oldugunu bulur.
int identifyRegister (string str[],int index);
//Bu fonksiyon hangi registerin hangisine denk oldugunu bulur.
int convertFromStringToInt (string str[],int index);
//Bu fonksiyon stringin icindeki sayiyi integer tipine donusturur.
int halt (int line, int numberOfLines);
//Bu fonksiyon programi sonlandirir.
int move (string str[], string str2[],int regisVal[], int index);
//Bu fonksiyon registera sabit bir sayiyi veya registerin icindeki degeri 
//kopyalar.
int substraction (string str[], string str2[], int regisVal[], int index);
//Bu fonksiyon registerlari birbirinden cikarir veya sabit bir sayidan cikarir.
int add (string str[], string str2[], int regisVal[], int index);
//Bu fonksiyon registerlari toplar veya sabit bir sayiyi registera ekler.
int jump (string str[], string str2[], int registerValue[],int index);
//Bu fonksiyonun iki durumu vardir.
//1-R1 sifirsa gosterilen satira atlar.
//2-Direkt gosterlilern satira atlar.
int print (string str[],int registerValue[], int index);
//Bu fonksiyon registerlarin degerlerini ekrana basar.
void concatString (string str[],string str2[],string str3[],string command[],int size);
//Bu fonksiyon verilen uc stringi birlestirir ve yeni stringe atar.

/*----------------------Sabit Degiskenler-------------------------------------*/
const int R1=0,R2=1,R3=2,R4=3,R5=4,NOT_REGISTER=-1;
const int MOV=1,PRN=2,SUB=3,ADD=4,JMP=5,HLT=6,NOT_INSTRUCTIONS=0;
const int NOT_NUMBER=-1, ASCII_ZERO_CH=48;
const int SIZE=200, REGISTER_SIZE=5, INS_SIZE=3;
const int TRUE=1, FALSE=0,NOT_JUMP=-1,JUMP=0;
/*----------------------------------------------------------------------------*/

int main(int argc, char** argv)
{
    fstream file;
    string line [SIZE],instruction[SIZE],regis[SIZE],regis2[SIZE],temp,
            statement[SIZE];
    int reg[REGISTER_SIZE]={0,0,0,0,0},totalLine,i,j,result;
    totalLine=0;
    file.open (argv[1]);
    if (file.is_open()) //Dosyanin hatali olup olmadigi kontrol edilir.
    {
        while (getline (file,temp)) //Dosyanin icindeki satir sayisi bulunmasi
            totalLine++;
    }
    else
        cerr << "Error: The file could not be found." << endl; //Hata mesaji
    file.close ();
    file.open (argv[1]); //Dosyanin hatali olup olmadigi kontrol edilir.
    if (file.is_open())
    {
        for (i=0; i<totalLine; i++) //Dosyanin satir satir okunmasi
            getline (file,line[i]);
    }
    else 
        cerr << "Error: The file could not be found." << endl; //Hata mesaji
    file.close();
    for (i=0; i<totalLine; i++)
/*-------------Her bir satirin basindaki bosluklarin silinmesi----------------*/
        removeFirstSpaces (line,i);
/*----------------------------------------------------------------------------*/
    for (i=0; i<totalLine; i++)
    {
/*-------------Her bir satirdaki instructionlarin bulunmasi-------------------*/
       instruction[i] = findInstructions (line,i);
       instruction[i] = upperCaseSensitivity (instruction[i]);
/*----------------------------------------------------------------------------*/
    }
    for (i=0; i<totalLine; i++)
/*----------------Her bir satirdaki registerlarin bulunmasi-------------------*/
        regis[i] = findRegister (line,i);
    for (i=0; i<totalLine; i++)
        regis2[i] = findRegisterTwo (line,i);
/*----------------------------------------------------------------------------*/
    
    if (*argv[2]== '0')//Option->0 olmasi durumunda
    {
        for (i=0; i<totalLine; i++)
        {
/*---------Move instructioni olmasi durumunda yapilacak islemler--------------*/
            if (identifyInstructions (instruction,i) == MOV)//
            {
                if (move (regis,regis2,reg,i) == 0)//Move fonk. cagrilmasi
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (i,totalLine); //Programin sonlanmasi
                }
            }
/*----------------------------------------------------------------------------*/
/*----------Print instructioni olmasi durumunda yapilacak islemler------------*/
            else if (identifyInstructions (instruction,i) == PRN)
            {
                result = print (regis,reg,i);
                if (result == 0)//Print fonk. cagrilmasi
                    i = halt (i,totalLine);
            }
/*----------------------------------------------------------------------------*/
/*-----Substraction instructioni olmasi durumunda yapilacak islemler----------*/
            else if (identifyInstructions (instruction,i) == SUB)
            {
                if (substraction (regis,regis2,reg,i) == 0)//Sub.fonk.cagrilmasi
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (i,totalLine); //Programin sonlanmasi
                }
            }
/*----------------------------------------------------------------------------*/
/*------------Add instructioni olmasi durumunda yapilacak islemler------------*/
            else if (identifyInstructions (instruction,i) == ADD)
            {
                if (add (regis,regis2,reg,i) == 0) //Add fonk. cagrilmasi
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (i,totalLine); //Programin sonlanmasi
                }
            }
/*------------Jump instructioni olmasi durumunda yapilacak islemler-----------*/
            else if (identifyInstructions (instruction,i) == JMP)
            {

                if (jump (regis,regis2,reg,i) == -1)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." 
                    << endl;
                    i = halt (i,totalLine); //Programin sonlanmasi
                }
                else
                    i = jump (regis,regis2,reg,i);//Jump fonk. cagrilmasi
            }
/*----------------------------------------------------------------------------*/
/*-----------Halt instructioni olmasi durumunda yapilacak islemler----------- */
            else if (identifyInstructions (instruction,i) == HLT)
            {
/* Halt instructionin yaninda herhangi bir register oldugunda yapilacak islem */
                if(((identifyRegister(regis,i)==R1||identifyRegister(regis,i)==R2))
                ||(identifyRegister(regis,i)==R3||identifyRegister(regis,i)==R4)
                ||identifyRegister(regis,i)==R5)
                    cerr << "Syntax Error:Line-"<<i+1 //Hata Mesaji
                    <<"->Unknown typing format."<<endl;
/*----------------------------------------------------------------------------*/
/*Halt instructionin yaninda herhangi bir sabit sayi oldugunda yapilacak islem*/                
                else if (convertFromStringToInt(regis,i)!=NOT_NUMBER)                 
                    cerr << "Syntax Error:Line-"<<i+1 //Hata Mesaji
                    <<"->Unknown typing format."<<endl; 
/*----------------------------------------------------------------------------*/
                i = halt (i,totalLine); //Programin sonlanmasi
            }
/*----------------------------------------------------------------------------*/
            else //Yanlis bir instruction oldugunda yapilacak islemler
            {
                cerr <<"Syntax Error: Line-"<<i+1 //Hata Mesaji
                << "->Invalid Instruction" << endl;
                i = halt (i,totalLine); // Programin sonlanmasi
            }
        }
    }
    else if (*argv[2] == '1') //Option->1 oldugu durumda
    {
/*-------------------Stringleri birlestirme islemi----------------------------*/
        concatString (instruction,regis,regis2,statement,totalLine);
        for (i=0; i<totalLine; i++)
        {
/*---------Move instructioni olmasi durumunda yapilacak islemler--------------*/
            if (identifyInstructions (instruction,i) == MOV)
            {
                if (move (regis,regis2,reg,i) == 0) //Move fonk. cagrilmasi
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (i,totalLine); //Programin sonlanmasi
                }
                else //Her bir registerin tuttugu degeri ekrana basacak.
                {
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;                 
                }
            }
/*----------------------------------------------------------------------------*/
/*----------Print instructioni olmasi durumunda yapilacak islemler------------*/
            else if (identifyInstructions (instruction,i) == PRN)
            {
                if (print (regis,reg,i) == 0) //Print fonk. cagrilmasi
                    i = halt (i,totalLine);
/*---------------Her bir registerin tuttugu degeri ekrana basacak-------------*/
                else
                {
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;                    
                }
            }
/*----------------------------------------------------------------------------*/
/*-----Substraction instructioni olmasi durumunda yapilacak islemler----------*/
            else if (identifyInstructions (instruction,i) == SUB)
            {
                if (substraction (regis,regis2,reg,i) == 0)//Sub.fonk.cagrilmasi
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (i,totalLine); // Programin sonlanmasi
                }
                else //Her bir registerin tuttugu degeri ekrana basacak.
                {
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;                 
                }
            }
/*----------------------------------------------------------------------------*/
/*------------Add instructioni olmasi durumunda yapilacak islemler------------*/           
            else if (identifyInstructions (instruction,i) == ADD)
            {
                if (add (regis,regis2,reg,i) == 0)//Add fonk. cagrilmasi
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (i,totalLine); //Programin sonlanmasi
                }
                else //Her bir registerin tuttugu degeri ekrana basacak.
                {
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;                 
                }
            }
/*----------------------------------------------------------------------------*/
/*------------Jump instructioni olmasi durumunda yapilacak islemler-----------*/            
            else if (identifyInstructions (instruction,i) == JMP)
            {
                if (jump (regis,regis2,reg,i) == -1)//Jump fonk. cagrilmasi
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line."<< endl;
                    i = halt (i,totalLine);//Programin sonlanmasi
                }
                else //Her bir registerin tuttugu degeri ekrana basacak.
                {
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                    i = jump (regis,regis2,reg,i); //Jump fonk. cagrilmasi              
                }
            }
/*----------------------------------------------------------------------------*/            
/*-----------Halt instructioni olmasi durumunda yapilacak islemler----------- */                        
            else if (identifyInstructions (instruction,i) == HLT)
            {
/* Halt instructionin yaninda herhangi bir register oldugunda yapilacak islem */                
                if(((identifyRegister(regis,i)==R1||identifyRegister(regis,i)==R2))
                ||(identifyRegister(regis,i)==R3||identifyRegister(regis,i)==R4)
                ||identifyRegister(regis,i)==R5)
                    cerr << "Syntax Error:Line-"<<i+1 //Hata Mesaji
                    <<"->Unknown typing format."<<endl;
/*----------------------------------------------------------------------------*/                            
                else if (convertFromStringToInt(regis,i)!=NOT_NUMBER)
/*Halt instructionin yaninda herhangi bir sabit sayi oldugunda yapilacak islem*/                    
                    cerr << "Syntax Error:Line-"<<i+1 //Hata Mesaji
                    <<"->Unknown typing format."<<endl;
/*----------------------------------------------------------------------------*/                
                else //Her bir registerin tuttugu degeri ekrana basacak.
                {
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                }
                i = halt (i,totalLine); //Programin sonlanmasi
            }
            else //Yanlis bir instruction oldugunda yapilacak islemler
            {
                cerr <<"Syntax Error: Line-"<<i+1 // Hata mesaji
                << "->Invalid Instruction" << endl;
                i = halt (i,totalLine); //Programin sonlanmasi
            }
        }
    }
    else // Programa yanlis bir parametre verilmesi durumunda yapilacak islem
        cout <<"Error: Invalid Parameters."<<endl; // Hata mesaji
    return 0;
}
string findRegister (string str[], int index)
{
    int i,indexOfSpace,indexOfNull,numberOfSpaces;
    i=0;
    numberOfSpaces=0; // Bosluk sayisi
    string reg[SIZE]; //Registerlari tutacak string
    indexOfSpace = str[index].find_first_of(' '); //İlk boslugun indeksi
    while (str[index][i] != '\0') //Bosluk sayisinin bulunmasi
    {
        if (str[index][i] == ' ')
            numberOfSpaces++;
        i++;
    }
    if (str[index].size() == numberOfSpaces+INS_SIZE)
        return reg[index] = str[index];
    if (indexOfSpace == -1)
        return reg[index] = str[index];
    reg[index] = str[index].substr (indexOfSpace);
    removeFirstSpaces (reg,index); //Bosluklarin silinmesi
/*---------------Stringin icindeki yorumlarin ayiklanmasi---------------------*/    
    for (i=0; (reg[index][i]!= ' ' && reg[index][i]!= ','); i++)
    {
        ;
    }
/*----------------------------------------------------------------------------*/
    reg[index] = reg[index].substr(0,i);
    indexOfNull = str[index].find_first_of('\0');//İlk null karakterin indeksi
    reg[index] = reg[index].substr(0,indexOfNull);
    return reg[index];  
}
string findRegisterTwo (string str[], int index)
{
    int i,indexOfSpace,indexOfNull,numberOfSpaces;
    string reg[SIZE]; //Registerlari tutacak string
    i=0;
    numberOfSpaces=0; //Bosluk sayisi
    indexOfSpace = str[index].find_first_of(' ');//İlk boslugun indeksi
    while (str[index][i] != '\0') //Bosluk sayisinin bulunmasi
    {
        if (str[index][i] == ' ')
            numberOfSpaces++;
        i++;
    }
    if (str[index].size() == numberOfSpaces+INS_SIZE)
        return reg[index] = str[index];
    if (indexOfSpace == -1)
        return reg[index] = str[index];
    reg[index] = str[index].substr (indexOfSpace);
    removeFirstSpaces (reg,index); //Bosluklarin silinmesi
    indexOfSpace= reg[index].find_first_of(' '); //İlk boslugun indeksi
    if (indexOfSpace == -1)
        return reg[index];
    reg[index] = reg[index].substr (indexOfSpace);
    removeFirstSpaces (reg,index); //Bosluklarin silinmesi
/*---------------Stringin icindeki yorumlarin ayiklanmasi---------------------*/    
    for (i=0; (reg[index][i]== ' ' || reg[index][i]== ','); i++)
    {
        ;
    }
    reg[index] = reg[index].substr(i);
/*----------------------------------------------------------------------------*/    
    indexOfSpace = reg[index].find_first_of(' '); //İlk boslugun indeksi
    reg[index] = reg[index].substr(0,indexOfSpace);
    indexOfNull = str[index].find_first_of('\0');//İlk null karakterin indeksi
    reg[index] = reg[index].substr(0,indexOfNull);
    return reg[index];  
}

void removeFirstSpaces (string str[], int index)
{
    int numberOfSpaces; //Bosluk sayisi
    numberOfSpaces=0;
    while (str[index][numberOfSpaces] == ' ') //Bosluk sayisinin bulunmasi
        numberOfSpaces++;
    str[index].erase(0,numberOfSpaces); //Bosluklarin silinmesi
}

string findInstructions (string str[], int index)
{
    int idx,i,numberOfSpaces;
    i=0;
    numberOfSpaces = 0; //Bosluk sayisi
    string instruction; //Instructionlarin tutuldugu indeks
    idx = str[index].find_first_of(' '); //İlk boslugun indeksi
    while (str[index][i] != '\0') //Bosluk sayisinin bulunmasi
    {
        if (str[index][i] == ' ')
            numberOfSpaces++;
        i++;
    }
    if (str[index].size() == numberOfSpaces+INS_SIZE)
    {
        instruction = str[index].substr(0,idx);
        return instruction;
    }
    if (idx == -1)
    {
        if (str[index].size() == INS_SIZE)
            return instruction = str[index];
/*----------------Stringin icindeki yorumlarin silinmesi----------------------*/
        for (i=0; str[index][i]!=';'; i++)
        {
            ;
        }
        instruction = str[index].erase(i);
        return instruction; 
/*----------------------------------------------------------------------------*/
    }
    instruction = str[index].substr(0,idx); //Instructionin ayiklanmasi
    return instruction;
}
string upperCaseSensitivity (string str)
{
    int j;
    for (j=0; j<str.size(); j++) //Kucuk harfleri buyuk harfe cevirmesi
    {
            if (str[j] >= 'a' && str[j] <= 'z')
       		str[j] += 'A' - 'a';
    }
    return str;
}
int identifyInstructions (string str[],int index)
{
/*---------------------Instructionlarin belirlenmesi--------------------------*/
    if (str[index].compare("MOV") == 0)
        return MOV;
    else if (str[index].compare("PRN") == 0)
        return PRN;
    else if (str[index].compare("SUB") == 0)
        return SUB;
    else if (str[index].compare("ADD") == 0)
        return ADD;
    else if (str[index].compare("JMP") == 0)
        return JMP;
    else if (str[index].compare("HLT") == 0)
        return HLT;
    else
        return NOT_INSTRUCTIONS;
/*----------------------------------------------------------------------------*/
}
int identifyRegister (string str[],int index)
{
/*---------------------Registerlarin belirlenmesi-----------------------------*/
    if ((str[index].compare("R1") && str[index].compare("r1"))== 0)
        return R1;
    else if ((str[index].compare("R2") && str[index].compare("r2")) == 0)
        return R2;
    else if ((str[index].compare("R3") && str[index].compare("r3")) == 0)
        return R3;
    else if ((str[index].compare("R4") && str[index].compare("r4")) == 0)
        return R4;
    else if ((str[index].compare("R5") && str[index].compare("r5")) == 0)
        return R5;
    else 
        return NOT_REGISTER;
/*----------------------------------------------------------------------------*/
}
int convertFromStringToInt (string str[],int index)
{
    int i,sum;
    sum=0;
    i=0;
    if (str[index][i] == '\0')
        return NOT_NUMBER;
    else
    {
        for (i=0; str[index][i]!='\0'; i++) //Stringi integer tipine cevirme
        {
            if (str[index][i] >= '0' && str[index][i] <= '9')
                sum = (sum * 10) + str[index][i] - ASCII_ZERO_CH;
            else
                return NOT_NUMBER;
        }
    }
    return sum;
}
int halt (int line, int numberOfLines)
{
    line = numberOfLines;
    return line;
}
int print(string str[],int registerValue[],int index)
{
    int value;
    if (identifyRegister (str,index) == R1)
    {
        cout << "R1=" <<registerValue[R1] << endl;
        return TRUE;
    }
    else if (identifyRegister (str,index) == R2)
    {
        cout << "R2=" <<registerValue[R2] << endl;        
        return TRUE;
    }
    else if (identifyRegister (str,index) == R3)
    {
        cout << "R3=" <<registerValue[R3] << endl;
        return TRUE;
    }
    else if (identifyRegister (str,index) == R4)
    {
        cout << "R4=" <<registerValue[R4] << endl;
        return TRUE;
    }
    else if (identifyRegister (str,index) == R5)
    {
        cout << "R5=" <<registerValue[R5] << endl;
        return TRUE;
    }
    else if (identifyRegister (str,index) == NOT_REGISTER)
    {
        value = convertFromStringToInt (str,index);
        if (value != NOT_NUMBER)
        {
            cout << "VALUE=" << value << endl;
            return TRUE;
        }
        else
        {
            cerr << "Syntax Error: Line-" << index+1 //Hata mesaji
            << "->It must be register or constant in this line." << endl;
            return FALSE;
        }
    }
    else
    {
        cerr << "Syntax Error: Line-" << index+1 //Hata mesaji
        << "->It must be register or constant in this line." << endl;
        return FALSE;
    }
}
int move(string str[],string str2[],int regisVal[],int index)
{
    int value; //sabit sayiyi tutan degisken
    if (identifyRegister (str,index) == R1)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R1] = regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R1] = regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R1] = regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R1] = regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R1] = regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R1] = value;
                return TRUE;
            }       
        }
    }
    else if (identifyRegister (str,index) == R2)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R2] = regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R2] = regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R2] = regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R2] = regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R2] = regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R2] = value;
                return TRUE;
            }
        }
    }
    else if (identifyRegister (str,index) == R3)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R3] = regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R3] = regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R3] = regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R3] = regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R3] = regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R3] = value;
                return TRUE;
            }
        }
    }    
    else if (identifyRegister (str,index) == R4)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R4] = regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R4] = regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R4] = regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R4] = regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R4] = regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R4] = value;
                return TRUE;
            }
        }
    }
    else if (identifyRegister (str,index) == R5) 
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R5] = regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R5] = regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R5] = regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R5] = regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R5] = regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R5] = value;
                return TRUE;
            }
        }
    }
    return FALSE;
}
int substraction (string str[], string str2[], int regisVal[], int index)
{
    int value;// sabit sayiyi tutan degisken
    if (identifyRegister (str,index) == R1)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R1] = regisVal[R1] - regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R1] = regisVal[R1] - regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R1] = regisVal[R1] - regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R1] = regisVal[R1] - regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R1] = regisVal[R1] - regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R1] = regisVal[R1] - value;
                return TRUE;
            }
        }
    }
    else if (identifyRegister (str,index) == R2)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R2] = regisVal[R2] - regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R2] = regisVal[R2] - regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R2] = regisVal[R2] - regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R2] = regisVal[R2] - regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R2] = regisVal[R2] - regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R2] = regisVal[R2] - value;
                return TRUE;
            }
        }
    }
    else if (identifyRegister (str,index) == R3)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R3] = regisVal[R3] - regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R3] = regisVal[R3] - regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R3] = regisVal[R3] - regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R3] = regisVal[R3] - regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R3] = regisVal[R3] - regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R3] = regisVal[R3] - value;
                return TRUE;
            }
        }
    }    
    else if (identifyRegister (str,index) == R4)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R4] = regisVal[R4] - regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R4] = regisVal[R4] - regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R4] = regisVal[R4] - regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R4] = regisVal[R4] - regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R4] = regisVal[R4] - regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R4] = regisVal[R4] - value;
                return TRUE;
            }
        }
    }
    else if (identifyRegister (str,index) == R5) 
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R5] = regisVal[R5] - regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R5] = regisVal[R5] - regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R5] = regisVal[R5] - regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R5] = regisVal[R5] - regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R5] = regisVal[R5] - regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R5] = regisVal[R5] - value;
                return TRUE;
            }
        }
    }
    return FALSE;
}
int add (string str[], string str2[], int regisVal[], int index)
{
    int value; //sabit sayiyi tutan degisken
    if (identifyRegister (str,index) == R1)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R1] = regisVal[R1] + regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R1] = regisVal[R1] + regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R1] = regisVal[R1] + regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R1] = regisVal[R1] + regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R1] = regisVal[R1] + regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R1] = regisVal[R1] + value;
                return TRUE;
            }
            
        }
    }
    else if (identifyRegister (str,index) == R2)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R2] = regisVal[R2] + regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R2] = regisVal[R2] + regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R2] = regisVal[R2] + regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R2] = regisVal[R2] + regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R2] = regisVal[R2] + regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R2] = regisVal[R2] + value;
                return TRUE;
            }
        }
    }
    else if (identifyRegister (str,index) == R3)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R3] = regisVal[R3] + regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R3] = regisVal[R3] + regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R3] = regisVal[R3] + regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R3] = regisVal[R3] + regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R3] = regisVal[R3] + regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R3] = regisVal[R3] + value;
                return TRUE;
            }
        }
    }    
    else if (identifyRegister (str,index) == R4)
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R4] = regisVal[R4] + regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R4] = regisVal[R4] + regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R4] = regisVal[R4] + regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R4] = regisVal[R4] + regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R4] = regisVal[R4] + regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R4] = regisVal[R4] + value;
                return TRUE;
            }
        }
    }
    else if (identifyRegister (str,index) == R5) 
    {
        if (identifyRegister (str2,index) == R1)
        {
            regisVal[R5] = regisVal[R5] + regisVal[R1];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R2)
        {
            regisVal[R5] = regisVal[R5] + regisVal[R2];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R3)
        {
            regisVal[R5] = regisVal[R5] + regisVal[R3];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R4)
        {
            regisVal[R5] = regisVal[R5] + regisVal[R4];
            return TRUE;
        }
        else if (identifyRegister (str2,index) == R5)
        {
            regisVal[R5] = regisVal[R5] + regisVal[R5];
            return TRUE;
        }
        else
        {
            value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
            if (value != NOT_NUMBER)
            {
                regisVal[R5] = regisVal[R5] + value;
                return TRUE;
            }
        }
    }
    return FALSE;
}
int jump (string str[], string str2[], int registerValue[],int index)
{
    int value; //sabit sayiyi tutan degisken
    if (identifyRegister (str,index) == R1)
    {
        value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
        if (value != NOT_NUMBER)
        {
            if (registerValue[R1] == 0) //R1 sifirsa gosterilen satira atlamasi
                return value-2;
        }
        else
            return NOT_JUMP;
    }
    else if (identifyRegister (str,index) == R2)
    {
        value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
        if (value != NOT_NUMBER)
        {
            if (registerValue[R2] == 0)//R2 sifirsa gosterilen satira atlamasi
                return value-2;
        }
        else
            return NOT_JUMP;
    }
    else if (identifyRegister (str,index) == R3)
    {
        value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
        if (value != NOT_NUMBER)
        {
            if (registerValue[R3] == 0)//R3 sifirsa gosterilen satira atlamasi
                return value-2;
        }
        else
            return NOT_JUMP;
    }
    else if (identifyRegister (str,index) == R4)
    {
        value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
        if (value != NOT_NUMBER)
        {
            if (registerValue[R4] == 0)//R4 sifirsa gosterilen satira atlamasi
                return value-2;
        }
        else
            return NOT_JUMP;
    }
    else if (identifyRegister (str,index) == R5)
    {
        value = convertFromStringToInt (str2,index);//İnteger tipine cevirme
        if (value != NOT_NUMBER)
        {
            if (registerValue[R5] == 0)//R5 sifirsa gosterilen satira atlamasi
                return value-2;
        }
        else
            return NOT_JUMP;
    }
    else //Gosterilen satira direkt atlama 
    {
        value = convertFromStringToInt (str,index);//İnteger tipine cevirme
        if (value != NOT_NUMBER)
            return value-2;
        else 
            return NOT_JUMP;
    }
    return index;
}
void concatString (string str[],string str2[],string str3[],string command[],int size)
{
    int i;
    for (i=0; i<size; i++) // String birlestirme islemi
    {
        str[i] = upperCaseSensitivity (str[i]);
        str2[i] = upperCaseSensitivity (str2[i]);
        str3[i] = upperCaseSensitivity (str3[i]);
        if ((str3[i][0] == 'R') || (str3[i][0]>='0' && str3[i][0]<='9'))
            command[i].append(str[i]+" "+str2[i]+","+str3[i]);
        else if (((str2[i][0]=='R')||(str2[i][0]>='0'&&str2[i][0]<='9')))
            command[i].append(str[i]+" "+str2[i]);
        else
            command[i].append(str[i]);
    }
}
