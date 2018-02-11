
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





