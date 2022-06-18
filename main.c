#include <stdio.h>
#include <stdlib.h>

/**
* Structure for needed input values
*/
struct input {
    int number;
    int column;
    int row;
};

/**
* Fills the field with numbers
*/
int fillField(char field[9][9]) {
    // Fill only 0 for now
    // TODO: Fill with real Sudoku numbers
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = 0;
        }
    }
    return 0;
}

/**
* Creates the multi-dimensional Array for the field
*/
int createField() {
    char field[9][9];
    fillField(field);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%i", field[i][j]);
        }
    }
    return 0;
}

/**
* Adds number to field
*/
int addNumber(struct input input) {
    return 0;
}

/**
* Removes number from field
*/
int removeNumber(struct input input) {
    return 0;
}

/**
* Updates the field by the given input at demanded place
*/
int updateField(struct input input) {
    return 0;
}

int printField()
{
    char line [25][25] = {{'+', '-', '.'}};
    char row [25][25] = {{'|'}};
    // 0 = no separation line , 1 = separation line
    int separator = 0;
    int i,j;

    // row
    for (i = 0; i < 13; i++){
        // indicating the 4 separation lines
        // no separation
        if (i != 0 && i != 4 && i != 8 && i != 12){
            separator = 0;
        }
        // separation
        else
        {
            separator = 1;
            printf("\n");
        }

        // line
        for (j = 0; j < 25; j++){
            // if separation line
            if (separator == 1){
                // print '+' every 8 character
                if (j == 0 || j == 8 || j == 16 || j == 24){
                    printf("%c ", line[0][0]); // '+'
                }else{
                    // print '-' in between
                    printf("%c ", line[0][1]); // '-'
                }
            }// end of separator = 1
            // NO separation line
            else if (separator == 0)
            {
                // print the first '|' in a new line
                j == 0 ? printf("\n%c", row[0][0]) : 0 ; // '|'

                // print '|' every 8 character
                if (j == 8 || j == 16 || j == 24){
                    printf(" %c ", row[0][0]); // '|'
                }
                // print '.' as placeholder. It is a 9x5 Block but for better lookings the dots have spaces in between and look like
                else if (j == 2 || j == 4 || j == 6 || j == 10 || j == 12 || j == 14 ||j == 18 || j == 20 || j == 22)
                {
                    printf(" %c ", line[0][2]); // '.'
                }else
                {
                    printf(" "); // '.'
                }
            }// end of separator = 0
        }//end of for line
    }// end of for (row)

    return 0;
}

int main()
{
    printField();
    return 0;
}
