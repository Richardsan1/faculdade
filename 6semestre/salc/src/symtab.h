#ifndef SYMTAB_H
#define SYMTAB_H

/*
 * symtab.h – Módulo da Tabela de Símbolos (TS) do compilador SAL
 *
 * Gerencia escopos, inserção e busca de identificadores.
 * Espelha a estrutura de blocos da SAL:
 *   - global       → seção globals do módulo
 *   - fn/proc      → escopos de sub-rotinas
 *   - locals       → variáveis locais dentro de sub-rotina
 *   - block#N      → blocos aninhados start...end
 */

#include <stdio.h>

/* ------------------------------------------------------------------ */
/* Tipos e categorias de símbolos                                       */
/* ------------------------------------------------------------------ */

typedef enum {
    CAT_VAR,       /* variável simples                               */
    CAT_VETOR,     /* variável composta (vetor)                      */
    CAT_PARAM,     /* parâmetro formal de sub-rotina                 */
    CAT_PROC,      /* procedimento (não retorna valor)               */
    CAT_FN         /* função (retorna valor)                         */
} SymCat;

typedef enum {
    TIP_INT,
    TIP_BOOL,
    TIP_CHAR,
    TIP_NENHUM     /* para procedimentos                             */
} SymType;

/* ------------------------------------------------------------------ */
/* Registro de símbolo                                                  */
/* ------------------------------------------------------------------ */
#define MAX_IDENT 256
#define MAX_SCOPE 256

typedef struct Symbol {
    char         name[MAX_IDENT]; /* lexema do identificador          */
    SymCat       cat;             /* categoria                        */
    SymType      type;            /* tipo de dado                     */
    int          extra;           /* tamanho (vetor) | nparams (fn/proc) */
    char         scope[MAX_SCOPE];/* caminho de escopo (ex: global)   */
    struct Symbol *next;          /* lista encadeada no mesmo escopo  */
} Symbol;

/* ------------------------------------------------------------------ */
/* Interface pública                                                     */
/* ------------------------------------------------------------------ */

/*
 * ts_init – inicializa a tabela de símbolos.
 */
void ts_init(void);

/*
 * ts_push_scope – cria um novo escopo com o nome dado.
 * @name: nome descritivo do escopo (ex: "global", "fn:SOMA", "block#1")
 */
void ts_push_scope(const char *name);

/*
 * ts_pop_scope – encerra o escopo corrente.
 */
void ts_pop_scope(void);

/*
 * ts_current_scope_name – retorna o caminho completo do escopo atual.
 */
const char *ts_current_scope_name(void);

/*
 * ts_insert – insere um identificador no escopo corrente.
 * Retorna ponteiro para o símbolo inserido.
 * Em caso de declaração duplicada no mesmo escopo, reporta erro via diag.
 */
Symbol *ts_insert(const char *name, SymCat cat, SymType type, int extra, int line);

/*
 * ts_lookup – busca um identificador a partir do escopo atual,
 * percorrendo escopos externos até encontrar ou retornar NULL.
 */
Symbol *ts_lookup(const char *name);

/*
 * ts_lookup_current – busca apenas no escopo corrente.
 * Útil para detectar redeclarações.
 */
Symbol *ts_lookup_current(const char *name);

/*
 * ts_dump – escreve o conteúdo consolidado da TS no arquivo dado.
 * Formato: SCOPE=<descr>  id="<lex>"  cat=<cat>  tipo=<tipo>  extra=<val>
 */
void ts_dump(FILE *out);

/*
 * ts_free – libera toda a memória alocada pela tabela.
 */
void ts_free(void);

/* Conversores de enum para string (para dump e diagnóstico) */
const char *ts_cat_name(SymCat cat);
const char *ts_type_name(SymType type);

#endif /* SYMTAB_H */
