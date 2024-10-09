
CODE_BANK_PUSH("LVL_BANK_00")
void lvl_done_update();
void mouse_and_cursor();

const uint8_t difficulty_pal_A[] ={
	0x21,	// easy
	0x2A,	// normal
	0x28,	// hard
	0x16,	// harder
	0x24,	// insane
	0x16,	// demon
	0x13,	// danger
};

const uint8_t difficulty_pal_B[] ={
	0x06,	// easy
	0x30,	// normal
	0x30,	// hard
	0x30,	// harder
	0x06,	// insane
	0x30,	// demon
	0x21,	// danger
};

void refreshmenu();
void refreshmenu_part2();
void code_checker();
void set_fun_settings();
void checkcointimer(){
	if (tmp1 == 1){
		sfx_play(sfx_coin,0);
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

	pal_bright(0);
	ppu_wait_nmi();
	ppu_off();
	delay_spr_0 = 0x20;
	gamemode = 0;
	kandodebugmode = 0;
	kandodebug2 = 0;
	cube_data[0] = 0;
	cube_data[1] = 0;

	current_state = 0;

	pal_bg(paletteMenu);
	pal_col(0x0A,0x2A);
	pal_col(0x0B,0x21);
	pal_set_update();
    //pal_spr(paletteMenu);
	pal_spr(paletteDefaultSP);
	mmc3_set_8kb_chr(LEVELCOMPLETEBANK);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
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
	// no longer required
    //vram_adr(0x2be1);
	//vram_fill(0xff, 0x6);

    vram_adr(NAMETABLE_D);
    vram_unrle(leveldone);

	#include "defines/endlevel_charmap.h"
	//multi_vram_buffer_horz((const char*)menutext3,sizeof(menutext3)-1,NTADR_C(6, 16));
	//multi_vram_buffer_horz((const char*)menutext4,sizeof(menutext4)-1,NTADR_C(8, 18));
	//multi_vram_buffer_horz((const char*)attemptstext,sizeof(attemptstext)-1,NTADR_C(7, 19));
	
	tmp1 = 0;
	tmpptr1 = NULL;

	display_attempt_counter(0xD0, NTADR_C(25, 13));	// Same bank as this
	
	if (!has_practice_point) {
		LEVELCOMPLETE[level] = 1;
		
		if (coins & COIN_1) coin1_obtained[level] = 1;
		if (coins & COIN_2) coin2_obtained[level] = 1;
		if (coins & COIN_3) coin3_obtained[level] = 1;

		level_completeness_normal[level] = 100;
	} else {
		level_completeness_practice[level] = 100;
	}
	
	has_practice_point = 0;
	
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
	// Set palettes back to natural colors since we aren't fading back in
	pal_bright(4);

    ppu_on_all();



	sfx_play(sfx_level_complete, 0);
	menuselection = 1;
	lvl_done_update();
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
			if (
				(__A__ = fourth_byte(top_scroll) | third_byte(top_scroll),
				__A__ |= high_byte(top_scroll),
				__A__ == 0) && low_byte(top_scroll) == 240) {
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

			tmp2 = 0;
			do {
				// TOTALCOINS = TOTALCOINS + coin1_obtained[tmp2] + coin2_obtained[tmp2] + coin3_obtained[tmp2];
				__A__ = tmp2; __asm__("tay");
				__A__ = TOTALCOINS;
				__asm__("clc \n adc %v, y", coin1_obtained);
				__asm__("clc \n adc %v, y", coin2_obtained);
				__asm__("clc \n adc %v, y", coin3_obtained);
				TOTALCOINS = __A__;
				
				if (LEVELCOMPLETE[tmp2]) TOTALSTARS += stars_list[tmp2];
				tmp2++;
			}
			#ifdef FLAG_ENABLE_TEST_LEVELS
			while (tmp2 < 255);
			#else
			while (tmp2 < LEVEL_COUNT2);
			#endif

			tmp2 = 0;


/*
			do {
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
			} while (++tmp2 <= 10);

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
*/
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
		oam_clear();

			mouse_and_cursor();

			if (mouse.left_press) {
				if (mouse.y >= 0xC5 && mouse.y <= 0xE3) {
					if (mouse.x >= 0x36 && mouse.x <= 0x53) {
						sfx_play(sfx_start_level, 0);
						gameState = 2;
						pal_fade_to_withmusic(4,0);
						memfill(attemptCounter, 0, sizeof(attemptCounter));

						//oam_clear();
						coins = 0;
						return;					
					}
					if (mouse.x >= 0xA6 && mouse.x <= 0xc3) {
						sfx_play(sfx_exit_level, 0);
						music_update();
						gameState = 1;
						menuselection = 0;
						kandowatchesyousleep = 1;
						//oam_clear();
						kandotemp = 0;
						return;
					}
				}
			}

			if (joypad1.press_left) { menuselection ^= 1; lvl_done_update(); }
			if (joypad1.press_right) { menuselection ^= 1; lvl_done_update(); }
			if (joypad1.press_start){
				if (menuselection) {
					
					sfx_play(sfx_exit_level, 0);
					music_update();
					gameState = 1;
					menuselection = 0;
					kandowatchesyousleep = 1;

					//oam_clear();
					kandotemp = 0;
					return;
				} else {
					
					sfx_play(sfx_start_level, 0);
					gameState = 2;
					pal_fade_to_withmusic(4,0);
					memfill(attemptCounter, 0, sizeof(attemptCounter));
					coins = 0;


					//oam_clear();
					return;
				}
			}



		}
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
						
	}
	#undef current_state
	#undef sprite_0_y
	#undef delay_spr_0
	#undef delay_timer
	#undef top_scroll
}





