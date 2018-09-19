#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "movielist.h"
#include "userlist.h"
#include "usertree.h"

#define MAX_USER_NUMBER 65536        // User 65536 is not possible.
#define MAX_MOVIE_NUMBER 2147483647  // Movie 2147483647 is possible.



/* Function which parses string to decimal number */

unsigned long int stringToInt(char *str) {
    unsigned long int res = 0;
    unsigned long int aux = 1;
    unsigned long int length = strlen(str);

    for (unsigned short int i = 0; i<length; i++) {
        for (unsigned short int j = 0; j<length-1-i; j++)
            aux = aux*10;

        res = res + aux*((int)str[i] - 48);
        aux = 1;
    }

    return res;
}



/* Function which determines if currently read line is valid 'delUser' input.
 * If it is, it passes the parsed args to given array.
 * exit codes:
 * 0 - the line is valid 'delUser' input.
 * -1 - the line is not valid input for any of functions:
 *      'addUser', 'delUser', 'addMovie', 'delMovie', 'marathon'.
 * -2 - the line is not valid 'delUser' input, but it can be valid for other functions.
*/

int isValid_delUser(unsigned long int *arr) {

    unsigned long int param1;
    const char str[] = "delUser";
    unsigned long int length;

    char input[12];

    // Scan the first 8 chars (if there is more then 8 chars then it can't be valid).
    if (scanf("%8s", input) != 1)
        return -1;

    if (strcmp(str, input) == 0) {
        if (getchar() != 32)
            return -1;

        else {
            int first = getchar();

            if (isdigit(first) == 0)
                return -1;

            else {
                ungetc(first, stdin);

                // Again - scan 6 chars, because if there is more than it can't be valid.
                if (scanf("%6s", input) != 1)
                    return -1;

                else {
                    length = strlen(input);

                    if (length > 5)
                        return -1;

                    else {

                        // Check if all the chars are digits.
                        for (unsigned short int i = 0; i < length; i++) {
                            if (isdigit(input[i]) == 0)
                                return -1;
                        }

                        // We assume that there is no front zeroes.
                        if (length > 1 && input[0] == 48)
                            return -1;

                        else {
                            param1 = stringToInt(input);

                            if (param1 > MAX_USER_NUMBER - 1)
                                return -1;

                            else if ((first = getchar()) != (int) '\n') {
                                ungetc(first, stdin);
                                return -1;
                            }

                            else {
                                arr[0] = param1;
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    // Put the chars to the input to check if the line is valid for other functions.
    else {
        length = strlen(input);
        for (unsigned short int i = 0; i < length; i++)
            ungetc(input[length-1-i], stdin);

        return -2;
    }
}



/* Function which determines if currently read line is valid input.
 * If it is, it passes the parsed args to given array.
 * exit codes:
 * 0 - the line is valid 'str' input.
 * -1 - the line is not valid input for any of functions:
 *      'addUser', 'delUser', 'addMovie', 'delMovie', 'marathon'.
 * -2 - the line is not valid 'delUser' input, but it can be valid for other functions.
*/

int isValid_others(const char *str, unsigned long int paramLength2, unsigned long int *arr) {

    unsigned long int param1 = 0;
    unsigned long int param2 = 0;
    unsigned long int paramMax2;
    unsigned long int length;

    if (paramLength2 == 5)
        paramMax2 = MAX_USER_NUMBER - 1;
    else
        paramMax2 = MAX_MOVIE_NUMBER;

    char input[12];

    if (scanf("%9s", input) != 1) // The all valid strings are at most 8 chars long, so we scan 9 first chars.
        return -1;

    if (strcmp(str, input) == 0) {
        if (getchar() != 32)
            return -1;

        else {
            int first = getchar();

            if (isdigit(first) == 0)
                return -1;

            else {
                ungetc(first, stdin);

                // Again, the all valid FIRST parameters are at most 5 chars.
                if (scanf("%6s", input) != 1)
                    return -1;

                else {
                    length = strlen(input);

                    if (length > 5)
                        return -1;

                    else {
                        // To check if all the chars are digits.
                        for (unsigned short int i = 0; i < length; i++) {
                            if (isdigit(input[i]) == 0)
                                return -1;
                        }

                        if (length > 1 && input[0] == 48)
                            return -1;

                        else {
                            param1 = stringToInt(input);

                            if (param1 > MAX_USER_NUMBER - 1)
                                return -1;

                            else if ((first = getchar()) != 32) {
                                ungetc(first, stdin);
                                return -1;

                            }

                            else {
                                first = getchar();

                                if (isdigit(first) == 0)
                                    return -1;

                                else {
                                    ungetc(first, stdin);

                                    if (scanf("%11s", input) != 1)
                                        return -1;

                                    length = strlen(input);

                                    if (length > paramLength2)
                                        return -1;

                                    else {
                                        for (unsigned short int i = 0; i < length; i++) {
                                            if (isdigit(input[i]) == 0)
                                                return -1;
                                        }

                                        if (length > 1 && input[0] == 48)
                                            return -1;

                                        else {
                                            param2 = stringToInt(input);

                                            if (param2 > paramMax2)
                                                return -1;

                                            else if (getchar() != (int) '\n')
                                                return -1;

                                            else {
                                                arr[0] = param1;
                                                arr[1] = param2;

                                                return 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // Put the chars to the input to check if //
    // the line is valid for other functions. //
    else {
        length = strlen(input);
        for (unsigned short int i = 0; i < length; i++)
            ungetc(input[length - 1 - i], stdin);

        return -2;
    }
}


// Function which skips the whole line.
void skipLine(void) {
        int c;

        do {
            c = getchar();
        } while (c != EOF && c != (int)'\n');
}



/* Function which parses the input line.
 * If there is valid input it calls proper function on array users.
 * exit codes:
 * -1 - end of input
 *  0 - successfully parsed and there could be more input
 *  1 - malloc failed somewhere
*/

int parse(User *users) {
    int firstChar = getchar();

    if (firstChar == EOF)
        return -1;

    else if (firstChar == (int)'\n')
        return 0;

    else if (firstChar == (int)'#') {
        skipLine();
        return 0;
    }

    else if (isspace(firstChar) != 0) {
        fprintf(stderr, "ERROR\n");
        skipLine();

        return 0;
    }

    else {
        int state, failed; // Variables to keep the exit codes of functions.
        unsigned long int arr[2]; // Array for arg values.

        ungetc(firstChar, stdin);

        state = isValid_others("addUser", 5, arr);

        if (state == 0) {
            //Checks if parsed args are valid.
            if (users[arr[0]] != NULL && users[arr[1]] == NULL) {
                failed = newUser(&users[arr[1]]);

                if (failed == 1)
                    return failed;

                failed = addNewUser(users[arr[0]], users[arr[1]]);

                if (failed == 0)
                    printf("OK\n");

                return failed;
            }

            else {
                fprintf(stderr, "ERROR\n");
                return 0;
            }
        }

        else if (state == -1) {
            fprintf(stderr, "ERROR\n");
            skipLine();

            return 0;
        }

        else {
            state = isValid_others("addMovie", 10, arr);

            if (state == 0) {
                if (users[arr[0]] == NULL) { // Check if arg is invalid.
                    fprintf(stderr, "ERROR\n");
                    return 0;
                }

                else {
                    failed = addMovie(users[arr[0]], (int) arr[1]);

                    if (failed == 0)
                        printf("OK\n");

                    else if (failed == 2) {
                        fprintf(stderr, "ERROR\n");
                        return 0;
                    }

                    return failed;
                }
            }

            else if (state == -1) {
                fprintf(stderr, "ERROR\n");
                skipLine();

                return 0;
            }

            else {
                state = isValid_others("delMovie", 10, arr);

                if (state == 0) {
                    if(users[arr[0]] == NULL) { // Check if arg is invalid.
                        fprintf(stderr, "ERROR\n");
                        return 0;
                    }

                    else {
                        failed = deleteMovie(users[arr[0]], (int) arr[1]);

                        if (failed == 0)
                            printf("OK\n");

                        else if (failed == 2)
                            fprintf(stderr, "ERROR\n");

                        return 0;
                    }
                }

                else if (state == -1) {
                    fprintf(stderr, "ERROR\n");
                    skipLine();

                    return 0;
                }

                else {
                    state = isValid_others("marathon", 10, arr);

                    if (state == 0) {
                        if (users[arr[0]] != NULL) { // Check if arg is valid.
                            movieList bestMovies = NULL;

                            failed = marathon(users[arr[0]], (int)arr[1], &bestMovies, -1);

                            if (failed == 0) {
                                if (bestMovies == NULL)
                                    printf("NONE\n");

                                else {
                                    printf("%d", bestMovies->movie);
                                    movieList iter = bestMovies->next;

                                    while (iter != NULL) {
                                        printf(" %d", iter->movie);
                                        iter = iter->next;
                                    }

                                    printf("\n");
                                }

                                deleteMovieList(bestMovies);
                            }

                            return failed;
                        }

                        else {
                            fprintf(stderr, "ERROR\n");
                            return 0;
                        }
                    }

                    else if (state == -1) {
                        fprintf(stderr, "ERROR\n");
                        skipLine();

                        return 0;
                    }

                    else {
                        state = isValid_delUser(arr);

                        if (state == 0) {
                            // Check if args are valid.
                            if (users[arr[0]] != NULL && arr[0] != 0) {
                                deleteUser(users[arr[0]]);
                                users[arr[0]] = NULL;

                                printf("OK\n");

                                return 0;
                            }

                            else {
                                fprintf(stderr, "ERROR\n");
                                return 0;
                            }
                        }

                        else {
                            fprintf(stderr, "ERROR\n");

                            skipLine();

                            return 0;
                        }
                    }
                }
            }
        }
    }
}

int main(void) {

    // Initialize users array and tree.

    User *users = calloc(MAX_USER_NUMBER, sizeof(User));

    for(int i = 0; i<MAX_USER_NUMBER; i++)
        users[i] = NULL;

    userList root;
    if (newUserList(&root) == 1)
        return 1;

    if (newUser(&users[0]) == 1) {
        deleteUserList(root);
        return 1;
    }

    if (addUserToList(users[0], root) == 1) {
        free(users[0]);
        deleteUserList(root);
        return 1;
    }



    // Run and exit program (with proper exit code).

    int failed;

    do {
        failed = parse(users);
    } while (failed == 0);

    deleteUserList(root);
    free(users);

    if (failed == -1) // Reached end of input with no problems.
        return 0;
    else              // Malloc failed somewhere.
        return 1;
}