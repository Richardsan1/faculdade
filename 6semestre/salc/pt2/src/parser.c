/*
 * parser.c - ASDR da linguagem SAL: analise sintatica + semantica + geracao MEPA
 *
 * A traducao e dirigida pela sintaxe (SDT): a cada producao reconhecida,
 * acoes semanticas verificam tipos/escopos e acoes de geracao emitem MEPA.
 *
 * Restricoes para geracao de codigo (conforme Apendice B da especificacao):
 *   - Sem vetores (tratados semanticamente mas nao geram codigo)
 *   - Sem sub-rotinas (aceitas sintaticamente, sem emissao de codigo MEPA)
 *   - Geração completa apenas para o proc main e seus comandos
 *
 * Endereçamento MEPA: ARMZ nivel,deslocamento
 *   nivel 0 = global, nivel 1 = local (proc main)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lex.h"
#include "diag.h"
#include "symtab.h"
#include "log.h"
#include "gerador.h"

/* ------------------------------------------------------------------ */
/* Estado do parser                                                      */
/* ------------------------------------------------------------------ */
static Token g_cur;
static int   g_block_cnt  = 0;
static int   g_in_main    = 0;  /* 1 quando analisando proc main      */
static int   g_addr_global = 0; /* proximo endereco livre no global   */
static int   g_addr_local  = 0; /* proximo endereco livre no local    */
static int   g_nivel       = 0; /* nivel lexico corrente (0=global)   */
static int   g_emit_code   = 0; /* emite MEPA no bloco corrente       */
static int   g_decl_main   = 0; /* declaracoes de locals do main      */
static int   g_main_base   = 0; /* base dos locals do main (nivel 0)  */
static int   g_curr_nparams = 0;/* parametros da sub-rotina atual     */
static int   g_curr_is_fn   = 0;/* 1 se sub-rotina atual é função     */
static char  g_label_main[16];

/* ------------------------------------------------------------------ */
/* Consumo de tokens                                                     */
/* ------------------------------------------------------------------ */
static void advance(void) {
    g_cur = lex_next();
    log_token(&g_cur);
    if (g_cur.kind == sERRO) diag_error_lex(g_cur.line, g_cur.lexeme);
}
static void expect(TokenKind k) {
    if (g_cur.kind != k)
        diag_error(g_cur.line, lex_kind_name(k), lex_kind_name(g_cur.kind));
    advance();
}

/* ------------------------------------------------------------------ */
/* Declaracoes antecipadas                                               */
/* ------------------------------------------------------------------ */
static void    p_glob(void);
static void    p_decls(int nivel_decl);
static SymType p_tpo(void);
static int     p_subs(void);
static void    p_func(void);
static void    p_princ(void);
static int     p_param(void);
static void    p_bco(void);
static void    p_cmd(void);
static void    p_out(void);
static void    p_inp(void);
static void    p_if(void);
static void    p_fr(void);
static void    p_call_cmd(char *name);
static void    p_ret(void);
static SymType p_expr(void);
static SymType p_exlog(void);
static SymType p_exrel(void);
static SymType p_exari(void);
static SymType p_exarp(void);
static SymType p_fact(void);
static SymType p_elem(void);

/* ================================================================== */
/* ini ::= "sMODULE" id ";" glob? subs? princ                         */
/* ================================================================== */
void parse_program(void) {
    diag_info(">> parse_program");
    advance();
    expect(sMODULE);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (nome modulo)", lex_kind_name(g_cur.kind));
    diag_info("  modulo: %s", g_cur.lexeme);
    advance();
    expect(sPONTVIRG);

    /* Escopo global */
    ts_push_scope("global");
    g_nivel = 0;
    g_addr_global = 0;

    /* INPP: inicializa o programa */
    gen(NULL, "INPP", NULL, NULL);

    /* globals: declara variaveis globais e emite AMEM */
    int n_glob = 0;
    if (g_cur.kind == sGLOBALS) {
        p_glob();
        n_glob = g_addr_global;
    }
    if (n_glob > 0)
        gen(NULL, "AMEM", gen_itoa(n_glob), NULL);

    g_main_base = g_addr_global;
    strncpy(g_label_main, gen_novo_rotulo(), sizeof(g_label_main) - 1);
    g_label_main[sizeof(g_label_main) - 1] = '\0';
    gen(NULL, "DSVS", g_label_main, NULL);

    /* sub-rotinas (sem geracao de codigo MEPA nesta versao) */
    int main_handled = 0;
    if (g_cur.kind == sFN || g_cur.kind == sPROC)
        main_handled = p_subs();

    if (!main_handled) {
        if (g_cur.kind == sPROC) p_princ();
        else diag_error(g_cur.line,
                        "sPROC main (obrigatorio)",
                        lex_kind_name(g_cur.kind));
    }

    /* Desaloca globals e encerra */
    if (n_glob > 0)
        gen(NULL, "DMEM", gen_itoa(n_glob), NULL);
    gen(NULL, "PARA", NULL, NULL);

    ts_pop_scope();

    if (g_cur.kind != sEOF)
        diag_error(g_cur.line, "sEOF", lex_kind_name(g_cur.kind));
    diag_info("<< parse_program");
}

/* ================================================================== */
/* glob ::= "sGLOBALS" decls+                                          */
/* ================================================================== */
static void p_glob(void) {
    diag_info(">> glob");
    expect(sGLOBALS);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (declaracao global)", lex_kind_name(g_cur.kind));
    while (g_cur.kind == sIDENTIF)
        p_decls(0); /* nivel 0 = global */
    diag_info("<< glob");
}