#include "defines/bgm_charmap.h"
const unsigned char TEXT_xlevel1text1[]="STEREO$";
const unsigned char TEXT_xlevel1text2[]="BACK$ON";
const unsigned char TEXT_xlevel1text5[]="BASE$AFTER";
const unsigned char TEXT_xlevel1textC[]="THEORY$OF";
const unsigned char TEXT_xlevel1textD[]="ELECTROMAN";

const unsigned char TEXT_xlevel2text1[]="MADNESS";
const unsigned char TEXT_xlevel2text2[]="TRACK";
const unsigned char TEXT_xlevel2text3[]="POLARGEIST";
const unsigned char TEXT_xlevel2text4[]="DRY$OUT";
const unsigned char TEXT_xlevel2text5[]="BASE";
const unsigned char TEXT_xlevel2text6[]="CANT$LET$GO";
const unsigned char TEXT_xlevel2text7[]="JUMPER";
const unsigned char TEXT_xlevel2text8[]="TIME$MACHINE";
const unsigned char TEXT_xlevel2text9[]="CYCLES";
const unsigned char TEXT_xlevel2textA[]="XSTEP";
const unsigned char TEXT_xlevel2textB[]="CLUTTERFUNK";
const unsigned char TEXT_xlevel2textC[]="EVERYTHING";
const unsigned char TEXT_xlevel2textD[]="ADVENTURES";
const unsigned char TEXT_xlevel2textE[]="DECODE";
const unsigned char TEXT_2textpractice[]="PRACTICE";
const unsigned char TEXT_2textmenu[]="MENU";
const unsigned char TEXT_2texteveryend[]="EVERY$END";

const unsigned char TEXT_sfxtext0[]="DEATH";
const unsigned char TEXT_sfxtext1[]="CLICK";
const unsigned char TEXT_sfxtext2[]="LEVEL$COMPLETE";
const unsigned char TEXT_sfxtext3[]="COIN";
const unsigned char TEXT_sfxtext4[]="CHEST$OPEN";
const unsigned char TEXT_sfxtext5[]="ORBS";
const unsigned char TEXT_sfxtext6[]="DIAMONDS";
const unsigned char TEXT_sfxtext7[]="EXIT$LEVEL";
const unsigned char TEXT_sfxtext8[]="START$LEVEL";
const unsigned char TEXT_sfxtext9[]="INVALID";
const unsigned char TEXT_sfxtextA[]="ACHIEVEMENT$GET";

