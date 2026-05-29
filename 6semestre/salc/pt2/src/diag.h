#ifndef DIAG_H
#define DIAG_H

/*
 * diag.h – Módulo de diagnósticos e relatórios do compilador SAL
 *
 * Centraliza todas as mensagens de erro e rastreamento,
 * evitando que lex e parser imprimam diretamente.
 */

#include <stdio.h>

/*
 * diag_init – inicializa o módulo de diagnóstico.
 * @trace_file: ponteiro para arquivo de trace (pode ser NULL).
 */
void diag_init(FILE *trace_file);

/*
 * diag_error – reporta um erro fatal e encerra a execução.
 * @line    : linha do arquivo fonte onde ocorreu o erro.
 * @expected: descrição do token/construção esperada.
 * @found   : descrição do token encontrado.
 */
void diag_error(int line, const char *expected, const char *found);

/*
 * diag_error_lex – reporta erro léxico e encerra a execução.
 * @line : linha do arquivo fonte.
 * @msg  : descrição do erro.
 */
void diag_error_lex(int line, const char *msg);

/*
 * diag_info – registra mensagem informativa de rastreamento.
 * Só tem efeito se o arquivo de trace estiver configurado.
 * @fmt: formato printf-like.
 */
void diag_info(const char *fmt, ...);

/*
 * diag_close – finaliza o módulo (fecha arquivo de trace, se houver).
 */
void diag_close(void);

#endif /* DIAG_H */
