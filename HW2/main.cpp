/* 
 * Dosya Ismi: main.cpp
 * Adi: Devrim
 * Soyadi: AKINCI
 * Numarasi: 141044052
 * Tarih: 10 Ekim 2016 
 * 
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string findRegister (string str[], int index, int indexOfRegister[]);
//Bu fonksiyon her bir satirdaki birinci registeri veya sabit sayiyi bulur ve
//return eder.
string findRegisterTwo (string str[], int index, int indexOfRegister[]);
//Bu fonksiyon her bir satirdaki ikinci registeri veya sabit sayiyi bulur ve
//return eder.
string findInstructions (string str[], int index);
//Bu fonksiyon her bir satirdaki instructionlari bulur ve return eder.
void removeFirstSpaces (string str[], int index);
//Bu fonksiyon her bir satirin basindaki bosluklari bulur ve bosluklari siler.
int convertFromStringToInt (string str[],int index);
//Bu fonksiyon stringin icindeki sayiyi integer tipine donusturur.
int identifyRegister (string str[],int index);
//Bu fonksiyon hangi registerin hangisine denk oldugunu bulur.
int identifyInstructions (string str[],int index);
//Bu fonksiyon hangi instructionin hangisine denk oldugunu bulur.
string upperCaseSensitivity (string str);
//Bu fonksiyon stringin icindeki her bir kucuk harfi buyuk harfe cevirir.
int moveRegister (int regisVal[],int indexOfRegister1[],int indexOfRegister2[],int index);
//Bu fonksiyon registera registerin icindeki degeri kopyalar.
int moveConstant (int regisVal[],int indexOfRegister[],int constant[],int index);
//Bu fonksiyon registera sabit bir sayiyi kopyalar.
int moveAdress (string str[],string str2[],int regisVal[],uint8_t mainMemory[], int indexOfRegister[], int indexOfMemory[],int index);
//Bu fonksiyon memory'deki adresin icerisindeki degeri registera, registerin 
//icindeki degeri memory'nin adresine veya memory'deki adresin icerisine
//sabit bir sayiyi kopyalar.
int substractionRegisters(int regisVal[],int indexOfRegister1[],int indexOfRegister2[],int index);
//Bu fonksiyon registerlari birbirinden cikarir.
int substractionConstant (int regisVal[],int indexOfRegister[], int constant[],int index);
//Bu fonksiyon registerin icerisindeki degeri sabit bir sayidan cikarir.
int substractionAdress (int regisVal[],uint8_t mainMemory[],int indexOfRegister[],int indexOfMemory[], int index);
//Bu fonksiyon registerin icerisindeki degeri memory'deki adresin gosterdigi 
// degerden cıkarır.
int addRegisters(int regisVal[],int indexOfRegister1[],int indexOfRegister2[],int index);
//Bu fonksiyon iki registerin icerisindeki degeri toplar ve ilk toplanan 
//registera yazar.
int addConstant (int regisVal[],int indexOfRegister[], int constant[],int index);
//Bu fonksiyon registerin icerisindeki degeri sabit bir sayi ile toplar ve
//topladıgı registera yazar.
int addAdress (int regisVal[], uint8_t mainMemory[],int indexOfRegister[],int indexOfMemory[],int index);
//Bu fonksiyon registerin icerisindeki degeri memory'deki adresin gosterdigi 
// degerle toplar ve registera yazar.
int jumpConditionally (int registerValue[],int indexOfRegister[], int constant[],int index);
//Bu fonksiyon eger verilen register sifir olursa gosterilen satira atlar.
int jumpDirectly (int indexOfRegister[], int index);
//Bu fonksiyon gosterilen satira direkt olarak atlar.
int jpnInstr (int regisVal[],int indexOfRegister[],int constant[],int index);
//Bu fonksiyon eger verilen register sifir veya kucukse gosterilen satira atlar.
int halt (int regVal[],uint8_t memory[],int line, int numberOfLines);
//Bu fonksiyon programi sonlandirir ve tum registerlarin icerisindeki degeri 
//ekrana basar.
void print(int registerValue[],int indexOfRegister[],int index);
//Bu fonksiyon registerlarin degerlerini ekrana basar.
void printAdress (uint8_t mainMemory[],int indexOfMemory[],int index);
//Bu fonksiyon memory'deki adresin gosterdigi degeri ekrana basar.
void printConstant (int regisVal[], int indexOfRegister[], int index);
//Bu fonksiyon sabit bir sayiyi ekrana basar.
void concatString (string str[],string str2[],string str3[],string command[],int size);
//Bu fonksiyon verilen uc stringi birlestirir ve yeni stringe atar.
void InitMemory (uint8_t mainMemory[], int size);
//Bu fonksiyon memory'deki adresin gosterdigi butun degerlere sifir atar.

/*----------------------Sabit Degiskenler-------------------------------------*/
const int SIZE=200,REGISTER_SIZE=5,INS_SIZE=3,MEMORY_SIZE=50;
const int NOT_NUMBER=-1, ASCII_ZERO_CH=48;
const int MOV=1,PRN=2,SUB=3,ADD=4,JMP=5,HLT=6,JPN=7,NOT_INSTRUCTIONS=-1;
/*----------------------------------------------------------------------------*/

