package Manager;

import Soldier.*;
import Soldier.Soldier.ExperienceInvalidException;
import Soldier.Soldier.RankInvalidException;
import General.*;
import Sack.Sack.GoldValueInvalidException;
import Army.*;
import Secretary.*;

import java.io.IOException;
import java.util.*;

public class Manager {
    
    private General gen1;
    private General gen2;
    private Army army1;
    private Army army2;
    private Secretary sec;

    public Manager() throws IOException{

        this.gen1 = new General(1);
        this.gen2 = new General(2);
        this.army1 = new Army(1);
        this.army2 = new Army(2);
        this.sec = new Secretary();
        
    }

    public Manager(int gen1Gold, int gen2Gold, List<Soldier> army1, List<Soldier> army2) throws IOException{

        this.gen1 = new General(1, gen1Gold);
        this.gen2 = new General(2, gen2Gold);
        this.army1 = new Army(1, army1);
        this.army2 = new Army(2, army2);
        this.sec = new Secretary();

    }

    public int getGeneralGold(int ID){

        if(ID == 1){

            return this.gen1.getSackValue();

        }
        else{

            return this.gen2.getSackValue();

        }

    }

    public int getArmyPower(int ID){

        if(ID == 1){

            return this.army1.getArmyPower();

        }
        else{

            return this.army2.getArmyPower();

        }

    }

    public int trainArmy(int ID) throws GoldValueInvalidException{

        int trainingCost;

        //return if training failed

        if(ID == 1){

            trainingCost = this.army1.getTrainingCost();
            if(trainingCost > this.gen1.getSackValue()) return 0;
            this.army1.trainArmy();
            this.gen1.setSackValue(this.gen1.getSackValue() - trainingCost);

        }
        else{

            trainingCost = this.army2.getTrainingCost();
            if(trainingCost > this.gen2.getSackValue()) return 0;
            this.army2.trainArmy();
            this.gen2.setSackValue(this.gen2.getSackValue() - trainingCost);

        }

        return 1;

    }

    public int buySoldier(int ID, int rank) throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException{

        if(ID == 1){

            if (this.gen1.getSackValue() < rank * 10) return 0;

        }
        else{

            if (this.gen2.getSackValue() < rank * 10) return 0;

        }

        Soldier sol = new Soldier(rank, 1);

        if(ID == 1){

            this.army1.addSoldier(sol);
            this.gen1.setSackValue(this.gen1.getSackValue() - (rank * 10));

        }
        else{

            this.army2.addSoldier(sol);
            this.gen2.setSackValue(this.gen2.getSackValue() - (rank * 10));

        }

        return 1;

    }

    private void calculateGoldAfterBattle(int winnerID) throws GoldValueInvalidException{

        if(winnerID == 1){

            int loserGold = this.gen2.getSackValue();

            loserGold = (int) (Math.ceil(loserGold * 0.1));

            this.gen1.setSackValue(this.gen1.getSackValue() + loserGold);
            this.gen2.setSackValue(this.gen2.getSackValue() - loserGold);

        }
        else{

            int loserGold = this.gen1.getSackValue();

            loserGold = (int) (Math.ceil(loserGold * 0.1));

            this.gen2.setSackValue(this.gen2.getSackValue() + loserGold);
            this.gen1.setSackValue(this.gen1.getSackValue() - loserGold);

        }

    }

    public int battle() throws GoldValueInvalidException{

        //return result based on winning general 0 - draw, 1 - gen1 wins, 2 - gen2 wins

        if(this.army1.getArmyPower() > this.army2.getArmyPower()){

            calculateGoldAfterBattle(1);
            this.army1.trainArmy();
            this.army2.lostBattle();

            return 1;

        }
        else if(this.army1.getArmyPower() < this.army2.getArmyPower()){

            calculateGoldAfterBattle(2);
            this.army2.trainArmy();
            this.army1.lostBattle();

            return 2;

        }
        else{

            int randomValue;
            
            randomValue = (int) (Math.random() * (this.army1.getArmySize()));
            this.army1.killSoldier(randomValue);

            randomValue = (int) (Math.random() * (this.army2.getArmySize()));
            this.army2.killSoldier(randomValue);

            return 0;

        }

    }

    public void saveFile() throws IOException{

        this.sec.writeToFile(this.gen1.getSackValue(), this.gen2.getSackValue(), this.army1, this.army2);

    }

    public void loadFile() throws IOException, GoldValueInvalidException, NumberFormatException, ExperienceInvalidException, RankInvalidException{

        this.gen1.setSackValue(this.sec.readGen1Gold());
        this.gen2.setSackValue(this.sec.readGen2Gold());
        this.army1 = this.sec.readArmy1();
        this.army2 = this.sec.readArmy2();

    }

    public int checkGameStatus(){

        //check if game over, someone lost
        if(this.gen1.getSackValue() == 0 && this.army1.getArmyPower() == 0) return 2;

        if(this.gen2.getSackValue() == 0 && this.army2.getArmyPower() == 0) return 1;

        return 0;

    }

}
