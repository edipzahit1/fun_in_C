#include <stdio.h>
#define COLUMN_SIZE1 4
#define ROW_SIZE1 2
#define COLUMN_SIZE2 2
#define ROW_SIZE2 4
#define COMMON_LINE_SIZE 4 // it is the same as ROW_SIZE2 and COLUMN_SIZE1 but we wanted to initialize it seperately for the sake of readability.

int matrixMultp (int a[][COLUMN_SIZE1], int b[][COLUMN_SIZE2], int C[][50])
{
    for (int j = 0; j < COLUMN_SIZE2; ++j)
    {
        for (int i = 0; i < ROW_SIZE1; ++i)
        {
            for (int k = 0; k < COMMON_LINE_SIZE; ++k)
                C[i][j] += a[i][k]*b[k][j];
        }
    }
}

int main(void)
{
    int m1[ROW_SIZE1][COLUMN_SIZE1] = {
                    {1, 2, 3, 5},
                    {4, 5, 6, 8}
                   };
    int m2[ROW_SIZE2][COLUMN_SIZE2] = {
                    {1, 2},
                    {4, 5},
                    {3, 6},
                    {3, 2}
                   };
    int res[50][50] = {0};

    matrixMultp(m1,m2,res);

    for(int i = 0; i < ROW_SIZE1; ++i)
    {
        printf("\n");
        
        for(int j = 0; j < COLUMN_SIZE2; ++j)
            printf("%i\t",res[i][j]);
    }
}