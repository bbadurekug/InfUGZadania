//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

import calculator.Calculator;

public class Main {
    public static void main(String[] args) {

        Calculator calc = new Calculator();

        calc.setState(5);

        calc.div(5);

        calc.setMemory();

        calc.setState(3);

        calc.add(calc.getMemory());

        System.out.println(calc.getState());

    }
}



