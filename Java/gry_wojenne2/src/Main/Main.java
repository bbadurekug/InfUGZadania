package Main;

import Manager.*;
import Sack.Sack.GoldValueInvalidException;
import Soldier.Soldier.ExperienceInvalidException;
import Soldier.Soldier.RankInvalidException;

import java.io.IOException;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws ExperienceInvalidException, RankInvalidException, GoldValueInvalidException, IOException {

        boolean gameRunning = true;
        int choice = -1;
        int result = -1;
        @SuppressWarnings("resource")
        Scanner input = new Scanner(System.in);

        System.out.println("Witaj w grze, wybierz 1 - zacznij nowa gre, 2 - zaladuj poprzednia gre");

        Manager man = new Manager();

        choice = input.nextInt();

        if(choice == 2) man.loadFile();

        while (gameRunning){

            System.out.println("General 1 - Twoja kolej, masz " + man.getGeneralGold(1) + " zlota i " + man.getArmyPower(1) + " sily armii");
            System.out.println("1 - trenuj armie, 2 - zaatakuj przeciwnika, 3 - kup zolnierza, 4 - zapisz gre, 5 - zakoncz gre");

            choice = input.nextInt();

            switch (choice) {
                case 1:
                    
                    result = man.trainArmy(1);
                    
                    if(result == 1){

                        System.out.println("Cala armia wytrenowana");

                    }
                    else{

                        System.out.println("Zbyt malo pieniedzy, aby wytrenowac cala armie. Wytrenowac czesciowo?");
                        System.out.println("1 - tak, 2 - nie");

                        choice = input.nextInt();

                        if(choice == 1){

                            result = man.trainArmyPartially(1);
                            System.out.println("Wytrenowano " + choice + " zolnierzy");

                        }

                    }

                    break;

                case 2:

                    man.battle();

                    break;

                case 3:

                    System.out.println("Jakiej rangi?");

                    choice = input.nextInt();

                    man.buySoldier(1, choice);

                    choice = -1;

                    break;

                case 4:

                    man.saveFile();

                    break;
                    
                case 5:

                    gameRunning = false;

                    break;

                default:
                    break;
            }

            choice = -1;

            System.out.println("General 2 - Twoja kolej, masz " + man.getGeneralGold(2) + " zlota i " + man.getArmyPower(2) + " sily armii");
            System.out.println("1 - trenuj armie, 2 - zaatakuj przeciwnika, 3 - kup zolnierza, 4 - zapisz gre, 5 - zakoncz gre");

            choice = input.nextInt();

            switch (choice) {
                case 1:
                    
                    result = man.trainArmy(2);
                        
                    if(result == 1){

                        System.out.println("Cala armia wytrenowana");

                    }
                    else{

                        System.out.println("Zbyt malo pieniedzy, aby wytrenowac cala armie. Wytrenowac czesciowo?");
                        System.out.println("1 - tak, 2 - nie");

                        choice = input.nextInt();

                        if(choice == 1){

                            result = man.trainArmyPartially(2);
                            System.out.println("Wytrenowano " + choice + " zolnierzy");

                        }

                    }

                    break;

                case 2:

                    man.battle();

                    break;

                case 3:

                    System.out.println("Jakiej rangi?");
                    choice = input.nextInt();

                    man.buySoldier(2, choice);

                    choice = -1;

                    break;

                case 4:

                    man.saveFile();

                    break;
                    
                case 5:

                    gameRunning = false;

                    break;
            
                default:
                    break;
            }

            choice = -1;

            if(man.checkGameStatus() != 0){

                gameRunning = false;

                if(man.checkGameStatus() == 1){
                    System.out.println("Gracz 1 wygrywa!");
                }
                else{
                    System.out.println("Gracz 2 wygrywa!");
                }

            }

        }

    }
}
