/**
 * Richard Barbosa Sanches - 10420179
 * Júlia Vitória Bomfim do Nascimento - 10425604
 * William Saran dos Santos Junior - 10420128
 *
 * Referências: slides da aula teórica e enunciado do projeto
 */

import estruturas.ArvoreDeOperacoes;

import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.Locale;
import java.util.Scanner;

public class Main {
    private static final DecimalFormat DF // Formatador de números
            = new DecimalFormat("#,##0.##############", new DecimalFormatSymbols(Locale.forLanguageTag("pt-BR")));
    private static ArvoreDeOperacoes arvore;

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String expressao = null;
        while (true) {
            try {
                exibirMenu();

                int opcao = Integer.parseInt(scanner.nextLine().trim());

                switch (opcao) {
                    case 1 -> {
                        System.out.println("Digite a expressão aritmética na notação infixa:");
                        expressao = scanner.nextLine();
                        if (expressao == null || expressao.trim().isEmpty()) {
                            throw new RuntimeException("A expressão aritmética não pode ser vazia");
                        }
                    }
                    case 2 -> {
                        if (expressao == null) {
                            throw new RuntimeException("A expressão aritmética não foi informada ainda");
                        } else {
                            arvore = new ArvoreDeOperacoes(expressao);
                            System.out.println("Árvore binária de expressão aritmética criada com sucesso.");
                        }
                    }
                    case 3 -> {
                        if (arvore == null) {
                            throw new RuntimeException("A árvore ainda não foi criada");
                        } else {
                            System.out.println("Árvore binária de expressão aritmética:");
                            arvore.exibir();
                        }
                    }
                    case 4 -> {
                        if (arvore == null) {
                            throw new RuntimeException("A árvore ainda não foi criada");
                        } else {
                            System.out.println("\nResultado da expressão: " + DF.format(arvore.calcular()) + "\n");
                        }
                    }
                    case 5 -> {
                        System.out.println("Encerrando o programa...");
                        scanner.close();
                        return;
                    }
                    default -> throw new RuntimeException("Opção inválida. Tente novamente.");
                }
            } catch (Exception e) {
                System.out.println("[ERRO] " + e.getMessage() + "\n");
            }
        }
    }

    private static void exibirMenu() {
        System.out.println("1. Entrada da expressão aritmética na notação infixa");
        System.out.println("2. Criar a árvore binária de expressão aritmética");
        System.out.println("3. Exibir a árvore binária de expressão aritmética");
        System.out.println("4. Calcular a expressão");
        System.out.println("5. Encerrar o programa");
        System.out.print("Escolha uma opção: ");
    }
}