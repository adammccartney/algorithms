#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Stack */
#define SIZE 255
#define TEST_CASES 5

/* Doubly linked list */
struct node {
	int candy;
	struct node* left;
	struct node* right;
};

/* Makes a house node with candy */
struct node* new_house(int candy)
{
	struct node* house = malloc(sizeof(struct node));
	if (house == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	house->candy = candy;
	house->left = NULL;
	house->right = NULL;
	return house;
}

struct node* new_nonhouse(struct node* left, struct node* right)
{
	struct node* nonhouse = malloc(sizeof(struct node));
	if (nonhouse == NULL) {
		fprintf(stderr, "malloc error\n");
		exit(1);
	}
	nonhouse->left = left;
	nonhouse->right = right;
	return nonhouse;
}

/* Helper function to calculate the total candy in tree */
int tree_candy(struct node* tree)
{
	if (!tree->left && !tree->right) {
		return tree->candy;
	}
	return tree_candy(tree->left) + tree_candy(tree->right);
}

int tree_nodes(struct node* tree) 
{
	if (!tree->left && !tree->right)
		return 1;
	return 1 + tree_nodes(tree->left) + tree_nodes(tree->right);
}

int tree_leaves(struct node* tree)
{
	if (!tree->left && !tree->right)
		return 1;
	return tree_leaves(tree->left) + tree_leaves(tree->right);
}

int tree_streets(struct node* tree)
{
	if (!tree->left && !tree->right)
		return 0;
	return tree_streets(tree->left) + tree_streets(tree->right) + 4;
}

int max(int v1, int v2)
{
	if (v1 > v2)
		return v1;
	else
		return v2;
}

int tree_height(struct node* tree)
{
	if (!tree->left && !tree->right)
		return 0;
	return 1 + max(tree_height(tree->left), tree_height(tree->right));
}

void tree_solve(struct node* tree)
{
	int candy = tree_candy(tree);
	int height = tree_height(tree);
	int num_streets = tree_streets(tree) - height;
	printf("%d %d\n", num_streets, candy);
}


struct node* read_tree_helper(char* line, int* pos)
{
	struct node* tree;
	tree = malloc(sizeof(struct node));
	if (tree == NULL) {
		printf("malloc error\n");
		exit(1);
	}
	if (line[*pos] == '(') {
		(*pos)++;
		tree->left = read_tree_helper(line, pos);
		(*pos)++;
		tree->right = read_tree_helper(line, pos);
		(*pos)++;
		return tree;
	} else {
		tree->left = NULL;
		tree->right = NULL;
		tree->candy = line[*pos] - '0';
		(*pos)++;
		if (line[*pos] != ')' && line[*pos] != ' ' &&
		    line[*pos] != '\0') {
			tree->candy = tree->candy * 10 + line[*pos] - '0';
			(*pos)++;
		}
		return tree;
	}
}

struct node* read_tree(char* line) 
{
	int pos = 0;
	return read_tree_helper(line, &pos);
}


/* IO to read/write 5 lines */
char* ad_getline(char* line, int size) 
{
	char buf[size]; // remember to copy whitespace!
	if(!fgets(buf, size, stdin))
	{
		// reading input failed.
		exit(1);
	}
	memcpy(line, buf, size);
	return line;
}

int main(void)
{
	int i;
	char* line;
	line = malloc(SIZE + 1);
	if (line == NULL) {
		printf("malloc error\n");
		exit(1);
	}
	struct node *tree;
	for (i = 0; i < TEST_CASES; i++) {
		line = ad_getline(line, SIZE + 1);
		tree = read_tree(line);
		tree_solve(tree);
	}
	free(line);
	return 0;
}
