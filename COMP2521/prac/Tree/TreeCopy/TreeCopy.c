
#include "tree.h"

static Tree newNode(int value);

Tree TreeCopy(Tree t, int depth) {
	if (t == NULL || depth < 0) {
		return NULL;
	}
	
	Tree copy = newNode(t->value);
	copy->left = TreeCopy(t->left, depth - 1);
	copy->right = TreeCopy(t->right, depth - 1);
	return copy;
}

static Tree newNode(int value) {
	Tree t = malloc(sizeof(*t));
	if (t == NULL) {
		fprintf(stderr, "Insufficient memory!\n");
		exit(EXIT_FAILURE);
	}
	
	t->value = value;
	t->left = NULL;
	t->right = NULL;
	return t;
}

