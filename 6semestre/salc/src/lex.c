#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"

static FILE *g_file   = NULL;
static int   g_line   = 1;
static int   g_peeked = 0;
static int   g_peek_c = 0;
static int   g_pending_lex_error = 0;
static int   g_pending_lex_line  = 1;
static char  g_pending_lex_msg[MAX_LEXEME];

typedef struct { const char *word; TokenKind kind; } Keyword;

static const Keyword g_keywords[] = {
    { "bool",      sBOOL      },
    { "char",      sCHAR      },
    { "do",        sDO        },
    { "else",      sELSE      },
    { "end",       sEND       },
    { "false",     sFALSE     },
    { "fn",        sFN        },
    { "for",       sFOR       },
    { "globals",   sGLOBALS   },
    { "if",        sIF        },
    { "int",       sINT       },
    { "locals",    sLOCALS    },
    { "loop",      sLOOP      },
    { "main",      sMAIN      },
    { "match",     sMATCH     },
    { "module",    sMODULE    },
    { "otherwise", sOTHERWISE },
    { "print",     sPRINT     },
    { "proc",      sPROC      },
    { "ret",       sRET       },
    { "scan",      sSCAN      },
    { "start",     sSTART     },
    { "step",      sSTEP      },
    { "to",        sTO        },
    { "true",      sTRUE      },
    { "until",     sUNTIL     },
    { "when",      sWHEN      },
    { "while",     sWHILE     },
    { NULL,        sERRO      }
};

static int next_char(void) {
    int c;
    if (g_peeked) {
        g_peeked = 0;
        c = g_peek_c;
    } else {
        c = fgetc(g_file);
    }
    if (c == '\n') g_line++;
    return c;
}

static void unget_char(int c) {
    if (c == '\n') g_line--;
    g_peeked = 1;
    g_peek_c = c;
}

static int peek_char(void) {
    int c = next_char();
    unget_char(c);
    return c;
}

static void skip_whitespace_and_comments(void) {
    int c;
    while (1) {
        c = next_char();

        if (c == EOF) return;

        if (isspace(c)) continue;

        if (c == '@') {
            int nc = peek_char();
            if (nc == '{') {
                next_char();
                while (1) {
                    c = next_char();
                    if (c == EOF) {
                        g_pending_lex_error = 1;
                        g_pending_lex_line = g_line;
                        strncpy(g_pending_lex_msg,
                                "comentario de bloco nao fechado",
                                sizeof(g_pending_lex_msg) - 1);
                        g_pending_lex_msg[sizeof(g_pending_lex_msg) - 1] = '\0';
                        return;
                    }
                    if (c == '}') {
                        int nc2 = peek_char();
                        if (nc2 == '@') {
                            next_char();
                            break;
                        }
                    }
                }
            } else {
                while (1) {
                    c = next_char();
                    if (c == EOF || c == '\n') break;
                }
            }
            continue;
        }

        unget_char(c);
        return;
    }
}

static TokenKind lookup_keyword(const char *word) {
    for (int i = 0; g_keywords[i].word != NULL; i++) {
        if (strcmp(g_keywords[i].word, word) == 0)
            return g_keywords[i].kind;
    }
    return sIDENTIF;
}

static Token make_error(int line, const char *msg) {
    Token t;
    t.kind = sERRO;
    t.line = line;
    strncpy(t.lexeme, msg, MAX_LEXEME - 1);
    t.lexeme[MAX_LEXEME - 1] = '\0';
    return t;
}

int lex_init(const char *filename) {
    g_file   = fopen(filename, "r");
    g_line   = 1;
    g_peeked = 0;
    g_pending_lex_error = 0;
    g_pending_lex_line  = 1;
    g_pending_lex_msg[0] = '\0';
    return (g_file != NULL) ? 0 : -1;
}

void lex_close(void) {
    if (g_file) { fclose(g_file); g_file = NULL; }
}

