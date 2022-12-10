
#include <stdlib.h>

#include "BSTree.h"



int BSTreeNodeDepth(BSTree t, int key) {
	// Base case
	if (t == NULL)
		return -1;
	
	// Recursive case
	if (t->value == key)
		return 0;

	else if (key < t->value) {
		int dist = BSTreeNodeDepth(t->left, key);
		if (dist == -1)
			return -1;
		else 
			return dist + 1;
	}
		
	else {
		int dist = BSTreeNodeDepth(t->right, key);
		if (dist == -1)
			return -1;
		else 
			return dist + 1;
	}
}

