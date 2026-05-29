/*
 * opt.c – Implementação do módulo de opções de execução (CLI)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "opt.h"

/* Instância global das opções (acessível apenas via opts_get) */
static Options g_opts;

/* Exibe mensagem de uso e encerra */
static void usage(const char *prog) {
    fprintf(stderr, "Uso: %s <arquivo.sal> [--tokens] [--symtab] [--trace]\n", prog);
    fprintf(stderr, "  --tokens  Gera lista de tokens (.tk)\n");
    fprintf(stderr, "  --symtab  Gera tabela de simbolos (.ts)\n");
    fprintf(stderr, "  --trace   Gera rastreamento da analise (.trc)\n");
    exit(EXIT_FAILURE);
}

void opts_parse(int argc, char *argv[]) {
    /* Inicializa todas as opções com valores padrão */
    memset(&g_opts, 0, sizeof(g_opts));

    if (argc < 2) {
        usage(argv[0]);
    }

    /* Primeiro argumento não iniciado com '--' é o arquivo fonte */
    if (argv[1][0] == '-') {
        fprintf(stderr, "Erro: o primeiro argumento deve ser o arquivo fonte.\n");
        usage(argv[0]);
    }
    g_opts.source_file = argv[1];

    /* Processa flags opcionais */
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--tokens") == 0) {
            g_opts.emit_tokens = 1;
        } else if (strcmp(argv[i], "--symtab") == 0) {
            g_opts.emit_symtab = 1;
        } else if (strcmp(argv[i], "--trace") == 0) {
            g_opts.emit_trace = 1;
        } else {
            fprintf(stderr, "Opcao desconhecida: %s\n", argv[i]);
            usage(argv[0]);
        }
    }
}

const Options *opts_get(void) {
    return &g_opts;
}
