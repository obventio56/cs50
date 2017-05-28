/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];
int d;
// board's dimension

// prototypes
void clear(void);
void greet(void);
void init(int d);
void draw(int d);
bool move(int tile, int d);
bool won(int d);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init(d);

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw(d);

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won(d))
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile, d))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */
void init(int d)
{
    int c = 1;
    int n = d*d - 1;
    if (n%2 == 0)
    {   
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d && ((j+1)*(i+1)) != (d*d); j++)
            {   
                board[i][j] = n + 1 - c;
                c++;
            } 
        }
        board[d-1][d-1] = 82;
    }
    else
    {  
         
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d && ((j+1)*(i+1)) != (d*d); j++)
            {   
                board[i][j] = n + 1 - c;
                c++;
            } 
        }
        board[d-1][d-1] = 82;
    
        board[d-1][d-3] = 1;
        board[d-1][d-2] = 2;
    }
}
/**
 * Prints the board in its current state.
 */
void draw(int d)
{
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 82)
            {
                printf("_ ");
            }
            else
            {
                if (board[i][j] > 9 )
                {
                printf("%d ", board[i][j]);
                }
                else
                {
                printf("%d  ", board[i][j]);
                }
            }
        }
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile, int d)
{
    bool s;
    int c = 0;
    int r, t;
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                r = i;
                t = j;
            }
        }
    }
    if (board[r+1][t] == 82)
    {
        board[r+1][t] = tile;
        board[r][t] = 82;
        s = true;
    }  
    else
    {
        c++;
    }
    if (board[r-1][t] == 82)
    {
        board[r-1][t] = tile;
        board[r][t] = 82;
        s = true;
    } 
    else
    {
        c++;
    } 
    if (board[r][t-1] == 82)
    {
        board[r][t-1] = tile;
        board[r][t] = 82;
        s = true;
    } 
    else
    {
        c++;
    } 
    if (board[r][t+1] == 82)
    {
        board[r][t+1] = tile;
        board[r][t] = 82;
        s = true;
    } 
    else
    {
        c++;
    }
    if (c == 4)
    { 
    s = false;
    }
    else
    {
    }
    return s;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(int d)
{
    bool s;
    int c= 0;
    if (board[0][0] == 86)
    {
        c++;
    }
    else
    {
        s = false;
    }
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if ((i+1)*(j+1) == 1)
            {
            }
            else
            {
                if (j == 0)
                {
                    if(board[i][j] > board[i -1][j + 2])
                    {
                        c++;
                    }
                    else
                    {
                        s = false;
                    }
                }
                else 
                {
                    if (board[i][j] > board[i][j - 1])
                    {
                        c++;
                    }
                    else
                    {
                        s = false;
                    }
                }   
            }   
        }
    }
    if (c == (d*d))
    {
        s = true;
    }
    return s;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