const unsigned char* const sfxtexts[] = {
	TEXT_sfxtext0, TEXT_sfxtext1, TEXT_sfxtext2, TEXT_sfxtext3, TEXT_sfxtext4, TEXT_sfxtext5, TEXT_sfxtext6, TEXT_sfxtext7, TEXT_sfxtext8, TEXT_sfxtext9, TEXT_sfxtextA
};

const unsigned char sfxtexts_size[] = {
	sizeof(TEXT_sfxtext0) - 1,
	sizeof(TEXT_sfxtext1) - 1,
	sizeof(TEXT_sfxtext2) - 1,
	sizeof(TEXT_sfxtext3) - 1,
	sizeof(TEXT_sfxtext4) - 1,
	sizeof(TEXT_sfxtext5) - 1,
	sizeof(TEXT_sfxtext6) - 1,
	sizeof(TEXT_sfxtext7) - 1,
	sizeof(TEXT_sfxtext8) - 1,
	sizeof(TEXT_sfxtext9) - 1,
	sizeof(TEXT_sfxtextA) - 1
};


const unsigned char* const xbgmtexts1[] = {
	0, 0, 0, 0, 0, 0, 0, TEXT_xlevel1textD, TEXT_xlevel1text1, TEXT_xlevel1text2, TEXT_xlevel1text5, 0, 0, 0, 0, TEXT_xlevel1textC
};

const unsigned char* const xbgmtexts2[] = {
	TEXT_xlevel2text8, TEXT_xlevel2textB, TEXT_xlevel2textE, TEXT_2textpractice, TEXT_2textmenu, TEXT_xlevel2text3, TEXT_xlevel2text7, TEXT_xlevel2textD, TEXT_xlevel2text1, TEXT_xlevel2text2, TEXT_xlevel2text5, TEXT_xlevel2text9, TEXT_xlevel2text4, TEXT_xlevel2text6, TEXT_xlevel2textA, TEXT_xlevel2textC, 
};

const unsigned char xbgmtext2_size[] = {
	sizeof(TEXT_xlevel2text8) - 1,
	sizeof(TEXT_xlevel2textB) - 1,
	sizeof(TEXT_xlevel2textE) - 1,
	sizeof(TEXT_2textpractice) - 1,
	sizeof(TEXT_2textmenu) - 1,	
	sizeof(TEXT_xlevel2text3) - 1,
	sizeof(TEXT_xlevel2text7) - 1,	
	sizeof(TEXT_xlevel2textD) - 1,	
	sizeof(TEXT_xlevel2text1) - 1,	
	sizeof(TEXT_xlevel2text2) - 1,	
	sizeof(TEXT_xlevel2text5) - 1,	
	sizeof(TEXT_xlevel2text9) - 1,	
	sizeof(TEXT_xlevel2text4) - 1,	
	sizeof(TEXT_xlevel2text6) - 1,	
	sizeof(TEXT_xlevel2textA) - 1,	
	sizeof(TEXT_xlevel2textC) - 1,	
};
const unsigned char xbgmtext1_size[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(TEXT_xlevel1textD) - 1,	
	sizeof(TEXT_xlevel1text1) - 1,	
	sizeof(TEXT_xlevel1text2) - 1,	
	sizeof(TEXT_xlevel1text5) - 1,	
	0,
	0,
	0,
	0,
	sizeof(TEXT_xlevel1textC) - 1,	
};




const char TEXT_debug_mode[] = "DEBUG MODE ENABLED";

