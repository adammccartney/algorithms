/*
 * adsort.c: very naive sorting program to sort 5 numbers.
 * */
#include "adsort.h"
#define SIZE 5

long int stack[SIZE];
int top = -1;
#define pop stack[top--];
#define push(s) stack[++top]=s;


/* shorten copies an existing array while reducing its length by 1*/
int* shorten(int* R, int len, int m) {
    int *N = malloc(sizeof(int) * len - 1);
    if (N == NULL) {
        fprintf(stderr, "malloc error\n");
        exit(1);
    }
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (i != m) {
            N[j] = R[i]; // copy over all elements apart from R[m]
            j++;
        }
    }
    return N;
}


/* adsort takes an 
 * */
void adsort(int *R, int len) {

    if (len == 0) { // base case
        return;
    } else {
        int m;
        int* n = NULL;
        m = min(R, len);
        push(R[m]);
        n = shorten(R, len, m);
        adsort(n, len-1);
    }
}

// Find the index where the smallest integer is stored
int min(int* R, int len) {
    int m = 0;
    for (int i = 0; i < len; i++) {
        if (R[i] < R[m]) { /* new min */
            m = i;
        }
    }
    return m;
}


int main(int argc, char* argv[]) {
    int R[SIZE] = {215, 382, 477, 910, 717};
    adsort(R, SIZE); // this implicitly fills the stack 
    int elem;
    while (top > -1) {
        elem = pop;
        printf("%d\n", elem);
    }
    return 0;
}
