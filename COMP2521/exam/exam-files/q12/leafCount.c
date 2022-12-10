
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "BSTree.h"

int leafCount(BSTree t, int pathLength)
{
    if (t == NULL)
        return 0;

    if (t->left == NULL && t->right == NULL)
        return 1;
    else
        return leafCount(t->left, pathLength) +
               leafCount(t->right, pathLength);
}
