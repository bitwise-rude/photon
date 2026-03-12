#include <raylib.h>
#include "../ppu.h"
#include <stdio.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_SCALE 8

void graphics_init(){
	InitWindow(SCREEN_WIDTH * SCREEN_SCALE, SCREEN_HEIGHT * SCREEN_SCALE, "03-10");
}

int show_buffer(u8 frame_buffer[64][128]){
	BeginDrawing();

	// Drawing the buffers
	// Explained in instructions on how to draw
	for(int i=0;i<SCREEN_HEIGHT;i++) {
		for(int j=0;j<SCREEN_WIDTH;j++){

			Color clr  = frame_buffer[i][j] == 0 ? BLACK: RAYWHITE;	

			DrawRectangle(
				j * SCREEN_SCALE, i * SCREEN_SCALE,
				SCREEN_SCALE, SCREEN_SCALE, clr 
			);
		}
	}
	EndDrawing();

	return WindowShouldClose();
}
