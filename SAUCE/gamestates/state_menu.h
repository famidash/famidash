#pragma code-name(push, "LVL_BANK_00")
#pragma data-name(push, "LVL_BANK_00")
#pragma rodata-name(push, "LVL_BANK_00")

const unsigned char loNTAddrTable[]={
    NTADR_A(9, 11)&0xFF,    // -1 = 4
    NTADR_A(15, 11)&0xFF,   // 0
    NTADR_A(21, 11)&0xFF,   // 1 
    NTADR_A(12, 17)&0xFF,   // 2
    NTADR_A(18, 17)&0xFF,   // 3
    NTADR_A(9, 11)&0xFF,    // 4
    NTADR_A(15, 11)&0xFF    // 5 = 0
};

const unsigned char hiNTAddrTable[]={
    (NTADR_A(9, 11)>>8)&0xFF,   // -1 = 4
    (NTADR_A(15, 11)>>8)&0xFF,  // 0
    (NTADR_A(21, 11)>>8)&0xFF,  // 1
    (NTADR_A(12, 17)>>8)&0xFF,  // 2
    (NTADR_A(18, 17)>>8)&0xFF,  // 3
    (NTADR_A(9, 11)>>8)&0xFF,   // 4
    (NTADR_A(15, 11)>>8)&0xFF   // 5 = 0
};

const unsigned char* const leveltexts[] = {
  level1text, level2text, level3text, level4text, level5text, level6text, level7text, level8text, level9text, levelAtext, levelBtext, levelCtext, levelDtext, levelEtext, levelFtext
};

#define GAME_MENU_TITLE_X_OFFSET 9
const unsigned char level_text_padding[] = {
    GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level1text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level2text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level3text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level4text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level5text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level6text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level7text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level8text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(level9text)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelAtext)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelBtext)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelCtext)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelDtext)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelEtext)) / 2),
	GAME_MENU_TITLE_X_OFFSET + ((17 - sizeof(levelFtext)) / 2),
};
const unsigned char level_text_size[] = {
    sizeof(level1text) - 1,
	sizeof(level2text) - 1,
	sizeof(level3text) - 1,
	sizeof(level4text) - 1,
	sizeof(level5text) - 1,
	sizeof(level6text) - 1,
	sizeof(level7text) - 1,
	sizeof(level8text) - 1,
	sizeof(level9text) - 1,
	sizeof(levelAtext) - 1,
	sizeof(levelBtext) - 1,
	sizeof(levelCtext) - 1,
	sizeof(levelDtext) - 1,
	sizeof(levelEtext) - 1,
	sizeof(levelFtext) - 1,
};

const char* coin_counter[] = {
  "___",
  "^__",
  "_^_",
  "^^_",
  "__^",
  "^_^",
  "_^^",
  "^^^",
};