/* ================================================================== */
/* decls ::= id ("," id)* ":" tpo ";"                                  */
/* Atribui enderecos sequenciais no nivel indicado.                    */
/* ================================================================== */
static void p_decls(int nivel_decl) {
    diag_info(">> decls");
#define MAX_DECL 64
    char names[MAX_DECL][MAX_LEXEME];
    int  sizes[MAX_DECL];
    int  count = 0;
    int  decl_line = g_cur.line;

    do {
        if (count > 0) advance(); /* consome ',' */
        if (g_cur.kind != sIDENTIF)
            diag_error(g_cur.line, "sIDENTIF", lex_kind_name(g_cur.kind));
        strncpy(names[count], g_cur.lexeme, MAX_LEXEME-1);
        names[count][MAX_LEXEME-1] = '\0';
        sizes[count] = 0;
        advance();
        if (g_cur.kind == sABRECOL) { /* vetor — suporte sintatico */
            advance();
            if (g_cur.kind != sCTEINT)
                diag_error(g_cur.line, "sCTEINT (tamanho)", lex_kind_name(g_cur.kind));
            sizes[count] = atoi(g_cur.lexeme);
            advance();
            expect(sFECHACOL);
        }
        count++;
        if (count >= MAX_DECL) break;
    } while (g_cur.kind == sVIRGULA);

    expect(sDOIS_PONT);
    SymType tipo = p_tpo();
    expect(sPONTVIRG);

    for (int i = 0; i < count; i++) {
        SymCat cat = (sizes[i] > 0) ? CAT_VETOR : CAT_VAR;
        Symbol *sym = ts_insert(names[i], cat, tipo, sizes[i], decl_line);
        if (g_decl_main) {
            sym->nivel = 0;
            sym->addr = g_addr_local++;
        } else if (nivel_decl == 0) {
            sym->nivel = 0;
            sym->addr = g_addr_global++;
        } else {
            sym->nivel = nivel_decl;
            sym->addr = g_addr_local++;
        }
    }
#undef MAX_DECL
    diag_info("<< decls");
}

/* ================================================================== */
/* tpo ::= "sINT" | "sBOOL" | "sCHAR"                                */
/* ================================================================== */
static SymType p_tpo(void) {
    SymType t;
    switch (g_cur.kind) {
        case sINT:  t = TIP_INT;  advance(); break;
        case sBOOL: t = TIP_BOOL; advance(); break;
        case sCHAR: t = TIP_CHAR; advance(); break;
        default:
            diag_error(g_cur.line, "sINT|sBOOL|sCHAR", lex_kind_name(g_cur.kind));
            t = TIP_INT;
    }
    return t;
}

/* ================================================================== */
/* subs ::= (func | proc)+                                             */
/* Retorna 1 se processou o main inline.                              */
/* ================================================================== */
static int p_subs(void) {
    diag_info(">> subs");
    while (g_cur.kind == sFN || g_cur.kind == sPROC) {
        if (g_cur.kind == sPROC) {
            advance(); /* consome 'proc' */
            if (g_cur.kind == sMAIN) {
                /* proc main encontrado */
                advance(); /* consome 'main' */
                expect(sABREPAR);
                expect(sFECHAPAR);

                g_in_main = 1;
                g_nivel   = 0;
                g_addr_local = g_main_base;
                ts_push_scope("proc:main");

                int n_loc = 0;
                if (g_cur.kind == sLOCALS) {
                    /* insere locais diretamente no escopo proc:main */
                    advance();
                    g_decl_main = 1;
                    while (g_cur.kind == sIDENTIF) p_decls(0);
                    g_decl_main = 0;
                    n_loc = g_addr_local - g_main_base;
                }
                gen(g_label_main, "NADA", NULL, NULL);
                if (n_loc > 0)
                    gen(NULL, "AMEM", gen_itoa(n_loc), NULL);

                g_emit_code = 1;
                g_curr_nparams = 0;
                g_curr_is_fn = 0;
                p_bco();
                g_emit_code = 0;

                if (n_loc > 0)
                    gen(NULL, "DMEM", gen_itoa(n_loc), NULL);

                ts_pop_scope();
                g_in_main = 0;
                g_nivel   = 0;
                diag_info("<< subs (main handled)");
                return 1;
            }
            /* proc comum — analise sintatica e semantica sem geracao MEPA */
            if (g_cur.kind != sIDENTIF)
                diag_error(g_cur.line, "sIDENTIF (nome proc)", lex_kind_name(g_cur.kind));
            char pname[MAX_LEXEME];
            strncpy(pname, g_cur.lexeme, MAX_LEXEME-1); pname[MAX_LEXEME-1] = '\0';
            int pline = g_cur.line;
            advance();
            expect(sABREPAR);
            char plabel[16];
            strncpy(plabel, gen_novo_rotulo(), sizeof(plabel) - 1);
            plabel[sizeof(plabel) - 1] = '\0';
            char pscope[512];
            snprintf(pscope, sizeof(pscope), "proc:%s", pname);
            ts_push_scope(pscope);   /* escopo do proc — parametros vao aqui */
            g_nivel = 1;
            int np = 0;
            if (g_cur.kind != sFECHAPAR) np = p_param();
            expect(sFECHAPAR);
            ts_fix_params(np, g_nivel);
            /* registra o simbolo proc no escopo pai SEM fechar o corrente */
            Symbol *psym = ts_insert_in_parent(pname, CAT_PROC, TIP_NENHUM, np, pline);
            strncpy(psym->label, plabel, sizeof(psym->label) - 1);
            psym->label[sizeof(psym->label) - 1] = '\0';
            if (g_cur.kind == sLOCALS) {
                advance();
                g_addr_local = 0;
                while (g_cur.kind == sIDENTIF) p_decls(1);
            }
            int n_loc = g_addr_local;
            gen(plabel, "NADA", NULL, NULL);
            gen(NULL, "ENPR", "1", NULL);
            if (n_loc > 0) gen(NULL, "AMEM", gen_itoa(n_loc), NULL);
            g_emit_code = 1;
            g_curr_nparams = np;
            g_curr_is_fn = 0;
            p_bco();
            g_emit_code = 0;
            if (n_loc > 0) gen(NULL, "DMEM", gen_itoa(n_loc), NULL);
            gen(NULL, "RTPR", gen_itoa(np), NULL);
            ts_pop_scope();
            g_nivel = 0;
        } else {
            p_func();
        }
    }
    diag_info("<< subs (no main)");
    return 0;
}

