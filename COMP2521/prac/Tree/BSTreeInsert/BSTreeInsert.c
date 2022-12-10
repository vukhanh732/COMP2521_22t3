
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

BSTree newNode(int val) {
	BSTree new = malloc(sizeof(*new));
	if (new == NULL) {
		fprintf(stderr, "couldn't allocate node");
		exit(EXIT_FAILURE);
	}

	new->value = val;
	new->left = new->right = NULL;
	return new;
}

BSTree BSTreeInsert(BSTree t, int val) {
	// TODO
	// Base case
	if (t == NULL)
		return newNode(val);

	// Recursive case
	if (val < t->value) 
		t->left = BSTreeInsert(t->left, val);
	else if (val > t->value)
		t->right = BSTreeInsert(t->right, val);

	return t;
}

