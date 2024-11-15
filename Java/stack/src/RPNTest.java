import RPN.*;

import static org.junit.Assert.*;

public class RPNTest {

	@org.junit.Test
	public void testExpression1() {

        RPN rpn = new RPN();

        rpn.calculateExpression("12 2 3 4 x 10 5 / + x +");

        String result = rpn.peekStack();

		assertEquals("40", result);
	}

	@org.junit.Test
	public void testExpression2() {

        RPN rpn = new RPN();

        rpn.calculateExpression("5 1 2 + 4 x + 3 -");

        String result = rpn.peekStack();

		assertEquals("14", result);
	}

	@org.junit.Test
	public void testExpression3() {

        RPN rpn = new RPN();

        rpn.calculateExpression("2 3 + 5 x");

        String result = rpn.peekStack();

		assertEquals("25", result);
	}

	@org.junit.Test
	public void testExpression4() {

        RPN rpn = new RPN();

        rpn.calculateExpression("2 7 + 3 / 14 3 - 4 x +");

        String result = rpn.peekStack();

		assertEquals("47", result);
	}

}
