//
//  main.c
//  lab4
//
//  Created by Kelly Krawczyk on 2/24/16.
//  Copyright © 2016 Kelly Krawczyk. All rights reserved.
//


/* NOTE: You will have to link in the 'pthread' library when you compile the code after you start using the pthread functions, i.e.
 * gcc systems-sudoku.c -pthread -o systems-sudoku
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE (9)

/*You can keep the sudoku solution in global memory for easy access*/

typedef struct {
    
    int row;
    int column;
    int (* board)[9];
    
} parameters;

void * walk_rows(void * params);

void * walk_columns(void * params);

void * check_square(void * params);

int sudoku[SIZE][SIZE];

/*Function prints out the sudoku solution you're trying to verify*/
void PrintSudoku()
{
    int i = 0;
    int j = 0;
    for(;i<9;i++)
    {
        for(j=0;j<9;j++)
            printf("%d ",sudoku[i][j]);
        printf("\n");
    }
    
    
}

int load_sudoku(int sudoku[][SIZE], const char *input_filename) {
    
    FILE *input_fp = fopen(input_filename, "r");
    int i = 0;
    int j = 0;
    
    if (input_fp != NULL) {
        
        for (; i < SIZE; i++) {
            
            for (j = 0; j < SIZE; j++) {
                fscanf(input_fp, "%d", &sudoku[i][j]);
            }
        }
        fclose(input_fp);
        return 1;
    }
    
    else {
        fprintf(stderr, "Error opening input file %s\n", input_filename);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int sudoku[9][9];
    
    if (argc != 2) {
        fprintf(stderr, "Usage ./systems-sudoku input-file\n");
        exit(1);
    }
    
    if (load_sudoku(sudoku, argv[1])) {
        
        for (int i = 0; i < 9; i++) {
            
            for (int j = 0; j < 9; j++) {
                printf("%d ", sudoku[i][j]);
            }
            printf("\n");
        }
    }
    else {
        return 1;
    }
    
    
    //parameter for columns and rows check
    parameters * param0 = (parameters *) malloc(sizeof(parameters));
    param0->row = 0;
    param0->column = 0;
    param0->board = sudoku;
    
    //parameters for 3x3 threads
    
    //first 3x3
    parameters * param1 = (parameters *) malloc(sizeof(parameters));
    param1->row = 0;
    param1->column = 0;
    param1->board = sudoku;
    
    //second 3x3
    parameters * param2 = (parameters *) malloc(sizeof(parameters));
    param2->row = 0;
    param2->column = 3;
    param2->board = sudoku;
    
    //third 3x3
    parameters * param3 = (parameters *) malloc(sizeof(parameters));
    param3->row = 0;
    param3->column = 6;
    param3->board = sudoku;
    
    //fourth 3x3
    parameters * param4 = (parameters *) malloc(sizeof(parameters));
    param4->row = 3;
    param4->column = 0;
    param4->board = sudoku;
    
    //fifth 3x3
    parameters * param5 = (parameters *) malloc(sizeof(parameters));
    param5->row = 3;
    param5->column = 3;
    param5->board = sudoku;
    
    //sixth 3x3
    parameters * param6 = (parameters *) malloc(sizeof(parameters));
    param6->row = 3;
    param6->column = 6;
    param6->board = sudoku;
    
    //seventh 3x3
    parameters * param7 = (parameters *) malloc(sizeof(parameters));
    param7->row = 6;
    param7->column = 0;
    param7->board = sudoku;
    
    //eighth 3x3
    parameters * param8 = (parameters *) malloc(sizeof(parameters));
    param8->row = 6;
    param8->column = 3;
    param8->board = sudoku;
    
    //ninth 3x3
    parameters * param9 = (parameters *) malloc(sizeof(parameters));
    param9->row = 6;
    param9->column = 6;
    param9->board = sudoku;
    
    pthread_t thread_rows, thread_columns, t1, t2, t3, t4, t5, t6, t7, t8, t9;
    void * rows;
    void * columns;
    void * s1;
    void * s2;
    void * s3;
    void * s4;
    void * s5;
    void * s6;
    void * s7;
    void * s8;
    void * s9;
    
    pthread_create(&thread_rows, NULL, walk_rows, (void *) param0);
    pthread_create(&thread_columns, NULL, walk_columns, (void *) param0);
    pthread_create(&t1, NULL, check_square, (void *) param1);
    pthread_create(&t2, NULL, check_square, (void *) param2);
    pthread_create(&t3, NULL, check_square, (void *) param3);
    pthread_create(&t4, NULL, check_square, (void *) param4);
    pthread_create(&t5, NULL, check_square, (void *) param5);
    pthread_create(&t6, NULL, check_square, (void *) param6);
    pthread_create(&t7, NULL, check_square, (void *) param7);
    pthread_create(&t8, NULL, check_square, (void *) param8);
    pthread_create(&t9, NULL, check_square, (void *) param9);
    
    pthread_join(thread_rows, &rows);
    pthread_join(thread_columns, &columns);
    pthread_join(t1, &s1);
    pthread_join(t2, &s2);
    pthread_join(t3, &s3);
    pthread_join(t4, &s4);
    pthread_join(t5, &s5);
    pthread_join(t6, &s6);
    pthread_join(t7, &s7);
    pthread_join(t8, &s8);
    pthread_join(t9, &s9);
    
    if ((int) rows == 1 &&
        (int) columns == 1 &&
        (int) s1 == 1 &&
        (int) s2 == 1 &&
        (int) s3 == 1 &&
        (int) s4 == 1 &&
        (int) s5 == 1 &&
        (int) s6 == 1 &&
        (int) s7 == 1 &&
        (int) s8 == 1 &&
        (int) s9 == 1) {
        printf("Solved\n");
    }
    
    else {
        printf("Not solved\n");
    }
    PrintSudoku();
    return 0;
}

void * walk_rows(void * params) {
    
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startColumn = data->column;
    
    for (int i = startRow; i < 9; ++i) {
        
        int row[10] = {0};
        
        for (int j = startColumn; j < 9; ++j) {
            
            int val = data->board[i][j];
            
            if (row[val] != 0) {
                return (void *) 0;
            }
            
            else {
                row[val] = 1;
            }
        }
    }
    return (void *) 1;
}

void * walk_columns(void * params) {
    
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startColumn = data->column;
    
    for (int i = startColumn; i < 9; ++i) {
        
        int column[10] = {0};
        
        for (int j = startRow; j < 9; ++j) {
            
            int val = data->board[j][i];
            
            if (column[val] != 0) {
                return (void *) 0;
            }
            
            else {
                column[val] = 1;
            }
        }
    }
    return (void *) 1;
}

void * check_square(void * params) {
    
    parameters * data = (parameters *) params;
    int startRow = data->row;
    int startColumn = data->column;
    int saved[10] = {0};
    
    for (int i = startRow; i < startRow + 3; ++i) {
        
        for (int j = startColumn; j < startColumn + 3; ++j) {
            
            int val = data->board[i][j];
            
            if (saved[val] != 0) {
                return (void *) 0;
            }
            
            else {
                saved[val] = 1;
            }
        }
    }
    return (void *) 1;
}
