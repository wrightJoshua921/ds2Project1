/* Student Name: Joshua Wright 
 * File Name: hash.c
 * Assignment Number: 1
 *
 * This file is the hash table
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

hash_table_t *create_hash_table(int size)
{
    int i;
    
    hash_table_t *new_table;
    
    if(size < 1) return NULL; //invalid size for table
    
    //try to allocate memory for the table struct
    if((new_table = malloc(sizeof(hash_table_t))) == NULL) {
        return NULL;
    }
    
    //try to allocate memory for the table
    if((new_table->table = 
            malloc(sizeof(list_t *) * size)) == NULL) {
        return NULL;
    }
    
    //initialize the elements of the table 
    for(i = 0; i < size; i++)
        new_table->table[i] = NULL;
    
    //set the table's size
    new_table->size = size;
    
    return new_table;
}

int hash(hash_table_t *hashtable, char *str)
{
	unsigned int hashval = 0;
	int i;
	for(i = 0; str[i] != '\0'; i++)
	{
		hashval = 31 * hashval + str[i];
	}
 	hashval = hashval % hashtable->size;
	
	if(hashval < 0) 
		hashval = hashval * -1; 
  	return hashval;
}

list_t *lookup_string(hash_table_t *hashtable, char *str)
{
    list_t *list;
    int hashval = hash(hashtable, str);

    //go to the correct list based on the hash value and see if str is 
    //in the list. If it is, return a pointer to the list element.
    // if not, the item isnt in the table, return NULL
   for(list = hashtable->table[hashval]; list != NULL; list = list->next){
       if(strcmp(str, list->string) == 0)
            return list;
     }    
    return NULL;
}

char add_string(hash_table_t *hashtable, char *str)
{
    list_t *new_list;
    list_t *current_list;
    unsigned int hashval = hash(hashtable, str);
    
    //allocate memory for list
    
    if((new_list = malloc(sizeof(list_t))) == NULL)
    return 1;
	//if(hashtable->table[hashval] == NULL)
	//	new_list = malloc(sizeof(list_t));
    //check to see if the item already exist
    current_list  = lookup_string(hashtable, str);
    //item already exists, dont insert it again
    if(current_list != NULL) return 2;
    //insert into list
    new_list->string = strdup(str);
    new_list->next = hashtable->table[hashval];
    hashtable->table[hashval] = new_list;
    
    return 0;
}

int count_strings(hash_table_t *hashtable)
{
	int i, count = 0;
	list_t *list;

	/*error check to make sure hashtable exists */
	if(hashtable == NULL) return -1;

	/*go through every index and count all list elements
 		in each index */
	for(i = 0; i < hashtable->size; i++)
	{
		for(list = hashtable->table[i]; list != NULL; list = list->next)
			count++;
	}
	return count;
}
void delete_table(hash_table_t *hashtable)
{
    //Free the table itself
    free(hashtable->table);
    free(hashtable);
}
void free_table(hash_table_t *hashtable)
{
	int i;
        list_t *list, *temp;
	if(hashtable == NULL)
		return;
	
	 for(i = 0; i < hashtable->size; i++){
        	list = hashtable->table[i];
        	while(list != NULL){
            		temp = list;
            		list = list->next;
            		free(temp->string);
            		free(temp);
        	}	
    	}
}