Token lex_next(void) {
    Token t;
    int   c;

    skip_whitespace_and_comments();

    if (g_pending_lex_error) {
        g_pending_lex_error = 0;
        return make_error(g_pending_lex_line, g_pending_lex_msg);
    }

    c = next_char();
    t.line = g_line;

    if (c == EOF) {
        t.kind = sEOF;
        strcpy(t.lexeme, "EOF");
        return t;
    }

    if (isalpha(c) || c == '_') {
        int len = 0;
        t.lexeme[len++] = (char)c;
        while (1) {
            int nc = peek_char();
            if (isalnum(nc) || nc == '_') {
                t.lexeme[len++] = (char)next_char();
                if (len >= MAX_LEXEME - 1) break;
            } else {
                break;
            }
        }
        t.lexeme[len] = '\0';

        /* 'v' isolado representa OR em SAL. */
        if (strcmp(t.lexeme, "v") == 0) {
            t.kind = sOR;
            return t;
        }

        t.kind = lookup_keyword(t.lexeme);
        return t;
    }

    if (isdigit(c)) {
        int len = 0;
        t.lexeme[len++] = (char)c;
        while (isdigit(peek_char())) {
            t.lexeme[len++] = (char)next_char();
            if (len >= MAX_LEXEME - 1) break;
        }
        t.lexeme[len] = '\0';
        t.kind = sCTEINT;
        return t;
    }

    if (c == '"') {
        int len = 0;
        t.lexeme[len++] = '"';
        while (1) {
            int nc = next_char();
            if (nc == EOF || nc == '\n') {
                return make_error(t.line, "string nao fechada");
            }
            t.lexeme[len++] = (char)nc;
            if (len >= MAX_LEXEME - 1) break;
            if (nc == '"') break;
        }
        t.lexeme[len] = '\0';
        t.kind = sSTRING;
        return t;
    }

    if (c == '\'') {
        int nc = next_char();
        if (nc == EOF || nc == '\n') {
            return make_error(t.line, "caractere nao fechado");
        }
        t.lexeme[0] = '\'';
        t.lexeme[1] = (char)nc;
        int close = next_char();
        if (close != '\'') {
            return make_error(t.line, "constante char invalida");
        }
        t.lexeme[2] = '\'';
        t.lexeme[3] = '\0';
        t.kind = sCTECHAR;
        return t;
    }

    switch (c) {
        case '+': t.kind = sSOMA;     strcpy(t.lexeme, "+");  return t;
        case '*': t.kind = sMULT;     strcpy(t.lexeme, "*");  return t;
        case '/': t.kind = sDIV;      strcpy(t.lexeme, "/");  return t;
        case '^': t.kind = sAND;      strcpy(t.lexeme, "^");  return t;
        case '~': t.kind = sNEG;      strcpy(t.lexeme, "~");  return t;
        case ';': t.kind = sPONTVIRG; strcpy(t.lexeme, ";");  return t;
        case ',': t.kind = sVIRGULA;  strcpy(t.lexeme, ",");  return t;
        case '(': t.kind = sABREPAR;  strcpy(t.lexeme, "(");  return t;
        case ')': t.kind = sFECHAPAR; strcpy(t.lexeme, ")");  return t;
        case '[': t.kind = sABRECOL;  strcpy(t.lexeme, "[");  return t;
        case ']': t.kind = sFECHACOL; strcpy(t.lexeme, "]");  return t;

        case '=': {
            int nc = peek_char();
            if (nc == '>') {
                next_char();
                t.kind = sIMPLIC;
                strcpy(t.lexeme, "=>");
            } else {
                t.kind = sIGUAL;
                strcpy(t.lexeme, "=");
            }
            return t;
        }

        case '-': t.kind = sSUBRAT;   strcpy(t.lexeme, "-");  return t;

        case ':': {
            int nc = peek_char();
            if (nc == '=') {
                next_char();
                t.kind = sATRIB;
                strcpy(t.lexeme, ":=");
            } else {
                t.kind = sDOIS_PONT;
                strcpy(t.lexeme, ":");
            }
            return t;
        }

        case '<': {
            int nc = peek_char();
            if (nc == '=') {
                next_char();
                t.kind = sMENORIG;
                strcpy(t.lexeme, "<=");
            } else if (nc == '>') {
                next_char();
                t.kind = sDIFERENTE;
                strcpy(t.lexeme, "<>");
            } else {
                t.kind = sMENOR;
                strcpy(t.lexeme, "<");
            }
            return t;
        }

        case '>': {
            int nc = peek_char();
            if (nc == '=') {
                next_char();
                t.kind = sMAIORIG;
                strcpy(t.lexeme, ">=");
            } else {
                t.kind = sMAIOR;
                strcpy(t.lexeme, ">");
            }
            return t;
        }

        case '.': {
            int nc = peek_char();
            if (nc == '.') {
                next_char();
                t.kind = sPTOPTO;
                strcpy(t.lexeme, "..");
            } else {
                return make_error(t.line, "ponto isolado invalido");
            }
            return t;
        }

        default: {
            char msg[64];
            snprintf(msg, sizeof(msg), "caractere invalido '%c' (0x%02X)",
                     isprint(c) ? c : '?', (unsigned char)c);
            return make_error(t.line, msg);
        }
    }
    return make_error(t.line, "erro interno do lexer");
}

