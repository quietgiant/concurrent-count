#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <iostream>
using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
	// errno_t err;
	int chr = 0;
	FILE *pInputFile;
	int const charLimit = 200000;
	unsigned long numberOfElementsInArray = 0;
	char a[charLimit];
	unsigned long i = 0;
	unsigned long numberOfSpaces = 0;
	unsigned long numberOfPeriods = 0;
	unsigned long numberOfChars = 0;
	unsigned long numberOfParagraphs = 0;
	unsigned long numberOfWords = 0;
	//if ((err = fopen_s(&pInputFile, "C:/Users/palibanwait/Documents/CURRENT CLASSES/fileToRead.txt", "r")) == 0)
	if (argc == 2)
	{
		printf("\nFile To read: %s\n", argv[1]);
		//if ((err = fopen_s(&pInputFile, "C:/Users/palibanwait/Documents/CURRENT CLASSES/fileToRead.txt", "r")) == 0) {
		pInputFile = fopen(argv[1], "r");
		if (pInputFile != NULL)
		{
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
			auto start = high_resolution_clock::now();

			for (int j = 0; j < numberOfElementsInArray; j++)
			{
				if (a[j] != ' ' && a[j] != '\n' && a[j] != '\0')
				{
					word[wordCharCounter] = a[j];
					wordCharCounter++;
				}
				if (a[j] == ' ' || a[j] == '\n' || a[j] == '\0' || j == numberOfElementsInArray - 1)
				{

					numberOfWords++;
					memset(word, 0, sizeof word);
					wordCharCounter = 0;
				}

				if (a[j] == ' ')
				{
					numberOfSpaces++;
				}
				else if (a[j] == '.' || a[j] == '?' || a[j] == '!')
				{
					numberOfPeriods++;
				}
				else if (a[j] == '\n')
				{
					numberOfParagraphs++;
				}
				numberOfChars++;
			}
			auto stop = high_resolution_clock::now();
			auto duration = duration_cast<microseconds>(stop - start);
			printf("\nNumber of Spaces in text: %lu", numberOfSpaces);
			printf("\nNumber of Words in text: %lu", numberOfWords);
			printf("\nNumber of Punctionation in text: %lu", numberOfPeriods);
			printf("\nNumber of Lines in text: %lu", numberOfParagraphs + 1);
			printf("\nNumber of Chars in text: %lu", numberOfChars - 2);
			printf("\nNumber of Chars in text without space: %lu", numberOfChars - 2 - numberOfSpaces);
			cout << "\nTime taken by Serial code: " << duration.count() << " microseconds" << endl;
		}
		else
		{
			fprintf(stderr, "Error: cannot open file\n");
		}
	}
	else
	{
		printf("You must provide a file to process as a parameter to this program.");
	}

	printf("\n-----\ndone.\n\n");
	return 0;
}
