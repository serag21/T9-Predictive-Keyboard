/*
 * You will want to replace this file with your test suite from HW4!
 */

#include "t9_lib.h"

#include "t9_priv.h"
#include "string.h"

#include "safe_assert.h"

void AssertReturnedStringEquals(char *expected, char *actual);

suite("T9") {
    test("Empty initialization") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);
        DestroyT9(dict);
    }

    test("Correct PredictT9?") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        // AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");


        char* word = PredictT9(dict, "2665");
        printf("word is: %s\n", word);
        AssertReturnedStringEquals("cool", word);
        DestroyT9(dict);
    }

    test("'nums' in PredictT9 is not number or # sign returns NULL") {
        T9 *dict = InitializeFromFileT9("dictionary.txt");
        safe_assert(dict != NULL);

        // AddWordToT9(dict, "cool");

        char* word = PredictT9(dict, "2665A#");
        char* word2 = PredictT9(dict, "A");
        char* word3 = PredictT9(dict, "a2665#");
        char* word4 = PredictT9(dict, "2665 ");
        safe_assert(word == NULL);
        safe_assert(word2 == NULL);
        safe_assert(word3 == NULL);
        safe_assert(word4 == NULL);
        DestroyT9(dict);
    }

    test("Digit after first #") {
        T9 *dict = InitializeFromFileT9("dictionary.txt");
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");

        char* word = PredictT9(dict, "266#5");
        safe_assert(word == NULL);
        DestroyT9(dict);
    }

    test("'nums' starts with #") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");

        char* word = PredictT9(dict, "#2665#");
        safe_assert(word == NULL);
        DestroyT9(dict);
    }

    test("Add empty string") {
        T9 *dict = InitializeEmptyT9();
        T9 *dict_2 = InitializeEmptyT9();

        safe_assert(dict != NULL);
        safe_assert(dict_2 != NULL);

        AddWordToT9(dict, "");  
        AddWordToT9(dict, "cool");
        AddWordToT9(dict_2, "cool");
        AssertReturnedStringEquals(PredictT9(dict, "2665"), PredictT9(dict_2, "2665"));
        // safe_assert(strcmp(PredictT9(dict, "2665"), PredictT9(dict_2, "2665")) == 0);

        DestroyT9(dict);
        DestroyT9(dict_2);

    }

    test("Add duplicate word") {
        T9 *dict = InitializeEmptyT9();
        T9 *dict_2 = InitializeEmptyT9();

        safe_assert(dict != NULL);
        safe_assert(dict_2 != NULL);
        
        AddWordToT9(dict, "book");
        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");
        safe_assert(strcmp(PredictT9(dict, "2665#"), "cool") == 0);


    }

    test("Invalid input File") {
        T9 *dict = InitializeFromFileT9("Invalid.txt");
        safe_assert(dict == NULL);
        T9 *dict2 = InitializeFromFileT9("");
        safe_assert(dict2 == NULL);
        //T9 *dict3;
        //safe_assert(dict3 == NULL);
        T9 *dict4 = InitializeFromFileT9(" .txt");
        safe_assert(dict4 == NULL);
    }

    test("nums is NULL in PredictT9()") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "cool");
        char* word = PredictT9(dict, NULL);

        safe_assert(word == NULL);
    }

    test("filename is null pointer") {
        char* filename = NULL;
        T9 *dict = InitializeFromFileT9(filename);

        safe_assert(dict == NULL);
    }

    test("Uppercase letters in word") {
        T9 *dict = InitializeEmptyT9();
        T9 *dict_2 = InitializeEmptyT9();

        safe_assert(dict != NULL);
        safe_assert(dict_2 != NULL);

        //AddWordToT9(dict, "cool");

        //AddWordToT9(dict_2, "cool");
        AddWordToT9(dict, "BOOK");
        AddWordToT9(dict, "BoOk");


        safe_assert(PredictT9(dict, "2665") == NULL);

        DestroyT9(dict);
        DestroyT9(dict_2);

    }

    test("PredictT9 returns char*") {
        T9 *dict = InitializeFromFileT9("dictionary.txt");
        safe_assert(dict != NULL);

        char* nums = "2665";
        char* word;
        word = PredictT9(dict, nums);
        safe_assert(word != NULL);

    }

    test("PredictT9 returns NULL with empty dict") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        char* nums = "2665";
        safe_assert(PredictT9(dict, nums) == NULL);

    }

    test("invalid symbols in PredictT9") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");

        char* word = PredictT9(dict, "!$@*");
        safe_assert(word == NULL);
    }

    test("invalid symbols in AddWordToT9") {
        T9 *dict = InitializeEmptyT9();
        safe_assert(dict != NULL);

        AddWordToT9(dict, "!@#$");

        //AssertReturnedStringEquals(dict, "");

        AddWordToT9(dict, "book?");
        AddWordToT9(dict, "book!");
        AddWordToT9(dict, "book#*");
        AddWordToT9(dict, "bo ok");
        AddWordToT9(dict, "bo#ok");
        AddWordToT9(dict, "book ");
        AddWordToT9(dict, "book #");
        AddWordToT9(dict, "book.");
        safe_assert(PredictT9(dict, "2665") == NULL);

        AddWordToT9(dict, "book");
        AssertReturnedStringEquals(PredictT9(dict, "2665"), "book");
    }

    test("Invalid inputs to nums") {
        T9 *dict = InitializeFromFileT9("dictionary.txt");
        safe_assert(dict != NULL);

        AddWordToT9(dict, "cool");

        char* word = PredictT9(dict, "2661");
        char* word2 = PredictT9(dict, "2660");
        char* word3 = PredictT9(dict, "266*");
        char* word4 = PredictT9(dict, "21?#");
        char* word5 = PredictT9(dict, NULL);
        char* word6 = PredictT9(dict, "1");
        char* word7 = PredictT9(dict, "0");
        safe_assert(word == NULL);
        safe_assert(word2 == NULL);
        safe_assert(word3 == NULL);
        safe_assert(word4 == NULL);
        safe_assert(word5 == NULL);
        safe_assert(word6 == NULL);
        safe_assert(word7 == NULL);
        DestroyT9(dict);
    }

    test("Uppercase in AddWordToT9") {
        T9 *dict = InitializeEmptyT9();
        T9 *dict_2 = InitializeEmptyT9();

        safe_assert(dict != NULL);
        safe_assert(dict_2 != NULL);

        AddWordToT9(dict, "cOoL");
        //AssertReturnedStringEquals(dict, dict_2);
        safe_assert((PredictT9(dict, "2665") == NULL));

        DestroyT9(dict);
        DestroyT9(dict_2);

    }

    test("Too many pound signs") {
        T9 *dict = InitializeFromFileT9("dictionary.txt");
        safe_assert(dict != NULL);

        char* word = PredictT9(dict, "2665#######");
        safe_assert(word == NULL);
    }


    test("Predict returns empty list"){
        T9 *dict = InitializeFromFileT9("small_dictionary.txt");
        safe_assert(dict != NULL);

        char* word = PredictT9(dict, "226");
        safe_assert(word == NULL);
    }
    
    test("SAME"){
        T9 *dict = InitializeEmptyT9();
        T9 *dict_2 = InitializeEmptyT9();

        AddWordToT9(dict_2, "book");
        //AddWordToT9(dict, "book");
        AddWordToT9(dict, "book");
        AddWordToT9(dict, "cool");
        safe_assert(strcmp(PredictT9(dict, "2665"), PredictT9(dict_2, "2665")) == 0);
    }
    
    //test("uninitialized dictionary") {
        //safe_assert(T9 *dict);

        //AddWordToT9(dict, "book");
        //safe_assert(dict == NULL);
        //safe_assert(InitializeFromFileT9("file") == NULL);
        //safe_assert(dict == NULL);
        //safe_assert(PredictT9(dict, "2665") == NULL);
    //}

    test("freed dictionary") {
        T9 *dict = InitializeEmptyT9();

        AddWordToT9(dict, "book");
        DestroyT9(dict);
        
        safe_assert(PredictT9(dict, "2665") == NULL);

    }

    test("freed dictionary 2") {
        T9 *dict = InitializeFromFileT9("dictionary.txt");

        DestroyT9(dict);
        char* word = PredictT9(dict, "2665");
        //printf("word is: %s\n", word);
        AssertReturnedStringEquals(word, "");

    }

    
}

void AssertReturnedStringEquals(char *expected, char *actual) {
    safe_assert(actual > 0);
    safe_assert(strlen(actual) == strlen(expected));
    safe_assert(strcmp(actual, expected) == 0);
}
