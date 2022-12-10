
#include <stdlib.h>

#include "tree.h"

int TreeHeight(Tree t) {
    
    // Base case
    if (t == NULL)
        return -1;

    // Recursive case
    int left_height = TreeHeight(t->left);
    int right_height = TreeHeight(t->right);
    
    int height = (left_height > right_height) ? left_height : right_height;
    return height + 1;
}

