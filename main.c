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

/**
* Checks if a number already appears in column of field
* Returns coordinates if number already exists, {42, 42} if not
*/
int[2] checkColumn(int field[9][9], int number, int column) {
    int result[2] = {42, 42};

    for (int i = 0; i < 9; i++) {
        if (field[i][column] == number) {
            result[0] = i;
            result[1] = column;
        }
    }

    return result;
}

/**
* Checks if a number already appears in row of field
* Returns coordinates if number already exists, {42, 42} if not
*/
int[2] checkRow(int field[9][9], int number, int row) {
    int result[2] = {42, 42};

    for (int i = 0; i < 9; i++) {
        if (field[row][i] == number) {
            result[0] = row;
            result[1] = i;
        }
    }

    return result;
}

/**
* Returns in which square of the field the input would be set
* Returns -1 if arguments are invalid (which isn't actually needed in this function, see below)
*/
int getSquare(int row, int column) {

    // Upper 3 squares
    if ((row >= 0 && row < 3) && (column >= 0 && column < 3)) {
        return 1;
    } else if ((row >= 0 && row < 3) && (column >= 3 && column < 6)) {
        return 2;
    } else if ((row >= 0 && row < 3) && (column >= 6 && column < 9)) {
        return 3;

    // Mid 3 squares
    } else if ((row >= 3 && row < 6) && (column >= 0 && column < 3)) {
        return 4;
    } else if ((row >= 3 && row < 6) && (column >= 3 && column < 6)) {
        return 5;
    } else if ((row >= 3 && row < 6) && (column >= 6 && column < 9)) {
        return 6;

    // Lower 3 squares
    } else if ((row >= 6 && row < 9) && (column >= 0 && column < 3)) {
        return 7;
    } else if ((row >= 6 && row < 9) && (column >= 3 && column < 6)) {
        return 8;
    } else if ((row >= 6 && row < 9) && (column >= 6 && column < 9)) {
        return 9;
    } else {
        return -1; // Won't be needed since rows and columns will be checked before function is called
    }
}


/**
* Checks if number already appears in square
* Returns coordinates if yes and {42, 42} if not
*/
int[2] checkSquare(int field[9][9], int input, int row, int column) {
    int result[2] = {42, 42};

    // We need to know which square to check
    int square = getSquare(row, column);

    // Array for the limits of the row and column area (minRow, maxRow, minCol, maxCol)
    int minRow = 0;
    int maxRow = 0;
    int minCol = 0;
    int maxCol = 0;

    // Define area of square
    switch (square) {

    // Upper 3 squares
    case 1:
        minRow = 0;
        maxRow = 2;
        minCol = 0;
        maxCol = 2;
        break;
    case 2:
        minRow = 0;
        maxRow = 2;
        minCol = 3;
        maxCol = 5;
        break;
    case 3:
        minRow = 0;
        maxRow = 2;
        minCol = 6;
        maxCol = 8;
        break;

    // Mid 3 squares
    case 4:
        minRow = 3;
        maxRow = 5;
        minCol = 0;
        maxCol = 2;
        break;
    case 5:
        minRow = 3;
        maxRow = 5;
        minCol = 3;
        maxCol = 5;
        break;
    case 6:
        minRow = 3;
        maxRow = 5;
        minCol = 6;
        maxCol = 8;
        break;

    // Lower 3 squares
    case 7:
        minRow = 6;
        maxRow = 8;
        minCol = 0;
        maxCol = 2;
        break;
    case 8:
        minRow = 6;
        maxRow = 8;
        minCol = 3;
        maxCol = 5;
        break;
    case 9:
        minRow = 6;
        maxRow = 8;
        minCol = 6;
        maxCol = 8;
        break;
    }

    // Now iterate through field array in the accurate limits
    for (int i = minRow; i <= maxRow; i++) {
        for (int j = minCol; j <= maxCol; j++) {

            // If cell holds same number that user wants to set, result is set to 1
            if (field[i][j] == input) {
                result[0] = i;
                result[1] = j;
            }
        }
    }

    return result;
}

/**
* Checks if input number already exists in row, column or square
* returns 1 if yes and 0 if not
*/
int checkAll(int field[9][9], int input, int row, int column) {
    int result = 0;

    int rowCheck[2] = checkRow(field, input, row);
    int columnCheck[2] = checkColumn(field, input, column);
    int squareCheck[2] = checkSquare(field, input, row, column);

    // Check if input appears in Row
    if (rowCheck[0] != 42) {
        printf("\nEine %i existiert bereits in dieser Zeile (%i, %i)", input, rowCheck[0], rowCheck[1]);
        result = 1;
    }

    // Check if input appears in Column
    if (columnCheck[0] != 42) {
        printf("\nEine %i existiert bereits in dieser Spalte (%i, %i)", input, columnCheck[0], columnCheck[1]);
        result = 1;
    }

    // Check if input appears in Square
    if (squareCheck[0] != 42) {
        printf("\nEine %i existiert bereits in diesem Block (%i, %i)", input, squareCheck[0], squareCheck[1]);
        result = 1;
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
    checkAll(field, 5, 3, 5);

    return 0;
}
