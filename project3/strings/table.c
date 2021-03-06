/*
	Alex Fang
	4/23/19
	COEN 12 - Project 3 part 1(string implementation)
	Utilizing a hash table of strings to store data	
*/


#include "set.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct set
{
	int count;	//count of elements
	int length;	//length
	char* *data;	//data
	char *flags;	//flags for data
};

static unsigned strhash(char *s);
static int search (SET* sp, char* elt, bool *found);


//complexity - O(n)
//create hashtable with an identifier array
SET *createSet(int maxElts)
{
	SET *sp;	
	sp = malloc(sizeof(SET));	//create set assign set pointer
	assert(sp != NULL);
	
	sp -> count = 0;		//set count to 0
	sp -> length = maxElts;		//set lenght to max elements
	sp -> flags = malloc(sizeof(char) *maxElts);	//allocate array of flags
	assert(sp -> flags != NULL);

	sp -> data = malloc(sizeof(char *) *maxElts);	//allocate array of data
	assert(sp -> data != NULL);

	for(int i = 0; i < maxElts; i++)		//assign each data a 'E'mpty flag
	{
		sp -> flags[i] = 'E';
	}
	return sp;
}

//complexity - O(n)
//free data point, idetnfier array and hashtable in reverse order
void destroySet(SET *sp)
{
	assert(sp != NULL);
	int i;
	for(i = 0; i < sp -> length; i++)
	{
		if(sp -> flags[i] == 'F')	//if data flag is F(full) free it
		{
			free(sp -> data[i]);
		}
	}
	free(sp -> data);	//free data
	free(sp -> flags);	//free flags
	free(sp);		//free set
}

//complexity - O(1)
//get number of elements in the set
int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp -> count;

}


//complexity - O(1) average O(n) worst case
//add element to set, increment count , change flag to F
void addElement(SET *sp, char *elt)
{
	assert((sp != NULL) & (elt != NULL));
	bool found;
	char *newElt;
	int index = search(sp, elt, &found);
	if(!found)					//add element if it not there
	{
		newElt = strdup(elt);
		assert(newElt != NULL);
		sp -> data[index] = newElt;
		sp -> flags[index] = 'F';		//set flag to filled
		sp -> count++;
	}
}
//complexity - O(1) average, O(n) worst case
//remove an element from set, decrement count , change flag to D
void removeElement(SET *sp, char *elt)
{
	assert((sp != NULL) & (elt != NULL));
	bool found;
	int index = search(sp, elt, &found);
	if(found)
	{
		free(sp -> data[index]);
		sp -> flags[index] = 'D';
		sp -> count--;
	}
}

//complexity - O(1) average, O(n) worst case
//find element in set return pointer to element if found else return NULL
char *findElement(SET *sp, char *elt)
{
	assert((sp != NULL) & (elt != NULL));
	bool found;
	int index = search(sp,elt,&found);
	if(!found)
	{
		return NULL;
	}
	return sp -> data[index];

}

//complexity - O(n)
//copy of elements in set
char **getElements(SET *sp)
{
	assert(sp != NULL);
	char **dataCopy;
	dataCopy = malloc(sizeof(char *)*sp->length);
	int i;
	int j = 0;

	for(i=0;i<sp->length;i++)
	{	
		if(sp->flags[i] == 'F') 
		{
			dataCopy[j] = sp->data[i];
			j++;
		}
	}
	return dataCopy;
}

////complexity - O(1) average, O(n) worst case
//search for element in set with hash function, linear probing
//Return index if found, else return index where element would be inserted.
//tell client if the element is found.
static int search(SET *sp, char *elt, bool *found)
{
	assert((sp!= NULL) && (elt != NULL));
	int index = strhash(elt)%sp->length;
	int deleted = -1;
	int locn;
	int i = 0;
	while(i<sp->length)
	{	locn = (index + i) % (sp->length);
		if(sp->flags[locn] == 'D') 
		{
			if(deleted == -1)
			{ 				// Record first deleted location, otherwise keep searching */
				deleted = locn;
			}
		}
		else if(sp->flags[locn] == 'E') 
		{ 	// Case to stop searching */
			*found = false;
			if(deleted == -1) 		// Preference to give deleted index if there is one when not found */
			{
				return locn;
			}
			return deleted;
		}
		else if(strcmp(sp->data[locn],elt) == 0)
		{						 /* Case found */
			*found = true;
			return locn;
		}
		i++;
	}
	*found = false;
	return deleted;
}

////complexity - O(1) 
//hash function
static unsigned strhash(char *s){
	unsigned hash = 0;
	assert(s != NULL);
	while(*s != '\0')
		hash = 31 * hash + *s++;
	return hash;
}