int main(int argc, char** argv)
{
    fstream file;
    string line [SIZE],instruction[SIZE],regis[SIZE],regis2[SIZE],temp,
            statement[SIZE];
    uint8_t memory[MEMORY_SIZE];//Memory'nin tutuldugu 1 bytelik string
    int index[SIZE],index2[SIZE],reg[REGISTER_SIZE],totalLine,i,j;
    totalLine=0; //Toplam satir
    InitMemory (memory,MEMORY_SIZE); //Memory'nin baslangic degerinin atanmasi
    file.open (argv[1]);
    if (file.is_open()) //Dosyanin hatali olup olmadigi kontrol edilir.
    {
        while (getline (file,temp)) //Dosyanin icindeki satir sayisi bulunmasi
            totalLine++;
    }
    else
        cerr << "Error: The file could not be found." << endl; //Hata mesaji
    file.close ();
    file.open (argv[1]);
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
        regis[i] = findRegister (line,i,index);
    for (i=0; i<totalLine; i++)
        regis2[i] = findRegisterTwo (line,i,index2);
    concatString (instruction,regis,regis2,statement,totalLine);//String birlestirme
    if (*argv[2]== '0')//Option->0 olmasi durumunda
    {
        for (i=0; i<totalLine; i++)
        {
/*---------Move instructioni olmasi durumunda yapilacak islemler--------------*/
            if (identifyInstructions (instruction,i) == MOV)
            {
                if (identifyRegister (regis,i) == 1)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis,i) == 2)
                {
                    if (identifyRegister (regis2,i) == 0)//Move fonk. cagrılmasi
                        moveAdress (regis,regis2,reg,memory,index,index2,i);
                    else if (identifyRegister (regis2,i) == 1)//Mov.fonk.cag.
                        moveAdress (regis,regis2,reg,memory,index,index2,i);
                }
                else if (identifyRegister(regis2,i) == 0)
                    moveRegister (reg,index,index2,i);//Move fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == 1)
                    moveConstant (reg,index,index2,i);//Move fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == 2)//Move fonk.cagrilmasi
                    moveAdress (regis,regis2,reg,memory,index,index2,i);
                else
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register or constant in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
            }    
/*----------------------------------------------------------------------------*/
/*----------Print instructioni olmasi durumunda yapilacak islemler------------*/
            else if (identifyInstructions (instruction,i) == PRN)
            {
                if (identifyRegister(regis,i) == 0)
                    print (reg,index,i);//Print fonk. cagrilmasi
                else if (identifyRegister(regis,i) == 1)
                    printConstant (reg,index,i);//Print fonk. cagrilmasi
                else if (identifyRegister(regis,i) == 2)
                    printAdress (memory,index,i);//Print fonk. cagrilmasi
                else 
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register or constant in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
            }
/*----------------------------------------------------------------------------*/
/*-----Substraction instructioni olmasi durumunda yapilacak islemler----------*/
            else if (identifyInstructions (instruction,i) == SUB)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister (regis,i) == 1))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis2,i) == 0)//Sub.fonk.cagrilmasi
                    substractionRegisters (reg,index,index2,i);
                else if (identifyRegister (regis2,i) == 1)//Sub.fonk.cagrilmasi
                    substractionConstant (reg,index,index2,i);
                else if (identifyRegister (regis2,i) == 2)//Sub.fonk.cagrilmasi
                    substractionAdress (reg,memory,index,index2,i);
                else
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
            }
/*----------------------------------------------------------------------------*/
/*------------Add instructioni olmasi durumunda yapilacak islemler------------*/
            else if (identifyInstructions (instruction,i) == ADD)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister (regis,i) == 1))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis2,i) == 0) 
                    addRegisters (reg,index,index2,i);//Add fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == 1)
                    addConstant (reg,index,index2,i);//Add fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == 2)
                    addAdress (reg,memory,index,index2,i);//Add fonk. cagrilmasi
                else
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
            }
/*------------Jump instructioni olmasi durumunda yapilacak islemler-----------*/
            else if (identifyInstructions (instruction,i) == JMP)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister(regis2,i) == 0))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis,i) == 1)
                        i = jumpDirectly (index,i);//Jump fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == -1 ||
                        identifyRegister (regis2,i) == 2)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis2,i) == 1)
                    i = jumpConditionally (reg,index,index2,i);//Jump cagrilmasi
            }
