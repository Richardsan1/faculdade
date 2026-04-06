/*
 * symtab.c – Implementação da Tabela de Símbolos do compilador SAL
 *
 * Usa uma pilha de escopos (ScopeFrame). Cada frame possui uma lista
 * encadeada dos símbolos declarados naquele escopo.
 * A busca percorre a pilha do topo até a base (do mais interno ao global).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"
#include "diag.h"

/* ------------------------------------------------------------------ */
/* Estrutura de um frame de escopo                                       */
/* ------------------------------------------------------------------ */
#define MAX_SCOPE_DEPTH 64

typedef struct ScopeFrame {
    char    name[MAX_SCOPE];  /* nome descritivo deste escopo        */
    Symbol *head;             /* lista de símbolos (ordem de inserção)*/
    Symbol *tail;             /* ponteiro para o último (inserção rápida) */
    int     block_count;      /* contador de sub-blocos start..end   */
} ScopeFrame;

/* Pilha de escopos */
static ScopeFrame g_stack[MAX_SCOPE_DEPTH];
static int        g_top = -1; /* índice do topo (-1 = vazia)        */

/* Lista de todos os frames já encerrados (para o dump ordenado) */
typedef struct ClosedFrame {
    char    name[MAX_SCOPE];
    Symbol *head;
    struct ClosedFrame *next;
} ClosedFrame;

static ClosedFrame *g_closed_head = NULL;
static ClosedFrame *g_closed_tail = NULL;

/* ------------------------------------------------------------------ */
/* Funções auxiliares                                                    */
/* ------------------------------------------------------------------ */

/* Constrói o caminho completo do escopo corrente (ex: fn:SOMA.locals) */
static void build_scope_path(char *buf, size_t bufsz) {
    buf[0] = '\0';
    for (int i = 0; i <= g_top; i++) {
        if (i > 0) strncat(buf, ".", bufsz - strlen(buf) - 1);
        strncat(buf, g_stack[i].name, bufsz - strlen(buf) - 1);
    }
}

/* ------------------------------------------------------------------ */
/* Interface pública                                                     */
/* ------------------------------------------------------------------ */

void ts_init(void) {
    g_top = -1;
    g_closed_head = NULL;
    g_closed_tail = NULL;
}

void ts_push_scope(const char *name) {
    if (g_top + 1 >= MAX_SCOPE_DEPTH) {
        fprintf(stderr, "[INTERNO] profundidade maxima de escopos atingida.\n");
        exit(EXIT_FAILURE);
    }
    g_top++;
    strncpy(g_stack[g_top].name, name, MAX_SCOPE - 1);
    g_stack[g_top].name[MAX_SCOPE - 1] = '\0';
    g_stack[g_top].head        = NULL;
    g_stack[g_top].tail        = NULL;
    g_stack[g_top].block_count = 0;
}

void ts_pop_scope(void) {
    if (g_top < 0) {
        fprintf(stderr, "[INTERNO] pop em pilha vazia de escopos.\n");
        exit(EXIT_FAILURE);
    }

    /* Guarda o frame fechado para o dump posterior */
    ClosedFrame *cf = (ClosedFrame *)malloc(sizeof(ClosedFrame));
    if (!cf) { perror("malloc"); exit(EXIT_FAILURE); }
    strncpy(cf->name, g_stack[g_top].name, MAX_SCOPE - 1);

    /* Constrói o caminho completo antes de desempilhar */
    char path[MAX_SCOPE * MAX_SCOPE_DEPTH];
    build_scope_path(path, sizeof(path));
    strncpy(cf->name, path, MAX_SCOPE - 1);
    cf->name[MAX_SCOPE - 1] = '\0';

    cf->head = g_stack[g_top].head;
    cf->next = NULL;

    if (!g_closed_tail) {
        g_closed_head = g_closed_tail = cf;
    } else {
        g_closed_tail->next = cf;
        g_closed_tail = cf;
    }

    g_top--;
}

