#include "getline.h"

/* Function to get a line of input */
char* getLine(size_t size)
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
