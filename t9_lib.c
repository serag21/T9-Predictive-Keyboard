// Copyright 2020 Serag Sorror

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "t9_lib.h"
#include "t9_priv.h"

#define MAX_WORD_LEN 51
#define DEFAULT_WORD_LOAD 10

// EACH DICT NODE HAS ITS OWN WORD VAR. CHANGE TO LIST?
T9* InitializeEmptyT9() {
    T9* dict = (T9*) calloc(10, sizeof(struct T9));
    dict -> word = (char**) calloc(10, sizeof(char*) + 1);
    // ^ might have to calloc
    // dict -> next = NULL;
    dict -> num_words = 0;
    for (int i = 0; i < 10; i++) {
        dict -> branch[i] = NULL;
    }
    return dict;
}

T9* InitializeFromFileT9(const char* filename) {
    if (filename == NULL) {
        return NULL;
    }
    if (strlen(filename) == 0) {
        return NULL;
    }
    T9* dict = InitializeEmptyT9();
    // AddWordToT9(dict, "book"); TEST
    char* word = (char*) malloc(MAX_WORD_LEN * sizeof(char));
    // = (char*) calloc(1, sizeof(char));
    // if (!word) {
        // printf("Memory allocation failed. Closing this program.");
        // exit(EXIT_FAILURE);
    // }
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    // word = (char*) realloc(word, (strlen(word) + 1) * sizeof(char));
    // char* line = fgets(word, MAX_WORD_LEN, file);
    // int len = strlen(word);
    while (fgets(word, MAX_WORD_LEN - 1, file) != NULL) {
        if (word[strlen(word) - 1] == '\n') {
            word[strlen(word) - 1] = '\0';
        }
        AddWordToT9(dict, word);
        // line = fgets(word, MAX_WORD_LEN, file);
    }
    free(word);
    fclose(file);
    // free(word) -- do this AFTER done using dictionary
    return dict;
}

void AddWordToT9(T9* dict, const char* words) {
    // bool valid = true;
    // if (dict == NULL) {
        // valid = false;
    // }
    // T9* curr = dict;
    if (words == NULL) {
        return;
    }
    if (strlen(words) == 0 || words[0] == '\0') {
        return;
    }
    if (strlen(words) >= MAX_WORD_LEN) {
        return;
    }
    // if (words[0] != '\0') {
        for (int i = 0; i < strlen(words); i++) {
            if (isalpha(words[i] == 0) || islower(words[i] == 0)) {
                return;
            }
        }
        // size_t index = sizeof(dict) / sizeof(T9);
        // if (valid == true) {
        char *i;
        char word2[MAX_WORD_LEN];
        int index = 0;
        char* text = (char*) malloc(MAX_WORD_LEN * sizeof(char));
        strncpy(text, words, MAX_WORD_LEN);

        for (i = text; *i != '\0'; i++) {
            int digit = getDigit(*i);
            word2[index] = '0' + digit;
            index++;
        }
        word2[index] = '\0';
        index = 0;

        while (word2[index] != '\0') {
            int next_num = word2[index] - '0';
            if (dict -> branch[next_num] == NULL) {
                dict -> branch[next_num] = InitializeEmptyT9();
            }
            dict = dict -> branch[next_num];
            index++;
        }
        for (int i = 0; i < dict -> num_words; i++) {
            if (strcmp(dict -> word[i], words) == 0) {
                return;
            }
        }
        if (dict -> word[0] == 0) {
                dict -> word[0] = text;
                dict -> num_words++;
            } else {
                    dict -> word =
                    realloc(dict -> word,
                    (dict -> num_words + 1) * sizeof(char*));
                    dict -> word[dict -> num_words] = text;
                    dict -> num_words++;
                // }
            }
    // }
}

char* PredictT9(T9* dict, const char* nums) {
    if (dict == NULL) {
        return NULL;
    }
    if (nums == NULL || nums[0] == '#') {
        return NULL;
    }
    if (nums[0] == '\0') {
        return NULL;
    }
    for (int i = 0; nums[i] != '\0'; i++) {
        if (nums[i] == '0' || nums[i] == '1') {
            return NULL;
        }
        if (isdigit(nums[i]) == 0 && nums[i] != '#') {
            return NULL;
        }
    }
    T9* cur = dict;
    int pounds = 0;
    bool firstPound = false;
    for (int i = 0; i < strlen(nums); i++) {
        if (nums[i] != '#') {
            if (firstPound == true) {
                return NULL;
            }
            if (cur -> branch[(nums[i] - '0')] == NULL) {
                return NULL;
            }
            cur = cur -> branch[(nums[i] - '0')];
        } else {
            firstPound = true;
            pounds++;
        }
    }
    if (cur -> num_words < pounds || cur -> num_words == pounds) {
        return NULL;
    } else {
        return cur -> word[pounds];
    }
}

void DestroyT9(T9* dict) {
    for (int i = 0; i < 10; i++) {
        if (dict -> branch[i] != NULL) {
            DestroyT9(dict -> branch[i]);
            free(dict -> branch[i]);
            // if (dict -> word != NULL) {
                // free(dict -> word);
            // }
        }
    }
    for (int i = 0; i < dict -> num_words; i++) {
        if (dict -> word[i] != NULL) {
            free(dict -> word[i]);
        }
    }
}

int getDigit(char letter) {
  char table[26] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7,
          8, 8, 8, 9, 9, 9, 9};
  int i = letter - 'a';
  return table[i];
}










