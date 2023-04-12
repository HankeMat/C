#include "header.h"


/**
 * @brief Function that count the number of lines in the dictionary
 * 
 * @return Number of the lines
 */
int countWords(){
	FILE *file = fopen("dictionary.txt", "r");		//Opens file
	int count = 0;
	char line[80];
	
	while(fgets(line, 80, file)!=NULL){				//Going through the file 
		count++;									//Counting number of lines
	}
	
	fclose(file);									//Closing file
	return count;									//Returning number of lines
}

/**
 * @brief Function that saves stats into a file based on given parameters
 * 
 * @param correct 
 * @param percentage 
 * @param questionCount 
 * @param wrong 
 * 
 * @return -1 if error, 0 if OK
 */
int saveToFile(int questionCount, float correct, float wrong, float percentage){
	FILE *file = fopen("stats.txt", "a");		//Opens a file
	
	if(NULL == file){							//Error message
		return -1;
	}
	/*Saving into file*/
	fprintf(file, "Number of words: %d\nCorrect answers: %.0f\nWrong answers: %.0f\nSuccess: %.2f %%\n-------------------------\n", questionCount, correct, wrong, percentage);
	
	fclose(file);								//Closing file
	return 0;
}

/**
 * @brief Function that deletes chosen word from dictionary
 * 
 * @param word 
 * 
 * @return -1 if error, 0 if OK
 */
int deleteWord(char word[]){
	FILE *file = fopen("dictionary.txt", "r");			//Opening files
	FILE *temp = fopen("tempDictionary.txt", "w");
	toLowerCase(word);									//Converting chosen word to lowercase for comparison (In dictionary everything is saved in lowercase)
	if(NULL == file){									//Error message
		printf("Could not open file\n");
		return -1;
	}
	char line[80], *cz, *en, *lec;						//Declaration
	int lect;
	while(fgets(line, 80, file)!=NULL){					//Loop for going through entire file by lines
		cz = strtok(line, "|");							//Splitting string into more parts
		en = strtok(NULL, "|");
		lec = strtok(NULL, "|");
		lect = atoi(lec);
		
		if(strcmp(cz, word) == 0){						//Comparing chosen word with word in file
			continue;
		}
		fprintf(temp, "%s|%s|%d\n", cz, en, lect);		//Saving everything except choosed word into another file (temporary)
	}
	
	fclose(file);										//Closing all files
	fclose(temp);
	
	system("del dictionary.txt");						//Deleting old file
	system("rename tempDictionary.txt dictionary.txt");	//Renaming new file back to old name "dictionary.txt"
	
	return 0;
}

/**
 * @brief Function for editing selected word
 * 
 * @param word 
 * 
 * @return -1 if error, 0 if OK
 */
int editWord(char word[]){
	FILE *file = fopen("dictionary.txt", "r");		//Opens files
	FILE *temp = fopen("tempDictionary.txt", "w");
	toLowerCase(word);								//Chosen word to lowercase
	if(NULL == file){								//Error message
		printf("Could not open file\n");
		return -1;
	}
	char line[80], *cz, *en, *lec;					//Declaration
	int lect;
	while(fgets(line, 80, file)!=NULL){				//Loop to go through entire file by lines
		cz = strtok(line, "|");						//Spliting string
		en = strtok(NULL, "|");	
		lec = strtok(NULL, "|");
		lect = atoi(lec);							//Converting lection into integer from string
		
		if(strcmp(cz, word) == 0){					//Comparing whether we read the chosen word and asking to edit the word
			printf("Cz: ");
			fflush(stdin);
			gets(cz);
			fflush(stdin);
			printf("En: ");
			fflush(stdin);
			gets(en);
			printf("Lection: ");
			scanf("%d", &lect);
		}
		toLowerCase(cz);							//New word goes into lowercase
		toLowerCase(en);
	
		fprintf(temp, "%s|%s|%d\n", cz, en, lect);	//Writing everything into new file
	}
	
	fclose(file);									//Closing files
	fclose(temp);
	
	system("del dictionary.txt");					//Deleting old dictionary
	system("rename tempDictionary.txt dictionary.txt");		//Renaming new dictionary after old one
	
	return 0;
}


/**
 * @brief Function for testing from a word and randomly chosing between whether user will be translating into czech or english
 * 
 * @param cz 
 * @param en 
 * 
 * @return -1 if error, 0 if OK
 */
