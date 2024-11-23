import Basket.*;
import Product.*;

import static org.junit.Assert.*;

public class TestBasket {

    @org.junit.Test
	public void testBasket() {

		Product product = new Product("1234", "Czekolada", 12.4, 11.5);

        Basket basket = new Basket();

        basket.addProduct(product);

        Product result = basket.peekProduct();

		assertEquals("1234", result.getCode());
	}
    
}
