// Declaration of tree of users (using definition of users from userlist.h).
//
//

#ifndef MARATON_USERTREE_H
#define MARATON_USERTREE_H

#include "movielist.h"
#include "userlist.h"


// Modifies 'uPtr' such that it points to freshly created User.

int newUser(User* uPtr);


// Adds 'son' to list of children of 'parent'.

int addNewUser(User parent, User son);


// Adds 'id' to list of movies of 'user'.

int addMovie(User user, int id);


// Deletes 'user'. The children of 'user' become children of parent of 'user'.

void deleteUser(User user);


// Deletes 'id' from list of movies of 'user'.

int deleteMovie(User user, int id);


/* Theoretical definition:
   Modifies '*bestMovies' such that it contains at most 'k' best movies of
   - 'user'
   - outcome of marathon applied to children of 'user', but only these
     movies which are greater than the greatest movie of 'user'.

   Practically, this function is programmed top-down (it puts to '*bestMovies'
   only these movies of 'user' which are greater than 'maxRating') , so it
   should be called with 'maxRating' = -1 to provide the first condition,
   and this parameter changes as we call this function recursively
   on children of 'user'.                                                  */

int marathon(User user, int k, movieList *bestMovies, int maxRating);

#endif //MARATON_USERTREE_H