package assignment;

import java.math.BigDecimal;

public class Volunteer implements Comparable<Volunteer>{

    private String name;
    private int boxes;//creating private variables

    public Volunteer(String name, int boxes) {//creating a constructor to set name and boxes
        this.name = name;
        this.boxes = boxes;
    }

    public String getName()
    {
        return name;
    }

    public int getBoxes() {
        return boxes;
    }//getters for name and boxes

    public double totalCost() {//method to find total cost of boxes delivered

        double total = 0;

        if (this.boxes > 50) {

            total +=  50 * 0.15;
            total +=  (this.boxes - 50) * 0.20;

        } else {
            total += this.boxes * 0.15;
        }
        return Math.round(total*100.00)/100.00;

    }

    public String display(){
        return String.format("%-10s | %-6d | %-10s\n", this.name, this.boxes, Formatter.formatCurrency((totalCost())));//display method to display Volunteers
    }

    public void addBoxes(int addedBoxes) throws ValidationException {

        if (addedBoxes <= 0 | addedBoxes >1000) {

            throw new ValidationException(String.format("Invalid value: %d is an invalid number", addedBoxes));

        }
        else
        {
            this.boxes +=  addedBoxes;
        }
    }
    public void addBoxes(String addedBoxes) throws ValidationException {


        throw new ValidationException(String.format("Invalid value: %s is invalid input", addedBoxes));

    }
    public void addBoxes(double addedBoxes) throws ValidationException {


        throw new ValidationException(String.format("Invalid value: %s is invalid input", addedBoxes));
    }
    //methods to add boxes or throw an exception if wrong

    @Override
    public int compareTo(Volunteer volunteer) {//compareTo method to sort my descending order then alphabetical order
        if (volunteer.getBoxes() > this.getBoxes()){
            return 1;
        }else if(volunteer.getBoxes() < this.getBoxes()){
            return -1;
        }
        else if (volunteer.getBoxes() == this.getBoxes()){
            return this.name.compareToIgnoreCase(volunteer.name);
        }else
        {
            return 0;
        }
    }
    class ValidationException extends Exception {
        public ValidationException(String message) {
            super(message);
        }//validation exception method
    }
}