# gcc (GNU compiler collection) is set to the variable CC
# The flags -Wall -Wextra -Werror are sets to the variable CFLAGS to enable all warning messages and treat them as errors
CC=gcc
CFLAGS=-Wall -Wextra -Werror

# The "all" target specifies that the default target of the makefile is to build the "my_mastermind" executable
all: my_mastermind

# The "my_mastermind" target specifies that "my_mastermind" executable should be build from "my_mastermind.c" and "my_mastermind.h"
# $(CC) $(CFLAGS) specify the compiler and flags to use. This command compiles and link the program
my_mastermind: my_mastermind.c my_mastermind.h
	$(CC) $(CFLAGS) my_mastermind.c -o my_mastermind

# The "clean" target specifies that object files should be removed using the command "rm -f *.o"
clean:
	rm -f *.o

# fclean target specifies that "my_mastermind" executable and object files shoul be removed
fclean: clean
	rm -f my_mastermind

# The "re" target specifies that the "fclean" and "all" targets should be run, effectively rebuilding the program
re: fclean all

# The ".phony" target specifies that the targets all, clean, fclean, re are not files and should be executed when called
.PHONY: all clean fclean re