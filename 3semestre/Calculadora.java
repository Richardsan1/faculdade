import java.util.Scanner;
import java.util.regex.Pattern;

public class Calculadora {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Bem vindo a calculadora!\ndigite sua expressão ou um comando:");
        while (true) { 
            String expression = scanner.nextLine();
            expression = expression.toUpperCase();
            if ("VARS".equals(expression)) {
                
            }
            if ("RESET".equals(expression)) {
                
            }
            if ("REC".equals(expression)) {
                
            }
            if ("STOP".equals(expression)) {
                
            }
            if ("PLAY".equals(expression)) {
                
            }
            if ("ERASE".equals(expression)) {
                
            }
            if ("EXIT".equals(expression)) {
                break;
            }

            Pattern pattern = Pattern.compile("^[A-Z] = \\d+$");
            if (pattern.matcher(expression).matches()) {
            }

            pattern = Pattern.compile("^[A-Z+\\-*/^()]+$");
            if (pattern.matcher(expression).matches()){
            }
        }
    }
}
