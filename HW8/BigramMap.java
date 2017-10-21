/**
 *
 * @author devo35
 * @param <T>
 *
 * Dosya Ismi: BigramMap.java
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 06 Ocak 2017
 */

import java.io.File;
import java.io.FileNotFoundException;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.NoSuchElementException;

public class BigramMap<T> implements Bigram<T>{
    private int size;//Dosyadaki eleman sayisi
    private int [] freq;//Tekrar eden ikilileri tutar
    private Object [] data;//Verileri tutan degisken
    private int dataType;//Veri tipi
    private Scanner input;//Dosyayi okumak icin
    private Object [] first;
    private Object [] second;
    
    public BigramMap(int type){//Constructor
        dataType = type;
        size = 0;
    }
    
    public void readFile(String fileName){
        String temp;
        try{
            input = new Scanner(new File(fileName));//Dosyanin acilmasi
/*---------------------Dosyadaki eleman sayisinin bulunmasi-------------------*/                        
            do{
                try{
                    temp = input.next();
                    size++;
                }                
                catch(NoSuchElementException inputException){
                    //Dosyanin ilk satiri bos ise program exception firlatir.
                    System.err.println("First line of file is empty!");
                    throw inputException;
                }
            }while(input.hasNext());
        }
        catch (FileNotFoundException fileNotFound){
            System.err.println("Error:This file could not be opened!");
        }
/*----------------------------------------------------------------------------*/        
        input.close();//Dosyanin kapatilmasi
        try{
            input = new Scanner(new File(fileName));//Dosyanin acilmasi
/*-------------------------Hata kontrolu--------------------------------------*/                        
            if (dataType == 1){
//Dosyanin icinde double veya string tipi bir veri varsa program exception firlatir.                                
                try{
                    data = new Integer[size];
                    for (int i=0; i<data.length; i++){   
                        data[i] = input.nextInt();//Verilerin okunmasi
                    }
                }
                catch(InputMismatchException inputException){
                    System.err.println("Invalid file. There are string or double data types in file!");
                    throw inputException;
                }
            }
            else if (dataType == 2){
                try{
                    data = new String[size];
                    for (int i=0; i<data.length; i++){
                        data[i] = input.next();//Verilerin okunmasi
                    }
                }
                catch(InputMismatchException inputException){
                    System.err.println("Invalid file!");
                    throw inputException;       
                }
            }
            else if (dataType == 3){
//Dosyanin icinde integer veya string tipi bir veri varsa program exception firlatir.                                                
                try{
                    String tmp;
                    tmp = input.nextLine();//Verilerin okunmasi
                    data = new Double[size];                
                    for (int i=0; i<data.length; i++){
                        data[i] = Double.parseDouble(tmp.split(" ")[i]);                        
                    }
                }
                catch(NumberFormatException inputException){
                    System.err.println("Invalid file. There are integer or string data types in file!");
                    throw inputException;
                }
            }
        }
        catch (FileNotFoundException fileNotException){
            System.err.println("Error:This file could not be opened!");
        } 
/*----------------------------------------------------------------------------*/        
    }
    public int numGrams(){
        return size - 1;
    }
    public int numOfGrams(Object firstElement, Object secondElement){
        int count = 0;//Verilen ikilinin veri dizisi icinde kac tane oldugunu tutar.
        if (((dataType == 1) || (dataType == 2)) || (dataType == 3)){
            for (int i=0; i<size; i++){
                if ((data[i].equals(firstElement)) && (data[i+1].equals(secondElement)))
                    count++;
            }
        }
        return count;
    }
    public String toString(){
        int temp;
        Object temp1,temp2;
        freq = new int[size-1];
        if (dataType == 1){
            first = new Integer[size-1];
            second = new Integer[size-1];
        }
        else if (dataType == 2){
            first = new String[size-1];
            second = new String[size-1];
        }
        else if (dataType == 3){
            first = new Double[size-1];
            second = new Double[size-1];
        }
        for (int i=0; i<size-1; i++){
            freq[i] = numOfGrams(data[i], data[i+1]);
            first[i] = data[i];
            second[i] = data[i+1];
        }
        for (int i=0; i<size-1; i++){
            for (int j=i+1; j<size-1; j++){
        //Tekrar eden ikilinin sayilarinin buyukten kucuge dogru siralanmasi                                            
                if (freq[i]<freq[j]){
                    //Swap islemi
                    temp=freq[i];
                    temp1=first[i];
                    temp2=second[i];
                    freq[i]=freq[j];
                    first[i]=first[j];
                    second[i]=second[j];
                    freq[j]=temp;
                    first[j]=temp1;
                    second[j]=temp2;
                }
            }
        }
        //Yazdirma islemi
        if (dataType == 1){
            for (int i=0; i<size-2; i++)
                System.out.printf("(%d,%d)-> %d\n",first[i],second[i],freq[i]);
            return String.format("(%d,%d)-> %d\n",first[size-2],second[size-2],freq[size-2]);
        }
        else if (dataType == 2){
            for (int i=0; i<size-2; i++)
            System.out.printf("(%s,%s)-> %d\n",first[i],second[i],freq[i]);
        return String.format("(%s,%s)-> %d\n",first[size-2],second[size-2],freq[size-2]);
        }
        else if (dataType == 3){
            for (int i=0; i<size-2; i++)
            System.out.printf("(%.1f,%.1f)-> %d\n",first[i],second[i],freq[i]);
        return String.format("(%.1f,%.1f)-> %d\n",first[size-2],second[size-2],freq[size-2]);
        }
        return String.format("");
    }
}