# Makefile – Compilador SALc
# Uso: make          → compila o projeto e gera o binário 'salc'
#      make clean    → remove arquivos objeto e o binário

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
TARGET  = salc
SRCDIR  = src

# Lista de fontes (todos os .c em src/)
SRCS = $(SRCDIR)/main.c    \
       $(SRCDIR)/opt.c     \
       $(SRCDIR)/lex.c     \
       $(SRCDIR)/diag.c    \
       $(SRCDIR)/symtab.c  \
       $(SRCDIR)/log.c     \
       $(SRCDIR)/parser.c

# Objetos derivados dos fontes
OBJS = $(SRCS:.c=.o)

# Regra padrão
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regra genérica para compilar .c → .o
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
