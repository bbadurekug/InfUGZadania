package Army;

import Soldier.*;
import java.util.*;

import Asset.*;

public class Army extends Asset{
    
    private List<Soldier> soldiers = new ArrayList<>();
    private int armyPower;

    public Army(int generalID){

        //blank army
        super(generalID);

    }

    public Army(int generalID, List<Soldier> soldiers){

        //loaded army
        super(generalID);
        this.soldiers = soldiers;

    }

    public void addSoldier(Soldier soldier){

        this.soldiers.add(soldier);

    }

    public int getArmySize(){

        return this.soldiers.size();

    }

    public int getArmyPower(){

        recalculateArmyPower();
        return this.armyPower;

    }

    public int getTrainingCost(){

        int result = 0;

        for(int i = 0; i < this.soldiers.size(); i++){

            result += this.soldiers.get(i).getRank();

        }

        return result;

    }

    public int getTrainingCost(int howMany){

        int result = 0;

        for(int i = 0; i < howMany; i++){

            result += this.soldiers.get(i).getRank();

        }

        return result;

    }

    public int getPartialTrainingAmount(int funds){

        int result = 0;

        for(int i = 0; i < this.soldiers.size(); i++){

            if(result + this.soldiers.get(i).getRank() > funds){

                return i;

            }
            else if(result + this.soldiers.get(i).getRank() == funds){

                return i+1;

            }
            else{

                result += this.soldiers.get(i).getRank();

            }

        }

        return -1;

    }

    private void recalculateArmyPower(){

        this.armyPower = 0;

        for(int i = 0; i < this.soldiers.size(); i++){

            this.armyPower += this.soldiers.get(i).getPower();

        }

    }

    public void trainArmy(){

        for(int i = 0; i < this.soldiers.size(); i++){

            if(this.soldiers.get(i).getRank() < 4 && (this.soldiers.get(i).getExperience() + 1) >= (this.soldiers.get(i).getRank() * 5)){

                this.soldiers.get(i).rankUp();

            }
            else{

                this.soldiers.get(i).trainSoldier();

            }

        }

    }

    public void trainArmy(int howMany){

        for(int i = 0; i < howMany; i++){

            if(this.soldiers.get(i).getRank() < 4 && (this.soldiers.get(i).getExperience() + 1) >= (this.soldiers.get(i).getRank() * 5)){

                this.soldiers.get(i).rankUp();

            }
            else{

                this.soldiers.get(i).trainSoldier();

            }

        }

    }

    public void lostBattle(){

        for(int i = 0; i < this.soldiers.size(); i++){

            if(this.soldiers.get(i).getExperience() - 1 == 0){

                killSoldier(i);
                i--;

            }
            else{

                this.soldiers.get(i).hurtSoldier();

            }

        }

    }

    public void killSoldier(int i){

        this.soldiers.remove(i);

    }

    public Soldier getSoldier(int i){

        return this.soldiers.get(i);

    }

}
