package Soldier;

public class Soldier {

    public class ExperienceInvalidException extends Exception{

        public ExperienceInvalidException(){

            super("Experience cannot be less than 0 or higher than or equal to the rank value times 5!");

        }

    }

    public class RankInvalidException extends Exception{

        public RankInvalidException(){

            super("Rank cannot be lower than 1 or higher than 4!");

        }

    }

    private int rank;
    private int experience;
    private int power;

    public Soldier(){

        this.experience = 1;
        this.rank = 1;

    }

    private boolean checkIfExperienceValid(int experience, int rank) throws ExperienceInvalidException{

        if((rank >= 4 || experience < 5 * rank) && experience > 0){
            return true;
        }
        else{
            throw new ExperienceInvalidException();
        }

    }

    private boolean checkIfRankValid(int rank) throws RankInvalidException{

        if(rank > 0 && rank <= 4){
            return true;
        }
        else{
            throw new RankInvalidException();
        }

    }

    public Soldier(int rank, int experience) throws ExperienceInvalidException, RankInvalidException{

        if(checkIfExperienceValid(experience, rank) && checkIfRankValid(rank)){
            this.experience = experience;
            this.rank = rank;
            this.power = rank * experience;
        }

    }

    private void recalculatePower(){

        this.power = this.experience * this.rank;

    }

    public int getPower(){

        recalculatePower();
        return this.power;

    }

    public void rankUp(){

        this.rank += 1;
        this.experience = 1;

    }

    public void trainSoldier(){

        this.experience += 1;

    }

    public void hurtSoldier(){

        this.experience -= 1;

    }

    public int getExperience(){

        return this.experience;

    }

    public void setExperience(int experience) throws ExperienceInvalidException{

        if(checkIfExperienceValid(experience, this.rank)){
            this.experience = experience;
        }

    }

    public int getRank(){

        return this.rank;

    }

    public void setRank(int rank) throws RankInvalidException{

        if(checkIfRankValid(rank)){
            this.rank = rank;
        }

    }
    
}