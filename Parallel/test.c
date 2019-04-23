#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Global variables */

const char Literals[] = "abcdefghijklmnopqrstuvwxyz";
const unsigned int NLiterals = sizeof(Literals) - 1;
const char TestString[] = "dave";
char EndString[16];

int CheckStatus = 0; // <-- This is the variable to check the search state

/* Functions */

static void BruteForcer(const int *, const int *, int, unsigned *);

int main()
{
    unsigned Counter = 0; // <-- This is the variable I want to use for counting

#pragma omp parallel default(none) shared(CheckStatus) reduction(+ \
                                                                 : Counter)
    {
        for (int WordLength = 0; WordLength < 5; ++WordLength)
        {
            int FirstEntry[WordLength], LastEntry[WordLength];
            int MyCheckStatus;

            for (int j = 0; j < WordLength; ++j)
                FirstEntry[j] = LastEntry[j] = 0;

#pragma omp for schedule(dynamic)
            for (int i = 0; i < NLiterals; ++i)
            {
                FirstEntry[0] = i;
                LastEntry[0] = i + 1;
#pragma omp atomic read
                MyCheckStatus = CheckStatus;
                if (!MyCheckStatus)
                    BruteForcer(FirstEntry, LastEntry, WordLength, &Counter);
                printf("%u %u %u\n", WordLength, i, Counter);
            }
        }
    }
    if (CheckStatus)
        fprintf(stdout, "\nWord found: '%s'! %u tries.\n", EndString, Counter);

    else
        fprintf(stdout, "\nNothing found: '%s'! %u tries.\n", "Empty", Counter);

    exit(EXIT_SUCCESS);
}

static void BruteForcer(const int *FstEntry, const int *LstEntry, int WdLength, unsigned *CounterPtr)
{
    char Word[WdLength];
    int Entry[WdLength + 1];
    int i, j;

    memset(Entry, '\0', WdLength);

    /* copy FstEntry to Entry */
    for (i = 0; i < WdLength; ++i)
        Entry[i] = FstEntry[i];

    i = 0;

    while (i < WdLength)
    {
        /* generate word */
        for (i = 0; i < WdLength; ++i)
            Word[i] = Literals[Entry[i]];

        /* null-byte at end of string */
        Word[WdLength] = '\0';

        /*
             * This part is okay. If the parallel region completes normally,
             * for example if the word was not found, at the end the number
             * of counts is right!
             */
        *CounterPtr += 1;

        /* string compare */
        if (strncmp(TestString, Word, sizeof(TestString)) == 0)
        {
            strncpy(EndString, Word, strlen(Word));
#pragma omp atomic write
            CheckStatus = 1;
        }

        /* increment Entry */
        for (i = 0; i < WdLength && ++Entry[WdLength - i - 1] == NLiterals; i++)
            Entry[WdLength - i - 1] = 0;

        /* when Entry != LstEntry then leave loop */
        for (j = 0; j < WdLength; ++j)
            if (Entry[j] != LstEntry[j])
                break;

        /* when Entry == LstEntry leave function */
        if (j == WdLength)
            return;
    }
}