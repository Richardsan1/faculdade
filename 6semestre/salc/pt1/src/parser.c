#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "lex.h"
#include "diag.h"
#include "symtab.h"
#include "log.h"

static Token g_cur;
static int   g_block_cnt = 0;

static Symbol *require_declared(const char *name, int line, const char *ctx) {
    Symbol *s = ts_lookup(name);
    if (!s) {
        char found[320];
        snprintf(found, sizeof(found), "identificador '%s' nao declarado (%s)", name, ctx);
        diag_error(line, "identificador declarado", found);
    }
    return s;
}

static void advance(void) {
    g_cur = lex_next();
    log_token(&g_cur);
    if (g_cur.kind == sERRO) diag_error_lex(g_cur.line, g_cur.lexeme);
}
static void expect(TokenKind k) {
    if (g_cur.kind != k) diag_error(g_cur.line, lex_kind_name(k), lex_kind_name(g_cur.kind));
    advance();
}

static void    p_glob(void);
static void    p_decls(void);
static SymType p_tpo(void);
static void    p_subs(void);
static void    p_func(void);
static void    p_princ(void);
static int     p_param(void);
static void    p_bco(void);
static void    p_cmd(void);
static void    p_out(void);
static void    p_inp(void);
static void    p_if(void);
static void    p_mat(void);
static void    p_wlst(void);
static void    p_whn(void);
static void    p_othr(void);
static void    p_wcnd(void);
static void    p_witem(void);
static void    p_fr(void);
static void    p_call(char *name);
static void    p_ret(void);
static void    p_elem(void);
static void    p_litl(void);
static void    p_expr(void);
static void    p_exlog(void);
static void    p_exrel(void);
static void    p_exari(void);
static void    p_exarp(void);
static void    p_fact(void);

void parse_program(void) {
    diag_info(">> parse_program");
    advance();
    expect(sMODULE);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (nome do modulo)", lex_kind_name(g_cur.kind));
    diag_info("  modulo: %s", g_cur.lexeme);
    advance();
    expect(sPONTVIRG);

    ts_push_scope("global");

    if (g_cur.kind == sGLOBALS) p_glob();
    if (g_cur.kind == sFN || g_cur.kind == sPROC) p_subs();
    if (g_cur.kind == sPROC) p_princ();
    else if (g_cur.kind != sEOF)
        diag_error(g_cur.line, "sPROC (proc main) ou sEOF", lex_kind_name(g_cur.kind));

    ts_pop_scope();
    if (g_cur.kind != sEOF)
        diag_error(g_cur.line, "sEOF", lex_kind_name(g_cur.kind));
    diag_info("<< parse_program");
}

static void p_glob(void) {
    diag_info(">> glob");
    expect(sGLOBALS);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (declaracao global)", lex_kind_name(g_cur.kind));
    while (g_cur.kind == sIDENTIF) p_decls();
    diag_info("<< glob");
}

