#include <raylib.h>
#include "../ppu.h"
#include <stdio.h>

#define SCREEN_HEIGHT 128
#define SCREEN_WIDTH 64
#define SCREEN_SCALE 5

void graphics_init(){
	InitWindow(SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE, "03-10");
}

int show_buffer(u8 frame_buffer[64][128]){
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello World",190,200,20, LIGHTGRAY);
	EndDrawing();

	return WindowShouldClose();
}
