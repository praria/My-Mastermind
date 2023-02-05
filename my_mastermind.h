// #ifndef MY_MASTERMIND_H and #define MY_MASTERMIND_H are preprocessor directives that are used to prevent the contents of the 
// header file from being included more than oce in a program. They chich if the macro "#MY_MASTERMIND_H" id defined, and if not, define it 
// and continue to the contents of the header file
#ifndef MY_MASTERMIND_H
#define MY_MASTERMIND_H

#define MAXIMUM_PIECES 9
#define CODE_LENGTH 4
# define MAXIMUM_ATTEMPTS 10

void randomCodeGenerator(int code[]);
int guessInput_validator(int guess[]);
int guessCode_actualCode_verifier(int code[], int guess[], int *misplacedNumber);

// #endif is the end of the preprocessor directive bugun at the start of th file, signalling the end of the header file
#endif