const char *lex_kind_name(TokenKind kind) {
    switch (kind) {
        case sIDENTIF:    return "sIDENTIF";
        case sCTEINT:     return "sCTEINT";
        case sCTECHAR:    return "sCTECHAR";
        case sSTRING:     return "sSTRING";
        case sMODULE:     return "sMODULE";
        case sGLOBALS:    return "sGLOBALS";
        case sLOCALS:     return "sLOCALS";
        case sPROC:       return "sPROC";
        case sFN:         return "sFN";
        case sMAIN:       return "sMAIN";
        case sSTART:      return "sSTART";
        case sEND:        return "sEND";
        case sIF:         return "sIF";
        case sELSE:       return "sELSE";
        case sMATCH:      return "sMATCH";
        case sWHEN:       return "sWHEN";
        case sOTHERWISE:  return "sOTHERWISE";
        case sFOR:        return "sFOR";
        case sTO:         return "sTO";
        case sSTEP:       return "sSTEP";
        case sDO:         return "sDO";
        case sLOOP:       return "sLOOP";
        case sWHILE:      return "sWHILE";
        case sUNTIL:      return "sUNTIL";
        case sPRINT:      return "sPRINT";
        case sSCAN:       return "sSCAN";
        case sRET:        return "sRET";
        case sINT:        return "sINT";
        case sBOOL:       return "sBOOL";
        case sCHAR:       return "sCHAR";
        case sTRUE:       return "sTRUE";
        case sFALSE:      return "sFALSE";
        case sATRIB:      return "sATRIB";
        case sSOMA:       return "sSOMA";
        case sSUBRAT:     return "sSUBRAT";
        case sMULT:       return "sMULT";
        case sDIV:        return "sDIV";
        case sIGUAL:      return "sIGUAL";
        case sDIFERENTE:  return "sDIFERENTE";
        case sMAIOR:      return "sMAIOR";
        case sMENOR:      return "sMENOR";
        case sMAIORIG:    return "sMAIORIG";
        case sMENORIG:    return "sMENORIG";
        case sAND:        return "sAND";
        case sOR:         return "sOR";
        case sNEG:        return "sNEG";
        case sIMPLIC:     return "sIMPLIC";
        case sPTOPTO:     return "sPTOPTO";
        case sPONTVIRG:   return "sPONTVIRG";
        case sVIRGULA:    return "sVIRGULA";
        case sDOIS_PONT:  return "sDOIS_PONT";
        case sABREPAR:    return "sABREPAR";
        case sFECHAPAR:   return "sFECHAPAR";
        case sABRECOL:    return "sABRECOL";
        case sFECHACOL:   return "sFECHACOL";
        case sEOF:        return "sEOF";
        case sERRO:       return "sERRO";
        default:          return "sINVALIDO";
    }
}
