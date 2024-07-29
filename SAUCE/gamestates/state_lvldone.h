extern volatile unsigned char VRAM_UPDATE;
#pragma zpsym ("VRAM_UPDATE")

#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")


void checkcointimer(){
	if (tmp1 == 1){
		famistudio_sfx_play(sfx_coin,0);
		tmp1 = 50;
	}
}
void checkcoinproceed(){
	if (tmp1 == 0 || tmp1 == 30) {
		tmp2++;
		tmp1 = 1;
	}
}


void state_lvldone() {
#define current_state tmp2
#define sprite_0_y tmp3
#define delay_spr_0 tmp4
#define delay_timer tmpptr1
#define top_scroll scroll_x
    ppu_off();

	delay_spr_0 = 0x20;

	current_state = 0;

	// Set palettes back to natural colors since we aren't fading back in
	pal_bright(4);

    pal_bg(paletteMenu);
	pal_col(0x0A,0x2A);
	pal_col(0x0B,0x21);
    pal_spr(paletteMenu);

	mmc3_set_8kb_chr(LEVELCOMPLETEBANK);

	// Make an a nametable for the chain
    vram_adr(NAMETABLE_A);
	vram_fill(0xfe, 0x3c0);
	vram_fill(0x00, 0x3f);
	// vertical increment: draw the chains
	vram_inc(1);
    vram_adr(NTADR_A(5, 0));
	vram_fill(0xae, 30);
    vram_adr(NTADR_A(26, 0));
	vram_fill(0xae, 30);

	// Make an empty nametable for the scroll split
    vram_adr(NAMETABLE_B);
	vram_inc(0);
	vram_fill(0xfe, 0x3c0);
	vram_fill(0x00, 0x3f);

	// Copy the level done screen to the bot left and right nametable
    vram_adr(NAMETABLE_C);
    vram_unrle(leveldone);

	// Change the text attributes for the press to return
    vram_adr(0x2be1);
	vram_fill(0xff, 0x6);

    vram_adr(NAMETABLE_D);
    vram_unrle(leveldone);

	#include "defines/endlevel_charmap.h"
	//multi_vram_buffer_horz((const char*)menutext3,sizeof(menutext3)-1,NTADR_C(6, 16));
	//multi_vram_buffer_horz((const char*)menutext4,sizeof(menutext4)-1,NTADR_C(8, 18));
	//multi_vram_buffer_horz((const char*)attemptstext,sizeof(attemptstext)-1,NTADR_C(7, 19));
	
	tmp1 = 0;
	tmpptr1 = NULL;

	printDecimal(attempts, 5, 0xD0, 0xFF, NTADR_C(18,13));
	
	if (!has_practice_point) {
		LEVELCOMPLETE[level] = 1;
		
		if (coins & COIN_1) coin1_obtained[level] = 1;
		if (coins & COIN_2) coin2_obtained[level] = 1;
		if (coins & COIN_3) coin3_obtained[level] = 1;

		level_completeness_normal[level] = 100;
	} else {
		level_completeness_practice[level] = 100;
	}
	
	
	if (!coins) {
		tmp1 = sizeof(coins0) - 1;
		tmpptr1 = (unsigned char*)coins0;
	} else if ((coins & 7) == 7) {
		tmp1 = sizeof(coins3) - 1;
		tmpptr1 = (unsigned char*)coins3;
	} else if (((coins & COIN_1) && (coins & COIN_2)) || ((coins & COIN_2) && (coins & COIN_3)) || ((coins & COIN_1) && (coins & COIN_3))) {
		tmp1 = sizeof(coins2) - 1;
		tmpptr1 = (unsigned char*)coins2;
	} else if (coins & COIN_1 || coins & COIN_2 || coins & COIN_3) {
		tmp1 = sizeof(coins1) - 1;
		tmpptr1 = (unsigned char*)coins1;
	}
	 
	//if (tmp1) multi_vram_buffer_horz((const char*)tmpptr1,tmp1,NTADR_C(17,18));
	flush_vram_update2();

	// Set the start of the scroll to the top nametable
	// so we can scroll it down (so the screen comes up)
    top_scroll = 0x00;

	// setup sprite zero at the very bottom of the screen for now
	sprite_0_y = 0xee;
	POKE(0x200, sprite_0_y);
	POKE(0x201, 0x02); // Use the second tile in the BG side which is pure black
	POKE(0x202, 0x02); // second palette
	POKE(0x203, 0);

    set_scroll_x(0);
    set_scroll_y(top_scroll);

//	one_vram_buffer(0xD0+coins, NTADR_A(12,9));

    ppu_on_all();



	sfx_play(sfx_level_complete, 0);
	menuselection = 1;

	while (1) {
		// Rather hacky, but when doing sprite zero at the bottom of the screen we DON'T 
		// want to skip a frame, so we re-enable NMI and then if NMI happens during the frame
		// we don't have a lag frame by skipping it.
		if (VRAM_UPDATE == 1) {
        	ppu_wait_nmi();
		}
		// force re-enable NMI every frame.
		VRAM_UPDATE = 1;

		music_update();

		// wait for sprite zero hit
		if (current_state > 0 && current_state < 3) {
			xy_split(0x100, scroll_y);
		}

 		// read the first controller
		pad_poll(0);
		// Move the sprite zero hit to the new location
		POKE(0x200, sprite_0_y);

		switch (current_state) {
		case 0:
			// Scroll the screen top bar up a bit
			top_scroll += 2;
			set_scroll_y(top_scroll);
			if (top_scroll >= 31) {
				scroll_y = 256 + 208 - 1;
				current_state = 1;
			}
			break;
		case 1:
			// keep scrolling up, but have sprite zero follow now
			sprite_0_y -= 2;
			top_scroll += 2;
			set_scroll_y(top_scroll);
			// Play the level complete noise
			// if (top_scroll == 115) {
			// }
			if (top_scroll > 151) {
				current_state = 2;
			}
			break;
		case 2:
			// keep scrolling up, but change the scroll split Y
			// so it starts to "unravel"
			sprite_0_y -= 2;
			top_scroll += 2;
			scroll_y -= 4;
			set_scroll_y(top_scroll);
			if (top_scroll == 240) {
				set_scroll_x(0);
				set_scroll_y(0x100);
				current_state = 3;
			}
			break;
		case 3:
			// Draw the level stat text
			//achievements
			TOTALCOINS = 0;
			TOTALSTARS = 0;

			for (tmp2 = 0; tmp2 < LEVEL_COUNT; tmp2++) {
				// TOTALCOINS = TOTALCOINS + coin1_obtained[tmp2] + coin2_obtained[tmp2] + coin3_obtained[tmp2];
				__A__ = tmp2; __asm__("tay");
				__A__ = TOTALCOINS;
				__asm__("clc \n adc %v, y", coin1_obtained);
				__asm__("clc \n adc %v, y", coin2_obtained);
				__asm__("clc \n adc %v, y", coin3_obtained);
				TOTALCOINS = __A__;
				
				if (LEVELCOMPLETE[tmp2]) TOTALSTARS += stars_list[tmp2];
			}

			for (tmp2 = 0; tmp2 <= 10; tmp2++) {
				if (!achievements[tmp2]) {
					if (LEVELCOMPLETE[tmp2]) {
						achievements[tmp2] = 1;
						switch (tmp2) {
							case 0:
							case 1:
							case 2:
							case 3:			//display achievements here
							case 4:
							case 5:
							case 6:
							case 7:
							case 8:
							case 9:
							case 10: break;
						};
					}
				}
			}

			if (!achievements[11]) {
				if (TOTALCOINS >= 10) {
					achievements[11] = 1;
					//display text here
				}
			}

			if (!achievements[12]) {
				if (TOTALCOINS >= 20) {
					achievements[12] = 1;
					//display text here
				}
			}
				
			
			if (!achievements[13]) {
				if (TOTALCOINS >= 30) {
					achievements[13] = 1;
					//display text here
				}
			}
				
			
			if (!achievements[14]) {
				
			}
			if (!achievements[15]) {
				
			}
			if (!achievements[16]) {
				
			}
			if (!achievements[17]) {
				
			}
			if (!achievements[18]) {
				
			}
			if (!achievements[19]) {
				
			}

			current_state = 4;
			tmp1 = 1;
			break;
		case 4: // coin 1
			if (coins & COIN_1){
				one_vram_buffer(0x90, NTADR_C(11,18));
				one_vram_buffer(0x91, NTADR_C(12,18));
				one_vram_buffer(0xA0, NTADR_C(11,19));
				one_vram_buffer(0xA1, NTADR_C(12,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 5: // coin 2
			if (coins & COIN_2){
				one_vram_buffer(0x90, NTADR_C(15,18));
				one_vram_buffer(0x91, NTADR_C(16,18));
				one_vram_buffer(0xA0, NTADR_C(15,19));
				one_vram_buffer(0xA1, NTADR_C(16,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 6: // coin 3
			if (coins & COIN_3){
				one_vram_buffer(0x90, NTADR_C(19,18));
				one_vram_buffer(0x91, NTADR_C(20,18));
				one_vram_buffer(0xA0, NTADR_C(19,19));
				one_vram_buffer(0xA1, NTADR_C(20,19));
				checkcointimer();
			}
			tmp1--;
			checkcoinproceed();
			break;
		case 7:
			if (pad_new[0] & PAD_LEFT) menuselection ^= 1;
			if (pad_new[0] & PAD_RIGHT) menuselection ^= 1;
			if (pad_new[0] & PAD_START){
				if (menuselection) {
					
					sfx_play(sfx_exit_level, 0);
					music_update();
					gameState = 1;
					menuselection = 0;
					kandowatchesyousleep = 1;
					return;
				} else {
					
					sfx_play(sfx_start_level, 0);
					gameState = 2;
					pal_fade_to_withmusic(4,0);
					return;
				}
			}


			if (menuselection) {
				one_vram_buffer(' ', NTADR_C(8,23));
				one_vram_buffer(' ', NTADR_C(9,23));
				one_vram_buffer(0x94, NTADR_C(22,23));
				one_vram_buffer(0x95, NTADR_C(23,23));
			} else {
				one_vram_buffer(0x94, NTADR_C(8,23));
				one_vram_buffer(0x95, NTADR_C(9,23));
				one_vram_buffer(' ', NTADR_C(22,23));
				one_vram_buffer(' ', NTADR_C(23,23));
			}
			break;
		}
	}
#undef current_state
#undef sprite_0_y
#undef delay_spr_0
#undef delay_timer
#undef top_scroll
}


void bgmtest() {
	#define sfx tmp4
	sfx = 0;

  	famistudio_music_stop();
  	music_update();
	kandotemp=0;
	pal_fade_to(4,0);
	ppu_off();
	pal_bg(paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(bgmtestscreen);   	
	#include "defines/mainmenu_charmap.h"
	ppu_on_all();
	pal_fade_to(0,4);
	while (1) {
		
		ppu_wait_nmi();
		music_update();
		pad_poll(0); // read the first controller
		
		one_vram_buffer(' '-1, NTADR_A(14, 10));
		one_vram_buffer(0xb0+song, NTADR_A(15,10));
		one_vram_buffer(' '-1, NTADR_A(14, 17));
		one_vram_buffer(0xb0+sfx, NTADR_A(15,17));

		if (settingvalue == 0) {
			one_vram_buffer('c', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			if (pad_new[0] & PAD_RIGHT) { song++; if (song == song_max) {song = 0;} }
			if (pad_new[0] & PAD_LEFT) { if (song == 0) {song = song_max - 1;} else song--; }
			if ((pad_new[0] & PAD_START || pad_new[0] & PAD_A)) music_play(song);
		}		
		else if (settingvalue == 1) {
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer('c', NTADR_A(11, 14));
			if (pad_new[0] & PAD_RIGHT) { sfx++; if (sfx == sfx_max) {sfx= 0;} };
			if (pad_new[0] & PAD_LEFT) { if (sfx == 0) {sfx = sfx_max - 1;} else sfx--; }
			if ((pad_new[0] & PAD_START || pad_new[0] & PAD_A)) famistudio_sfx_play(sfx, 0);
		}

		if (pad_new[0] & PAD_DOWN) settingvalue ^= 1;
		if (pad_new[0] & PAD_UP) settingvalue ^= 1;
		
				
		if (pad_new[0] & PAD_B) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			kandotemp = 1;
			gameState = 1;
			return;
		}
	}
#undef sfx
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