/*
	Refreshes level name & number
*/
void __fastcall__ refreshmenu(void) {
	#include "../defines/color1_charmap.h"
	// Clear out the previous title
	one_vram_buffer_horz_repeat(' ', 17, NTADR_A(8, 11));
	// center this by offseting the write by the padding amount
	multi_vram_buffer_horz((const char*)leveltexts[level],
		level_text_size[level],
		NTADR_A(level_text_padding[level], 11));

	if (LEVELCOMPLETE[level]) { one_vram_buffer('y', NTADR_A(7, 9));
	one_vram_buffer('z', NTADR_A(8, 9)); }
	else one_vram_buffer_horz_repeat(' ', 2, NTADR_A(7, 9));
	
	// switch(difficulty_list[level]) {
	// 	case 0x00:
	// 		one_vram_buffer('a', NTADR_A(7, 10));
	// 		one_vram_buffer('b', NTADR_A(8, 10));
	// 		one_vram_buffer('c', NTADR_A(7, 11));			
	// 		one_vram_buffer('d', NTADR_A(8, 11));			
	// 		break;
	// 	case 0x01:
	// 		one_vram_buffer('e', NTADR_A(7, 10));
	// 		one_vram_buffer('f', NTADR_A(8, 10));
	// 		one_vram_buffer('g', NTADR_A(7, 11));			
	// 		one_vram_buffer('h', NTADR_A(8, 11));			
	// 		break;
	// 	case 0x02:
	// 		one_vram_buffer('i', NTADR_A(7, 10));
	// 		one_vram_buffer('j', NTADR_A(8, 10));
	// 		one_vram_buffer('k', NTADR_A(7, 11));			
	// 		one_vram_buffer('l', NTADR_A(8, 11));		
	// 		break;
	// 	case 0x03:
	// 		one_vram_buffer('m', NTADR_A(7, 10));
	// 		one_vram_buffer('n', NTADR_A(8, 10));
	// 		one_vram_buffer('o', NTADR_A(7, 11));			
	// 		one_vram_buffer('p', NTADR_A(8, 11));			
	// 		break;
	// 	case 0x04:
	// 		one_vram_buffer('q', NTADR_A(7, 10));
	// 		one_vram_buffer('r', NTADR_A(8, 10));
	// 		one_vram_buffer('s', NTADR_A(7, 11));			
	// 		one_vram_buffer('t', NTADR_A(8, 11));		
	// 		break;
	// 	case 0x05:
	// 		one_vram_buffer('u', NTADR_A(7, 10));
	// 		one_vram_buffer('v', NTADR_A(8, 10));
	// 		one_vram_buffer('w', NTADR_A(7, 11));			
	// 		one_vram_buffer('x', NTADR_A(8, 11));		
	// 		break;
	// };	
	{	// write the difficulty
		tmp1 = (difficulty_list[level] << 1);
		pal_col(0x0a, difficulty_pal[tmp1]);
		pal_col(0x0b, difficulty_pal[tmp1+1]);
		
		tmp1 = (difficulty_list[level] << 1) + 'a';
		one_vram_buffer(tmp1, NTADR_A(7, 10));
		one_vram_buffer(++tmp1, NTADR_A(8, 10));
		tmp1 += byte('c' - 'a' - 1);
		one_vram_buffer(tmp1, NTADR_A(7, 11));
		one_vram_buffer(++tmp1, NTADR_A(8, 11));
		

	}
	tmp7 = stars_list[level];
	tmp8 = 0;
	while (tmp7 > 9) {
		tmp7 = tmp7 - 10;
		tmp8++;
	}

	if (tmp8) one_vram_buffer(0xb0+tmp8, NTADR_A(22,9));
	else one_vram_buffer(' ', NTADR_A(22, 9));
	one_vram_buffer(0xb0+tmp7, NTADR_A(23,9));

//coin stuff
	coins = 0;


// then in the function...
// combine all three into a single number from 0 - 7 to represent which coins have been grabbed
		tmp7 = coin1_obtained[level] | (coin2_obtained[level] << 1) | (coin3_obtained[level] << 2);
// actually draw the coins
		multi_vram_buffer_horz(coin_counter[tmp7], 3, NTADR_A(22, 12));

};

void state_menu();
void levelselection() {
  
	pal_fade_to_withmusic(4,0);
  	ppu_off();
	pal_bright(0);
//    pal_bg((char *)paletteMenu);
	set_scroll_x(0);
    set_scroll_y(0);  
    
    
     vram_adr(NAMETABLE_A);
    vram_unrle(game_main_menu);   

	refreshmenu();

//	one_vram_buffer(0xb0+TOTALCOINSTENS, NTADR_A(17,17));
//	one_vram_buffer(0xb0+TOTALCOINSONES, NTADR_A(18,17));

	cube_rotate[0] = 0;
	cube_rotate[1] = 0;
	attempts = 1;

	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	#include "../defines/mainmenu_charmap.h"
	while (1){
		ppu_wait_nmi();
		music_update();

		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);





		if (pad_new[0] & PAD_START){
			famistudio_sfx_play(sfx_start_level, 0);
			famistudio_music_stop();
			for (tmp1 = 0; tmp1 < 30; tmp1++){
				ppu_wait_nmi();
				music_update();
			}
			gameState = 0x02;
			pal_fade_to(4,0);
			kandotemp = 0;
			return;
		}

		if (pad_new[0] & (PAD_B)){
			state_menu();
			return;
		}
			
			
		if (pad_new[0] & (PAD_RIGHT)){
			++level;
			famistudio_sfx_play(sfx_select, 0);
			if (level > 0x0E){
				level = 0x00;
			}
			refreshmenu();
		//	break;
		}
		if (pad_new[0] & PAD_LEFT){
			--level;
			famistudio_sfx_play(sfx_select, 0); 
			if (level == 0xFF){
				level = 0x0E;
			}
			
			//break;
			refreshmenu();
		}
	}	

}




