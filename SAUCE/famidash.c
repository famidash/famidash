// THE GAME LOOP ==============================================
//
// yup, this is the entire game loop. it's that simple.
// I wanted to make the code super easy to read, so I split it
// into dozens of files, each containing segments of code.
//
// ============================================================



// THE INCLUDE FILE ===========================================
//
// The entirety of the project is on the shoulders of this
// singular line. 
//
//                    DO. NOT. REMOVE. IT.
//
// If you have issues with the repository and the cause is you
// removing this line, the entire team will be informed to not
// communicate with you further.
#include "include.h"
// ============================================================



// VOID MAIN() ================================================
//
// This isn't an int main() because i don't use the terminal to
// debug lmao
void main(){
    ppu_off();

    ppu_mask(0x00 | (1 << 1) | (1 << 2));

	mmc3_set_8kb_chr(MENUBANK);

    //pal_bg(paletteDefault);
    //pal_spr(paletteDefaultSP);
    // use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
	bank_spr(1);

    set_vram_buffer(); // do at least once

    // ppu_on_all();
    // pal_fade_to(4,0);

	// These are done at init time
    // gameState = 0x01;
    // level = 0x00;
	// auto_fs_updates = 0;

	

	gameState = 0x00;
    while (1){
        ppu_wait_nmi();

		switch (gameState){
			case 0x01: {
				mmc3_set_prg_bank_1(GET_BANK(state_menu));
				if (!kandowatchesyousleep) state_menu();
				else {
					pal_fade_to_withmusic(4,0);
					ppu_off();
					pal_bg(splashMenu);
					mmc3_set_8kb_chr(MENUBANK);

					set_scroll_x(0);
					set_scroll_y(0);

					kandowatchesyousleep = 1;

					//	mmc3_set_prg_bank_1(GET_BANK(state_menu));

					if (kandotemp == 0) music_play(song_menu_theme);

					settingvalue = 0;

					has_practice_point = 0;

					#include "defines/mainmenu_charmap.h"
					

					oam_clear();	

					levelselection();
				}
					break;
			}
			case 0x02: {
  				player_gravity[0] = 0x00;
				player_gravity[1] = 0x00;					
				state_game(); break;
			}
			case 0x03: {
				mmc3_set_prg_bank_1(GET_BANK(state_lvldone));
				state_lvldone();
				break;
			}
			case 0x04: {
				mmc3_set_prg_bank_1(GET_BANK(bgmtest));
				bgmtest();
				break;
			}
			case 0x05: {
				mmc3_set_prg_bank_1(GET_BANK(state_savefile_validate));
				state_savefile_validate();
				break;
			}
			default: {
				mmc3_set_prg_bank_1(GET_BANK(state_demo));
				state_demo();
				
				break;
			}
		}
    }
}
// ============================================================


// WHY I SPLIT THE GAME LOOP ==================================
//
// I like making my code super readable by outsiders, and I
// felt like this was the best way to do it.
// ============================================================

void setdefaultoptions() {
	// Enable SRAM write
	POKE(0xA001, 0x80);

	// fill with zeros
	memfill((uint8_t *)0x6000, 0, 0x2000);

	// set the first four bytes; LEET, save version, and 21.
	// if none of these are what is expected, the game will tell you
	SRAM_VALIDATE[0] = 0x13;
	SRAM_VALIDATE[1] = 0x37;
	SRAM_VALIDATE[2] = FLAG_SAVE_VER;
	SRAM_VALIDATE[3] = 0x21;
	
	// only non-zero values need to be set here

	//twoplayer = 0;
	//musicoff = 0;
	//sfxoff = 0;
	//jumpsound = 0;
	//oneptwoplayer = 0;
	//platformer = 0;
	//options = 0; 


	//invisible = 0;
	color1 = 0x2A;
	color2 = 0X2C;		
	color3 = 0x0F;
	//discomode = 0;
	//icon = 0;
	//trails = 0;
	//retro_mode = 0;
	//palette_cycle_mode = 0;
	//gameboy_mode = 0;
	decorations = 1;
	//invisblocks = 0;
	return;
}