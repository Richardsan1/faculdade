#ifndef PARSER_H
#define PARSER_H

/*
 * parser.h – Módulo do Analisador Sintático Descendente Recursivo (ASDR)
 *
 * Implementa a gramática oficial da linguagem SAL (EBNF do Apêndice A).
 * Cada não-terminal possui função própria.
 * O parser consome tokens do lex e controla escopos na tabela de símbolos.
 */

/*
 * parse_program – ponto de entrada do parser.
 * Deve ser chamado após lex_init, ts_init e diag_init.
 * Em caso de erro sintático, encerra via diag_error.
 */
void parse_program(void);

#endif /* PARSER_H */