/* ================================================================== */
/* func ::= "sFN" id "(" param? ")" ":" tpo bco                       */
/* ================================================================== */
static void p_func(void) {
    diag_info(">> func");
    expect(sFN);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (nome funcao)", lex_kind_name(g_cur.kind));
    char fname[MAX_LEXEME];
    strncpy(fname, g_cur.lexeme, MAX_LEXEME-1); fname[MAX_LEXEME-1] = '\0';
    int fline = g_cur.line;
    advance();
    expect(sABREPAR);
    char flabel[16];
    strncpy(flabel, gen_novo_rotulo(), sizeof(flabel) - 1);
    flabel[sizeof(flabel) - 1] = '\0';
    char fscope[512];
    snprintf(fscope, sizeof(fscope), "fn:%s", fname);
    ts_push_scope(fscope);   /* escopo da fn — parametros vao aqui */
    g_nivel = 1;
    int np = 0;
    if (g_cur.kind != sFECHAPAR) np = p_param();
    expect(sFECHAPAR);
    expect(sDOIS_PONT);
    SymType rt = p_tpo();
    ts_fix_params(np, g_nivel);
    /* registra o simbolo fn no escopo pai SEM fechar o escopo corrente */
    Symbol *fsym = ts_insert_in_parent(fname, CAT_FN, rt, np, fline);
    strncpy(fsym->label, flabel, sizeof(fsym->label) - 1);
    fsym->label[sizeof(fsym->label) - 1] = '\0';
    if (g_cur.kind == sLOCALS) {
        advance();
        g_addr_local = 0;
        while (g_cur.kind == sIDENTIF) p_decls(1);
    }
    int n_loc = g_addr_local;
    gen(flabel, "NADA", NULL, NULL);
    gen(NULL, "ENPR", "1", NULL);
    if (n_loc > 0) gen(NULL, "AMEM", gen_itoa(n_loc), NULL);
    g_emit_code = 1;
    g_curr_nparams = np;
    g_curr_is_fn = 1;
    p_bco();
    g_emit_code = 0;
    if (n_loc > 0) gen(NULL, "DMEM", gen_itoa(n_loc), NULL);
    gen(NULL, "CRCT", "0", NULL);
    gen(NULL, "ARMZ", "1", gen_itoa(-(np + 5)));
    gen(NULL, "RTPR", gen_itoa(np), NULL);
    ts_pop_scope();
    g_nivel = 0;
    diag_info("<< func");
}

/* ================================================================== */
/* princ ::= "sPROC" "sMAIN" "(" ")" bco                             */
/* ================================================================== */
static void p_princ(void) {
    diag_info(">> princ");
    expect(sPROC);
    expect(sMAIN);
    expect(sABREPAR);
    expect(sFECHAPAR);

    g_in_main    = 1;
    g_nivel      = 0;
    g_addr_local = g_main_base;
    ts_push_scope("proc:main");

    int n_loc = 0;
    if (g_cur.kind == sLOCALS) {
        advance();
        g_decl_main = 1;
        while (g_cur.kind == sIDENTIF) p_decls(0);
        g_decl_main = 0;
        n_loc = g_addr_local - g_main_base;
    }
    gen(g_label_main, "NADA", NULL, NULL);
    if (n_loc > 0)
        gen(NULL, "AMEM", gen_itoa(n_loc), NULL);

    g_emit_code = 1;
    g_curr_nparams = 0;
    g_curr_is_fn = 0;
    p_bco();
    g_emit_code = 0;

    if (n_loc > 0)
        gen(NULL, "DMEM", gen_itoa(n_loc), NULL);

    ts_pop_scope();
    g_in_main = 0;
    g_nivel   = 0;
    diag_info("<< princ");
}

/* ================================================================== */
/* param ::= id ":" tpo ("," id ":" tpo)*                             */
/* ================================================================== */
static int p_param(void) {
    int count = 0;
    do {
        if (count > 0) advance();
        if (g_cur.kind != sIDENTIF)
            diag_error(g_cur.line, "sIDENTIF (param)", lex_kind_name(g_cur.kind));
        char pn[MAX_LEXEME];
        strncpy(pn, g_cur.lexeme, MAX_LEXEME-1); pn[MAX_LEXEME-1] = '\0';
        int pl = g_cur.line;
        advance();
        expect(sDOIS_PONT);
        SymType t = p_tpo();
        Symbol *sym = ts_insert(pn, CAT_PARAM, t, 0, pl);
        sym->nivel = g_nivel;
        sym->addr  = 0;
        count++;
    } while (g_cur.kind == sVIRGULA);
    return count;
}

/* ================================================================== */
/* bco ::= "sSTART" (cmd ";")* "sEND"                                 */
/* ================================================================== */
static void p_bco(void) {
    diag_info(">> bco");
    expect(sSTART);
    while (g_cur.kind != sEND && g_cur.kind != sEOF) {
        p_cmd();
        expect(sPONTVIRG);
    }
    expect(sEND);
    diag_info("<< bco");
}