//#include "defines/bgm_charmap.h"
void bgmtest() {
	song = 0;
	#define sfx tmp4
	sfx = 0;
	settingvalue = 0;
  	famistudio_music_stop();
  	music_update();
	kandotemp=0;
	pal_fade_to_withmusic(4,0);
	mmc3_disable_irq();
	ppu_off();
	pal_bg(paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(bgmtestscreen);   	
	ppu_on_all();
	pal_fade_to_withmusic(0,4);
	while (1) {
		
		ppu_wait_nmi();
		music_update();
		oam_clear();

		mouse_and_cursor();
		 // read the first controller
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
		if (mouse.left_press) {
			if ((mouse.x >= 0x63 && mouse.x <= 0x8C)) {
				if (mouse.y >= 0x34 && mouse.y <= 0x3A) {		
					settingvalue = 0;
				}
				else if ((mouse.y >= 0x6C && mouse.y <= 0x73)) {		
					settingvalue = 1;
				}
			}
			if ((mouse.x >= 0x2E && mouse.x <= 0xCC) && (mouse.y >= 0xAC && mouse.y <= 0xB3)) {		
				if (settingvalue == 1) { sfx_play(sfx, 0); }
				else {
					music_play(song);
				}
			}
			if ((mouse.x >= 0x56 && mouse.x <= 0xA5) && (mouse.y >= 0x24 && mouse.y <= 0x2B)) {		
				code_checker();
				if (gameState == 0xF0) return;
			}
			if ((mouse.y >= 0x4E && mouse.y <= 0x5C)) {
				if ((mouse.x >= 0x24 && mouse.x <= 0x2C)) {		
					if (song == 0) {song = song_max - 1;} else song--; settingvalue = 0;
				}
				else if ((mouse.x >= 0xCC && mouse.x <= 0xD4)) {		
					song++; if (song == song_max) {song = 0;} settingvalue = 0;
				}
			}
			if ((mouse.y >= 0x86 && mouse.y <= 0x93)) {

				if ((mouse.x >= 0x24 && mouse.x <= 0x2C)) {		
					if (sfx == 0) {sfx = sfx_max - 1;} else sfx--; settingvalue = 1;
				}
				else if ((mouse.x >= 0xCC && mouse.x <= 0xD4)) {		
					sfx++; if (sfx == sfx_max) {sfx= 0;} settingvalue = 1;
				}
			}
			if ((mouse.x >= 0x35 && mouse.x <= 0xC4)) {
				if (mouse.y >= 0xBC && mouse.y <= 0xC4) {		
					tmp3--;			
					one_vram_buffer(' ', NTADR_A(11, 7));
					one_vram_buffer(' ', NTADR_A(11, 14));
					kandotemp = 1;
					gameState = 1;
					return;
				}
				else if (mouse.y >= 0x3D && mouse.y <= 0x64) {
					music_play(song);
				}
				else if (mouse.y >= 0x75 && mouse.y <= 0x9C) {
					sfx_play(sfx, 0);
				}
			}
		}			
	__A__ = idx16_load_hi_NOC(xbgmtexts1, song);
	if (__A__) draw_padded_text(xbgmtexts1[song & 0x7F], xbgmtext1_size[song], 17, NTADR_A(7, 10));
	else one_vram_buffer_horz_repeat('$', 17, NTADR_A(7, 10));
	__A__ = idx16_load_hi_NOC(xbgmtexts2, song);
	if (__A__) draw_padded_text(xbgmtexts2[song & 0x7F], xbgmtext2_size[song], 17, NTADR_A(7, 11));
	else one_vram_buffer_horz_repeat('$', 17, NTADR_A(7, 11));
	
	draw_padded_text(sfxtexts[sfx & 0x7F], sfxtexts_size[sfx], 17, NTADR_A(7, 18));

	
		if (settingvalue == 0) {
			one_vram_buffer('c', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			if (joypad1.press_right) { song++; if (song == song_max) {song = 0;} }
			if (joypad1.press_left) { if (song == 0) {song = song_max - 1;} else song--; }
			if (joypad1.press_a) music_play(song);
		}		
		else if (settingvalue == 1) {
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer('c', NTADR_A(11, 14));
			if (joypad1.press_right) { sfx++; if (sfx == sfx_max) {sfx= 0;} };
			if (joypad1.press_left) { if (sfx == 0) {sfx = sfx_max - 1;} else sfx--; }
			if (joypad1.press_a) sfx_play(sfx, 0);
		}

		if (joypad1.press_down) settingvalue ^= 1;
		if (joypad1.press_up) settingvalue ^= 1;
		
		if (joypad1.press_select) famistudio_music_stop();
		if (joypad1.press_b) {
			tmp3--;			
			one_vram_buffer(' ', NTADR_A(11, 7));
			one_vram_buffer(' ', NTADR_A(11, 14));
			kandotemp = 1;
			gameState = 1;
			return;
		}

				
		
		// sound test codes
		if (joypad1.press_start) {
			code_checker();
			if (gameState == 0xF0) return;
		}
	}
	#undef sfx
}


void gameboy_check() {
		if (gameboy_mode == 0) color_emphasis(COL_EMP_NORMAL);
		else if (gameboy_mode == 1) color_emphasis(COL_EMP_GREY);
		else if (gameboy_mode == 2) { color_emphasis(COL_EMP_GREYRED); }
		else if (gameboy_mode == 3) { color_emphasis(COL_EMP_GREYGREEN); }
		else if (gameboy_mode == 4) { color_emphasis(COL_EMP_GREYBLUE); }
		else if (gameboy_mode == 5) { color_emphasis(COL_EMP_GREYYELLOW); }
		else if (gameboy_mode == 6) { color_emphasis(COL_EMP_GREYPURPLE); }
		else if (gameboy_mode == 7) { color_emphasis(COL_EMP_GREYCYAN); }
		else if (gameboy_mode == 8) { color_emphasis(COL_EMP_GREYDARK); }
}



void colorinc() {
	if (idx8_inc(icon_colors, settingvalue) & 0x30) {
		if ((uint8_t)(icon_colors[settingvalue] & 0x0F) >= 0x0D)
			idx8_store(icon_colors, settingvalue, (icon_colors[settingvalue] + 0x10) & 0x30);
	} else {
		if (((icon_colors[settingvalue] - 0x0D) & 0xFE) == 0)	// if color == 0x0D or 0x0E
			icon_colors[settingvalue] = 0x0F;
	}	
}

void colordec() {
	if (idx8_dec(icon_colors, settingvalue) & 0x30) {
		if ((uint8_t)(icon_colors[settingvalue] & 0x0F) >= 0x0D)
			idx8_store(icon_colors, settingvalue, (icon_colors[settingvalue] & 0x30) | 0x0C);
	} else {
		if (((icon_colors[settingvalue] - 0x0D) & 0xFE) == 0)	// if color == 0x0D or 0x0E
			icon_colors[settingvalue] = 0x0C;
	}
}	


#include "defines/mainmenu_charmap.h"


const unsigned char gameboytext1[]="  GREY";
const unsigned char gameboytext2[]="   RED";
const unsigned char gameboytext3[]=" GREEN";
const unsigned char gameboytext4[]="  BLUE";
const unsigned char gameboytext5[]="YELLOW";
const unsigned char gameboytext6[]="PURPLE";
const unsigned char gameboytext7[]="  CYAN";
const unsigned char gameboytext8[]="  DARK";

const unsigned char* const gameboytexts[] = {
	0, gameboytext1, gameboytext2, gameboytext3, gameboytext4, gameboytext5, gameboytext6, gameboytext7, gameboytext8
};

const unsigned char gameboy_text_size[] = {
	0,
	sizeof(gameboytext1) - 1,
	sizeof(gameboytext2) - 1,
	sizeof(gameboytext3) - 1,
	sizeof(gameboytext4) - 1,
	sizeof(gameboytext5) - 1,
	sizeof(gameboytext6) - 1,
	sizeof(gameboytext7) - 1,
	sizeof(gameboytext8) - 1
};



void funsettings() {
	settingvalue = 0; 
	pal_fade_to_withmusic(4,0);
	ppu_off();
	pal_bg(paletteMenu);
	vram_adr(NAMETABLE_A);
	vram_unrle(funsettingscreen);   
	//kandotemp4 = 0;
	mmc3_set_2kb_chr_bank_0(0xFF);
	mmc3_set_2kb_chr_bank_1(MOUSEBANK);
	ppu_on_all();
	one_vram_buffer('c', NTADR_A(4, 7));	// settingvalue is set to 0 by default	
	pal_fade_to_withmusic(0,4);
	while (1) {
		ppu_wait_nmi();
		music_update();
		oam_clear();

		mouse_and_cursor();
		 // read the first controller
		if (mouse.left_press) {
			if (mouse.x >= 0x2D && mouse.x <= 0xDD) {
				if (mouse.y >= 0x34 && mouse.y <= 0x3C) {
					settingvalue = 0; set_fun_settings();
				}
				else if (mouse.y >= 0x44 && mouse.y <= 0x4C) {
					settingvalue = 1; set_fun_settings();
				}
				else if (mouse.y >= 0x54 && mouse.y <= 0x5C) {
					settingvalue = 2; set_fun_settings();
				}
				else if (mouse.y >= 0x64 && mouse.y <= 0x6C) {
					settingvalue = 3; set_fun_settings();
				}
				else if (mouse.y >= 0x74 && mouse.y <= 0x7C) {
					settingvalue = 4; set_fun_settings();
				}
				else if (mouse.y >= 0x84 && mouse.y <= 0x8C) {
					settingvalue = 5; set_fun_settings();
				}
				else if (mouse.y >= 0x94 && mouse.y <= 0x9C) {
					settingvalue = 6; set_fun_settings();
				}
				else if (mouse.y >= 0xA4 && mouse.y <= 0xAC) {
					settingvalue = 7; set_fun_settings();
				}

			}
			if ((mouse.x >= 0x1D && mouse.x <= 0xDD) && (mouse.y >= 0xBC && mouse.y <= 0xC4)) {		
				gameState = last_gameState;
				return;
			}

		}	
		if (invisible) 	one_vram_buffer('g', NTADR_A(26, 7));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 7));	// this is auto optimized by cc65

		if ((options & platformer)) 	one_vram_buffer('g', NTADR_A(26, 9));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 9));	// this is auto optimized by cc65

		if (retro_mode) 	one_vram_buffer('g', NTADR_A(26, 11));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 11));	// this is auto optimized by cc65

		if (discomode) 	one_vram_buffer('g', NTADR_A(26, 13));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 13));	// this is auto optimized by cc65
		
		if (invisblocks) 	one_vram_buffer('g', NTADR_A(26, 15));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 15));	// this is auto optimized by cc65
		
		if (cam_seesaw) 	one_vram_buffer('g', NTADR_A(26, 17));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 17));	// this is auto optimized by cc65

		if (cursedmusic & 0x40) 	one_vram_buffer('g', NTADR_A(26, 21));	// believe it or not, 
		else 	one_vram_buffer('f', NTADR_A(26, 21));	// this is auto optimized by cc65
		


