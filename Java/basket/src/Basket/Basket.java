package Basket;

import Product.*;

import java.util.*;

public class Basket {
    
    private List<Product> products = new ArrayList<>();

    boolean usedDiscount30 = false;
    boolean freeCup = false;

    public void addProduct(Product product){

        this.products.add(product);

    }

    public Product getProduct(int index){

        return this.products.get(index);

    }

    public void sortProductsByName(){

        this.products.sort(new CompareName());

    }

    public void sortProductsByPrice(){

        this.products.sort(new ComparePrice());

    }

    public void sortProducts(){

        sortProductsByName();
        sortProductsByPrice();

    }

    public Product getCheapest(){

        sortProducts();
        return getProduct(0);

    }

    public Product getMostExpensive(){

        sortProducts();
        return getProduct(this.products.size()-1);

    }

    public List<Product> getCheapestProducts(int n){

        List<Product> result = new ArrayList<>();

        for(int i = 0; i < n; i++){

            result.add(this.products.get(i));

        }

        return result;

    }

    public List<Product> getMostExpensiveProducts(int n){

        List<Product> result = new ArrayList<>();

        for(int i = this.products.size() - 1; i > (this.products.size() - 1) - n; i--){

            result.add(this.products.get(i));

        }

        return result;

    }

    public double sumPrice(){

        double result = 0.0;

        sortProducts();

        //jezeli trzy podukty, trzeci najtanszy gratis

        if(products.size() <= 2) result += products.get(0).getPrice();

        for(int i = 1; i < products.size(); i++){

            result += products.get(i).getPrice();

        }

        //jezeli ponad 200zl darmowy kubek

        if(!freeCup && result >= 200.0) {
            
            Product cup = new Product("9999", "Firmowy kubek", 0.0);
            this.products.add(cup);
            freeCup = true;
        }
        
        //jezeli ponad 300zl 5% taniej

        if(result >= 300.0) result *= 0.95;

        return result;

    }

    public void applyDiscountOnProduct(int index) throws DiscountUsedException{

        if(!usedDiscount30) {
            this.products.get(index).setPrice(this.products.get(index).getDiscountPrice());
            usedDiscount30 = true;
        }
        else{
            throw new DiscountUsedException();
        }

    }

    public class DiscountUsedException extends Exception{

        public DiscountUsedException(){

            super("Discount is already used!");

        }

    }

}