void bgmtest() {
	famistudio_music_stop();
	music_update();
	kandotemp=0;
	pal_fade_to(4,0);
	ppu_off();
	pal_bg((char *)paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(bgmtestscreen);   	
	#include "../defines/mainmenu_charmap.h"
	ppu_on_all();
	pal_fade_to(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);
		if (settingvalue == 0) {
			one_vram_buffer('c', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
		}		
		else if (settingvalue == 1) {
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer('c', NTADR_A(11, 14));
		}
		if (pad_new[0] & PAD_DOWN) settingvalue ^= 1;
		if (pad_new[0] & PAD_UP) settingvalue ^= 1;
		if (pad_new[0] & PAD_B) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			//state_menu();
			return;
		}
	}
}





void funsettings() {
	pal_fade_to_withmusic(4,0);
	ppu_off();
	pal_bg((char *)paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(funsettingscreen);   
	#include "../defines/mainmenu_charmap.h"
	ppu_on_all();
	one_vram_buffer('c', NTADR_A(4, 8));	// settingvalue is set to 0 by default	
	pal_fade_to_withmusic(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		if (twoplayer) 	one_vram_buffer('d', NTADR_A(6, 8));	// believe it or not, 
		else 	one_vram_buffer('e', NTADR_A(6, 8));	// this is auto optimized by cc65

		if (invisible) 	one_vram_buffer('d', NTADR_A(6, 12));	// believe it or not, 
		else 	one_vram_buffer('e', NTADR_A(6, 12));	// this is auto optimized by cc65

		if (PRACTICE_ENABLED) 	one_vram_buffer('d', NTADR_A(6, 16));	// believe it or not, 
		else 	one_vram_buffer('e', NTADR_A(6, 16));	// this is auto optimized by cc65

		tmp1 = settingvalue;

		if (pad_new[0] & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == 2) { settingvalue = 0; }
			else { settingvalue++; famistudio_sfx_play(sfx_select, 0);  }
		}

		if (pad_new[0] & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = 2; }
			else { settingvalue--; famistudio_sfx_play(sfx_select, 0);  }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 4) << 5 = tmp1<<7 = (tmp1<<8)>>1
			one_vram_buffer(' ', NTADR_A(4, 8)+((tmp1<<8)>>1));
			one_vram_buffer('c', NTADR_A(4, 8)+((settingvalue<<8)>>1));
		}

		if (pad_new[0] & (PAD_START | PAD_A)) {
			switch (settingvalue) {
				case 0x00: twoplayer ^= 1; break;
				case 0x01: invisible ^= 1; break;
				case 0x02: PRACTICE_ENABLED ^= 1; break;
			};
		}
			
		if (pad_new[0] & PAD_B) {
			tmp3--;			
			// one_vram_buffer(' ', NTADR_A(6, 8));
			// one_vram_buffer(' ', NTADR_A(6, 12));
			// one_vram_buffer(' ', NTADR_A(6, 16));
			one_vram_buffer(' ', NTADR_A(4, 8));
			one_vram_buffer(' ', NTADR_A(4, 12));
			one_vram_buffer(' ', NTADR_A(4, 16));
			//state_menu();
			return;
		}

	}
}