//		if (cursedmusic) 	one_vram_buffer('g', NTADR_A(26, 21));	// believe it or not, 
//		else 	one_vram_buffer('f', NTADR_A(26, 21));	// this is auto optimized by cc65
		
		__A__ = idx16_load_hi_NOC(gameboytexts, gameboy_mode);
		if (__A__) { draw_padded_text(gameboytexts[gameboy_mode & 0x7F], gameboy_text_size[gameboy_mode], 8, NTADR_A(19, 19)); 	one_vram_buffer('g', NTADR_A(26, 19));	}// believe it or not, 
		else { one_vram_buffer_horz_repeat('$', 8, NTADR_A(19, 19)); one_vram_buffer('f', NTADR_A(26, 19)); }



		tmp1 = settingvalue;

		if (joypad1.press & (PAD_RIGHT | PAD_DOWN)) {
			if (settingvalue == 7) { settingvalue = 0; }
			else { settingvalue++;  }
		}

		if (joypad1.press & (PAD_LEFT | PAD_UP)) {
			if (settingvalue == 0) { settingvalue = 7; }
			else { settingvalue--;  }
		}

		if (tmp1 != settingvalue) {
			// NTADR_A = (NAMETABLE_A|(((y)<<5)|(x)))
			// (tmp1 * 2) << 5 = tmp1<<6 = (tmp1<<8)>>2
			one_vram_buffer(' ', NTADR_A(4, 7)+((tmp1<<8)>>2));
			one_vram_buffer('c', NTADR_A(4, 7)+((settingvalue<<8)>>2));
		}

		one_vram_buffer('X'-0x1B, NTADR_A(26, 13));
		if (discomode & 0x02) { one_vram_buffer('2' - 0x20, NTADR_A(25, 13)); }
		else if (discomode & 0x04) { one_vram_buffer('3' - 0x20, NTADR_A(25, 13));}
		else if (discomode & 0x08) { one_vram_buffer('4' - 0x20, NTADR_A(25, 13));}
		else if (discomode & 0x10) { one_vram_buffer('5' - 0x20, NTADR_A(25, 13));}
		else if (discomode & 0x01) { one_vram_buffer('1' - 0x20, NTADR_A(25, 13));}
		else { one_vram_buffer(' '-0x01, NTADR_A(25, 13)); one_vram_buffer(0x0F, NTADR_A(26, 13)); }

		if (joypad1.press & (PAD_START | PAD_A)) {
			set_fun_settings();
		}
			
		if (joypad1.press_b) {
			gameState = last_gameState;
			return;
		}

		crossPRGBankJump0(gameboy_check);

		if (gameboy_mode) kandotemp4 = 1;
		kandoframecnt++;
		if (kandoframecnt & 1 && mouse_timer) mouse_timer--;	
						
	}
}

