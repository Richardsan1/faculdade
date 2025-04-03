import java.util.Scanner;
import java.util.Stack;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Node root = null;

        while (true) {
            System.out.println("1. Entrada da expressão aritmética na notação infixa");
            System.out.println("2. Criar a árvore binária de expressão aritmética");
            System.out.println("3. Exibir a árvore binária de expressão aritmética");
            System.out.println("4. Calcular a expressão");
            System.out.println("5. Encerrar o programa");
            System.out.print("Escolha uma opção:");
            int opcao = scanner.nextInt();
            scanner.nextLine(); // Consumir a quebra de linha

            switch (opcao) {
                case 1 -> {
                    System.out.println("Digite a expressão aritmética na notação infixa:");
                    String expressao = scanner.nextLine();
                    root = criarArvore(expressao);
                }
                case 2 -> {
                    if (root == null) {
                        System.out.println("A árvore ainda não foi criada. Insira uma expressão primeiro.");
                    } else {
                        System.out.println("Árvore criada com sucesso!");
                    }
                }
                case 3 -> {
                    if (root == null) {
                        System.out.println("A árvore ainda não foi criada.");
                    } else {
                        System.out.println("Árvore binária de expressão aritmética:");
                        exibirArvore(root, 0);
                    }
                }
                case 4 -> {
                    if (root == null) {
                        System.out.println("A árvore ainda não foi criada.");
                    } else {
                        System.out.println("\nResultado da expressão: " + calcularExpressao(root) + "\n");
                    }
                }
                case 5 -> {
                    System.out.println("Encerrando o programa...");
                    scanner.close();
                    return;
                }
                default -> System.out.println("Opção inválida. Tente novamente.");
            }
        }
    }

    // Função 2: Criar a árvore binária de expressão aritmética
    public static Node criarArvore(String expressao) {
        Stack<Node> pilha = new Stack<>();
        Stack<Character> operadores = new Stack<>();
        StringBuilder numero = new StringBuilder();

        for (char c : expressao.toCharArray()) {
            if (Character.isDigit(c) || c == '.') {
                numero.append(c); // Constrói o número com várias casas decimais
            } else {
                if (numero.length() > 0) {
                    pilha.push(new Node(Double.valueOf(numero.toString())));
                    numero.setLength(0); // Limpa o número acumulado
                }
                if (c == '(') {
                    operadores.push(c);
                } else if (c == ')') {
                    while (!operadores.isEmpty() && operadores.peek() != '(') {
                        pilha.push(criarSubArvore(operadores.pop(), pilha));
                    }
                    operadores.pop(); // Remove '('
                } else if (isOperador(c)) {
                    while (!operadores.isEmpty() && prioridade(operadores.peek()) >= prioridade(c)) {
                        pilha.push(criarSubArvore(operadores.pop(), pilha));
                    }
                    operadores.push(c);
                }
            }
        }
    
        if (numero.length() > 0) {
            pilha.push(new Node(Double.valueOf(numero.toString())));
        }

        while (!operadores.isEmpty()) {
            pilha.push(criarSubArvore(operadores.pop(), pilha));
        }

        return pilha.pop();
    }

    private static Node criarSubArvore(char operador, Stack<Node> pilha) {
        Node direito = pilha.pop();
        Node esquerdo = pilha.pop();
        return new Node(operador, esquerdo, direito);
    }

    private static boolean isOperador(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    private static int prioridade(char operador) {
        if (operador == '+' || operador == '-') return 1;
        if (operador == '*' || operador == '/') return 2;
        return 0;
    }

    public static void exibirArvore(Node node, int nivel) {
        // refatorar ta meio bugado
        if (node == null) return;
        exibirArvore(node.getRight(), nivel + 1);
        System.out.println(" ".repeat(nivel * 4) + node.getData());
        exibirArvore(node.getLeft(), nivel + 1);
        }

    public static double calcularExpressao(Node node) {
        if (node == null) return 0;
        if (node.getLeft() == null && node.getRight() == null) {
            return (double) node.getData();
        }
        double esquerdo = calcularExpressao(node.getLeft());
        double direito = calcularExpressao(node.getRight());
        switch ((char) node.getData()) {
            case '+' -> {
            return esquerdo + direito;
            }
            case '-' -> {
            return esquerdo - direito;
            }
            case '*' -> {
            return esquerdo * direito;
            }
            case '/' -> {
            return esquerdo / direito;
            }
        }
        return 0;
    }
}