/**
 * Richard Barbosa Sanches - 10420179
 * Júlia Vitória Bomfim do Nascimento - 10425604
 * William Saran dos Santos Junior - 10420128
 *
 * Referências: slides da aula teórica e enunciado do projeto
 */

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
