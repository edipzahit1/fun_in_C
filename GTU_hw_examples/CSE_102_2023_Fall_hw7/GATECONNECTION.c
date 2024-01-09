#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct gate
{
    int type;
    char name[20];
    struct gate *inp1;
    struct gate *inp2;
    int output;
    int former_out;
}gate;

enum GATES {INPUT, OUTPUT, AND, OR, NOT, FLIPFLOP};

void purifyGates(gate **gates);                             //set all flipflops former_out to be -1 
int calculate(gate *root);                                  //evalute the inputs in the circuit
int getGATEcount(char *fileName);                           //find the total gates of the circuit in order to allocate memory for ptr array
void buildTree(char *fileName, gate **gates);               //build the tree
int getGATEtype(char *gateName);                            //get the enum GATE type
void createGate(int gateType, char *gateName, gate **gates);//allocate memory and place values to a gate
void connectGates(char *from, char *to, gate **gates);      //link the gates
void putInputsAndCalc(char *filename, gate **gates, int gateCount);//put the inputs in the input gates

int getGATEcount(char *fileName)
{
    FILE *ptr = fopen(fileName, "r");
    if (ptr == NULL)
    {
        printf("Can't open file.(at \"getGATEcount\")\nShutting down...");
        exit(EXIT_FAILURE);
    }
    char line[50];
    int count = 0;
    while (fgets(line, sizeof(line), ptr)) //read the file line by line until null 
    {
        if (line[0] == 'G')  count++;   //count occurunces of G character
    }
    fclose(ptr);
    return count;
}

void buildTree(char *fileName, gate **gates)
{
    FILE *ptr = fopen(fileName, "r");
    if (ptr == NULL)
    {
        printf("Can't open file.(at \"buildTree\")\nShutting down...");
        exit(EXIT_FAILURE);
    }
    char line[50];

    while (fgets(line, sizeof(line), ptr))
    {
        char instruction[20], str1[10], str2[10];
        sscanf(line, "%s %s %s", instruction, str1, str2);  //parse every line and get 3 strings

        if (instruction[0] == 'G')      //if it starts with GATE 
        {
            int type = getGATEtype(str1);   //get the type of the gate
            createGate(type, str2, gates);  //and create a node (connect it with pointer array gates[])
        }
        else
        {
            connectGates(str1, str2, gates);    //if it is CONNECTION link the gates
        }
    }
    fclose(ptr);
}

int getGATEtype(char *gateName) //function to get type of the GATE
{
    if (gateName[0] == 'I') return INPUT;
    if (gateName[0] == 'O')
    {
        if (gateName[1] == 'U') return OUTPUT;
        else                    return OR;
    }
    if (gateName[0] == 'A') return AND;
    if (gateName[0] == 'N') return NOT;
    if (gateName[0] == 'F') return FLIPFLOP;
}

void createGate(int gateType, char *gateName, gate **gates)
{
    int i = 0;
    while (gates[i] != NULL) {++i;}

    gate *newGate = (gate *)malloc(sizeof(gate));

    strcpy(newGate->name, gateName);
    newGate->type = gateType;
    gates[i] = newGate;
    newGate->output = -1;
    newGate->former_out = 0; //for flipflop
    newGate->inp1 = NULL;
    newGate->inp2 = NULL;
    //gates[i]->inp1 = NULL;
    //gates[i]->inp2 = NULL;
}

void connectGates(char *child, char *parent, gate **gates)
{
    gate *childGate = NULL;
    gate *parentGate = NULL;
    for (int i = 0; gates[i] != NULL; ++i)  //locate the child node
    {
        if (strcmp(gates[i]->name, child) == 0)
        {
            childGate = gates[i];
            break;
        }
    }
    for (int i = 0; gates[i] != NULL; ++i)  //locate the parent node
    {
        if (strcmp(gates[i]->name, parent) == 0)
        {
            parentGate = gates[i];
            break;
        }
    }   

    if (childGate != NULL && parentGate != NULL)
    {
        //if type is flipflop or not and trying to connect some node to inp2
        //print error message and return
        if (parentGate->inp1 != NULL && (parentGate->type == FLIPFLOP || parentGate->type == NOT)) 
        {
            printf("FLIPFLOP or NOT gate cant take more than one input.\n");
            return;   
        }
        else if (parentGate->inp1 == NULL)    parentGate->inp1 = childGate;  //if inp1 is empty link parent to child
        else if (parentGate->inp2 == NULL)    parentGate->inp2 = childGate;  //if inp2 is empty link parent to child 
        else printf("Gate %s already have 2 inputs.\n", parentGate->name);
    }
    else    //if childGate or parentGate are not located print error message
    {
        printf("Cannot locate gates %s %s.\n", child, parent);
    }
}

void putInputsAndCalc(char *filename, gate **gates, int gateCount)
{
    FILE *ptr = fopen("input.txt", "r");
    if (ptr == NULL)
    {
        printf("File could not open(input.txt).\n");
        exit(EXIT_FAILURE);
    }

    gate *root = NULL;  
    for (int i = 0; i < gateCount; ++i) 
    {
        if (gates[i]->type == OUTPUT) //find the output gate
        {
            root = gates[i];
            break;
        }
    }

    char line[10];
    while (fgets(line, sizeof(line), ptr))
    {
        int i = 0, j = 0;
        while (line[i] != '\n' && gates[j] != NULL)
        {
            if (gates[j]->type == INPUT)
            {
                gates[j]->output = line[i] - '0';
                ++i;
            }
            ++j;
        }
        //we are sending root->inp1 because in calculate function
        //we dont want to encounter OUTPUT gate
        //because of switch-case logic
        purifyGates(gates);
        int outputVal = calculate(root->inp1);  
        printf("%i\n", outputVal);
    }
    fclose(ptr);
}

void purifyGates(gate **gates) {
    int i = 0;
    while (gates[i] != NULL) 
    {
        if (gates[i]->type == FLIPFLOP) 
        {
            gates[i]->output = -1; 
        } 
        ++i;
    }
}

int calculate(gate *root)
{
    if (root->type == INPUT) 
    {
        return root->output;
    }
    //if it has been in ff while calculating same line return the former output (output is flag)
    if ((root->type == FLIPFLOP && root->output != -1))  
    {
        return root->former_out;
    }
    int inp1;

    switch (root->type)
    {
        case FLIPFLOP:
            inp1 = calculate(root->inp1);

            if (inp1 == 0 && root->former_out == 0) {
                root->former_out = 0;
            } else if (inp1 == 1 && root->former_out == 0) {
                root->former_out = 1;
            } else if (inp1 == 0 && root->former_out == 1) {
                root->former_out = 1;
            } else if (inp1 == 1 && root->former_out == 1) {
                root->former_out = 0;
            }
            root->output = root->former_out;
            return root->output;
        case AND:     
            return calculate(root->inp1) && calculate(root->inp2); 
        case OR:      
            return calculate(root->inp1) || calculate(root->inp2); 
        case NOT:     
            return !calculate(root->inp1);
    }
}

int main()
{
    int gateCount = getGATEcount("circuit.txt");
    gate **gates = (gate **)calloc(gateCount + 1, sizeof(gate *));

    buildTree("circuit.txt", gates);

    putInputsAndCalc("input.txt", gates, gateCount);

    for (int i = 0; i < gateCount; ++i) 
        free(gates[i]);
    free(gates);
}