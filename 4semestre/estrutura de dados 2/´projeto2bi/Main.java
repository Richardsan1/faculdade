import java.io.*;
import java.time.LocalDate;

public class Main {
    public static void main(String[] args) {
        System.out.println("=== ANÁLISE EXPLORATÓRIA - ODS 8: TRABALHO DECENTE E CRESCIMENTO ECONÔMICO ===\n");

        EmpresaRecord[] registros = lerCSV("REL_2025-01_04_PDA_CONSTITUICAO_MES.csv");
        if (registros.length == 0) {
            System.out.println("Nenhum registro encontrado no arquivo CSV.");
            return;
        }
        System.out.println("Total de registros carregados: " + registros.length + "\n");

        // Criação das estruturas de dados
        BST bstPorData = new BST();
        BST bstPorMunicipio = new BST();
        BST bstPorNatureza = new BST();
        BST bstPorPorte = new BST();
        BST bstPorCnae = new BST();

        AVL avlPorData = new AVL();
        AVL avlPorMunicipio = new AVL();
        AVL avlPorNatureza = new AVL();
        AVL avlPorPorte = new AVL();
        AVL avlPorCnae = new AVL();

        // Inserção dos dados nas árvores
        for (int i = 0; i < registros.length; i++) {
            EmpresaRecord r = registros[i];
            bstPorData.insert(r.getPeriodo(), r);
            bstPorMunicipio.insert(r.getMunicipio(), r);
            bstPorNatureza.insert(r.getNaturezaJuridica(), r);
            bstPorPorte.insert(r.getPorte(), r);
            bstPorCnae.insert(r.getCnae(), r);

            avlPorData.insert(r.getPeriodo(), r);
            avlPorMunicipio.insert(r.getMunicipio(), r);
            avlPorNatureza.insert(r.getNaturezaJuridica(), r);
            avlPorPorte.insert(r.getPorte(), r);
            avlPorCnae.insert(r.getCnae(), r);
        }

        // 1. Análise Temporal
        System.out.println("1. ANÁLISE TEMPORAL - CRESCIMENTO DE CONSTITUIÇÕES");
        System.out.println("------------------------------------------------------");
        medirDesempenho("BST", () -> analisarCrescimentoTemporal(bstPorData));
        medirDesempenho("AVL", () -> analisarCrescimentoTemporal(avlPorData));


        // 2. Natureza Jurídica
        System.out.println("\n2. DIVERSIDADE EMPRESARIAL POR NATUREZA JURÍDICA");
        System.out.println("------------------------------------------------");
        medirDesempenho("BST", () -> analisarNaturezaJuridica(bstPorNatureza));
        medirDesempenho("AVL", () -> analisarNaturezaJuridica(avlPorNatureza));

        // 3. Porte Empresarial
        System.out.println("\n3. DISTRIBUIÇÃO POR PORTE EMPRESARIAL");
        System.out.println("------------------------------------");
        medirDesempenho("BST", () -> analisarPorteEmpresarial(bstPorPorte));
        medirDesempenho("AVL", () -> analisarPorteEmpresarial(avlPorPorte));

        // 4. Distribuição Geográfica
        System.out.println("\n4. DISTRIBUIÇÃO GEOGRÁFICA");
        System.out.println("--------------------------");
        medirDesempenho("BST", () -> analisarDistribuicaoGeografica(bstPorMunicipio));
        medirDesempenho("AVL", () -> analisarDistribuicaoGeografica(avlPorMunicipio));

        // 5. Atividades Econômicas (CNAE)
        System.out.println("\n5. ANÁLISE SETORIAL - ATIVIDADES ECONÔMICAS");
        System.out.println("-------------------------------------------");
        medirDesempenho("BST", () -> analisarAtividadesEconomicas(bstPorCnae));
        medirDesempenho("AVL", () -> analisarAtividadesEconomicas(avlPorCnae));


                // 6. Indicadores ODS 8
        System.out.println("\n6. INDICADORES RELACIONADOS À ODS 8");
        System.out.println("-----------------------------------");
        medirDesempenho("BST", () -> calcularIndicadoresODS8(bstPorCnae, bstPorPorte, bstPorMunicipio));
        medirDesempenho("AVL", () -> calcularIndicadoresODS8(avlPorCnae, avlPorPorte, avlPorMunicipio));

        // Teste de busca nas árvores
        System.out.println("\n=== TESTES DE BUSCA NAS ESTRUTURAS DE DADOS ===");
        LocalDate dataBusca = LocalDate.of(2025, 1, 2);
        EmpresaRecord resultadoBST = bstPorData.search(dataBusca);
        EmpresaRecord resultadoAVL = avlPorData.search(dataBusca);
        System.out.println("Busca por data " + dataBusca + " (BST): " + (resultadoBST != null ? resultadoBST : "Nenhum registro"));
        System.out.println("Busca por data " + dataBusca + " (AVL): " + (resultadoAVL != null ? resultadoAVL : "Nenhum registro"));

        String municipioBusca = "SÃO PAULO";
        EmpresaRecord resultadoMunicipioBST = bstPorMunicipio.search(municipioBusca);
        EmpresaRecord resultadoMunicipioAVL = avlPorMunicipio.search(municipioBusca);
        System.out.println("Busca por município " + municipioBusca + " (BST): " + (resultadoMunicipioBST != null ? resultadoMunicipioBST : "Nenhum registro"));
        System.out.println("Busca por município " + municipioBusca + " (AVL): " + (resultadoMunicipioAVL != null ? resultadoMunicipioAVL : "Nenhum registro"));

        // Demonstração da eficiência das estruturas
        System.out.println("\n=== INFORMAÇÕES DAS ESTRUTURAS DE DADOS ===");
        System.out.println("AVL por Natureza: Nós = " + avlPorNatureza.countNodes() + ", Altura = " + avlPorNatureza.getTreeHeight() + ", Balanceada: " + avlPorNatureza.isBalanced());
        System.out.println("BST por Natureza: Nós = " + bstPorNatureza.countNodes() + ", Altura = " + bstPorNatureza.getTreeHeight());
        System.out.println("AVL por Porte: Nós = " + avlPorPorte.countNodes() + ", Altura = " + avlPorPorte.getTreeHeight());
        System.out.println("BST por Porte: Nós = " + bstPorPorte.countNodes() + ", Altura = " + bstPorPorte.getTreeHeight());
    }