void set_fun_settings() {
	switch (settingvalue) {
		case 0x00: invisible ^= 1; break;
		case 0x01: options ^= platformer; break;
		case 0x02: retro_mode ^= 1; break;
		case 0x03: 
			if (discomode & 0x10) discomode = 0;
			else {
				discomode = discomode << 1;
				if (discomode == 0) ++discomode;
			}
			
			break;
		case 0x04: invisblocks ^= 1; break;
		case 0x05: cam_seesaw = (cam_seesaw > 0 ? 0 : 1); break;
		case 0x06: gameboy_mode = (gameboy_mode == 8 ? 0 : gameboy_mode + 1); break;
		case 0x07: cursedmusic ^= 0x40; break;
	};
}	


#define sfx tmp4
void code_checker() {
	last_gameState = gameState;
	sfx_play(sfx_achievement_get, 0);
	tmp3 = 1;

	// bgm 9 & sfx 2
	if (song == 0x9 && sfx == 0x2 && code_count == 0) {
		code_count++;
		tmp3--;
	}
	
	else if (song == 1 && sfx == 7 && code_count == 1) {
		gameState = 0xF0; // fun settings gamestate
		tmp3--;
	}		
	else code_count = 0;
	
/*   debug code disabled
	if (song == 0xB && sfx == 0x7) {
		multi_vram_buffer_horz(TEXT_debug_mode, sizeof(TEXT_debug_mode)-1, NTADR_A(7,26));
		options |= debugtoggle;
		tmp3--;
	}
*/

	// this is quite literally the greatest hack ever
	// since sfx doesn't update until the next frame i can just
	// overwrite the success sfx with the invalid one
	if (tmp3) sfx_play(sfx_invalid, 0);	
}

