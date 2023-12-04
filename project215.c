#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generateWords(int phoneNum[], char currentWord[], FILE *outputFile);
void convertToLower(char *word);

int main() {
    int i;
    int phoneNumber[7];
    printf("Enter a seven-digit phone number (excluding 0 and 1): ");
   char input[9];
   scanf("%8s", input);
    if (strlen(input) != 7) {
        printf("Invalid input! Please enter a seven-digit number.\n");
        return 1; 
    }
    for (i = 0; i < 7; i++) {
       int digit = input[i] - '0'; 
        if (digit <= 1 || digit > 9) {
            printf("Invalid input! Please enter a number excluding 0 and 1.\n");
            return 1; 
        }

        phoneNumber[i] = digit;
    }
    char word[8];
    FILE *outputFile = fopen("output.txt", "w");

    generateWords(phoneNumber,word, outputFile);

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
            convertToLower(tempWord);
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

void generateWords(int phoneNum[], char currentWord[], FILE *outputFile) {
    int a, b, c, d, e, f, g;
    const char letters[10][5] = {
        "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"
    };

    for ( a = 0; a < 3; a++) {
        currentWord[0] = letters[phoneNum[0]][a];
        for ( b = 0; b < 3; b++) {
            currentWord[1] = letters[phoneNum[1]][b];
            for ( c = 0; c < 3; c++) {
                currentWord[2] = letters[phoneNum[2]][c];
                for ( d = 0; d < 3; d++) {
                    currentWord[3] = letters[phoneNum[3]][d];
                    for ( e = 0; e < 3; e++) {
                        currentWord[4] = letters[phoneNum[4]][e];
                        for ( f = 0; f < 3; f++) {
                            currentWord[5] = letters[phoneNum[5]][f];
                            for ( g = 0; g < 3; g++) {
                                currentWord[6] = letters[phoneNum[6]][g];
                                fprintf(outputFile, "%s\n", currentWord);
                            }
                        }
                    }
                }
            }
        }
    }
}

void convertToLower(char *word) {
    while (*word) {
        *word = tolower(*word);
        word++;
    }
}
