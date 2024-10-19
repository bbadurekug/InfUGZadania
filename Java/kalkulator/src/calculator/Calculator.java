package calculator;

public class Calculator {
    private int state = 0;
    private int memory = 0;

    public int getState() {
        return this.state;
    }

    public void setState(int state) {
        this.state = state;
    }

    private boolean checkOverflow(int value){
        if (this.state > 0 && value > 0 && this.state + value < 0 ||
                this.state < 0 && value < 0 && this.state + value > 0){
            return true;
        }
        return false;
    }

    public void add(int value){
        if (checkOverflow(value)){
            System.out.println("Overflow! Operation was not performed.");
        }
        else {
            this.state += value;
        }
    }

    public void mult(int value){
        this.state *= value;
    }

    public void square(){

        if(this.state * this.state < 0) {
            System.out.println("Overflow! Operation was not performed.");
        }
        else {
            this.state *= this.state;
        }
    }

    public void mod(int value){
        if(value!=0) {
            this.state %= value;
        }
        else{
            System.out.println("Error: Modulo by zero! Operation cannot be performed.");
        }
    }

    public void setMemory(){
        this.memory = this.state;
    }

    public int getMemory(){
        return this.memory;
    }

    public void clearMemory(){
        this.memory = 0;
    }

}