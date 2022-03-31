// dont remove any delay(); code
#include <gb/gb.h>
#include <gb/font.h>
#include <stdio.h>
#include "FaceSprites.c"
#include "background.c"
#include "backgroundmap.c"
#include "windowmap.c"
INT8 playerlocation[2];
BYTE jumping = 0;
UINT8 gravity = -2;
UINT8 currentspeedY;
UINT8 groundYPos = 117;
INT8 wouldhitsurface(UINT8 projectedYPos){
	if(projectedYPos >= groundYPos){
		return groundYPos;
	}
	return -1;
}
void jump(){
	INT8 possiblesurfaceY;
	if(jumping==0){
		jumping = 1;
		currentspeedY = 10;
	}
	currentspeedY = currentspeedY + gravity;
	playerlocation[1] = playerlocation[1] - currentspeedY;
	possiblesurfaceY = wouldhitsurface(playerlocation[1]);
	if(possiblesurfaceY > -1){
		jumping = 0;
		move_sprite(0,playerlocation[0],possiblesurfaceY);
	}else{
		move_sprite(0,playerlocation[0],playerlocation[1]);
	}
	move_sprite(0,playerlocation[0],playerlocation[1]);
}
void main(){
	UINT8 currentspriteindex = 0;
	font_t min_font;
	font_init();
	min_font = font_load(font_min);
	font_set(min_font);
	set_bkg_data(37, 7, backgroundtiles);
	set_bkg_tiles(0, 0, 40, 18, backgroundmap);
	set_win_tiles(0, 0, 7, 1, windowmap);
	move_win(7, 120);
	set_sprite_data(0, 2, Faces);
	set_sprite_tile(0, 0);
	playerlocation[0] = 10;
	playerlocation[1] = groundYPos;
	move_sprite(0,playerlocation[0],playerlocation[1]);
	NR52_REG = 0x80;
	NR50_REG = 0x77;
	NR51_REG = 0xFF;
	SHOW_BKG;
	SHOW_WIN;
	SHOW_SPRITES;
	DISPLAY_ON;
	while(1){
		UBYTE joypad_state = joypad();	
		if(joypad() & J_LEFT){
			playerlocation[0] = playerlocation[0] - 2;
			move_sprite(0,playerlocation[0],playerlocation[1]);
		}
		if(joypad() & J_RIGHT){
			playerlocation[0] = playerlocation[0] + 2;
			move_sprite(0,playerlocation[0],playerlocation[1]);
		}
		if((joypad() & J_A) || jumping == 1){
			jump();
		}
		if(joypad_state){
			NR10_REG = 0x16;
			NR11_REG = 0x40;
			NR12_REG = 0x73;
			NR13_REG = 0x00;
			NR14_REG = 0xC3;
		}
		scroll_bkg(1,0);
		delay(100);
	}
}
