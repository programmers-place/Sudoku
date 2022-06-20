#include <stdio.h>
#include <stdlib.h>

/* prints field
*
* @param 2d int array 
* @return 0
*/
int printField(int field[9][9]) {

    // 0 = no separation line , 1 = separation line
    int separator = 0;

    // row 
    for (int i = 0; i < 9; i++) {
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
        for (int j = 0; j < 25; j++) {
            // if separation line
            if (separator == 1){
                // print '+' every 8 character
                if (j == 0 || j == 8 || j == 16 || j == 24){
                    printf("+ "); // '+'
                }else{
                    // print '-' in between
                    printf("- "); // '-'
                }
            }// end of separator = 1
            // NO separation line
            else if (separator == 0)
            {
                // print '|' as vertical separator in a new line 
                j == 0 ? printf("\n|") : 0 ; // '|'
                
                // print '|' every 8 character
                if (j == 3 || j == 6 || j == 9){
                    printf("|"); // '|'
                }

                //PRINT ARRAY 
                if (!(j >=9) )
                {
                    printf("%4i ", field[i][j]);
                }
                
            }
        }
    }
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

    printField(field);
    return 0;
}
