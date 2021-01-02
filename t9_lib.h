// Copyright 2020 Andrew Hu

#ifndef T9_LIB_H_
#define T9_LIB_H_
/**
 * An allocated T9 instance. Contains an initialized (but possibly empty)
 * dictionary.
 */
struct T9;
typedef struct T9 T9;


/**
 * Allocates a new T9 instance with empty internal dictionary.
 * 
 * Pre: The computer has sufficient memory to allocate a T9 instance.
 * 
 * Post: The returned pointer points to a valid T9 instance which has no words
 * in its dictionary.
 */
T9* InitializeEmptyT9();

/**
 * Allocates a new T9 instance and initializes its dictionary to include all
 * words in the given file.
 * 
 * Pre: "filename" is a non-null pointer which points to a valid C string.
 * 
 * Post: If no file exists with the given name, NULL is returned and an error
 * message is printed. Otherwise, the file is read and each line is interpreted
 * as a word. A new T9 instance is allocated, as with InitializeEmptyT9, and
 * AddWordToT9 is called on it for every line in the file. Note that this means
 * invalid words, as defined by AddWordToT9, are skipped.
 */
T9* InitializeFromFileT9(const char* filename);

/**
 * Adds the given word to the internal T9 dictionary.
 * 
 * Pre: "dict" is a pointer previously returned from a call to InitializeEmptyT9
 * or InitializeFromFileT9, and not yet freed by DestroyT9. "word" points to a
 * valid C string, or NULL.
 * 
 * Post: If "word" was nonempty and contained only lowercase English letters
 * (i.e., the 26 letters of the alphabet), and "word" was not already present
 * in the dictionary, the specified dictionary has been updated to include
 * this word. Otherwise, the dictionary remains unchanged.
 */
void AddWordToT9(T9* dict, const char* word);

/**
 * Attempts to identify a word which is specified by the given sequence of
 * T9 commands.
 * 
 * Pre: "dict" is a pointer previously returned from a call to InitializeEmptyT9
 * or InitializeFromFileT9, and not yet freed by DestroyT9. "nums" points to a
 * valid C string, or NULL.
 * 
 * Post: If "nums" is NULL, NULL is returned. If "nums" contains any characters
 * other than digits two ("2") through nine ("9") and the pound ("#") sign,
 * NULL is returned. If "nums" contains any digit after the first "#" in the
 * string, NULL is returned. If "nums" starts with a "#", NULL is returned.
 * Otherwise, a search is performed on the internal dictionary.
 * 
 * A list of words which are of the same length as the digits-only portion of
 * the string, and are exactly represented on a phone keyboard by those digits,
 * is identified. If this list is empty, NULL is returned. Otherwise, the Nth
 * (zero-indexed, such that N=0 gives the first element) item in the list, where
 * "N" is the number of pound signs given in "nums", is returned. If there are
 * fewer than N-1 items in the list, NULL is returned.
 */
char* PredictT9(T9* dict, const char* nums);

/**
 * Destroys the given T9 implementation, and frees all associated memory.
 * 
 * Pre: "dict" is a pointer previously returned from a call to InitializeEmptyT9
 * or InitializeFromFileT9, and not yet freed by DestroyT9.
 * 
 * Post: The instance pointed to by "dict", and all memory allocated for it, is
 * freed.
 */
void DestroyT9(T9* dict);

#endif  // T9_LIB_H_
