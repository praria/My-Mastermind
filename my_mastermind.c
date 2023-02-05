#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>
#include "my_mastermind.h"

// This header file <unistd.h>  includes the file descriptor for standard input in read() which is typically 0
// returns a if it is minimum otherise returns b
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// This function generates a code of constant length determined by "CODE_LENGTH" and assigns random values to each element of the
// code array "code[]". The random value "rand() % MAX_ PIECES" will be in the range 0..(MAX_PIECES)

void randomCodeGenerator(int code[]) {
    int i;
    for (i = 0; i < CODE_LENGTH; i++) {
        code[i] = rand() % MAXIMUM_PIECES;
    }
}
// This function reads input from user and stores it in an integer array "guess[]"
int guessInput_validator(int guess[]) {
    char input[CODE_LENGTH + 2];
    int i;
    ssize_t n;
    ssize_t input_size = 0;
    char c;
    // the variable n is assigned the value returned by read function, which reads input from the standard input file descriptor 0
    // The variable "input_size" is used to keep track of the number of characters read.The function continues reading characters until it encounters a newline
    // character or the number of characters read reaches "CODE_LENGTH"
    while ((n = read(0, &c, 1)) > 0 && c != '\n' && input_size < CODE_LENGTH) {
        input[input_size++] = c;
    }
    input[input_size] = '\0';

    // handles end of file. Press Ctrl + d on unix operating system or Ctrl + z on windows operating system
    // If the function encounters an end of file while reading input, it returns "EOF"
    if (n == 0) {
        return EOF;
    }
    // handles error. If the "read" function returns a negative value, the function returns 0
    if (n < 0) {
        return 0;
    }
    // handles invalid input. If the number of characters read is not equal to "CODE_LENGTH", the function returns 0, indicating that the input is invalid
    if (input_size !=CODE_LENGTH) {
        return 0;
    }
    // check each character of input and returns 0 indicating error if any character is not a digit or a space
    for (i = 0; i < CODE_LENGTH; i++) {
        if (!isdigit(input[i]) && input[i] != ' ') {
            return 0;
        }
    }

    // for each iteration, the input digit/ character at the current index is converted to an integer by subtractin the ASCII value of '0'
    // and store the result in the corresponding index of guess[] array
    // If the character is a space, the corresponding index of the "guess" array is set to -1. 
    // If the function reaches the end without encountering any errors, it returns 1, indicating the valid input
    for (i = 0; i < CODE_LENGTH; i++) {
        if (input[i] == ' ') {
            guess[i] = -1;
        }
        else {
            guess[i] = input[i] - '0';
        }
    }
    return 1;
}
// This function checks the user's guess against a code. It counts the number of correct pieces and the number of misplaced pieces
int guessCode_actualCode_verifier(int code[], int guess[], int *misplacedNumber) {
    int i =0;
    // this variable is used to store number of correct pieces
    int correctNumber = 0;
    //codeCount and guessCout are used to store counts of each piece in code and guess array respectively
    int codeCount[MAXIMUM_PIECES] = {0};
    int guessCount[MAXIMUM_PIECES] = {0};

    for (i = 0; i < CODE_LENGTH; i++) {
        if (code[i] == guess[i]) {
            correctNumber++;
        }
        else {
            codeCount[code[i]]++;
            guessCount[guess[i]]++;
        }
    }
// The "*misplacedNumber" is a pointer to an integer and it is used to store the number of misplaced pieces in the user's guess
// MIN(codeCount[i], guessCount[i]) is used in order to prevent counting the same piece twice
    *misplacedNumber = 0;
    for (i = 0; i < MAXIMUM_PIECES; i++) {
        *misplacedNumber += MIN(codeCount[i], guessCount[i]);
    }
    return correctNumber;
}

int main(int argc, char *argv[]) {
    int code[CODE_LENGTH];
    int guess[CODE_LENGTH];
    int correctNumber = 0;
    int misplacedNumber = 0;
    int attempts = MAXIMUM_ATTEMPTS;
    int i = 0;
    int round = 1;
    bool codeSpecified = false;

    // This function initializes the random number generator with a seed value based on the current time. The function time(NULL)
    // returns the current time in seconds, this value is then passed as an argument to the srand() which uses it to seed the random number generator

    srand(time(NULL));
// The following loop checks if the command line arguments passed to the program. It "-c" is passed in the argument, it parses the code
// from the next argument and assigns it to the code array, and also sets codeSpecified to true. It "-t" is passed in the argument, it assign the next argument to the attempts variable
// The loop starts at 1 because the first element of argv is the name of the program
// strcmp() compares two strings argv[i] and -c and returns 0 if they are equals. It the comparison returns 0, it means that current element of argv is "-c"
// Then it checks if there is a next element in argv by comparing i+1 with argc. It there is next element in argv, it sets codeSpecified to true
// and starts another for loop. Within the nested loop, it assigns the j-th character of the next element in argv to the code array
// by subtracting the ASCII value of '0' fron the j-th character in the next elemnent of argv.
    for (i = 1; i< argc; i++) {
        if (strcmp(argv[i], "-c") == 0) {
            if (i+1 < argc) {
                codeSpecified = true;
                for (int j = 0; j < CODE_LENGTH; j++){
                    code[j] = argv[i + 1][j] - '0';
                }
            }
        }
// if the i-th element of argv is not "-c" , the loop checks if the i-th element of argv is "-t". if the i-th element of argv is "-t", it
//checks if there is a next element in argv and if so, it assigns the next element in argv to the attemps variable
// using atoi() funciton which converts the string to integer
        else if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                attempts = atoi(argv[i + 1]);
            }
        }
    }

    if (!codeSpecified) {
        randomCodeGenerator(code);
    }

    printf("Will you find the secret code?\nPlease enter a valid guess\n---\nRound 0\n");
    while (round < attempts) {
        if(guessInput_validator(guess) == 0) {
            printf("Wrong input!\n");
            continue;
        }
        correctNumber = guessCode_actualCode_verifier(code, guess, &misplacedNumber);
        if (correctNumber == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            return 0;
        }

        printf("Well placed pieces: %d\n", correctNumber);
        printf("Misplaced pieces: %d\n", misplacedNumber);

        printf("---\nRound %d\n", round);
        round++;
    }

    printf("Sorry, you have reached the maximum number of attempts. The code was: ");
    for (i = 0; i < CODE_LENGTH; i++) {
        printf("%d", code[i]);
    }
    printf("\n");

    return 0;

}