/* ================================================================== */
/* cmd — despacha para o comando correto                               */
/* ================================================================== */
static void p_cmd(void) {
    diag_info(">> cmd");
    switch (g_cur.kind) {
        /* ---- print ---- */
        case sPRINT: p_out(); break;

        /* ---- scan ---- */
        case sSCAN: p_inp(); break;

        /* ---- if ---- */
        case sIF: p_if(); break;

        /* ---- for ---- */
        case sFOR: p_fr(); break;

        /* ---- ret ---- */
        case sRET: p_ret(); break;

        /* ---- bloco aninhado ---- */
        case sSTART: {
            char bn[64];
            snprintf(bn, sizeof(bn), "block#%d", ++g_block_cnt);
            ts_push_scope(bn);
            p_bco();
            ts_pop_scope();
            break;
        }

        /* ---- loop while / loop..until ---- */
        case sLOOP: {
            advance(); /* consome 'loop' */
            if (g_cur.kind == sWHILE) {
                /*
                 * loop while (expr) cmd
                 *
                 * MEPA:
                 *   L_inicio: NADA
                 *             <avaliar expr>
                 *             DSVF L_fim
                 *             <cmd>
                 *             DSVS L_inicio
                 *   L_fim:    NADA
                 */
                advance(); /* consome 'while' */
                char L_ini[16], L_fim[16];
                strncpy(L_ini, gen_novo_rotulo(), 15);
                strncpy(L_fim, gen_novo_rotulo(), 15);

                gen(L_ini, "NADA", NULL, NULL);

                expect(sABREPAR);
                SymType tcond = p_expr();
                if (tcond != TIP_BOOL && tcond != TIP_INT)
                    diag_error(g_cur.line, "expressao booleana no loop while",
                               ts_type_name(tcond));
                expect(sFECHAPAR);

                if (g_emit_code) gen(NULL, "DSVF", L_fim, NULL);

                p_cmd();

                if (g_emit_code) {
                    gen(NULL, "DSVS", L_ini, NULL);
                    gen(L_fim, "NADA", NULL, NULL);
                }
            } else {
                /*
                 * loop cmd* until (expr)
                 *
                 * MEPA:
                 *   L_inicio: NADA
                 *             <cmds>
                 *             <avaliar expr>
                 *             DSVF L_inicio
                 */
                char L_ini[16];
                strncpy(L_ini, gen_novo_rotulo(), 15);

                if (g_emit_code) gen(L_ini, "NADA", NULL, NULL);

                while (g_cur.kind != sUNTIL && g_cur.kind != sEOF) {
                    p_cmd();
                    expect(sPONTVIRG);
                }
                expect(sUNTIL);
                expect(sABREPAR);
                SymType tcond = p_expr();
                if (tcond != TIP_BOOL && tcond != TIP_INT)
                    diag_error(g_cur.line, "expressao booleana no until",
                               ts_type_name(tcond));
                expect(sFECHAPAR);

                if (g_emit_code) gen(NULL, "DSVF", L_ini, NULL);
            }
            break;
        }

        /* ---- match ---- */
        case sMATCH: {
            expect(sMATCH);
            expect(sABREPAR);
            int temp_addr = g_addr_local;
            if (g_emit_code) {
                gen(NULL, "AMEM", "1", NULL);
                g_addr_local++;
            }
            SymType tmatch = p_expr();
            if (tmatch != TIP_INT)
                diag_error(g_cur.line, "int (match)", ts_type_name(tmatch));
            expect(sFECHAPAR);

            if (g_emit_code)
                gen(NULL, "ARMZ", gen_itoa(g_nivel), gen_itoa(temp_addr));

            char L_end[16];
            strncpy(L_end, gen_novo_rotulo(), 15);

            if (g_cur.kind != sWHEN)
                diag_error(g_cur.line, "sWHEN", lex_kind_name(g_cur.kind));

            while (g_cur.kind == sWHEN) {
                char L_body[16], L_next_when[16];
                strncpy(L_body, gen_novo_rotulo(), 15);
                strncpy(L_next_when, gen_novo_rotulo(), 15);

                expect(sWHEN);

                /* wcnd: witem (, witem)* */
                while (1) {
                    char L_item_next[16];
                    strncpy(L_item_next, gen_novo_rotulo(), 15);
                    int neg = 0;
                    if (g_cur.kind == sSUBRAT) { neg = 1; advance(); }
                    if (g_cur.kind != sCTEINT)
                        diag_error(g_cur.line, "sCTEINT", lex_kind_name(g_cur.kind));
                    int v1 = atoi(g_cur.lexeme);
                    if (neg) v1 = -v1;
                    advance();

                    if (g_cur.kind == sPTOPTO) {
                        advance();
                        neg = 0;
                        if (g_cur.kind == sSUBRAT) { neg = 1; advance(); }
                        if (g_cur.kind != sCTEINT)
                            diag_error(g_cur.line, "sCTEINT (limite)", lex_kind_name(g_cur.kind));
                        int v2 = atoi(g_cur.lexeme);
                        if (neg) v2 = -v2;
                        advance();

                        if (g_emit_code) {
                            gen(NULL, "CRVL", gen_itoa(g_nivel), gen_itoa(temp_addr));
                            gen(NULL, "CRCT", gen_itoa(v1), NULL);
                            gen(NULL, "CMAG", NULL, NULL);
                            gen(NULL, "CRVL", gen_itoa(g_nivel), gen_itoa(temp_addr));
                            gen(NULL, "CRCT", gen_itoa(v2), NULL);
                            gen(NULL, "CMEG", NULL, NULL);
                            gen(NULL, "CONJ", NULL, NULL);
                            gen(NULL, "DSVF", L_item_next, NULL);
                            gen(NULL, "DSVS", L_body, NULL);
                            gen(L_item_next, "NADA", NULL, NULL);
                        }
                    } else {
                        if (g_emit_code) {
                            gen(NULL, "CRVL", gen_itoa(g_nivel), gen_itoa(temp_addr));
                            gen(NULL, "CRCT", gen_itoa(v1), NULL);
                            gen(NULL, "CMIG", NULL, NULL);
                            gen(NULL, "DSVF", L_item_next, NULL);
                            gen(NULL, "DSVS", L_body, NULL);
                            gen(L_item_next, "NADA", NULL, NULL);
                        }
                    }

                    if (g_cur.kind == sVIRGULA) {
                        advance();
                        continue;
                    }
                    break;
                }

                expect(sIMPLIC);
                if (g_emit_code) gen(NULL, "DSVS", L_next_when, NULL);
                if (g_emit_code) gen(L_body, "NADA", NULL, NULL);
                p_cmd();
                expect(sPONTVIRG);
                if (g_emit_code) gen(NULL, "DSVS", L_end, NULL);
                if (g_emit_code) gen(L_next_when, "NADA", NULL, NULL);
            }

            if (g_cur.kind == sOTHERWISE) {
                expect(sOTHERWISE);
                expect(sIMPLIC);
                p_cmd();
                expect(sPONTVIRG);
            }
            expect(sEND);

            if (g_emit_code) {
                gen(L_end, "NADA", NULL, NULL);
                gen(NULL, "DMEM", "1", NULL);
                g_addr_local--;
            }
            break;
        }

        /* ---- atribuicao ou chamada de sub-rotina ---- */
        case sIDENTIF: {
            char name[MAX_LEXEME];
            strncpy(name, g_cur.lexeme, MAX_LEXEME-1); name[MAX_LEXEME-1] = '\0';
            int id_line = g_cur.line;
            advance();

            if (g_cur.kind == sABREPAR) {
                /* chamada de sub-rotina como comando */
                p_call_cmd(name);
            } else {
                /*
                 * Atribuicao: id := expr  ou  id[idx] := expr
                 *
                 * Semantica:
                 *   - id deve estar declarado
                 *   - tipo do lado direito compativel com o da variavel
                 *
                 * MEPA: <avaliar expr>  ARMZ nivel,addr
                 */
                Symbol *sym = ts_lookup(name);
                if (!sym)
                    diag_error(id_line, "identificador declarado",
                               name);
                if (sym->cat != CAT_VAR && sym->cat != CAT_PARAM)
                    diag_error(id_line, "variavel", ts_cat_name(sym->cat));

                int is_vec = (g_cur.kind == sABRECOL);
                if (is_vec) {
                    advance();
                    p_expr(); /* indice */
                    expect(sFECHACOL);
                }

                expect(sATRIB);
                SymType trhs = p_expr();

                /* checagem de tipo */
                if (sym->type != trhs && trhs != TIP_INT)
                    diag_error(id_line, ts_type_name(sym->type),
                               ts_type_name(trhs));

                /* emite ARMZ nivel,addr  (apenas variaveis simples) */
                if (g_emit_code && !is_vec) {
                    gen(NULL, "ARMZ",
                        gen_itoa(sym->nivel),
                        gen_itoa(sym->addr));
                }
            }
            break;
        }

        default:
            diag_error(g_cur.line, "comando valido", lex_kind_name(g_cur.kind));
    }
    diag_info("<< cmd");
}

