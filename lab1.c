/*
	Alex Fang
	4/2/19
	COEN 12 LAB #1
	Description: Counting number of words in a file
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_WORD_LENGTH 30

void countWords(char *file_name);

int main(int argc, char *argv[])	//argc = number of arguments  //argv = file name
{
	if(argc == 1)
	{
		printf("File name is missing.\n");
		return 1;
	}

	countWords(argv[1]);	
}

void countWords(char *file_name)
{
	FILE *fp;
	int counter = 0;	
	char fileName[MAX_WORD_LENGTH];

	fp = fopen(file_name, "r");

	if(fp == NULL)
	{
		printf("No file\n");
		return;
	}

	while(fscanf(fp,"%s",fileName) == 1)
	{
		counter++;	
	}
	
	fclose(fp);	
	printf("%d total words\n", counter); 
	return;
}








