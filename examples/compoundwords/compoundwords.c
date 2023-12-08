/* read n lines from standard in, 
 * one word per line 
 * Check if the word is a two-word compound word.
 * A two-word compound word is the concatenation of two words that exist in the
 * dictionary.
 * */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAXWORDS 500000
#define WORDLEN  16
#define SIZE 256
#define NUM_BITS 17

#define hashsize(n) ((unsigned long)1 << (n))
#define hashmask(n) (hashsize(n) - 1)

unsigned long oaat(char *key, unsigned long len,
		   unsigned long bits) {
	unsigned long hash, i;
	for (hash = 0, i = 0; i < len; i++) {
		hash += key[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash & hashmask(bits);
}

struct word_node {
	char** word;
	struct word_node *next;
};

int in_hash_table(struct word_node* hash_table[], char* find,
		  unsigned find_len)
{
	unsigned word_code;
	struct word_node* wordptr;
	word_code = oaat(find, find_len, NUM_BITS);
	wordptr = hash_table[word_code];
	while (wordptr) {
		if ((strlen(*(wordptr->word)) == find_len) &&
		    (strncmp(*(wordptr->word), find, find_len) == 0)) {
			return 1;
		}
		wordptr = wordptr->next;
	}
	return 0;
}


void identify_compound_words(char* words[],
			     struct word_node* hash_table[],
			     int total_words)
{
	int i, j;
	unsigned len;
	for (i = 0; i < total_words; i++) {
		len = strlen(words[i]);
		for (j = 1; j < len; j++) {
			if (in_hash_table(hash_table, words[i], j) &&
			    in_hash_table(hash_table, &words[i][j], len - j)) {
				printf("%s\n", words[i]);
				break;
			}
		}
	}
}



/* Function to get a line of input */
char* ad_getline(size_t size)
{
	char* input = NULL;
	char* buf;
	buf = malloc(size);  /* allocate the min number of bytes */
	if (buf == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
        size_t len = 0, newlen = 0;
	do {
		/* read at most size bytes */
		if(!fgets(buf, size, stdin))
		{
			/* read null bytes */
			buf[0] = '\0';
			return buf;
		}
		newlen = strlen(buf); /* check length of string to be copied */
		if (newlen > 0 && buf[newlen-1] == '\n') {
			buf[--newlen] = '\0'; /* remove the trailing newline if present */
		}
		if (newlen == size-1) { /* we're not finished */ 
			size *= 2;   /* Double the size    */
		} 		
		input = realloc(input, size); 
		if (input == NULL) {
			fprintf(stderr, "realloc error\n");
			exit(1);
		}
		memcpy(input + len, buf, newlen+1); /* begin to write at byte 0, else */
		len += newlen;
		size += newlen;
	} while (buf[newlen] && buf[newlen-1]!='\n' && buf[newlen-1]!=EOF);
	return input;
}

int main(int argc, char* argv[])
{
	static char* words[1 << NUM_BITS] = {NULL};
	static struct word_node* hash_table[1 << NUM_BITS] = {NULL};
	int total = 0;
	char* word;
	struct word_node* wordptr;
	unsigned length, word_code;
	word = ad_getline(WORDLEN);
	while (*word) {
		words[total] = word;
		wordptr = malloc(sizeof(struct word_node));
		if (wordptr == NULL) {
			fprintf(stderr, "malloc error\n");
			exit(1);
		}
		length = strlen(word);
		word_code = oaat(word, length, NUM_BITS);
		wordptr->word = &words[total];
		wordptr->next = hash_table[word_code];
		hash_table[word_code] = wordptr;
		word = ad_getline(WORDLEN);
		total++;
	}
	identify_compound_words(words, hash_table, total);
	return 0;
}