void settings() {
	pal_fade_to_withmusic(4,0);
	ppu_off();
	pal_bg((char *)paletteSettings);
	vram_adr(NAMETABLE_A);
	vram_unrle(settingscreen);   	
	#include "../defines/mainmenu_charmap.h"
	ppu_on_all();
	one_vram_buffer('c', NTADR_A(4, 7));	// settingvalue is set to 0 beforehand
	pal_fade_to_withmusic(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

/*		
		if (pad_new[0] & PAD_SELECT){
			if (pad[0] & PAD_A){
				if (pad[0] & PAD_B){
					for (tmp2 = 0; tmp2 <= LEVEL_COUNT; tmp2++) {
						coin1_obtained[tmp2] = 0;
						coin2_obtained[tmp2] = 0;
						coin3_obtained[tmp2] = 0;
					}
							
					tmp2 = 0;
					while (tmp2 < 0x20) {
						LEVELCOMPLETE[tmp2] = 0;
						tmp2++;
					}
				
					SRAM_VALIDATE[0x0E] = 0;
					SRAM_VALIDATE[0x0F] = 0;
					SRAM_VALIDATE[0x10] = 0;
					SRAM_VALIDATE[0x11] = 0;
					SRAM_VALIDATE[0x12] = 0;
					SRAM_VALIDATE[0x13] = 0;
					SRAM_VALIDATE[0x14] = 0;
					SRAM_VALIDATE[0x15] = 0;
					SRAM_VALIDATE[0x16] = 0;
					SRAM_VALIDATE[0x17] = 0;
					SRAM_VALIDATE[0x18] = 0;
					SRAM_VALIDATE[0x19] = 0;
					SRAM_VALIDATE[0x1A] = 0;
					SRAM_VALIDATE[0x1B] = 0;
					SRAM_VALIDATE[0x1C] = 0;
					SRAM_VALIDATE[0x1D] = 0;
					SRAM_VALIDATE[0x1E] = 0;
					SRAM_VALIDATE[0x1F] = 0;
					TOTALCOINSONES = 0;
					TOTALCOINSTENS = 0;
				//	one_vram_buffer(0xb0+TOTALCOINSTENS, NTADR_A(17,17));
				//	one_vram_buffer(0xb0+TOTALCOINSONES, NTADR_A(18,17));					
					famistudio_sfx_play(sfx_death, 0);
				//	one_vram_buffer_horz_repeat(' ', 1, NTADR_A(16, 15));		
				}
			}
			else {
				famistudio_sfx_play(sfx_click, 0);			
				twoplayer ^= 1;
			}
		}
*/		
		if (oneptwoplayer) one_vram_buffer('g', NTADR_A(26, 7));
		else one_vram_buffer('f', NTADR_A(26, 7));

		if (deathsound) one_vram_buffer('g', NTADR_A(26, 9));
		else one_vram_buffer('f', NTADR_A(26, 9));

		if (jumpsound) one_vram_buffer('g', NTADR_A(26, 11));
		else one_vram_buffer('f', NTADR_A(26, 11));

		if (platformer) one_vram_buffer('g', NTADR_A(26, 13));
		else one_vram_buffer('f', NTADR_A(26, 13));

		tmp1 = settingvalue;

		if (pad_new[0] & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == 4) { settingvalue = 0; famistudio_sfx_play(sfx_select, 0); }
			else { settingvalue++; famistudio_sfx_play(sfx_select, 0);  }
		}

		if (pad_new[0] & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = 4; famistudio_sfx_play(sfx_select, 0); }
			else { settingvalue--; famistudio_sfx_play(sfx_select, 0);  }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 2) << 5 = tmp1<<6 = (tmp1<<8)>>2
			one_vram_buffer(' ', NTADR_A(4, 7)+((tmp1<<8)>>2));
			one_vram_buffer('c', NTADR_A(4, 7)+((settingvalue<<8)>>2));
		}
		
		if (pad_new[0] & (PAD_A | PAD_START)) {
			switch (settingvalue) {
				case 0:
					oneptwoplayer ^= 1; break;
				case 1:
					deathsound ^= 1; break;
				case 2:
					jumpsound ^= 1; break;
				case 3:
					platformer ^= 1; break;
				case 4:
					if (pad[0] & PAD_A && pad_new[0] & PAD_START) {
						for (tmp2 = 0; tmp2 <= LEVEL_COUNT; tmp2++) {
							coin1_obtained[tmp2] = 0;
							coin2_obtained[tmp2] = 0;
							coin3_obtained[tmp2] = 0;
						}
								
						tmp2 = 0;
						while (tmp2 < 0x20) {
							LEVELCOMPLETE[tmp2] = 0;
							tmp2++;
						}
					
						SRAM_VALIDATE[0x0E] = 0;
						SRAM_VALIDATE[0x0F] = 0;
						SRAM_VALIDATE[0x10] = 0;
						SRAM_VALIDATE[0x11] = 0;
						SRAM_VALIDATE[0x12] = 0;
						SRAM_VALIDATE[0x13] = 0;
						SRAM_VALIDATE[0x14] = 0;
						SRAM_VALIDATE[0x15] = 0;
						SRAM_VALIDATE[0x16] = 0;
						SRAM_VALIDATE[0x17] = 0;
						SRAM_VALIDATE[0x18] = 0;
						SRAM_VALIDATE[0x19] = 0;
						SRAM_VALIDATE[0x1A] = 0;
						SRAM_VALIDATE[0x1B] = 0;
						SRAM_VALIDATE[0x1C] = 0;
						SRAM_VALIDATE[0x1D] = 0;
						SRAM_VALIDATE[0x1E] = 0;
						SRAM_VALIDATE[0x1F] = 0;
						TOTALCOINSONES = 0;
						TOTALCOINSTENS = 0;
						deathsound = 1;
					//	one_vram_buffer(0xb0+TOTALCOINSTENS, NTADR_A(17,17));
					//	one_vram_buffer(0xb0+TOTALCOINSONES, NTADR_A(18,17));					
						famistudio_sfx_play(sfx_death, 0);
					//	one_vram_buffer_horz_repeat(' ', 1, NTADR_A(16, 15));					
					}
					break;
			}
		}
		if (platformer) twoplayer = 0;		
		if (twoplayer) platformer = 0;		

		if (pad_new[0] & PAD_B) {
			tmp3--;			
			//state_menu();
			return;
		}

	}
}





