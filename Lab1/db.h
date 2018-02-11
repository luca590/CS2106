
#ifndef PHONEBOOK

#define PHONEBOOK

#define NAME_LENGTH	64
#define C_LENGTH 	4
#define NUM_LENGTH 	10

typedef struct {
	unsigned index;
	int deleted;
	char name[NAME_LENGTH];
	char countryCode[C_LENGTH];
	char phoneNumber[NUM_LENGTH];
} TPhonebook;

enum {
	OK = 0,
	MAX_REACHED = 1,
	DUPLICATE = 2,
	CANNOT_FIND = 3,
	SAVE_FAIL = 4,
	LOAD_FAIL = 5
};
	
//Initializes phonebook with the argument passed as the max number of records
void initPhonebook (int maxRecords);

//phonebook has already been initlialized - free it. Afterwards no longer accessible
void freePhonebook();

//Add person into phonebook
void addPerson(char* name, char* countryCode, char* phoneNumber, int* result);

//Look for person in phonebook, but only do full mathces, not partial. Returns NULL if not found
TPhonebook *findPerson(char* name);

//List contents of phone book with stdout
void listPhonebook();

// If person doesn't exist, returns CANNOT_FIND
int deletePerson (char* name);

//returns OK if successful and SAVE_FAIL if unsucessful
int saveDB(char* filename);

//returns OK if successful and LOAD_FAIL if unsucessful
int loadDB(char* filename);

//Resize phonebook - increment maximum number of records by 'numNewRecords'
void resizeDB(int numNewRecords);

//nr = number of non-empty records in phonebook, ms = Maximum size of phonebook (in records)
void getDBsize(int *nr, int *ms);

#endif

