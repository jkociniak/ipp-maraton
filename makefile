main : main.o usertree.o userlist.o movielist.o
	gcc -o main main.o usertree.o userlist.o movielist.o

main.o : main.c movielist.h userlist.h usertree.h
	gcc -Wall -Wextra -std=c11 -O2 -c main.c

usertree.o : usertree.c usertree.h movielist.h userlist.h
	gcc -Wall -Wextra -std=c11 -O2 -c usertree.c

userlist.o : userlist.c userlist.h movielist.h
	gcc -Wall -Wextra -std=c11 -O2 -c userlist.c

movielist.o : movielist.c movielist.h
	gcc -Wall -Wextra -std=c11 -O2 -c movielist.c

clean :
	rm main main.o usertree.o userlist.o movielist.o
