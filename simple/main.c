#include <stdio.h>
#include <stdbool.h>

#define SIZE_X 9
#define SIZE_Y 9

void print_Sudoku(int Sudoku[SIZE_X][SIZE_Y])
{
    char v_space[3] = " | "; //vertical separator
    char h_space[3] = "---"; //horizontal separator
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            printf("[%d]", Sudoku[i][j]); //output element
            if (((j + 1) % 3 == 0) && j < SIZE_Y-1)
            {
                printf("%.3s", v_space); //creates vertical separator after every 3 separators but not at the board edges 
            }

        }
        putchar('\n');

        if (((i + 1) % 3 == 0) && i < SIZE_X-1)
        {
            for (int k = 0; k < (SIZE_Y+2); k++)
            {
                printf("%.3s", h_space); //creates horizontal separator after every 3 separators but not at the board edges 
            }
            putchar('\n');
        }
    }
}

bool check_entry(int Sudoku[SIZE_X][SIZE_Y], int pos_x, int pos_y)
{
    int check_x = 0; //tests first row
    int check_y = 0; //tests first column
    int check_area = 0; //tests first box

    //iterates through each row
    //checks each entry is correct
    for (int i = 0; i < SIZE_X; i++)
    {
        if (Sudoku[i][pos_x] == Sudoku[pos_y][pos_x])
        {
            check_x++;
        }
        if (Sudoku[pos_y][i] == Sudoku[pos_y][pos_x])
        {
            check_y++;
        }
    }

    //iterates through each box
    //sect_x corresponds to either the first, second, or third horizontal box (if second: 3 numbers are to the left, if third: 6 numbers are to the left) 
    //sect_y corresponds to either the first, second, or third vertical box (if second: 3 numbers are above, if third: 6 numbers are above)
    int sect_x = 0;
    int sect_y = 0;
    //assigns the position of each number in terms of which box it is in (based on rules stated above)
    switch(pos_x)
    {
        case 0: sect_x = 0; break;
        case 1: sect_x = 0; break;
        case 2: sect_x = 0; break;
        case 3: sect_x = 3; break;
        case 4: sect_x = 3; break;
        case 5: sect_x = 3; break;
        case 6: sect_x = 6; break;
        case 7: sect_x = 6; break;
        case 8: sect_x = 6; break;
        default: sect_x = -1; break;
    }

    switch(pos_y)
    {
        case 0: sect_y = 0; break;
        case 1: sect_y = 0; break;
        case 2: sect_y = 0; break;
        case 3: sect_y = 3; break;
        case 4: sect_y = 3; break;
        case 5: sect_y = 3; break;
        case 6: sect_y = 6; break;
        case 7: sect_y = 6; break;
        case 8: sect_y = 6; break;
        default: sect_y = -1; break;
    }

    if (sect_y == -1 || sect_x == -1)
    {
        printf("Error- Unidentified box");
        return false;
    }
    for (int i = sect_x; i <= sect_x + 2; i++)
    {
        for (int j = sect_y; j <= sect_y + 2; j++)
        {
            if (Sudoku[j][i] > 0)
            {
                if (Sudoku[j][i] == Sudoku[pos_y][pos_x])
                {
                    check_area++;
                }
            }
        }
    }


    if (check_x > 1)
    {
        return false;
    }
    if (check_y > 1)
    {
        return false;
    }
    if (check_area > 1)
    {
        return false;
    }
    return true;
}

int solve_Sudoku(int Sudoku[SIZE_X][SIZE_Y], int pos_x, int pos_y)
{
    //rows are processed before columns

    if (pos_x == 9) //iterates through each row
    {
        pos_x = 0;
        pos_y++;
    }

    if (Sudoku[pos_y][pos_x] == 0)
    {
        for (int i = 1; i <= 9; i++)
        {
            Sudoku[pos_y][pos_x] = i;
            if (check_entry(Sudoku, pos_x, pos_y))
            {
                if ((pos_x == 8) && (pos_y == 8))
                {
                    if (check_entry(Sudoku, pos_x, pos_y))
                    {
                        return 0;
                    }
                } else {
                    if (solve_Sudoku(Sudoku, pos_x+1, pos_y) == 0)
                    {
                        return 0;
                    }
                }
            }
        }
    } else {
        if ((pos_x == 8) && (pos_y == 8))
        {
            if (check_entry(Sudoku, pos_x, pos_y))
            {
                return 0;
            } else {
                return -1;
            }
        } else {
            if (solve_Sudoku(Sudoku, pos_x+1, pos_y) == 0)
            {
                return 0;
            } else {
                return -1;
            }
        }
    }
    Sudoku[pos_y][pos_x] = 0;
    return -1;
}

int main()
{

      int Sudoku[SIZE_X][SIZE_Y] = {{0, 9, 8, 0, 0, 0, 0, 0, 2},
                                    {0, 5, 0, 0, 0, 2, 1, 8, 7},
                                    {0, 0, 0, 0, 0, 0, 5, 9, 0},
                                    {1, 0, 0, 0, 0, 0, 4, 0, 5},
                                    {0, 0, 0, 0, 0, 0, 9, 0, 0},
                                    {0, 0, 0, 3, 0, 5, 0, 1, 6},
                                    {0, 0, 0, 7, 0, 1, 0, 0, 3},
                                    {9, 4, 7, 6, 2, 0, 0, 0, 0},
                                    {6, 0, 1, 5, 4, 0, 0, 0, 0}};


    if (solve_Sudoku(Sudoku, 0, 0) == 0)
    {
        printf("Puzzle solved!");
        putchar('\n');
    } else {
        printf("Cannot find a solution.  Ended here: ");
        putchar('\n');
    }
    print_Sudoku(Sudoku);


    return 0;
}