/*----------------------------------------------------------------------------*/            
/*-------------JPN instructioni olmasi durumunda yapilacak islemler-----------*/            
            else if (identifyInstructions (instruction,i) == JPN)
            {
                if ((identifyRegister (regis,i) == 1 || 
                        (identifyRegister (regis,i) == 2 ||
                        identifyRegister (regis,i) == -1)))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if ((identifyRegister (regis2,i) == 0 ||
                        (identifyRegister (regis2,i) == 2 ||
                    identifyRegister (regis2,i) == -1)))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis2,i) == 1)
                    i = jpnInstr (reg,index,index2,i);//Jump fonk. cagrilmasi
            }
/*----------------------------------------------------------------------------*/
/*-----------Halt instructioni olmasi durumunda yapilacak islemler----------- */
            else if (identifyInstructions (instruction,i) == HLT)
                i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
/*----------------------------------------------------------------------------*/
            else //Yanlis bir instruction oldugunda yapilacak islemler
            {
                cerr <<"Syntax Error: Line-"<<i+1 //Hata Mesaji
                << "->Invalid Instruction" << endl;
                i = halt (reg,memory,i,totalLine); // Programin sonlanmasi
            }
        }
    }
    else if (*argv[2] == '1') //Option->1 olmasi durumunda
    {
        for (i=0; i<totalLine; i++)
        {
/*---------Move instructioni olmasi durumunda yapilacak islemler--------------*/
            if (identifyInstructions (instruction,i) == MOV)//
            {
                if (identifyRegister (regis,i) == 1)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis,i) == 2)
                {
                    if (identifyRegister (regis2,i) == 0)
                        moveAdress (regis,regis2,reg,memory,index,index2,i);
                    else if (identifyRegister (regis2,i) == 1)
                        moveAdress (regis,regis2,reg,memory,index,index2,i);
                }
                else if (identifyRegister(regis2,i) == 0)//Move fonk.cagrilmasi
                    moveRegister (reg,index,index2,i);
                else if (identifyRegister (regis2,i) == 1)//Move fonk.cagrilmasi
                    moveConstant (reg,index,index2,i);
                else if (identifyRegister (regis2,i) == 2)//Move fonk.cagrilmasi
                    moveAdress (regis,regis2,reg,memory,index,index2,i);
                else
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register or constant in this line."<<endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                //Her bir registerin tuttugu degeri ekrana basacak.
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;
            }
/*----------Print instructioni olmasi durumunda yapilacak islemler------------*/
            else if (identifyInstructions (instruction,i) == PRN)
            {
                if (identifyRegister(regis,i) == 0)
                    print (reg,index,i);//Print fonk. cagrilmasi
                else if (identifyRegister(regis,i) == 1)
                    printConstant (reg,index,i);//Print fonk. cagrilmasi
                else if (identifyRegister(regis,i) == 2)
                    printAdress (memory,index,i);//Print fonk. cagrilmasi
                else 
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register or constant in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;
            }
/*----------------------------------------------------------------------------*/
/*-----Substraction instructioni olmasi durumunda yapilacak islemler----------*/
            else if (identifyInstructions (instruction,i) == SUB)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister (regis,i) == 1))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister(regis2,i) == 0)//Sub.fonk.cagrilmasi
                    substractionRegisters (reg,index,index2,i);
                else if (identifyRegister (regis2,i) == 1)//Sub.fonk.cagrilmasi
                    substractionConstant (reg,index,index2,i);
                else if (identifyRegister (regis2,i) == 2)//Sub.fonk.cagrilmasi
                    substractionAdress (reg,memory,index,index2,i);
                else if (identifyRegister (regis2,i) == -1)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (reg,memory,i,totalLine); // Programin sonlanmasi
                }
                //Her bir registerin tuttugu degeri ekrana basacak.
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;                 
            }
/*----------------------------------------------------------------------------*/
/*------------Add instructioni olmasi durumunda yapilacak islemler------------*/           
            else if (identifyInstructions (instruction,i) == ADD)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister (regis,i) == 1))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister(regis2,i) == 0)
                    addRegisters (reg,index,index2,i);//Add fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == 1)
                    addConstant (reg,index,index2,i);//Add fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == 2)
                    addAdress (reg,memory,index,index2,i);//Add fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == -1)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); // Programin sonlanmasi
                }
                //Her bir registerin tuttugu degeri ekrana basacak.
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;
            }
