/* Student Name: Joshua Wright
 * File Name: compare.c
 * Assignment Number: 1
 *
 * Created on August 28, 2015, 6:30 PM
 *
 * This file is my main file. It opens inputfile.txt and puts each file name in an array and 
 * then uses that array to create a path to open each individuale file. It then uses that to 
 * create tokens of each word in each file and adds them to a queue. With that queue it 
 * creates word phrases depending on the number of phrases the user gives us. With that word
 * phrase I hash that individual word phrase. All of this happens with the 1st file.
 * After I have the phrases from the first file, I then open up all the files below that and 
 * token them, queue them, phrase them, and then compare those phrases with the phrases in
 * the hash table.
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "queue.h"
#define NameLength 20000
char line[20000] = {'\0'};
char theFileName[30][NameLength];
char hashName[NameLength] = {'\0'};
char fname[NameLength];
char *token;
char *search = " ";
int adder = 0;
/*
 *
 *
 */ 
void isList(hash_table_t *hashtable, list_t *list, char *hashName);
void openFile(hash_table_t *hashtable, list_t* list, char *line, char *fname, char theFileName[30][NameLength], int word, FILE *file, char *hashName, int a);
void compareFile(hash_table_t *hashtable, list_t* list, char *line, char *fname, char theFileName[30][NameLength], int word, char *hashName, int b);
void fileLength(FILE *file1, char theFileName[30][NameLength], int lines);
/*
 *
 *
 */
int main(int argc, char** argv) {
	system("ls ./datafiles/ > inputfile.txt");

	//create my queue
	create();

        int a = 0,b = 1, i, j, word, ch = 0, lines = 0;

	//get user input
	do
	{
		printf("What is the number of words to analyze(2-10)?\n");
		scanf("%d", &word);

	}while(word < 2 || word > 10);
    
	//create and initialize my hash table
	hash_table_t *my_hash_table;
	int size_of_table = 80000;
	my_hash_table = create_hash_table(size_of_table);
	

	//set my list in the hashtable to NULL
	list_t *list = NULL;	
        
	//open up the inputfile.txt
	FILE *file1;
	file1 = fopen("inputfile.txt", "r");
	//count how many files are being used inside inputfile.txt
	while(!feof(file1))
        {
                ch = fgetc(file1);
                if(ch == '\n')
                {
                        lines++;
                }
        }
	//use this function to exchange the newline given by fgets with \0
	fileLength(file1, theFileName, lines);
        fclose(file1);	

	//initialize my 2d array to 0
	int simWords[lines][lines];
	for(i = 0; i < lines; i++){
                for(j = 0; j < lines; j++){
                        simWords[i][j] = 0;
                }
        }
	//my loop to hash the phrases from the first file and phrase and compare from all the other files
	while(a < lines)
	{
		openFile(my_hash_table, list, line, fname, theFileName, word, file1, hashName, a);

		while(b < lines)
		{
			compareFile(my_hash_table, list, line, fname, theFileName, word, hashName, b);
			simWords[a][b] = adder;
			b++;
			adder = 0; 
		} 
		a++;
		b = a + 1; 
	}

	//printing out my 2d array of file comparison information
	printf("File Comparison\n");
	printf("Word Phrase Length: %i \n\n", word);
	printf("      ");
	for(i = 0; i < lines; i++)
		printf("%-5i", i);
		 
	printf("\n\n");
	for(i = 0; i < lines; i++){
		if(i < 10)
			printf("%-4i ", i);
		else
			printf("%-4i ", i);
		for(j = 0; j < lines; j++){
			printf(" ");
			if(i <= j)
				printf("%-4i", simWords[i][j]);
			else

				printf("%-4c", '-');
	            
		}
		printf("\n");
	}
	//freeing my hashtable
	free_table(my_hash_table);
	delete_table(my_hash_table);
	
 
	return (EXIT_SUCCESS);
}

void fileLength(FILE *file1, char theFileName[30][NameLength], int lines)
{
	int i = 0;
        file1 = fopen("inputfile.txt", "r");
	while((i < lines) && (fgets(theFileName[i], NameLength, file1) != NULL))
        {
                size_t length = strlen(theFileName[i]);

        	if(theFileName[i][length-1] == '\n')
                {
                        theFileName[i][length - 1] = '\0';
                }
                i++;
        }
fclose(file1);
}
void isList(hash_table_t *hashtable, list_t *list, char *hashName)
{
	list = lookup_string(hashtable, hashName);
	if(list != NULL)
	{
		adder++;
        }else
		return;
       
}
void openFile(hash_table_t *hashtable, list_t* list, char *line, char *fname, char theFileName[30][NameLength], int word, FILE *file, char *hashName, int a)
{
	int compareQ = 1;

		memset(line, '\0', NameLength);
		int i = 0;
		strcpy(fname, "./datafiles/");
        	strcat(fname, theFileName[a]);
        	file = fopen(fname, "r");
        	fgets(line, NameLength, file);
		size_t ln = strlen(line) - 1;
                if(line[ln] == '\n')
                        line[ln] = '\0';

        	token = strtok(line, search);
		while(token != NULL)
		{	
			while(i < word && token != NULL)
			{
				enq(token);
				token = strtok(NULL, search);
				i++;
			}
			hashQ(hashtable, hashName, compareQ);
			memset(hashName, '\0', NameLength);
			deq();
			i = i - 1;
		}
		delete();
		fclose(file);
}

void compareFile(hash_table_t *hashtable, list_t* list, char *line, char *fname, char theFileName[30][NameLength], int word, char *hashName, int b)
{
	FILE *file;
	int compareQ = 3;

		memset(line, '\0', NameLength);
		int i = 0;
		strcpy(fname, "./datafiles/");
  	        strcat(fname, theFileName[b]);
        	file = fopen(fname, "r");
       		fgets(line, NameLength, file);
		size_t ln = strlen(line) - 1;
		if(line[ln] == '\n')
			line[ln] = '\0';

        	token = strtok(line, search);
		while(token != NULL)
		{
			while(i< word && token != NULL)
			{
				enq(token);
				token = strtok(NULL, search);
				i++;
			}
			hashQ(hashtable, hashName, compareQ);
			isList(hashtable, list, hashName);
			memset(hashName, '\0', NameLength);
			deq();
			i = i - 1;
		}
		delete();
		fclose(file);
}
