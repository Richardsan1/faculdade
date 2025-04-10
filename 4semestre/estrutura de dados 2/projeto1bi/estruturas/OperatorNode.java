/**
 * Richard Barbosa Sanches - 10420179
 * Júlia Vitória Bomfim do Nascimento - 10425604
 * William Saran dos Santos Junior - 10420128
 *
 * Referências: slides da aula teórica e enunciado do projeto
 */

package estruturas;

/**
 * Os nós que representam as operações são obrigatoriamente não folhas, e, seus filhos
 * podem ser ValueNodes ou outros OperatorNodes
 */
public class OperatorNode implements Node {
    private final char operator;
    private final Node esquerda;
    private final Node direita;

    public OperatorNode(char operator, Node esquerda, Node direita) {
        this.operator = operator;
        this.esquerda = esquerda;
        this.direita = direita;
    }

    @Override
    public Node getEsquerda() {
        return esquerda;
    }

    @Override
    public Node getDireita() {
        return direita;
    }

    /**
     * Retorna o valor da operação de acordo com seu tipo de operador
     *
     * @return Valor da operação entre seus nós filhos
     */
    @Override
    public double getValue() {
        // Se faltar algum operando
        if (esquerda == null || direita == null) {
            throw new OperandosInsuficientesException(operator);
        }

        switch (operator) {
            case '*':
                return esquerda.getValue() * direita.getValue();
            case '/':
                double dir = direita.getValue();
                // Se for divisão por 0
                if (dir == 0) {
                    throw new DivisaoPorZeroException();
                }
                return esquerda.getValue() / dir;
            case '+':
                return esquerda.getValue() + direita.getValue();
            case '-':
                return esquerda.getValue() - direita.getValue();
            default:
                return 0;
        }
    }

    // Função utilitária para checar se um caractere é um operador

    public static boolean isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    // Função utilitária que retorna a prioridade de um operador
    public static int getPrioridade(char operator) {
        if (operator == '*' || operator == '/') {
            return 2;
        } else if (operator == '+' || operator == '-') {
            return 1;
        }
        return 0;
    }

    @Override
    public String toString() {
        return String.valueOf(operator);
    }

    /**
     * Se o nó operador não tiver 2 operandos, a exceção é lançada, pois não é possível fazer
     */
    private static class OperandosInsuficientesException extends RuntimeException {
        private static final String ERROR_MESSAGE = "A operação '%c' não pode ser realizada sem dois operandos";

        public OperandosInsuficientesException(char operator) {
            this(String.format(ERROR_MESSAGE, operator));
        }

        private OperandosInsuficientesException(String message) {
            super(message);
        }
    }

    private static class DivisaoPorZeroException extends RuntimeException {
        public DivisaoPorZeroException() {
            super("A divisão por 0 não é possível");
        }
    }
}
