package Basket;

import Product.*;

import java.util.*;

public class Basket {
    
    private List<Product> products = new ArrayList<>();

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

        for(int i = this.products.size() - 1; i >= 0; i--){

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

        if(result >= 300.0) result *= 0.95;

        return result;

    }

}
