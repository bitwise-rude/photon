all : main

main : main.c memory.c cpu.c
	gcc -Wall -Wextra main.c cpu.c memory.c -o builds/main

clean: 
	rm builds/main
