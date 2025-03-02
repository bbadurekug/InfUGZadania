package TestManager;

import Manager.*;
import Sack.Sack.GoldValueInvalidException;
import Soldier.Soldier.ExperienceInvalidException;
import Soldier.Soldier.RankInvalidException;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

import java.io.IOException;

public class TestManager {
    
    @Test
    public void TestBuySolder() throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException, IOException{

        Manager man = new Manager();

        man.buySoldier(1, 4);

        int result = man.getGeneralGold(1);

        //starting gold 1000 - (rank * 10)

        assertEquals(result, 960);

    }

    @Test
    public void TestArmyTraining() throws ExperienceInvalidException, RankInvalidException, IOException, GoldValueInvalidException{

        Manager man = new Manager();

        man.buySoldier(1, 4);
        man.trainArmy(1);

        int result = man.getArmyPower(1);

        assertEquals(result, 8);

    }

    @Test
    public void TestBattleDrawRandom() throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException, IOException{

        Manager man = new Manager();

        man.buySoldier(1, 4);
        man.buySoldier(1, 2);
        man.buySoldier(2, 4);
        man.buySoldier(2, 2);

        man.battle();

        int result = man.getArmyPower(1);

        assertEquals(result, 4);

    }

    @Test
    public void TestExperienceDownAfterLoss() throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException, IOException{

        Manager man = new Manager();

        man.buySoldier(1, 1);
        man.buySoldier(1, 1);
        man.buySoldier(1, 1);
        man.buySoldier(2, 1);
        man.buySoldier(2, 1);

        //XP after buying Gen1 - 3 Gen2 - 2

        man.trainArmy(1);
        man.trainArmy(2);

        //XP after training Gen1 - 6 Gen2 - 4

        man.battle();

        //XP after training Gen1 - 9 Gen2 - 2

        int result = man.getArmyPower(2);

        assertEquals(result, 2);

    }

    @Test
    public void TestRankUpAfterWin() throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException, IOException{

        Manager man = new Manager();

        man.buySoldier(1, 1);
        man.buySoldier(1, 1);
        man.buySoldier(2, 1);

        //XP after buying Gen1 - 2 (1 x 1 x 2)

        man.trainArmy(1);
        man.trainArmy(1);
        man.trainArmy(1);

        //XP after training Gen1 - 8 (4 x 1 x 2)

        man.battle();

        //XP after training Gen1 - 4 (1 x 2 x 2)

        int result = man.getArmyPower(1);

        assertEquals(result, 4);

    }

    @Test
    public void TestGoldAfterLoss() throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException, IOException{

        Manager man = new Manager();

        man.buySoldier(1, 1);
        man.buySoldier(1, 1);
        man.buySoldier(2, 1);

        //Gold after buying Gen1 - 980 Gen2 - 990

        man.battle();

        //XP after training Gen1 - 980 + (990 * 10%) Gen 2 - 990 - (990 * 10%)

        int result = man.getGeneralGold(1);

        assertEquals(result, 980 + (990 * 0.1), 0.1);

    }

    @Test
    public void TestPartialTraining1() throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException, IOException{

        Manager man = new Manager();

        for(int i = 0; i < 24; i++){
            man.buySoldier(1, 4);
        }

        //Gen1 40 gold

        int result = man.trainArmy(1); //return 0 - cannot train entire army

        assertEquals(result, 0);

    }

    @Test
    public void TestPartialTraining2() throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException, IOException{

        Manager man = new Manager();

        for(int i = 0; i < 24; i++){
            man.buySoldier(1, 4);
        }

        //Gen1 40 gold

        int result = man.trainArmyPartially(1); //returns 10 = 40 / 4

        assertEquals(result, 10);

    }

}
