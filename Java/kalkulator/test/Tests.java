import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;
import calculator.Calculator;

class TestCalculator {

    @Test
    public void testAdditionPositive() {

        Calculator calc = new Calculator();

        calc.setState(0);
        calc.add(5);

        Assertions.assertEquals(calc.getState(), 5);

    }

    @Test
    public void testAdditionNegative() {

        Calculator calc = new Calculator();

        calc.setState(-100);
        calc.add(-100);

        Assertions.assertEquals(calc.getState(), -200);

    }

    @Test
    public void testAdditionOverflow() {

        Calculator calc = new Calculator();

        calc.setState(2147483647);
        calc.add(1);

        Assertions.assertEquals(calc.getState(), 2147483647);

    }

    @Test
    public void testMultiplicationNegative() {

        Calculator calc = new Calculator();

        calc.setState(-10);
        calc.mult(10);

        Assertions.assertEquals(calc.getState(), -100);

    }

    @Test
    public void testMultiplicationZero() {

        Calculator calc = new Calculator();

        calc.setState(10);
        calc.mult(0);

        Assertions.assertEquals(calc.getState(), 0);

    }

    @Test
    public void testMultiplicationPositive() {

        Calculator calc = new Calculator();

        calc.setState(100);
        calc.mult(100);

        Assertions.assertEquals(calc.getState(), 10000);

    }

    @Test
    public void testSquarePositive() {

        Calculator calc = new Calculator();

        calc.setState(4);
        calc.square();

        Assertions.assertEquals(calc.getState(), 16);

    }

    @Test
    public void testSquareNegative() {

        Calculator calc = new Calculator();

        calc.setState(-5);
        calc.square();

        Assertions.assertEquals(calc.getState(), 25);

    }

    @Test
    public void testSquareOverflow() {

        Calculator calc = new Calculator();

        calc.setState(1000000);
        calc.square();

        Assertions.assertEquals(calc.getState(), 1000000);

    }

    @Test
    public void testModuloZero() {

        Calculator calc = new Calculator();

        calc.setState(100000000);
        calc.mod(0);

        Assertions.assertEquals(calc.getState(), 100000000);

    }

    @Test
    public void testModuloWithRest() {

        Calculator calc = new Calculator();

        calc.setState(5);
        calc.mod(3);

        Assertions.assertEquals(calc.getState(), 2);

    }

    @Test
    public void testModuloNoRest() {

        Calculator calc = new Calculator();

        calc.setState(15);
        calc.mod(15);

        Assertions.assertEquals(calc.getState(), 0);

    }

    @Test
    public void testMemoryMod() {

        Calculator calc = new Calculator();

        calc.setState(2);
        calc.mod(3);

        calc.setMemory();

        calc.setState(4);

        calc.add(calc.getMemory());

        Assertions.assertEquals(calc.getState(), 6);

    }

    @Test
    public void testMemoryMultiplication() {

        Calculator calc = new Calculator();

        calc.setState(2);
        calc.mult(2);

        calc.setMemory();

        calc.setState(2);

        calc.add(calc.getMemory());

        Assertions.assertEquals(calc.getState(), 6);

    }

    @Test
    public void testMemoryClear() {

        Calculator calc = new Calculator();

        calc.setState(15);
        calc.setMemory();

        calc.clearMemory();

        Assertions.assertEquals(calc.getMemory(), 0);

    }
}