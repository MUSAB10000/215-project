#include <stdio.h>
#include <string.h>

// Function to print all combinations of letters for a given phone number
void generateWords(int phoneNum[], int currentIndex, char currentWord[], FILE *file) {
    // Define a mapping of digits to letters
    char letters[10][4] = {
        "", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PRS", "TUV", "WXY"
    };

    // Base case: if the current index reaches the length of phone number
    if (currentIndex == 7) {
        fprintf(file, "%s\n", currentWord); // Write the generated word to file
        return;
    }

    // Get the current digit
    int digit = phoneNum[currentIndex];

    // If the digit is 0 or 1, skip and move to the next digit
    if (digit == 0 || digit == 1) {
        generateWords(phoneNum, currentIndex + 1, currentWord, file);
        return;
    }

    // Iterate through all possible letters corresponding to the current digit
    for (int i = 0; i < strlen(letters[digit]); i++) {
        // Add the current letter to the word being generated
        currentWord[currentIndex] = letters[digit][i];

        // Generate words for the next digit
        generateWords(phoneNum, currentIndex + 1, currentWord, file);
    }
}

int main() {
    int phoneNumber[7];
    printf("Enter a seven-digit phone number (excluding 0 and 1): ");

    // Input the seven-digit phone number
    for (int i = 0; i < 7; i++) {
        scanf("%1d", &phoneNumber[i]);
    }

    char word[8]; // Initialize a word to store combinations

    FILE *file = fopen("output.txt", "w"); // Open file in write mode

    // Generate words for the provided phone number and write to file
    generateWords(phoneNumber, 0, word, file);

    fclose(file); // Close the file stream

    return 0;
}