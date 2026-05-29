/*
 * diag.c – Implementação do módulo de diagnósticos do compilador SAL
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "diag.h"

/* Arquivo de trace (NULL = desabilitado) */
static FILE *g_trace = NULL;

void diag_init(FILE *trace_file) {
    g_trace = trace_file;
}

void diag_error(int line, const char *expected, const char *found) {
    fprintf(stderr,
            "[ERRO SINTATICO] linha %d: esperado '%s', encontrado '%s'.\n",
            line, expected, found);
    exit(EXIT_FAILURE);
}

void diag_error_lex(int line, const char *msg) {
    fprintf(stderr,
            "[ERRO LEXICO] linha %d: %s.\n",
            line, msg);
    exit(EXIT_FAILURE);
}

void diag_info(const char *fmt, ...) {
    if (!g_trace) return;
    va_list ap;
    va_start(ap, fmt);
    vfprintf(g_trace, fmt, ap);
    va_end(ap);
    fputc('\n', g_trace);
}

void diag_close(void) {
    /* O arquivo de trace é fechado pelo main, pois foi aberto lá */
    g_trace = NULL;
}
