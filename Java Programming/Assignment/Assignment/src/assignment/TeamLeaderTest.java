package assignment;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class TeamLeaderTest {
    TeamLeader Rabia = new TeamLeader("Rabia", 385);

    @BeforeEach
    void setUp() {
    }

    @Test
    void totalCost() {
        assertEquals(89.40, Rabia.totalCost());
    }

    @Test
    void display() {
        assertEquals("TL Rabia   | 385    | £89.40    \n", Rabia.display());
    }
}