#undef sfx






const unsigned char* const leveltexts[] = {
  level1text, level2text, NULL, NULL, level5text, NULL, NULL, NULL, NULL, NULL, NULL, levelCtext, levelDtext, NULL, NULL, NULL, NULL, NULL, NULL, NULL, level15text
};
const unsigned char* const leveltexts2[] = {
  level1text2, level2text2, level3text2, level4text2, level5text2, level6text2, level7text2, level8text2, level9text2, levelAtext2, levelBtext2, levelCtext2, levelDtext2, levelEtext2, levelFtext2, level10text2, level11text2, level12text2, level13text2, level14text2, level15text2
};


const unsigned char level_text_size[] = {
    sizeof(level1text) - 1,
	sizeof(level2text) - 1,
	0,
	0,
	sizeof(level5text) - 1,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(levelCtext) - 1,
	sizeof(levelDtext) - 1,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(level15text) - 1,
};
const unsigned char level_text_size2[] = {
    sizeof(level1text2) - 1,
	sizeof(level2text2) - 1,
	sizeof(level3text2) - 1,
	sizeof(level4text2) - 1,
	sizeof(level5text2) - 1,
	sizeof(level6text2) - 1,
	sizeof(level7text2) - 1,
	sizeof(level8text2) - 1,
	sizeof(level9text2) - 1,
	sizeof(levelAtext2) - 1,
	sizeof(levelBtext2) - 1,
	sizeof(levelCtext2) - 1,
	sizeof(levelDtext2) - 1,
	sizeof(levelEtext2) - 1,
	sizeof(levelFtext2) - 1,
	sizeof(level10text2) - 1,
	sizeof(level11text2) - 1,
	sizeof(level12text2) - 1,
	sizeof(level13text2) - 1,
	sizeof(level14text2) - 1,
	sizeof(level15text2) - 1,
};