/* ================================================================== */
/* out ::= "sPRINT" "(" expr ("," expr)* ")"                          */
/* MEPA: <avaliar expr>  IMPR  (para cada argumento)                  */
/* ================================================================== */
static void p_out(void) {
    diag_info(">> out");
    expect(sPRINT);
    expect(sABREPAR);
    do {
        if (g_cur.kind == sVIRGULA) advance();
        /* strings nao geram IMPR (MEPA nao tem instrucao de string) */
        if (g_cur.kind == sSTRING) {
            advance(); /* aceita sintaticamente, ignora na geracao */
        } else {
            p_expr();
            if (g_emit_code) gen(NULL, "IMPR", NULL, NULL);
        }
    } while (g_cur.kind == sVIRGULA);
    expect(sFECHAPAR);
    diag_info("<< out");
}

/* ================================================================== */
/* inp ::= "sSCAN" "(" id ")"                                         */
/* MEPA: LEIT  ARMZ nivel,addr                                        */
/* ================================================================== */
static void p_inp(void) {
    diag_info(">> inp");
    expect(sSCAN);
    expect(sABREPAR);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (variavel)", lex_kind_name(g_cur.kind));

    char name[MAX_LEXEME];
    strncpy(name, g_cur.lexeme, MAX_LEXEME-1); name[MAX_LEXEME-1] = '\0';
    int id_line = g_cur.line;
    advance();

    int is_vec = (g_cur.kind == sABRECOL);
    if (is_vec) { advance(); p_expr(); expect(sFECHACOL); }

    /* semantica: variavel deve estar declarada */
    Symbol *sym = ts_lookup(name);
    if (!sym)
        diag_error(id_line, "variavel declarada", name);
    if (sym->cat != CAT_VAR && sym->cat != CAT_PARAM)
        diag_error(id_line, "variavel", ts_cat_name(sym->cat));

    expect(sFECHAPAR);

    if (g_emit_code && !is_vec) {
        gen(NULL, "LEIT", NULL, NULL);
        gen(NULL, "ARMZ", gen_itoa(sym->nivel), gen_itoa(sym->addr));
    }
    diag_info("<< inp");
}

