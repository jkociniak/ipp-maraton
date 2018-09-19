// Definition of tree of users.
//
//

#include <stdio.h>
#include <stdlib.h>
#include "usertree.h"


/* exit codes for newUser:
 * 0 - function executed without failure
 * 1 - malloc failed in some place
*/

int newUser(User* uPtr) {
    User u = malloc(sizeof(struct Node));

    if (u == NULL)
        return 1;

    userList empty;

    if (newUserList(&empty) == 1)
        return 1;

    u->leftmost = empty;
    u->rightmost = empty->next;
    u->movies = NULL;

    *uPtr = u;
    return 0;
}





/* exit codes for addNewUser:
 * 0 - function executed without failure
 * 1 - malloc failed in some place
*/

int addNewUser(User parent, User son) {
    return addUserToList(son, parent->leftmost);
}





/* exit codes for addMovie:
 * 0 - function executed without failure
 * 1 - malloc failed in some place
 * 2 - the element is already in list
*/

int addMovie(User user, int id) {
    return addMovieToList(id, &user->movies);
}





void deleteUser(User user) {
    userList userElt = user->list;

    /* We will put the list of the children of user between the neighbors
     * of user (they are children of the user's parent).                   */
    userList leftNeighbor = userElt->prev;
    userList rightNeighbor = userElt->next;

    if (((user->leftmost)->next)->user == NULL) { // The user has no children (only header/trailer).
        leftNeighbor->next = rightNeighbor;
        rightNeighbor->prev = leftNeighbor;
    }

    else {
        userList userLeftmost = (user->leftmost)->next;
        userList userRightmost = (user->rightmost)->prev;

        leftNeighbor->next = userLeftmost;
        userLeftmost->prev = leftNeighbor;

        rightNeighbor->prev = userRightmost;
        userRightmost->next = rightNeighbor;
    }

    deleteMovieList(user->movies);
    free(user->leftmost);
    free(user->rightmost);
    free(user);
    free(userElt);
}





/* exit codes for deleteMovie:
 * 0 - function executed without failure
 * 2 - there is no such element in the list
*/

int deleteMovie(User user, int id) {
    return deleteMovieFromList(id, &user->movies);
}





//AUXILIARY FUNCTION
int max(int x, int y) {
    if (x >= y)
        return x;
    else
        return y;
}





/* exit codes for marathon:
 * 0 - function executed without failure
 * 1 - malloc failed in some place
*/

int marathon(User user, int k, movieList *bestMovies, int maxRating) {
    if (mergeLists(user->movies, bestMovies, k, maxRating) == 1)
        return 1;

    userList child = user->leftmost;


    int maxUserRating;
    if (user->movies == NULL)
        maxUserRating = -1;
    else
        maxUserRating = (user->movies)->movie;

    while(child != NULL){
        if(child->user != NULL)

            /* To be in the final list, the movie of a user within the subtree of users with
             * root 'user' must be greater than every best movie of users creating the path
             * from root to this user (exclusively), so as we go down we change parameter
             * maxRating to be the max of the current maxRating and the best user's movie.   */

            if (marathon(child->user, k, bestMovies, max(maxRating, maxUserRating)) == 1)
                return 1;

        child = child->next;
    }
    return 0;
}


