#include <stdbool.h>
#include "list.h"

// Insert at head of the list
void listInsert(List l, int data) {
	Node n = newNode(data);
	n->next = l->head;
	l->head = n;
}

// Check if value already existed in the list. True if it is, false if it is not
int alreadyInList(List l, int data) {
	for (Node curr = l->head; curr != NULL; curr = curr->next) {
		if (curr->value == data)
			return true;
	}
	return false;
}

List listSetIntersection(List s1, List s2) {
	// TODO
	List l = newList();
	List k = newList();

	for (Node curr = s1->head; curr != NULL; curr = curr->next) {
		listInsert(l, curr->value);
	}

	// Check if the element is already in list l, if not then insert it
	for (Node curr = s2->head; curr != NULL; curr = curr->next) {
		if (alreadyInList(l, curr->value))
			listInsert(k, curr->value);
	}

	freeList(l);	
	return k;
}

