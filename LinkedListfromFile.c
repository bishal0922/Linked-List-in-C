// Bishal Giri 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef struct node
{
    int number;
    struct node *next_ptr;
} NODE;

void AddNodeToLL(int Number, NODE **LinkedListHead)
{
    NODE *TempPtr, *NewNode;

    NewNode = malloc(sizeof(NODE));
    NewNode->number = Number;
    NewNode->next_ptr = NULL;

    if (*LinkedListHead == NULL)
    {
        *LinkedListHead = NewNode;
    }
    else
    {
        TempPtr = *LinkedListHead;
        while (TempPtr->next_ptr != NULL)
        {
            TempPtr = TempPtr->next_ptr;
        }
        TempPtr->next_ptr = NewNode;
    }
}

void ReadFileIntoLL(int argc, char *argv[], NODE **LLH)
{
    FILE *myFile;
    char file_name[100];
    char file_line[10];
    int file_number, total_sum = 0, track_of_items = 0;
    char *token;

    if (argc == 2)
    {
        strcpy(file_name, argv[1]);
        myFile = fopen(file_name, "r");
    }
    else
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }
    // myFile = fopen("TestFile.txt", "r");

    while (fgets(file_line, sizeof(file_line) - 1, myFile))
    {
        token = strtok(file_line, " ");
        file_number = atoi(file_line);
        total_sum += file_number;
        track_of_items += 1;
        AddNodeToLL(file_number, LLH);
    }

    printf("\n%d records were read for a total sum of %d\n", track_of_items, total_sum);
}

void PrintLL(NODE *LLH)
{
    NODE *TempPtr = LLH;
    int total_sum = 0, track_of_items = 0;
    while (TempPtr != NULL)
    {
        total_sum += TempPtr->number;
        track_of_items++;
        printf("%p %d %p\n", TempPtr, TempPtr->number, TempPtr->next_ptr);
        TempPtr = TempPtr->next_ptr;
    }

    printf("\n%d records were read for a total sum of %d\n", track_of_items, total_sum);
}

void FreeLL(NODE **LLH)
{
    NODE *TempPtr = *LLH;
    NODE *PrevPtr = NULL;
    int total_sum = 0, track_of_items = 0;
    while (TempPtr != NULL)
    {

        PrevPtr = TempPtr;
        total_sum += PrevPtr->number;
        track_of_items++;
        TempPtr = TempPtr->next_ptr;
#ifdef PRINT
        printf("Freeing %p %d %p\n", PrevPtr, PrevPtr->number, PrevPtr->next_ptr);
#endif
        free(PrevPtr);
    }
    printf("\n%d nodes were deleted for a total sum of %d\n", track_of_items, total_sum);
}

int main(int argc, char *argv[])
{
    NODE *LLH = NULL;
    clock_t start, end;

    /* capture the clock in a start time */
    start = clock();
    ReadFileIntoLL(argc, argv, &LLH);
    /* capture the clock in an end time */
    end = clock();
    printf("\n%ld tics to write the file into the linked list\n", end - start);

    /* capture the clock in a start time */
#ifdef PRINT
    start = clock();
    PrintLL(LLH);
    /* capture the clock in an end time */
    end = clock();
    printf("\n%ld tics to print the linked list\n\n", end - start);
#endif

    /* capture the clock in a start time */
    start = clock();
    FreeLL(&LLH);
    /* capture the clock in an end time */
    end = clock();
    printf("\n%ld tics to free the linked list\n", end - start);

    return 0;
}
