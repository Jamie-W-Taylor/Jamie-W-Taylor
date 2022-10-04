package assignment;


import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class TeamTest {

    private final Volunteer volunteer1 = new Volunteer("Bob", 18);
    private final Volunteer volunteer2 = new Volunteer("Jim", 47);
    private final Team team = new Team();

    @Test
    void addingMembersIncreasesTheTotalCost() {
        team.addMember(volunteer1);
        assertEquals(2.70, team.calculateTotalCost());
        team.addMember(volunteer2);
        assertNotEquals(2.70, team.calculateTotalCost());
    }

    @Test
    void ShouldPrintAllVolunteers() {
        team.addMember(volunteer1);
        assertEquals("Bob\n", team.printVolunteers());
        team.addMember(volunteer2);
        assertNotEquals("Bob\n", team.printVolunteers());
    }

    @Test
    void shouldDisplayAllDetails() {
        team.addMember(volunteer1);
        assertEquals("""
                Bob        | 18     | £2.70    \s

                The total boxes delivered is 18 and the total cost to be paid out is £2.70\s""", team.display());
        team.addMember(volunteer2);
        assertNotEquals("""
                Bob        | 18     | £2.70    \s

                The total boxes delivered is 18 and the total cost to be paid out is £2.70\s""", team.display());//shows it being updated
    }

    @Test
    void shouldDisplayTotalDelivered() {
        team.addMember(volunteer1);
        assertEquals(18, team.totalDelivered());
        team.addMember(volunteer2);
        assertNotEquals(18, team.totalDelivered());
    }

    @Test
    void shouldCalculateTotalCost() {
        team.addMember(volunteer1);
        assertEquals(2.70, team.calculateTotalCost());
        team.addMember(volunteer2);
        assertNotEquals(10, team.calculateTotalCost());
    }

    @Test
    void shouldChangeTheOrderWhenSortIsCalled() {

        team.addMember(volunteer1);
        team.addMember(volunteer2);

        assertEquals("""
                Bob        | 18     | £2.70    \s
                Jim        | 47     | £7.05    \s

                The total boxes delivered is 65 and the total cost to be paid out is £9.75\s""", team.display());

        team.sort();

        assertEquals("""
                Jim        | 47     | £7.05    \s
                Bob        | 18     | £2.70    \s

                The total boxes delivered is 65 and the total cost to be paid out is £9.75\s""", team.display());
    }
}