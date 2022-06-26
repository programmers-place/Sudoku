#include <stdio.h>
#include <stdlib.h>

//TODO: functions like printField() can be void or not | CHECK
//TODO: Check User Input 
//TODO: Remove printArray function 
//TODO: fillArray 

struct userInput
{
    int changeRow, changeColumn, userValue;
};

/** prints field
*
* @param 2d int array
* @return int
*/
int printField(int field[9][9])
{
    // 0 = no separation line , 1 = separation line
    int separator = 0;
    // defines the first value (row) in  2d array field
    int y = 0;
    // to make sure y is 0 in the first loop
    int bool = 0;

    // row
    for (int row = 0; row < 13; row++) {
        // indicating the 4 separation lines
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

        // line
        for (int line = 0; line < 25; line++) {
            // if separation line
            if (separator == 1){
                // print '+' every 8 character
                if (line == 0 || line == 8 || line == 16 || line == 24){
                    printf("+ "); // '+'
                }else{
                    // print '-' in between
                    printf("- "); // '-'
                }
            }// end of separator == 1
            // NO separation line
            else if (separator == 0){
                // print '|' as vertical separator in a new line
                line == 0 ? printf("\n|") : 0 ; // '|'

                // print '|' after every 3 characters
                if (line == 3 || line == 6 || line == 9){
                    printf("|"); // '|'
                }

                if(line < 9){
                    if (field[y][line] == 0) {
                        printf("%4c ", '.');
                    } else {
                        printf("%4i ", field[y][line]);
                    }
                }
            }// end of separator = 0
        }// end of for line
    }// end of for row
    return 0;
}// end of printField

//debug purposes
int printArray(int userValue, int changeRow, int changeColumn, int field[9][9]) {
    field[changeRow-1][changeColumn-1] = userValue;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%2i", field[i][j]);
        }
        printf("\n");
    }
    return 0;
}

/**
* Checks if input number already appears in column of field
* @param 2d array field, int, int 
* @return int 1 if number already exists, int 0 if not
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
* @param 2d array, int, int 
* @return int 1 if number already exists, int 0 if not
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
* @param int, int 
* @return int -1 if arguments are invalid (which isn't actually needed in this function, see below)
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
        return -1; // Won't be needed since rows and columns will be checked before function is called (checkSquare())
    }
}// end of getSquare


/**
* Checks if number already appears in square
* @param 2d array field, int, int, int 
* @return int 1 if yes and int 0 if not
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
* Checks if input number already appears in row, column or square
* @param 2d array field, int, int, int
* @return int 1 if yes and int 0 if not
*/
int numberAppears(int field[9][9], int input, int row, int column) {
    int result = 0;

    int rowCheck = checkRow(field, input, row);
    int columnCheck = checkColumn(field, input, column);
    int squareCheck = checkSquare(field, input, row, column);

    // Check if input appears in Row
    if (rowCheck) {
        printf("\nEs gibt bereits eine %i in dieser Zeile.", input);
        result = 1;
    }

    // Check if input appears in Column
    if (columnCheck) {
        printf("\nEs gibt bereits eine %i in dieser Spalte.", input);
        result = 1;
    }

    // Check if input appears in Square
    if (squareCheck) {
        printf("\nEs gibt bereits eine %i in diesem Block.", input);
        result = 1;
    }

    // Spacing if something was printed
    if (result) {
        printf("\n");
    }

    return result;
}// end fo numberAppears


/** still in process
* changes input array
* @param 2d array field 
* @return 2d array field
*
int fillArray(int field[9][9]){
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = 0;
        }
    }

    return field;
}
*/

/**
* checks if user input is integer 
* @param struct userInput, int, int  
* @return int  
**/
int checkUserInput(struct userInput input, int scanIsInteger, int userInput) {
    
    // if input is not an integer
    while ( scanIsInteger != 1 ){
        getchar();
        printf("\nInput ist keine Nummer\nNochmal eingeben: ");
        scanIsInteger = scanf("%d", &userInput);  
    }
    
    // if input is not between 1 - 9
    while ( userInput < 0 || userInput > 9){
        getchar();
        printf("\nNur Ganzzahlen von 1 - 9\nNochmal eingeben: ");
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

    printf("\n\n______________________________________________  ");

    // get line / row
    printf("\n\nZeile:  ");
    scanIsInteger = scanf("%d", &userInput);
    userInput = checkUserInput(input, scanIsInteger, userInput);
    input.changeRow = userInput;

    // get column
    printf("Spalte: ");
    //scanf("%i", &input.changeColumn);
    scanIsInteger = scanf("%d", &userInput);
    userInput = checkUserInput(input, scanIsInteger, userInput);
    input.changeColumn = userInput;

    // get value to change
    printf("Wert: ");
    //scanf("%i", &input.userValue);
    scanIsInteger = scanf("%d", &userInput);
    userInput = checkUserInput(input, scanIsInteger, userInput);
    input.userValue = userInput;

    // return struct userInput
    return input;

    printf("\n______________________________________________");
}

int main()
{
    // declare field
    int field[9][9] = {0};

    // for endless while loop
    int loop = 1;

    // initialise struct userInput
    struct userInput input;

    // TODO: outsource in function
    // fill array
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = 0;
        }
    }
    //field = fillArray(field);

    // first time print for the user
    printField(field);
    
    while (loop == 1)
    {
        // TODO: comments on functions @return and @param
        // initialise struct
        input = getUserInput();

        if (numberAppears(field, input.userValue, input.changeRow - 1 , input.changeColumn - 1)) {
            continue;
        } else {
            // added -1 because indexing starts with 1 now == first value is (1/1)
            field[input.changeRow-1][input.changeColumn-1] = input.userValue;

            printField(field);
        }
    }
    return 0;
}