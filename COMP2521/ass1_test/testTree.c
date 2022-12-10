#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHT_NUMBER 8
#define MAX_AIRPORT_NAME  8

typedef struct tree *Tree;
typedef struct node *Node;
typedef struct record *Record;

struct node {
    Record rec;
    Node   left;
    Node   right;

    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary
    int height;

};

struct tree {
    Node root;
    int (*compare)(Record, Record);

    // IMPORTANT: Do not modify the fields above
    // You may add additional fields below if necessary

};

struct record {
    char flightNumber[MAX_FLIGHT_NUMBER + 1];
    char departureAirport[MAX_AIRPORT_NAME + 1];
    char arrivalAirport[MAX_AIRPORT_NAME + 1];
    int departureDay;    // 0 for Monday, ... , 6 for Sunday
    int departureHour;   // Between 0 and 23 (inclusive)
    int departureMinute; // Between 0 to 59 (inclusive)
    int durationMinutes; // Duration of the flight, in minutes
};

void print2DUtil(struct tree *t, int space);
void print2D(struct node *root);
static int compareByFlightNumber(Record r1, Record r2);
Record RecordNew(char *flightNumber,  
                 char *departureAirport, char *arrivalAirport, 
                 int departureDay, int departureHour, int departureMinute,
                 int durationMinutes);
// Function to print binary tree in 2D
// It does reverse inorder traversal


int main() {
     Record recs[] = {
        // this should be inserted
        RecordNew("QF409", "SYD", "MEL", 0,  7,  5,  90),

        // this should not be inserted, because it is exactly the same
        // as the previous record
        RecordNew("QF409", "SYD", "MEL", 0,  7,  5,  90),

        // this should not be inserted even though the duration is
        // different, because the flight number and time are the same,
        RecordNew("QF409", "SYD", "MEL", 0,  7,  5,  91),

        // this should be inserted because the time is different
        RecordNew("QF409", "SYD", "MEL", 0,  7,  6,  90),

        // this should be inserted because the flight number is different
        RecordNew("QF401", "SYD", "MEL", 0,  7,  5,  90),

        // this should be inserted
        RecordNew("VA323", "MEL", "BNE", 6, 11,  0, 110),
    };

    
}



void print2DUtil(Tree t, int space)
{
    
    // Base case
    struct node *root = t->root;
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += 10;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->rec->flightNumber);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(struct node *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

static int compareByFlightNumber(Record r1, Record r2) {
    return RecordGetFlightNumber(r1) - RecordGetFlightNumber(r2);
}

Record RecordNew(char *flightNumber,  
                 char *departureAirport, char *arrivalAirport, 
                 int departureDay, int departureHour, int departureMinute,
                 int durationMinutes)
{
    if (strlen(flightNumber) > MAX_FLIGHT_NUMBER) {
        fprintf(stderr, "error: flight number '%s' is too long\n",
                flightNumber);
        return NULL;
    }
    
    if (strlen(departureAirport) > MAX_AIRPORT_NAME) {
        fprintf(stderr, "error: departure airport name '%s' is too long\n",
                departureAirport);
        return NULL;
    }
    
    if (strlen(arrivalAirport) > MAX_AIRPORT_NAME) {
        fprintf(stderr, "error: arrival airport name '%s' is too long\n",
                arrivalAirport);
        return NULL;
    }

    if (departureDay < 0 || departureDay > 6) {
        fprintf(stderr, "error: invalid departure day '%d'\n",
                departureDay);
        return NULL;
    }

    if (departureHour < 0 || departureHour > 23) {
        fprintf(stderr, "error: invalid departure hour '%d'\n",
                departureHour);
        return NULL;
    }
    
    if (departureMinute < 0 || departureMinute > 59) {
        fprintf(stderr, "error: invalid departure minute '%d'\n",
                departureMinute);
        return NULL;
    }

    if (durationMinutes < 0) {
        fprintf(stderr, "error: invalid duration '%d'\n",
                durationMinutes);
        return NULL;
    }

    Record r = malloc(sizeof(*r));
    if (r == NULL) {
        fprintf(stderr, "error: out of memory\n");
        exit(EXIT_FAILURE);
    }

    strcpy(r->flightNumber, flightNumber);
    strcpy(r->departureAirport, departureAirport);
    strcpy(r->arrivalAirport, arrivalAirport);
    r->departureDay = departureDay;
    r->departureHour = departureHour;
    r->departureMinute = departureMinute;
    r->durationMinutes = durationMinutes;

    return r;
}