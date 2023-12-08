#include <stdio.h>
#include <stdbool.h>

int numberOfElements (char str[])
{
    int i = 0;
    while ( str[i] != '\0' )
    {
        ++i;
    }
    return i;
}

void insertString (char source[], char insert[], int start)
{
    int i,j,k;
    char newSource[150];

    for (i = 0; i < start; ++i)    // start a kadar olanları yeni stringe insertledik.
    {
        newSource[i] = source[i];
    }

    for (j = 0; j < numberOfElements(insert); ++j)   // stringimizi insertledik.
    {
        newSource[start + j] = insert[j];
    }

    for (k = start + numberOfElements(insert); i < numberOfElements(source); ++k)  // tamamladık.
    {
       newSource[k] = source[i];
       ++i;
    }

    for (i = 0; i < k; ++i)
    {                           
        source[i] = newSource[i];
    }
    
}

int findString (char source[], char search[])
{
    int i = 0, j = 0, k = 0;

    while ( source[i] != '\0' )
    {
        if ( source[i] == search[0] )                    
        {
            while ( search[j] != '\0' && search[j] == source[i] )        
            {
                ++j;
                ++i;
                if ( j == numberOfElements(search) )                 
                {
                    return i - numberOfElements(search);                                            
                }                   
            }
            j = 0; 
        }
        else 
        {
            ++i; 
        }
    }
    return -1;
}

void removeString (char string[], int start, int count)
{
    int i = 0;
    int numberOfElements(char str[]);
    if ( start + count > numberOfElements(string) )
    {
        count = numberOfElements(string) - start;
    }

    for ( i = start; i < numberOfElements(string); ++i)
    {
        string[i] = string[i + count] ;
    }
    string[i + 1] = '\0';
}

bool replaceString (char text[], char oldStr[], char newStr[])
{
    bool isFound = true;
    int startingIndex = findString(text, oldStr);

    if (startingIndex == -1)
    {
        isFound = false;
        return isFound;
    }
    removeString(text, startingIndex, numberOfElements(oldStr));

    insertString(text, newStr, startingIndex);

    return isFound;
}

int main (void)
{
    char text[150] = "ahmet gel ";
    char old[] = "e";
    char new[] = "a";
    bool stillFound;

    do{
        stillFound = replaceString(text,old,new);
    }while ( stillFound == true );
    
    printf("%s",text);
}