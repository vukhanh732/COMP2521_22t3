// BFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Queue.h"

// Use BFS to find a path from start to finish
bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    Cell start = MazeGetStart(m);
    int height = MazeHeight(m);
    int width = MazeWidth(m);

    // create a queue
    Queue q = QueueNew();

    // enqueue the start cell
    QueueEnqueue(q, start);


    bool **visited = createBoolMatrix(height, width);
    Cell **parent = createCellMatrix(height, width);

    // Traverse the maze
    while (!QueueIsEmpty(q)) {
        Cell curr = QueueDequeue(q);

        // Check if the cell is visited // Can do wall check here instead 
        if (visited[curr.row][curr.col] == true) {
            continue;
        }

        // If cell is not visited, mark it as visited
        bool res = MazeVisit(m, curr);
        visited[curr.row][curr.col] = true;

        // Check if the cell is the finish cell
        if (res == true) {
           while (curr.row != start.row || curr.col != start.col) {
               MazeMarkPath(m, curr);
               printf("Marking (%d, %d)", curr.row, curr.col);
               curr = parent[curr.row][curr.col];
           }
            MazeMarkPath(m, start);
            
            // Free the memory // Use flag and free at the end
            freeBoolMatrix(visited);
            freeCellMatrix(parent);
            QueueFree(q);
            return true;
        }

        // If the cell is not the finish cell, enqueue its neighbours 
        Cell upper = {curr.row - 1, curr.col};
        if (curr.row > 0 && MazeIsWall(m, upper) == false 
            && visited[upper.row][upper.col] == false) {
                Cell up = {curr.row - 1, curr.col};
                printf("Enqueueing (%d, %d)", up.row, up.col);
                QueueEnqueue(q, up);
                parent[up.row][up.col] = curr;
        }

        Cell lower = {curr.row + 1, curr.col};
        if (curr.row < height - 1 && MazeIsWall(m, lower) == false 
            && visited[lower.row][lower.col] == false) {
                Cell down = {curr.row + 1, curr.col};
                printf("Enqueueing (%d, %d)", down.row, down.col);
                QueueEnqueue(q, down);
                parent[down.row][down.col] = curr;
        }

        Cell left = {curr.row, curr.col - 1};
        if (curr.col > 0 && MazeIsWall(m, left) == false 
            && visited[left.row][left.col] == false) {
                Cell left = {curr.row, curr.col - 1};
                printf("Enqueueing (%d, %d)", left.row, left.col);
                QueueEnqueue(q, left);
                parent[left.row][left.col] = curr;
        }

        Cell right = {curr.row, curr.col + 1};
        if (curr.col < width - 1 && MazeIsWall(m, right) == false 
            && visited[right.row][right.col] == false) {
                Cell right = {curr.row, curr.col + 1};
                printf("Enqueueing (%d, %d)", right.row, right.col);
                QueueEnqueue(q, right);
                parent[right.row][right.col] = curr;
        }

    }

    // Free the memory
    freeBoolMatrix(visited);
    freeCellMatrix(parent);
    QueueFree(q);
    return false;
}
