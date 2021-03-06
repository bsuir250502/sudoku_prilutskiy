#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void help()
{
    puts("Usage:");
    printf
        ("Start the program and make sure u've got a task file in the same folder as the executable. \nAfter starting - wait for a moment, a nd u'l see the result\n");
}

void printCells(int **cells)
{
    FILE *file;
    if (!file = fopen("solved.txt", "w+")) {
        puts("Error reading the solution");
        freeAll(cells);
        exit(1);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 2 || j == 5) {
                printf("%d  ", cells[i][j]);
            }

            else {
                printf("%d ", cells[i][j]);
            }
        }
        if (i == 2 || i == 5)
            puts("\n");
        else
            puts("");
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fprintf(file, "%d ", cells[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void load(int **cells)
{

    FILE *file;
    if (!file = fopen("task.txt", "r+")) {
        puts("Error reading task file");
        freeAll(cells);
        exit(1);
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            fscanf(file, "%d", &cells[i][j]);
        }
    }
    fclose(file);
}

int rows(int **cells)
{
    int repeats = 0;
    for (int value = 1; value < 10; value++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (cells[i][j] == value)
                    repeats++;
            }
            if (repeats > 1) {
                return 1;
            }
            repeats = 0;
        }
    }
    return EXIT_SUCCESS;
}

int coloumns(int **cells)
{
    int repeats = 0;
    for (int value = 1; value < 10; value++) {
        for (int j = 0; j < 9; j++) {
            for (int i = 0; i < 9; i++) {
                if (cells[i][j] == value)
                    repeats++;
            }
            if (repeats > 1) {
                return 1;
            }
            repeats = 0;
        }
    }
    return EXIT_SUCCESS;

}

int squares(int **cells)
{
    int repeats = 0;
    for (int value = 1; value < 10; value++) {
        for (int i = 0; i < 9; i += 3) {
            for (int j = 0; j < 9; j += 3) {
                for (int i1 = i; i1 < i + 3; ++i1) {
                    for (int j1 = j; j1 < j + 3; ++j1) {
                        if (cells[i1][j1] == value)
                            repeats++;
                    }
                }
                if (repeats > 1) {
                    return 1;
                }
                repeats = 0;
            }
        }
    }
    return EXIT_SUCCESS;
}

int checkCells(int **cells)
{
    if (rows(cells) == 0) {
        if (coloumns(cells) == 0) {
            if (squares(cells) == 0)
                return 0;
            else
                return 1;
        }
        return 1;
    }
    return 1;
}

int SudokuSolution(int **source, int i, int j)
{
    int accepted = 0;
    int default_value = 0;
    if (j >= 9) {
        i++;
        j = 0;
    }
    if (i >= 9)
        return 1;
    if (source[i][j] != 0)
        default_value = 1;
    if (default_value)
        SudokuSolution(source, i, j + 1);
    if (!default_value)
        for (int value = 1; value < 10; value++) {
            source[i][j] = value;
            if (checkCells(source) == 0) {
                accepted = 1;
                if (SudokuSolution(source, i, j + 1) == 1)
                    break;
                else
                    accepted = 0;
            }
        }
    if (!accepted && !default_value) {
        source[i][j] = 0;
        return 0;
    }
    return 1;
}

void freeAll(int **source)
{
    for (int i = 0; i < 9; i++)
        free(source[i]);
    free(source);
}

int main(int argc, char *argv[])
{
    int **cells = (int **) calloc(9, sizeof(int *));
    for (int i = 0; i < 9; i++)
        cells[i] = (int *) calloc(9, sizeof(int));
    if (argc > 1)
        if (strcmp(argv[1], "-h") == 0) {
            help();
            freeAll(cells);
            return EXIT_SUCCESS;
        }
    load(cells);
    if (SudokuSolution(cells, 0, 0) == 0) {
        puts("Improper task. Try again");
        freeAll(cells);
        return EXIT_SUCCESS;
    } else {
        puts("There's the answer:");
        printCells(cells);
    }
    freeAll(cells);
    return EXIT_SUCCESS;
}
