// COMP2521 Assignment 2

// Written by: Vu Khanh Luu (z5311086)
// Date: 18/11/2022

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *word;
    char *url;
    double pageRank;
    struct node *next;
}List;




int main(int argc, char *argv[]) {

    if (argc != 1) {
        fprintf(stderr, "Please enter arguments correctly");
        return EXIT_SUCCESS;
    }

    // Read words from command line to an array
    int numWords = argc - 1;
    char *words[numWords];
    for (int i = 0; i < numWords; i++) {
        words[i] = argv[i + 1];
    }

    // Go through invertexIndex.txt and add them to a linked list if they are
    // the word we are looking for
    FILE *fp = fopen("invertedIndex.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "Cannot open invertedIndex.txt");
        return EXIT_SUCCESS;
    }

    char temp[1000];
    while (fscanf(fp, "%s", temp) != EOF) {
        for (int i = 0; i < numWords; i++) {
            if (strcmp(temp, words[i]) == 0) {
                while (fscanf(fp, "%s", temp) != '\n') {
                    // Add url to linked list separated by space until \n                
                }
                    
            }
        }
    }
}







