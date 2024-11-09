package RPN;

import Stack.*;

import java.util.StringTokenizer;

public class RPN {

    private Stack stack = new Stack();

    private void addition(){

        int num1, num2;
        String result;

        stack.pop();
        num1 = Integer.valueOf(stack.pop());
        num2 = Integer.valueOf(stack.pop());  

        result = String.valueOf(num2 + num1);

        stack.push(result);

    }

    private void subtraction(){

        int num1, num2;
        String result;

        stack.pop();
        num1 = Integer.valueOf(stack.pop());
        num2 = Integer.valueOf(stack.pop());  

        result = String.valueOf(num2 - num1);

        stack.push(result);

    }

    private void multiplication(){

        int num1, num2;
        String result;

        stack.pop();
        num1 = Integer.valueOf(stack.pop());
        num2 = Integer.valueOf(stack.pop());  

        result = String.valueOf(num2 * num1);

        stack.push(result);

    }

    private void division(){

        int num1, num2;
        String result;

        stack.pop();
        num1 = Integer.valueOf(stack.pop());
        num2 = Integer.valueOf(stack.pop());  

        result = String.valueOf(num2 / num1);

        stack.push(result);

    }

    public void calculateExpression(String input){

        StringTokenizer st = new StringTokenizer(input, " ");

        while(st.hasMoreTokens()){

            stack.push(st.nextToken());
            
            //zrobic oddzielne metody na dzialania
            //wrzucic gdzies try catch

            switch (stack.peek()) {
                case "+":
                    addition();
                    break;

                case "-":
                    subtraction();
                    break;

                case "x":
                    multiplication();
                    break;

                case "/":
                    division();
                    break;

                default:
                    break;
            }

            System.out.println(stack.peek());

        }

    }

    public String peekStack(){

        return this.stack.peek();

    }

    //private int calculateExpression(){



    //}

}
