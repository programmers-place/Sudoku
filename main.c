#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

// Define userInput struct
struct userInput
{
    int changeRow, changeColumn, userValue;
};

/**
* Prints the field
*/
int printField(int field[9][9], int initialField[9][9])
{
    // Clear last output
    #if __APPLE__
        system("clear");
    #elif __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #endif

    // 0 = no separation line, 1 = separation line
    int separator = 0;
    // defines the first value (row) in  2d array field
    int y = 0;
    // to make sure y is 0 in the first loop
    int bool = 0;

    int number = 0; // input number

    // row
    for (int row = 0; row < 13; row++) {
        // indicating the 4 separation line
        // no separation
        if (row != 0 && row != 4 && row != 8 && row != 12){
            separator = 0;
            if (row < 12 && bool == 1){
                y = y + 1;
            }
            bool = 1;
        }
        // separation
        else{
            separator = 1;
            printf("\n");
        }

        // column
        for (int column = 0; column < 25; column++) {
            // if separation line
            if (separator == 1){
                // print '+' every 8 character
                if (column == 0 || column == 8 || column == 16 || column == 24){
                    printf("+ "); // '+'
                }else{
                    // print '-' in between
                    printf("- "); // '-'
                }
            }// end of separator = 1
            // NO separation line
            else if (separator == 0){
                // print '|' as vertical separator in a new column
                column == 0 ? printf("\n|") : 0 ; // '|'

                // print '|' every 8 character
                if (column == 3 || column == 6 || column == 9){
                    printf("|"); // '|'
                }

                if(column < 9){
                    if (field[y][column] == 0) {
                        printf("%4c ", '.');
                    } else {

                        number = field[y][column];
                        field[y][column] = 0;

                        if (number == initialField[y][column]) {
                            printf("%4i ", number);
                        } else if (numberAppears(field, number, y, column, 0)) {
                            printf(ANSI_COLOR_RED "%4i " ANSI_COLOR_RESET, number);

                        } else {
                            printf(ANSI_COLOR_CYAN "%4i " ANSI_COLOR_RESET, number);
                        }

                        field[y][column] = number;
                    }

                }


            }// end of separator = 0
        }// end of for column
    }// end of for row

    return 0;
}// end of printField

/**
 * Checks if game is finished
 * @return 1 if yes and 0 if not
 */
int isFinished(int field[9][9], int initialField[9][9]) {
    // If there are no zeros in the Array and no wrong numbers, the Sudoku is finished
    int zeroCounter = 0; // Counter for all zeros
    int wrongCounter = 0; // Counter for all wrongly set numbers
    int isInitial = 0; // Bool if number was initially from the Sudoku
    int isFinished = 0; // Holds the return value
    int temp = 0; // Temporarily hold value of current cell

    // Iterate through field array
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {

            // Check if number was a user Input
            if (field[i][j] == initialField[i][j]) {
                isInitial = 1;
            }

            // Check if number is 0
            if (field[i][j] == 0) {
                zeroCounter++;
            }

            // Check if number is wrong
            // To do that, we have to take out the value for numberAppears() to work

            temp = field[i][j];
            field[i][j] = 0;

            if (isInitial == 0 && numberAppears(field, temp, i, j, 0)) {
                wrongCounter++;
            }

            field[i][j] = temp;

            isInitial = 0;
        }
    }

    // If there are no zeros and no wrong numbers, the Sudoku is finished.
    if (zeroCounter == 0 && wrongCounter == 0) {
        isFinished = 1;
    }

    return isFinished;
}

/**
* Checks if input number already appears in column of field
* @return 1 if number already exists, 0 if not
*/
int checkColumn(int field[9][9], int input, int column) {
    int result = 0;

    for (int i = 0; i < 9; i++) {
        if (field[i][column] == input) {
            result = 1;
        }
    }

    return result;
}// end of checkColumn

/**
* Checks if input number already appears in row of field
* @return 1 if number already exists, 0 if not
*/
int checkRow(int field[9][9], int input, int row) {
    int result = 0;

    for (int i = 0; i < 9; i++) {
        if (field[row][i] == input) {
            result = 1;
        }
    }

    return result;
}// end of checkRow

/**
* Returns in which square of the field the input would be set
* @return -1 if arguments are invalid (which isn't actually needed in this function, see below)
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
}// end of getSquare


/**
* Checks if number already appears in square
* @return 1 if yes and 0 if not
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
    }// end of switch square

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
}// end of checkSquare

/**
* Checks if the chosen cell can be altered or if it is fixed
* @return 1 if cell can be altered, 0 if not
*/
int cellIsUsable(int initialField[9][9], int row, int column) {
    if (initialField[row][column] == 0) {
        return 1;
    }

    return 0;
}

