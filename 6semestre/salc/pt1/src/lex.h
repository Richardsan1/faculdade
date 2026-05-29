#ifndef LEX_H
#define LEX_H

/*
 * lex.h – Módulo do analisador léxico da linguagem SAL
 *
 * Responsável pela varredura sequencial do arquivo fonte,
 * devolvendo um token por chamada a lex_next().
 */

#include <stdio.h>

/* Tamanho máximo de um lexema */
#define MAX_LEXEME 256

/*
 * Categorias de tokens da linguagem SAL.
 * Nomes seguem a convenção "s<CATEGORIA>" conforme a especificação.
 */
typedef enum {
    /* --- Identificadores e literais --- */
    sIDENTIF,      /* identificador definido pelo programador       */
    sCTEINT,       /* constante inteira                             */
    sCTECHAR,      /* constante caractere  'x'                      */
    sSTRING,       /* literal string  "..."                         */

    /* --- Palavras reservadas --- */
    sMODULE,
    sGLOBALS,
    sLOCALS,
    sPROC,
    sFN,
    sMAIN,
    sSTART,
    sEND,
    sIF,
    sELSE,
    sMATCH,
    sWHEN,
    sOTHERWISE,
    sFOR,
    sTO,
    sSTEP,
    sDO,
    sLOOP,
    sWHILE,
    sUNTIL,
    sPRINT,
    sSCAN,
    sRET,
    sINT,
    sBOOL,
    sCHAR,
    sTRUE,
    sFALSE,

    /* --- Operadores --- */
    sATRIB,        /* :=   atribuição                               */
    sSOMA,         /* +    adição                                   */
    sSUBRAT,       /* -    subtração / negativo unário              */
    sMULT,         /* *    multiplicação                            */
    sDIV,          /* /    divisão inteira                          */
    sIGUAL,        /* =    igualdade                                */
    sDIFERENTE,    /* <>   diferença                                */
    sMAIOR,        /* >    maior                                    */
    sMENOR,        /* <    menor                                    */
    sMAIORIG,      /* >=   maior ou igual                           */
    sMENORIG,      /* <=   menor ou igual                           */
    sAND,          /* ^    conjunção lógica                         */
    sOR,           /* v    disjunção lógica                         */
    sNEG,          /* ~    negação lógica                           */
    sIMPLIC,       /* =>   implicação (cláusula when)               */
    sPTOPTO,       /* ..   intervalo no match                       */

    /* --- Delimitadores e pontuação --- */
    sPONTVIRG,     /* ;    ponto e vírgula                          */
    sVIRGULA,      /* ,    vírgula                                  */
    sDOIS_PONT,    /* :    dois pontos (declaração de tipo)         */
    sABREPAR,      /* (    abre parêntese                           */
    sFECHAPAR,     /* )    fecha parêntese                          */
    sABRECOL,      /* [    abre colchete                            */
    sFECHACOL,     /* ]    fecha colchete                           */

    /* --- Controle --- */
    sEOF,          /* fim de arquivo                                */
    sERRO          /* token inválido (erro léxico)                  */
} TokenKind;

/* Estrutura de um token */
typedef struct {
    TokenKind   kind;            /* categoria do token              */
    char        lexeme[MAX_LEXEME]; /* lexema (texto original)      */
    int         line;            /* linha no arquivo fonte          */
} Token;

/*
 * lex_init – abre o arquivo fonte e prepara o analisador.
 * Retorna 0 em caso de sucesso, -1 se o arquivo não puder ser aberto.
 */
int lex_init(const char *filename);

/*
 * lex_next – lê e devolve o próximo token do arquivo fonte.
 * Ao atingir o fim do arquivo, devolve token com kind == sEOF.
 */
Token lex_next(void);

/*
 * lex_close – fecha o arquivo e libera recursos do analisador léxico.
 */
void lex_close(void);

/*
 * lex_kind_name – retorna a string do nome da categoria de um token.
 * Útil para mensagens de erro e logs.
 */
const char *lex_kind_name(TokenKind kind);

#endif /* LEX_H */
