//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.

import calculator.Calculator;

public class Main {
    public static void main(String[] args) {

        Calculator calc = new Calculator();

        calc.setState(1000000);

        calc.square();

        System.out.println(calc.getState());

    }
}