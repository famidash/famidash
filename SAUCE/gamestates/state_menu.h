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
  level1text, level2text, level3text, level4text, level5text, level6text, level7text, level8text, level9text, levelAtext, levelBtext, levelCtext, levelDtext
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

	if (LEVELCOMPLETE[level]) { one_vram_buffer_horz_repeat('y', 1, NTADR_A(7, 9));
	one_vram_buffer_horz_repeat('z', 1, NTADR_A(8, 9)); }
	else one_vram_buffer_horz_repeat(' ', 2, NTADR_A(7, 9));
	
	switch(difficulty_list[level]) {
		case 0x00:
			one_vram_buffer_horz_repeat('a', 1, NTADR_A(7, 10));
			one_vram_buffer_horz_repeat('b', 1, NTADR_A(8, 10));
			one_vram_buffer_horz_repeat('c', 1, NTADR_A(7, 11));			
			one_vram_buffer_horz_repeat('d', 1, NTADR_A(8, 11));			
			break;
		case 0x01:
			one_vram_buffer_horz_repeat('e', 1, NTADR_A(7, 10));
			one_vram_buffer_horz_repeat('f', 1, NTADR_A(8, 10));
			one_vram_buffer_horz_repeat('g', 1, NTADR_A(7, 11));			
			one_vram_buffer_horz_repeat('h', 1, NTADR_A(8, 11));			
			break;
		case 0x02:
			one_vram_buffer_horz_repeat('i', 1, NTADR_A(7, 10));
			one_vram_buffer_horz_repeat('j', 1, NTADR_A(8, 10));
			one_vram_buffer_horz_repeat('k', 1, NTADR_A(7, 11));			
			one_vram_buffer_horz_repeat('l', 1, NTADR_A(8, 11));		
			break;
		case 0x03:
			one_vram_buffer_horz_repeat('m', 1, NTADR_A(7, 10));
			one_vram_buffer_horz_repeat('n', 1, NTADR_A(8, 10));
			one_vram_buffer_horz_repeat('o', 1, NTADR_A(7, 11));			
			one_vram_buffer_horz_repeat('p', 1, NTADR_A(8, 11));			
			break;
		case 0x04:
			one_vram_buffer_horz_repeat('q', 1, NTADR_A(7, 10));
			one_vram_buffer_horz_repeat('r', 1, NTADR_A(8, 10));
			one_vram_buffer_horz_repeat('s', 1, NTADR_A(7, 11));			
			one_vram_buffer_horz_repeat('t', 1, NTADR_A(8, 11));		
			break;
		case 0x05:
			one_vram_buffer_horz_repeat('u', 1, NTADR_A(7, 10));
			one_vram_buffer_horz_repeat('v', 1, NTADR_A(8, 10));
			one_vram_buffer_horz_repeat('w', 1, NTADR_A(7, 11));			
			one_vram_buffer_horz_repeat('x', 1, NTADR_A(8, 11));		
			break;
	};	
	tmp7 = stars_list[level];
	tmp8 = 0;
	while (tmp7 > 9) {
		tmp7 = tmp7 - 10;
		tmp8++;
	}

	if (tmp8) one_vram_buffer(0xb0+tmp8, NTADR_A(22,9));
	else one_vram_buffer_horz_repeat(' ', 1, NTADR_A(22, 9));
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
	pal_fade_to(0,4);
	#include "../defines/mainmenu_charmap.h"
	while (1){
		ppu_wait_nmi();
		music_update();

		pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);





		if (pad_new[0] & PAD_START){
			if (pad[0] & PAD_A){
				if (pad[0] & PAD_B){
					invisible = 1;
					famistudio_sfx_play(sfx_death, 0);
					gameState = 0x02;
					pal_fade_to(4,0);
					kandotemp = 0;
					return;
				}
			}
			else {
				gameState = 0x02;
				pal_fade_to(4,0);
				kandotemp = 0;
				return;
			}
			
		}

		if (pad_new[0] & (PAD_B)){
			state_menu();
			return;
		}
			
			
		if (pad_new[0] & (PAD_RIGHT)){
			++level;
			if (level > 0x0C){
				level = 0x00;
			}
			refreshmenu();
		//	break;
		}
		if (pad_new[0] & PAD_LEFT){
			--level;
			if (level == 0xFF){
				level = 0x0C;
			}
			
			//break;
			refreshmenu();
		}
	}	

}









