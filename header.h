#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int addWordToDic(char wordEn[], char wordCz[], int lection);
void toLowerCase(char word[]);
int readFromDic();
int translate(char word[]);
int readLection(int lectionNum);
int testFromLection(int lectionNum);
int countWords();
int deleteWord(char word[]);
int testRNG();
int editWord(char word[]);
int testCZtoENorENtoCZ(char *cz, char *en);
int saveToFile(int questionCount, float correct, float wrong, float percentage);

#endif
