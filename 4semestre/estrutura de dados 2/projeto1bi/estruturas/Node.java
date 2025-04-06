package estruturas;

/**
 * Interface comum entre os dois tipos de nó, tanto os nós de operadores,
 * quanto os nós de valores irão retornar seus respectivos valores
 */
public interface Node {
    double getValue();

    default Node getEsquerda() {
        return null;
    }
    default Node getDireita() {
        return getEsquerda();
    }
}
