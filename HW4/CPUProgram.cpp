/* 
 * Dosya Ismi: CPUProgram.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih:31 Ekim 2016 
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
string CPUProgram::getLine(int line){
    if (line>0 && line< 201)
        return commandLine[line-1];
    else{
        cerr << "Number of lines must be (1-200)" << endl;
        exit(1);
    }
}
void CPUProgram::setOption(int opt){
    option = opt;
}
int CPUProgram::getOption() const {
    return option;
}
void CPUProgram::ReadFile(string filename){
    fstream file;
    int i=0;
    file.open(filename); //Dosyanin acilmasi
    if (file.is_open()){ //Dosyanin hatali olup olmadigi kontrol edilir
        while (getline (file,commandLine[i])){ //Tum satirlarin okunmasi
            fileSize++; //Satir sayisinin bulunmasi
            i++;
        }
    }
    else
        cerr << "Error: The file could not be found." << endl; //Hata mesaji
    file.close(); //Dosyanin kapatilmasi
}
int CPUProgram::size(){
    return fileSize;
}
void CPUProgram::setSize(int totalLines) {
    fileSize = totalLines;
}
void CPUProgram::setLine (int index,string line) {
    commandLine[index-1] = line;
}