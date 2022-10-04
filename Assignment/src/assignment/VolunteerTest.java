package assignment;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;


class VolunteerTest {
    private final Volunteer volunteer1 = new Volunteer("Bob", 18);
    private final Volunteer volunteer2 = new Volunteer("Jim", 53);

    @BeforeEach
    void setUp() {
    }
    @Test
    void ShouldGetName() {
        assertEquals("Bob", volunteer1.getName());
        assertNotEquals("Jim", volunteer1.getName());
    }
    @Test
    void ShouldGetBoxes() {
        assertEquals(18, volunteer1.getBoxes());
        assertNotEquals(18, volunteer2.getBoxes());
    }
    @Test
    void ShouldCalculateTotalCost() {
        assertEquals(2.7, volunteer1.totalCost());
        assertNotEquals(2.7, volunteer2.totalCost());
    }
    @Test
    void shouldDisplayAllDetails() {
        assertEquals("Bob        | 18     | £2.70     \n", volunteer1.display());
        assertNotEquals("Bob        | 18     | £2.70     \n", volunteer2.display());
    }
    @Test
    public void shouldThrowAnExceptionWhenInvalidBoxValueAdded() {
        try {
            volunteer1.addBoxes(-5);

            fail("Expected failure to be thrown");

        } catch (Volunteer.ValidationException ignore) {
        }
    }
    @Test
    void shouldAllowBoxesToBeAdded() throws Volunteer.ValidationException {
        assertEquals(18, volunteer1.getBoxes());
        volunteer1.addBoxes(5);
        assertEquals(23, volunteer1.getBoxes());

    }

}