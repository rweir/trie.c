#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "trie.h"

int trie_add(trie_t *t, char *word) {
    int c, i = 0;

    while ((c = word[i++]) != '\0') {
        assert(c >= 0 && c <= 127);
        if (t->chars[c] == NULL) {
            t->chars[c] = trie_init();
        }
        t = t->chars[c];
    }
    if (i > 0) {
        t->chars[0] = trie_init();
    }
    return i;
}

int trie_exists(trie_t *t, char *word) {
    int c, i = 0;

    while ((c = word[i++]) != '\0') {
        if (t->chars[c] == NULL) {
            return 0;
        }
        t = t->chars[c];
    }
    return t->chars[0] != NULL ? 1 : 0;
}

int trie_load(trie_t *t, char *file) {
    FILE *stream = fopen(file, "r");
    trie_t *root = t;
    int c, words = 0, word_len = 0;

    if (stream == NULL) {
        return -1;
    }
    while ((c = getc(stream)) != EOF) {
        if (c == '\n' || c == '\r') {
            if (word_len > 0) {
                t->chars[0] = trie_init();
                words++;
                word_len = 0;
                t = root;
            }
        } else {
            word_len++;
            assert(c >= 0 && c <= 127);
            if (t->chars[c] == NULL) {
                t->chars[c] = trie_init();
            }
            t = t->chars[c];
        }
    }
    if (t != root && word_len > 0) {
        t->chars[0] = trie_init();
    }
    return words;
}

char *trie_strip(trie_t *t, char *sentence) {
    if (sentence == NULL) {
        return NULL;;
    }
    char *result = (char *) malloc(sizeof(sentence) / sizeof(char));
    int c, i = 0, j = 0, last_break = 0, in_trie = 1;
    trie_t *root = t;

    while (1) {
        c = result[j++] = sentence[i++];
        if (c == ' ' || c == '\n' || c == '\r' || c == '\0') {
            t = root;
            if (in_trie) {
                j = last_break;
            } else {
                in_trie = 1;
                last_break = j;
            }
            if (c == '\0') {
                if (j < i) {
                    result[j] = '\0';
                }
                break;
            }
            continue;
        }
        if (!in_trie) {
            continue;
        }
        if (t->chars[c] == NULL) {
            in_trie = 0;
        } else {
            t = t->chars[c];
            in_trie = 1;
        }
    }
    return result;
}

void trie_free(trie_t *t) {
    for (int i = 0; i < TRIE_SIZE; i++) {
        if (t->chars[i] != NULL) {
            trie_free(t->chars[i]);
        }
    }
    free(t);
}
