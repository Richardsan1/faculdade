package estruturas;

import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.Locale;

/**
 * Os nós que representam valores são obrigatoriamente folhas,
 * por isso, não tem referência a outros nós
 */
public class ValueNode implements Node {
    private static final DecimalFormat DF // Formatador de números para o toString
            = new DecimalFormat("#,##0.##", new DecimalFormatSymbols(Locale.forLanguageTag("pt-BR")));
    private final double value;

    public ValueNode(double value) {
        this.value = value;
    }

    /**
     * Por ser mais simples, o nó de valor retorna apenas seu valor decimal
     *
     * @return Valor decimal do nó
     */
    @Override
    public double getValue() {
        return value;
    }

    @Override
    public String toString() {
        return DF.format(value);
    }
}
