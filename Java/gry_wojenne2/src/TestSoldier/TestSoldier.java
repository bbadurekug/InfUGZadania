package TestSoldier;

import Soldier.*;
import Soldier.Soldier.ExperienceInvalidException;
import Soldier.Soldier.RankInvalidException;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

public class TestSoldier {

    @Test
    public void TestSoldiers() throws ExperienceInvalidException, RankInvalidException {
        Soldier testSoldier = new Soldier(4, 50);
        int result = testSoldier.getPower();
        assertEquals(200, result);
    }
    
}