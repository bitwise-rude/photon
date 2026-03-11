all : main

main : main.c memory.c cpu.c platform/linux/timer.c platform/linux/ppu.c 
	gcc   main.c platform/linux/ppu.c platform/linux/timer.c cpu.c memory.c -o builds/main \
-lraylib -lm -lpthread -ldl -lrt -lX11 -Iplatform/ 

windows : main.c memory.c cpu.c platform/windows/timer.c
	gcc -Wall -Wextra -Ipthread -lpthread -Iplatform/ platform/windows/timer.c main.c cpu.c memory.c -o builds/main
clean: 
	rm builds/main

esp: main.c memory.c cpu.c
	idf.py -C esp/  build flash monitor
