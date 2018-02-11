
// -I flag tells gcc to search the following directories for header files

#include <stdio.h>	//gcc will search in these headers in /usr/include directory
#include <string.h>
#include <stdlib.h>

#include "db.h"	//gcc will search for headers with "..." in current directory

//max size of DB
static int maxSize = 0; //static is used so vars are only accessable through db.c

//Current num records
static int numRecords = 0;

//The database
static TPhonebook* database = NULL;

//free memory if database was previously initialized
void initPhonebook(int maxRecords) {
	if(database != NULL)
		free(database);

	maxSize = maxRecords;
	numRecords = 0;

	//Call calloc to allocate memory for phonebook.
	//calloc is different from malloc in that you can specify number of variables and size of each variable
	//calloc also clears memory it allocates
	database = (TPhonebook *) calloc(maxSize, sizeof(TPhonebook));
}

//Assuming phonebook has been initialized, add a new person into it
//result is either OK, MAX_REACHED, or DUPLICATE
void addPerson(char* name, char* countryCode, char* phoneNumber, int* result) {
	if(numRecords >= maxSize)
		*result = MAX_REACHED; //must deallocate pointer
	else {
		if(findPerson(name) != NULL)
			*result = DUPLICATE;
		else {
			//strncpy allows to specify max number of char, preventing stack overflow attacks
			strncpy(database[numRecords].name, name, NAME_LENGTH);
			strncpy(database[numRecords].countryCode, countryCode, C_LENGTH);
			strncpy(database[numRecords].phoneNumber, phoneNumber, NUM_LENGTH);

			//Adding the 'deleted' flag
			database -> deleted = 0;
			database -> index = numRecords++;
			*result = OK;
		}
	}
}

//looks for person in the phonebook using a full string match - returns NULL if not found
TPhonebook *findPerson (char* name) {
	int i;
	int found = 0;
	TPhonebook* result = NULL;

	//run through all records

	for (i = 0; i < numRecords && !found; i++) {
		found = (strcmp(name, database[i].name) == 0);

		//don't look for deleted records
		if (found && !database[i].deleted)
			result = &database[i];
	}

	return result;
}

//List contents of phonebook
void listPhonebook() {
	printf("\nPHONE LISTING\n");
	printf(	  "============\n\n");

	//check if database is initialized
	if(database != NULL) {
		int i;

		//print details of every record that isn't deleted
		for (int i = 0; i < numRecords; i++)	
			if(!database[i].deleted)
				printf("%d: %s (%s)-(%s)\n", i + 1, database[i].name,
						database[i].countryCode, database[i].phoneNumber);
	}

	else
		printf("*** EMPTY ***\n\n");
}

int deletePerson(char* name) {

	TPhonebook* result = findPerson(name);

	if(result == NULL)
		return CANNOT_FIND;
	else {
		//if found, set deleted flag to true
		result -> deleted = 1;
		return OK;
	}
}

//save phonebook, return SAVE_FAIL or OK. Data may not be saved if error occurs
int saveDB(char* filename) {

	//this is how to open a file, "w" means only for writing. fopen returns pointer to 
	//structure of type FILE which contains info like where we are in a file
	FILE *fp = fopen(filename, "w");

	//returns NULL if there's been an error
	if(fp != NULL) {
		fprintf(fp, "%d %d\n", maxSize, numRecords);

		//go over all records and store everything including deleted records
		for (int i = 0; i < numRecords; i++)
			fprintf(fp, "%d\n%d\n%s\n%s\n%s\n", database[i].index, database[i].deleted,
					database[i].name, database[i].countryCode, database[i].phoneNumber);

		fclose(fp);
		return OK;
	}
	else
		return SAVE_FAIL;
}

void stripNL(char* str) {
	int NLIdx = strlen(str) - 1;

	if(str[NLIdx] == '\r' || str[NLIdx] == '\n')
		str[NLIdx] = '\0';
}

int loadDB(char* filename) {
	FILE *fp = fopen(filename, "r");

	int dbSize, dbRecords;

	if(fp != NULL) {
		fscanf(fp, "%d %d\n", &dbSize, &dbRecords);
		printf("Read %d records max DB size is %d\n", dbRecords, dbSize);

		//initializing phone book will deallocate any previouslly initialized phonebooks
		initPhonebook(dbSize);

		for(int i = 0; i < dbRecords; i++) {
			char buffer[128];

			fscanf(fp, "%d\n", &database[i].index);
			fscanf(fp, "%d\n", &database[i].deleted);

			//fscanf reads only up to the first white space or new line
			//fgets will read all the way up to new line character, problem is it also gets
			//new line
			fgets(buffer, NAME_LENGTH, fp);
			stripNL(buffer);
			printf("%d: Name: %s\n", i, buffer);
			strcpy(database[i].name, buffer);

			fgets(buffer, NAME_LENGTH, fp);
			stripNL(buffer);
			printf("%d: Country Code: %s\n", i, buffer);
			strcpy(database[i].countryCode, buffer);
			
			fgets(buffer, NAME_LENGTH, fp);
			stripNL(buffer);
			printf("%d: Phone Number: %s\n", i, buffer);
			strcpy(database[i].phoneNumber, buffer);

		}

		maxSize = dbSize;
		numRecords = dbRecords;
		return OK;
	}
	else
		return LOAD_FAIL;
}

void resizeDB(int numNewRecords) {
	maxSize += numNewRecords;
	database = (TPhonebook *) realloc(database, sizeof(TPhonebook) * maxSize);
}

void getDBSize(int *nr, int *ms) {
	*nr = numRecords;
	*ms = maxSize;
}

void freePhonebook() {
	if(database != NULL)
		free(database);
}

























