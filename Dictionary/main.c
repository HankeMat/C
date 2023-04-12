#include "header.h"

int main() {
	int choice;
	
	do{
		printf("0 - EXIT\n");
		printf("1 - Add a word into dictionary\n");
		printf("2 - Read entire dictionary\n");
		printf("3 - Translate\n");
		printf("4 - Read selected lection\n");
		printf("5 - Test from selected lection\n");
		printf("6 - Random test\n");
		printf("7 - Delete word\n");
		printf("8 - Edit word\n");
		
		printf("Your choice: ");
		scanf("%d", &choice);
		system("cls");
		
		switch (choice) {
		case 0:
			printf("Thanks for using me :)\n");
			break;	
		case 1: ;
			char CzWord[80];
			char EnWord[80];
			int lection;
			
			printf("Word (cz): ");
			fflush(stdin);
			gets(CzWord);
			
			printf("Word (en): ");
			fflush(stdin);
			gets(EnWord);
			
			printf("Lection: ");
			scanf("%d", &lection);
			
			toLowerCase(CzWord);
			toLowerCase(EnWord);
			
			addWordToDic(CzWord, EnWord, lection);
			
			break;
		case 2:
			readFromDic();
			system("pause");
			system("cls");
			break;
		case 3: ;
			char find[80];
			printf("Word you wish to translate: ");
			fflush(stdin);
			gets(find);
			translate(find);
			system("pause");
			system("cls");
			break;
		
		case 4: ;
			int lecNum;
			printf("Enter lection number: ");
			scanf("%d", &lecNum);
			readLection(lecNum);
			system("pause");
			system("cls");
			break;
		case 5: ;
			int lecNumber;
			printf("Enter lection number: ");
			scanf("%d", &lecNumber);
			testFromLection(lecNumber);
			system("pause");
			system("cls");
			break;
		case 6:
			testRNG();
			system("cls");
			break;
		case 7: ;
			char word[80];
			printf("Word to delete (cz): ");
			fflush(stdin);
			gets(word);
			deleteWord(word);
			break;
		case 8: ;
			char edit[80];
			printf("Word to edit (cz): ");
			fflush(stdin);
			gets(edit);
			editWord(edit);
			break;
		default:
			printf("You probably missclicked - wrong value\n");
			break;
		}	
	}while(choice != 0);
	
	
	return 0;
}
