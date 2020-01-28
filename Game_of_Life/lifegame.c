/******************************************************************************
 *  Name: Ke Fan                                                               *
 *  BlazerId: kefan                                                            *
 *  Course Section: CS 732                                                     *
 *  Homework #: 1 (Game of life)                                               *
 *  Date: January 23, 2020                                                     *
 *                                                                             *
 *                                                                             *
 *  To Compile: gcc lifegame.c -o life (to print matrices add -DDEBUG_PRINT)   *
 *  To run: ./life <size> <the number of max generations>                      *
 *                                                                             *
 ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


char **allocBoard(int N);
void randomInitBoard(char **b, int N);
void copyGhostCell(char **b, int N);
void printBoard(char **b, int N);
void copyBoard(char **next, char **current, int N);
void nextBoard(char **next, int N);
bool compareGeneration(char **next, char **current, int N);
double gettime();


int main(int argc, char **argv)
{
    // Exit program if there are no required arguments
    if (argc != 3)
    {
        printf("Usage: %s <N> <max generations> \n", argv[0]);
        return -1;
    }
    
    // Get arguments from users <size N> and <then number of max generations>
    int N = atoi(argv[1]);
    int maxGeneration = atoi(argv[2]);
    
    // Get start time
    double starttime = gettime();
    
    // Initial board randomly
    char **board = allocBoard(N);
    randomInitBoard(board, N);
    copyGhostCell(board, N);
    
    // Debug: print initial board
    #ifdef DEBUG_PRINT
    printf("Initial board\n");
    printBoard(board, N);
    printf("\nThe max generation is %d\n", maxGeneration);
    #endif
    
    // Copy current board to next board
    char **next = allocBoard(N);
    copyBoard(next, board, N);
    
    // Game of life main loop
    int generates = 0;
    while (1) {
        
        // Game ends when max generation is reached and print out duration
        if (generates > maxGeneration - 1) {
            // Get end time
            double endtime = gettime();
            printf("STOP: Max generation has been reached! \n");
            printf("Time taken = %lf seconds\n", endtime-starttime);
            free(next);
            free(board);
            return -1;
        }
        
        // Debug: print generation number and current board
        #ifdef DEBUG_PRINT
        printf("\nGeneration %d\n", generates);
        printf("Current Board\n");
        printBoard(board, N);
        #endif
        
        // Get next board by game rules
        nextBoard(next, N);
        copyGhostCell(next, N);
        
        generates += 1;
        
        // Debug: print next board
        #ifdef DEBUG_PRINT
        printf("Next Board \n");
        printBoard(next, N);
        #endif

        /* Compare current board with next board.
           Game will end if there is no change between two generations.*/
        bool compare = compareGeneration(next, board, N);
        if ( compare == 1)
        {
            double endtime = gettime();
            printf("STOP: There is no change between two generations! \n");
            printf("Time taken = %lf seconds\n", endtime-starttime);
            free(next);
            free(board);
            return -1;
        }
        
        // Debug: print compare result
        #ifdef DEBUG_PRINT
        printf("Compare current board with next: %d\n", compare);
        #endif
        
        // Copy the next board to current board
        copyBoard(board, next, N);
    }
    
    return 0;
}


// allocate (N+2) * (N*2) memory for game board
char **allocBoard(int N)
{
    int i;
    char *p, **b;
    
    // p points to a (N*2) * (N*2) array
    p = (char *)malloc((N+2)*(N+2)*sizeof(char) + 1);
    // b points to (N+2) p
    b = (char **)malloc((N+2)*sizeof(char*));
    
    if (p == NULL || b == NULL)
        printf("Error allocating memory\n");
    
    /* for row major storage */
    for (i = 0; i < (N+2); i++)
        b[i] = &p[i*(N+2)];
    
    return b;
}


// Initial board randomly
void randomInitBoard(char **b, int N)
{
    // Generate random start point
    srand((unsigned int)time(NULL));
    // Initial N*N board randomly (except ghost cells)
    for (int i = 1; i < N+1; i++)
    {
        for (int j = 1; j < N+1; j++)
        {
            // Generate random number between (0,10)
            int cell = rand()%10;
            // 'o' means alive cell, '-' means dead
            if (cell < 3)
                b[i][j] = 'o';
            else
                b[i][j] = '-';
        }
    }
}

// Copy ghose cell with the corresponding values from the opposite boundary
void copyGhostCell(char **b, int N)
{
    // Copy vertical ghost cells
    for (int i = 1; i < N+1; i++)
    {
        b[i][0] = b[i][N];
        b[i][N+1] = b[i][1];
    }
    
    // Copy horizontal ghost cells
    for (int j = 0; j < N+2; j++)
    {
        b[0][j] = b[N][j];
        b[N+1][j] = b[1][j];
    }
    
    b[N+1][N+2] = '\0';
}

// Print board
void printBoard(char **b, int N)
{
    for (int i = 0; i < N+2; i++)
    {
        for(int j = 0; j < N+2; j++)
        {
            printf("%c ", b[i][j]);
        }
        printf("\n");
    }
}


// Copy one board to another board
void copyBoard(char **next, char **current, int N)
{
    for(int i = 0; i < N+2; i++)
        strncpy(next[i], current[i], (N+2));
}


/* Generate next board:
    1. Each cell with one or no neighbor dies, as if by loneliness.
    2. Each cell with four or more neighbors dies, as if by overpopulation.
    3. Each cell with two or three neighbors survives.
    4. If a cell is “dead” in the current generation, then if there are exactly three neighbors "alive" then it will change to the "alive" state in the next generation.
 */
void nextBoard(char **next, int N)
{

    #ifdef DEBUG_PRINT
    printf("Alive neighbors\n");
    #endif
    
    for (int i = 1; i < N+1; i++)
    {
        for(int j = 1; j < N+1; j++)
        {
            int alives = 0;
            
            // Get 8 neighbors
            char neighbors[8] =
            {   next[i-1][j-1], next[i-1][j], next[i-1][j+1], next[i][j-1],
                next[i][j+1], next[i+1][j-1], next[i+1][j], next[i+1][j+1]
            };
            
            // Calulate the number of alive neighbors
            for (int k = 0; k < 8; k++)
            {
                if (neighbors[k] == 'o')
                    alives += 1;
            }
            
            // Debug: print the number of alive neighbors
            #ifdef DEBUG_PRINT
            printf("%d ", alives);
            #endif
            
            // Rules of next generation
            if (next[i][j] == 'o' && alives < 2)
                next[i][j] = '-';
            if (next[i][j] == 'o' && alives > 3)
                next[i][j] = '-';
            if (next[i][j] == '-' && alives == 3)
                next[i][j] = 'o';
        }
        
        #ifdef DEBUG_PRINT
        printf("\n");
        #endif
    }
}


// Compare two generations
bool compareGeneration(char **next, char **current, int N)
{
    // Debug: print two comparison strings
    #ifdef DEBUG_PRINT
    printf("Compare: next board: %s, current board: %s\n", next[0], current[0]);
    #endif
    
    if (strcmp(next[0], current[0]) == 0)
        return true;
    return false;
}


// Get current system time;
double gettime()
{
    struct timeval tval;
    gettimeofday(&tval, NULL);
    return( (double)tval.tv_sec + (double)tval.tv_usec/1000000.0 );
}

