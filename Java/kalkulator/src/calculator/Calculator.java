package calculator;

public class Calculator {
    private int state = 0;
    private int memory = 0;

    public int getState() {
        return state;
    }

    public void setState(int state) {
        this.state = state;
    }

    public void add(int value){
        state += value;
    }

    public void mult(int value){
        state *= value;
    }

    public void div(int value){
        if (value != 0) {
            state /= value;
        }
        else{
            System.out.println("Error: Division by zero!");
        }
    }

    public void mod(int value){
        if(value!=0) {
            state %= value;
        }
        else{
            System.out.println("Error: Modulo by zero!");
        }
    }

    public void setMemory(){
        memory = state;
    }

    public int getMemory(){
        return memory;
    }

    public void clearMemory(){
        memory = 0;
    }

}
