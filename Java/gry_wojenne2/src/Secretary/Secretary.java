package Secretary;

import Army.*;
import Soldier.Soldier;
import Soldier.Soldier.ExperienceInvalidException;
import Soldier.Soldier.RankInvalidException;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Secretary {
    
    //create TXT files for saving
    private String fileName;
    private BufferedWriter writer;
    private BufferedReader reader;
    

    public Secretary() throws IOException{

        this.fileName = "savefile.txt";

    }

    public void writeToFile(int gen1Gold, int gen2Gold, Army army1, Army army2) throws IOException{

        this.writer = new BufferedWriter(new FileWriter(fileName));

        writer.write(Integer.toString(gen1Gold));
        writer.newLine();
        writer.write(Integer.toString(gen2Gold));
        writer.newLine();

        writer.write(Integer.toString(army1.getArmySize()));
        writer.newLine();

        for(int i = 0; i < army1.getArmySize(); i++){

            writer.write(Integer.toString(army1.getSoldier(i).getRank()));
            writer.newLine();
            writer.write(Integer.toString(army1.getSoldier(i).getExperience()));
            writer.newLine();

        }

        writer.write(Integer.toString(army2.getArmySize()));
        writer.newLine();

        for(int i = 0; i < army2.getArmySize(); i++){

            writer.write(Integer.toString(army2.getSoldier(i).getRank()));
            writer.newLine();
            writer.write(Integer.toString(army2.getSoldier(i).getExperience()));
            writer.newLine();

        }

        writer.close();

    }

    public int readGen1Gold() throws IOException{

        int result;

        this.reader = new BufferedReader(new FileReader(fileName));
        result = Integer.valueOf(reader.readLine());
        this.reader.close();

        return result;

    }

    public int readGen2Gold() throws IOException{

        int result;

        this.reader = new BufferedReader(new FileReader(fileName));
        reader.readLine();
        result = Integer.valueOf(reader.readLine());
        this.reader.close();

        return result;

    }

    public Army readArmy1() throws IOException, NumberFormatException, ExperienceInvalidException, RankInvalidException{

        Army result = new Army(1);
        int size;

        this.reader = new BufferedReader(new FileReader(fileName));
        reader.readLine();
        reader.readLine();

        size = Integer.valueOf(reader.readLine());

        for(int i = 0; i < size; i++){

            Soldier sol = new Soldier(Integer.valueOf(reader.readLine()), Integer.valueOf(reader.readLine()));

            result.addSoldier(sol);

        }

        this.reader.close();

        return result;

    }

    public Army readArmy2() throws IOException, NumberFormatException, ExperienceInvalidException, RankInvalidException{

        Army result = new Army(2);

        int size1;
        int size2;

        this.reader = new BufferedReader(new FileReader(fileName));
        reader.readLine();
        reader.readLine();

        size1 = Integer.valueOf(reader.readLine());

        for(int i = 0; i < size1; i++){

            reader.readLine();
            reader.readLine();

        }

        size2 = Integer.valueOf(reader.readLine());

        for(int i = 0; i < size2; i++){

            Soldier sol = new Soldier(Integer.valueOf(reader.readLine()), Integer.valueOf(reader.readLine()));

            result.addSoldier(sol);

        }

        this.reader.close();

        return result;

    }

}