/*----------------------------------------------------------------------------*/
/*------------Jump instructioni olmasi durumunda yapilacak islemler-----------*/
            else if (identifyInstructions (instruction,i) == JMP)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister(regis2,i) == 0))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis,i) == 1)
                {
                    //Her bir registerin tuttugu degeri ekrana basacak.
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                    i = jumpDirectly (index,i);//Jump fonk. cagrilmasi
                }
                else if (identifyRegister (regis2,i) == -1 ||
                        identifyRegister (regis2,i) == 2)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis2,i) == 1)
                {
                    //Her bir registerin tuttugu degeri ekrana basacak.
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;    
                    i = jumpConditionally (reg,index,index2,i);//Jump cagrilmasi
                }
            }
/*----------------------------------------------------------------------------*/            
/*-------------JPN instructioni olmasi durumunda yapilacak islemler-----------*/            
            else if (identifyInstructions (instruction,i) == JPN)
            {
                if ((identifyRegister (regis,i) == 1 || 
                        (identifyRegister (regis,i) == 2 ||
                        identifyRegister (regis,i) == -1)))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if ((identifyRegister (regis2,i) == 0 ||
                        (identifyRegister (regis2,i) == 2 ||
                    identifyRegister (regis2,i) == -1)))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis2,i) == 1)
                {
                    //Her bir registerin tuttugu degeri ekrana basacak.
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                    i = jpnInstr (reg,index,index2,i);//Jump fonk. cagrilmasi
                }
            }
/*----------------------------------------------------------------------------*/
/*-----------Halt instructioni olmasi durumunda yapilacak islemler----------- */                        
            else if (identifyInstructions (instruction,i) == HLT)
            {
                //Her bir registerin tuttugu degeri ekrana basacak.
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
            }
/*----------------------------------------------------------------------------*/
            else //Yanlis bir instruction oldugunda yapilacak islemler
            {
                cerr <<"Syntax Error: Line-"<<i+1 //Hata Mesaji
                << "->Invalid Instruction" << endl;
                i = halt (reg,memory,i,totalLine); // Programin sonlanmasi
            }
        }
    }
    else if (*argv[2] == '2')//Option->2 olmasi durumunda
    {
        for (i=0; i<totalLine; i++)
        {
/*---------Move instructioni olmasi durumunda yapilacak islemler--------------*/
            if (identifyInstructions (instruction,i) == MOV)//
            {
                if (identifyRegister (regis,i) == 1)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis,i) == 2)
                {
                    if (identifyRegister (regis2,i) == 0)//Move fonk. cagrilmasi
                        moveAdress (regis,regis2,reg,memory,index,index2,i);
                    else if (identifyRegister (regis2,i) == 1)//Move fonk. cagrilmasi
                        moveAdress (regis,regis2,reg,memory,index,index2,i);
                }
                else if (identifyRegister(regis2,i) == 0)//Move fonk. cagrilmasi
                    moveRegister (reg,index,index2,i);
                else if (identifyRegister(regis2,i) == 1)//Move fonk. cagrilmasi
                    moveConstant (reg,index,index2,i);
                else if (identifyRegister(regis2,i) == 2)//Move fonk. cagrilmasi
                    moveAdress (regis,regis2,reg,memory,index,index2,i);
                else
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register or constant in this line."<<endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                //Her bir registerin tuttugu degeri ekrana basacak.
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                //Her bir memory'deki adresin gosterdigi degeri ekrana basacak.
                for (j=0; j<MEMORY_SIZE; j++)
                    cout <<"Value of Memory->" << j <<"="
                    <<static_cast <int>(memory[j]) << endl;
            }
/*----------Print instructioni olmasi durumunda yapilacak islemler------------*/
            else if (identifyInstructions (instruction,i) == PRN)
            {
                if (identifyRegister(regis,i) == 0)
                    print (reg,index,i);//Print fonk. cagrilmasi
                else if (identifyRegister(regis,i) == 1)
                    printConstant (reg,index,i);//Print fonk. cagrilmasi
                else if (identifyRegister(regis,i) == 2)
                    printAdress (memory,index,i);//Print fonk. cagrilmasi
                else 
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata mesaji
                    << "->It must be register or constant in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                //Her bir memory'deki adresin gosterdigi degeri ekrana basacak.
                for (j=0; j<MEMORY_SIZE; j++)
                    cout <<"Value of Memory->" << j <<"="
                    <<static_cast <int>(memory[j]) << endl; 
            }
