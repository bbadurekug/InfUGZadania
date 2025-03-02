package TestArmy;

import Soldier.*;
import Soldier.Soldier.ExperienceInvalidException;
import Soldier.Soldier.RankInvalidException;

import Army.*;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class TestArmy {

    @Test
    public void TestCreateArmy() throws ExperienceInvalidException, RankInvalidException{

        Soldier testSoldier1 = new Soldier(1, 4);
        Soldier testSoldier2 = new Soldier(1, 2);
        Soldier testSoldier3 = new Soldier(3, 14);

        Army testArmy = new Army(1);

        testArmy.addSoldier(testSoldier1);
        testArmy.addSoldier(testSoldier2);
        testArmy.addSoldier(testSoldier3);

        testArmy.trainArmy();

        int result = testArmy.getArmyPower();

        assertEquals(result, 9);

    }

    @Test
    public void TestAfterLoss() throws ExperienceInvalidException, RankInvalidException{

        Soldier testSoldier1 = new Soldier(2, 4);
        Soldier testSoldier2 = new Soldier(3, 2);

        Army testArmy = new Army(1);

        testArmy.addSoldier(testSoldier1);
        testArmy.addSoldier(testSoldier2);

        testArmy.lostBattle(); // 8 + 6 -> 6 + 3

        int result = testArmy.getArmyPower();

        assertEquals(result, 9);

    }

}