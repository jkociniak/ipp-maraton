// Declaration of doubly linked list of ints sorted in descending order.
//
//

#ifndef MARATON_MOVIELIST_H
#define MARATON_MOVIELIST_H

struct movieElement;

struct movieElement {
    int movie;
    struct movieElement* prev;
    struct movieElement* next;
};

typedef struct movieElement* movieList;


// Adds to list an element 'id'.

int addMovieToList(int id, movieList *lPtr);


// Deletes from list an element 'id'.

int deleteMovieFromList(int id, movieList *lPtr);


// Deletes a list.

void deleteMovieList(movieList l);


/* Adds elements (in descending order) from 'l' to 'bestMovies' but the element
   from 'l' can be added to 'bestMovies' only if it's greater than 'maxRating'.
   Also, 'bestMovies' remains at most 'k' elements long.                        */

int mergeLists(movieList l, movieList *bestMovies, int k, int maxRating);


#endif //MARATON_MOVIELIST_H
