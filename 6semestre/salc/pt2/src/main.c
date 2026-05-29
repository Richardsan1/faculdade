/*
 * main.c - Orquestrador do compilador SALc (Fase 1 + Fase 2)
 *
 * Inicializa todos os modulos, executa a analise (lexica, sintatica,
 * semantica) e a geracao de codigo MEPA, depois encerra ordenadamente.
 */

#include <stdio.h>
#include <stdlib.h>
#include "opt.h"
#include "log.h"
#include "diag.h"
#include "lex.h"
#include "symtab.h"
#include "parser.h"
#include "gerador.h"

int main(int argc, char *argv[]) {
    /* 1. Linha de comando */
    opts_parse(argc, argv);
    const Options *opts = opts_get();

    /* 2. Logs opcionais (.tk, .ts, .trc) */
    if (log_init(opts->source_file,
                 opts->emit_tokens,
                 opts->emit_symtab,
                 opts->emit_trace) != 0) {
        fprintf(stderr, "Erro ao criar arquivos de log.\n");
        return EXIT_FAILURE;
    }

    /* 3. Diagnostico com arquivo de trace */
    diag_init(log_trace_file());

    /* 4. Analisador lexico */
    if (lex_init(opts->source_file) != 0) {
        fprintf(stderr, "Erro: nao foi possivel abrir '%s'.\n", opts->source_file);
        log_close();
        return EXIT_FAILURE;
    }

    /* 5. Tabela de simbolos */
    ts_init();

    /* 6. Gerador de codigo MEPA */
    if (gen_init(opts->source_file) != 0) {
        fprintf(stderr, "Erro ao criar arquivo .mepa.\n");
        lex_close();
        log_close();
        return EXIT_FAILURE;
    }

    /* 7. Analise + semantica + geracao de codigo (tudo em uma passagem) */
    parse_program();

    /* 8. Tabela de simbolos para log */
    if (opts->emit_symtab) log_symtab();

    /* 9. Encerramento ordenado */
    gen_close();
    ts_free();
    lex_close();
    diag_close();
    log_close();

    printf("Compilacao concluida com sucesso.\n");
    return EXIT_SUCCESS;
}
