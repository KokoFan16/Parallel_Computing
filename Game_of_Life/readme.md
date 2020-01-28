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

![example](https://github.com/KokoFan16/Parallel_Computing/blob/master/Game_of_Life/example.png)

## Compile 

There are two compile mode, one for perfermance printing, and the other for debugging. 

- ```gcc <filename> -std=c99 -o <name> -O3``` (perfermance)
- ```gcc <filename> -std=c99 -o <name> -O3 -DDEBUG_PRINT``` (debugging)

## Usage

```./<name> <N> <max generations>```

## Result
```
kokos-MacBook-Pro:homework1 kokofan$ gcc lifegame.c -o life 
kokos-MacBook-Pro:homework1 kokofan$ ./life 
Usage: ./life <N> <max generations>
kokos-MacBook-Pro:homework1 kokofan$ ./life 100 100
STOP: Max generation has been reached!
Time taken = 0.051962 seconds
```

```
kokos-MacBook-Pro:homework1 kokofan$ gcc lifegame.c -o life -DDEBUG_PRINT
kokos-MacBook-Pro:homework1 kokofan$ ./life 5 5
Initial board
- - - - o - - 
- o - - o - o 
- - - o - - - 
- o - - - - o 
- - - - - - - 
- - - - o - - 
- o - - o - o 

The max generation is 5

Generation 0
Current Board
- - - - o - - 
- o - - o - o 
- - - o - - - 
- o - - - - o 
- - - - - - - 
- - - - o - - 
- o - - o - o 
Alive neighbors
0 1 3 3 3 
1 3 3 4 4 
1 2 2 1 1 
0 0 1 1 2 
1 1 2 1 2 
Next Board 
- - - - - - - 
o - - o o o - 
- - o o - - - 
- - - - - - - 
- - - - - - - 
- - - - - - - 
o - - o o o - 
Compare: next board: -------o--ooo---oo------------------------o--ooo-, current board: ----o---o--o-o---o----o----o-----------o---o--o-o
Compare current board with next: 0

Generation 1
Current Board
- - - - - - - 
o - - o o o - 
- - o o - - - 
- - - - - - - 
- - - - - - - 
- - - - - - - 
o - - o o o - 
Alive neighbors
2 3 4 2 1 
3 3 3 2 1 
2 3 3 2 0 
1 2 2 1 0 
1 1 2 3 3 
Next Board 
o - - - o o - 
- - o - o - - 
- o o o - - o 
- - o o - - - 
- - - - - - - 
o - - - o o - 
- - o - o - - 
Compare: next board: o---oo---o-o---ooo--o--oo----------o---oo---o-o--, current board: -------o--ooo---oo------------------------o--ooo-
Compare current board with next: 0

Generation 2
Current Board
o - - - o o - 
- - o - o - - 
- o o o - - o 
- - o o - - - 
- - - - - - - 
o - - - o o - 
- - o - o - - 
Alive neighbors
4 3 5 3 4 
3 5 4 2 2 
2 2 1 0 1 
2 1 2 2 2 
2 1 3 3 2 
Next Board 
o - - o o o - 
- - o - o - - 
- o - - - - o 
- - o - - - - 
- - - - - - - 
o - - o o o - 
- - o - o - - 
Compare: next board: o--ooo---o-o---o----o--o-----------o--ooo---o-o--, current board: o---oo---o-o---ooo--o--oo----------o---oo---o-o--
Compare current board with next: 0

Generation 3
Current Board
o - - o o o - 
- - o - o - - 
- o - - - - o 
- - o - - - - 
- - - - - - - 
o - - o o o - 
- - o - o - - 
Alive neighbors
3 3 4 3 4 
3 4 3 2 2 
2 2 2 1 1 
2 2 3 4 2 
2 3 5 3 2 
Next Board 
o - o - o o - 
- o o - o - o 
- o - o - - o 
- - o - - - - 
- - - o - - - 
o - o - o o - 
- o o - o - o 
Compare: next board: o-o-oo--oo-o-o-o-o--o--o-------o---o-o-oo--oo-o-o, current board: o--ooo---o-o---o----o--o-----------o--ooo---o-o--
Compare current board with next: 0

Generation 4
Current Board
o - o - o o - 
- o o - o - o 
- o - o - - o 
- - o - - - - 
- - - o - - - 
o - o - o o - 
- o o - o - o 
Alive neighbors
4 3 5 3 5 
2 4 3 2 3 
2 3 3 4 2 
3 5 4 3 3 
5 3 5 4 4 
Next Board 
- - o - - - - 
- - o - o - - 
o o - o - o o 
- - o o - - - 
o o - - o o o 
- - o - - - - 
- - o - o - - 
Compare: next board: --o------o-o--oo-o-oo--oo---oo--ooo--o------o-o--, current board: o-o-oo--oo-o-o-o-o--o--o-------o---o-o-oo--oo-o-o
Compare current board with next: 0
STOP: Max generation has been reached! 
Time taken = 0.000385 seconds
```
