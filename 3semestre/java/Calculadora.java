import java.util.Scanner;

// participantes:
// 1. Richard Barbosa sanches - 10420179
// 2. Juan Nacif - 10428509

// referências: 
// https://www.w3schools.com/java/ref_string_concat.asp
// https://regex-generator.olafneumann.org/

public class Calculadora {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Bem vindo a calculadora!");
        helper();

        Pilha expStack = new Pilha(50);
        Fila recQueue = new Fila(10);
        int[] variables = new int[26];

        boolean rec = false;
        boolean play = false;

        OUTER: 
        while (true) {
            String expression;
            if (rec){
                if (recQueue.isFull()){
                    rec = false;
                    System.out.println("INFO: Fila Cheia, Gravação de comandos desativada!");
                } else {
                    System.out.println("INFO: Gravando: "+recQueue.size()+"/10");
                }
            }
            if (play){
                expression = recQueue.dequeue();
                if (expression == null){
                    play = false;
                    recQueue.resetFront();
                    System.err.println("ERRO: Fila Vazia, Execução de comandos finalizada!");
                    continue;
                }
                System.out.println(expression);
            } else {
                System.out.print("> ");
                expression = scanner.nextLine();
                expression = expression.toUpperCase().replaceAll("\\s", "");
            }

            switch (expression) {
                case "VARS" -> {
                    if (rec){
                        System.err.println("ERRO: Comando inválido na gravação!");
                        continue;
                    }
                    int count = 0;
                    for (int i = 0; i < variables.length; i++) {
                        if (variables[i] != 0) {
                            System.out.println((char) (i + 65) + " = " + variables[i]);
                            count++;
                        }
                    }
                    if (count == 0) {
                        System.out.println("Sem variáveis definidas!");
                    }
                    continue;
                }
                case "RESET" -> {
                    if (rec){
                        recQueue.enqueue(expression);
                        continue;
                    }
                    variables = new int[26];
                    System.out.println("Variáveis resetadas!");
                    continue;
                }
                case "REC" -> {
                    if (rec){
                        System.err.println("ERRO: Comando inválido na gravação!");
                    } else {
                        recQueue = new Fila(10);
                        rec = true;
                        System.err.println("INFO: Gravação de comandos ativada!");
                    }
                    continue;
                }
                case "STOP" -> {
                    if (rec){
                        rec = false;
                        System.err.println("INFO: Gravação de comandos desativada!");
                    } else {
                        System.err.println("ERRO: Comando inválido!");
                    }
                    continue;
                }
                case "PLAY" -> {
                    if (rec){
                        System.err.println("ERRO: Comando inválido na gravação!");
                        continue;
                    }
                    if (recQueue.isEmpty()){
                        System.err.println("ERRO: Não há gravação para ser reproduzida!");
                        continue;
                    }
                    play = true;
                    System.err.println("INFO: Executando comandos gravados!");
                    continue;
                }
                case "ERASE" -> {
                    if (rec){
                        System.err.println("ERRO: Comando inválido na gravação!");
                        continue;
                    }
                    recQueue = new Fila(10);
                    System.out.println("INFO: Comandos apagados!");
                    continue;
                }
                case "EXIT" -> {
                    break OUTER;
                }
                case "CLEAR" -> {
                    if (rec){
                        System.err.println("ERRO: Comando inválido na gravação!");
                    }
                    System.out.print("\033[H\033[2J");
                    System.out.flush();
                    continue;
                }
                case "HELP" -> {
                    if (rec){
                        System.out.println("Comando inválido na gravação!");
                        continue;
                    }
                    helper();
                    continue;
                }
                default -> {
                    // verifica se o comando é uma expressão de atribuir valor a variavel
                    if (expression.matches("[A-Z]=[0-9]+")) {
                        if (rec){
                            recQueue.enqueue(expression);
                            continue;
                        }
                        variables[expression.charAt(0) - 65] = Integer.parseInt(expression.split("=")[1]);
                        if (play){
                            continue;
                        }
                        System.out.println(expression.charAt(0) + " = " + variables[expression.charAt(0) - 65]);
                    }
                    // verifica se o comando é uma expressão matemática
                    else if (expression.matches("^[A-Z+\\-*/^()]+$") && validateExpression(expression)) {
                        if (rec){
                            recQueue.enqueue(expression);
                            continue;
                        }
                        String transformedExp = tranformExpression(expression, expStack);
                        try {
                            System.out.println("RESULTADO: "+calculateExpression(transformedExp, variables));
                        } catch (Exception e) {
                            System.err.println(e.getMessage());
                        }
                    } else {
                        System.out.println("ERRO: Comando inválido!");
                    }
                }
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
                    String letter = valueStack.pop();
                    a = vars[letter.charAt(0) - 65];
                    if (a == 0){
                        throw new Exception("ERRO: Variável "+ letter +" não definida!");
                    }
                } else {
                    a = Integer.parseInt(valueStack.pop());
                }

                int b;
                if (valueStack.topElement().matches("[A-Z]")) {
                    String letter = valueStack.pop();
                    b = vars[letter.charAt(0) - 65];
                    if (b == 0){
                        throw new Exception("ERRO: Variável "+ letter +" não definida!");
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
    
    public static void helper(){
        System.out.println("===================================================================");
        System.out.println("1. Digite uma expressão matemática ou de atribuição de variável;");
        System.out.println("2. Digite 'VARS' para ver as variáveis;");
        System.out.println("3. Digite 'RESET' para resetar as variáveis;");
        System.out.println("4. Digite 'REC' para gravar comandos;");
        System.out.println("5. Digite 'STOP' para parar de gravar comandos;");
        System.out.println("6. Digite 'ERASE' para apagar comandos gravados;");
        System.out.println("7. Digite 'PLAY' para executar comandos gravados;");
        System.out.println("8. Digite 'CLEAR' para limpar a tela;");
        System.out.println("9. Digite 'HELP' para ver os comandos disponíveis;");
        System.out.println("10. Digite 'EXIT' para sair;");
        System.out.println("===================================================================");
    }
}