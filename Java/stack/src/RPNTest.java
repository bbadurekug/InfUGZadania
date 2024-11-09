import RPN.*;

import static org.junit.Assert.*;

public class RPNTest {

	@org.junit.Test
	public void testInsertSingle() {

        RPN rpn = new RPN();

        rpn.calculateExpression("12 2 3 4 x 10 5 / + x +");

        String result = rpn.peekStack();

		assertEquals("40", result);
	}

}
