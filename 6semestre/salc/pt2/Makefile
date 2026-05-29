# Makefile – Compilador SALc (Fase 1 + Fase 2)

CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99
TARGET  = salc
SRCDIR  = src

SRCS = $(SRCDIR)/main.c    \
       $(SRCDIR)/opt.c     \
       $(SRCDIR)/lex.c     \
       $(SRCDIR)/diag.c    \
       $(SRCDIR)/symtab.c  \
       $(SRCDIR)/log.c     \
       $(SRCDIR)/gerador.c \
       $(SRCDIR)/parser.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I$(SRCDIR) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
