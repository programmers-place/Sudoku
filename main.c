#include <stdio.h>
#include <stdlib.h>

/* prints field
*
* @param 2d int array 
* @return 0
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
            }// end of separator = 1
            // NO separation line 
            else if (separator == 0){
                // print '|' as vertical separator in a new line 
                line == 0 ? printf("\n|") : 0 ; // '|'

                // print '|' every 8 character
                if (line == 3 || line == 6 || line == 9){
                    printf("|"); // '|'
                }

                if(line < 9){
                    //DEBUG
                    //printf("|line = %i| ", line);
                    //printf("|y = %i| ", y);
                    printf("%4i ", field[y][line]);
                }

            }// end of separator = 0
        }// end of for line 
    }// end of for row 
    return 0;
}// end of printField

//debug purposes
int printArray(int userValue, int changeRow, int changeLine, int field[9][9]) {
    field[changeRow-1][changeLine-1] = userValue;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%2i", field[i][j]);
        }
        printf("\n");
    }
    return 0;
}


int main()
{
    int field[9][9];
    // for user input 
    int changeRow, changeLine, userValue;

    // TODO: outsource in function
    // fill array
    int k = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = k;
            // printf("%2i", field[i][j]);
            k++;
        }
        // printf("\n");
        k = 1;
    }
    // first time print for the user 
    printField(field);

    // get user input for changing values
    printf("\n\n______________________________________________  ");
    printf("\n\nZeile:  ");
    scanf("%i", &changeRow);
    printf("\nReihe: ");
    scanf("%i", &changeLine);
    printf("\nWert: ");
    scanf("%i", &userValue);
    printf("\n______________________________________________  ");
    
    // change specific spot 
    // added -1 because indexing starts with 1 now == first value is (1/1)
    field[changeRow-1][changeLine-1] = userValue;

    printField(field);
    
    return 0;
}// end of main 