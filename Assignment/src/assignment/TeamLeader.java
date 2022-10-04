package assignment;

public class TeamLeader extends Volunteer {

    public TeamLeader( String name, int boxes) {
        super(name, boxes);

    }
    @Override
    public double totalCost() {

        return super.totalCost() * 1.2;
    }
    @Override
    public String display(){

        return String.format("TL %-7s | %-6d | %-10s\n",  getName(), getBoxes(), Formatter.formatCurrency(totalCost()));

    }
}