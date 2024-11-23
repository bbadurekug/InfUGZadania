package Basket;

import Product.*;

public class Basket {
    
    private Product [] products = new Product[0];

    private boolean isEmpty(Product [] products){

		if(products.length == 0){ return true;}
		return false;

	}

    private void copyProducts(Product [] source, Product [] dest){

        if(isEmpty(source) || isEmpty(dest)){return;}

		int len = (source.length < dest.length)? source.length: dest.length;

		for(int i = 0; i < len; i++) {

			dest[i] = source[i];

		}

    }

    public void addProduct(Product product){

        Product [] temp = new Product[this.products.length + 1];
        copyProducts(products, temp);
        temp[temp.length-1] = product;
        products = new Product[temp.length];
        this.products = temp;

    }

    public Product peekProduct(){

        return this.products[this.products.length-1];

    }

}