static void p_decls(void) {
    diag_info(">> decls");
#define MAX_DECL 64
    char names[MAX_DECL][MAX_LEXEME];
    int  sizes[MAX_DECL];
    int  count = 0;
    int  decl_line = g_cur.line;
    do {
        if (count > 0) advance();
        if (g_cur.kind != sIDENTIF)
            diag_error(g_cur.line, "sIDENTIF", lex_kind_name(g_cur.kind));
        strncpy(names[count], g_cur.lexeme, MAX_LEXEME-1);
        names[count][MAX_LEXEME-1] = '\0';
        sizes[count] = 0;
        advance();
        if (g_cur.kind == sABRECOL) {
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
        ts_insert(names[i], cat, tipo, sizes[i], decl_line);
    }
#undef MAX_DECL
    diag_info("<< decls");
}

static SymType p_tpo(void) {
    diag_info(">> tpo");
    SymType t;
    switch (g_cur.kind) {
        case sINT:  t = TIP_INT;  advance(); break;
        case sBOOL: t = TIP_BOOL; advance(); break;
        case sCHAR: t = TIP_CHAR; advance(); break;
        default:
            diag_error(g_cur.line, "sINT|sBOOL|sCHAR", lex_kind_name(g_cur.kind));
            t = TIP_INT;
    }
    diag_info("<< tpo");
    return t;
}

static void p_subs(void) {
    diag_info(">> subs");
    while (g_cur.kind == sFN || g_cur.kind == sPROC) {
        if (g_cur.kind == sPROC) {
            advance();
            if (g_cur.kind == sMAIN) {
                diag_info(">> princ (via subs)");
                advance();
                expect(sABREPAR);
                expect(sFECHAPAR);
                ts_push_scope("proc:main");
                int has_locals = 0;
                if (g_cur.kind == sLOCALS) {
                    has_locals = 1;
                    ts_push_scope("locals");
                    advance();
                    while (g_cur.kind == sIDENTIF) p_decls();
                }
                p_bco();
                if (has_locals) ts_pop_scope();
                ts_pop_scope();
                diag_info("<< princ (via subs)");
                diag_info("<< subs");
                return;
            }
            if (g_cur.kind != sIDENTIF)
                diag_error(g_cur.line, "sIDENTIF (nome proc)", lex_kind_name(g_cur.kind));
            char pname[MAX_LEXEME];
            strncpy(pname, g_cur.lexeme, MAX_LEXEME-1); pname[MAX_LEXEME-1] = '\0';
            int pline = g_cur.line;
            Symbol *psym = ts_insert(pname, CAT_PROC, TIP_NENHUM, 0, pline);
            advance();
            expect(sABREPAR);
            char pscope[512];
            snprintf(pscope, sizeof(pscope), "proc:%s", pname);
            ts_push_scope(pscope);
            int np = 0;
            if (g_cur.kind != sFECHAPAR) np = p_param();
            expect(sFECHAPAR);
            psym->extra = np;
            int has_locals = 0;
            if (g_cur.kind == sLOCALS) {
                has_locals = 1;
                ts_push_scope("locals");
                advance();
                while (g_cur.kind == sIDENTIF) p_decls();
            }
            p_bco();
            if (has_locals) ts_pop_scope();
            ts_pop_scope();
        } else {
            p_func();
        }
    }
    diag_info("<< subs");
}

static void p_func(void) {
    diag_info(">> func");
    expect(sFN);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (nome funcao)", lex_kind_name(g_cur.kind));
    char fname[MAX_LEXEME];
    strncpy(fname, g_cur.lexeme, MAX_LEXEME-1); fname[MAX_LEXEME-1] = '\0';
    int fline = g_cur.line;
    Symbol *fsym = ts_insert(fname, CAT_FN, TIP_NENHUM, 0, fline);
    advance();
    expect(sABREPAR);
    char fscope[512];
    snprintf(fscope, sizeof(fscope), "fn:%s", fname);
    ts_push_scope(fscope);
    int np = 0;
    if (g_cur.kind != sFECHAPAR) np = p_param();
    expect(sFECHAPAR);
    expect(sDOIS_PONT);
    SymType rt = p_tpo();
    fsym->type = rt;
    fsym->extra = np;
    int has_locals = 0;
    if (g_cur.kind == sLOCALS) {
        has_locals = 1;
        ts_push_scope("locals");
        advance();
        while (g_cur.kind == sIDENTIF) p_decls();
    }
    p_bco();
    if (has_locals) ts_pop_scope();
    ts_pop_scope();
    diag_info("<< func");
}

static void p_princ(void) {
    diag_info(">> princ");
    expect(sPROC);
    expect(sMAIN);
    expect(sABREPAR);
    expect(sFECHAPAR);
    ts_push_scope("proc:main");
    int has_locals = 0;
    if (g_cur.kind == sLOCALS) {
        has_locals = 1;
        ts_push_scope("locals");
        advance();
        while (g_cur.kind == sIDENTIF) p_decls();
    }
    p_bco();
    if (has_locals) ts_pop_scope();
    ts_pop_scope();
    diag_info("<< princ");
}

static int p_param(void) {
    diag_info(">> param");
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
        ts_insert(pn, CAT_PARAM, t, 0, pl);
        count++;
    } while (g_cur.kind == sVIRGULA);
    diag_info("<< param (%d)", count);
    return count;
}

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

