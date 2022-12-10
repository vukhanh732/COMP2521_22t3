
#include "BSTree.h"

#include <stdlib.h>

BSTree BSTreeGetSmallest(BSTree t) {
	// TODO

	// Base case
	if (t == NULL)
		return t;
	
	BSTree curr = t;
	while (curr->left != NULL) {
		curr = curr->left;
	}
	
	return curr;	
}

