
#include <stdlib.h>

#include "BSTree.h"

static int BSTreeSize(BSTree t) {
	if (t == NULL) {
		return 0;
	} else {
		return 1 + BSTreeSize(t->left) + BSTreeSize(t->right);
	}
}

int BSTreeGetKth(BSTree t, int k) {
	int leftSize = BSTreeSize(t->left);
	if (k == leftSize) {
		return t->value;
	} else if (k < leftSize) {
		return BSTreeGetKth(t->left, k);
	} else {
		return BSTreeGetKth(t->right, k - leftSize - 1);
	}
}



