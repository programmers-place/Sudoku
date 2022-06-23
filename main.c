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
* Checks if input number already appears in column of field
* Returns 1 if number already exists, 0 if not
*/
int checkColumn(int field[9][9], int input, int column) {
    int result = 0;

    for (int i = 0; i < 9; i++) {
        if (field[i][column] == input) {
            result = 1;
        }
    }

    return result;
}

/**
* Checks if input number already appears in row of field
* Returns 1 if number already exists, 0 if not
*/
int checkRow(int field[9][9], int input, int row) {
    int result = 0;

    for (int i = 0; i < 9; i++) {
        if (field[row][i] == input) {
            result = 1;
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
* Returns 1 if yes and 0 if not
*/
int checkSquare(int field[9][9], int input, int row, int column) {
    int result = 0;

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
                result = 1;
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

    int rowCheck = checkRow(field, input, row);
    int columnCheck = checkColumn(field, input, column);
    int squareCheck = checkSquare(field, input, row, column);

    // Check if input appears in Row
    if (rowCheck) {
        printf("\nEine %i existiert bereits in dieser Zeile.\n", input);
        result = 1;
    }

    // Check if input appears in Column
    if (columnCheck) {
        printf("\nEine %i existiert bereits in dieser Spalte.\n", input);
        result = 1;
    }

    // Check if input appears in Square
    if (squareCheck) {
        printf("\nEine %i existiert bereits in diesem Block.\n", input);
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
    checkAll(field, 5, 1, 1);

    return 0;
}
