package TestSoldier;

import Soldier.*;
import Soldier.Soldier.ExperienceInvalidException;
import Soldier.Soldier.RankInvalidException;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class TestSoldier {

    @Test
    public void TestPowers() throws ExperienceInvalidException, RankInvalidException{

        Soldier testSoldier1 = new Soldier(2, 4);
        
        int result = testSoldier1.getPower();

        assertEquals(result, 8);

    }

    @Test
    public void TestInvaildRank() throws ExperienceInvalidException, RankInvalidException{

        Soldier testSoldier1 = new Soldier(5, 4);
        
        int result = testSoldier1.getPower();

        assertEquals(result, 20);

    }

    @Test
    public void TestInvaildExpierience() throws ExperienceInvalidException, RankInvalidException{

        Soldier testSoldier1 = new Soldier(1, 5);
        
        int result = testSoldier1.getPower();

        assertEquals(result, 5);

    }

    @Test
    public void TestRankUp() throws ExperienceInvalidException, RankInvalidException{

        Soldier testSoldier1 = new Soldier(1, 4);
        
        testSoldier1.rankUp(); // 1 * 4 -> 2 * 1
        int result = testSoldier1.getPower();

        assertEquals(result, 2);

    }
}