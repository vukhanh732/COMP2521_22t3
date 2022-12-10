// Implementation of the Tree ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Record.h"
#include "Tree.h"

struct node {
    Record rec;
    Node   left;
    Node   right;

    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary
    int height;

};

struct tree {
    Node root;
    int (*compare)(Record, Record);

    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary

};

static void doTreeFree(Node n, bool freeRecords);

// HELPER FUNCTIONS
static Node doTreeInsert(Tree t, Node n, Record rec, bool *res);
static Node newNode(Record rec);
static Node rotateRight(Node root);
static Node rotateLeft(Node root);
static int getHeight(Node n);
static Record doTreeSearch(Tree t, Node n, Record rec);

////////////////////////////////////////////////////////////////////////
// Provided functions
// !!! DO NOT MODIFY THESE FUNCTIONS !!!

Tree TreeNew(int (*compare)(Record, Record)) {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    t->root = NULL;
    t->compare = compare;
    return t;
}

void TreeFree(Tree t, bool freeRecords) {
    doTreeFree(t->root, freeRecords);
    free(t);
}

static void doTreeFree(Node n, bool freeRecords) {
    if (n != NULL) {
        doTreeFree(n->left, freeRecords);
        doTreeFree(n->right, freeRecords);
        if (freeRecords) {
            RecordFree(n->rec);
        }
        free(n);
    }
}

////////////////////////////////////////////////////////////////////////
// Functions you need to implement

bool TreeInsert(Tree t, Record rec) {
    bool res = false; // if the record was inserted
    t->root = doTreeInsert(t, t->root, rec, &res);
    return res;
}

Record TreeSearch(Tree t, Record rec) {
    return doTreeSearch(t, t->root, rec);
}

List TreeSearchBetween(Tree t, Record lower, Record upper) {
    return ListNew();
}

Record TreeNext(Tree t, Record rec) {
    return NULL;
}

////////////////////////////////////////////////////////////////////////


///////////////////////////HELPER FUNCTIONS/////////////////////////

// Insert a new node into the tree and rotate if tree is unbalanced using AVL 
// insert


static Node doTreeInsert(Tree t, Node n, Record rec, bool *res) {
    if (n == NULL) {
        *res = true;
        return newNode(rec);
    }

    int cmp = t->compare(rec, n->rec);

    if (cmp < 0) {
        n->left =  doTreeInsert(t, n->left, rec, res);
    } else if (cmp > 0) {
        n->right = doTreeInsert(t, n->right, rec, res);
    } else {
        *res = false;
    }

    // Update the height 
    n->height = 1 + getHeight(n->left) + getHeight(n->right);

    // If tree is unbalance then perform rotatation
    int balance = getHeight(n->left) - getHeight(n->right);

    // Left left case
    if (balance > 1 && t->compare(rec, n->left->rec) < 0)
        return rotateRight(n);

    // Right right case
    else if (balance < -1 && t->compare(rec, n->right->rec) > 0 )
        return rotateLeft(n);

    // Left right case
    else if (balance > 1 && t->compare(rec, n->left->rec) > 0) {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    // Right left case
    else if (balance < -1 && t->compare(rec, n->right->rec) < 0) {
        n->right = rotateRight(n);
        return rotateLeft(n);
    }

    return n;
}


// create a new node
static Node newNode(Record rec) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->left = NULL;
    n->right = NULL;
    n->rec = rec;
    return n;
}

// rotate the tree right
static Node rotateRight(Node root) {
    Node newRoot = root->left;
    if (root == NULL || newRoot == NULL)
        return root;
    root->left = newRoot->right;
    newRoot->right = root;
    return newRoot;
}

// rotate the tree left
static Node rotateLeft(Node root) {
    Node newRoot = root->right;
    if (root == NULL || newRoot == NULL)
        return root;
    root->right = newRoot->left;
    newRoot->left = root;
    return newRoot;
}


// get the height of the node
static int getHeight(Node n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// From lab04
static Record doTreeSearch(Tree t, Node n, Record rec) {
    if (n == NULL) {
        return NULL;
    }

    int cmp = t->compare(rec, n->rec);
    if (cmp < 0) {
        return doTreeSearch(t, n->left, rec);
    } else if (cmp > 0) {
        return doTreeSearch(t, n->right, rec);
    } else {
        return n->rec;
    }
}