/* ================================================================== */
/* if ::= "sIF" "(" expr ")" cmd ("sELSE" cmd)?                       */
/*                                                                      */
/* MEPA sem else:                                                       */
/*   <expr>  DSVF L_fim  <cmd>  L_fim: NADA                           */
/*                                                                      */
/* MEPA com else:                                                       */
/*   <expr>  DSVF L_else  <cmd>  DSVS L_fim                           */
/*   L_else: NADA  <cmd_else>  L_fim: NADA                            */
/* ================================================================== */
static void p_if(void) {
    diag_info(">> if");
    expect(sIF);
    expect(sABREPAR);
    SymType tcond = p_expr();
    if (tcond != TIP_BOOL && tcond != TIP_INT)
        diag_error(g_cur.line, "expressao booleana no if", ts_type_name(tcond));
    expect(sFECHAPAR);

    char L_else[16], L_fim[16];
    strncpy(L_else, gen_novo_rotulo(), 15);
    strncpy(L_fim,  gen_novo_rotulo(), 15);

    if (g_emit_code) gen(NULL, "DSVF", L_else, NULL);

    p_cmd();

    if (g_cur.kind == sELSE) {
        if (g_emit_code) gen(NULL, "DSVS", L_fim, NULL);
        if (g_emit_code) gen(L_else, "NADA", NULL, NULL);
        advance();
        p_cmd();
        if (g_emit_code) gen(L_fim, "NADA", NULL, NULL);
    } else {
        if (g_emit_code) gen(L_else, "NADA", NULL, NULL);
    }
    diag_info("<< if");
}

/* ================================================================== */
/* fr ::= "sFOR" id ":=" expr "to" expr ["step" n] "do" cmd           */
/*                                                                      */
/* Implementado como loop while equivalente:                           */
/*   id := ini                                                          */
/*   L_ini: NADA                                                        */
/*   id <= fim  -> DSVF L_fim                                          */
/*   <cmd>                                                              */
/*   id := id + passo                                                   */
/*   DSVS L_ini                                                         */
/*   L_fim: NADA                                                        */
/* ================================================================== */
static void p_fr(void) {
    diag_info(">> fr");
    expect(sFOR);

    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (var controle)", lex_kind_name(g_cur.kind));
    char ctrl[MAX_LEXEME];
    strncpy(ctrl, g_cur.lexeme, MAX_LEXEME-1); ctrl[MAX_LEXEME-1] = '\0';
    int ctrl_line = g_cur.line;
    advance();

    /* semantica: variavel de controle deve estar declarada */
    Symbol *sym = ts_lookup(ctrl);
    if (!sym) diag_error(ctrl_line, "variavel de controle declarada", ctrl);
    if (sym->cat != CAT_VAR && sym->cat != CAT_PARAM)
        diag_error(ctrl_line, "variavel", ts_cat_name(sym->cat));

    expect(sATRIB);
    p_expr(); /* valor inicial — deixa na pilha */

    /* armazena valor inicial na variavel de controle */
    if (g_emit_code)
        gen(NULL, "ARMZ", gen_itoa(sym->nivel), gen_itoa(sym->addr));

    expect(sTO);
    /* valor final: guarda em temporario para reuso no teste */
    char L_ini[16], L_fim[16];
    strncpy(L_ini, gen_novo_rotulo(), 15);
    strncpy(L_fim, gen_novo_rotulo(), 15);

    int temp_addr = g_addr_local; /* temporario apos os locais */

    if (g_emit_code) {
        gen(NULL, "AMEM", "1", NULL);
        g_addr_local++;
    }

    /* Avalia o valor final e armazena em temp */
    p_expr(); /* valor final */
    if (g_emit_code) {
        gen(NULL, "ARMZ", gen_itoa(g_nivel), gen_itoa(temp_addr));
        gen(L_ini, "NADA", NULL, NULL);
    }

    /* passo */
    int passo = 1;
    int passo_neg = 0;
    if (g_cur.kind == sSTEP) {
        advance();
        if (g_cur.kind == sSUBRAT) { passo_neg = 1; advance(); }
        if (g_cur.kind == sCTEINT) {
            passo = atoi(g_cur.lexeme);
            if (passo_neg) passo = -passo;
            advance();
        } else if (g_cur.kind == sIDENTIF) {
            advance(); /* aceita variavel como step sintaticamente */
        } else {
            diag_error(g_cur.line, "fator step", lex_kind_name(g_cur.kind));
        }
    }

    expect(sDO);

    /*
     * Teste: ctrl <= fim  (ou ctrl >= fim se passo negativo)
     * Recarrega o valor final do temporario a cada iteracao.
     */
    if (g_emit_code) {
        gen(NULL, "CRVL", gen_itoa(sym->nivel), gen_itoa(sym->addr));
        gen(NULL, "CRVL", gen_itoa(g_nivel), gen_itoa(temp_addr));
        if (passo >= 0) {
            gen(NULL, "CMEG", NULL, NULL); /* ctrl <= fim */
        } else {
            gen(NULL, "CMAG", NULL, NULL); /* ctrl >= fim */
        }
        gen(NULL, "DSVF", L_fim, NULL);
    } else {
        /* nada a emitir */
    }

    p_cmd(); /* corpo do for */

    /* incremento: ctrl := ctrl + passo */
    if (g_emit_code) {
        gen(NULL, "CRVL", gen_itoa(sym->nivel), gen_itoa(sym->addr));
        gen(NULL, "CRCT", gen_itoa(passo < 0 ? -passo : passo), NULL);
        if (passo >= 0) gen(NULL, "SOMA", NULL, NULL);
        else            gen(NULL, "SUBT", NULL, NULL);
        gen(NULL, "ARMZ", gen_itoa(sym->nivel), gen_itoa(sym->addr));
        gen(NULL, "DSVS", L_ini, NULL);
        gen(L_fim, "NADA", NULL, NULL);
        gen(NULL, "DMEM", "1", NULL);
        g_addr_local--;
    }

    diag_info("<< fr");
}

