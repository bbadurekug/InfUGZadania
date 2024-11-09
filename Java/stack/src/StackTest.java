import Stack.*;

import static org.junit.Assert.*;

public class StackTest {
	@org.junit.Test
	public void testPopAfterPush() {

		Stack stack = new Stack();
		stack.push("napis");
		String result = stack.pop();

		assertEquals("napis", result);
	}

	@org.junit.Test
	public void testPopAfterTwoPushes() {

		Stack stack = new Stack();
		stack.push("napis1");
		stack.push("napis2");
		String result = stack.pop();

		assertEquals("napis2" , result);

	}

	@org.junit.Test
	public void testPopEmptyStack(){

		Stack stack = new Stack();
		String result = stack.pop();

		assertEquals("", result);

	}

	@org.junit.Test
	public void testPeekStack(){

		Stack stack = new Stack();
		stack.push("napis");
		String result = stack.peek();

		assertEquals("napis" , result);

	}

	@org.junit.Test
	public void testPeekEmptyStack(){

		Stack stack = new Stack();
		String result = stack.peek();

		assertEquals("", result);

	}

	@org.junit.Test
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
