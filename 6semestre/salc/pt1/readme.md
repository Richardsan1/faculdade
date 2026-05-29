# SALc — Compilador para a Linguagem SAL

Implementação completa, em C, da **fase 1** do compilador SALc para a linguagem
**SAL – Simple Academic Language** (especificação versão 1.0).

---

## Compilação

```bash
make
```

Requer `gcc` com suporte a C99. O binário `salc` é gerado na raiz do projeto.

Para limpar os artefatos de compilação:

```bash
make clean
```

---

## Uso

```
./salc <arquivo.sal> [--tokens] [--symtab] [--trace]
```

| Opção       | Descrição                                                  | Arquivo gerado |
|-------------|------------------------------------------------------------|----------------|
| `--tokens`  | Lista todos os tokens reconhecidos pelo analisador léxico  | `<base>.tk`    |
| `--symtab`  | Tabela de símbolos consolidada ao final da análise         | `<base>.ts`    |
| `--trace`   | Rastreamento da entrada/saída de cada não-terminal         | `<base>.trc`   |

### Exemplos

```bash
# Análise simples
./salc programa.sal

# Com todos os logs habilitados
./salc programa.sal --tokens --symtab --trace
```

---

## Estrutura do projeto

```
salc/
├── Makefile
├── readme.md
└── src/
    ├── main.c      Orquestração e inicialização dos módulos
    ├── opt.h / opt.c       Interpretação dos argumentos de linha de comando
    ├── lex.h / lex.c       Analisador léxico
    ├── diag.h / diag.c     Diagnósticos e mensagens de erro
    ├── symtab.h / symtab.c Tabela de símbolos com controle de escopo
    ├── log.h / log.c       Geração dos arquivos de log opcionais
    ├── parser.h / parser.c Analisador sintático descendente recursivo (ASDR)
    └── (sem dependências externas)
```

---

## Módulos

### `opt` — Opções de execução
Interpreta `argc/argv` e expõe as opções via `opts_get()`. Qualquer argumento
inválido exibe a mensagem de uso e encerra.

### `lex` — Analisador Léxico
Varredura sequencial do arquivo-fonte, sem pré-processamento. Cada chamada a
`lex_next()` devolve um `Token` com `kind`, `lexeme` e `line`.

Reconhece:
- Palavras reservadas (`module`, `proc`, `fn`, `if`, `match`, `for`, `loop`, `while`, `until`, …)
- Identificadores e o operador especial `v` (disjunção lógica)
- Constantes: inteiras (`sCTEINT`), caractere (`sCTECHAR`), strings (`sSTRING`), booleanas
- Operadores simples e compostos (`:=`, `<>`, `>=`, `<=`, `=>`, `..`)
- Comentários de linha (`@`) e de bloco (`@{…}@`), descartados silenciosamente
- Erros léxicos reportados via `diag_error_lex` com linha e descrição

### `diag` — Diagnósticos
Centraliza as saídas de erro e rastreamento. `lex` e `parser` nunca imprimem
diretamente; chamam `diag_error`, `diag_error_lex` ou `diag_info`. Erros
encerram imediatamente a execução com `exit(EXIT_FAILURE)`.

Formato dos erros:
```
[ERRO SINTATICO] linha N: esperado '<TOKEN_ESPERADO>', encontrado '<TOKEN_ENCONTRADO>'.
[ERRO LEXICO]    linha N: <descricao>.
```

### `symtab` — Tabela de Símbolos
Pilha de frames de escopo (`ScopeFrame`). Cada frame contém uma lista
encadeada de símbolos em ordem de inserção.

Escopos criados pelo parser:
| Escopo            | Quando                              |
|-------------------|-------------------------------------|
| `global`          | Abertura do módulo                  |
| `fn:<nome>`       | Cabeçalho de função                 |
| `proc:<nome>`     | Cabeçalho de procedimento           |
| `locals`          | Seção `locals` de sub-rotinas/main  |
| `block#N`         | Bloco `start…end` aninhado          |

A busca (`ts_lookup`) percorre da camada mais interna até a global, respeitando
a visibilidade da SAL. Redeclarações no mesmo escopo são detectadas e
reportadas via `diag_error`.