void state_menu() {
	pal_fade_to_withmusic(4,0);
	ppu_off();
    pal_bg((char *)splashMenu);

	mmc3_set_8kb_chr(12);

	set_scroll_x(0);
    set_scroll_y(0);

	mmc3_set_prg_bank_1(0);

	switch (kandotemp){
		case 0x00:	music_play(song_menu_theme); break;
		case 0x01:	break;
	}

	settingvalue = 0;
	
	has_practice_point = 0;
	
	#include "../defines/mainmenu_charmap.h"
	// Enable SRAM write
	POKE(0xA001, 0x80);

	// Get it? it spells DASH
	if (SRAM_VALIDATE[0] != 0x0D
	 || SRAM_VALIDATE[1] != 0x0A
	 || SRAM_VALIDATE[2] != 0x01
	 || SRAM_VALIDATE[3] != 0x01) {
		// set the validation header and then reset coin counts
		SRAM_VALIDATE[0] = 0x0d;
		SRAM_VALIDATE[1] = 0x0a;
		SRAM_VALIDATE[2] = 0x01;
		SRAM_VALIDATE[3] = 0x01;
		for (tmp2 = 0; tmp2 <= LEVEL_COUNT; tmp2++) {
			coin1_obtained[tmp2] = 0;
			coin2_obtained[tmp2] = 0;
			coin3_obtained[tmp2] = 0;
		}

		tmp2 = 0;
		while (tmp2 < 20) {
			LEVELCOMPLETE[tmp2] = 0;
			tmp2++;
		}
		SRAM_VALIDATE[0x0E] = 0;
		SRAM_VALIDATE[0x0F] = 0;
		SRAM_VALIDATE[0x10] = 0;
		SRAM_VALIDATE[0x11] = 0;
		SRAM_VALIDATE[0x12] = 0;
		SRAM_VALIDATE[0x13] = 0;
		SRAM_VALIDATE[0x14] = 0;
		SRAM_VALIDATE[0x15] = 0;
		SRAM_VALIDATE[0x16] = 0;
		SRAM_VALIDATE[0x17] = 0;
		SRAM_VALIDATE[0x18] = 0;
		SRAM_VALIDATE[0x19] = 0;
		SRAM_VALIDATE[0x1A] = 0;
		SRAM_VALIDATE[0x1B] = 0;
		SRAM_VALIDATE[0x1C] = 0;
		SRAM_VALIDATE[0x1D] = 0;
		SRAM_VALIDATE[0x1E] = 0;
		SRAM_VALIDATE[0x1F] = 0;
		deathsound = 1;
		jumpsound = 0;
		twoplayer = 0;
		oneptwoplayer = 0;
	}

	kandotemp = 1;
//	invisible = 0;
	TOTALCOINS = 0;
	TOTALCOINSONES = 0;
	TOTALCOINSTENS = 0;

	for (tmp2 = 0; tmp2 <= LEVEL_COUNT; tmp2++) {
		TOTALCOINS = TOTALCOINS + coin1_obtained[tmp2] + coin2_obtained[tmp2] + coin3_obtained[tmp3];
	}
	TOTALCOINSTEMP = TOTALCOINS;
	
	while (TOTALCOINSTEMP > 9) {
		TOTALCOINSTENS = TOTALCOINSTENS + 1;
		TOTALCOINSTEMP = TOTALCOINSTEMP - 10;
	}
	TOTALCOINSONES = TOTALCOINSTEMP;
	
		

	oam_clear();

	// Expand the data for the menu nametable while the PPU is still off
    vram_adr(NAMETABLE_A);
    vram_unrle(game_start_screen);
 	ppu_on_all();
	pal_fade_to_withmusic(0,4);
		tmp4 = menuselection; ++tmp4;
		tmp5 = loNTAddrTable[tmp4]|(hiNTAddrTable[tmp4]<<8);
		one_vram_buffer('a', tmp5);
		one_vram_buffer('b', addloNOC(tmp5, 1));
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);
	while (!(pad_new[0] & PAD_START)){
		ppu_wait_nmi();
		music_update();
		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

            tmp3 = 0; 
            
            if (pad_new[0] & PAD_RIGHT) {
                if (menuselection == 4) menuselection = 0;
                else menuselection++;
                tmp3--;
				famistudio_sfx_play(sfx_select, 0);
            }
            if (pad_new[0] & PAD_LEFT) {
                if (menuselection == 0) menuselection = 4;
                else menuselection--;
                tmp3++;
				famistudio_sfx_play(sfx_select, 0);
            }

            if (tmp3) {    // menu selection incremented
                tmp4 = menuselection; ++tmp4;
				tmp5 = loNTAddrTable[tmp4]|(hiNTAddrTable[tmp4]<<8);
                one_vram_buffer('a', tmp5);
                one_vram_buffer('b', addloNOC(tmp5, 1));

                tmp4 += tmp3;   // Get the old index
				tmp5 = loNTAddrTable[tmp4]|(hiNTAddrTable[tmp4]<<8);
                one_vram_buffer(' ', tmp5);
                one_vram_buffer(' ', addloNOC(tmp5, 1));
            }



	}		
	switch (menuselection) {
		case 0x00: levelselection(); return; break;
		case 0x01: settingvalue = 0; funsettings(); return; break;
		case 0x02: bgmtest(); return; break;
		case 0x03: settingvalue = 0; settings(); return; break;
		case 0x04: state_menu(); return; break;
			
	};
  
}



#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
