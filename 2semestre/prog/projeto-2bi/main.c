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

int compare(const void *a, const void *b) {
    return strcmp(((Word *)a)->word, ((Word *)b)->word);
}

void toLowerCase(char* str) {
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

void removePunctuation(char* str) {
    int len = strlen(str);
    if (ispunct(str[len - 1])) {
        str[len - 1] = '\0';
    }
}

int main() {
    FILE *file = fopen("text.txt", "r");
    char word[MAX_WORD_LEN];
    Word words[MAX_WORDS] = {0};
    int num_words = 0;

    while (fscanf(file, "%s", word) != EOF) {
        toLowerCase(word);
        removePunctuation(word);
        int found = 0;
        for (int i = 0; i < num_words; i++) {
            if (strcmp(words[i].word, word) == 0) {
                words[i].count++;
                found = 1;
                break;
            }
        }
        if (!found && num_words < MAX_WORDS) {
            strncpy(words[num_words].word, word, MAX_WORD_LEN);
            words[num_words].count = 1;
            num_words++;
        }
    }

    qsort(words, num_words, sizeof(Word), compare);
    int sum_words = 0;
    for (int i = 0; i < num_words; i++) {
        sum_words += words[i].count;
        printf("%s, %d\n", words[i].word, words[i].count);
    }

    fclose(file);
    printf("total de palavras diferentes no dicionario=%d\n", num_words);
    return 0;
}