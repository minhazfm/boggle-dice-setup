//***********************************************************************
// COP3502C - Boggle Assignment 1 - main.c
// Author: Minhaz Mohammad
// A C program that reads in data from a file and stores it as
// a linear linked list. A second linear linked list copies the
// data from the first linked list in to sixteen dice, each with
// six sides.
//***********************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for data
struct boggleDataNode
{
    char data[3];
    struct boggleDataNode *nextData;
};

// Struct for die
struct boggleDieSideNode
{
    char dieSideData[3];
    struct boggleDieSideNode *nextSide;
};

// Function to add character from file to BoggleData Linked List
void addBoggleData(struct boggleDataNode **head1, char * ch)
{
    struct boggleDataNode *temp = NULL;
    struct boggleDataNode *right = NULL;

    temp = (struct boggleDataNode *)malloc(sizeof(struct boggleDataNode));

    strcpy(temp->data, ch);

    temp->nextData = NULL;

    if (*head1 == NULL)
    {
        *head1 = temp;
    }
    else
    {
        right = *head1;

        while(right->nextData != NULL)
        {
            right = right->nextData;
        }

        right->nextData = temp;
    }

    return;
}

// Function to read the data file "BoggleData.txt"
void read(struct boggleDataNode **head1)
{
    char ch[3];

    FILE *input;

    input = fopen("BoggleData.txt", "r");

    if (input == NULL)
    {
        printf("Cannot open data file.\n");
    }
    else
    {
        while(fscanf(input, "%s", ch) != EOF)
        {
            addBoggleData(head1, ch);
        }
    }

    fclose(input);

    return;
}

// Function to add a node to the linked list that contains the side data for each die
void addBoggleDieSide(struct boggleDataNode *head1, struct boggleDieSideNode **head2, int index)
{
    int i = 0;

    struct boggleDieSideNode *temp = NULL;
    struct boggleDieSideNode *right = NULL;

    struct boggleDataNode *helper = NULL;

    temp = (struct boggleDieSideNode *)malloc(sizeof(struct boggleDieSideNode));

    helper = (struct boggleDataNode *)malloc(sizeof(struct boggleDataNode));

    helper = head1;

    for(i = 0; i < index; i++)
    {
        helper = helper->nextData;
    }

    strcpy(temp->dieSideData, helper->data);

    temp->nextSide = NULL;

    if (*head2 == NULL)
    {
        *head2 = temp;
    }
    else
    {
        right = *head2;

        while(right->nextSide != NULL)
        {
            right = right->nextSide;
        }

        right->nextSide = temp;
    }

    return;
}

// Function to display the nodes of the linked list that contains the data from the data file
void displayDataFile(struct boggleDataNode *head1)
{
    int value = 0;
    struct boggleDataNode *temp = NULL;
    temp = (struct boggleDataNode *)malloc(sizeof(struct boggleDataNode));

    temp = head1;

    printf("**** Displaying Boggle Data ****\n");

    if(temp == NULL)
    {
        return;
    }
    else
    {
        while(temp != NULL)
        {
            printf("Data value %d : %s\n", value, temp->data);
            value++;

            temp = temp->nextData;

            if(temp == NULL)
            {
                break;
            }
        }
    }

    return;
}

// Function to display the nodes of the linked list that contains the data on the six sides of the die
void displayDieSide(struct boggleDieSideNode *head2)
{
    int value = 0;
    struct boggleDieSideNode *temp = NULL;
    temp = (struct boggleDieSideNode *)malloc(sizeof(struct boggleDieSideNode));

    temp = head2;

    if(temp == NULL)
    {
        return;
    }
    else
    {
        while(temp != NULL)
        {
            printf("Side %d : %s\n", value, temp->dieSideData);
            value++;

            temp = temp->nextSide;

            if(temp == NULL)
            {
                break;
            }
        }
    }

    return;
}

// Main function
int main()
{
    int counter = 0;
    int i = 0;
    int j = 0;

    struct boggleDataNode *head1 = NULL;
    struct boggleDieSideNode *head2 = NULL;

    read(&head1);

    displayDataFile(head1);

    for(i = 0; i < 16; i++)
    {
        head2 = NULL;

        for(j = 0; j < 6; j++)
        {
            addBoggleDieSide(head1, &head2, counter);
            counter++;
        }

        printf("\n");
        printf("**** Displaying Die Side Data ****\n");
        displayDieSide(head2);
    }

    return 0;
}
