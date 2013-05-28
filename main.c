#include <stdio.h>
#include <stdlib.h>
#include <string.h>
   
int Cells[9][9];

void PrintCells()
{
    FILE *file = fopen("solved.txt", "w+");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 2 || j == 5 || j == 8) {
                printf("%d ", Cells[i][j]);
            }

            else {
                printf("%d ", Cells[i][j]);
            }
        }
        puts("");
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(file, "%d ", Cells[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void Load()
{
    
    FILE *file = fopen("task.txt","r+");
    for (int i = 0; i< 9; i++)  {
        for(int j = 0;j < 9; j++) {
            fscanf(file,"%d" ,&Cells[i][j] );
        }
    }
    fclose(file);
}

int Rows()
{
    int REPEATS = 0;
    for(int value = 1; value < 10 ; value++ ) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if ( Cells[i][j] == value)
                    REPEATS ++;
            }
            if ( REPEATS > 1 ) {
                return 1;
            }
            REPEATS = 0;
        }
    }
    return 0;
}

int Coloumns ()
{
    int REPEATS = 0;
    for(int value = 1; value < 10; value++ ) {
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                if ( Cells[i][j] == value)
                    REPEATS ++;
            }
            if ( REPEATS > 1 ){
                return 1;
            }
            REPEATS = 0;
        }
    }
    return 0;

}

int Squares ()
{
    int REPEATS = 0;
    for(int value = 1; value < 10; value++ ) {
        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 9; j += 3) {
                for (int i1 = i; i1 < i+3 ; ++ i1) {
                    for (int j1 = j; j1 < j+3 ; ++ j1) {
                        if (Cells[i1][j1] == value)
                            REPEATS ++;
                    }
                }
                if ( REPEATS > 1 ) {
                    return 1;
                }
                REPEATS = 0;                       
            }          
        }
    }
    return 0;
}

int ChackCells ()
{
    if (Rows () == 0)
    {
        if (Coloumns () == 0)
        {
            if (Squares () == 0)
                return 0;
            else 
                return 1;
        }
        return 1;
    }
    return 1;    
}

int SolveCells(int i,int j)
{
    int  value = 1;
    while (1) {
        if ((i + 1) >= 9 && (j + 1) >= 9)
            return 0;
        if (j >= 9) {
            i++;
            j = 0;
        }
        if(Cells[i][j] != 0) {
            j++;
        }
        else
            break;
    }
    while (1) {
        while (1) {
            if(value <= 9) {
                Cells[i][j] = value;
                value ++;
                if (ChackCells() == 0) {
                    break;
                }
            }
            if (value >= 10) {
                Cells[i][j] = 0;
                return 1;
            }
        }
        if ( SolveCells(i, (j + 1 )) == 0) {
            return 0;
        }
    }
}
   
void Help()
{
    puts("Usage:");
    printf("Start the program and make sure u've got a task file in the same folder as the executable. \nAfter starting - wait for a moment, a nd u'l see the result\n");

}

int main(int argc, char* argv[])
{       
    if (argc>1)
        if (strcmp(argv[1],"-h")==0){
                Help();
                return 0;
            } 
    Load();
    if (SolveCells(0,0) == 1) {
        puts ("Improper task. Try again");
        return 0;
    }
    else {
        puts("There's the answer:");
        PrintCells();
    }          
    return 0;
}