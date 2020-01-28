# Game of Life

## Problem Specification 

The "Game of Life" is a well-known cellular automaton devised by John Horton Conway, a Cambridge mathematician. The Game of Life is a board game that consists of a two-dimensional array of cells. Each cell can hold an organism and has eight neighboring cells (left, right, top, bottom, top-left, bottom-right, top-right, and bottom-left). Assume that the array wraps around in both dimensions, which means that the left boundary is adjacent to the right boundary and the top boundary is adjacent to the bottom boundary (often referred to as periodic boundary conditions). Each cell can be in two states: alive or dead. The game starts with an initial state and cells either live, die or multiply in the next iteration (generation) according to the following rules:

- If a cell is “alive” in the current generation, then depending on its neighbor’s state, in the next generation the cell will either live or die based on the following conditions:
   - Each cell with one or no neighbor dies, as if by loneliness.
   - Each cell with four or more neighbors dies, as if by overpopulation. 
   - Each cell with two or three neighbors survives.
- If a cell is “dead” in the current generation, then if there are exactly three neighbors "alive" then it will change to the "alive" state in the next generation, as if the neighboring cells gave birth to a new organism.

The above rules apply at each iteration (generation) so that the cells evolve, or change state from generation to generation. Also, all cells are affected simultaneously in a generation (i.e., for each cell you need to use the value of the neighbors in the current iteration to compute the values for the next generation).

The program must take the size of the board and the maximum number of generations as command-line arguments. The game will end when there is no change in the board between two generations or when the maximum generation count is reached.

## Required Language

C Language 

## Hint

Instead of allocation a two-dimensional array of size N X N, where N is the size of the board, allocate a two-dimensional array of size (N+2) X (N+2). This will create an extra set of cells around the board, commonly referred to as ghost cells. Initialize these ghost cells with the corresponding values from the opposite boundary (by following the steps shown in the diagram). Having these ghost cells avoids the need to check if a cell is along the boundary and makes the computation of number of neighboring cells "alive" simpler. Also, note that you will require two arrays, one for the values from the previous generation and one for the new values computed in the current generation. You have to copy the ghost cells at the end of each iteration to reflect the new values along the boundaries.

Here is an example:

![example]()

## Compile 

There are two compile mode, one for perfermance printing, and the other for debugging. 

- ```gcc <filename> -std=c99 -o <name> -O3``` (perfermance)
- ```gcc <filename> -std=c99 -o <name> -O3 -DDEBUG_PRINT``` (debugging)



