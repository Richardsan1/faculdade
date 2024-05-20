#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_WORDS 1000
#define MAX_WORD_LEN 20
#define MAX_LINE 256

typedef struct Word {
    char word[MAX_WORD_LEN];
    int count;
} Word;

void show_words(struct Word * arr, int length){
    int words = 0;
    for(int i = 0; i < length; i++){
        words += arr[i].count;
        printf("%s: %d\n", arr[i].word, arr[i].count);
    }
    printf("Total words: %d\n", words);
}

int compare(const void *a, const void *b) {
    return strcmp(((Word *)a)->word, ((Word *)b)->word);
}

void remove_punctuation(char* str) {
    if (str[strlen(str)-1] == '.' || str[strlen(str)-1] == ','){
        str[strlen(str)-1] = '\0';
    }
}

int main() {
    FILE *file = fopen("text.txt", "r");
    char line[MAX_LINE];
    Word words[MAX_WORDS] = {0};
    int num_words = 0;
    char * buffer = NULL;
    while (fgets(line, sizeof(line), file)) {
        char * token = strtok(line, " ");
        char * next_token = strtok(NULL, " ");
        next_token = strtok(NULL, " ");
        while (token = strtok(NULL, " ")) {
            if (!next_token){
                buffer = token;
                break;
            }
            for (int i = 0; i < num_words; i++) {
                if (buffer){
                    char val[strlen(token)+ strlen(buffer)];
                    strcpy(val, buffer);
                    strcat(val, token);
                    if (strcmp(words[i].word, val) == 0) {
                        words[i].count++;
                        token = NULL;
                        buffer = NULL;
                        break;
                    }
                } else {
                    if (strcmp(words[i].word, token) == 0) {
                        words[i].count++;
                        token = NULL;
                        break;
                    }
                }
            }
            if (token) {
                if (buffer){ 
                    char val[strlen(token)+ strlen(buffer)];
                    strcpy(val, buffer);
                    strcat(val, token);
                    strncpy(words[num_words].word, val, MAX_WORD_LEN);
                    buffer = NULL;
                } else {
                    strncpy(words[num_words].word, token, MAX_WORD_LEN);
                }
                words[num_words].count = 1;
                num_words++;
                if (num_words >= MAX_WORDS) {
                    printf("Too many unique words.\n");
                    return 1;
                }
            }
            next_token = strtok(NULL, " ");
        }
    }

    qsort(words, num_words, sizeof(Word), compare);

    show_words(words, num_words);

    printf("Total unique words: %d\n", num_words);

    return 0;
}