/* ================================================================== */
/* call como comando: id ( args )                                      */
/* Semantica: verifica se e proc/fn declarada e quantidade de args     */
/* ================================================================== */
static void p_call_cmd(char *name) {
    diag_info(">> call_cmd (%s)", name);
    int id_line = g_cur.line;

    Symbol *sym = ts_lookup(name);
    if (!sym)
        diag_error(id_line, "sub-rotina declarada", name);
    if (sym->cat != CAT_PROC)
        diag_error(id_line, "procedimento", ts_cat_name(sym->cat));

    expect(sABREPAR);
    int nargs = 0;
    if (g_cur.kind != sFECHAPAR) {
        p_expr(); nargs++;
        while (g_cur.kind == sVIRGULA) { advance(); p_expr(); nargs++; }
    }
    expect(sFECHAPAR);

    /* verifica quantidade de argumentos */
    if (nargs != sym->extra)
        diag_error(id_line,
                   "numero correto de argumentos",
                   gen_itoa(nargs));
    if (g_emit_code) {
        gen(NULL, "CHPR", sym->label, "1");
    }
    diag_info("<< call_cmd");
}

/* ================================================================== */
/* ret ::= "sRET" expr                                                 */
/* ================================================================== */
static void p_ret(void) {
    diag_info(">> ret");
    expect(sRET);
    SymType t = p_expr();
    if (g_curr_is_fn) {
        if (g_emit_code) {
            gen(NULL, "ARMZ", "1", gen_itoa(-(g_curr_nparams + 5)));
            gen(NULL, "RTPR", gen_itoa(g_curr_nparams), NULL);
        }
    } else {
        diag_error(g_cur.line, "ret apenas em funcao", ts_type_name(t));
    }
    diag_info("<< ret");
}

/* ================================================================== */
/* Hierarquia de expressoes com propagacao de tipo                     */
/*                                                                      */
/* Cada funcao retorna o SymType resultante da expressao.              */
/* As instrucoes MEPA sao emitidas durante a avaliacao pos-fixa.       */
/* ================================================================== */

/* expr ::= exlog (sOR exlog)* */
static SymType p_expr(void) {
    SymType t = p_exlog();
    while (g_cur.kind == sOR) {
        advance();
        SymType t2 = p_exlog();
        /* checagem: ambos bool */
        if (t != TIP_BOOL && t != TIP_INT)
            diag_error(g_cur.line, "bool (operando v)", ts_type_name(t));
        if (t2 != TIP_BOOL && t2 != TIP_INT)
            diag_error(g_cur.line, "bool (operando v)", ts_type_name(t2));
        if (g_emit_code) gen(NULL, "DISJ", NULL, NULL);
        t = TIP_BOOL;
    }
    return t;
}

/* exlog ::= exrel (sAND exrel)* */
static SymType p_exlog(void) {
    SymType t = p_exrel();
    while (g_cur.kind == sAND) {
        advance();
        SymType t2 = p_exrel();
        if (t != TIP_BOOL && t != TIP_INT)
            diag_error(g_cur.line, "bool (operando ^)", ts_type_name(t));
        if (t2 != TIP_BOOL && t2 != TIP_INT)
            diag_error(g_cur.line, "bool (operando ^)", ts_type_name(t2));
        if (g_emit_code) gen(NULL, "CONJ", NULL, NULL);
        t = TIP_BOOL;
    }
    return t;
}

/* exrel ::= exari (oprel exari)* */
static SymType p_exrel(void) {
    SymType t = p_exari();
    while (g_cur.kind == sMAIOR   || g_cur.kind == sMAIORIG ||
           g_cur.kind == sIGUAL   || g_cur.kind == sMENOR   ||
           g_cur.kind == sMENORIG || g_cur.kind == sDIFERENTE) {
        TokenKind op = g_cur.kind;
        advance();
        SymType t2 = p_exari();
        /* tipos devem ser compativeis */
        if (t != t2 && !(t == TIP_INT && t2 == TIP_INT))
            diag_error(g_cur.line, "tipos compativeis", ts_type_name(t2));
        if (g_emit_code) {
            switch (op) {
                case sIGUAL:     gen(NULL, "CMIG", NULL, NULL); break;
                case sDIFERENTE: gen(NULL, "CMDG", NULL, NULL); break;
                case sMAIOR:     gen(NULL, "CMMA", NULL, NULL); break;
                case sMENOR:     gen(NULL, "CMME", NULL, NULL); break;
                case sMAIORIG:   gen(NULL, "CMAG", NULL, NULL); break;
                case sMENORIG:   gen(NULL, "CMEG", NULL, NULL); break;
                default: break;
            }
        }
        t = TIP_BOOL;
    }
    return t;
}