Atributo `extra`:
- Vetores: tamanho declarado (ex.: `255` para `buf[255]: char`)
- Funções/procedimentos: número de parâmetros formais

### `log` — Artefatos intermediários
Cria e grava nos arquivos `.tk`, `.ts` e `.trc` conforme as opções ativas.
`log_token()` é chamado a cada `advance()` no parser; `log_symtab()` é
chamado pelo `main` após a análise completa.

Formato do `.tk`:
```
<linha>  <CATEGORIA>  "<lexema>"
```

Formato do `.ts`:
```
SCOPE=<caminho_escopo>  id="<lexema>"  cat=<categoria>  tipo=<tipo>  extra=<valor>
```

### `parser` — ASDR
Implementa a gramática EBNF do Apêndice A da especificação SAL. Cada
não-terminal tem sua função `static`:

| Função      | Não-terminal |
|-------------|--------------|
| `parse_program` | `ini`    |
| `p_glob`    | `glob`       |
| `p_decls`   | `decls`      |
| `p_tpo`     | `tpo`        |
| `p_subs`    | `subs`       |
| `p_func`    | `func`       |
| `p_princ`   | `princ`      |
| `p_param`   | `param`      |
| `p_bco`     | `bco`        |
| `p_cmd`     | `cmd`        |
| `p_out`     | `out`        |
| `p_inp`     | `inp`        |
| `p_if`      | `if`         |
| `p_mat`     | `mat`        |
| `p_wlst/p_whn/p_othr/p_wcnd/p_witem` | `wlst/whn/othr/wcnd/witem` |
| `p_fr`      | `fr`         |
| `p_call`    | `call`       |
| `p_ret`     | `ret`        |
| `p_elem`    | `elem`       |
| `p_litl`    | `litl`       |
| `p_expr … p_fact` | `expr … fact` |

**Hierarquia de expressões** (do menos ao mais prioritário):

```
p_expr  → p_exlog  (sOR)
p_exlog → p_exrel  (sAND)
p_exrel → p_exari  (oprel: < <= > >= = <>)
p_exari → p_exarp  (+ -)
p_exarp → p_fact   (* /)
p_fact  → p_elem | ~ p_fact | - p_fact | ( p_expr )
```

---

## Decisões de implementação

- **`p_elem` vs `p_expr`**: atribuições e `ret` usam `p_expr` (expressão completa)
  no lado direito, garantindo que `x := A + (i-1) * R` seja corretamente aceito.
  `p_elem` trata literais e identificadores sem ambiguidade com os operadores.
- **Detecção de `proc main`**: `p_subs` consome `proc` e verifica o nome seguinte.
  Se for `main`, processa o bloco principal inline e retorna; `parse_program`
  não tenta chamar `p_princ` novamente.
- **Operador `v`**: o identificador de um único caractere `v` é tratado como
  `sOR` quando não seguido de caractere alfanumérico ou `_`.
- **Operador `=>`**: reconhecido no analisador léxico a partir do `=` seguido de `>`.
- **Escopos duplicados**: ao registrar uma sub-rotina na TS, o parser abre o
  escopo para os parâmetros, fecha para inserir o símbolo no pai, e reabre
  para o corpo — garantindo que os parâmetros pertençam ao escopo da
  sub-rotina e não ao pai.

---

## O que está implementado (Fase 1)

- [x] Análise léxica completa com todas as categorias da SAL
- [x] Comentários de linha e de bloco
- [x] ASDR fiel à gramática EBNF da especificação
- [x] Tabela de símbolos com escopos aninhados (global, fn, proc, locals, block#N)
- [x] Detecção de redeclaração de identificadores
- [x] Geração de logs: `.tk`, `.ts`, `.trc`
- [x] Interface de linha de comando (`--tokens`, `--symtab`, `--trace`)
- [x] Mensagens de erro com linha, token esperado e token encontrado
- [x] Todos os 7 exemplos da especificação analisados corretamente

## O que será implementado na Fase 2

- [ ] Verificação semântica (compatibilidade de tipos, variável declarada antes do uso)
- [ ] Geração de código MEPA para a máquina virtual baseada em pilha
