/* Student Name: Joshua Wright
 * File Name: queue.c
 * Assignment Number: 1
 *
 *
 *This file works the queue and also creates the word phrases to be hashed
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#include "hash.h"
int count = 0; 
void create()
{
	front = rear = NULL;

}
void enq(char *data)
{
	if(rear == NULL)
	{
		rear = (struct node *)malloc(1*sizeof(struct node));
		rear->ptr = NULL;
		rear->info = data;
		front = rear;
	}
	else
	{
		temp = (struct node *)malloc(1*sizeof(struct node));
		rear->ptr = temp;
		temp->info = data;
		temp->ptr = NULL;

		rear = temp;
		
	}
	count++;
}
void hashQ(hash_table_t *hashtable, char *hashName, int compareQ)
{

	int i =0;
	front1 = front;

	if((front1 == NULL) && (rear == NULL))
	{
		printf("Queue is empty \n");
		return;
	}

	while(front1 != rear)
	{
		strcat(hashName, front1->info);
		strcat(hashName, " ");
		front1 = front1->ptr;	
		i++;
	}

	if(front1 == rear)
	{
		strcat(hashName, front1->info);
	}

        if(compareQ == 1)
	{
		add_string(hashtable, hashName);
	}
}
void deq()
{
	front1 = front;

	if(front1 == NULL)
	{
		printf("Error: Trying to display elements from empty queue!\n");
		return;
	}
	else
	   if(front1->ptr != NULL)
	   {
		front = front1->ptr;
		free(front1);
	   }
	   else
           {
		front = NULL;
		rear = NULL;
		free(front1);
	   }
	   count--;
}
void delete()
{
	struct node *var = rear;
	while(var != NULL)
	{
		struct node* buf = var->ptr;
		free(var);
		var = buf;
	}
	
	rear = NULL;
	front = NULL;
}
