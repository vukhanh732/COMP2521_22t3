
#include <stdio.h>
#include <stdlib.h>

#include "Queue.h"

int main(void)
{
	Queue q = QueueNew();

	// TODO
	// Write a benchmark test to demonstrate the difference in
	// efficiency between ArrayQueue and CircularArrayQueue

	// Enqueue random numbers 100,000 times
	for (int i = 0; i < 100000; i++)
	{
		QueueEnqueue(q, rand());
	}

	// Dequeue
	for (int i = 0; i < 100000; i++)
	{
		QueueDequeue(q);
	}

	QueueFree(q);
}

/*
Paste the results of the time commands here:

./benchmarkArrayQueue

real    1m4.165s
user    1m3.028s
sys     0m1.128s

./benchmarkCircularArrayQueue

real    0m0.032s
user    0m0.016s
sys     0m0.004s

*/
