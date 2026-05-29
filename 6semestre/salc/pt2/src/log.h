#ifndef LOG_H
#define LOG_H

/*
 * log.h – Módulo de registro de artefatos intermediários do compilador SAL
 *
 * Gerencia a criação e escrita dos arquivos opcionais:
 *   .tk  – lista de tokens (--tokens)
 *   .ts  – tabela de símbolos (--symtab)
 *   .trc – rastreamento da análise (--trace)
 */

#include <stdio.h>
#include "lex.h"
#include "symtab.h"

/*
 * log_init – abre os arquivos de log habilitados pelas opções.
 * @base      : nome base do arquivo fonte (sem extensão).
 * @do_tokens : habilita log de tokens.
 * @do_symtab : habilita log de tabela de símbolos.
 * @do_trace  : habilita log de rastreamento.
 * Retorna 0 em sucesso; -1 se algum arquivo não puder ser criado.
 */
int log_init(const char *base, int do_tokens, int do_symtab, int do_trace);

/*
 * log_token – registra um token no arquivo .tk (se habilitado).
 * Formato: <linha>  <CATEGORIA>  "<lexema>"
 */
void log_token(const Token *tok);

/*
 * log_symtab – escreve a tabela de símbolos no arquivo .ts.
 */
void log_symtab(void);

/*
 * log_trace_file – retorna o FILE* do arquivo de trace
 * (para passar ao módulo diag). Pode ser NULL se não habilitado.
 */
FILE *log_trace_file(void);

/*
 * log_close – fecha todos os arquivos de log abertos.
 */
void log_close(void);

#endif /* LOG_H */
