import java.util.Scanner;

// participantes:
// 1. Richard Barbosa sanches - 10420179
// 2. Juan - 1042----

public class Calculadora {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Bem vindo a calculadora!");
        Pilha expStack = new Pilha(50);
        Fila recQueue = new Fila(10);
        int[] variables = new int[26];

        boolean rec = false;

        OUTER: 
        while (true) {
            System.out.print("digite sua expressão ou um comando: ");
            String expression = scanner.nextLine();
            expression = expression.toUpperCase().replaceAll("\\s", "");

            if (null != expression) {
                switch (expression) {
                    case "VARS" -> {
                        if (variables.length == 0) {
                            System.out.println("Sem variáveis definidas!");
                        }
                        for (int i = 0; i < variables.length; i++) {
                            if (variables[i] != 0) {
                                System.out.println((char) (i + 65) + " = " + variables[i]);
                            }
                        }
                        continue;
                    }
                    case "RESET" -> {
                        variables = new int[26];
                        continue;
                    }
                    case "REC" -> {
                        if (rec){
                            System.err.println("Comando inválido!");
                        } else {
                            rec = true;
                        }
                        continue;
                    }
                    case "STOP" -> {
                        if (rec){
                            rec = false;
                        } else {
                            System.err.println("Comando inválido!");
                        }
                        continue;
                    }
                    case "PLAY" -> {
                        while (true) {
                            if (recQueue.isEmpty()) {
                                break;
                            }
                            System.out.println(recQueue.dequeue());
                        }
                    }
                    case "ERASE" -> {
                        recQueue = new Fila(10);
                        continue;
                    }
                    case "EXIT" -> {
                        break OUTER;
                    }
                    default -> {
                        // verifica se o comando é uma expressão de atribuir valor a variavel
                        if (expression.matches("[A-Z]=[0-9]+")) {
                            variables[expression.charAt(0) - 65] = Integer.parseInt(expression.split("=")[1]);
                        }
                        // verifica se o comando é uma expressão matemática
                        else if (expression.matches("^[A-Z+\\-*/^()]+$") && validateExpression(expression)) {
                            String transformedExp = tranformExpression(expression, expStack);
                            System.out.println("transformedExp: "+transformedExp);
                            try {
                                System.out.println("Resultado: "+calculateExpression(transformedExp, variables));
                            } catch (Exception e) {
                                System.err.println(e.getMessage());
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
                if (openParenthesis < 0) {
                    return false;
                }
            }
        }
        return !((operatorCount != operandCount-1 || operandCount <= 1) || openParenthesis != 0);
    }
    
    public static String tranformExpression(String exp, Pilha valueStack) {
        StringBuilder out = new StringBuilder();
        for (String elem : exp.split("")) {
            if (elem.matches("[A-Z]")) {
                out.append(elem);
            } 
            else if (elem.matches("[+\\-*/(]")) {
                while (!valueStack.isEmpty() && precedence(elem.charAt(0)) <= precedence(valueStack.topElement().charAt(0))) {
                    out.append(valueStack.pop());
                }
                valueStack.push(elem);
                
            } 
            else if (elem.equals(")")) {
                while (!valueStack.topElement().equals("(")) {
                    out.append(valueStack.pop());
                }
                valueStack.pop();
            }
        }
        while (!valueStack.isEmpty()) {
            out.append(valueStack.pop());
        }
        
        return out.toString();
    }

    public static int calculateExpression(String exp, int[] vars) throws Exception {
        Pilha valueStack = new Pilha(10);
        for (String elem : exp.split("")) {
            if (elem.matches("[A-Z]")){
                valueStack.push(elem);
            } 
            else if (elem.matches("[+\\-*/]")) {
                int a;
                if (valueStack.topElement().matches("[A-Z]")) {
                    a = vars[valueStack.pop().charAt(0) - 65];
                    if (a == 0){
                        throw new Exception("Variável não definida!");
                    }
                } else {
                    a = Integer.parseInt(valueStack.pop());
                }

                int b;
                if (valueStack.topElement().matches("[A-Z]")) {
                    b = vars[valueStack.pop().charAt(0) - 65];
                    if (b == 0){
                        throw new Exception("Variável não definida!");
                    }
                } else {
                    b = Integer.parseInt(valueStack.pop());
                }
                
                switch (elem) {
                    case "+" -> valueStack.push(String.valueOf(a + b));
                    case "-" -> valueStack.push(String.valueOf(b - a));
                    case "*" -> valueStack.push(String.valueOf(a * b));
                    case "/" -> valueStack.push(String.valueOf(b / a));
                }
            }
        }
        return Integer.parseInt(valueStack.pop());
    }

    public static int precedence(char c) {
        return switch (c) {
            case '+', '-' -> 1;
            case '*', '/' -> 2;
            default -> -1;
        };
    }
}


// refs: https://www.w3schools.com/java/ref_string_concat.asp
//       https://regex-generator.olafneumann.org/