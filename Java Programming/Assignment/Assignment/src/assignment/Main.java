package assignment;

public class Main {

    public static void main(String[] args) {
        Team members = new Team();

        Volunteer sofya = new Volunteer("Sofya", 127);
        Volunteer steve = new Volunteer("Steve", 46);
        Volunteer muhammed = new Volunteer("Muhammed", 273);
        Volunteer amaara = new Volunteer("Amaara", 129);
        Volunteer ayub = new Volunteer("Ayub", 129);
        Volunteer tony = new Volunteer("Tony", 17);
        //creating new instances of volunteer

        TeamLeader rabia = new TeamLeader("Rabia", 385);
        //creating a team leader

        members.addMember(sofya);
        members.addMember(steve);
        members.addMember(muhammed);
        members.addMember(amaara);
        members.addMember(ayub);
        members.addMember(tony);
        members.addMember(rabia);

        //adding members to the team (array list)

        try {//try method so anything that's incorrect throws an exception
            System.out.println(members.display());//displaying all members inside the array

            sofya.addBoxes(13);
            steve.addBoxes(9);
            muhammed.addBoxes(27);
            amaara.addBoxes(33);
            ayub.addBoxes(39);
            tony.addBoxes(106);
            //adding boxes to each volunteer

            System.out.println(members.printVolunteers());//displaying all volunteers

            members.sort();//sorting volunteers first in descending order of boxes delivered then alphabetically
            System.out.println(members.display());//displaying all members inside the array after being sorted
            System.out.println(members.totalDelivered());//displaying the total boxes delivered
            System.out.println(Formatter.formatCurrency(members.calculateTotalCost()));//displaying the total cost to be paid out

        } catch (Volunteer.ValidationException validationException) {//catch method if anything in the try method fails

            System.out.println(validationException.getMessage());

        }
    }
}