package Product;

public class Product {
    
    private String code;
    private String name;
    private double price;
    private double discountPrice;

    public Product(String code, String name, double price, double discountPrice){

        this.code = code;
        this.name = name;
        //blad jezeli cena jest ujemna
        this.price = price;
        //blad jezeli cena po promocji jest ujemna lub wyzsza od ceny poczatkowej
        this.discountPrice = discountPrice;

    }

    public String getCode(){

        return this.code;

    }

    public String getName(){

        return this.name;

    }

    public double getPrice(){

        return this.price;

    }

    public void setPrice(double price){

        this.price = price;

    }

    public double getDiscountPrice(){

        return this.discountPrice;

    }

}