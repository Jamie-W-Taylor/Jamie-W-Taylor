package assignment;

import java.text.NumberFormat;
import java.util.Locale;

public class Formatter { //separate class for formatting money due to not belonging in volunteer or team class
    public static String formatCurrency(double amount){
        NumberFormat nf = NumberFormat.getCurrencyInstance(Locale.UK);
        return nf.format(amount);
    }
}