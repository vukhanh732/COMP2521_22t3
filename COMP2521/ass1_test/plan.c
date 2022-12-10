//Part 1 functions to implement:


//***************************************************************

/**
 * Inserts a record into the tree.
 * Returns true if the record was inserted into the tree, and false if
 * the tree already contains a record that compares equal to the given
 * record.
 * The time complexity of this function must be O(log n).
 */
bool TreeInsert(Tree t, Record rec) {
   // Use AVL tree insert in week 4
   // Create 3 functions: newNode() ,rotateLeft(Tree) and rotateRight(Tree)

}

//Example for this function:

bool TreeInsert(Tree t, Record rec) {
    bool res = false; // if the record was inserted
    t->root = doTreeInsert(t, t->root, rec, &res);
    return res;
}

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

    if (balance < 1 && )
    

    return n;
}


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
//***********************************************************************



/**
 * Searches the tree for a record that compares equal to the given
 * record. Returns the record if it exists, and NULL otherwise.
 * The time complexity of this function must be O(log n).
 */
Record TreeSearch(Tree t, Record rec) {
    // Use TreeSearch function
}


//***********************************************************************
/**
 * Searches for all records between the two given records (inclusive)
 * and returns the records in a list in ascending order. Returns an
 * empty list if there are no such records.
 * The time complexity of this function must be O(m + log n), where m is
 * the length of the returned list.
 */
List TreeSearchBetween(Tree t, Record lower, Record upper) {
    return ListNew();
}

// Example:
List TreeSearchBetween(Tree t, Record lower, Record upper) {
    List l = ListNew();
    doTreeSearchBetween(t, t->root, lower, upper, l);
    return l;
}


// n - the current node
// l - a list to accumulate results
static void doTreeSearchBetween(Tree t, Node n, Record lower,
                                Record upper, List l) {
    // TODO: Complete this function

    // Base case
    if (n == NULL) return;
    int cmp1 = t->compare(n->rec, lower);
    int cmp2 = t->compare(n->rec, upper);

    // Recursive case 
    if (cmp1 > 0) doTreeSearchBetween(t, n->left, lower, upper, l);
    if (cmp1 >= 0 && cmp2 <= 0) ListAppend(l, n->rec);
    if (cmp2 < 0) doTreeSearchBetween(t, n->right, lower, upper, l);

      
}
//***********************************************************************


/**
 * Returns the smallest record greater than or equal to the given record,
 * or NULL if there is no such record.
 * The time complexity of this function must be O(log n).
 */
Record TreeNext(Tree t, Record rec) {
    //Use tree search between with lowerbound = rec, upperbound = max;
}