static void p_cmd(void) {
    diag_info(">> cmd");
    switch (g_cur.kind) {
        case sPRINT: p_out(); break;
        case sSCAN:  p_inp(); break;
        case sIF:    p_if();  break;
        case sMATCH: p_mat(); break;
        case sFOR:   p_fr();  break;
        case sRET:   p_ret(); break;
        case sSTART: {
            char bn[64];
            snprintf(bn, sizeof(bn), "block#%d", ++g_block_cnt);
            ts_push_scope(bn);
            p_bco();
            ts_pop_scope();
            break;
        }
        case sLOOP:
            advance(); /* consome 'loop' */
            if (g_cur.kind == sWHILE) {
                diag_info(">> wh");
                advance();
                expect(sABREPAR);
                p_expr();
                expect(sFECHAPAR);
                p_cmd();
                diag_info("<< wh");
            } else {
                diag_info(">> rpt");
                while (g_cur.kind != sUNTIL && g_cur.kind != sEOF) {
                    p_cmd();
                    expect(sPONTVIRG);
                }
                expect(sUNTIL);
                expect(sABREPAR);
                p_expr();
                expect(sFECHAPAR);
                diag_info("<< rpt");
            }
            break;
        case sIDENTIF: {
            char name[MAX_LEXEME];
            int  name_line = g_cur.line;
            strncpy(name, g_cur.lexeme, MAX_LEXEME-1); name[MAX_LEXEME-1] = '\0';
            advance();
            if (g_cur.kind == sABREPAR) {
                p_call(name);
            } else {
                Symbol *lhs = require_declared(name, name_line, "atribuicao");
                if (lhs->cat == CAT_PROC || lhs->cat == CAT_FN) {
                    char found[320];
                    snprintf(found, sizeof(found), "'%s' nao e atribuivel", name);
                    diag_error(name_line, "variavel, vetor ou parametro", found);
                }
                if (g_cur.kind == sABRECOL) { advance(); p_expr(); expect(sFECHACOL); }
                expect(sATRIB);
                p_expr();
            }
            break;
        }
        default:
            diag_error(g_cur.line, "comando valido", lex_kind_name(g_cur.kind));
    }
    diag_info("<< cmd");
}

static void p_out(void) {
    diag_info(">> out");
    expect(sPRINT);
    expect(sABREPAR);
    p_expr();
    while (g_cur.kind == sVIRGULA) { advance(); p_expr(); }
    expect(sFECHAPAR);
    diag_info("<< out");
}

static void p_inp(void) {
    diag_info(">> inp");
    expect(sSCAN);
    expect(sABREPAR);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (variavel)", lex_kind_name(g_cur.kind));
    {
        Symbol *s = require_declared(g_cur.lexeme, g_cur.line, "scan");
        if (s->cat == CAT_PROC || s->cat == CAT_FN) {
            char found[320];
            snprintf(found, sizeof(found), "'%s' nao e destino valido para scan", g_cur.lexeme);
            diag_error(g_cur.line, "variavel, vetor ou parametro", found);
        }
    }
    advance();
    if (g_cur.kind == sABRECOL) { advance(); p_expr(); expect(sFECHACOL); }
    expect(sFECHAPAR);
    diag_info("<< inp");
}

static void p_if(void) {
    diag_info(">> if");
    expect(sIF);
    expect(sABREPAR);
    p_expr();
    expect(sFECHAPAR);
    p_cmd();
    if (g_cur.kind == sELSE) { advance(); p_cmd(); }
    diag_info("<< if");
}

static void p_mat(void) {
    diag_info(">> mat");
    expect(sMATCH);
    expect(sABREPAR);
    p_expr();
    expect(sFECHAPAR);
    p_wlst();
    expect(sEND);
    diag_info("<< mat");
}

static void p_wlst(void) {
    diag_info(">> wlst");
    if (g_cur.kind != sWHEN)
        diag_error(g_cur.line, "sWHEN", lex_kind_name(g_cur.kind));
    while (g_cur.kind == sWHEN) p_whn();
    if (g_cur.kind == sOTHERWISE) p_othr();
    diag_info("<< wlst");
}

static void p_whn(void) {
    diag_info(">> whn");
    expect(sWHEN);
    p_wcnd();
    expect(sIMPLIC);
    p_cmd();
    expect(sPONTVIRG);
    diag_info("<< whn");
}

static void p_othr(void) {
    diag_info(">> othr");
    expect(sOTHERWISE);
    expect(sIMPLIC);
    p_cmd();
    expect(sPONTVIRG);
    diag_info("<< othr");
}

static void p_wcnd(void) {
    diag_info(">> wcnd");
    p_witem();
    while (g_cur.kind == sVIRGULA) { advance(); p_witem(); }
    diag_info("<< wcnd");
}

static void p_witem(void) {
    diag_info(">> witem");
    if (g_cur.kind == sSUBRAT) advance();
    if (g_cur.kind != sCTEINT)
        diag_error(g_cur.line, "sCTEINT (valor when)", lex_kind_name(g_cur.kind));
    advance();
    if (g_cur.kind == sPTOPTO) {
        advance();
        if (g_cur.kind == sSUBRAT) advance();
        if (g_cur.kind != sCTEINT)
            diag_error(g_cur.line, "sCTEINT (limite intervalo)", lex_kind_name(g_cur.kind));
        advance();
    }
    diag_info("<< witem");
}

