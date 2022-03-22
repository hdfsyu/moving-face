#include <gb/gb.h>
#include <stdio.h>
#include "FaceSprites.c"
#include "background.c"
#include "backgroundmap.c"
void main(){
	UINT8 currentspriteindex = 0;
	set_bkg_data(0, 7, backgroundtiles);
	set_bkg_tiles(0, 0, 40, 18, backgroundmap);
	set_sprite_data(0, 2, Faces);
	set_sprite_tile(0, 0);
	move_sprite(0, 88, 78);
	SHOW_BKG;
	SHOW_SPRITES;
	DISPLAY_ON;
	while(1){
		switch(joypad()){
			case J_LEFT:
				scroll_sprite(0, -5, 0);
				break;
			case J_RIGHT:
				scroll_sprite(0, 5, 0);
				break;
			case J_UP:
				scroll_sprite(0, 0, -5);
				break;
			case J_DOWN:
				scroll_sprite(0, 0, 5);
				break;
		}
		scroll_bkg(1,0);
		delay(100); // please dont remove this otherwise you get an uncontrollable sonic tile
	}
}
