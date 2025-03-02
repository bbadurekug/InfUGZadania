package Sack;

import Asset.*;

public class Sack extends Asset {

    public class GoldValueInvalidException extends Exception{

        public GoldValueInvalidException(){

            super("Gold value cannot be lower than 0!");

        }

    }

    private int goldValue;

    public Sack(int generalID){

        super(generalID);
        //starting value can be changed accordingly
        this.goldValue = 1000;

    }

    public Sack(int generalID, int goldValue){

        super(generalID);
        this.goldValue = goldValue;

    }

    public int getGoldValue(){

        return this.goldValue;

    }

    private boolean checkifGoldValid(int goldValue) throws GoldValueInvalidException{

        if(goldValue >= 0){

            return true;

        }
        else{

            throw new GoldValueInvalidException();

        }

    }

    public void setGoldValue(int goldValue) throws GoldValueInvalidException{

        if(checkifGoldValid(goldValue)){

            this.goldValue = goldValue;

        }

    }
    
}