int testCZtoENorENtoCZ(char *cz, char *en){
	char answer[80];							//Declaration
	int randomNum = rand() % (1 - 0 + 1) + 0;	//Random number generated for deciding whether czech to english or otherwise
	
	if(randomNum == 0){							//First option Czech to English
		printf("%s = ", cz);
		fflush(stdin);
		gets(answer);
		toLowerCase(answer);
		
		if(strcmp(en, answer)==0){
			printf("Correct!\n");
			system("pause");
			return 1;
		}else{
			printf("Wrong :-(\n");
			printf("Correct answer is: %s\n", en);
			system("pause");
			return 0;
		}
	}else if(randomNum == 1){					//First option English to Czech
		printf("%s = ", en);
		fflush(stdin);
		gets(answer);
		toLowerCase(answer);
		
		if(strcmp(cz, answer)==0){
			printf("Correct!\n");
			system("pause");
			return 1;
		}else{
			printf("Wrong :-(\n");
			printf("Correct answer is: %s\n", cz);
			system("pause");
			return 0;
		}
	}
	return -1;
}

/**
 * @brief This function works as a random testing from all words in dictionary 
 * 
 * @return -1 if errors, 0 if OK 
 */
int testRNG(){
	FILE *file = fopen("dictionary.txt", "r");					//Opens the file "dictionary.txt"
	srand(time(NULL));											//Initialize random time
	int wordCount = countWords();
	char line[80];

	if(file == NULL){											//Condition in case there was a problem opening the file
		printf("Cannot open file\n");		
		return -1;												//Returns "-1" so the function doesn´t continue
	}
	

	int randomNumber = rand() % ((wordCount - 1) - 0 + 1) + 0;	//Generating a random number, in range of word count, that we look after afterwards
	int lineNumber = 0;											//Declaration
	int exists = 0;
	char *cz, *en;
	float cor = 0, wro = 0;
	
	while(fgets(line, 80, file)!=NULL){							//While loop to go through the entire file by lines
		cz = strtok(line, "|");									//Spliting string into two parts
		en = strtok(NULL, "|");									//Spliting string into two parts

		if(randomNumber == lineNumber){							//Condition if we found that random number
	
			int result = testCZtoENorENtoCZ(cz, en);			//Testing from that word
			
			if(result == 1){									//Conditions for recognizing if there was a correct answer or not
				//cor++;
			}else if(result == 0){
				//wro++;
			}
			exists++;
			
		}
		lineNumber++;										//Add up a 1 to lineNumber so we are comparing another number 
	}

	if(exists<1){												//Error message
		printf("Error\n");
	}

	fclose(file);													//Closing the file
	return 0;
}

/**
 * @brief A function for adding a word into file (dictionary)
 * 
 * @param lection 
 * @param wordCz 
 * @param wordEn 
 * 
 * @return 0 if correct, -1 if there was a problem opening the file
 */
int addWordToDic(char wordCz[], char wordEn[], int lection){
	system("cls");		
	FILE *file;								//Declaration
	
	file = fopen("dictionary.txt", "a");	//Opening the file int "append" mode
	if(file == NULL){						//Condition in case there was a problem opening the file
		printf("Cannot open file\n");		
		return -1;							//Returns "-1" so the function doesn´t continue
	}
	
	fprintf(file, "%s|%s|%d\n", wordCz, wordEn, lection);	//Writing selected words into file
	
	fclose(file);							//Closing file
	return 0;								
}


/**
 * @brief A function converting all high case characters into lower case characters
 * 
 * @param word 
 */
void toLowerCase(char word[]){			
	
	int j = strlen(word);					//Command for finding out the lenght of the string
	
	for(int i = 0; i < j; i++){				//Loop that goes through all the characters in the string
		word[i] = tolower(word[i]);		//Converting to lower case via "tolower" command that belongs to ctype.h library
	}
}


/**
 * @brief A function for reading from file (dictionary) using a while loop
 * 
 * @return 0 if correctly, -1 if there was a problem opening the file
 */
int readFromDic(){
	system("cls");							//Declaration
	FILE *file;
	
	file = fopen("dictionary.txt", "r");	//Opening the file in "read" mode
	
	if(file == NULL){						//Condition in case there was a problem opening the file
		printf("Cannot open file\n");
		return -1;							//Returns "-1" so the function doesn´t continue
	}
	
	char line[80], *cz, *en, *ltemp;		//Declaration if needed (if there was no problem opening the file)
	int lec;
	while(fgets(line, 80, file)!=NULL){			//While loop for going through entire file
		cz = strtok(line, "|");				//Splits a string into 2 strings 
		en = strtok(NULL, "|");				
		ltemp = strtok(NULL, "|");			
		lec = atoi(ltemp);					//Converts string into integer 
		
		printf("Cz: %s\nEn: %s\nLection: %d\n", cz, en, lec);	//Printing the result into console
		printf("===============\n");
	}
	fclose(file);							//Closing the file
	return 0;
}