    // Função para ler CSV e retornar array fixo
    public static EmpresaRecord[] lerCSV(String caminho) {
        EmpresaRecord[] temp = new EmpresaRecord[10000]; // ajuste conforme necessário
        int count = 0;
        try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(caminho), "ISO-8859-1"))) {
            String linha = br.readLine(); // cabeçalho
            while ((linha = br.readLine()) != null) {
                linha = linha.trim();
                if (linha.isEmpty()) continue;
                try {
                    String[] campos = linha.split(";", -1);
                    if (campos.length >= 9) {
                        EmpresaRecord er = new EmpresaRecord(campos);
                        if (count == temp.length) {
                            EmpresaRecord[] novo = new EmpresaRecord[temp.length * 2];
                            for (int i = 0; i < temp.length; i++) novo[i] = temp[i];
                            temp = novo;
                        }
                        temp[count++] = er;
                    }
                } catch (Exception e) {
                    // Ignora linhas inválidas
                }
            }
        } catch (IOException e) {
            System.err.println("Erro ao ler arquivo: " + e.getMessage());
        }
        EmpresaRecord[] resultado = new EmpresaRecord[count];
        for (int i = 0; i < count; i++) resultado[i] = temp[i];
        return resultado;
    }

    // Funções de análise para ambas as árvores
    private static void analisarCrescimentoTemporal(Object arvore) {
        System.out.println("Constituições por data:");
        if (arvore instanceof BST) {
            ((BST)arvore).inOrderTraversal((data, lista) -> printTotalPorChave(data, lista));
        } else if (arvore instanceof AVL) {
            ((AVL)arvore).inOrderTraversal((data, lista) -> printTotalPorChave(data, lista));
        }
    }

    private static void analisarNaturezaJuridica(Object arvore) {
        System.out.println("Distribuição por natureza jurídica:");
        int totalEmpresas = 0;
        class NaturezaCount {
            String natureza;
            int total;
        }
        NaturezaCount[] naturezas = new NaturezaCount[100];
        int[] nCount = {0};

        if (arvore instanceof BST) {
            ((BST)arvore).inOrderTraversal((natureza, lista) -> {
                int total = 0;
                EmpresaRecord atual = lista;
                while (atual != null) {
                    total += atual.getEmpresas();
                    atual = atual.next;
                }
                NaturezaCount nc = new NaturezaCount();
                nc.natureza = (String) natureza;
                nc.total = total;
                naturezas[nCount[0]++] = nc;
            });
        } else if (arvore instanceof AVL) {
            ((AVL)arvore).inOrderTraversal((natureza, lista) -> {
                int total = 0;
                EmpresaRecord atual = lista;
                while (atual != null) {
                    total += atual.getEmpresas();
                    atual = atual.next;
                }
                NaturezaCount nc = new NaturezaCount();
                nc.natureza = (String) natureza;
                nc.total = total;
                naturezas[nCount[0]++] = nc;
            });
        }

        for (int i = 0; i < nCount[0]; i++) totalEmpresas += naturezas[i].total;
        for (int i = 0; i < nCount[0]; i++) {
            double percentual = (naturezas[i].total * 100.0) / (totalEmpresas == 0 ? 1 : totalEmpresas);
            System.out.printf("  %s: %d empresas (%.1f%%)\n", naturezas[i].natureza, naturezas[i].total, percentual);
        }
    }

    private static void analisarPorteEmpresarial(Object arvore) {
        System.out.println("Distribuição por porte empresarial:");
        int totalEmpresas = 0;
        class PorteCount {
            String porte;
            int total;
        }
        PorteCount[] portes = new PorteCount[20];
        int[] pCount = {0};

        if (arvore instanceof BST) {
            ((BST)arvore).inOrderTraversal((porte, lista) -> {
                int total = 0;
                EmpresaRecord atual = lista;
                while (atual != null) {
                    total += atual.getEmpresas();
                    atual = atual.next;
                }
                PorteCount pc = new PorteCount();
                pc.porte = (String) porte;
                pc.total = total;
                portes[pCount[0]++] = pc;
            });
        } else if (arvore instanceof AVL) {
            ((AVL)arvore).inOrderTraversal((porte, lista) -> {
                int total = 0;
                EmpresaRecord atual = lista;
                while (atual != null) {
                    total += atual.getEmpresas();
                    atual = atual.next;
                }
                PorteCount pc = new PorteCount();
                pc.porte = (String) porte;
                pc.total = total;
                portes[pCount[0]++] = pc;
            });
        }

        for (int i = 0; i < pCount[0]; i++) totalEmpresas += portes[i].total;
        for (int i = 0; i < pCount[0]; i++) {
            double percentual = (portes[i].total * 100.0) / (totalEmpresas == 0 ? 1 : totalEmpresas);
            System.out.printf("  %s: %d empresas (%.1f%%)\n", portes[i].porte, portes[i].total, percentual);
        }
    }

    private static void analisarDistribuicaoGeografica(Object arvore) {
        System.out.println("Municípios com constituições:");
        class MunicipioCount {
            String municipio;
            int total;
        }
        MunicipioCount[] municipios = new MunicipioCount[1000];
        int[] mCount = {0};

        if (arvore instanceof BST) {
            ((BST)arvore).inOrderTraversal((municipio, lista) -> {
                int total = 0;
                EmpresaRecord atual = lista;
                while (atual != null) {
                    total += atual.getEmpresas();
                    atual = atual.next;
                }
                MunicipioCount mc = new MunicipioCount();
                mc.municipio = (String) municipio;
                mc.total = total;
                municipios[mCount[0]++] = mc;
            });
        } else if (arvore instanceof AVL) {
            ((AVL)arvore).inOrderTraversal((municipio, lista) -> {
                int total = 0;
                EmpresaRecord atual = lista;
                while (atual != null) {
                    total += atual.getEmpresas();
                    atual = atual.next;
                }
                MunicipioCount mc = new MunicipioCount();
                mc.municipio = (String) municipio;
                mc.total = total;
                municipios[mCount[0]++] = mc;
            });
        }

        // Ordena top 5 (bubble sort simples)
        for (int i = 0; i < mCount[0] - 1; i++) {
            for (int j = i + 1; j < mCount[0]; j++) {
                if (municipios[j].total > municipios[i].total) {
                    MunicipioCount tmp = municipios[i];
                    municipios[i] = municipios[j];
                    municipios[j] = tmp;
                }
            }
        }

        System.out.println("Top 5 municípios com mais constituições:");
        int limite = mCount[0] < 5 ? mCount[0] : 5;
        for (int i = 0; i < limite; i++) {
            System.out.printf("  %s: %d empresas\n", municipios[i].municipio, municipios[i].total);
        }
    }

    private static void analisarAtividadesEconomicas(Object arvore) {
        System.out.println("Setores econômicos mais ativos:");
        class CNAECount {
            String cnae;
            int total;
            String descricao;
        }
        CNAECount[] top5 = new CNAECount[5];

        if (arvore instanceof BST) {
            ((BST)arvore).inOrderTraversal((cnae, lista) -> {
                int total = 0;
                String descricao = "";
                EmpresaRecord atual = lista;
                while (atual != null) {
                    total += atual.getEmpresas();
                    descricao = atual.getDescCnae();
                    atual = atual.next;
                }
                for (int i = 0; i < 5; i++) {
                    if (top5[i] == null || total > top5[i].total) {
                        for (int j = 4; j > i; j--) top5[j] = top5[j-1];
                        top5[i] = new CNAECount();
                        top5[i].cnae = (String) cnae;
                        top5[i].total = total;
                        top5[i].descricao = descricao;
                        break;
                    }
                }
            });
        } else if (arvore instanceof AVL) {
            ((AVL)arvore).inOrderTraversal((cnae, lista) -> {
                int total = 0;
                String descricao = "";
                EmpresaRecord atual = lista;
                while (atual != null) {
                    total += atual.getEmpresas();
                    descricao = atual.getDescCnae();
                    atual = atual.next;
                }
                for (int i = 0; i < 5; i++) {
                    if (top5[i] == null || total > top5[i].total) {
                        for (int j = 4; j > i; j--) top5[j] = top5[j-1];
                        top5[i] = new CNAECount();
                        top5[i].cnae = (String) cnae;
                        top5[i].total = total;
                        top5[i].descricao = descricao;
                        break;
                    }
                }
            });
        }

        System.out.println("Top 5 CNAEs mais frequentes:");
        for (int i = 0; i < 5; i++) {
            if (top5[i] != null) {
                System.out.printf("  CNAE %s: %d empresas - %s\n",
                    top5[i].cnae, top5[i].total, top5[i].descricao);
            }
        }
    }

    private static void calcularIndicadoresODS8(Object arvoreCnae, Object arvorePorte, Object arvoreMunicipio) {
        // Diversidade de setores (número de CNAEs diferentes)
        final int[] cnaeCount = {0};
        if (arvoreCnae instanceof BST) {
            ((BST)arvoreCnae).inOrderTraversal((cnae, lista) -> cnaeCount[0]++);
        } else if (arvoreCnae instanceof AVL) {
            ((AVL)arvoreCnae).inOrderTraversal((cnae, lista) -> cnaeCount[0]++);
        }

        // Participação de micro e pequenas empresas
        final int[] totalEmpresas = {0};
        final int[] microPequenas = {0};
        if (arvorePorte instanceof BST) {
            ((BST)arvorePorte).inOrderTraversal((porte, lista) -> {
                EmpresaRecord atual = lista;
                while (atual != null) {
                    totalEmpresas[0] += atual.getEmpresas();
                    String p = atual.getPorte().toLowerCase();
                    if (p.contains("micro") || p.contains("pequen")) {
                        microPequenas[0] += atual.getEmpresas();
                    }
                    atual = atual.next;
                }
            });
        } else if (arvorePorte instanceof AVL) {
            ((AVL)arvorePorte).inOrderTraversal((porte, lista) -> {
                EmpresaRecord atual = lista;
                while (atual != null) {
                    totalEmpresas[0] += atual.getEmpresas();
                    String p = atual.getPorte().toLowerCase();
                    if (p.contains("micro") || p.contains("pequen")) {
                        microPequenas[0] += atual.getEmpresas();
                    }
                    atual = atual.next;
                }
            });
        }
        double percentualMPE = (microPequenas[0] * 100.0) / (totalEmpresas[0] == 0 ? 1 : totalEmpresas[0]);

        // Descentralização geográfica (número de municípios diferentes)
        final int[] municipioCount = {0};
        if (arvoreMunicipio instanceof BST) {
            ((BST)arvoreMunicipio).inOrderTraversal((municipio, lista) -> municipioCount[0]++);
        } else if (arvoreMunicipio instanceof AVL) {
            ((AVL)arvoreMunicipio).inOrderTraversal((municipio, lista) -> municipioCount[0]++);
        }

        System.out.println("Indicadores ODS 8 - Trabalho Decente e Crescimento Econômico:");
        System.out.println("  • Diversidade setorial: " + cnaeCount[0] + " setores diferentes");
        System.out.printf("  • Participação de MPEs: %.1f%% (%d de %d empresas)\n", percentualMPE, microPequenas[0], totalEmpresas[0]);
        System.out.println("  • Descentralização geográfica: " + municipioCount[0] + " municípios diferentes");
        System.out.println("  • Taxa de empreendedorismo: " + totalEmpresas[0] + " novas empresas constituídas");
    }

    private static void printTotalPorChave(Object chave, EmpresaRecord lista) {
        int total = 0;
        EmpresaRecord atual = lista;
        while (atual != null) {
            total += atual.getEmpresas();
            atual = atual.next;
        }
        System.out.println("  " + chave + ": " + total + " empresas");
    }
    private static void medirDesempenho(String nome, Runnable func) {
        long ini = System.nanoTime();
        func.run();
        long fim = System.nanoTime();
        System.out.printf("Tempo %s: %.2f ms\n", nome, (fim - ini) / 1_000_000.0);
    }
}