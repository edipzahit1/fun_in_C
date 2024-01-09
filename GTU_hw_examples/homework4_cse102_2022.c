#include <stdio.h>


int main()
{
    int choice;
    int a, b, c;
    int x, y;
    while (1)
    {
        printf("Select an operation.\n0.Enter the coefficents.\n1.Draw the graph.\n2.Print the graph into a .txt file.\n3.Exit\n\nChoice:");
        scanf(" %i",&choice);

        switch (choice)
        {
        case 0:
            printf("Enter the coefficents x = a(y*y) + b*y + c\n");
            printf("a:");
            scanf("%i",&a);
            printf("b:");
            scanf("%i",&b);
            printf("c:");
            scanf("%i",&c);

            for ( y = 15; y >= -15; --y )
            {
                for ( x = -50; x <= 50; ++x )
                {
                    if ( x == (a*y*y + b*y + c) )
                    {
                        if ( y == -1 )
                        {
                            printf("\x1b[34m\b#\x1b[0m");
                        }
                        else
                        {
                            printf("\x1b[34m#\x1b[0m");
                        }
                    }
                    else if ( x == 0 && y == 15 )
                    {
                        printf("^");
                    }
                    else if ( y == 15 && x == -2 )
                    {
                        printf("\b15");
                    }
                    else if ( y == 10 && x == -2 )
                    {
                        printf("\b10");
                    }
                    else if ( y == 5 && x == -2 )
                    {
                        printf("5");
                    }
                    else if ( y == -5 && x == -2 )
                    {
                        printf("\b-5");
                    }
                    else if ( y == -10 && x == -2 )
                    {
                        printf("\b\b-10");
                    }
                    else if ( y == -15 && x == -2 )
                    {
                        printf("\b\b-15");
                    }
                    else if ( y == -1 && x == - 50 )
                    {
                        printf("-50");
                    }
                    else if ( y == -1 && x == - 40 )
                    {
                        printf("\b\b-40");
                    }
                    else if ( y == -1 && x == - 30 )
                    {
                        printf("\b\b-30");
                    }
                    else if ( y == -1 && x == - 20 )
                    {
                        printf("\b\b-20");
                    }
                    else if ( y == -1 && x == - 10 )
                    {
                        printf("\b\b-10");
                    }
                    else if ( y == -1 && x == -1 )
                    {
                        printf("\b0");
                    }
                    else if ( y == -1 && x == 10 )
                    {
                        printf("\b\b10");
                    }
                    else if ( y == -1 && x == 20 )
                    {
                        printf("\b\b20");
                    }
                    else if ( y == -1 && x == 30 )
                    {
                        printf("\b\b30");
                    }
                    else if ( y == -1 && x == 40 )
                    {
                        printf("\b\b40");
                    }
                    else if ( y == -1 && x == 50 )
                    {
                        printf("\b\b50");
                    }
                    else if ( x == 0 )
                    {
                        if ( y == -1 )
                        {
                            printf("\b|");
                        }
                        else
                        {
                            printf("|");
                        }
                    }
                    else if ( y == 0  && x == -50 ) 
                    {
                        printf("<");
                    }
                    else if ( y == 0 )
                    {
                        printf("-");
                    }
                    else if ( y == 0 && x == 50 )
                    {
                        printf(">");
                    }
                    else 
                    {
                        printf(" ");
                    }
                }
                printf("\n");
            }
            break;
        case 1:

        default:
            break;
        }
    }
}

