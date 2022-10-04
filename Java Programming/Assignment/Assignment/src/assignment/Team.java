package assignment;


import java.util.ArrayList;
import java.util.Collections;

public class Team {

    private final ArrayList<Volunteer> team = new ArrayList<>();//creating array

    public Team(){//default constructor so array can be created

    }

    public void addMember(Volunteer Member){//public method to add member

        team.add(Member);

    }

    public String printVolunteers() {//method to print out volunteers
        StringBuilder sb = new StringBuilder();
        for (Volunteer volunteer : team) {
            volunteer.display();
            sb.append(String.format("%s", volunteer.getName()));
            sb.append("\n");

        }
        return sb.toString();
    }


    public String display()//method to display all details of each volunteer in a table
    {

        StringBuilder sb = new StringBuilder();
        for (Volunteer volunteer: team)
        {
            sb.append(volunteer.display());
        }

            sb.append(String.format("\nThe total boxes delivered is %d and the total cost to be paid out is %s ", totalDelivered(), Formatter.formatCurrency(calculateTotalCost())));
            return sb.toString();




    }

    public int totalDelivered(){//method to return the total amount of boxes deliverd
        int totalBoxes = 0;
        for(Volunteer volunteer: team){
            totalBoxes += volunteer.getBoxes();
        }
        return totalBoxes;
    }

    public double calculateTotalCost() {//method to calculate total cost to be paid out

        double totalCost = 0;


        for(Volunteer volunteer: team){
            totalCost += volunteer.totalCost();

        }
        return totalCost;
    }

    public void sort(){//method for sorting the array

        Collections.sort(team);

    }

}