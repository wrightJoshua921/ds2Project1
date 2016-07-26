/* Student Name: Joshua Wright
 * File Name: queue.h
 * Assignment Number: 1
 *
 *This is the header file with my struct and function prototypes
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#ifndef QUEUE_H
#define QUEUE_H

//my node struct for my queue and i declare my structure variables right after the struct
//template 
struct node
{
	char *info;
	struct node *ptr;

}*front, *rear, *temp, *front1;

//In this function I take the individual tokens and add them to the queue
void enq(char *data);

//I delete the top token in this function
void deq();

//In this function I take the individual tokens and create a word phrase and
//then hash that word phrase in the hash table
void hashQ(hash_table_t *hashtable, char *hashName, int compareQ);

//I initialize the queue in this function
void create();

//I set the queue to NULL in this function
void delete();
#endif

