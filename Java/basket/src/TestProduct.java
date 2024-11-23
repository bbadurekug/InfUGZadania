import Product.*;

import static org.junit.Assert.*;

public class TestProduct {

	@org.junit.Test
	public void testProduct() {

		Product product = new Product("123", "Czekolada", 12.4, 11.5);

        String result = product.getCode();

		assertEquals("123", result);
	}

}