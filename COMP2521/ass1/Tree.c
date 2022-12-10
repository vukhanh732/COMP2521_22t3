// Implementation of the Tree ADT

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "Record.h"
#include "Tree.h"

#define INT_MAX 2147483647

typedef struct node *Node;
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
static void doTreeSearchBetween(Tree t, Node n, Record lower,
                                Record upper, List l);
static Record doTreeNext(Tree t, Node n, Record rec, int min_diff, Record r);
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
    List l = ListNew();
    doTreeSearchBetween(t, t->root, lower, upper, l);
    return l;
}

// Search for a record in the tree, return the record if found
// if not found return the smallest record that 
// is larger than the given record. 
Record TreeNext(Tree t, Record rec) {
    Record r = TreeSearch(t, rec);
    if (r == NULL) {
        // Search for the smallest record that is larger than the given record
        return doTreeNext(t, t->root, rec, INT_MAX, r);
    }
    return r;
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

    // Normal BST insert
    int cmp = t->compare(rec, n->rec);
    if (cmp < 0) {
        n->left = doTreeInsert(t, n->left, rec, res);
    } else if (cmp > 0) {
        n->right = doTreeInsert(t, n->right, rec, res);
    } else {
        *res = false;
    }

    // Update the height 
    n->height = 1 + (getHeight(n->left) > getHeight(n->right) ? 
        getHeight(n->left) : getHeight(n->right));

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
// Code from lab04
static Node newNode(Record rec) {
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->left = NULL;
    n->right = NULL;
    n->rec = rec;
    n->height = 0;
    return n;
}

// rotate the tree right
static Node rotateRight(Node root) {
    // New root is the left child of the current root
    Node newRoot = root->left;

    if (newRoot == NULL || root == NULL) {
        return root;
    }

    Node temp = newRoot->right;
    // New root's right child is the current root
    newRoot->right = root;

    // Current root's left child is the temp node
    root->left = temp;

    // Update the height
    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? 
        getHeight(root->left) : getHeight(root->right));

    newRoot->height = 1 + (getHeight(newRoot->left) > getHeight(newRoot->right) ?
        getHeight(newRoot->left) : getHeight(newRoot->right));
    
    return newRoot;
}

// rotate the tree left
static Node rotateLeft(Node root) {
    Node newRoot = root->right;

    if (newRoot == NULL || root == NULL) {
        return root;
    }

    Node temp = newRoot->left;
    newRoot->left = root;
    root->right = temp;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? 
        getHeight(root->left) : getHeight(root->right));
    newRoot->height = 1 + (getHeight(newRoot->left) > getHeight(newRoot->right) ? 
        getHeight(newRoot->left) : getHeight(newRoot->right));

    return newRoot;
}


// get the height of the node
static int getHeight(Node n) {
    if (n == NULL)
        return 0;
    return n->height;
}


// Code from lab04
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


// Code from lab04
static void doTreeSearchBetween(Tree t, Node n, Record lower,
                                Record upper, List l) {
    // Base case
    if (n == NULL) return;
    int cmp1 = t->compare(n->rec, lower);
    int cmp2 = t->compare(n->rec, upper);

    // Recursive case 
    if (cmp1 > 0) doTreeSearchBetween(t, n->left, lower, upper, l);
    if (cmp1 >= 0 && cmp2 <= 0) ListAppend(l, n->rec);
    if (cmp2 < 0) doTreeSearchBetween(t, n->right, lower, upper, l);
      
}

static Record doTreeNext(Tree t, Node n, Record rec, int min_diff, Record r) {

    if (t == NULL) {
        return NULL;
    }

    if (n == NULL) {
        return r;
    }
    int cmp = t->compare(rec, n->rec);
    int prev_diff = min_diff;
    min_diff = t->compare(n->rec, rec);

    // Find the record with the smallest difference
    if (min_diff < prev_diff)
        r = n->rec;

    // If the given record is smaller than the current record then go left
    if (cmp < 0) {
        return doTreeNext(t, n->left, rec, min_diff, r);
    } else if (cmp > 0) {
        return doTreeNext(t, n->right, rec, min_diff, r);
    } 

    return r;
}