// Implementation of the Queue ADT using a circular array

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

#define DEFAULT_SIZE 16 // DO NOT change this line

// DO NOT modify this struct
struct queue
{
	Item *items;
	int size;
	int capacity;
	int frontIndex;
};

/**
 * Creates a new empty queue
 */
Queue QueueNew(void)
{
	Queue q = malloc(sizeof(*q));
	if (q == NULL)
	{
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->items = malloc(DEFAULT_SIZE * sizeof(Item));
	if (q->items == NULL)
	{
		fprintf(stderr, "couldn't allocate Queue");
		exit(EXIT_FAILURE);
	}

	q->size = 0;
	q->capacity = DEFAULT_SIZE;
	q->frontIndex = 0;
	return q;
}

/**
 * Frees all resources associated with the given queue
 */
void QueueFree(Queue q)
{
	free(q->items);
	free(q);
}

/**
 * Adds an item to the end of the queue
 */
void QueueEnqueue(Queue q, Item it)
{
	// If queue is empty
	if (QueueIsEmpty(q))
	{
		q->items[0] = it;
		q->size++;
		q->frontIndex = 0;
		q->capacity = DEFAULT_SIZE;
	}
	else
	{
		if (q->size == q->capacity)
		{
			// Queue Resize
			q->capacity *= 2;
			q->items = realloc(q->items, q->capacity * sizeof(Item));

			// Relocate the front Index and the rest of the array to the correct index

			// For example: For array queue of capacity 4
			//  v
			// [1][2][3][4] after resizing to capacity 8 will be
			//			v
			// [][][][][1][2][3][4]
			for (int i = q->frontIndex, j = 0; j <= q->size; j++) {
				int newIndex = (i + q->size) % q->capacity;
				q->items[newIndex] = q->items[i];
				i++;
			}
			q->frontIndex = (q->frontIndex + q->size) % q->capacity;

			// Enqueue operation
			int position = (q->size + q->frontIndex) % q->capacity;
			q->items[position] = it;
			q->size++;
		}
		else
		{
			// 											  v
			// Enqueue to correct position. For example: [1][2][][]
			// + 3 will be insert into index 2 because (2 + 0) % 4 = 2
			//  v
			// [1][2][3][]						   
			//						   v
			// For array queue [2][][][1] + 3 will be insert into index
			// (2 + 3) % 4 = 1;

			int position = (q->size + q->frontIndex) % q->capacity;
			q->items[position] = it;
			q->size++;
		}
	}
}

/**
 * Removes an item from the front of the queue and returns it
 * Assumes that the queue is not empty
 */
Item QueueDequeue(Queue q)
{
	assert (q != NULL);
	Item remove = q->items[q->frontIndex];
	q->frontIndex++;
	if (q->frontIndex >= q->capacity)
		q->frontIndex -= q->capacity;
	q->size--;
	return remove;
}

/**
 * Gets the item at the front of the queue without removing it
 * Assumes that the queue is not empty
 */
Item QueueFront(Queue q)
{
	assert(q->size > 0);

	return q->items[q->frontIndex];
}

/**
 * Gets the size of the given queue
 */
int QueueSize(Queue q)
{
	return q->size;
}

/**
 * Returns true if the queue is empty, and false otherwise
 */
bool QueueIsEmpty(Queue q)
{
	return q->size == 0;
}

/**
 * Prints the items in the queue to the given file with items space-separated
 */
void QueueDump(Queue q, FILE *fp)
{
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++)
	{
		fprintf(fp, "%d ", q->items[i]);
	}
	fprintf(fp, "\n");
}

/**
 * Prints out information for debugging
 */
void QueueDebugPrint(Queue q)
{
	for (int i = q->frontIndex, j = 0; j < q->size; i = (i + 1) % q->capacity, j++)
	{
		printf("%d (index: %d) ", q->items[i], i);
	}
	printf("\n");
}
