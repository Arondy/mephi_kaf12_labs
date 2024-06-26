#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include <string.h>

int bubble_sort(int *array, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = len - 1; j > i; j--) {
            if (array[j] < array[j - 1]) {
                int t = array[j - 1];
                array[j - 1] = array[j];
                array[j] = t;
            }
        }
    }
    return 0;
}

int remove_duplicates(int *A_data, int *lenA){
    for (int i = 0; i < *lenA; i++){
        if (A_data[i] == A_data[i + 1]){
            for (int k = i; k <= *lenA; k++){
                A_data[k] = A_data[k + 1];
            }
            i -= 1;
            *lenA -= 1;
        }
    }
    A_data = realloc(A_data, (*lenA) * sizeof(int));

    return 0;
}

char *process(const char *str) {
    char *str_copy = strdup(str);
    int copy_len = strlen(str_copy);
    int max_ar_len = copy_len / 2 + 1;
    int used = 0;
    int *len_array = calloc(max_ar_len, sizeof(int));
    char **word_array = calloc(max_ar_len, sizeof(char *));
    char *result = calloc(copy_len + 1, sizeof(char));
    int out_len = 0;
    char *word = strtok(str_copy, " \t");
    while (word != NULL) {
        len_array[used] = strlen(word);
        word_array[used] = word;
        used += 1;
        word = strtok(NULL, " \t");
    }
    int words_num = used;
    len_array = realloc(len_array, used * sizeof(int));
    word_array = realloc(word_array, words_num * sizeof(char *));
    bubble_sort(len_array, used);
    remove_duplicates(len_array, &used);

    for (int i = 0; i < used; i++){
        for (int j = 0; j < words_num; j++){
            int word_len = strlen(word_array[j]);
            if (len_array[i] == word_len){
                memcpy(result + out_len, word_array[j], word_len * sizeof(char));
                out_len += word_len;
                result[out_len] = ' ';
                out_len++;
            }
        }
    }

    if (out_len > 0) {
        out_len--;
    }
    result[out_len] = '\0';
    result = realloc(result, (out_len + 1) * sizeof(char));
    free(str_copy);
    free(len_array);
    free(word_array);

    return result;
}

int main() {
    char *input = readline("Your input: ");
    while (input != NULL) {
        printf("\"%s\"\n", input);
        char *result = process(input);
        printf("\"%s\"\n", result);
        free(input);
        free(result);
        input = readline("Your input: ");
    }
    return 0;
}