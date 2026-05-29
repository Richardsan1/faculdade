/*
 * main.c – Módulo de orquestração do compilador SALc
 *
 * Coordena a execução:
 *   1. Processa parâmetros de linha de comando (opt)
 *   2. Inicializa os módulos: log, diag, lex, symtab
 *   3. Aciona a análise via parser (parse_program)
 *   4. Gera artefatos opcionais (tabela de símbolos)
 *   5. Encerra todos os módulos de forma ordenada
 *
 * Não realiza análise léxica, sintática ou semântica diretamente.
 */

#include <stdio.h>
#include <stdlib.h>
#include "opt.h"
#include "log.h"
#include "diag.h"
#include "lex.h"
#include "symtab.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    /* 1. Processa argumentos da linha de comando */
    opts_parse(argc, argv);
    const Options *opts = opts_get();

    /* 2. Inicializa módulo de log (abre arquivos de saída opcionais) */
    if (log_init(opts->source_file,
                 opts->emit_tokens,
                 opts->emit_symtab,
                 opts->emit_trace) != 0) {
        fprintf(stderr, "Erro ao criar arquivos de log.\n");
        return EXIT_FAILURE;
    }

    /* 3. Inicializa módulo de diagnóstico com o arquivo de trace */
    diag_init(log_trace_file());

    /* 4. Inicializa o analisador léxico */
    if (lex_init(opts->source_file) != 0) {
        fprintf(stderr, "Erro: nao foi possivel abrir '%s'.\n", opts->source_file);
        log_close();
        return EXIT_FAILURE;
    }

    /* 5. Inicializa a tabela de símbolos */
    ts_init();

    /* 6. Executa a análise sintática (e léxica / construção da TS) */
    parse_program();

    /* 7. Gera o arquivo de tabela de símbolos (se habilitado) */
    if (opts->emit_symtab) {
        log_symtab();
    }

    /* 8. Encerramento ordenado */
    ts_free();
    lex_close();
    diag_close();
    log_close();

    printf("Analise concluida com sucesso.\n");
    return EXIT_SUCCESS;
}
