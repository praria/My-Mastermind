# Welcome to My Mastermind

## Task
To write a program called Mastermind which is an implementation of the famous game

## Description
Mastermind is a game composed of 9 pieces of different colors.
A secret code is then composed of 4 distinct pieces.

The player has 10 attempts to find the secret code.
After each input, the game indicates to the player the number of well placed pieces and the number of misplaced pieces.

Pieces will be '0' '1' '2' '3' '4' '5' '6' '7' '8'.

If the player finds the code, he wins, and the game stops.
A misplaced piece is a piece that is present in the secret code but that is not in a good position.

The Program should read the player's input from the standard input.

The program will also receive the following parameters:
-c [CODE]: specifies the secret code. If no code is specified, a random code will be generated.
-t [ATTEMPTS]: specifies the number of attempts; by default, the playerhas 10 attempts.

## Installation
Technical information
We must create a Makefile, and the ouput is the command itself
It will contain rule all/clean/fclean (re => fclean + all)

We can use:
printf(3)
write(2)
read(2)
rand() (/ srand())
time()
atoi()
strcmp()
We can NOT use:
Any functions/syscalls which does not appear in the previous list
Yes, it includes exit

The Program needs to handle the sequence Ctrl + d. It's End Of File.
It's consider as a normal execution.

Requirements
The code must be compiled with the flags -Wall -Wextra -Werror.
Multiline macros are forbidden
Include another .c is forbidden
Macros with logic (while/if/variables/...) are forbidden

## Usage
Example:
PROMPT>./my_mastermind -c "0123"
Will you find the secret code?
Please enter a valid guess
---
Round 0
>1456
Well placed pieces: 0
Misplaced pieces: 1
---
Round 1
>tata
Wrong input!
>4132
Well placed pieces: 1
Misplaced pieces: 2
---
Round 2
>0123
Congratz! You did it!

Output formats
When the program starts, it must display:
Will you find the secret code?
Please enter a valid guess

When the user wins, it must display:
Congratz! You did it!

When the user enters an invalid code, it must respect the following format:
Well placed pieces: X
Misplaced pieces: Y
X and Y are two digits with the correct values.

Test the code with command: 
echo "5678\n4321\n1256" | ./my_mastermind -c 1234

### The Core Team
Solo -- Prakash Shrestha


<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>
<span><img alt='Qwasar SV -- Software Engineering School's Logo' src='https://storage.googleapis.com/qwasar-public/qwasar-logo_50x50.png' width='20px'></span>
