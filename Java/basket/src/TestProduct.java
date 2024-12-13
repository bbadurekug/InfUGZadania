import Product.*;

import static org.junit.Assert.*;

public class TestProduct {

	@org.junit.Test
	public void testProduct() {

		Product product = new Product("123", "Czekolada", 12.4);

        String result = product.getCode();

		assertEquals("123", result);
	}

	@org.junit.Test
	public void testChangePrice() {

		Product product = new Product("123", "Czekolada", 12.4);
		
		product.setPrice(product.getDiscountPrice());

        double result = product.getPrice();

		assertEquals(12.4 * 0.7, result, 0.001);
	}

}