/**
 * @file BookDatabase.c
 * @author Matěj Hanke (hanke.matej@seznam.cz)
 * @brief Program that works as database for books
 * @version 0.1
 * @date 2023-04-07
 * 
 * @copyright Copyright Hanke Matěj (c) 2023
 * 
 */

// Linking libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// New struct called Data used in struct Book
typedef struct data{
	int id;				//Declaration
	float price;
	char genre[40];
}Data;

// New struct called Book
typedef struct book{
	Data data;			//Declaration of nested struct
	struct book *prev, *next;	//Declaration of pointers to next and previous book
}Book;

// Global variable used as an start of the list
Book *first = NULL;

/**
 * @brief Adds a book into database
 * 
 * @param genre 
 * @param id 
 * @param price 
 */
void addToList(int id, float price, char genre[]){
	Book *new;							//Declaration of new book
	new = (Book*)malloc(sizeof(Book));	//Allocating space in memory for the new book
	
	if(NULL == new){					//Error message (If there is no space for new book)
		printf("Not enough space\n");
		system("pause");
		exit(1);
	}
	
	new->next = NULL;					//Setting the new´s book previous and next pointers to default NULL 
	new->prev = NULL;
	
	new->data.id = id;					//Adding data into new book
	new->data.price = price;
	strcpy(new->data.genre, genre);
	
	if(NULL != first){					//Condition whether there is another book or is not
		first->prev = new;				//Setting the new book into its place
		new->next = first;
		first = new;
	}else{
		first = new;					//Setting the new book into its place
	}
}

/**
 * @brief Adds book into the end of database
 * 
 * @param genre 
 * @param id 
 * @param price 
 */
void addToEndOfList(int id, float price, char genre[]){
	Book *new, *last;					//Declaration of new 2 books
	new = (Book*)malloc(sizeof(Book));	//Allocating space in memory for the new book (We dont allocate space for the "last" book, because it´ll be only as a pointer)
	
	if(NULL == new){					//Error message (If there is no space for new book)
		printf("Not enough space\n");
		system("pause");
		exit(1);
	}
	
	new->next = NULL;					//Setting the new´s book previous and next pointers to default NULL
	new->prev = NULL;
	
	new->data.id = id;					//Adding data into new book
	new->data.price = price;
	strcpy(new->data.genre, genre);
	
	if(NULL != first){					//Condition whether there is another book or is not
		last = first;					//Setting the "last" pointer to position of first pointer (default)
		while(last->next != NULL){		//Shifting the "last" pointer until it is in the end of the list
			last = last->next;
		}
		last->next = new;				//Setting the new book into its place 
	}else{
		first = new;					//Setting the new book into its place
	}
}

/**
 * @brief Function for reading and printing the database
 */
void readList(){
	Book *temp;							//Declaration of new Book (used just as pointer => no memory allocation)
	
	if(NULL == first){					//Error message whether there is a book in the list
		printf("There is nothing in the list\n");
		system("pause");
		exit(1);
	}
	
	for(temp = first;temp != NULL;temp = temp->next){	//Goinbg through entire database
		printf("Book ID: %d\n", temp->data.id);			//Printing every book´s data
		printf("Price: %.2f\n", temp->data.price);
		printf("Genre: %s\n", temp->data.genre);
	}
}

/**
 * @brief Looks after a book with wanted ID
 */
void findInListByID(){
	Book *temp;			//Declaration of a Book (used as a pointer => no allocation)
	
	if(NULL == first){	//Error message if the database is empty
		printf("There is nothing in the list\n");
		system("pause");
		exit(1);
	}

	int wantedID;		//Delaration
	printf("Enter wanted ID: ");	
	scanf("%d", &wantedID);	//Getting the wanted ID
	for(temp = first;temp != NULL;temp = temp->next){	//Goinbg through entire database
		if(temp->data.id == wantedID){					//Condition whether we found the entered id
			printf("ID: %d\n", temp->data.id);			//Printing that book´s data
			printf("Price: %.2f\n", temp->data.price);
			printf("Genre: %s\n", temp->data.genre);
		}
	}
}

/**
 * @brief Function that gives back highest price in the database
 * 
 * @return highest price (max)
 */
float highestPrice(){
	Book *temp;

	float max = first->data.price;	//Setting default max price to the first book
	
	for(temp = first;temp != NULL;temp = temp->next){	//Going through entire database 
		if(max < temp->data.price){						//Checking whether current max is less than book´s we are currently checking	
			max = temp->data.price;						//Setting new max price
			temp = first;								//Returning temp pointer back to first book, so it goes again from begining
		}
	}
	return max;
}

/**
 * @brief Function that gives back lowest price in the database
 * 
 * @return lowest price (min)
 */
float lowestPrice(){
	Book *temp;
	
	float min = first->data.price;	//Setting default min price to the first book
	
	for(temp = first;temp != NULL;temp = temp->next){	//Going through entire database 
		if(min > temp->data.price){						//Checking whether current min is greater than book´s we are currently checking
			min = temp->data.price;						//Setting new min price
			temp = first;								//Returning temp pointer back to first book, so it goes again from begining
		}
	}
	return min;
}

