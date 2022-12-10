
#include "list.h"

void reverseDLList(List l) {
	// Use curr for looping
	Node curr = l->first;
	Node temp;

	// Swap prev and next pointer. Looping until NULL
	while (curr != NULL) {
		temp = curr->prev;
		curr->prev = curr->next;
		curr->next = temp;

		curr = curr->prev;
	}

	// Swap l->first and l->last
	temp = l->first;
	l->first = l->last;
	l->last = temp;
}

