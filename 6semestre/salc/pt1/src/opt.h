#ifndef OPT_H
#define OPT_H

/*
 * opt.h – Módulo de opções de execução (CLI)
 * Interpreta os argumentos da linha de comando e disponibiliza
 * as opções para os demais módulos do compilador.
 */

/* Estrutura com todas as opções configuráveis via CLI */
typedef struct {
    const char *source_file; /* caminho do arquivo fonte .sal       */
    int         emit_tokens; /* --tokens: gera arquivo .tk          */
    int         emit_symtab; /* --symtab: gera arquivo .ts          */
    int         emit_trace;  /* --trace : gera arquivo .trc         */
} Options;

/*
 * opts_parse – processa argv/argc e preenche a estrutura de opções.
 * Encerra o processo com mensagem de uso em caso de argumento inválido.
 */
void opts_parse(int argc, char *argv[]);

/*
 * opts_get – retorna ponteiro para a estrutura de opções preenchida.
 * Deve ser chamada após opts_parse.
 */
const Options *opts_get(void);

#endif /* OPT_H */
