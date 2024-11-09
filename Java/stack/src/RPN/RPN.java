package RPN;

import Stack.*;

import java.util.StringTokenizer;

public class RPN {

    private Stack stack = new Stack();

    public void calculateExpression(String input){

        StringTokenizer st = new StringTokenizer(input, " ");
        int num1, num2;
        String result;

        while(st.hasMoreTokens()){

            stack.push(st.nextToken());
            
            //zrobic oddzielne metody na dzialania

            switch (stack.peek()) {
                case "+":

                    stack.pop();
                    num1 = Integer.valueOf(stack.pop());
                    num2 = Integer.valueOf(stack.pop());  

                    result = String.valueOf(num2 + num1);

                    stack.push(result);

                    break;

                case "-":

                    stack.pop();
                    num1 = Integer.valueOf(stack.pop());
                    num2 = Integer.valueOf(stack.pop());  

                    result = String.valueOf(num2 - num1);

                    stack.push(result);

                    break;

                case "x":

                    stack.pop();
                    num1 = Integer.valueOf(stack.pop());
                    num2 = Integer.valueOf(stack.pop());  

                    result = String.valueOf(num2 * num1);

                    stack.push(result);

                    break;

                case "/":

                    stack.pop();
                    num1 = Integer.valueOf(stack.pop());
                    num2 = Integer.valueOf(stack.pop());  

                    result = String.valueOf(num2 / num1);

                    stack.push(result);

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
