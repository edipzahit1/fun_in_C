#include <stdio.h>

struct doubly
{
    int val;
    struct doubly *next;
    struct doubly *prev;  
};

struct deneme
{
    char car;
    struct deneme *next;
};

struct entry
{
    int value;
    struct entry *link;
};

void insertEntry(struct entry *insert, struct entry *head, int ins_index)
{
    struct entry *temp;
    temp = head;
    
    for(int i = 1; i < ins_index - 1; ++i)
    {
        temp = temp->link;
    }
    insert->link = temp->link;
    temp->link = insert;    
}

void removeEntry(struct entry *head, int rem_index)
{
    struct entry *temp;
    temp = head;
    for(int i = 1; i < rem_index - 1; ++i)
    {
        temp = temp->link;
    }
    temp->link = temp->link->link;
    temp->link->link = NULL;  // çıkarılan entry nin bağlantısını kestik.
}

int main (void)
{
    struct entry n1,n2,n3,n1_1;
    struct entry *listPointer = &n1;

    struct entry dic[] =              // linked listi böyle tanımlayabilirsin.
    {{1,NULL},{2,NULL},{3}};    // pointerin adresini null yapmadan da işini görebilirsin.

    for(int i = 0; i < 2; ++i)              //linked listi linkledik.
        dic[i].link = &dic[i + 1];

    printf("%i ",dic[1].link->value);    

    struct entry lab[5] = {{3},{4},{5}};   // kalan integerlar 0 a atar. 

    for(int i = 0; i < 4; ++i)
        lab[i].link = &lab[i + 1];

    printf("%i ",lab[3].link->value);

    struct deneme arr[5] = {{'z'},{'y'},{'x'}};   //kalan char lara space karakteri atar.

    for(int i = 0; i < 4; ++i)
        arr[i].next = &arr[i + 1];

    printf("%c ",arr[3].next->car);

    for(int j = 0; j < 3; ++j)
        printf("%c",arr[j].car);

    n1.value = 100;
    n1.link = &n2;

    n2.value = 200;
    n2.link = &n3;

    n3.value = 300;
    n3.link = NULL;

    n1_1.value = 400;
    n1_1.link = NULL;

    insertEntry(&n1_1,listPointer,2);

    printf("%i",n1.link->link->value);

//doubly linked lists...

    void doublyInsertEntry(struct doubly *insert, struct doubly *head, int ins_index);
    void doublyRemoveEntry(struct doubly *head, int rem_index);

    printf("\n\ndoubly linked list\n\n");

    struct doubly duo[3] =      
    { 
    {10,NULL,NULL},
    {20,NULL,NULL},
    {30,NULL,NULL}
    };

    for(int i = 0; i < 3; ++i)           //ileri doğru bağladık.
        duo[i].next = &duo[i + 1];

    for(int i = 3; i > 0; --i)          //geri doğru bağladık.
        duo[i].prev = &duo[i - 1];

    struct doubly *head_point;
    head_point = &duo[0];

    struct doubly toInsert;
    
    toInsert.val = 40;
    toInsert.next = NULL;
    toInsert.prev = NULL;

    doublyInsertEntry(&toInsert,head_point,2);

    printf("\n%i",duo[0].next->val);

    doublyRemoveEntry(head_point,2);

    printf(" %i",duo[0].next->val);
}

void doublyInsertEntry(struct doubly *insert, struct doubly *head, int ins_index)
{
    struct doubly *temp;
    temp = head;

    if(ins_index == 1)                  //listenin başına eklenecekse.
    {
        insert->next = temp;
        temp->prev = insert;
    }
    else
    {
        for(int i = 1; i < ins_index - 1; ++i)          //listenin herhangi bir yerine eklenecekse.
        {   
            temp = temp->next;
        }
        insert->next = temp->next;
        temp->next->prev = insert;
        temp->next = insert;
        insert->prev = temp;
    }
}

void doublyRemoveEntry(struct doubly *head, int rem_index)
{
    struct doubly *temp;
    temp = head;

    if(rem_index == 1)                  //listenin başındaki elemanı kaldırır.
    {
        temp->next = NULL;
        temp->next->prev = NULL;
    }
    else                                //listenin herhangi bir yerindeki elemanı kaldırır.
    {
        for(int i = 1; i < rem_index - 1; ++i)  
        {
            temp = temp->next;
        }
        temp->next->next->prev = temp;
        temp->next = temp->next->next;
    }
}