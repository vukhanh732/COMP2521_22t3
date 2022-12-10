
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void listInsert(List l, int value)
{
    Node curr = l->first;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = newNode(value);
}

List findShortestSublist(List l, int start, int end)
{
    List new = ListNew();

    int length = 0;
    Node curr = l->first;
    while (curr != NULL)
    {
        if (curr->value == start)
        {
            Node temp = curr;
            while (temp->next != NULL)
            {
                if (temp->value == end)
                {
                    break;
                }
                listInsert(new, temp->value);
                length++;
                temp = temp->next;
            }
        }
        curr = curr->next;
    }

    return new;
}
