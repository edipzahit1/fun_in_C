#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAP_SIZE 7
#define WORD_COUNT 3

char Map[MAP_SIZE][MAP_SIZE];

void initializeMap();
void placeWord(char *word, int row_index, int col_index, int direction);
int isValid(char *word, int row_index, int col_index, int direction);
void generateMap(char *words[WORD_COUNT]);
void printMap();
int isFound(char *word, int row, int col);
void updateMap(char *word, int row, int col, int direction);

void initializeMap()
{
    for (int i = 0; i < MAP_SIZE; ++i)
        for (int j = 0; j < MAP_SIZE; ++j)
            Map[i][j] = ' ';
}

//function to place the word in map
void placeWord(char *word, int row_index, int col_index, int direction)
{
    int change_in_row[] = {-1, 0, 1, -1, 1, -1, 0, 1};      //these arrays represent the increment and decrement operations 
    int change_in_col[] = {1, 1, 1, 0, 0, -1, -1, -1};      //for direction variable
    int i = 0;

    while (word[i] != '\0')
    {
        int row = row_index + i * change_in_row[direction];     //adjust the row and col to correct position 
        int col = col_index + i * change_in_col[direction];

        Map[row][col] = word[i]; //put the char
        ++i;
    }
}

//function to check if a word can be placed in a coordinate
int isValid(char *word, int row_index, int col_index, int direction)
{
    int change_in_row[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int change_in_col[] = {1, 1, 1, 0, 0, -1, -1, -1};
    int length = strlen(word);
    
    int last_row = row_index + (length - 1) * change_in_row[direction];
    int last_col = col_index + (length - 1) * change_in_col[direction];

    if (last_row < 0 || last_row >= MAP_SIZE || last_col < 0 || last_col >= MAP_SIZE)   return 0; 
    
    for (int i = 0; i < length; i++)
    {
        int row = row_index + i * change_in_row[direction];
        int col = col_index + i * change_in_col[direction];
        if (Map[row][col] != ' ' && Map[row][col] != word[i])   return 0; 
    }
    return 1;
}

//function to generate random map each run
void generateMap(char *words[WORD_COUNT])
{
    int wordCounter = WORD_COUNT - 1;
    do
    {
        int row_index = rand() % MAP_SIZE;      //get random coordinates and random direction
        int col_index = rand() % MAP_SIZE;
        int direction = rand() % 8;

        if (isValid(words[wordCounter], row_index, col_index, direction))   //check if is valid to put the word
        {
            placeWord(words[wordCounter], row_index, col_index, direction); //if so, put the word
            wordCounter--;  //decrement words put
        }
    } while (wordCounter >= 0);

    //put random chars remaining indexes
    for (int i = 0; i < MAP_SIZE; ++i)
    {
        for (int j = 0; j < MAP_SIZE; ++j)
        {
            if (Map[i][j] == ' ')
            {
                Map[i][j] = (rand() % 26) + 'a';
            }
        }
    }
}

void printMap()
{
    for (int i = 0; i < MAP_SIZE; ++i)
    {
        for (int j = 0; j < MAP_SIZE; ++j)
        {
            printf("%c ",Map[i][j]);
        }
        printf("\n");
    }
}

//function to check if inputted word and coordinate found in map
//returns direction if found //else -1
int isFound(char *word, int row, int col)
{
    int change_in_row[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int change_in_col[] = {1, 1, 1, 0, 0, -1, -1, -1};
    int direction, i = 0;

    for (int direction = 0; direction < 8; ++direction) 
    {
        int i;
        for (i = 0; word[i] != '\0'; ++i) 
        {
            int row_toBeSearched = row + i * change_in_row[direction];
            int col_toBeSearched = col + i * change_in_col[direction];

            if (row_toBeSearched < 0 || row_toBeSearched >= MAP_SIZE || col_toBeSearched < 0 || 
                col_toBeSearched >= MAP_SIZE || Map[row_toBeSearched][col_toBeSearched] != word[i]) 
            {
                break;
            }
        }
        if (word[i] == '\0') 
        {
            return direction;
        }
    }
    return -1;
}

//function to put X es to found words indexes
void updateMap(char *word, int row, int col, int direction)
{
    int change_in_row[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int change_in_col[] = {1, 1, 1, 0, 0, -1, -1, -1};
    
    for (int len = 0; len < strlen(word); ++len)
    {
        int new_row = row + len * change_in_row[direction];
        int new_col = col + len * change_in_col[direction];
        Map[new_row][new_col] = 'X';
    }
}

int main()
{
    char *words[WORD_COUNT] = {"gemi","pamut","kahve"};
    int remainingChance = 3;
    int wordCounter = WORD_COUNT;
    char word[MAP_SIZE];
    int row, column;

    srand(time(NULL));

    initializeMap();
    generateMap(words);
    
    do
    {
        printMap();
        
        printf("\nEnter the word (enter \":q\" to finish)\n");
        scanf("%s", word);
        if (strcmp(":q", word) == 0)
            break;
        
        printf("and coordinate (x,y) \n");
        scanf("%i%i", &row, &column);
        
        int dir = isFound(word, row, column);

        if (dir != -1)
        {
            updateMap(word, row, column, dir);
            wordCounter--;
            printf("Correct!!\n\n");
        }
        else
        {
            printf("\nThere is no word %s at (%i, %i)\n", word, row, column);
            remainingChance--;
            printf("You have %i chances left.\n",remainingChance);
        }  
        if (wordCounter == 0 || remainingChance == 0) 
            break; 
    } while (1);

    if (wordCounter == 0)
    {
        printf("\n\033[0;32mCONGRULUCATIONS!! YOU HAVE WON!!\033[0m\n");
    }
    else
    {
        printf("\n\033[0;31mYOU FUCKING MORON YOU KNOW NOTHING IDIOT GO FUCK YOURSELF.\033[0m\n");
    }
}