/**
 * @brief Sorts the database based on either ID or Genre 
 * 
 * @param byWhat (What is the sort based on)
 *
 * @return checking variable whether the sort was successful
 */
int sortBy(int byWhat) {
	Book *temp1, *temp2;	//Declaration of (pointers)
	int swap;				//Checking variable
	
	if (first == NULL) {	//Error message
		printf("There is nothing in the list\n");
		return -1;
	}
	
	if(byWhat == 1){		//Copndition whether the entered parameter was ID or Genre
		do {
			swap = 0;		//Sets default 0
			temp1 = first;	//Sets default position
			
			while (temp1->next != NULL) {	//Loop for going through entire database
				temp2 = temp1->next;		//Setting the next book just after temp1
				
				if (temp1->data.id > temp2->data.id) {	//Condition checking whether ID in temp1 is higher than ID in the temp2
					// Swap data
					Data tempData = temp1->data;		
					temp1->data = temp2->data;
					temp2->data = tempData;
					
					swap = 1;	//Sets checking variable to 1
				}
				
				temp1 = temp1->next;		//Shifting to another book
			}
		} while (swap);	//Do it again if there was a swap
		return 0;
	}else if(byWhat == 2){	//Completely the same except we are comparing genre in this one
		do {
			swap = 0;
			temp1 = first;
			
			while (temp1->next != NULL) {
				temp2 = temp1->next;
				
				if (strcmp(temp1->data.genre, temp2->data.genre) > 0) {
					// Swap data
					Data tempData = temp1->data;
					temp1->data = temp2->data;
					temp2->data = tempData;
					
					swap = 1;
				}
				
				temp1 = temp1->next;
			}
		} while (swap);
		return 0;
	}
	return -1;
}

/**
 * @brief Function that gives back average price in the database 
 * 
 * @return average price
 */
float avgPrice(){
	Book *test;
	
	if(NULL == first){	//Error message
		printf("There is nothing in the list\n");
		system("pause");
		exit(1);
	}
	
	float priceSum = 0;	//Inicialization
	int countOfBooks = 0;
	
	for(test = first ; test != NULL ; test = test->next){ //Loop for going through the entire database
		priceSum = priceSum + test->data.price;		//Adding current price to current total
		countOfBooks++;								//Counting number of books
	}
	
	return priceSum/countOfBooks;				//Returning average price
}

/**
 * @brief function that sums up all prices
 * 
 * @return sum of prices
 */
float sumPrice(){
	Book *test;
	
	if(NULL == first){	//Error message
		printf("There is nothing in the list\n");
		system("pause");
		exit(1);
	}
	
	float priceSum = 0;	//Inicialization
	
	for(test = first ; test != NULL ; test = test->next){	//Loop for going through the entire database
		priceSum = priceSum + test->data.price;				//Adding current price to current total
	}
	
	return priceSum;
}

/**
 * @brief Function that deletes book by entered ID
 * 
 * @param id 
 */
int deleteBook(int id){
	Book *test;
	int isThere = 0;		//Checking variable
	
	for(test = first;test!=NULL;test = test->next){	//Loop that goes through entire database
		if(test->data.id == id){					//Condition that checks whether we found our wanted book
			if(test->prev == NULL && test->next == NULL){	//Deleting the book if there is no other book
				first = NULL;
				free(test);
				printf("Book deleted\n");
				isThere = 1;
				return 0;
			}else if(test->next == NULL){					//Deleting the book if the wanted book is last in database
				test->prev->next = NULL;
				free(test);
				printf("Book deleted\n");
				isThere = 1;
				return 0;
			}else if(test->prev == NULL){					//Deleting the book if the wanted book is first in database
				test->next->prev = NULL;
				first = test->next;
				free(test);
				isThere = 1;
				return 0;
			}else{											//Deleting the book if the wanted book is in the middle of a database
				test->next->prev = test->prev;
				test->prev->next = test->next;
				free(test);
				isThere = 1;
				return 0;
			}
		}
	}
	
	if(0 == isThere){		//Error message when there was not found book with that ID
		printf("There is no book with this ID\n");
		system("pause");
		return -1;
	}
	return -1;
}

/**
 * @brief Function that gives user ability to edit a book in the database
 * 
 * @param id 
 */
int edit(int id){
	Book *test;
	
	if(NULL == first){	//Error message
		printf("There is nothing in the list\n");
		system("pause");
		return -1;
	}
	int isThere = 0;	//Checking variable
	
	for(test = first ; NULL != test ; test = test->next){	//Loop that goes through entire database
		if(test->data.id == id){							//Condition that checks whether we found our wanted book
			printf("New ID: ");								//Setting new data variables
			scanf("%d", &test->data.id);
			printf("New Price: ");
			scanf("%f", &test->data.price);
			printf("New Genre: ");
			fflush(stdin);
			gets(test->data.genre);
			
			isThere = 1;	//Sets checking variable to 1 so there was the book with that ID
		}
	}
	if(isThere == 0){		//Error message when there was no such ID in the database
		printf("There is no book with that ID\n");
		return -1;
	}	
	return 0;
}

