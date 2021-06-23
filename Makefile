dict1 : triprecord.o linkedlist.o bst.o
	gcc -g -Wall -o dict1 dict1.c triprecord.o linkedlist.o bst.o
    
triprecord.o : triprecord.c triprecord.h
	gcc -c -Wall triprecord.c

linkedlist.o : linkedlist.c linkedlist.h triprecord.h
	gcc -c -Wall linkedlist.c

bst.o : bst.c bst.h triprecord.h linkedlist.h
	gcc -c -Wall bst.c

dict2 : triprecord.o linkedlist.o bst.o
	gcc -g -Wall -o dict2 dict2.c triprecord.o linkedlist.o bst.o