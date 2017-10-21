/* 
 * Dosya Ismi: CPUProgram.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih:22 Ekim 2016 Cumartesi
 */

#include "CPUProgram.h"

CPUProgram::CPUProgram(string fileName) {
    readFile (fileName); //Dosyanin okunmasi
}
string CPUProgram::getLine(int line){
    return commandLine[line-1];
}
void CPUProgram::readFile(string filename){
    fstream file;
    file.open(filename); //Dosyanin acilmasi
    if (file.is_open()){ //Dosyanin hatali olup olmadigi kontrol edilir
        for (int i=0; i<size(filename); i++)
            getline (file,commandLine[i]);//Tum satirlarin okunmasi
    }
    else
        cerr << "Error: The file could not be found." << endl; //Hata mesaji
    file.close(); //Dosyanin kapatilmasi
}
int CPUProgram::size(string nameOfFile){
    int totalLines = 0; //Dosyadaki satir sayisi
    string temp;//Satir sayisini okumak icin gecici olarak her satiri tutacak string
    fstream file;
    file.open(nameOfFile); //Dosyanin cilmasi
    if (file.is_open()){ //Dosyanin hatali olup olmadigi kontrol edilir
        while (getline(file,temp)){
            totalLines++;
        }
    }
    else
        cerr << "Error: The file could not be found." << endl; //Hata mesaji
    file.close();
    return totalLines;
}