/**
* Checks if input number already appears in row, column or square
* If print is 1 print errors, if it's zero don't print errors
* @return 1 if yes and 0 if not
*/
int numberAppears(int field[9][9], int input, int row, int column, int print) {
    int result = 0;

    int rowCheck = checkRow(field, input, row);
    int columnCheck = checkColumn(field, input, column);
    int squareCheck = checkSquare(field, input, row, column);

    // Check if input appears in Row
    if (rowCheck) {
        if (print) {
            printf("\nEs gibt bereits eine %i in dieser Zeile.", input);
        }

        result = 1;
    }

    // Check if input appears in Column
    if (columnCheck) {
        if (print) {
           printf("\nEs gibt bereits eine %i in dieser Spalte.", input);
        }

        result = 1;
    }

    // Check if input appears in Square
    if (squareCheck) {
        if (print) {
            printf("\nEs gibt bereits eine %i in diesem Block.", input);
        }

        result = 1;
    }

    // Spacing if something was printed
    if (print && result) {
        printf("\n");
    }

    return result;
}// end of numberAppears

/**
* Collects user input
* @return struct userInput
**/
struct userInput getUserInput(){
    // define struct variable
    struct userInput input;

    // get user input for changing values

    // get column / row
    printf("\n\nZeile:  ");
    scanf("%i", &input.changeRow);

    // get column
    printf("Spalte: ");
    scanf("%i", &input.changeColumn);

    // get value to change
    printf("Wert: ");
    scanf("%i", &input.userValue);

    // return userInput
    return input;
}

/**
* Defines the field array as an actual Sudoku game
*/
int fillField(int field[9][9], int sudoku[81]) {

    int i = 0; // Iterator for loop 1
    int j = 0; // Iterator for loop 2
    int sudokuIndex = 0; // Iterator for Sudoku index

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            field[i][j] = sudoku[sudokuIndex];
            sudokuIndex++;
        }
    }
    return 0;
}

/**
* Saves field into text file
* @param 2d array field
* @return int 0
*/
int saveGame(int field [9][9]) {
    // open file.txt for writing field
    FILE *f = fopen("file.txt", "w");

    // Error if file can't be opened
    if (f == NULL) {
        Printf("Error opening file!\n");
        exit(1);
    }


    // print field into file.txt
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            fprintf(f, "%d\n", field[x][y]);
        }
    }

    // Close file.txt
    fclose(f);
    return 0;
} // end of saveGame


int main()
{
    struct userInput input; // Declare user input
    int field[9][9]; // Declare field
    int loop = 1; // Variable to decide if game continues

    // We need another field that is the field the player begins with. This field never changes.
    // Purpose: We need to know which numbers the player is allowed to change and which he is not
    int initialField[9][9];

    // Define some Sudokus
    int easy1[81] = {8, 5, 4, 0, 3, 1, 0, 9, 7, 7, 0, 6, 0, 9, 8, 5, 2, 1, 0, 2, 0, 0, 6, 5, 0, 0, 0, 0, 0, 0, 8, 0, 2, 0, 7, 6, 0, 4, 0, 0, 0, 7, 0, 0, 0, 0, 0, 8, 9, 0, 0, 3, 0, 5, 3, 0, 7, 0, 0, 9, 0, 0, 0, 4, 9, 0, 0, 0, 0, 7, 0, 2, 0, 0, 0, 5, 0, 0, 0, 3, 0};

    // Fill both fields with the chosen Sudoku
    fillField(initialField, easy1);
    fillField(field, easy1);

    // First time print for the user
    printField(field, initialField);



    do {
        // Get the user input
        input = getUserInput();

        if (!cellIsUsable(initialField, input.changeRow-1, input.changeColumn-1)) {
            printf("Diese Zelle kann nicht veraendert werden.\n");
            continue;
        } else {
            // Added - 1 because indexing starts with 1 now == first value is (1/1)
            field[input.changeRow - 1][input.changeColumn - 1] = input.userValue;

            // Print field
            printField(field, initialField);
        }

        if (isFinished(field, initialField)) {
            printf("\n\nSie haben das Sudoku geloest!");
            loop = 0;
        }

    } while (loop);

    return 0;
}
