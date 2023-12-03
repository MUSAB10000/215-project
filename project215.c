#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateWords(int phoneNum[], int currentIndex, char currentWord[], FILE *outputFile);
void convertToLower(char *word);

int main() {
    int i;
    int phoneNumber[7];
    printf("Enter a seven-digit phone number (excluding 0 and 1): ");
   char input[9];
   scanf("%8s", input);
    if (strlen(input) != 7) {
        printf("Invalid input! Please enter a seven-digit number.\n");
        return 1; // Exit the program
    }
    for (i = 0; i < 7; i++) {
       int digit = input[i] - '0'; // Convert character to integer
        if (digit <= 1 || digit > 9) {
            printf("Invalid input! Please enter a number excluding 0 and 1.\n");
            return 1; // Exit the program
        }

        phoneNumber[i] = digit;
    }
    char word[8];
    FILE *outputFile = fopen("output.txt", "w");

    generateWords(phoneNumber, 0, word, outputFile);

    fclose(outputFile);

    FILE *matchedWordsFile = fopen("matched_words.txt", "w");
    FILE *dictionaryFile = fopen("words_alpha.txt", "r");
    if (dictionaryFile == NULL) {
        printf("Unable to open dictionary file.\n");
        return 1;
    }

    rewind(dictionaryFile);

    while (fscanf(dictionaryFile, "%s", word) != EOF) {
        char tempWord[8];
        convertToLower(word);
        FILE *outputFile = fopen("output.txt", "r");
        rewind(outputFile);
        
        while (fscanf(outputFile, "%s", tempWord) != EOF) {
            if (strcmp(word, tempWord) == 0) {
                fprintf(matchedWordsFile, "%s\n", word);
                break;
            }
        }
        fclose(outputFile);
    }

    fclose(dictionaryFile);
    fclose(matchedWordsFile);

    return 0;
}

void generateWords(int phoneNum[], int currentIndex, char currentWord[], FILE *outputFile) {
    int i;
   const char letters[10][4] = {
        "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"
    };

    if (currentIndex == 7) {
        fprintf(outputFile, "%s\n", currentWord);
        return;
    }

    int digit = phoneNum[currentIndex];
    for ( i = 0; i < strlen(letters[digit]); i++) {
        currentWord[currentIndex] = letters[digit][i];
        generateWords(phoneNum, currentIndex + 1, currentWord, outputFile);
    }
}

void convertToLower(char *word) {
    while (*word) {
        *word = tolower(*word);
        word++;
    }
}
