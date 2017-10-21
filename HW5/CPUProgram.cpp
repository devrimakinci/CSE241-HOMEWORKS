/* 
 * Dosya Ismi: CPUProgram.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 13 Kasim 2016
 */

#include "CPUProgram.h"
#include "CPU.h"

CPUProgram::CPUProgram(string fileName) {
    ReadFile (fileName); //Dosyanin okunmasi
}
CPUProgram::CPUProgram(int opt){
    setOption(opt); 
}
CPUProgram::CPUProgram(){}
string CPUProgram::getLine(int line)const {
    return commandLine[line];
}
void CPUProgram::setOption(int opt){
    option = opt;
}
int CPUProgram::getOption() const {
    return option;
}
void CPUProgram::ReadFile(string filename){
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
    setVectorSize(fileSize);
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
int CPUProgram::size() const {
    return fileSize;
}
void CPUProgram::setSize(int totalLines) {
    fileSize = totalLines;
}
void CPUProgram::setLine (int index,string line) {
    commandLine[index] = line;
}
void CPUProgram::setVectorSize(int sizeOfFile) {
    commandLine.resize(sizeOfFile);
}
string CPUProgram::operator [](int index){
    if (index<0 || index>=size()){//Indeks sifirdan kucuk veya size'dan buyukse
        cerr << "WARNING: Range out size!" << endl; //Uyari mesaji
        return "";
    }
    for (int i=0; i<size(); i++){
        if (index == i)
            return getLine(i);
    }
}
CPUProgram CPUProgram::operator +(const string instr){
    int numberSpaces=0; //Verilen stringteki bosluk sayisi
    //Verilen stringteki bosluk sayisinin bulunmasi
    CPUProgram newProgram(getOption());
    newProgram.setSize(size());
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
        exit(1);
    }
    for (int i=0; i<size(); i++)
        newProgram.commandLine.push_back(getLine(i));
    newProgram.commandLine.push_back(instr);//Son satira bir string eklenmesi
    newProgram.setSize(newProgram.size() + 1);//Filesize'in bir buyutulmesi
    return newProgram;
}
CPUProgram& CPUProgram::operator +=(const string instr){
    int numberSpaces=0; //Verilen stringteki bosluk sayisi
    //Verilen stringteki bosluk sayisinin bulunmasi
    for (int i=0; instr[i]!='\0'; i++){
        if (instr[i] == ' ')
            numberSpaces++;
    }
    if (instr.compare("") == 0){//Verilen string null ise
        //Uyari mesaji
        cerr << "WARNING:Given string should be valid. Not null string" << endl;
    }
    else if (numberSpaces == instr.length()){//Bos bir string verilirse
        //Hata mesaji
        cerr << "Error: Given string should be valid. Not empty string" << endl;
        exit(1);
    }
    commandLine.push_back(instr);//Son satira bir string eklenmesi
    setSize(size()+1);//Filesize'in bir buyutulmesi*/
    return *this;
}
CPUProgram CPUProgram::operator +(const CPUProgram& otherProg){
    CPUProgram newProgram(getOption()); //Yeni bir program olusturulmasi
    //Yeni programin size'in ayarlanmasi
    newProgram.setSize(size() + otherProg.size());
    //Verilen bir programin icindeki satir sayisinin sifir veya negatif olmasi
    if (otherProg.size() <= 0 || size() <= 0){
        cerr << "Error: Size of file of program can not be zero or negative" 
        << endl;
        exit(1);
    }
    for (int i=0; i<size(); i++)
        newProgram.commandLine.push_back(getLine(i));
    for (int i=0; i<otherProg.size(); i++)
        newProgram.commandLine.push_back(otherProg.getLine(i));
    return newProgram;
}
ostream& operator<< (ostream& out, const CPUProgram &otherProg) {
    for (int i=0; i<otherProg.size(); i++)
        out << otherProg.getLine(i) << endl; 
    return out;
}
bool CPUProgram::operator ==(const CPUProgram& otherProgram) const {
    return (size() == otherProgram.size());
}
bool CPUProgram::operator !=(const CPUProgram& otherProgram) const {
    return (size() != otherProgram.size());
}
bool CPUProgram::operator <(const CPUProgram& otherProgram) const {
    return (size() < otherProgram.size());
}
bool CPUProgram::operator <=(const CPUProgram& otherProgram) const {
    return (size() <= otherProgram.size());
}
bool CPUProgram::operator >(const CPUProgram& otherProgram) const {
    return (size() > otherProgram.size());
}
bool CPUProgram::operator >=(const CPUProgram& otherProgram) const {
    return (size() >= otherProgram.size());
}
CPUProgram& CPUProgram::operator --(){
    commandLine.pop_back();//Son satirin silinmesi
    setSize (size()-1);//Filesize bir azaltilmasi
    return *this;
}
CPUProgram CPUProgram::operator --(int){
    CPUProgram temp(getOption());
    temp.setSize(size());
    for (int i=0; i<size(); i++)
        //Diger programin satirlarinin temp programina eklenmesi
        temp.commandLine.push_back(getLine(i));
    commandLine.pop_back();//Son satirin silinmesi
    setSize (size()-1);//Filesize bir azaltilmasi
    return temp;
}
CPUProgram CPUProgram::operator ()(int index1, int index2) {
    CPUProgram newProgram(getOption());
    if (index1 > size()){ //Ilk indeks programib size'indan buyukse
    	cerr << "WARNING:First index can not be bigger than program size!\n";
        return newProgram;
    }
    if (index2 > size()){ //Ikinci indeks programin size'indan buyukse
        cerr << "WARNING:Second index can not be bigger than program size!\n";
        return newProgram;
    }
    else if (index1 > index2){ //Ilk indeks ikinci indeksten buyukse
        cerr << "WARNING:First index can not be bigger than second index!\n";
        return newProgram;
    }
    else if (index1 < 0){
        cerr << "WARNING:First index can not be negative\n";
        return newProgram;
    }
    else if (index2 < 0){
        cerr << "WARNING:Second index can not be negative\n";
        return newProgram;
    }
    int newSize = (index2 - index1) + 1; //Yeni programin size
    newProgram.setSize(newSize);
    for (int i=index1; i<=index2; i++){
        //Verilen satirlar arasinda yeni bir program olusturma
        newProgram.commandLine.push_back(getLine(i));
    }
    return newProgram;
}
