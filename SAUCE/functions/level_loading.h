// prototype
void init_sprites(void);
#include "../defines/bg_charmap.h"
const unsigned char attempttext[]="PQQRSTQ"; //ATTEMPT
const unsigned char whartxt[]="wxyz";	// WHAR
void setdefaultoptions();
/* 
	Reset run-length decoder back to zero
	Implemented in asm
*/
void __fastcall__ init_rld(unsigned char level);

/* 
	This should explain itself
	Requires the correct PRG1 bank to be set
	Implemented in asm
*/
void __fastcall__ unrle_next_column(void);

void __fastcall__ copy_column_to_collmap(void);

/* 
	Scrolling to the right, draw metatiles as we go
	Implemented in asm	
*/
void __fastcall__ draw_screen_R(void);
void __fastcall__ draw_screen_R_frame0(void);
void __fastcall__ draw_screen_R_frame1(void);
void __fastcall__ draw_screen_R_frame2(void);

/*
	Load ground tiles into collision map
	Implemented in asm
*/
void __fastcall__ load_ground(unsigned char id);

void increase_parallax_scroll_column() {
	// The parallax is a 6 x 9 tile background, and when it repeats
	// horizontally, we offset the start of the next column by 3
	// to stagger the repeat
	parallax_scroll_column++;
	if (parallax_scroll_column >= 6) {
		parallax_scroll_column = 0;
		parallax_scroll_column_start += 3;
		if (parallax_scroll_column_start >= 9) {
			parallax_scroll_column_start = 0;
		}
	}
}
extern unsigned char scroll_count;
void unrle_first_screen(void){ // run-length decode the first screen of a level
	// register unsigned char i;
	#define i (*((unsigned char *)&ii))
	register unsigned long ii;
	mmc3_set_prg_bank_1(GET_BANK(init_sprites));
	init_sprites();

	cube_data[0] = 0;
	cube_data[1] = 0;

	mmc3_set_prg_bank_1(level_data_bank);

	// If practice mode has set a scroll position to restart from, run the unrle function
	// over and over until it catches up
	if (has_practice_point) {
		parallax_scroll_column = 0;
		parallax_scroll_column_start = 0;
		scroll_count = 0;
		scroll_x = practice_scroll_x - 256;
		scroll_y = practice_scroll_y;
		// for (i = practice_scroll_x >> 24, i++; i > 0; i--) {
		// 	for (ii = practice_scroll_x >> 8, ii++; ii > 0; ii--) {
		// 		unrle_next_column();
		// 		increase_parallax_scroll_column();
		// 		scroll_count = !scroll_count;
		// 	}
		// }
		// for (i = byte(low_byte(practice_scroll_x) >> 4), i++; i > 0; i--) {
		// 	unrle_next_column(); copy_column_to_collmap();
		// 	increase_parallax_scroll_column();
		// 	scroll_count = !scroll_count;
		// }
		for (ii = (practice_scroll_x >> 4), ++ii; ii > 0; ii--) {
			unrle_next_column(); copy_column_to_collmap();
			increase_parallax_scroll_column();
			scroll_count = !scroll_count;
		}
		player_x[0] = practice_player_x[0];
		player_x[1] = practice_player_x[1];
		player_y[0] = practice_player_y[0];
		player_y[1] = practice_player_y[1];
		long_temp_x = high_byte(practice_player_x[0]);
		gamemode = practice_player_gamemode;
		mini = practice_mini;
		dual = practice_dual;
		speed = practice_speed;
		player_vel_x[0] = practice_player_vel_x[0];
		player_vel_x[1] = practice_player_vel_x[1];
		player_vel_y[0] = practice_player_vel_y[0];
		player_vel_y[1] = practice_player_vel_y[1];
		player_gravity[0] = practice_player_gravity[0];
		player_gravity[1] = practice_player_gravity[1];
		cube_rotate[0] = practice_cube_rotate[0];
		cube_rotate[1] = practice_cube_rotate[1];

		__A__ = currplayer<<1;
		__asm__("tay");
		#define quick_ld(to, from) __asm__("lda %v,y\n sta %v\n lda %v+1,y\n sta %v+1", from, to, from, to)
		
		quick_ld(currplayer_x, player_x);
		quick_ld(currplayer_y, player_y);
		quick_ld(currplayer_vel_x, player_vel_x);
		quick_ld(currplayer_vel_y, player_vel_y);

		#undef quick_ld
		currplayer_gravity = player_gravity[currplayer];
		
	//	memcpy(famistudio_state, practice_famistudio_state, sizeof(practice_famistudio_state));
	} else {
		// To get the draw screen R to start in the left nametable, scroll must be negative.
		low_word(scroll_x) = LSW(-256); high_word(scroll_x) = MSW(-256);
	}

	// Draw the nametable starting from where the scroll is set
	i = 0;
    do {
		draw_screen_R();
		flush_vram_update2();
		++scroll_x;
		i++;
	} while (i != 0);

	set_scroll_x(scroll_x);
	set_scroll_y(scroll_y);
	if (!has_practice_point) {
		multi_vram_buffer_horz((const char*)attempttext,sizeof(attempttext)-1,NTADR_C(7, 15));
		
		TOTALCOINSONES = 0;
		TOTALCOINSTENS = 0;
		TOTALATTEMPTSHUNDREDS = 0;		////attempts stuff here and below
		TOTALATTEMPTSTHOUSANDS = 0;
		
		TOTALCOINSTEMP = attempts;
		
		while (TOTALCOINSTEMP > 9) {
			TOTALCOINSTENS++;
			TOTALCOINSTEMP = TOTALCOINSTEMP - 10;
			if (TOTALCOINSTENS == 10) {
				TOTALCOINSTENS = 0;
				TOTALATTEMPTSHUNDREDS++;
			}
			if (TOTALATTEMPTSHUNDREDS == 10) {
				TOTALATTEMPTSHUNDREDS = 0;
				TOTALATTEMPTSTHOUSANDS++;
			}
		}
		TOTALCOINSONES = TOTALCOINSTEMP;

		if (TOTALATTEMPTSTHOUSANDS >= 10)
			multi_vram_buffer_horz((const char*)whartxt,sizeof(whartxt)-1,NTADR_C(15, 15));

		else {
			if (TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xf5+TOTALATTEMPTSTHOUSANDS, NTADR_C(15,15));
			if (TOTALATTEMPTSHUNDREDS || TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xf5+TOTALATTEMPTSHUNDREDS, NTADR_C(16,15));
			if (TOTALATTEMPTSHUNDREDS || TOTALCOINSTENS || TOTALATTEMPTSTHOUSANDS) one_vram_buffer(0xf5+TOTALCOINSTENS, NTADR_C(17,15));
			one_vram_buffer(0xf5+TOTALCOINSONES, NTADR_C(18,15));		
		}
	}
	#undef i
}
