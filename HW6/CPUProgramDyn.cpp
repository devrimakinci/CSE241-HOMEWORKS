/* 
 * Dosya Ismi: CPUProgramDyn.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 26 Kasim 2016
 */

#include "CPUProgramDyn.h"
#include "CPU.h"

namespace Program{
    CPUProgramDyn::CPUProgramDyn(string fileName) {
        ReadFile (fileName); //Dosyanin okunmasi
    }
    CPUProgramDyn::CPUProgramDyn(int opt){
        setOption(opt);
        commandLine = new string[size()];
    }
    CPUProgramDyn::CPUProgramDyn(){
        commandLine = new string[size()];
    }

    CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& otherProgram){
        commandLine = new string[otherProgram.size()];
        setSize(otherProgram.size());
        for (int i=0; i<size(); i++)
            commandLine[i] = otherProgram.commandLine[i];
    }
    CPUProgramDyn::~CPUProgramDyn(){
        delete []commandLine;
    }
    string CPUProgramDyn::getLine(int line)const {
        return commandLine[line];
    }
    void CPUProgramDyn::setOption(int opt){
        option = opt;
    }
    int CPUProgramDyn::getOption() const {
        return option;
    }
    string* CPUProgramDyn::reallocDyn (int size){
        //Pointer yeni bir boyutu olan arrayi gosterir.
        string *newCommandLine = new string[size];
        //Yeni array'e eski array'in icindekiler atanir.
        for (int i=0; i<this->size(); i++)
            newCommandLine[i] = commandLine[i];
        delete []commandLine;//Pointerin gosterdigi yeri siler.
        commandLine = newCommandLine;//Pointer yeni olusturulan arrayi gosterir.
        return commandLine;
    }
    void CPUProgramDyn::ReadFile(string filename){
        fstream file;
        string temp = "";
        file.open(filename); //Dosyanin acilmasi
        if (file.is_open()){ //Dosyanin hatali olup olmadigi kontrol edilir
            while (getline (file,temp)) //Satir sayisinin bulunmasi
                fileSize++;
        }
        else{
            cerr << "Error: The file could not be found." << endl; //Hata mesaji
            exit(1);
        }
        file.close(); //Dosyanin kapatilmasi
        commandLine = new string[fileSize];
        file.open(filename);
        if (file.is_open()){
            for (int i=0; i<fileSize; i++)
                getline (file,commandLine[i]);
        }
        else{
            cerr << "Error: The file could not be found." << endl; //Hata mesaji
            exit(1);
        }
    }
    int CPUProgramDyn::size() const {
        return fileSize;
    }
    void CPUProgramDyn::setSize(int totalLines) {
        fileSize = totalLines;
    }
    void CPUProgramDyn::setLine (int index,string line) {
        commandLine[index] = line;
    }
    string CPUProgramDyn::operator [](int index){
        if (index<0 || index>=size()){//Indeks sifirdan kucuk veya size'dan buyukse
            cerr << "WARNING: Range out size!" << endl; //Uyari mesaji
            return "";
        }
        for (int i=0; i<size(); i++){
            if (index == i)
                return getLine(i);
        }
    }
    CPUProgramDyn CPUProgramDyn::operator +(const string instr){
        int numberSpaces=0; //Verilen stringteki bosluk sayisi
        //Verilen stringteki bosluk sayisinin bulunmasi
        CPUProgramDyn newProgram(getOption());
        newProgram.setSize(size());
        newProgram.commandLine = new string[newProgram.size()];
        for (int i=0; instr[i]!='\0'; i++){ 
            if (instr[i] == ' ')
                numberSpaces++;
        }
        if (instr.compare("") == 0){ //Verilen string null ise
            //Uyari mesaji
            cerr << "WARNING:Given string should be valid. Not null string" << endl;
            return newProgram;
        }
        else if (numberSpaces == instr.length()){ //Verilen string bos ise
            cerr << "Error: Given string should be valid. Not empty string" << endl;
            return newProgram;
        }
        for (int i=0; i<size(); i++)
            newProgram.commandLine[i] = commandLine[i];
        //Sonuna yeni bir instruction ekleneceginden dolayi stringin 
        //boyutunun bir buyutulmesi
        int newSize = size()+1; 
        //Yeni bir size sahip olan array olusturulmasi
        newProgram.reallocDyn(newSize);
        newProgram.setSize(newProgram.size() + 1);//Filesize'in bir buyutulmesi
        newProgram.commandLine[newSize-1] = instr;//Son satira bir string eklenmesi
        return newProgram;
    }
    const CPUProgramDyn& CPUProgramDyn::operator +=(const string instr){
        int numberSpaces=0; //Verilen stringteki bosluk sayisi
        //Verilen stringteki bosluk sayisinin bulunmasi
        for (int i=0; instr[i]!='\0'; i++){
            if (instr[i] == ' ')
                numberSpaces++;
        }
        if (instr.compare("") == 0){//Verilen string null ise
            CPUProgramDyn *emptyProgram;
            //Uyari mesaji
            cerr << "WARNING:Given string should be valid. Not null string" << endl;
            return *emptyProgram;//Bos obje dondurulmesi
        }
        else if (numberSpaces == instr.length()){//Bos bir string verilirse
            CPUProgramDyn *emptyProgram;
            //Hata mesaji
            cerr << "Error: Given string should be valid. Not empty string" << endl;
            return *emptyProgram;//Bos obje dondurulmesi
        }
        //Yeni bir size sahip olan array olusturulmasi
        reallocDyn(size()+1);
        setSize(size()+1);//Filesize'in bir buyutulmesi
        commandLine[size()-1] = instr;//Son satira bir string eklenmesi
        return *this;
    }
    const CPUProgramDyn CPUProgramDyn::operator +(const CPUProgramDyn& otherProg){
        CPUProgramDyn newProgram(getOption()); //Yeni bir program olusturulmasi
        //Yeni programin size'in ayarlanmasi
        newProgram.setSize(size() + otherProg.size());
        newProgram.commandLine = new string[newProgram.size()];
        //Verilen bir programin icindeki satir sayisinin sifir veya negatif olmasi
        if (otherProg.size() <= 0 || size() <= 0){
            cerr << "Error: Size of file of program can not be zero or negative" 
            << endl;
            return newProgram;//Bos obje dondurulmesi
        }
        for (int i=0; i<size(); i++)
            newProgram.commandLine[i] = commandLine[i];
        for (int i=size(),j=0; j<otherProg.size(); i++,j++)
            newProgram.commandLine[i] = otherProg.commandLine[j];
        return newProgram;
    }
    ostream& operator<< (ostream& out, const CPUProgramDyn &otherProg) {
        for (int i=0; i<otherProg.size(); i++)
            out << otherProg.getLine(i) << endl; 
        return out;
    }
    bool CPUProgramDyn::operator ==(const CPUProgramDyn& otherProgram) const {
        return (size() == otherProgram.size());
    }
    bool CPUProgramDyn::operator !=(const CPUProgramDyn& otherProgram) const {
        return (size() != otherProgram.size());
    }
    bool CPUProgramDyn::operator <(const CPUProgramDyn& otherProgram) const {
        return (size() < otherProgram.size());
    }
    bool CPUProgramDyn::operator <=(const CPUProgramDyn& otherProgram) const {
        return (size() <= otherProgram.size());
    }
    bool CPUProgramDyn::operator >(const CPUProgramDyn& otherProgram) const {
        return (size() > otherProgram.size());
    }
    bool CPUProgramDyn::operator >=(const CPUProgramDyn& otherProgram) const {
        return (size() >= otherProgram.size());
    }
    CPUProgramDyn& CPUProgramDyn::operator --(){
        string *newCommandLine = new string[size()-1];
        for (int i=0; i<size()-1; i++)
            newCommandLine[i] = commandLine[i];
        delete []commandLine;//Pointerin gosterdigi yeri siler.
        commandLine = newCommandLine;//Pointer yeni olusturulan arrayi gosterir.
        setSize (size()-1);//Filesize bir azaltilmasi
        return *this;
    }
    CPUProgramDyn CPUProgramDyn::operator --(int){
        CPUProgramDyn temp(getOption());
        temp.setSize(size());
        temp.commandLine = new string[temp.size()];
        for (int i=0; i<size(); i++)
            //Diger programin satirlarinin temp programina eklenmesi
            temp.commandLine[i] = commandLine[i];
        string *newCommandLine = new string[size()-1];
        for (int i=0; i<size()-1; i++)
            newCommandLine[i] = commandLine[i];
        delete []commandLine;//Pointerin gosterdigi yeri siler.
        commandLine = newCommandLine;//Pointer yeni olusturulan arrayi gosterir.
        setSize (size()-1);//Filesize bir azaltilmasi
        return temp;
    }
    const CPUProgramDyn CPUProgramDyn::operator ()(int index1, int index2) {
        CPUProgramDyn newProgram(getOption());
        if (index2 > size()){ //Ikinci indeks programin size'indan buyukse
            cerr << "WARNING:Second index can not be bigger than program size!\n";
            return newProgram;//Bos obje dondurulmesi
        }
        else if (index1 > index2){ //Ilk indeks ikinci indeksten buyukse
            cerr << "WARNING:First index can not be bigger than second index!\n";
            return newProgram;//Bos obje dondurulmesi
        }
        else if (index1 < 0){
            cerr << "WARNING:First index can not be negative\n";
            return newProgram;//Bos obje dondurulmesi
        }
        int newSize = (index2 - index1) + 1; //Yeni programin size
        newProgram.setSize(newSize);
        newProgram.commandLine = new string[newProgram.size()];
        for (int i=index1,j=0; i<=index2; i++,j++){
            //Verilen satirlar arasinda yeni bir program olusturma
            newProgram.commandLine[j] = commandLine[i]; 
        }
        return newProgram;
    }
    CPUProgramDyn& CPUProgramDyn::operator=(const CPUProgramDyn& otherProgram){
        if (this == &otherProgram)//Gelen obje kendisi ile ayniysa
            return *this;
        else{
            int newSize = otherProgram.size();
            delete []commandLine;//Pointerin gosterdigi yeri siler.
            //Gelen objenin size degerinde yeni bir string olusturulmasi
            commandLine = new string[newSize];
            //Yeni olusturulan stringin gelen objenin stringine atanmasi
            for (int i=0; i<newSize; i++)
                commandLine[i] = otherProgram.commandLine[i];
            return *this;
        }
    }
}