/* exari ::= exarp ((+ | -) exarp)* */
static SymType p_exari(void) {
    SymType t = p_exarp();
    while (g_cur.kind == sSOMA || g_cur.kind == sSUBRAT) {
        TokenKind op = g_cur.kind;
        advance();
        SymType t2 = p_exarp();
        if (t != TIP_INT)
            diag_error(g_cur.line, "int (operando +/-)", ts_type_name(t));
        if (t2 != TIP_INT)
            diag_error(g_cur.line, "int (operando +/-)", ts_type_name(t2));
        if (g_emit_code) {
            if (op == sSOMA) gen(NULL, "SOMA", NULL, NULL);
            else             gen(NULL, "SUBT", NULL, NULL);
        }
        t = TIP_INT;
    }
    return t;
}

/* exarp ::= fact ((* | /) fact)* */
static SymType p_exarp(void) {
    SymType t = p_fact();
    while (g_cur.kind == sMULT || g_cur.kind == sDIV) {
        TokenKind op = g_cur.kind;
        advance();
        SymType t2 = p_fact();
        if (t != TIP_INT)
            diag_error(g_cur.line, "int (operando */)", ts_type_name(t));
        if (t2 != TIP_INT)
            diag_error(g_cur.line, "int (operando */)", ts_type_name(t2));
        if (g_emit_code) {
            if (op == sMULT) gen(NULL, "MULT", NULL, NULL);
            else             gen(NULL, "DIVI", NULL, NULL);
        }
        t = TIP_INT;
    }
    return t;
}

/* fact ::= elem | ~ fact | - fact | ( expr ) */
static SymType p_fact(void) {
    if (g_cur.kind == sNEG) {
        advance();
        SymType t = p_fact();
        if (t != TIP_BOOL && t != TIP_INT)
            diag_error(g_cur.line, "bool (operando ~)", ts_type_name(t));
        if (g_emit_code) gen(NULL, "NEGA", NULL, NULL);
        return TIP_BOOL;
    }
    if (g_cur.kind == sSUBRAT) {
        advance();
        SymType t = p_fact();
        if (t != TIP_INT)
            diag_error(g_cur.line, "int (operando unario -)", ts_type_name(t));
        if (g_emit_code) gen(NULL, "INVR", NULL, NULL);
        return TIP_INT;
    }
    if (g_cur.kind == sABREPAR) {
        advance();
        SymType t = p_expr();
        expect(sFECHAPAR);
        return t;
    }
    return p_elem();
}

/* ================================================================== */
/* elem ::= literal | id | id[idx] | id(args)                         */
/* ================================================================== */
static SymType p_elem(void) {
    diag_info(">> elem");
    SymType t = TIP_INT;

    switch (g_cur.kind) {
        case sCTEINT: {
            int val = atoi(g_cur.lexeme);
            if (g_emit_code) gen(NULL, "CRCT", gen_itoa(val), NULL);
            advance();
            t = TIP_INT;
            break;
        }
        case sTRUE: {
            if (g_emit_code) gen(NULL, "CRCT", "1", NULL);
            advance();
            t = TIP_BOOL;
            break;
        }
        case sFALSE: {
            if (g_emit_code) gen(NULL, "CRCT", "0", NULL);
            advance();
            t = TIP_BOOL;
            break;
        }
        case sCTECHAR: {
            /* caracter: usa o valor ASCII */
            int ascii = (unsigned char)g_cur.lexeme[1]; /* 'x' -> x */
            if (g_emit_code) gen(NULL, "CRCT", gen_itoa(ascii), NULL);
            advance();
            t = TIP_CHAR;
            break;
        }
        case sSTRING: {
            /* strings: sem instrucao MEPA equivalente — ignora na geracao */
            advance();
            t = TIP_CHAR;
            break;
        }
        case sIDENTIF: {
            char name[MAX_LEXEME];
            strncpy(name, g_cur.lexeme, MAX_LEXEME-1); name[MAX_LEXEME-1] = '\0';
            int id_line = g_cur.line;
            advance();

            if (g_cur.kind == sABREPAR) {
                /* chamada de funcao em expressao */
                Symbol *sym = ts_lookup(name);
                if (!sym)
                    diag_error(id_line, "funcao declarada", name);
                if (sym->cat != CAT_FN)
                    diag_error(id_line, "funcao", ts_cat_name(sym->cat));

                expect(sABREPAR);
                if (g_emit_code) gen(NULL, "AMEM", "1", NULL);
                int nargs = 0;
                if (g_cur.kind != sFECHAPAR) {
                    p_expr(); nargs++;
                    while (g_cur.kind == sVIRGULA) { advance(); p_expr(); nargs++; }
                }
                expect(sFECHAPAR);

                if (nargs != sym->extra)
                    diag_error(id_line, "numero de argumentos correto", gen_itoa(nargs));

                t = sym->type;
                if (g_emit_code) gen(NULL, "CHPR", sym->label, "1");
            } else if (g_cur.kind == sABRECOL) {
                /* acesso a vetor */
                Symbol *sym = ts_lookup(name);
                if (!sym)
                    diag_error(id_line, "variavel declarada", name);
                advance();
                p_expr(); /* indice */
                expect(sFECHACOL);
                t = sym ? sym->type : TIP_INT;
                /* vetor: sem geracao MEPA nesta versao */
            } else {
                /* variavel simples */
                Symbol *sym = ts_lookup(name);
                if (!sym)
                    diag_error(id_line, "identificador declarado", name);
                if (sym->cat != CAT_VAR && sym->cat != CAT_PARAM)
                    diag_error(id_line, "variavel", ts_cat_name(sym->cat));

                if (g_emit_code)
                    gen(NULL, "CRVL",
                        gen_itoa(sym->nivel),
                        gen_itoa(sym->addr));
                t = sym->type;
            }
            break;
        }
        default:
            diag_error(g_cur.line, "expressao valida", lex_kind_name(g_cur.kind));
    }

    diag_info("<< elem -> %s", ts_type_name(t));
    return t;
}
