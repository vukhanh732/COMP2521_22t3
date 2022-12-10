
#include "list.h"
#include <stdbool.h>
#include <stdlib.h>

int testOrder(List l);

bool listIsOrdered(List l) {
	// TODO
	if (l->head == NULL || l->head->next == NULL) 
		return true;
	
	Node curr = l->head->next;
	Node prev = l->head;;

	int flag = testOrder(l);
	if (flag == 0) return true;

	// Increasing case
	if (flag > 0) {
		while (curr != NULL) {
			if (curr->value >= prev->value) {
			} else {
				return false;
			}
			prev = curr;
			curr = curr->next;
		}
	}
	
	// Descreasing case
	if (flag < 0) {
		while (curr != NULL) {
			if (curr->value <= prev->value) {
			} else {
				return false;
			}
			prev = curr;
			curr = curr->next;
		}
	}

	return true;
}

// Function to test for list order. Increasing or Descreasing
int testOrder(List l) {
	Node curr = l->head->next;
	Node prev = l->head;
	int n = 0;

	while (curr != NULL) {
		n = curr->value - prev->value;
		if (n != 0) break;
		prev = curr;
		curr = curr->next;
	}

	return n;
}