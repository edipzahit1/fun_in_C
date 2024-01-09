#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int dice(void);
int startGame(void);
void PrintMap(char map[15][30]);

int main()
{
    srand(time(NULL));

    char map[15][30]  =
{    
    "..............................",
    ".1            X              .",
    "._.......................... .",
    ". .2      X       X        . .",
    ". ._...................... . .",
    ". . .                    .X. .",
    ". . .                    . . .",
    ". . .                    . .X.",
    ". . .                    . . .",
    ". . .                    . . .",
    ". . ......................X. .",
    ". .       X       X        . .",
    ". .......................... .",
    ".             X              .",
    ".............................."
};    

    int player1Penalties[3][2] = {{1, 14}, {7, 28}, {13, 14}};
    int player2Penalties[6][2] = {{3, 10}, {3, 18}, {5, 26}, {10, 26}, {11, 10}, {11, 18}};
    int player_turn = startGame();
    int player_1_x = 1, player_1_y = 1;
    int player_2_x = 3, player_2_y = 3;

    while (1)   // game loop.
    {
        PrintMap(map);

        int roll = dice();  
        
        printf("Enter a character to toss.\n");
        getchar();
        printf("Player %i rolled %i!!\n",player_turn, roll);
            
        if (player_turn == 1)
        {
            map[player_1_x][player_1_y] = ' ';
                if ( (player_1_x == 1) && (player_1_y) != 28 )  // the statement != 28 is for the top right corner in case the next move is 6.
                {
                    if ( (player_1_y + roll) != player1Penalties[0][1] )
                    {
                        if ( (player_1_y + roll) < 29 )
                        {
                            player_1_y += roll;
                        }
                        else
                        {
                            player_1_x = roll - (28 - player_1_y) + 1;
                            player_1_y = 28;
                        }
                    }
                    else
                    {
                        player_1_y += roll;
                        printf("Player 1 stepped on X 2 moves back!!\n");
                        player_1_y -= 2;
                    }     
                }
                else if ( (player_1_y == 28) )
                {
                    if ( (player_1_x + roll) != player1Penalties[1][0] )
                    {
                        if ( (player_1_x + roll) < 13 )
                        {
                            player_1_x += roll;
                        }
                        else
                        {
                            player_1_y -= (player_1_x + roll) - 13;
                            player_1_x = 13;
                        }
                    }
                    else if ( (player_1_x + roll) == player1Penalties[1][0] )
                    {
                        player_1_x += roll;
                        printf("Player 1 stepped on X 2 moves back!!\n");
                        player_1_x -= 2;
                    }
                    else if ( (player_1_x == 1) && roll == 6 )
                    {
                        player_1_x += roll;
                        printf("Player 1 stepped on X 2 moves back!!\n");
                        player_1_x -= 2;
                    }
                }
                else if ( (player_1_x == 13) )
                {
                    if ( (player_1_y - roll) != player1Penalties[2][1] )
                    {
                        if ( (player_1_y - roll) > 0 )
                        {
                            player_1_y -= roll;
                        }
                        else
                        {
                            player_1_x = 13 - ( roll - player_1_y );
                            player_1_y = 1;
                        }
                    }
                    else 
                    {
                        player_1_y -= roll;
                        printf("Player 1 stepped on X 2 moves back!!\n");
                        player_1_y += 2;
                    }
                }
                else if ( (player_1_y == 1) )
                {
                    if ( (player_1_x - roll) > 0 )
                    {
                        player_1_x -= roll;
                    }
                    else
                    {
                        player_1_y = 3 + (roll - player_1_x);
                        player_1_x = 1;
                    }
                }
            
            map[player_1_x][player_1_y] = '1';

            if (player_1_x == 2 && player_1_y == 1)
            {
                PrintMap(map);
                printf("Player 1 won!!\n");
                exit(EXIT_SUCCESS);
            }
            player_turn = (player_turn == 1) ? 2 : 1;
            continue;
        }

        if (player_turn == 2)
        {
            map[player_2_x][player_2_y] = ' ';
            if ( (player_2_x == 3) )
            {
                if ( (player_2_y + roll) != player2Penalties[0][1] && (player_2_y + roll) != player2Penalties[1][1])
                {
                    if ( (player_2_y + roll) <= 26 )
                    {
                        player_2_y += roll;
                    }
                    else
                    {
                        player_2_x += (player_2_y + roll) - 26;
                        player_2_y = 26;
                    }
                }
                else
                {
                    player_2_y += roll;
                    printf("Player 2 stepped on X 2 moves back!!\n");
                    player_2_y -= 2;
                }
            }
            else if ( (player_2_y == 26) )
            {
                if ( (player_2_x + roll) != player2Penalties[2][0] && (player_2_x + roll) != player2Penalties[3][0] )
                {
                    if ( (player_2_x + roll) < 11 )
                    {
                        player_2_x += roll;
                    }
                    else
                    {
                        player_2_y -= (player_2_x + roll) - 11;
                        player_2_x = 11;
                    }
                }
                else
                {
                    player_2_x += roll; //we are assinging this because we want to step back from the position where the X is.
                    printf("Player 2 stepped on X 2 moves back!!\n");
                    player_2_x -= 2;
                }
                if ( (player_2_x == 3) && (player_2_y == 26) && (player_2_x + roll) == player2Penalties[2][0] )
                {
                    player_2_x += roll; 
                    printf("Player 2 stepped on X 2 moves back!!\n");
                    player_2_x -= 2;
                }
            }
            else if ( (player_2_x == 11) )
            {
                if ( (player_2_y - roll) != player2Penalties[4][1] && (player_2_y - roll) != player2Penalties[5][1] )
                {
                    if ( (player_2_y - roll) >= 3 )
                    {
                        player_2_y -= roll;
                    }
                    else
                    {
                        player_2_x -= roll - (player_2_y - 3);
                        player_2_y = 3;
                    }
                }
                else
                {
                    player_2_y -= roll;
                    printf("Player 2 stepped on X 2 moves back!!\n");
                    player_2_y += 2;
                }
            }
            else if ( (player_2_y == 3) )
            {
                if ( (player_2_x - roll) >= 3 )
                {
                    player_2_x -= roll;
                }
                else
                {
                    player_2_y += roll - (player_2_x - 3);
                    player_2_x = 3;
                }
            }
            map[player_2_x][player_2_y] = '2';
            
            if (player_2_x == 4 && player_2_y == 3)
            {
                PrintMap(map);
                printf("Player 2 won!!\n");
                exit(EXIT_SUCCESS);
            }
            player_turn = (player_turn == 1) ? 2 : 1;
            continue;
        }

        
    }
    

}

void PrintMap(char map[15][30])
{
    for (int i = 0; i < 15; ++i)
    {
        for (int j = 0; j < 30; ++j)
        {
            if (map[i][j] == 'X')
            {
                printf("\x1b[31m%c\x1b[0m",map[i][j]);
            }
            else if (map[i][j] == '1')
            {
                printf("\x1b[34m%c\x1b[0m",map[i][j]);
            }
            else if (map[i][j] == '2')
            {
                printf("\x1b[35m%c\x1b[0m",map[i][j]);
            }
            else if (map[i][j] == '_')
            {
                printf("\x1b[33m%c\x1b[0m",map[i][j]);
            }
            else
            {
                printf("%c",map[i][j]);
            }
        }
        printf("\n");
    }
}

int dice(void)
{
    return rand() % 6 + 1;
}

int startGame(void)
{
    int player1Dice = dice();
    int player2Dice = dice();

    if (player1Dice > player2Dice)
    {
        printf("Player 1 goes first!!\n");
        return 1;
    }
    else if (player2Dice > player1Dice)
    {
        printf("Player 2 goes first!!\n");
        return 2;
    }
    else
    {
        printf("It is a tie! Rolling again.\n");
        return startGame();
    }

}