void settings() {
	ppu_off();
	pal_bg((char *)paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(settingsscreen);   	
	#include "../defines/mainmenu_charmap.h"
	ppu_on_all();
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
		if (settingvalue == 0) {
			one_vram_buffer_horz_repeat('c', 1, NTADR_A(4, 8));
			one_vram_buffer_horz_repeat('d', 1, NTADR_A(4, 9));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 12));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 13));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 16));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 17));
		}		
		else if (settingvalue == 1) {
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 8));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 9));
			one_vram_buffer_horz_repeat('c', 1, NTADR_A(4, 12));
			one_vram_buffer_horz_repeat('d', 1, NTADR_A(4, 13));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 16));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 17));
		}		
		else if (settingvalue == 2) {
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 8));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 9));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 12));
			one_vram_buffer_horz_repeat(' ', 1, NTADR_A(4, 13));
			one_vram_buffer_horz_repeat('c', 1, NTADR_A(4, 16));
			one_vram_buffer_horz_repeat('d', 1, NTADR_A(4, 17));
		}		

		if (pad_new[0] & PAD_RIGHT || pad_new[0] & PAD_DOWN) {
			if (settingvalue == 2) { settingvalue = 0; }
			else settingvalue++;
		}

		if (pad_new[0] & PAD_LEFT || pad_new[0] & PAD_UP) {
			if (settingvalue == 0) { settingvalue = 2; }
			else settingvalue--;
		}


		if (pad_new[0] & PAD_B) {
			tmp3--;			
			state_menu();
			return;
		}

	}
}





void state_menu() {
	ppu_off();
	pal_bright(0);
    pal_bg((char *)splashMenu);

	mmc3_set_8kb_chr(12);

	set_scroll_x(0);
    set_scroll_y(0);

	mmc3_set_prg_bank_1(0);

	switch (kandotemp){
		case 0x00:	music_play(song_menu_theme); break;
		case 0x01:	break;
	}


	has_practice_point = 0;
	#include "../defines/mainmenu_charmap.h"
	// Enable SRAM write
	POKE(0xA001, 0x80);

	// Get it? it spells DASH
	if (SRAM_VALIDATE[0] != 0x0D
	 || SRAM_VALIDATE[1] != 0x0A
	 || SRAM_VALIDATE[2] != 0x05
	 || SRAM_VALIDATE[3] != 0x06) {
		// set the validation header and then reset coin counts
		SRAM_VALIDATE[0] = 0x0d;
		SRAM_VALIDATE[1] = 0x0a;
		SRAM_VALIDATE[2] = 0x05;
		SRAM_VALIDATE[3] = 0x06;
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
	}

	kandotemp = 1;
	invisible = 0;
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
	pal_fade_to(0,4);
		if (menuselection == 0) {
			one_vram_buffer_horz_repeat('a', 1, NTADR_A(15, 11));
			one_vram_buffer_horz_repeat('b', 1, NTADR_A(16, 11));
		}
		else if (menuselection == 1) {
			one_vram_buffer_horz_repeat('a', 1, NTADR_A(21, 11));
			one_vram_buffer_horz_repeat('b', 1, NTADR_A(22, 11));
		}
		else if (menuselection == 2) {
			one_vram_buffer_horz_repeat('a', 1, NTADR_A(12, 17));
			one_vram_buffer_horz_repeat('b', 1, NTADR_A(13, 17));
		}
		else if (menuselection == 3) {
			one_vram_buffer_horz_repeat('a', 1, NTADR_A(18, 17));
			one_vram_buffer_horz_repeat('b', 1, NTADR_A(19, 17));
		}
		else if (menuselection == 4) {
			one_vram_buffer_horz_repeat('a', 1, NTADR_A(9, 11));
			one_vram_buffer_horz_repeat('b', 1, NTADR_A(10, 11));
		}
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
            }
            if (pad_new[0] & PAD_LEFT) {
                if (menuselection == 0) menuselection = 4;
                else menuselection--;
                tmp3++;
            }

            if (tmp3) {    // menu selection incremented
                tmp4 = menuselection; ++tmp4;
				tmp5 = loNTAddrTable[tmp4]|(hiNTAddrTable[tmp4]<<8);
                one_vram_buffer_horz_repeat('a', 1, tmp5);
                one_vram_buffer_horz_repeat('b', 1, (((tmp5&0xFF)+1)&0xFF)|(tmp5&0xFF00));	// tells cc65 to not check overflow

                tmp4 += tmp3;   // Get the old index
				tmp5 = loNTAddrTable[tmp4]|(hiNTAddrTable[tmp4]<<8);
                one_vram_buffer_horz_repeat(' ', 1, tmp5);
                one_vram_buffer_horz_repeat(' ', 1, (((tmp5&0xFF)+1)&0xFF)|(tmp5&0xFF00));	// tells cc65 to not check overflow
            }



	}		
	switch (menuselection) {
		case 0x00: levelselection(); return; break;
		case 0x01: settingvalue = 0; settings(); return; break;
		case 0x02: state_menu(); return; break;
		case 0x03: state_menu(); return; break;
		case 0x04: state_menu(); return; break;
			
	};
  
}



#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
