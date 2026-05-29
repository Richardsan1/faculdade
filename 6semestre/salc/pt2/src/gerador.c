/*
 * gerador.c - Gerador de codigo MEPA para o compilador SALc
 *
 * Emite instrucoes MEPA formatadas para o arquivo .mepa.
 * Gerencia rotulos unicos para desvios condicionais e loops.
 *
 * Formato das instrucoes (requisito do interpretador):
 *   ROTULO: MNEM [P1[,P2]]
 * Sem espaco entre P1 e P2 quando ha dois parametros.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerador.h"

static FILE *g_out       = NULL;
static int   g_label_cnt = 0;

/* Constroi nome .mepa a partir do caminho do fonte */
static void make_mepa_path(char *out, size_t sz, const char *src) {
    strncpy(out, src, sz - 1);
    out[sz - 1] = '\0';
    char *dot = strrchr(out, '.');
    if (dot) *dot = '\0';
    strncat(out, ".mepa", sz - strlen(out) - 1);
}

int gen_init(const char *source_path) {
    char path[512];
    make_mepa_path(path, sizeof(path), source_path);
    g_out = fopen(path, "w");
    g_label_cnt = 0;
    return (g_out != NULL) ? 0 : -1;
}

void gen_close(void) {
    if (g_out) { fclose(g_out); g_out = NULL; }
}

/*
 * gen – emite uma instrucao MEPA.
 *
 * Formato de saida:
 *   [ROTULO:] <TAB> MNEM [P1[,P2]]
 *
 * Exemplos:
 *   gen(NULL,  "INPP", NULL, NULL) ->       INPP
 *   gen("L1",  "NADA", NULL, NULL) -> L1:   NADA
 *   gen(NULL,  "AMEM", "3",  NULL) ->       AMEM 3
 *   gen(NULL,  "ARMZ", "0",  "2" ) ->       ARMZ 0,2
 */
void gen(const char *rotulo, const char *mnem,
         const char *p1,     const char *p2) {
    if (!g_out) return;

    if (rotulo && rotulo[0] != '\0') {
        fprintf(g_out, "%s:", rotulo);
    } else {
        fprintf(g_out, "       ");
    }

    fprintf(g_out, " %s", mnem);

    if (p1 && p1[0] != '\0') {
        fprintf(g_out, " %s", p1);
        if (p2 && p2[0] != '\0') {
            /* SEM espaco: requisito do interpretador MEPA */
            fprintf(g_out, ",%s", p2);
        }
    }

    fputc('\n', g_out);
}

const char *gen_novo_rotulo(void) {
    static char buf[16];
    snprintf(buf, sizeof(buf), "L%d", ++g_label_cnt);
    return buf;
}

const char *gen_itoa(int n) {
    /* Dois buffers alternados para permitir duas chamadas na mesma expressao */
    static char bufs[2][32];
    static int  idx = 0;
    idx = 1 - idx;
    snprintf(bufs[idx], sizeof(bufs[idx]), "%d", n);
    return bufs[idx];
}
