#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "t9_lib.h"

#define MAX_INPUT_LEN 50
#define INPUT_BUF_LEN (MAX_INPUT_LEN+1)

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <dict.txt>\n", argv[0]);
        return 1;
    }

    T9 *dict = InitializeFromFileT9(argv[1]);
    if (!dict) {
        return 1;
    }

    printf("Welcome to T9!\n");
    printf("Type \"exit\" and press Enter to quit.\n");

    char input_buf[INPUT_BUF_LEN];
    while (true) {
        printf("Enter key sequence:\n> ");
        if (fgets(input_buf, INPUT_BUF_LEN, stdin) == NULL) {
            DestroyT9(dict);
            return 1;
        }

        // Truncate to first newline
        for (int i = 0; input_buf[i] != '\0'; i++) {
            if (input_buf[i] == '\n') {
                input_buf[i] = '\0';
                break;
            }
        }

        if (strcmp(input_buf, "exit") == 0) {
            DestroyT9(dict);
            return 0;
        }

        char *prediction = PredictT9(dict, input_buf);
        if (prediction) {
            printf("%s", prediction);
        } else {
            printf("No entry for %s.\n", input_buf);
        }
    }
}