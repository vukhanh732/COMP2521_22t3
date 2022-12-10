#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define COUNT 10

typedef struct node *Node;
typedef struct tree *Tree;

// A binary tree node
struct node {
    int  data;
    Node   left;
    Node   right;

    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary
    int height;
};

struct tree {
    Node root;
    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary

};
// Helper function to allocates a new node
Node newNode(int data)
{
    Node n = malloc(sizeof(*n));
    if (n == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    n->left = NULL;
    n->right = NULL;
    n->height = 0;
    n->data = data;
    return n;
}

void print2DUtil(Node root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(Node root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

Tree TreeNew() {
    Tree t = malloc(sizeof(*t));
    if (t == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    t->root = NULL;
    return t;
}

// Assignment functions
bool TreeInsert(Tree t, int data);
static Node doTreeInsert(Tree t, Node n, int data, bool *res);
static Node rotateRight(Node root);
static Node rotateLeft(Node root);
static int getHeight(Node n);
int TreeSearch(Tree t, int data); 
static int doTreeSearch(Tree t, Node n, int data);
static int TreeNext(Tree t, int data); 
static int doTreeNext(Tree t, Node n, int data, int min_diff, int r);
// Driver program to test above functions
int main()
{
    Tree t = TreeNew();
    TreeInsert(t, 10);
    TreeInsert(t, 20);
    TreeInsert(t, 30);
    TreeInsert(t, 40);
    TreeInsert(t, 50);
    TreeInsert(t, 25);
    TreeInsert(t, 35);
    TreeInsert(t, 45);
    
    print2D(t->root);
    printf("Searching for 100: Found %d\n", TreeSearch(t, 100));
    printf("Test TreeNext: Searching for 9: Found %d\n", TreeNext(t, 9));
    return 0;
}

bool TreeInsert(Tree t, int data) {
    bool res = false; // if the record was inserted
    t->root = doTreeInsert(t, t->root, data, &res);
    return res;
}

static Node doTreeInsert(Tree t, Node n, int data, bool *res) {
   if (n == NULL) {
        *res = true;
        return newNode(data);
    }

    int cmp = (data - n->data);
    if (cmp < 0) {
        n->left = doTreeInsert(t, n->left, data, res);
    } else if (cmp > 0) {
        n->right = doTreeInsert(t, n->right, data, res);
    } else {
        *res = false;
    }

    n->height = 1 + (getHeight(n->left) > getHeight(n->right) ? 
        getHeight(n->left) : getHeight(n->right));

    int balance = getHeight(n->left) - getHeight(n->right);

    if (balance > 1 && data < n->left->data) {
        return rotateRight(n);
    }

    if (balance < -1 && data > n->right->data) {
        return rotateLeft(n);
    }

    if (balance > 1 && data > n->left->data) {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    if (balance < -1 && data < n->right->data) {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    return n;
}

// rotate the tree right and update the heights
static Node rotateRight(Node root) {
    Node newRoot = root->left;
    Node temp = newRoot->right;

    newRoot->right = root;
    root->left = temp;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? 
        getHeight(root->left) : getHeight(root->right));
    newRoot->height = 1 + (getHeight(newRoot->left) > getHeight(newRoot->right) ? 
        getHeight(newRoot->left) : getHeight(newRoot->right));

    return newRoot;
}

// rotate the tree left
static Node rotateLeft(Node root) {
    Node newRoot = root->right;
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

int TreeSearch(Tree t, int data) {
    return doTreeSearch(t, t->root, data);
}

static int doTreeSearch(Tree t, Node n, int data) {
    if (n == NULL) {
        return -1;
    }

    int cmp = (data - n->data);
    if (cmp < 0) {
        return doTreeSearch(t, n->left, data);
    } else if (cmp > 0) {
        return doTreeSearch(t, n->right, data);
    } else {
        return data;
    }
}

static int TreeNext(Tree t, int data) {
    int r = TreeSearch(t, data);
    if (r == -1) {
        // Search for the smallest record that is larger than the given record
        return doTreeNext(t, t->root, data, 290000, r);
    }
    return r;
}
static int doTreeNext(Tree t, Node n, int data, int min_diff, int r ){
    if (n == NULL) {
        return r;
    }
    int cmp = (data - n->data);
    int prev_diff = min_diff;
    min_diff = n->data - data;

    if (min_diff < prev_diff) {
        r = n->data;
    }

    if (cmp < 0) {
        return doTreeNext(t, n->left, data, min_diff, r);
    } else if (cmp > 0) {
        return doTreeNext(t, n->right, data, min_diff, r);
    } 

    return r;
}
