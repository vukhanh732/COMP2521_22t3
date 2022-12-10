
#include "list.h"

int listDeleteLargest(List l) {
	// Base case
	if (l->head == NULL || l->head->next == NULL)
		return 0;

	// Find the largest value in the list
	int largest = l->head->value;
	for (Node curr = l->head; curr != NULL; curr = curr->next) {
		if (curr->value > largest)
			largest = curr->value; 
	}

	// Loop through the list and unlink the first largest value found
	Node prev = NULL;
	for (Node curr = l->head; curr != NULL; curr = curr->next) {
		if (curr->value == largest && prev != NULL) {
			prev->next = curr->next;
			free(curr);
			break;
		} else if (curr->value == largest && prev == NULL){
			Node temp = curr;
			curr = curr->next;
			free(temp);
			l->head = curr;
		}
		prev = curr;
	}
	return largest;
}