/*----------------------------------------------------------------------------*/
/*-----Substraction instructioni olmasi durumunda yapilacak islemler----------*/
            else if (identifyInstructions (instruction,i) == SUB)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister (regis,i) == 1))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister(regis2,i) == 0)//Sub.fonk.cagrilmasi
                    substractionRegisters (reg,index,index2,i);
                else if (identifyRegister (regis2,i) == 1)//Sub.fonk.cagrilmasi 
                    substractionConstant (reg,index,index2,i);
                else if (identifyRegister (regis2,i) == 2)//Sub.fonk.cagrilmasi
                    substractionAdress (reg,memory,index,index2,i);
                else if (identifyRegister (regis2,i) == -1)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line." <<endl; 
                    i = halt (reg,memory,i,totalLine); // Programin sonlanmasi
                }
                //Her bir registerin tuttugu degeri ekrana basacak.
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;                 
                //Her bir memory'deki adresin gosterdigi degeri ekrana basacak.
                for (j=0; j<MEMORY_SIZE; j++)
                    cout <<"Value of Memory->" << j <<"="
                    <<static_cast <int>(memory[j]) << endl; 
            }
/*----------------------------------------------------------------------------*/
/*------------Add instructioni olmasi durumunda yapilacak islemler------------*/           
            else if (identifyInstructions (instruction,i) == ADD)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister (regis,i) == 1))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister(regis2,i) == 0)
                    addRegisters (reg,index,index2,i);//Add fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == 1)
                    addConstant (reg,index,index2,i);//Add fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == 2)
                    addAdress (reg,memory,index,index2,i);//Add fonk. cagrilmasi
                else if (identifyRegister (regis2,i) == -1)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register or constant in this line."<<endl; 
                    i = halt (reg,memory,i,totalLine); // Programin sonlanmasi
                }
                //Her bir registerin tuttugu degeri ekrana basacak.
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                //Her bir memory'deki adresin gosterdigi degeri ekrana basacak.
                for (j=0; j<MEMORY_SIZE; j++)
                    cout <<"Value of Memory->" << j <<"="
                    <<static_cast <int>(memory[j]) << endl; 
            }
/*----------------------------------------------------------------------------*/
/*------------Jump instructioni olmasi durumunda yapilacak islemler-----------*/
            else if (identifyInstructions (instruction,i) == JMP)
            {
                if (identifyRegister (regis,i) == -1 ||
                        (identifyRegister (regis,i) == 2||
                        identifyRegister(regis2,i) == 0))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis,i) == 1)
                {
                    //Her bir registerin tuttugu degeri ekrana basacak.
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                    for (j=0; j<MEMORY_SIZE; j++)
                    //Her bir memory'deki adresin gosterdigi degeri ekrana basacak.
                        cout <<"Value of Memory->" << j <<"="
                        <<static_cast <int>(memory[j]) << endl; 
                    i = jumpDirectly (index,i);//Jump cagrilmasi
                }
                else if (identifyRegister (regis2,i) == -1 ||
                        identifyRegister (regis2,i) == 2)
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis2,i) == 1)
                {
                    //Her bir registerin tuttugu degeri ekrana basacak.
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;    
                    for (j=0; j<MEMORY_SIZE; j++)
                    //Her bir memory'deki adresin gosterdigi degeri ekrana basacak.
                        cout <<"Value of Memory->" << j <<"="
                        <<static_cast <int>(memory[j]) << endl; 
                    i = jumpConditionally (reg,index,index2,i);//Jump cagrilmasi
                }
            }
/*----------------------------------------------------------------------------*/            
/*-------------JPN instructioni olmasi durumunda yapilacak islemler-----------*/            
            else if (identifyInstructions (instruction,i) == JPN)
            {
                if ((identifyRegister (regis,i) == 1 || 
                        (identifyRegister (regis,i) == 2 ||
                        identifyRegister (regis,i) == -1)))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be register in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if ((identifyRegister (regis2,i) == 0 ||
                        (identifyRegister (regis2,i) == 2 ||
                    identifyRegister (regis2,i) == -1)))
                {
                    cerr << "Syntax Error: Line-" << i+1 //Hata Mesaji
                    << "->It must be constant in this line."<< endl;
                    i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
                }
                else if (identifyRegister (regis2,i) == 1)
                {
                    //Her bir registerin tuttugu degeri ekrana basacak.
                    cout << statement[i] << "-";
                    for (j=0; j<REGISTER_SIZE-1; j++)
                        cout << "R" <<j+1 << "=" <<reg[j] << ",";
                    cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                    for (j=0; j<MEMORY_SIZE; j++)
                    //Her bir memory'deki adresin gosterdigi degeri ekrana basma
                        cout <<"Value of Memory->" << j <<"="
                        <<static_cast <int>(memory[j]) << endl; 
                    i = jpnInstr (reg,index,index2,i);//Jump cagrilmasi
                }
            }
