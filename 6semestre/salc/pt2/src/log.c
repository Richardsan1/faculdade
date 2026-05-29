/*
 * log.c – Implementação do módulo de log do compilador SAL
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "log.h"
#include "lex.h"
#include "symtab.h"

/* Arquivos de log internos */
static FILE *g_tk  = NULL; /* .tk  – tokens          */
static FILE *g_ts  = NULL; /* .ts  – tabela de símbolos */
static FILE *g_trc = NULL; /* .trc – trace           */

/* Constrói o nome do arquivo de saída substituindo a extensão */
static void make_path(char *out, size_t outsz,
                      const char *base, const char *ext) {
    snprintf(out, outsz, "%s.%s", base, ext);
}

/* Remove a extensão de um caminho de arquivo, retorna nome base */
static void strip_extension(char *out, size_t outsz, const char *path) {
    strncpy(out, path, outsz - 1);
    out[outsz - 1] = '\0';
    char *dot = strrchr(out, '.');
    if (dot) *dot = '\0';
}

int log_init(const char *source_path, int do_tokens, int do_symtab, int do_trace) {
    char base[512];
    char fpath[520];
    strip_extension(base, sizeof(base), source_path);

    if (do_tokens) {
        make_path(fpath, sizeof(fpath), base, "tk");
        g_tk = fopen(fpath, "w");
        if (!g_tk) { perror(fpath); return -1; }
    }
    if (do_symtab) {
        make_path(fpath, sizeof(fpath), base, "ts");
        g_ts = fopen(fpath, "w");
        if (!g_ts) { perror(fpath); return -1; }
    }
    if (do_trace) {
        make_path(fpath, sizeof(fpath), base, "trc");
        g_trc = fopen(fpath, "w");
        if (!g_trc) { perror(fpath); return -1; }
    }
    return 0;
}

void log_token(const Token *tok) {
    if (!g_tk) return;
    /*
     * Formato: <L>  <CAT>  "<LEX>"
     * A coluna de linha tem largura fixa de 5 para alinhamento.
     */
    fprintf(g_tk, "%5d  %-15s  \"%s\"\n",
            tok->line,
            lex_kind_name(tok->kind),
            tok->lexeme);
}

void log_symtab(void) {
    if (!g_ts) return;
    ts_dump(g_ts);
}

FILE *log_trace_file(void) {
    return g_trc;
}

void log_close(void) {
    if (g_tk)  { fclose(g_tk);  g_tk  = NULL; }
    if (g_ts)  { fclose(g_ts);  g_ts  = NULL; }
    if (g_trc) { fclose(g_trc); g_trc = NULL; }
}
