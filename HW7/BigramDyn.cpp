/* 
 * Dosya Ismi: BigramDyn.cpp
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 21 Aralik 2016
 */

#include "BigramDyn.h"

template <class T>
BigramDyn<T>::BigramDyn(int type){
    dataType = type;
}

template <class T>
BigramDyn<T>::~BigramDyn() {
    delete [] data;
}

template <class T>
void BigramDyn<T>::readFile(string fileName){
    fstream file;
    string temp;
    data = new T[size];
    file.open(fileName);//Dosyanin acilmasi
    if(file.is_open()){
/*---------------------Dosyadaki eleman sayisinin bulunmasi-------------------*/        
        file >> temp;
        if (temp == "")
            throw myException(-1);
        do{
/*-------------------------Hata kontrolu--------------------------------------*/
            if (dataType == 1){
//Dosyanin icinde double veya string tipi bir veri varsa program exception firlatir.
                if(temp[0] < '0' || temp[0] > '9')
                    throw myException(dataType);
                else if (searchDot(temp,'.') == 1)
                    throw myException(dataType);
            }
            else if (dataType == 2){
//Dosyanin icinde double veya integer tipi bir veri varsa program exception firlatir.                
                if ('0' <= temp[0] && temp[0] <= '9')
                    throw myException(dataType);
            }
            else if (dataType == 3){
//Dosyanin icinde integer veya string tipi bir veri varsa program exception firlatir.                
                if(temp[0] < '0' || temp[0] > '9')
                    throw myException(dataType);
                else if (searchDot(temp,'.') == 0)
                    throw myException(dataType);
            }
            else//Dosyanin ilk satiri bos ise program exception firlatir.
                throw myException(0);
/*----------------------------------------------------------------------------*/            
            size++;  
        }while(file >> temp);
/*----------------------------------------------------------------------------*/        
    }
    else//Eger dosya hatali ise program exception firlatir.
    	throw myException();
    file.close();//Dosyanin kapanmasi
    data = new T[size];
    file.open(fileName); //Dosyanin acilmasi
    if (file.is_open()){
    	for (int i=0; i<size; i++)
            file >>data[i];//Verilerin okunmasi
    }
    else//Eger dosya hatali ise program exception firlatir.
    	throw myException();
    file.close();//Dosyanin kapanmasi
}
template <class T>
int BigramDyn<T>::numGrams(){
    return size - 1;
}
template <class T>
int BigramDyn<T>::numOfGrams(T firstElement,T secondElement){
    int count=0;//Verilen ikilinin veri dizisi icinde kac tane oldugunu tutar
    if (((dataType == 1) || (dataType == 2)) || (dataType == 3)){
        for (int i=0; i<size; i++){
            if ((data[i] == firstElement) && (data[i+1] == secondElement))                
                count++;
        }
    }
    return count;
}
template <class T>
pair <T,T>BigramDyn<T>::maxGrams(){
	pair <T,T> maxPair;
    setPair (data);
    freq = new int[size-1];
    for (int i=0; i<size-1; i++)
        freq[i] = numOfGrams(data[i],data[i+1]);
    int max = freq[0];
    maxPair.first = data[0];
    maxPair.second = data[1];
    for (int i=1; i<size-1; i++){//En cok tekrar eden ikilinin bulunmasi
        if (freq[i] > max){
            freq[i] = numOfGrams(data[i],data[i+1]);   
            maxPair.first = data[i];
            maxPair.second = data[i+1];
        }
    }
    return maxPair;
}
template <class T>
int BigramDyn<T>::getSize() const{
    return size;
}

template<class T>
ostream& BigramDyn<T>::print(ostream& out){
    int temp;
    pair <T,T>tempPair;
    for (int i=0; i<size-1; i++){
        for (int j=i+1; j<size-1; j++){
//Tekrar eden ikilinin sayilarinin buyukten kucuge dogru siralanmasi            
            if (freq[i]<freq[j]){
                //Swap islemi
            	temp=freq[i];
                freq[i]=freq[j];
                freq[j]=temp;
                tempPair = myPair[i];
                myPair[i] = myPair[j];
                myPair[j] = tempPair;
            }
        }
    }
    for (int i=0; i<getSize()-1; i++)
        cout << "("<< myPair[i].first << "," <<myPair[i].second << ")->"
        << freq[i] << endl;
    delete [] freq;//Pointerin gosterdigi yeri siler.
    return out;
}
template <class T>
int BigramDyn<T>::searchDot(const string str, char target) const{
    int result=0;//Dosyanin icinde nokta karakterinin sayisini tutar
    for (int i=0; str[i] != '\0'; i++){
        if (str[i] == target)//Nokta karakterinin bulunmasi
            result++;
    }
    return result;
}
template <class T>
void BigramDyn<T>::setPair (T* fileData){
	myPair = new pair<T,T>[size-1];
	for (int i=0; i<size-1; i++){
    	myPair[i].first = fileData[i];
        myPair[i].second = fileData[i+1];
	}
}
