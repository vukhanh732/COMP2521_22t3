
#include <stdlib.h>

#include "tree.h"

int TreeSumOdds(Tree t) {
	// Base case
	if (t == NULL) 
		return 0;

	// Recursive case
	if (t->value % 2 != 0)
		return t->value + TreeSumOdds(t->left) + TreeSumOdds(t->right);
	else 
		return TreeSumOdds(t->left) + TreeSumOdds(t->right); 
}

