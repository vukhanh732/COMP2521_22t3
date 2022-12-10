
#include "list.h"

int numDupesInOrderedList(List l) {
	// TODO

	// Base case
	if (l->head == NULL || l->head->next == NULL) 
		return 0;

	// Make curr = head and duplicate = first element
	Node curr = l->head;
	int count = 0;
	int dup = curr->value;

	// If the next element is different from prev make that new element the duplicate
	while (curr->next != NULL) {
		if (curr->next->value != dup)
			dup = curr->next->value;
		else 
			count++;
		curr = curr->next;
	}
	return count;
}

