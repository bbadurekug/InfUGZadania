package General;

import Sack.*;
import Sack.Sack.GoldValueInvalidException;

public class General {
    
    private int ID;
    private Sack gold;

    public General(int ID){

        this.ID = ID;
        this.gold = new Sack(ID);

    }

    public General(int ID, int goldValue){

        this.ID = ID;
        this.gold = new Sack(ID, goldValue);

    }

    public int getSackValue(){

        return this.gold.getGoldValue();

    }

    public void setSackValue(int goldValue) throws GoldValueInvalidException{

        this.gold.setGoldValue(goldValue);

    }

}