const char coin_counter[][3] = {
  "___",
  "^__",
  "_^_",
  "^^_",
  "__^",
  "^_^",
  "_^^",
  "^^^",
};


#include "defines/color1_charmap.h"

/*
	Refreshes level name & number
*/
void refreshmenu(void) {
	tmp5 = ((level&1)<<10);
	set_scroll_x(((level-tmp4)&1)<<8);
	
	__A__ = idx16_load_hi_NOC(leveltexts, level);
	if (__A__) draw_padded_text(leveltexts[level & 0x7F], level_text_size[level], 17, NTADR_A(8, 10)+tmp5);
	else one_vram_buffer_horz_repeat(' ', 17, NTADR_A(8, 10)+tmp5);
	// if (leveltexts2[level]) // always true
	draw_padded_text(leveltexts2[level & 0x7F], level_text_size2[level], 17, NTADR_A(8, 11)+tmp5);

	if (LEVELCOMPLETE[level]) { one_vram_buffer('y', NTADR_A(7, 9)+tmp5);
	one_vram_buffer('z', NTADR_A(8, 9)+tmp5); }
	else one_vram_buffer_horz_repeat(' ', 2, NTADR_A(7, 9)+tmp5);

	{	// write the difficulty
		tmp1 = difficulty_list[level];
		pal_col(0x0a, difficulty_pal_A[tmp1]);
		pal_col(0x0b, difficulty_pal_B[tmp1]);
		pal_set_update();
		
		tmp1 = (tmp1 << 1) + 'a';
		one_vram_buffer(tmp1, NTADR_A(7, 10)+tmp5);
		one_vram_buffer(++tmp1, NTADR_A(8, 10)+tmp5);
		one_vram_buffer((tmp1 += ('c'-'b')), NTADR_A(7, 11)+tmp5);
		one_vram_buffer(++tmp1, NTADR_A(8, 11)+tmp5);
		

	}
	// Star count stuff
		printDecimal(stars_list[level], 2, '0', ' ', NTADR_A(22, 9)+tmp5);

	// level number
	#ifdef FLAG_ENABLE_TEST_LEVELS
		printDecimal(level, 3, '0', ' ', NTADR_A(29, 2));
		printDecimal(level, 3, '0', ' ', NTADR_B(29, 2));
	#endif
};

void refreshmenu_part2(void) {
	
	// Normal level completeness stuff
		printDecimal(level_completeness_normal[level], 3, '0', ' ', NTADR_A(14, 16)+tmp5);

	// Practice level completeness stuff
		printDecimal(level_completeness_practice[level], 3, '0', ' ', NTADR_A(14, 19)+tmp5);

	//palette stuff
		tmp3 = level % 9;
		pal_col(0,colors_list[tmp3]);
		pal_col(0xE,colors_list[tmp3]);
		pal_set_update();
	//coin stuff
		coins = 0;


	// then in the function...
	// combine all three into a single number from 0 - 7 to represent which coins have been grabbed
		tmp7 = byte((byte(coin3_obtained[level] << 1) | coin2_obtained[level]) << 1) | coin1_obtained[level];
		tmp7 = byte(tmp7<<1) + tmp7;
	// actually draw the coins
		multi_vram_buffer_horz((const char * const)coin_counter+tmp7, 3, NTADR_A(22, 12)+tmp5);

}

#include "defines/endlevel_charmap.h"
void lvl_done_update() {
	if (menuselection) {
		one_vram_buffer(0xFF, NTADR_C(8,23));
		one_vram_buffer(0xFF, NTADR_C(9,23));
		one_vram_buffer(0x94, NTADR_C(22,23));
		one_vram_buffer(0x95, NTADR_C(23,23));
	} else {
		one_vram_buffer(0x94, NTADR_C(8,23));
		one_vram_buffer(0x95, NTADR_C(9,23));
		one_vram_buffer(0xFF, NTADR_C(22,23));
		one_vram_buffer(0xFF, NTADR_C(23,23));
	}
}	

CODE_BANK_POP()

