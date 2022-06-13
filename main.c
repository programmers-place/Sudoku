#include <stdio.h>
#include <stdlib.h>

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