/**
 * @brief Function for translating chosen word
 * 
 * @param word 
 * 
 * @return -1 if errors, 0 if OK
 */
int translate(char word[]){
	FILE *file;
	
	file = fopen("dictionary.txt", "r");
	if(file == NULL){						//Condition in case there was a problem opening the file
		printf("Cannot open file\n");
		return -1;							//Returns "-1" so the function doesn´t continue
	}
	
	toLowerCase(word);						//Converts word int lowercase
	char line[80], *cz, *en;				//Declaration
	int exists = 0;
	
	while(fgets(line, 80, file)!=NULL){		//While loop for going through entire file
		cz = strtok(line, "|");				//Splits string
		en = strtok(NULL, "|");

		if(strcmp(cz, word)==0){			//Comparing whether the chosen word is in the dictionary and whether user entered czech or english word
			system("cls");
			printf("%s = %s\n", cz, en);
			exists++;		
		}
		else if(strcmp(en, word)==0){
			system("cls");
			printf("%s = %s\n", en, cz);
			exists++;
		}
		
	}
	if(exists < 1){							//Error message
		printf("Dictionary does not contain this word\n");
	}
	fclose(file);							//Closing file
	return 0;
} 


/**
 * @brief Function for reading selected lection
 * 
 * @param lectionNum 
 * 
 * @return -1 if errors, 0 if OK
 */
int readLection(int lectionNum){
	FILE *file = fopen("dictionary.txt", "r");			//Opens file
	char line[80], *cz, *en, *lec;						//Declaration
	int lect, exists = 0;	
	
	while(fgets(line, 80, file)!=NULL){					//While loop for going through entire file
		
		cz = strtok(line, "|");							//Splits string
		en = strtok(NULL, "|");
		lec = strtok(NULL, "|");
		lect = atoi(lec);
		
		if(lect == lectionNum){							//Comparing lection and selected lection
			printf("%s\t|%s\t|%d\n", cz, en, lect);		//Printing words from the lection
			exists++;
		}
	}
	
	if(exists<1){										//Error message
		printf("Dictionary does not contain any word from selected lection\n");
	}
	
	fclose(file);										//Closing file
	return 0;
}

/**
 * @brief Function for testing user from selected lection
 * 
 * @param lectionNum 
 * 
 * @return -1 if errors, 0 if OK
 */
int testFromLection(int lectionNum){
	FILE *file = fopen("dictionary.txt", "r");		//Opens file
	srand(time(NULL));								//Initialize random time
	char line[80], *cz, *en, *lec;					//Declaration
	int lect, exists = 0;
	float cor = 0, wro = 0;
	
	while(fgets(line, 80, file)!=NULL){				//While loop for going through entire file
		
		cz = strtok(line, "|");						//Splits string
		en = strtok(NULL, "|");	
		lec = strtok(NULL, "|");
		lect = atoi(lec);
		
		if(lect == lectionNum){						//Comparing lection and selected lection
			int result = testCZtoENorENtoCZ(cz, en);//Testing from current word
			if(result == 0){						//Counting results
				wro++;
			}else if(result == 1){
				cor++;
			}
			exists++;
		}
	}
		
	if(exists<1){									//Error message
		printf("Dictionary does not contain any word from selected lection\n");
	}
	
	float per = (cor * 100)/exists;					//Calculating percentage success
	system("cls");
	
	printf("Evaluation\n");							//Printing stats
	printf("==========\n");
	printf("Number of words: %d\nCorrect answers: %.0f\nWrong answers: %.0f\nSuccess: %.2f %%\n\n", exists, cor, wro, per);
	
	int dec;
	
	printf("Do you want to save stats into file?(1-Yes 0-No): ");	//Asking whether user want to save stats into file
	scanf("%d", &dec);
	if(dec == 1){
		int check = saveToFile(exists, cor, wro, per);				//Saving to file
		
		if(check == -1){
			printf("Failed to save statistics\n");
		}else if(check == 0){
			printf("Saved successfully into \"stats.txt\"\n");
		}
	}
	

	fclose(file);				//Closing file
	return 0;
}
