***************************************************
Your name Haoxiang Dong		Your student number 0850990
The class name	CIS2750	The assignment name/numberA2

****************************************************
************
Compilation
************
gcc -Wall -std=c11 -g -c  src/LinkedListAPI.c -o llist.o -Iinclude
gcc -Wall -std=c11 -g -c  src/GEDCOMparser.c -o cparse.o -Iinclude
ar cr bin/libllist.a llist.o
ar cr bin/libparser.a cparse.o
hdong04@george:~/Downloads/assign1$ 


***********************
Running the program(s)
***********************
I do not test more case
because I donot know what I should test
but this most time is working

*****************
Known Limitations
*****************
if  "errors" is happen, some case cannot free all things. 
in all the  properties I save as a string and put in 
name all the  properties' propDescr is NULL

