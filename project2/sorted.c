/*
	Alex Fang
	4/16/19
	Project 2 - Week 3
	Sorted.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "set.h"

struct set{
	int count;	//address of the array; string stuff
	int length;	//length of the array
	char* *data;	//number of elements in the array 
};

typedef struct set SET;

static int search(SET *sp, char *elt, bool *found);


SET *createSet(int maxElts)
{
	SET *sp;
        sp = malloc(sizeof(SET));			//allocate memory for set, assert set has memory
        assert(sp != NULL);
        sp -> count = 0;				//initilize count to 0
        sp -> length = maxElts;				//initlize length to max elements
        
	sp ->data = malloc(sizeof(char *) * maxElts);	//allocate memory for data, assert data has memory
        assert(sp ->data != NULL);
        return sp;
}		


void destroySet(SET *sp)
{
	int i;
        for(i=0; i<sp->count; i++)	//free data
                 free(sp->data[i]);
        free(sp->data);			//free array
        free(sp);			//free set
}


int numElements(SET *sp)
{
	assert(sp != NULL);
	return sp->count;
}

void addElement(SET *sp, char *elt)
{
         assert((elt != NULL) && (sp != NULL) && (sp->length > sp->count));	// Assert ability to add string to set 
         char * NewElt;
         int posn;
         int i;
         bool found;
         posn = search(sp, elt,&found);			//search for new element
         if(!found)	//if not found add
         {
                 // Make sure element has memory, add element, increment counter 
                 NewElt = strdup(elt);
                 assert(NewElt != NULL);
                 for(i=sp->count;i>posn;i--)
                         sp->data[i] = sp->data[i-1];
                 sp->data[posn] = NewElt;
                 sp->count++;
         }	
}

void removeElement(SET *sp, char *elt)
{
         assert((sp != NULL) && (elt != NULL));		//Assert ability to remove element from set
         int locn;
         int i;
         bool found;
         locn = search(sp,elt,&found);	//search for element to delete
         if(found) {	//if found = remove
                 // Free element, move last element to empty space, decrement counter 
                 free(sp->data[locn]);
                 for(i=locn+1;i<sp->count;i++)
                         sp->data[i-1] = sp->data[i];
                 sp->count--;
         }

}


char *findElement(SET *sp, char *elt)
{
	assert((sp != NULL) && (elt != NULL));			//assert ability to search for elements
        int locn;
        bool found;
        locn = search(sp, elt, &found);			//search for element
        if(!found)
	{						//RETURNS null if not found
                 return NULL;
        }
        return sp->data[locn];			//returns pointer to location if found
	
}

char **getElements(SET *sp)
{
        assert(sp != NULL);		//assert ability to get elements
        // Create memory for copy, assert copy has memory
        char ** DataCopy;
        DataCopy = malloc(sizeof(char *) * sp -> length);
        assert(DataCopy != NULL);
        int i;
        for(i=0; i<sp->count; i++)		//initlize pointers to elements of original array
	{
                 DataCopy[i] = sp->data[i];
        } 
	return DataCopy;

}

static int search(SET *sp, char *elt, bool *found)
{
	int lo, hi, mid, diff;		//initlize variables
	lo = 0;
	hi = sp->count - 1;

	while(lo <= hi)			//loop for binary search
	{
		mid = (lo+hi)/2;
		diff = strcmp(elt, sp->data[mid]);		//compare middle element with elt then changes the bounds
		if(diff < 0)				//if element is less that 0 sets high to the middle minus 1
		{
			hi = mid - 1;
		}
		else if(diff > 0)			//if element is more than 0 sets low to the middle plus 1
		{			
			lo = mid + 1;
		}
		else
		{
			*found = true;			//sets found to trye returns elements index
			return mid;
		}
	}	
	*found = false;					//set foudn to flase returns indec where insertion would start
	return lo;
}




