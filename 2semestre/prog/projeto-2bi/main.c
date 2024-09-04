#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 1000
#define MAX_WORD_LEN 20

typedef struct Word {
    char word[MAX_WORD_LEN];
    int count;
} Word;

void toLowerCase(char* str) { // Converte a palavra para minúsculo
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void removePunctuation(char* str) { // Remove a pontuação do final da palavra
    int len = strlen(str);
    if (ispunct(str[len - 1])) {
        str[len - 1] = '\0';
    }
}

int binarySearch(Word *words, int num_words, char *word) { // Busca binária
    int left = 0, right = num_words - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int res = strcmp(words[mid].word, word);
        if (res == 0) return mid;
        if (res < 0) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

void insertWord(Word *words, int num_words, char *word) { // Insere a palavra no dicionário, ordenada
    int i = num_words - 1;
    while (i >= 0 && strcmp(words[i].word, word) > 0) {
        words[i + 1] = words[i];
        i--;
    }
    strncpy(words[i + 1].word, word, MAX_WORD_LEN);
    words[i + 1].count = 1;
}

int main() {
    FILE *file = fopen("text.txt", "r"); // Arquivo de texto
    char word[MAX_WORD_LEN]; // Palavra
    Word words[MAX_WORDS] = {0}; // lista de palavras
    int num_words = 0;

    while (fscanf(file, "%s", word) != EOF) { // Lê palavra por palavra
        toLowerCase(word);
        removePunctuation(word);
        int index = binarySearch(words, num_words, word); // Busca a palavra no dicionário
        if (index != -1) { // Se a palavra já existe, incrementa o contador dela
            words[index].count++;
        } else if (num_words < MAX_WORDS) { // Se a palavra não existe e ainda cabe no dicionário, insere ela, ordenada
            insertWord(words, num_words, word);
            num_words++; // Incrementa o número de palavras no dicionário
        }
    }

    for (int i = 0; i < num_words; i++) { // Ordena o dicionário
        printf("%s, %d\n", words[i].word, words[i].count);
    }

    fclose(file);
    printf("total de palavras diferentes no dicionario=%d\n", num_words); // Imprime o número de palavras diferentes no dicionário
    return 0;
}