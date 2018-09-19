// Declaration of doubly linked list of users.
//
//

#ifndef MARATON_TREELIST_H
#define MARATON_TREELIST_H

#include "movielist.h"

struct Node;

struct userElement;

struct Node {
    struct userElement* list; // The pointer to element of list the children of the user's parent which contains user.
    struct userElement* leftmost; // The beginning of the list of the user's children.
    struct userElement* rightmost; // The end of the list of the user's children.
    movieList movies;
};

struct userElement {
    struct Node* user;
    struct userElement* prev;
    struct userElement* next;
};

typedef struct Node* User;

typedef struct userElement* userList;


// Modifies 'uPtr' such that it points to freshly created userList.

int newUserList(userList* uPtr);


// Adds 'user' to userList 'l'.

int addUserToList(User user, userList l);


// Deletes userList 'l'.

void deleteUserList(userList l);

#endif //MARATON_TREELIST_H
