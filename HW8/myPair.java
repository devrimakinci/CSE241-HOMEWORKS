/**
 *
 * @author devo35
 * @param <T1>
 * @param <T2>
 *
 * 
 * Dosya Ismi: myPair.java
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 06 Ocak 2017
 */

public class myPair<T1,T2> {
    private T1 firstElem;
    private T2 secondElem;
    
    public myPair(){}
    
    public myPair (T1 value1, T2 value2){
        firstElem = value1;
        secondElem = value2;
    }
    public T1 getFirstElem(){
        return firstElem;
    }
    public T2 getSecondElem(){
        return secondElem;
    }
    public void setFirstElem(T1 value){
        firstElem = value;
    }
    public void setSecondElem(T2 value){
        secondElem = value;
    }
    
}
