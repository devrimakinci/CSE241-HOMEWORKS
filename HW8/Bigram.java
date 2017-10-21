/**
 *
 * @param <T>
 * 
 * 
 *
 * 
 * Dosya Ismi: Bigram.java
 * Yazan: Devrim AKINCI
 * Numarasi: 141044052
 * Tarih: 06 Ocak 2017
 */


public interface Bigram<T> {
    public void readFile (String fileName);//Dosyadan verileri okur.
    public int numGrams();//Toplam ikili sayisini bulur.
    public int numOfGrams(T firstElement, T secondElement);
    //Verilen ikilinin veri dizisi icinde kac tane oldugunu bulur.
    public String toString();//Ikililerin sayisinin azalan gore ekrana basar.
}
