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
int numberAppears(int field[9][9], int input, int row, int column) {
    int result = 0;

    int rowCheck = checkRow(field, input, row);
    int columnCheck = checkColumn(field, input, column);
    int squareCheck = checkSquare(field, input, row, column);

    // Check if input appears in Row
    if (rowCheck) {
        result = 1;
    }

    // Check if input appears in Column
    if (columnCheck) {
        result = 1;
    }

    // Check if input appears in Square
    if (squareCheck) {
        result = 1;
    }

    return result;
}// end of numberAppears

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
                        } else if (numberAppears(field, number, y, column)) {
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

            if (isInitial == 0 && numberAppears(field, temp, i, j)) {
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
* checks if user input is integer
* @param int, int, int
* @return int
**/
int checkUserInput(int scanIsInteger, int userInput, int isValue) {

    // input value can be 0, but field range cannot. Therefore the range can differ
    int minRange = 1; // bottom range

    if (isValue == 1) {
        minRange = 0;
    }

    // if input is not an integer
    while ( scanIsInteger != 1 ){
        getchar();
        printf("\nInput ist keine Nummer. Nochmal eingeben: ");
        scanIsInteger = scanf("%d", &userInput);
    }


    // if input is not between 1 - 9
    while ( userInput < minRange || userInput > 9){
        getchar();
        printf("\nNur Ganzzahlen von %i - 9. Nochmal eingeben: ", minRange);
        scanIsInteger = scanf("%d", &userInput);
    }
    return userInput;
}// end of checkUserInput

/**
* Collects user input
* @return struct input
**/
struct userInput getUserInput(){
    // initialise struct userInput
    struct userInput input;

    // initialise integer for storing input and cheking data type
    int userInput, scanIsInteger;

    printf("\n\n_________________________________________________");

    // get column
    printf("\n\nSpalte: ");
    //scanf("%i", &input.changeColumn);
    scanIsInteger = scanf("%d", &userInput);
    userInput = checkUserInput(scanIsInteger, userInput, 0);
    input.changeColumn = userInput;

    // get line / row
    printf("Zeile:  ");
    scanIsInteger = scanf("%d", &userInput);
    userInput = checkUserInput(scanIsInteger, userInput, 0);
    input.changeRow = userInput;

    // get value to change
    printf("Wert (0 zum entfernen): ");
    //scanf("%i", &input.userValue);
    scanIsInteger = scanf("%d", &userInput);
    userInput = checkUserInput(scanIsInteger, userInput, 1);
    input.userValue = userInput;

    // return struct userInput
    return input;

    printf("\n______________________________________________");
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

int chooseSudoku(int field[9][9], int initialField[9][9]) {
    // Define some Sudokus
    int easy1[81] = {8, 5, 4, 0, 3, 1, 0, 9, 7, 7, 0, 6, 0, 9, 8, 5, 2, 1, 0, 2, 0, 0, 6, 5, 0, 0, 0, 0, 0, 0, 8, 0, 2, 0, 7, 6, 0, 4, 0, 0, 0, 7, 0, 0, 0, 0, 0, 8, 9, 0, 0, 3, 0, 5, 3, 0, 7, 0, 0, 9, 0, 0, 0, 4, 9, 0, 0, 0, 0, 7, 0, 2, 0, 0, 0, 5, 0, 0, 0, 3, 0};
    int easy2[81] = {0, 0, 0, 7, 0, 0, 0, 0, 0, 7, 2, 0, 0, 0, 9, 0, 5, 1, 8, 9, 1, 0, 2, 6, 0, 7, 0, 9, 0, 3, 2, 0, 0, 0, 6, 8, 6, 8, 0, 1, 0, 0, 3, 4, 2, 2, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 9, 3, 1, 0, 6, 8, 0, 0, 0, 0, 9, 5, 0, 0, 0, 4, 0, 3, 0, 6, 7, 0, 0, 1, 0};
    int medium1[81] = {9, 7, 1, 6, 8, 5, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 7, 1, 0, 0, 0, 0, 0, 2, 9, 0, 0, 6, 0, 2, 3, 8, 0, 6, 0, 0, 0, 6, 8, 0, 0, 0, 0, 5, 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, 7, 4, 0, 7, 2, 6, 0, 0, 0, 1, 0, 6, 5, 0, 0, 7, 9, 0, 0};
    int medium2[81] = {5, 0, 0, 0, 0, 0, 0, 1, 8, 0, 9, 0, 0, 0, 8, 0, 0, 0, 0, 3, 8, 1, 7, 5, 0, 9, 0, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 3, 6, 0, 0, 0, 0, 6, 0, 9, 4, 0, 2, 0, 9, 2, 0, 7, 0, 0, 0, 0, 5, 8, 0, 3, 0, 0, 1, 0, 0, 0, 0, 6, 5, 0, 8, 0, 3, 0, 0};
    int hard1[81] = {0, 0, 0, 0, 4, 3, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 6, 1, 7, 8, 0, 4, 0, 0, 7, 0, 0, 0, 0, 0, 6, 0, 8, 0, 0, 2, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 8, 6, 0, 0, 7, 0, 0, 0, 0, 3, 0, 3, 2, 0, 1, 0, 0, 0, 7, 0, 1, 0, 3, 8, 6, 0, 0, 4};
    int hard2[81] = {7, 0, 4, 0, 0, 0, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 5, 4, 0, 0, 8, 0, 2, 6, 0, 4, 0, 0, 5, 0, 0, 0, 3, 0, 9, 0, 9, 0, 0, 8, 0, 0, 7, 0, 0, 0, 0, 1, 0, 0, 5, 0, 0, 0, 8, 0, 0, 7, 0, 0, 0, 0, 2, 0, 0, 0, 2, 1, 0, 0, 0, 8};

    int difficulty = 0;

    printf("Waehlen sie einen Schwierigkeitsgrad: ");
    printf("\n einfach: 1");
    printf("\n mittel: 2");
    printf("\n schwer: 3");
    printf("\n\n");

    scanf("%i", &difficulty);

    while (!(difficulty >= 1 && difficulty <= 3)) {
        printf("\nUngueltiger Schwierigkeitsgrad. Erneut eingeben:\n\n");
        scanf("%i", &difficulty);
    }

    // Random number generator
    srand(time(NULL));
    int randomNumber = (rand()%2) + 1; // Zufallszahl

    switch (difficulty) {
    case 1:
        if (randomNumber == 1) {
            fillField(field, easy1);
            fillField(initialField, easy1);
        } else {
            fillField(field, easy2);
            fillField(initialField, easy2);
        }
        break;
    case 2:
        if (randomNumber == 1) {
            fillField(field, medium1);
            fillField(initialField, medium1);
        } else {
            fillField(field, medium2);
            fillField(initialField, medium2);
        }
        break;
    case 3:
        if (randomNumber == 1) {
            fillField(field, hard1);
            fillField(initialField, hard1);
        } else {
            fillField(field, hard2);
            fillField(initialField, hard2);
        }
        break;
    }
}

int main()
{
    struct userInput input; // Declare user input
    int field[9][9]; // Declare field
    int loop = 1; // Variable to decide if game continues

    // We need another field that is the field the player begins with. This field never changes.
    // Purpose: We need to know which numbers the player is allowed to change and which he is not
    int initialField[9][9];

    // Introduction
    printf("Willkommen bei Sudoku. ");

    // Fill both fields with the chosen Sudoku
    chooseSudoku(field, initialField);

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
