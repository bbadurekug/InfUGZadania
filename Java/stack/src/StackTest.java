import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class StackTest {
	@Test
	public void testPopAfterPush() {

		Stack stack = new Stack();
		stack.push("napis");
		String result = stack.pop();

		assertEquals("napis", result);
	}

	@Test
	public void testPopAfterTwoPushes() {

		Stack stack = new Stack();
		stack.push("napis1");
		stack.push("napis2");
		String result = stack.pop();

		assertEquals("napis2" , result);

	}

	@Test
	public void testPopEmptyStack(){

		Stack stack = new Stack();
		String result = stack.pop();

		assertEquals("", result);

	}

	@Test
	public void testPeekStack(){

		Stack stack = new Stack();
		stack.push("napis");
		String result = stack.peek();

		assertEquals("napis" , result);

	}

	@Test
	public void testPeekEmptyStack(){

		Stack stack = new Stack();
		String result = stack.peek();

		assertEquals("", result);

	}

	@Test
	public void testPushPushPopPushPeek(){

		Stack stack = new Stack();

		stack.push("napis1");
		stack.push("napis2");
		stack.pop();
		stack.push("napis3");

		String result = stack.peek();

		assertEquals("napis3" , result);

	}
}
