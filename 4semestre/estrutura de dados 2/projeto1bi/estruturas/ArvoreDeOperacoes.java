/**
 * Richard Barbosa Sanches - 10420179
 * Júlia Vitória Bomfim do Nascimento - 10425604
 * William Saran dos Santos Junior - 10420128
 *
 * Referências: slides da aula teórica e enunciado do projeto
 */

package estruturas;

import java.util.Stack;

/**
 * Representa a árvore de operações que contém nós do tipo Node
 */
public class ArvoreDeOperacoes {
    // Variáveis auxiliares para formatação
    private static final String ESPACO = " ";
    public static final String NEW_LINE = "\n";

    // Raiz da árvore
    private final Node raiz;

    /**
     * Construtor que popula a árvore a partir de uma expressão infixa,
     * utiliza pilhas como estruturas de dados auxiliares
     *
     * @param expressao Expressão infixa a ser convertida
     */
    public ArvoreDeOperacoes(String expressao) {
        // Verifica se a expressão é nula ou vazia
        if (expressao == null || expressao.trim().isEmpty()) {
            throw new IllegalArgumentException("Expressão vazia ou nula.");
        }

        // Variáveis auxiliares e pilhas para armazenar os nós e operadores
        Stack<Node> pilha = new Stack<>();
        Stack<Character> operadores = new Stack<>();
        StringBuilder numero = new StringBuilder();
        int parentesesBalanceados = 0;
        char ultimoChar = 0;

        // Remove espaços em branco da expressão
        expressao = expressao.replaceAll("\\s+", "");

        // Verifica se a expressão começa ou termina com um operador
        for (int i = 0; i < expressao.length(); i++) {
            char c = expressao.charAt(i);

            // Verifica se o caractere é um dígito ou ponto decimal para gerar os números
            if (Character.isDigit(c) || c == '.') {
                numero.append(c);
            } else { // Se não for um dígito ou ponto decimal, processa o número acumulado
                if (!numero.isEmpty()) {
                    try {
                        pilha.push(new ValueNode(Double.parseDouble(numero.toString())));
                    } catch (NumberFormatException e) {
                        throw new IllegalArgumentException("Número inválido: " + numero);
                    }
                    numero.setLength(0); // Reseta o buffer do número
                }

                // Verifica se o caractere é um operador ou parêntese
                if (c == '(') {
                    operadores.push(c);
                    parentesesBalanceados++;
                } else if (c == ')') { // Se for um parêntese de fechamento, retira os operadores da pilha até encontrar o correspondente '('
                    parentesesBalanceados--;
                    if (parentesesBalanceados < 0) {
                        throw new IllegalArgumentException("Parênteses desbalanceados: ')' inesperado.");
                    }

                    // Processa os operadores até encontrar o parêntese de abertura
                    while (!operadores.isEmpty() && operadores.peek() != '(') {
                        if (pilha.size() < 2) throw new IllegalArgumentException("Expressão mal formada.");
                        pilha.push(criarOperador(operadores.pop(), pilha));
                    }
                    // Se não houver parênteses de abertura correspondente, a expressão está mal formada
                    if (operadores.isEmpty()) {
                        throw new IllegalArgumentException("Parênteses desbalanceados: '(' ausente.");
                    }
                    operadores.pop(); // Remove '('
                } else if (OperatorNode.isOperator(c)) { // Se for um operador, verifica se é válido
                    if (i == 0 || i == expressao.length() - 1 || OperatorNode.isOperator(ultimoChar)) {
                        throw new IllegalArgumentException("Operador inválido na posição " + i + ": '" + c + "'");
                    }

                    // Processa os operadores na pilha de acordo com a prioridade
                    while (!operadores.isEmpty() && OperatorNode.getPrioridade(operadores.peek()) >= OperatorNode.getPrioridade(c)) {
                        // Se não houver operandos suficientes na pilha, a expressão está mal formada
                        if (pilha.size() < 2) throw new IllegalArgumentException("Expressão mal formada.");
                        pilha.push(criarOperador(operadores.pop(), pilha));
                    }
                    operadores.push(c);
                } else { // Se o caractere não for um dígito, operador ou parêntese, é inválido
                    throw new IllegalArgumentException("Caractere inválido: '" + c + "'");
                }
            }

            // Atualiza o último caractere processado
            ultimoChar = c;
        }

        // Se ainda houver um número acumulado, adiciona à pilha
        if (!numero.isEmpty()) {
            try {
                pilha.push(new ValueNode(Double.parseDouble(numero.toString())));
            } catch (NumberFormatException e) {
                throw new IllegalArgumentException("Número inválido no fim da expressão: " + numero);
            }
        }

        // Verifica se a expressão termina com um operador
        if (parentesesBalanceados != 0) {
            throw new IllegalArgumentException("Parênteses desbalanceados na expressão.");
        }

        // Processa os operadores restantes na pilha
        while (!operadores.isEmpty()) {
            // Se ainda houver parênteses na pilha, a expressão está mal formada
            if (operadores.peek() == '(' || operadores.peek() == ')') {
                throw new IllegalArgumentException("Parênteses desbalanceados restantes.");
            }
            // Se não houver operandos suficientes na pilha, a expressão está mal formada
            if (pilha.size() < 2) throw new IllegalArgumentException("Expressão mal formada.");
            pilha.push(criarOperador(operadores.pop(), pilha));
        }

        // Se ainda houver operadores na pilha, a expressão está mal formada
        if (pilha.size() != 1) {
            throw new IllegalArgumentException("Expressão mal formada: múltiplos nós restantes.");
        }

        // O elemento no fim do pilha é a raiz da árvore
        raiz = pilha.pop();
    }

    /**
     * Calcula o valor da expressão aritmética representada pela árvore
     *
     * @return Valor da expressão
     */
    public double calcular() {
        return raiz.getValue();
    }

    // Cria o nó de operador a partir da operaçõo e de dois nós filhos
    private static Node criarOperador(char operador, Stack<Node> pilha) {
        Node direito = pilha.pop();
        Node esquerdo = pilha.pop();
        return new OperatorNode(operador, esquerdo, direito);
    }

    // Função para exibir a árvore em diferentes ordens
    public void exibir() {
        exibirPreOrdem();
        exibirEmOrdem();
        exibirPosOrdem();
        System.out.print(NEW_LINE);
    }


    // Funções para exibir a árvore em pré-ordem, em ordem e pós-ordem
    public void exibirPreOrdem() {
        System.out.print("Pré ordem: ");
        exibirPreOrdem(raiz);
        System.out.print(NEW_LINE);
    }

    public void exibirEmOrdem() {
        System.out.print("Em ordem: ");
        exibirEmOrdem(raiz);
        System.out.print(NEW_LINE);
    }

    public void exibirPosOrdem() {
        System.out.print("Pós ordem: ");
        exibirPosOrdem(raiz);
        System.out.print(NEW_LINE);
    }

    private void exibirPreOrdem(Node node) {
        if (node == null) {
            return;
        }
        System.out.print(node + ESPACO);
        exibirPreOrdem(node.getEsquerda());
        exibirPreOrdem(node.getDireita());
    }

    private void exibirEmOrdem(Node node) {
        if (node == null) {
            return;
        }
        exibirEmOrdem(node.getEsquerda());
        System.out.print(node + ESPACO);
        exibirEmOrdem(node.getDireita());
    }

    private void exibirPosOrdem(Node node) {
        if (node == null) {
            return;
        }
        exibirPosOrdem(node.getEsquerda());
        exibirPosOrdem(node.getDireita());
        System.out.print(node + ESPACO);
    }
    // Fim das funções de exibição
}
