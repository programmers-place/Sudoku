#include <stdio.h>
#include <stdlib.h>

int fieldOutput(int field[9][9]) {
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

int printField()
{
    char line [3] = {'+', '-', '.'};
    char row = '|';
    // 0 = no separation line , 1 = separation line
    int separator = 0;
    int i, j;

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
                    printf("%c ", line[0]); // '+'
                }else{
                    // print '-' in between
                    printf("%c ", line[1]); // '-'
                }
            }// end of separator = 1
            // NO separation line
            else if (separator == 0)
            {
                // print the first '|' in a new line
                j == 0 ? printf("\n%c", row) : 0 ; // '|'

                // print '|' every 8 character
                if (j == 8 || j == 16 || j == 24){
                    printf(" %c ", row); // '|'
                }
                // print '.' as placeholder. It is a 9x5 Block but for better lookings the dots have spaces in between and look like
                else if (j == 2 || j == 4 || j == 6 || j == 10 || j == 12 || j == 14 ||j == 18 || j == 20 || j == 22)
                {
                    printf(" %c ", line[2]); // '.'
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
    int field[9][9];

    int k = 1;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            field[i][j] = k;
            k++;
        }
        k = 1;
    }

    fieldOutput(field);
    return 0;
}
