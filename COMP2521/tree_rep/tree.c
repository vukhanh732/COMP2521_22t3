#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct Node {
    int data;
    Tree left;
    Tree right;
} Node;

Tree TreeCreate(Item it) {
    // TODO
    Tree new_tree = malloc(sizeof(Tree));
    if (new_tree == NULL) 
        fprintf(stderr, "Can not create a new tree");
    
    new_tree->data = it;
    new_tree->left = new_tree->right = NULL;
    return new_tree;
}

void TreeDestroy(Tree t) {
    // Base case
    
}

Tree TreeInsert(Tree t, Item it) {
    if (t == NULL) 
        return TreeCreate(it);
    else if (it < t->data)
        t->left = TreeInsert(t->left, it);
    else if (it > t->data)
        t->right = TreeInsert(t->right, it);
    return t;
}

void TreePrint(Tree t) {
    if (t == NULL)
        return;
    else if (t->)
}

