#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to print all combinations of letters for a given phone number
void generateWords(int phoneNum[], int currentIndex, char currentWord[], FILE *outputFile);

// Function to convert a word to lowercase
void convertToLower(char *word);

int main() {
    int phoneNumber[7];
    printf("Enter a seven-digit phone number (excluding 0 and 1): ");

    // Input the seven-digit phone number
    for (int i = 0; i < 7; i++) {
        scanf("%1d", &phoneNumber[i]);
    }

    char word[8]; // Initialize a word to store combinations

    FILE *outputFile = fopen("output.txt", "w"); // Open output file in write mode

    // Generate words for the provided phone number and write to output file
    generateWords(phoneNumber, 0, word, outputFile);

    fclose(outputFile); // Close the output file stream

    // Create a new file to store lowercase words from dictionary matching generated words
    FILE *matchedWordsFile = fopen("matched_words.txt", "w");

    // Open dictionary file in read mode
    FILE *dictionaryFile = fopen("words_alpha.txt", "r");
    if (dictionaryFile == NULL) {
        printf("Unable to open dictionary file.\n");
        return 1;
    }

    // Reset file pointers to beginning
    rewind(dictionaryFile);

    // Check for matching words in dictionary and write lowercase matches to file
    while (fscanf(dictionaryFile, "%s", word) != EOF) {
        char tempWord[8];
        convertToLower(word); // Convert dictionary word to lowercase for comparison
        FILE *outputFile = fopen("output.txt", "r"); // Open output file in read mode
        rewind(outputFile);
        while (fscanf(outputFile, "%s", tempWord) != EOF) {
            convertToLower(tempWord); // Convert generated word to lowercase for comparison
            if (strcmp(word, tempWord) == 0) {
                // Write the lowercase word to the matched words file
                fprintf(matchedWordsFile, "%s\n", word);
                break; // Move to the next word in the dictionary
            }
        }
        fclose(outputFile); // Close the output file stream
    }

    fclose(dictionaryFile); // Close the dictionary file stream
    fclose(matchedWordsFile); // Close the matched words file stream

    return 0;
}

void generateWords(int phoneNum[], int currentIndex, char currentWord[], FILE *outputFile) {
    // Define a mapping of digits to letters
    char letters[10][5] = {
        "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"
    };

    // Base case: if the current index reaches the length of phone number
    if (currentIndex == 7) {
        fprintf(outputFile, "%s\n", currentWord); // Write the generated word to output file
        return;
    }

    // Get the current digit
    int digit = phoneNum[currentIndex];

    // If the digit is 0 or 1, skip and move to the next digit
    if (digit == 0 || digit == 1) {
        generateWords(phoneNum, currentIndex + 1, currentWord, outputFile);
        return;
    }

    // Iterate through all possible letters corresponding to the current digit
    for (int i = 0; i < strlen(letters[digit]); i++) {
        // Add the current letter to the word being generated
        currentWord[currentIndex] = letters[digit][i];

        // Generate words for the next digit
        generateWords(phoneNum, currentIndex + 1, currentWord, outputFile);
    }
}

void convertToLower(char *word) {
    while (*word) {
        *word = tolower(*word);
        word++;
    }
}
