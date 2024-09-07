import java.util.Scanner;

public class Calculadora {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Bem vindo a calculadora!");
        Pilha expressionStack = new Pilha(50);

        OUTER: 
        while (true) {
            System.out.println("digite sua expressão ou um comando: ");
            String expression = scanner.nextLine();
            expression = expression.toUpperCase().replaceAll("\\s", "");

            if (null != expression) {
                switch (expression) {
                    case "VARS" -> {
                    }
                    case "RESET" -> {
                    }
                    case "REC" -> {
                    }
                    case "STOP" -> {
                    }
                    case "PLAY" -> {
                    }
                    case "ERASE" -> {
                    }
                    case "EXIT" -> {
                        break OUTER;
                    }
                    default -> {
                        // verifica se o comando é uma expressão de atribuir valor a variavel
                        if (expression.matches("^[A-Z] = \\d+$")) {
                            // String var = expression.split("=")[0];
                            // int val = Integer.parseInt(expression.split("=")[1]);

                        }
                        // verifica se o comando é uma expressão matemática
                        else if (expression.matches("^[A-Z+\\-*/^()]+$") && validateExpression(expression)) {
                            for (String elem : expression.split("")) {
                                if (elem.matches("[A-Z]")) {
                                    // System.out.println("Variável: " + elem);
                                } else if (elem.matches("[+\\-*/^]")) {
                                    // System.out.println("Operador: " + elem);
                                } else {
                                    // System.out.println("Operando: " + elem);
                                }
                            }
                        } else {
                            System.out.println("Comando inválido!");
                        }
                    }
                }
            } else {
                System.out.println("Comando inválido!");
            }
        }

    }
    
    public static boolean validateExpression(String exp) {
        int operatorCount = 0;
        int operandCount = 0;
        int openParenthesis = 0;
        for (String elem : exp.split("")) {
            if (elem.matches("[+\\-*/^]")) {
                operatorCount++;
            } else if (elem.matches("[A-Z]")) {
                operandCount++;
            } else if (elem.equals("(")) {
                openParenthesis++;
            } else if (elem.equals(")")) {
                openParenthesis--;
            }
        }
        if (operatorCount != operandCount - 1) {
            return false;
        } else if (openParenthesis != 0) {
            return false;
        }
        return true;
    }
}
