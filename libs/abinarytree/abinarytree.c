#include <stdio.h>
#include "abinarytree.h"

void pushStack(stack *s, binarytree* bt) {
    s->tree[++s->top] = bt;
}

binarytree* popStack(stack* s) {
    return s->tree[s->top--];
}

int isempty(stack* s) {
    if (s->top == -1) {
        return 1;  /* true */
    }
    return 0;
}

void visit(binarytree* p, int level) {
    for (int i = 0; i < level; i++) {
        putchar('*');
    }
    printf("-%c-\n", p->c);
}

/* An initialized, empty stack with sufficient memory must be provided by the
 * caller */
void traverseInorder(binarytree *t, stack *s) {
    /* T1. initialize */
    int rc;
    int level = 0; /* root */
    binarytree *p = t;

    for(;;) {
        while (p) {                 /* T2. p = Λ? */
            pushStack(s, p);        /* T3.        */
            p = p->left;
            level++;
        }
        if ((rc = isempty(s) == 1)) /* T4. finished? */
            return;
        p = popStack(s);
        visit(p, level);
        level--;
        p = p->right;
    }
}