static void p_fr(void) {
    diag_info(">> fr");
    expect(sFOR);
    if (g_cur.kind != sIDENTIF)
        diag_error(g_cur.line, "sIDENTIF (var controle)", lex_kind_name(g_cur.kind));
    {
        Symbol *s = require_declared(g_cur.lexeme, g_cur.line, "for");
        if (s->cat == CAT_PROC || s->cat == CAT_FN) {
            char found[320];
            snprintf(found, sizeof(found), "'%s' nao pode ser variavel de controle", g_cur.lexeme);
            diag_error(g_cur.line, "variavel, vetor ou parametro", found);
        }
    }
    advance();
    expect(sATRIB);
    p_expr();
    expect(sTO);
    p_expr();
    if (g_cur.kind == sSTEP) {
        advance();
        if (g_cur.kind == sSUBRAT) advance();
        if (g_cur.kind == sCTEINT || g_cur.kind == sIDENTIF) advance();
        else diag_error(g_cur.line, "fator de step", lex_kind_name(g_cur.kind));
    }
    expect(sDO);
    p_cmd();
    diag_info("<< fr");
}

static void p_call(char *name) {
    diag_info(">> call (%s)", name);
    {
        Symbol *s = require_declared(name, g_cur.line, "chamada de sub-rotina");
        if (s->cat != CAT_PROC && s->cat != CAT_FN) {
            char found[320];
            snprintf(found, sizeof(found), "'%s' nao e sub-rotina", name);
            diag_error(g_cur.line, "procedimento ou funcao", found);
        }
    }
    expect(sABREPAR);
    if (g_cur.kind != sFECHAPAR) {
        p_expr();
        while (g_cur.kind == sVIRGULA) { advance(); p_expr(); }
    }
    expect(sFECHAPAR);
    diag_info("<< call");
}

static void p_ret(void) {
    diag_info(">> ret");
    expect(sRET);
    p_expr();
    diag_info("<< ret");
}

static void p_elem(void) {
    diag_info(">> elem");
    switch (g_cur.kind) {
        case sSTRING:
        case sCTEINT:
        case sCTECHAR:
        case sTRUE:
        case sFALSE:
            p_litl();
            break;
        case sIDENTIF: {
            char name[MAX_LEXEME];
            int  name_line = g_cur.line;
            strncpy(name, g_cur.lexeme, MAX_LEXEME-1); name[MAX_LEXEME-1] = '\0';
            require_declared(name, name_line, "expressao");
            advance();
            if (g_cur.kind == sABREPAR)      { p_call(name); }
            else if (g_cur.kind == sABRECOL)  { advance(); p_expr(); expect(sFECHACOL); }
            break;
        }
        default:
            diag_error(g_cur.line,
                       "elemento valido (literal, identificador, chamada, vetor)",
                       lex_kind_name(g_cur.kind));
    }
    diag_info("<< elem");
}

static void p_litl(void) {
    diag_info(">> litl");
    switch (g_cur.kind) {
        case sSTRING: case sCTEINT: case sCTECHAR: case sTRUE: case sFALSE:
            advance(); break;
        default:
            diag_error(g_cur.line, "literal", lex_kind_name(g_cur.kind));
    }
    diag_info("<< litl");
}

static void p_expr(void) {
    diag_info(">> expr");
    p_exlog();
    while (g_cur.kind == sOR) { advance(); p_exlog(); }
    diag_info("<< expr");
}

static void p_exlog(void) {
    diag_info(">> exlog");
    p_exrel();
    while (g_cur.kind == sAND) { advance(); p_exrel(); }
    diag_info("<< exlog");
}

static void p_exrel(void) {
    diag_info(">> exrel");
    p_exari();
    while (g_cur.kind == sMAIOR   || g_cur.kind == sMAIORIG  ||
           g_cur.kind == sIGUAL   || g_cur.kind == sMENOR     ||
           g_cur.kind == sMENORIG || g_cur.kind == sDIFERENTE) {
        advance(); p_exari();
    }
    diag_info("<< exrel");
}

static void p_exari(void) {
    diag_info(">> exari");
    p_exarp();
    while (g_cur.kind == sSOMA || g_cur.kind == sSUBRAT) { advance(); p_exarp(); }
    diag_info("<< exari");
}

static void p_exarp(void) {
    diag_info(">> exarp");
    p_fact();
    while (g_cur.kind == sMULT || g_cur.kind == sDIV) { advance(); p_fact(); }
    diag_info("<< exarp");
}

/* fact ::= elem | ~fact | -fact | (expr) */
static void p_fact(void) {
    diag_info(">> fact");
    if (g_cur.kind == sNEG || g_cur.kind == sSUBRAT) {
        advance(); p_fact();          /* unario, associativo a direita */
    } else if (g_cur.kind == sABREPAR) {
        advance(); p_expr(); expect(sFECHAPAR);
    } else {
        p_elem();
    }
    diag_info("<< fact");
}
