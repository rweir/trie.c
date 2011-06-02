#include <stdio.h>
#include <time.h>

#include "trie.h"

int main(int argc, char **argv) {
    trie_t *t = trie_init();

    //Add some words to the trie
    trie_add(t, "foo");
    trie_add(t, "foobar");
    trie_add(t, "bar");

    //Check for the existence of a word
    printf("'foo' is in the trie: %s\n",    trie_exists(t, "foo")    ? "yes" : "no");
    printf("'foob' is in the trie: %s\n",   trie_exists(t, "foob")   ? "yes" : "no");
    printf("'foobar' is in the trie: %s\n", trie_exists(t, "foobar") ? "yes" : "no");
    printf("'bar' is in the trie: %s\n",    trie_exists(t, "bar")    ? "yes" : "no");
    printf("'cars' is in the trie: %s\n\n", trie_exists(t, "cars")   ? "yes" : "no");

    //Load the words from stopwords.txt into a trie
    trie_t *stopwords = trie_init();
    trie_load(stopwords, "stopwords.txt");

    //Remove stopwords from a sentence in a single iteration
    char *sentence = "the quick brown fox jumped over the lazy dog";
    char *result = trie_strip(stopwords, sentence);

    printf("Stripping stopwords from '%s'\n", sentence);
    printf("Result '%s'\n\n", result);

    //Speed test
    clock_t start = clock();
    for (int i = 0; i < 1000000; i++) {
        result = trie_strip(stopwords, sentence);
    }
    clock_t elapsed = (clock() - start) / (CLOCKS_PER_SEC / (double) 1000.0);
    printf("Completed 1 million iterations of the stop word example in %.0f ms\n", (double) elapsed);

    //Cleanup
    trie_free(t);
    trie_free(stopwords);

    return 0;
}

/* Expected output:

'foo' is in the trie: yes
'foob' is in the trie: no
'foobar' is in the trie: yes
'bar' is in the trie: yes
'cars' is in the trie: no

Stripping stopwords from 'the quick brown fox jumped over the lazy dog'
Result 'quick brown fox jumped lazy dog'

Completed 1 million iterations of the stop word example in 668 ms

*/
