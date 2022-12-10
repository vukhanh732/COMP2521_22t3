// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

bool solve(Maze m) {
    // TODO: Complete this function
    //       Feel free to add helper functions
    Cell start = MazeGetStart(m);
    int height = MazeHeight(m);
    int width = MazeWidth(m);

    Stack s = StackNew();

    StackPush(s, start);

    bool **visited = createBoolMatrix(height, width);
    Cell **parent = createCellMatrix(height, width);

    while (!StackIsEmpty(s)) {
        Cell curr = StackPop(s);
        
        if (visited[curr.row][curr.col] == true) {
            continue;
        }

        bool res = MazeVisit(m, curr);
        visited[curr.row][curr.col] = true;

        if (res == true) {
            while (curr.row != start.row || curr.col != start.col) {
                MazeMarkPath(m, curr);
                curr = parent[curr.row][curr.col];
            }
            MazeMarkPath(m, start);

            // free memory
            freeBoolMatrix(visited);
            freeCellMatrix(parent);
            StackFree(s);
            return true;

        }

        Cell upper = {curr.row - 1, curr.col};
        if (curr.row > 0 && MazeIsWall(m, upper) == false 
            && visited[upper.row][upper.col] == false) {
                Cell up = {curr.row - 1, curr.col};
                StackPush(s, up);
                parent[up.row][up.col] = curr;
        }

        Cell lower = {curr.row + 1, curr.col};
        if (curr.row < height - 1 && MazeIsWall(m, lower) == false 
            && visited[lower.row][lower.col] == false) {
                Cell down = {curr.row + 1, curr.col};
                StackPush(s, down);
                parent[down.row][down.col] = curr;
        }

        Cell left = {curr.row, curr.col - 1};
        if (curr.col > 0 && MazeIsWall(m, left) == false 
            && visited[left.row][left.col] == false) {
                Cell l = {curr.row, curr.col - 1};
                StackPush(s, l);
                parent[l.row][l.col] = curr;
        }

        Cell right = {curr.row, curr.col + 1};
        if (curr.col < width - 1 && MazeIsWall(m, right) == false 
            && visited[right.row][right.col] == false) {
                Cell r = {curr.row, curr.col + 1};
                StackPush(s, r);
                parent[r.row][r.col] = curr;
        }
    }

    // free memory
    freeBoolMatrix(visited);
    freeCellMatrix(parent);
    StackFree(s);

    return false;
}

