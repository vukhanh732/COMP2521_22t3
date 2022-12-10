typedef struct Node *Tree;

typedef int Item;

Tree TreeCreate(Item it);
void TreeDestroy(Tree t);
Tree TreeInsert(Tree t, Item it);
void TreePrint(Tree t);

