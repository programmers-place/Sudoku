#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a [9][9] ;
    FILE *f = fopen("file.txt", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    /* print integers and floats */
    int i = 1;
    int array [9][9] = {{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9},{1,2,3,4,5,6,7,8,9}};
    float pi= 3.1415927;


    for (int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            fprintf(f, "%d", array[x][y]);
            fprintf(f, "\n");
        }
    }


    fclose(f);

    ///////////////////////////////////////////////////////////////////////////////////////////
    FILE *pf = fopen ("file.txt", "r");
    if (pf == NULL) {
        return 0;
    }

    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            fscanf(pf, "%d", a[i] + j);
        }
    }



    fclose (pf);

    for (int x = 0; x < 9; x++){
        for (int y = 0; y < 9; y++){
            printf("%d", a[x][y]);
        }
        printf("\n");
    }
}
