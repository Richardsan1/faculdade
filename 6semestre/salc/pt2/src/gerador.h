#ifndef GERADOR_H
#define GERADOR_H

/*
 * gerador.h – Modulo de geracao de codigo MEPA
 *
 * Emite instrucoes MEPA formatadas para o arquivo de saida (.mepa).
 * Gerencia rotulos (labels) unicos para desvios condicionais e loops.
 *
 * Formato das instrucoes:
 *   rotulo:  MNEMONICO param1,param2
 * Sem espacos entre param1 e param2 (requisito do interpretador MEPA).
 */

#include <stdio.h>

/* ------------------------------------------------------------------ */
/* Inicializacao e encerramento                                          */
/* ------------------------------------------------------------------ */

/*
 * gen_init – abre o arquivo .mepa para escrita.
 * @source_path: caminho do arquivo .sal (base para o nome .mepa)
 * Retorna 0 em sucesso, -1 em falha.
 */
int  gen_init(const char *source_path);

/*
 * gen_close – fecha o arquivo .mepa.
 */
void gen_close(void);

/* ------------------------------------------------------------------ */
/* Geracao de instrucoes                                                 */
/* ------------------------------------------------------------------ */

/*
 * gen – emite uma instrucao MEPA.
 * @rotulo  : rotulo opcional (ex: "L1") ou NULL
 * @mnem    : mnemonico obrigatorio (ex: "SOMA", "ARMZ")
 * @p1      : primeiro parametro ou NULL
 * @p2      : segundo parametro ou NULL (junto com p1 sem espaco)
 *
 * Exemplos de saida:
 *   gen(NULL,  "INPP", NULL, NULL)  →      INPP
 *   gen("L1",  "NADA", NULL, NULL)  → L1:  NADA
 *   gen(NULL,  "AMEM", "3",  NULL)  →      AMEM 3
 *   gen(NULL,  "ARMZ", "0",  "2")   →      ARMZ 0,2
 */
void gen(const char *rotulo, const char *mnem,
         const char *p1,     const char *p2);

/* ------------------------------------------------------------------ */
/* Gerenciamento de rotulos                                              */
/* ------------------------------------------------------------------ */

/*
 * gen_novo_rotulo – retorna um novo rotulo unico (ex: "L1", "L2", ...).
 * O buffer retornado e estatico; copie antes de chamar novamente.
 */
const char *gen_novo_rotulo(void);

/* ------------------------------------------------------------------ */
/* Helpers para conversao de inteiro para string                        */
/* ------------------------------------------------------------------ */

/*
 * gen_itoa – converte inteiro para string em buffer estatico interno.
 * Nao e thread-safe, mas suficiente para uso no compilador.
 */
const char *gen_itoa(int n);

#endif /* GERADOR_H */
