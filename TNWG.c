#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct key {
    int digit;
    char letter[4];
};

char word[8];
char number[9];

FILE* printTo;
FILE* dictionaryFile;

char dictionary[70000][50];
int wordCount = 0;

int length(char* str) {
    int l = 0;
    while (str[l] != '\0') l++;
    return l;
}

void toUpper(char* str) {
    int offset = 'A' - 'a';
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] += offset;
    }
}

void setDictionary() {
    wordCount = 0;
    if (dictionaryFile != NULL) {
        while (!feof(dictionaryFile)) {
            fscanf(dictionaryFile, "%s\n", dictionary[wordCount]);
            wordCount++;
        }
    }
    fclose(dictionaryFile);
}

void searchDictionary(struct key* keys, char* number) {
    for (int currentLength = 1; currentLength < 8; currentLength++) {
        for (int start = 0; start < 8 - currentLength; start++) {
            for (int i = 0; i < wordCount; i++) {
                int search = 1;
                int l = length(dictionary[i]);
                if (l <= currentLength) {
                    int wordIndex = 0;
                    for (int j = start; j < start + l && search; j++) {
                        struct key k = keys[number[j] - '0' - 2];
                        if (dictionary[i][wordIndex] != k.letter[0] && dictionary[i][wordIndex] != k.letter[1] && dictionary[i][wordIndex] != k.letter[2])
                            search = 0;
                        wordIndex++;
                    }
                    if (search) {
                        toUpper(dictionary[i]);
                        printf("%s\n", dictionary[i]);
                        if (printTo != NULL) {
                            fprintf(printTo, "%s\n", dictionary[i]);
                        }
                    }
                }
            }
        }
    }
}

int checkNumber(char* number) {
    for (int i = 0; i < 7; i++) {
        if (number[i] == '1' || number[i] == '0') return 0;
    }
    return 1;
}

void formatNumber(char* number) {
    for (int i = 3; i < 8; i++) {
        number[i] = number[i + 1];
    }
}

void initializeKeypad(struct key* keys) {
    keys[0].digit = 2;
    strcpy(keys[0].letter, "ABC");

    keys[1].digit = 3;
    strcpy(keys[1].letter, "DEF");

    keys[2].digit = 4;
    strcpy(keys[2].letter, "GHI");

    keys[3].digit = 5;
    strcpy(keys[3].letter, "JKL");

    keys[4].digit = 6;
    strcpy(keys[4].letter, "MNO");

    keys[5].digit = 7;
    strcpy(keys[5].letter, "PRS");

    keys[6].digit = 8;
    strcpy(keys[6].letter, "TUV");

    keys[7].digit = 9;
    strcpy(keys[7].letter, "WXY");
}

int main() {
    printTo = fopen("words.dat", "w");
    dictionaryFile = fopen("dictionary.txt", "r");
    setDictionary();

    struct key keys[8];
    initializeKeypad(keys);

    printf("Input a number: \n");
    scanf("%s", number);
    formatNumber(number);

    if (checkNumber(number)) {
        searchDictionary(keys, number);
    } else {
        printf("The number cannot contain 0s or 1s!\n");
    }

    if (printTo != NULL) {
        fclose(printTo);
    }

    return 0;
}
