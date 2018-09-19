// Definition of doubly linked list of ints sorted in descending order.
//
//

#include <stdio.h>
#include <stdlib.h>
#include "movielist.h"


/* exit codes for addMovieToList:
 * 0 - function executed without failure
 * 1 - malloc failed in some place
 * 2 - the element is already in list
*/

int addMovieToList(int id, movieList *lPtr) {
    movieList l = *lPtr;


    // The case of empty list.

    if (l == NULL) {
        l = (movieList)malloc(sizeof(struct movieElement));

        if (l == NULL) //
            return 1;

        l->prev = NULL;
        l->next = NULL;
        l->movie = id;
        *lPtr = l;
        return 0;
    }


    else if (l->movie == id) // The element is already in list - return code 2 (wrong parameter).
        return 2;

    else if (l->movie > id) // List is in descending order, so in this case we need to go further.
        return addMovieToList(id, &l->next);


    /* List is in descending order, so we are guaranteed that we must
     * put our element between current element and previous element.  */

    else {
        movieList prevL = l->prev;

        movieList elt = (movieList)malloc(sizeof(struct movieElement));

        if (elt == NULL)
            return 1;

        elt->movie = id;
        elt->next = l;
        elt->prev = prevL;

        if (prevL == NULL){
            l->prev = elt;
            *lPtr = elt;
            return 0;
        }

        else {
            (l->prev)->next = elt;
            l->prev = elt;
            return 0;
        }
    }
}



/* exit codes for deleteMovieFromList:
 * 0 - function executed without failure
 * 2 - there is no such element in the list
*/

int deleteMovieFromList(int id, movieList *lPtr) {
    movieList l = *lPtr;

    if (l == NULL) // The list is empty or we went to it's end.
        return 2;

    else if (l->movie != id) // Go further.
        return deleteMovieFromList(id, &l->next);

    else {
        movieList prevL = l->prev;
        movieList nextL = l->next;

        free(l);

        if (prevL == NULL) {
            if (nextL == NULL) {
                *lPtr = NULL;
                return 0;
            }

            else {
                nextL->prev = NULL;
                *lPtr = nextL;
                return 0;
            }
        }

        else {
            if (nextL == NULL) {
                prevL->next = NULL;
                return 0;
            }

            else {
                prevL->next = nextL;
                nextL->prev = prevL;
                return 0;
            }
        }
    }

}

void deleteMovieList(movieList l){
    if (l != NULL){
        deleteMovieList(l->next);
        free(l);
    }
}



/* exit codes for mergeLists:
 * 0 - function executed without failure
 * 1 - malloc failed in some place
*/

int mergeLists(movieList lMovies, movieList *bestMovies, int k, int maxRating) {
    if (lMovies != NULL) {

        movieList newBestMovies = NULL; //temp

        int flag = 0; // Describes if the rest of movies of lMovies less or equal to maxRating?
        int h = 0; // The counter of elements of newBestMovies.

        movieList elt1 = lMovies;
        movieList elt2 = *bestMovies;

        while (h < k) {
            if (elt1 == NULL) { // The end of lMovies - just add an element from *bestMovies to newBestMovies.
                if (elt2 == NULL) // There is no elements in both lists - stop adding.
                    break;

                else {
                    int state = addMovieToList(elt2->movie, &newBestMovies);

                    if (state == 1) { // Malloc failed.
                        deleteMovieList(newBestMovies);
                        return 1;
                    }

                    else if (state == 2) { // No element added, do not increase counter, go on to the next element.
                        elt2 = elt2->next;
                    }

                    else { // Element added, increase counter, go on to the next element.
                        h++;
                        elt2 = elt2->next;
                    }
                }
            }

            else { // Not the end of lMovies.
                if (elt2 == NULL) { // The end of *bestMovies.
                    if (elt1->movie <= maxRating) // Check if movie from lMovies fulfills the conditions.
                        break;                    // No more films will fulfill the condition, so break.

                    else {
                        int state = addMovieToList(elt1->movie, &newBestMovies);

                        if (state == 1) {
                            deleteMovieList(newBestMovies);
                            return 1;
                        }

                        else if (state == 2) {
                            elt1 = elt1->next;
                        }

                        else {
                            h++;
                            elt1 = elt1->next;
                        }
                    }
                }

                else { // Not the end of either of lists.
                    if (flag == 1) { // The rest lMovies is less or equal than maxRating, so add from *bestMovies.
                        int state = addMovieToList(elt2->movie, &newBestMovies);

                        if (state == 1) {
                            deleteMovieList(newBestMovies);
                            return 1;
                        }

                        else if (state == 2) {
                            elt2 = elt2->next;
                        }

                        else {
                            h++;
                            elt2 = elt2->next;
                        }
                    }

                    else { // Both of the movies fulfill conditions - compare them and put the greater to newBestMovies.
                        if (elt1->movie < elt2->movie) {
                            int state = addMovieToList(elt2->movie, &newBestMovies);

                            if (state == 1) {
                                deleteMovieList(newBestMovies);
                                return 1;
                            }

                            else if (state == 2) {
                                elt2 = elt2->next;
                            }

                            else {
                                h++;
                                elt2 = elt2->next;
                            }
                        }

                        else if (elt1->movie <= elt2->movie) {
                            if (elt1->movie <= maxRating) { // Check if the rest of lMovies fulfills conditions.
                                flag = 1;
                                continue;
                            }

                            else {
                                int state = addMovieToList(elt2->movie, &newBestMovies);

                                if (state == 1) {
                                    deleteMovieList(newBestMovies);
                                    return 1;
                                }

                                else if (state == 2) { // Go on to the next elements of both lists (because heads are equal).
                                    elt2 = elt2->next;
                                    elt1 = elt1->next;
                                }

                                else { // As above, but increase counter.
                                    h++;
                                    elt2 = elt2->next;
                                    elt1 = elt1->next;
                                }
                            }
                        }

                        else {
                            if (elt1->movie <= maxRating) {
                                flag = 1;
                                continue;
                            }

                            else {
                                int state = addMovieToList(elt1->movie, &newBestMovies);

                                if (state == 1) {
                                    deleteMovieList(newBestMovies);
                                    return 1;
                                }

                                else if (state == 2) {
                                    elt1 = elt1->next;
                                }

                                else {
                                    h++;
                                    elt1 = elt1->next;
                                }
                            }
                        }
                    }
                }
            }
        }

        deleteMovieList(*bestMovies);
        *bestMovies = newBestMovies;
    }
    return 0;
}