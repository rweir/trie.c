#include <stdlib.h>

#ifndef _TRIE_H_
#define _TRIE_H_

#define TRIE_SIZE 128

typedef struct _trie_t {
    struct _trie_t *chars[TRIE_SIZE];
} trie_t;

#define trie_init() ((trie_t *) malloc(sizeof(trie_t)))

int trie_add(trie_t *, char *);
int trie_exists(trie_t *, char *);
int trie_load(trie_t *, char *);
char *trie_strip(trie_t *, char *);
void trie_free(trie_t *);

#endif
