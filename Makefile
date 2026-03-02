all : main

main : main.c memory.c cpu.c platform/linux/timer.c
	gcc -Wall -Wextra -Ipthread -lpthread -Iplatform/ platform/linux/timer.c main.c cpu.c memory.c -o builds/main

clean: 
	rm builds/main

esp: main.c memory.c cpu.c
	idf.py -C esp/  build flash monitor
