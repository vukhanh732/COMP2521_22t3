#include <stdio.h>
#include "tree.h"

int main(int argc, char* argv[]) {
    Tree t = TreeCreate(1);
    TreeInsert(t, 2);
    TreePrint(t);
    TreeInsert(t, 4);
    TreePrint(t);
    TreeInsert(t, 5);
    TreePrint(t);
    TreeInsert(t, 3);
    TreePrint(t);
    TreeDestroy(t);
    return 0;
}