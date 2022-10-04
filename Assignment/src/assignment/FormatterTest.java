package assignment;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

class FormatterTest {

    @Test
    void testFormatCurrency() {
        assertEquals("£10.00", Formatter.formatCurrency(10));
        assertNotEquals("£10", Formatter.formatCurrency(10));
    }

    @Test
    void testFormatCurrencyWithPence() {
        assertEquals("£10.21", Formatter.formatCurrency(10.21));
        assertNotEquals("£10", Formatter.formatCurrency(10.21));
    }
}