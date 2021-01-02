// Copyright 2020 Serag Sorror

#ifndef T9_PRIV_H_
#define T9_PRIV_H_

#define DEFAULT_WORD_LOAD 10
#define MAX_WORD_LEN 51

typedef struct T9 {
    char** word;
    int num_words;
    struct T9* branch[10];
} T9;



int getDigit(char letter);

#endif  // T9_PRIV_H_
