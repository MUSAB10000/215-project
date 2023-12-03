#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 8 // Including the null terminator
#define TOTAL_COMBINATIONS 2187

// Mapping of numbers to letters on a phone keypad
const char phoneLetters[10][5] = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "prs", "tuv", "wxy"
};

// Function to generate all possible words for a given number
void generateWords(int phoneNumber[], int index, char word[], FILE *file) {
    if (index == 7) {
        fprintf(file, "%s\n", word); // Write the generated word to file
        return;
    }

    int digit = phoneNumber[index];
    if (digit == 0 || digit == 1) {
        generateWords(phoneNumber, index + 1, word, file);
        return;
    }

    const char *letters = phoneLetters[digit];
    int lettersCount = strlen(letters);

    for (int i = 0; i < lettersCount; i++) {
        word[index] = letters[i];
        generateWords(phoneNumber, index + 1, word, file);
    }
}

int main() {
    int phoneNumber[7]; // Replace with the desired phone number

    printf("Enter a 7-digit phone number (without spaces): ");
    for (int i = 0; i < 7; i++) {
        scanf("%1d", &phoneNumber[i]);
        if (phoneNumber[i] < 0 || phoneNumber[i] > 9) {
            printf("Invalid input! Please enter digits only (0-9).\n");
            return 1;
        }
    }

    FILE *file = fopen("possible_words.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char word[MAX_WORD_LENGTH];
    word[7] = '\0'; // Null terminator for the word

    generateWords(phoneNumber, 0, word, file);

    // Close the file after generating words
    fclose(file);
    printf("Words generated and written to possible_words.txt\n");

    FILE *dictionaryFile = fopen("words_alpha.txt", "r");
    if (dictionaryFile == NULL) {
        printf("Error opening the dictionary file.\n");
        return 1;
    }

    FILE *validWordsFile = fopen("valid_words.txt", "w");
    if (validWordsFile == NULL) {
        printf("Error creating valid_words.txt file.\n");
        fclose(dictionaryFile);
        return 1;
    }

    // read words from the dictionary
    char dictionaryWord[MAX_WORD_LENGTH];

    // Read each word from the dictionary file and check against generated words
    while (fgets(dictionaryWord, MAX_WORD_LENGTH, dictionaryFile) != NULL) {
        dictionaryWord[strcspn(dictionaryWord, "\n")] = 0; // Remove newline character if present

        // Convert dictionary word to lowercase
        for (int i = 0; dictionaryWord[i]; i++) {
            dictionaryWord[i] = tolower(dictionaryWord[i]);
        }

        // Compare each dictionary word against the generated words
        if (strlen(dictionaryWord) == 7) {
            if (strstr(word, dictionaryWord) != NULL) {
                fprintf(validWordsFile, "%s\n", dictionaryWord);
            }
        }
    }

    // Close the files
    fclose(dictionaryFile);
    fclose(validWordsFile);
    printf("Valid words found in dictionary and written to valid_words.txt\n");

    return 0;
}
