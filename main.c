#include <stdio.h>
#include <stdlib.h>

int printField(int field[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%3i", field[i][j]);
            if (j == 8) {
                printf("\n");
            }
        }
    }
    return 0;
}

/* Checks if a number already exists in column of field
*
* @param int[9][9] field: Main game field
* @param int number: Input number
* @param int column: Column of choice for input number
*
* @return int: 1 if number already exists, 0 if not
*/
int checkHorizontal(int field[9][9], int number, int column) {
    int result = 0;

    for (int i = 0; i < 9; i++) {
        if (field[i][column] == number) {
            result = 1;
        }
    }

    return result;
}

/* Checks if a number already exists in row of field
*
* @param int[9][9] field: Main game field
* @param int number: Input number
* @param int row: Row of choice for input number
*
* @return int: 1 if number already exists, 0 if not
*/
int checkVertical(int field[9][9], int number, int row) {
    int result = 0;

    for (int i = 0; i < 9; i++) {
        if (field[row][i] == number) {
            result = 1;
        }
    }

    return result;
}

int main()
{
    int field[9][9];

    int k = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = k;
            k++;
        }
        k = 1;
    }
    printField(field);
    return 0;
}