/*----------------------------------------------------------------------------*/
/*-----------Halt instructioni olmasi durumunda yapilacak islemler----------- */                        
            else if (identifyInstructions (instruction,i) == HLT)
            {
                //Her bir registerin tuttugu degeri ekrana basacak.
                cout << statement[i] << "-";
                for (j=0; j<REGISTER_SIZE-1; j++)
                    cout << "R" <<j+1 << "=" <<reg[j] << ",";
                cout << "R" <<j+1 << "=" <<reg[j]<<endl;
                for (j=0; j<MEMORY_SIZE; j++)
                //Her bir memory'deki adresin gosterdigi degeri ekrana basacak.
                    cout <<"Value of Memory->" << j <<"="
                    <<static_cast <int>(memory[j]) << endl;
                i = halt (reg,memory,i,totalLine); //Programin sonlanmasi
            }
/*----------------------------------------------------------------------------*/
            else //Yanlis bir instruction oldugunda yapilacak islemler
            {
                cerr <<"Syntax Error: Line-"<<i+1 //Hata Mesaji
                << "->Invalid Instruction" << endl;
                i = halt (reg,memory,i,totalLine); // Programin sonlanmasi
            }
        }
    }
    else // Programa yanlis bir parametre verilmesi durumunda yapilacak islem
        cout <<"Error: Invalid Parameters."<<endl; // Hata mesaji
    return 0;
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
string findRegister (string str[], int index, int indexOfRegister [])
{
    int i,indexOfSpace,numberOfSpaces,indexOfR,indexOfSharp;
    i=0;
    numberOfSpaces=0; // Bosluk sayisi
    string reg[SIZE]; //Registerlari tutacak string
    indexOfSpace = str[index].find_first_of(' '); //İlk boslugun indeksi
    reg[index] = str[index].substr (indexOfSpace);
    removeFirstSpaces (reg,index); //Bosluklarin silinmesi
/*---------------Stringin icindeki yorumlarin ayiklanmasi---------------------*/    
    for (i=0; ((reg[index][i]!= ' ' && reg[index][i]!= ',') &&reg[index][i]!=';'); i++)
    {
        ;
    }
/*----------------------------------------------------------------------------*/
    reg[index] = reg[index].substr(0,i);
    indexOfR = reg[index].find_first_of('R');//ilk R harfinin indeksi
    if (indexOfR == -1)
    {
        indexOfR = reg[index].find_first_of('r');//ilk r harfinin indeksi
        if (indexOfR == -1)
        {   
            indexOfSharp = reg[index].find_first_of('#');//ilk # karakterinin indeksi
            if (indexOfSharp == -1)
            {
                //Integer tipine cevrilmesi
                indexOfRegister[index] = convertFromStringToInt (reg,index);
                return reg[index];
            }
            else
            {
                reg[index] = reg[index].substr(1);
                //Integer tipine cevrilmesi
                indexOfRegister[index] = convertFromStringToInt (reg,index);
                reg[index].insert(0,1,'#');//Stringe # karakteri eklenmesi
                return reg[index];
            }
        }
        else
        {
            reg[index] = reg[index].substr(1);
            //Integer tipine cevrilmesi
            indexOfRegister[index] = convertFromStringToInt (reg,index);
            reg[index].insert(0,1,'R'); //Stringe R harfinin eklenmesi
            return reg[index];
        }
    }
    reg[index] = reg[index].substr(1);
    //Integer tipine cevrilmesi
    indexOfRegister[index] = convertFromStringToInt (reg,index);
    reg[index].insert(0,1,'R');//Stringe R harfinin eklenmesi
    return reg[index];  
}
string findRegisterTwo (string str[], int index, int indexOfRegister[])
{
    int i,indexOfSpace,numberOfSpaces,indexOfR,indexOfSharp;
    string reg[SIZE]; //Registerlari tutacak string
    i=0;
    numberOfSpaces=0; //Bosluk sayisi
    indexOfSpace = str[index].find_first_of(' ');//İlk boslugun indeksi
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
    indexOfR = reg[index].find_first_of('R');//ilk R harfinin indeksi
    if (indexOfR == -1)
    {
        indexOfR = reg[index].find_first_of('r');//ilk r harfinin indeksi
        if (indexOfR == -1)
        {   
            indexOfSharp = reg[index].find_first_of('#');//ilk # karakterinin indeksi
            if (indexOfSharp == -1)
            {
                //Integer tipine cevrilmesi
                indexOfRegister[index] = convertFromStringToInt (reg,index);
                return reg[index];
            }
            else
            {
                reg[index] = reg[index].substr(1);
                //Integer tipine cevrilmesi
                indexOfRegister[index] = convertFromStringToInt (reg,index);
                reg[index].insert(0,1,'#');//Stringe # karakterinin eklenmesi
                return reg[index];
            }
        }
        else
        {
            reg[index] = reg[index].substr(1);
            //Integer tipine cevrilmesi
            indexOfRegister[index] = convertFromStringToInt (reg,index);
            reg[index].insert(0,1,'R');//Stringe R harfinin eklenmesi
            return reg[index];
        }
    }
    reg[index] = reg[index].substr(1);
    //Integer tipine cevrilmesi
    indexOfRegister[index] = convertFromStringToInt (reg,index);
    reg[index].insert(0,1,'R');//Stringe R harfinin eklenmesi
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
int identifyInstructions (string str[],int index)
{
/*---------------------Instructionlarin belirlenmesi---------------------------*/
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
    else if (str[index].compare("JPN") == 0)
        return JPN;
    else if (str[index].compare("HLT") == 0)
        return HLT;
    else
        return NOT_INSTRUCTIONS;
/*----------------------------------------------------------------------------*/
}
void print(int registerValue[],int indexOfRegister[],int index)
{
    int i;
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister[index])
            cout << "R" << i << "=" << registerValue [i-1] << endl;
    }
}
void printAdress (uint8_t mainMemory[],int indexOfMemory[], int index)
{
    int i,result;
    for (i=0; i<MEMORY_SIZE; i++)
    {
        if (i == indexOfMemory[index])
        {
            result = mainMemory[i];
            cout << "Value of address=" << result << endl;
        }
        else if (indexOfMemory[index] >= REGISTER_SIZE)
            cerr << "Sytanx Error Line-" << index+1 << "Invalid Address" 
            << "Address must be (0-49)" << endl;
    }
}
void printConstant (int regisVal[], int indexOfRegister[], int index)
{
    int i;
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister[index])
            cout << "Value=" << i << endl;
    }
    
}
int moveRegister(int regisVal[],int indexOfRegister1[], int indexOfRegister2[],int index)
{
    int i,j,value;
    
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister1[index])
        {
            for (j=0; j<REGISTER_SIZE; j++)
            {
                if (j == indexOfRegister2 [index])
                {
                    regisVal[i-1] = regisVal[j-1]; //Registerlarin kopyalanmasi
                    return true;
                }
            }
        }
    }
    return false;
}
int moveConstant (int regisVal[],int indexOfRegister[],int constant[], int index)
{
    int i;
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister[index])
        {
            regisVal[i-1]=constant[index];//Sabit bir sayiyi registera kopyalama
            return true;
        }
    }
    return false;
}
int moveAdress (string str[],string str2[],int regisVal[],uint8_t mainMemory[],int indexOfRegister[],int indexOfMemory[],int index)
{
    int i;
    if (str[index][0] == 'R')
    {
        for (i=0; i<MEMORY_SIZE; i++)
        {
            if (i == indexOfRegister[index])
            {
                //Registerin tuttugu degeri memory'deki gosterilen adrese yazma
                mainMemory[indexOfMemory[index]] = regisVal[i-1];
                return true;
            }
        }
    }
    else if (str[index][0]=='#' && str2[index][0]=='R')
    {
        for (i=0; i<MEMORY_SIZE; i++)
        {
            if (i == indexOfRegister[index])
            {
                //Memory'deki gosterilen adresin degerini registera kopyalanmasi
                regisVal[indexOfMemory[index]-1] = mainMemory[i];
                return true;
            }
        }
    }
    else if (str[index][0]=='#'&&(str2[index][0]>='0'&&str2[index][0]<='9'))
    {
        for (i=0; i<MEMORY_SIZE; i++)
        {
            if (i == indexOfRegister[index])
            {
           //Memory'deki gosterilen adresin degerine sabit bir sayi kopyalanmasi
                mainMemory[i] = indexOfMemory[index];
                return true;
            }
        }
    }
    return false;
}
int identifyRegister (string str[],int index)
{
    int i,indexOfR;
    i=0;
    if (str[index][i] == 'R' || str[index][i] == 'r') //Registerin belirlenmesi
        return 0;
    else if (str[index][i]>='0' && str[index][i]<='9') //Sayini belirlenmesi
        return 1;
    else if (str[index][i] == '#') //Adresin belirlenmesi
        return 2;
    else
        return -1;
}
int substractionRegisters(int regisVal[],int indexOfRegister1[],int indexOfRegister2[],int index)
{
    int i,j;
    i=0; 
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister1[index])
        {
            for (j=0; j<REGISTER_SIZE; j++)
            {
                if (j == indexOfRegister2[index])
                {
                    //Registerlarin birbirinden cikarilmasi
                    regisVal[i-1] = regisVal[i-1] - regisVal[j-1];
                    return true;
                }
            }
        }
    }
    return false;
}
int substractionConstant (int regisVal[],int indexOfRegister[], int constant[],int index)
{
    int i;
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister[index])
        {
            //Registerin sabit bir sayidan cikarilmasi
            regisVal[i-1] = regisVal[i-1] - constant[index];
            return true;
        }
    }
    return false;
}
int substractionAdress (int regisVal[],uint8_t mainMemory[],int indexOfRegister[],int indexOfMemory[], int index)
{
    int i;
    for (i=0; i<MEMORY_SIZE; i++)
    {
        if (i == indexOfRegister[index])
        {
            //Registerin memory'deki adresin gosterdigi degerden cikarilmasi
            regisVal[i-1] = regisVal[i-1] - mainMemory[indexOfMemory[index]];
            return true;
        }
    }
    
}
int addRegisters(int regisVal[],int indexOfRegister1[],int indexOfRegister2[],int index)
{
    int i,j;
    i=0; 
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister1[index])
        {
            for (j=0; j<REGISTER_SIZE; j++)
            {
                if (j == indexOfRegister2[index])
                {
                    //Registerlarin toplanmasi
                    regisVal[i-1] = regisVal[i-1] + regisVal[j-1];
                    return true;
                }
            }
        }
    }
    return false;
}
int addConstant (int regisVal[],int indexOfRegister[], int constant[],int index)
{
    int i;
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister[index])
        {
            //Registerin sabit bir sayi ile toplanmasi
            regisVal[i-1] = regisVal[i-1] + constant[index];
            return true;
        }
    }
    return false;
}
int addAdress (int regisVal[],uint8_t mainMemory[],int indexOfRegister[],int indexOfMemory[],int index)
{
    int i;
    for (i=0; i<MEMORY_SIZE; i++)
    {
        if (i == indexOfRegister[index])
        {
            //Registerin memory'deki adresin gosterdigi deger ile toplanmasi
            regisVal[i-1] = regisVal[i-1] + mainMemory[indexOfMemory[index]];
            return true;
        }
    }
}
int jumpConditionally (int registerValue[],int indexOfRegister[], int constant[],int index)
{
    int i;
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister[index])
        {
            if (registerValue[i-1] == 0) //Registerin degeri sifirsa
                return constant[index]-2; //Gosterilen satira atlanmasi
            else
                return index; //Degilse bir sonraki satira gecmesi
        }   
    }
}
int jumpDirectly (int indexOfRegister[],int index)
{
    int line;
    line = indexOfRegister[index];
    return line-2;//Gosterilen satira atlanmasi
}
int jpnInstr (int regisVal[],int indexOfRegister[],int constant[],int index)
{
    int i;
    for (i=0; i<REGISTER_SIZE; i++)
    {
        if (i == indexOfRegister[index])
        {
            if (regisVal[i-1] <= 0)//Registerin degeri sifir veya kucukse
                return constant[index]-2;//Gosterilen satira atlanmasi
            else 
                return index; //Degilse bir sonraki satira gecmesi
        }   
    }
}
int halt (int regVal[],uint8_t mainMemory[],int line, int numberOfLines)
{
    int i;
    //Tum registerlarin tuttugu degeri ekrana basma islemi
    cout << "Executed Halt instruction and value of registers" << endl << "->";
    for (i=0; i<REGISTER_SIZE; i++)
        cout << "R" << i+1 <<"=" << regVal[i] << " " ;
    //Memory'deki tum adreslerin gosterdigi degerleri ekrana basma
    cout<<endl<<"Executed Halt instruction and value of memory" << endl << "->";
    for (i=0; i<MEMORY_SIZE; i++)
        cout<<"Value of Memory->"<<i<<"="<<static_cast <int>(mainMemory[i])<<endl; 
    line = numberOfLines;
    return line; // Programin durdurulmasi
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
void concatString (string str[],string str2[],string str3[],string command[],int size)
{
    int i;
    for (i=0; i<size; i++) // String birlestirme islemi
    {
        str[i] = upperCaseSensitivity (str[i]);
        str2[i] = upperCaseSensitivity (str2[i]);
        str3[i] = upperCaseSensitivity (str3[i]);
        if ((str3[i][0] == 'R') || (str3[i][0]>='0' && str3[i][0]<='9')||
                str3[i][0]=='#')
            command[i].append(str[i]+" "+str2[i]+","+str3[i]);
        else if ((str2[i][0]=='R')||(str2[i][0]>='0'&&str2[i][0]<='9')||
                str2[i][0]=='#')
            command[i].append(str[i]+" "+str2[i]);
        else
            command[i].append(str[i]);  
    }
}
void InitMemory (uint8_t mainMemory[], int size)
{
    int i;
    for (i=0; i<size; i++)
        //Memory'deki adresin gosterdigi tum degerlere sifir atanmasi        
        mainMemory[i] = 0; 
}