/**
 * @brief Function that saves database into binary file (casual user cannot read binary files)
 */
int writeToBinFile(){
	FILE *file = fopen("data.dat", "wb");	//Opens the file in write mode
	Book *temp;
	
	if (file == NULL) {						//Error message when problem occured during opening the file
		printf("Unable to open file\n");
		system("pause");
		return -1;
	}
	
	if(NULL == first){						//Error message if there is nothing in the database
		printf("There is nothing in the list\n");
		system("pause");
		return -1;
	}
	
	for(temp = first; temp != NULL; temp = temp->next){	//Loop for going through the whole database
		fwrite(temp, sizeof(Book), 1, file);			//Writing current books information into binary file
	}		

	fclose(file);	//Closing file
	return 0;
}

/**
 * @brief Loads book database from file
 */
int loadFromBinaryFile() {	
	FILE *file = fopen("data.dat", "rb");	//Opens file in read mode
	if (file == NULL) {						//Error message when problem occured during opening the file
		printf("Unable to open file\n");
		system("pause");
		return -1;
	}
	
	Book temp;

	while(fread(&temp, sizeof(Book), 1, file)){	//Reading whole file
		addToList(temp.data.id, temp.data.price, temp.data.genre);	//Adding those books back into database
	}
	
	fclose(file);	//Closing file
	return 0;
}

int main(){
	int dec;
	
	do{
		printf("0 - EXIT\n");
		printf("1 - Add a book into a database\n");
		printf("2 - Add a book into end of a database\n");
		printf("3 - Read the database\n");
		printf("4 - Find book by ID\n");
		printf("5 - Highest price\n");
		printf("6 - Lowest price\n");
		printf("7 - Sort\n");
		printf("8 - Average price\n");
		printf("9 - Delete book\n");
		printf("10 - Edit book\n");
		printf("11 - Price sumarization\n");
		printf("12 - Save to binary file\n");
		printf("13 - Load from binary file\n");
		
		printf("Your decision: ");
		scanf("%d", &dec);
		
		switch (dec) {
		case 0:
			system("cls");
			printf("Thanks for using me :-)\n");
			break;
		case 1:
			system("cls");
			int id;
			float price;
			char genre[40];
			
			printf("Book ID: ");
			scanf("%d", &id);
			printf("Price: ");
			scanf("%f", &price);
			printf("Genre: ");
			fflush(stdin);
			gets(genre);
			
			addToList(id, price, genre);
			system("cls");
			break;
		case 2:
			system("cls");
			int idend;
			float priceend;
			char genreend[40];
			
			printf("Book ID: ");
			scanf("%d", &idend);
			printf("Price: ");
			scanf("%f", &priceend);
			printf("Genre: ");
			fflush(stdin);
			gets(genreend);
			
			addToList(idend, priceend, genreend);
			system("cls");
			break;
		case 3:
			system("cls");
			readList();
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			findInListByID();
			system("pause");
			system("cls");
			break;
		case 5:
			system("cls");
			float maxPrice = highestPrice();
			printf("Highest price in list is: %.2f,-\n", maxPrice);
			system("pause");
			system("cls");
			break;
		case 6:
			system("cls");
			float minPrice = lowestPrice();
			printf("Lowest price in list is: %.2f,-\n", minPrice);
			system("pause");
			system("cls");
			break;
		case 7:
			system("cls");
			int decision;
			printf("1 - ID\n");
			printf("2 - Genre\n");
			printf("Sort by: ");
			scanf("%d", &decision);
			int check = sortBy(decision);
			if(check == 0){
				printf("Sort done!\n");
			}
			system("pause");
			system("cls");
			break;
		case 8:
			system("cls");
			printf("Average price is %.2f,-\n", avgPrice());
			system("pause");
			system("cls");
			break;
		case 9:
			system("cls");
			int toDel;
			printf("ID to delete: ");
			scanf("%d", &toDel);
			int checkDel = deleteBook(toDel);
			if(checkDel == 0){
				printf("Delete successful\n");
			}
			system("pause");
			system("cls");
			break;
		case 10:
			system("cls");
			int editID;
			printf("ID to edit: ");
			scanf("%d", &editID);
			int checkEdit = edit(editID);
			if(checkEdit == 0){
				printf("Book edited successfully\n");
			}
			system("pause");
			system("cls");
			break;
		case 11:
			system("cls");
			printf("Price total: %.2f,-\n", sumPrice());
			system("pause");
			system("cls");
			break;
		case 12:
			system("cls");
			int checkSave = writeToBinFile();
			if(checkSave == 0){
				printf("List has been saved into bin file\n");
			}
			system("pause");
			system("cls");
			break;
		case 13:
			system("cls");
			int checkLoad = loadFromBinaryFile();
			if(checkLoad == 0){
				printf("List loaded\n");
			}
			system("pause");
			system("cls");
			break;
		default:
			system("cls");
			printf("Missclick?, Try again\n");
			system("pause");
			break;
		}
	}while(dec != 0);
	
	return 0;
}
