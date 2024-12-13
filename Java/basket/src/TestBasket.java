import Basket.*;
import Basket.Basket.DiscountUsedException;
import Product.*;

import java.util.ArrayList;
import java.util.List;

import static org.junit.Assert.*;

public class TestBasket {

    @org.junit.Test
    public void testBasket() {

        Product product = new Product("1234", "Czekolada", 12.4, 11.5);

        Basket basket = new Basket();

        basket.addProduct(product);

        Product result = basket.getProduct(0);

        assertEquals(product, result);
    }

    @org.junit.Test
    public void testBasket2() {

        Product product = new Product("1234", "Czekolada", 12.4, 11.5);

        Product product2 = new Product("1235", "Domek", 11.4, 10.5);

        Product product3 = new Product("1236", "LEGO", 100.0, 85.5);
        
        Product product4 = new Product("1237", "Opona", 100.0, 85.5);

        Basket basket = new Basket();

        basket.addProduct(product);

        basket.addProduct(product2);

        basket.addProduct(product3);

        basket.addProduct(product4);

        basket.sortProducts();

        Product result = basket.getProduct(2);

        assertEquals(product3, result);
    }

    @org.junit.Test
    public void testPriceSum() {

        Product product = new Product("1234", "Czekolada", 12.4, 11.5);

        Product product2 = new Product("1235", "Domek", 11.4, 10.5);

        Product product3 = new Product("1236", "LEGO", 100.0, 85.5);
        
        Product product4 = new Product("1237", "Opona", 100.0, 85.5);

        Basket basket = new Basket();

        basket.addProduct(product);

        basket.addProduct(product2);

        basket.addProduct(product3);

        basket.addProduct(product4);

        basket.sortProducts();

        double result = basket.sumPrice();

        //przecena bo wiecej niz 300 zl

        assertEquals(212.4, result, 0);
    }

    @org.junit.Test
    public void testMostExpensive() {

        Product product = new Product("1234", "Czekolada", 12.4, 11.5);

        Product product2 = new Product("1235", "Domek", 11.4, 10.5);
        
        Product product3 = new Product("1237", "Opona", 100.0, 85.5);

        Basket basket = new Basket();

        basket.addProduct(product);

        basket.addProduct(product2);

        basket.addProduct(product3);

        basket.sortProducts();

        List<Product> result = basket.getMostExpensiveProducts(2);

        List<Product> expected = new ArrayList<>();

        expected.add(product3); //opona
        expected.add(product); //czekolada
        expected.add(product2); //domek

        assertEquals(expected, result);
    }
    
    @org.junit.Test
    public void testDiscount() throws DiscountUsedException {

		Product product = new Product("1234", "Czekolada", 12.4, 11.5);

        Basket basket = new Basket();

        basket.addProduct(product);

        basket.applyDiscountOnProduct(0);

        double result = basket.getProduct(0).getPrice();

        //basket.applyDiscountOnProduct(0);

        double expected = 12.4 * 0.7;

		assertEquals(expected, result , 0);
	}

    @org.junit.Test
    public void testCup(){

		Product product = new Product("1234", "Czekolada", 200.0, 215.0);

        Basket basket = new Basket();

        basket.addProduct(product);

        basket.sumPrice();

        String result = basket.getCheapest().getName();

		assertEquals("Firmowy kubek", result);
	}

}
