import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;
import calculator.Calculator;

class Tests {

    @Test
    public void testAddition1() {

        Calculator calc = new Calculator();

        calc.setState(0);
        calc.add(5);

        Assertions.assertEquals(calc.getState(), 5);

    }

    @Test
    public void testAddition2() {

        Calculator calc = new Calculator();

        calc.setState(-100);
        calc.add(-100);

        Assertions.assertEquals(calc.getState(), -200);

    }

    @Test
    public void testAddition3() {

        Calculator calc = new Calculator();

        calc.setState(2147483647);
        calc.add(1);

        Assertions.assertEquals(calc.getState(), 2147483647);

    }

    @Test
    public void testMultiplication1() {

        Calculator calc = new Calculator();

        calc.setState(-10);
        calc.mult(10);

        Assertions.assertEquals(calc.getState(), -100);

    }

    @Test
    public void testMultiplication2() {

        Calculator calc = new Calculator();

        calc.setState(0);
        calc.mult(0);

        Assertions.assertEquals(calc.getState(), 0);

    }

    @Test
    public void testMultiplication3() {

        Calculator calc = new Calculator();

        calc.setState(100);
        calc.mult(100);

        Assertions.assertEquals(calc.getState(), 10000);

    }

    @Test
    public void testSquare1() {

        Calculator calc = new Calculator();

        calc.setState(4);
        calc.square();

        Assertions.assertEquals(calc.getState(), 16);

    }

    @Test
    public void testSquare2() {

        Calculator calc = new Calculator();

        calc.setState(-5);
        calc.square();

        Assertions.assertEquals(calc.getState(), 25);

    }

    @Test
    public void testSquare3() {

        Calculator calc = new Calculator();

        calc.setState(1000000);
        calc.square();

        Assertions.assertEquals(calc.getState(), 1000000);

    }

    @Test
    public void testModulo1() {

        Calculator calc = new Calculator();

        calc.setState(100000000);
        calc.mod(0);

        Assertions.assertEquals(calc.getState(), 100000000);

    }

    @Test
    public void testModulo2() {

        Calculator calc = new Calculator();

        calc.setState(5);
        calc.mod(3);

        Assertions.assertEquals(calc.getState(), 2);

    }

    @Test
    public void testModulo3() {

        Calculator calc = new Calculator();

        calc.setState(15);
        calc.mod(15);

        Assertions.assertEquals(calc.getState(), 0);

    }

    @Test
    public void testMemory1() {

        Calculator calc = new Calculator();

        calc.setState(2);
        calc.mod(3);

        calc.setMemory();

        calc.setState(4);

        calc.add(calc.getMemory());

        Assertions.assertEquals(calc.getState(), 6);

    }

    @Test
    public void testMemory2() {

        Calculator calc = new Calculator();

        calc.setState(2);
        calc.mult(2);

        calc.setMemory();

        calc.setState(2);

        calc.add(calc.getMemory());

        Assertions.assertEquals(calc.getState(), 6);

    }

    @Test
    public void testMemory3() {

        Calculator calc = new Calculator();

        calc.setState(15);
        calc.setMemory();

        calc.clearMemory();

        Assertions.assertEquals(calc.getMemory(), 0);

    }
}