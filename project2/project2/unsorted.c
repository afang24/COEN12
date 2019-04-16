/*
	Alex Fang
	4/9/19
	Project 2 - Week 2
	Unsorted.c
*/

#include "set.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct set
{
	int count;	//address of the array; string stuff
	int length;	//length of the array
	char* *data;	//number of elements in the array 
};

typedef struct set SET;


static int search(SET *sp, char *elt);


SET *createSet(int maxElts)
{
	SET *sp;
	sp = malloc(sizeof(SET));	//allocating memoring for the set 
	assert(sp!=NULL);		//assert set has memory

	sp->count = 0;			//initialize address 
	sp->length = maxElts;		//initialize length to max

	sp->data = malloc(sizeof(char *) *maxElts);	//allocate data
	assert(sp->data!=NULL);				//assert data has memory
	return sp;
}		


void destroySet(SET *sp)
{
	int i; 
	assert(sp != NULL);	

	//have to do reverse order, free data, then the array of pointers, then the set
	for(i = 0; i < sp->count; i++)	//free data
	{
		free(sp->data[i]);
	}
	free(sp->data);		//free array
	free(sp);		//free set

}

int numElements(SET *sp)
{
	assert(sp != NULL);
	return(sp -> count);
}

void addElement(SET *sp, char *elt)
{
	assert((elt!=NULL)&& (sp!=NULL) && (sp->length > sp->count));
	char * NewElt;
	int posn;
	posn = search(sp, elt);		//search for new element
	if(posn == -1)			//add if not found
	{
		NewElt = strdup(elt);		//ensures element has memory; alllocates memory using malloc, copies the string and returns a pointer to the copy
		assert(NewElt != NULL);		//add element
		sp->data[sp->count++] = NewElt;	//increment counter
	}	
}

void removeElement(SET *sp, char *elt)
{
	assert((sp != NULL) && (elt != NULL));		//assert ability to remove element from set
	int locn;
	locn = search(sp,elt);			//search for element to delete
	if(locn != -1) {			//if found
		free(sp->data[locn]);		//free element move last element ot empty space 
		sp->data[locn] = sp->data[--sp->count];	//decrement counter
	}
}

char *findElement(SET *sp, char *elt)
{
	assert((sp != NULL) && (elt != NULL));		//assert ability to find element
	int locn;
	locn = search(sp, elt);				//search for elemenet
	if(locn == -1)					//returns null if not found
		return NULL;
	return sp->data[locn];				//returns ponter to location if found
	
}

char **getElements(SET *sp)
{
	assert(sp != NULL);		//assert ability to get elements
	char ** DataCopy;		//create memory for copy
	DataCopy = malloc(sizeof(char *)*sp -> length);
	assert(DataCopy != NULL);	//assert copy has memory
	int i;
	for(i=0; i<sp->count; i++)		//initialize pointers to elements of original array
		DataCopy[i] = sp->data[i];
	return DataCopy;
}

static int search(SET *sp, char *elt)
{
	int i;
	for(i=0;i<sp->count;i++)	//traverse data to look for elt
	{
		if(strcmp(sp->data[i], elt) == 0)	//return location if found
			return i;
	}
	return -1;	//not found returns -1	
}



