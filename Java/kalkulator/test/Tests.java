import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Assertions;
import calculator.Calculator;

public class Tests {

    @Test
    public void test() {

        Calculator calc = new Calculator();

        calc.setState(3);

        Assertions.assertEquals(calc.getState(), 3);

    }

}


