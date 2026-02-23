all : main

main : main.c
	gcc -Wall -Wextra main.c -o builds/main

