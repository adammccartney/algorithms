#ifndef ABINARYTREE_H
#define ABINARYTREE_H

typedef struct stack stack;
typedef struct binarytree binarytree;

/* memory for binarytree must be managed by caller */
struct binarytree {
    char c;
    binarytree *left;
    binarytree *right;
};

void traverseInorder(binarytree *t, stack *s);
void visit(binarytree* p, int level);

/* memory for stack must be managed by caller */
struct stack {
    int size;
    int top;
    binarytree** tree;
};

void pushStach(stack* s, binarytree* bt);
binarytree* popStack(stack* s);
int isempty(stack* s);

#endif
