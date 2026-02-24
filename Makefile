all : main

main : main.c cpu.c
	gcc -Wall -Wextra main.c cpu.c -o builds/main

