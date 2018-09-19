// Definition of doubly linked list of users.
//
//

#include <stdlib.h>
#include "userlist.h"


/* exit codes for newUserList:
 * 0 - function executed without failure
 * 1 - malloc failed in some place

   The list is implemented with header and trailer.
*/

int newUserList(userList* uPtr) {
    userList header = malloc(sizeof(struct userElement));

    if (header == NULL)
        return 1;

    userList trailer = malloc(sizeof(struct userElement));

    if (trailer == NULL) {
        deleteUserList(header); // Second malloc failed, so delete first element and return failure.
        return 1;
    }

    header->prev = NULL;
    header->next = trailer;
    header->user = NULL;

    trailer->next = NULL;
    trailer->prev = header;
    trailer->user = NULL;

    *uPtr = header;
    return 0;
}



/* exit codes for addUserToList:
 * 0 - function executed without failure
 * 1 - malloc failed in some place

   Puts user between header and the first actual element.
*/

int addUserToList(User user, userList l) {
    userList lNext = l->next;

    userList elt = (userList)malloc(sizeof(struct userElement));

    if (elt == NULL)
        return 1;

    else {
        elt->user = user;
        elt->prev = l;
        elt->next = lNext;

        user->list = elt;

        l->next = elt;
        lNext->prev = elt;
        return 0;
    }
}


void deleteUserList(userList l) {
    if (l != NULL) {
        deleteUserList(l->next);

        if(l->user != NULL) { // If it's not header/trailer, first delete children and movies of current user.
            deleteUserList((l->user)->leftmost);
            deleteMovieList((l->user)->movies);
            free(l->user);
        }

        free(l);
    }
}