const char *ts_current_scope_name(void) {
    static char buf[MAX_SCOPE * MAX_SCOPE_DEPTH];
    if (g_top < 0) return "(nenhum)";
    build_scope_path(buf, sizeof(buf));
    return buf;
}

Symbol *ts_insert(const char *name, SymCat cat, SymType type, int extra, int line) {
    if (g_top < 0) {
        fprintf(stderr, "[INTERNO] ts_insert sem escopo ativo.\n");
        exit(EXIT_FAILURE);
    }

    /* Verifica redeclaração no escopo corrente */
    if (ts_lookup_current(name)) {
        char msg[MAX_IDENT + 64];
        snprintf(msg, sizeof(msg),
                 "identificador '%s' ja declarado neste escopo", name);
        diag_error(line, "(unico)", msg);
    }

    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym) { perror("malloc"); exit(EXIT_FAILURE); }

    strncpy(sym->name,  name,  MAX_IDENT - 1); sym->name[MAX_IDENT - 1]   = '\0';
    sym->cat   = cat;
    sym->type  = type;
    sym->extra = extra;
    sym->next  = NULL;

    /* Armazena o caminho completo do escopo no símbolo */
    build_scope_path(sym->scope, MAX_SCOPE);

    /* Insere no final da lista (preserva ordem de declaração) */
    if (!g_stack[g_top].tail) {
        g_stack[g_top].head = g_stack[g_top].tail = sym;
    } else {
        g_stack[g_top].tail->next = sym;
        g_stack[g_top].tail = sym;
    }

    return sym;
}

Symbol *ts_lookup(const char *name) {
    /* Percorre da camada mais interna (topo) até a global (base) */
    for (int i = g_top; i >= 0; i--) {
        for (Symbol *s = g_stack[i].head; s; s = s->next) {
            if (strcmp(s->name, name) == 0) return s;
        }
    }
    return NULL;
}

Symbol *ts_lookup_current(const char *name) {
    if (g_top < 0) return NULL;
    for (Symbol *s = g_stack[g_top].head; s; s = s->next) {
        if (strcmp(s->name, name) == 0) return s;
    }
    return NULL;
}

void ts_dump(FILE *out) {
    /* Percorre os frames fechados na ordem em que foram encerrados */
    for (ClosedFrame *cf = g_closed_head; cf; cf = cf->next) {
        for (Symbol *s = cf->head; s; s = s->next) {
            fprintf(out,
                    "SCOPE=%-40s  id=\"%s\"  cat=%s  tipo=%s  extra=%d\n",
                    cf->name,
                    s->name,
                    ts_cat_name(s->cat),
                    ts_type_name(s->type),
                    s->extra);
        }
    }
}

void ts_free(void) {
    /* Libera frames ainda na pilha */
    for (int i = 0; i <= g_top; i++) {
        Symbol *s = g_stack[i].head;
        while (s) { Symbol *nx = s->next; free(s); s = nx; }
        g_stack[i].head = g_stack[i].tail = NULL;
    }
    g_top = -1;

    /* Libera frames fechados */
    ClosedFrame *cf = g_closed_head;
    while (cf) {
        Symbol *s = cf->head;
        while (s) { Symbol *nx = s->next; free(s); s = nx; }
        ClosedFrame *nx = cf->next;
        free(cf);
        cf = nx;
    }
    g_closed_head = g_closed_tail = NULL;
}

const char *ts_cat_name(SymCat cat) {
    switch (cat) {
        case CAT_VAR:   return "var";
        case CAT_VETOR: return "vetor";
        case CAT_PARAM: return "param";
        case CAT_PROC:  return "proc";
        case CAT_FN:    return "fn";
        default:        return "?";
    }
}

const char *ts_type_name(SymType type) {
    switch (type) {
        case TIP_INT:    return "int";
        case TIP_BOOL:   return "bool";
        case TIP_CHAR:   return "char";
        case TIP_NENHUM: return "-";
        default:         return "?";
    }
}
