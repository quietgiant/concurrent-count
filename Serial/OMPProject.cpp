// OMPProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
	errno_t err;
	int chr = 0;
	FILE *pInputFile;
	int const charLimit = 150000;
	unsigned long numberOfElementsInArray = 0;
	char a[charLimit];
	unsigned long i = 0;
	unsigned long numberOfSpaces = 0;
	unsigned long numberOfPeriods = 0;
	unsigned long numberOfChars = 0;
	unsigned long numberOfParagraphs = 0;
	unsigned long numberOfWords = 0;
	//if ((err = fopen_s(&pInputFile, "C:/Users/palibanwait/Documents/CURRENT CLASSES/fileToRead.txt", "r")) == 0)
	if (argc == 2) {
		printf("\nFile To read: %s", argv[1]);
		if ((err = fopen_s(&pInputFile, argv[1], "r")) == 0) {
			
			// file exists: don't read a char before the loop or
			// it will be lost

			while ((chr = getc(pInputFile)) != EOF)
			{
				a[i] = chr;
				numberOfElementsInArray++;
				i++;

			}
			char word[100];
			int wordCharCounter = 0;
			for (int j = 0; j < numberOfElementsInArray; j++) {
				if (a[j] != ' ' && a[j] != '\n'&& a[j] != '\0') {
					word[wordCharCounter] = a[j];
					wordCharCounter++;
				}
				if (a[j] == ' ' || a[j] == '\n' || a[j] == '\0' || j == numberOfElementsInArray - 1) {
				
					numberOfWords++;
					memset(word, 0, sizeof word);
					wordCharCounter = 0;


				}

				if (a[j] == ' ') {
					numberOfSpaces++;
				}
				else if (a[j] == '.' || a[j] == '?' || a[j] == '!') {
					numberOfPeriods++;
				}
				else if (a[j] == '\n') {
					numberOfParagraphs++;
				}
				numberOfChars++;
			}

			printf("\nNumber of Spaces in text: %d", numberOfSpaces);
			printf("\nNumber of Words in text: %d", numberOfWords);
			printf("\nNumber of Punctionation in text: %d", numberOfPeriods);
			printf("\nNumber of Lines in text: %d", numberOfParagraphs + 1);
			printf("\nNumber of Chars in text: %d", numberOfChars - 2);
			printf("\nNumber of Chars in text without space: %d", numberOfChars - 2 - numberOfSpaces);
		}
		else
		{
			fprintf(stderr, "Cannot open file, error %d\n", err);

		}
	}
	
	


	return 0;
}

