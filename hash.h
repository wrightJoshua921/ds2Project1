/* Student Name: Joshua Wright
 * File Name: hash.h
 * Assignment Number: 1
 *
 * 
 * This is the hash table that holds that hword phrases
 */

#ifndef HASH_H
#define	HASH_H

typedef struct _list_t_{
    char *string;
    struct _list_t_ *next;
} list_t;

typedef struct _hash_table_t_{
    int size;
    list_t **table;
} hash_table_t;

//creation of a hash_table
hash_table_t *create_hash_table(int size);

//hash function
int hash(hash_table_t *hashtable, char *str);

//string lookup
list_t *lookup_string(hash_table_t *hashtable, char *str);

//inserting a string
char add_string(hash_table_t *hashtable, char *str);

//Deleting a table
void free_table(hash_table_t *hashtable);

int count_strings(hash_table_t *hashtable);

void delete_table(hash_table_t *hashtable);

#endif




