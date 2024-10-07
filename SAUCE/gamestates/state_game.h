/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
void set_tile_banks();
void __fastcall__ movement(void);
void __fastcall__ movement2(void);
extern uint8_t famistudio_song_speed;
const uint8_t BG_Table[]={
	0x11,
	0x12,
	0x13,
	0x14,
	0x15,
	0x16,
	0x17,
	0x18,
	0x19,
	0x1A,
	0x1B,
	0x1C
};

const uint8_t G_Table[]={
	0x21,
	0x22,
	0x23,
	0x24,
	0x25,
	0x26,
	0x27,
	0x28,
	0x29,
	0x2A,
	0x2B,
	0x2C
};

#define stereo_madness  0
#define back_on_track  1
#define polargeist  2
#define dryout  3
#define base_after_base  4
#define cant_let_go  5
#define jumper  6
#define time_machine  7
#define cycles  8
#define xstep  9
#define clutterfunk  0x0A
#define theory_of_everything  0x0B
#define electroman_adventures  0x0C
#define nightmare  0x0D
#define decode  0x0E
#define luckydraw  0x0F
#define test  0x10
#define test2  0x11
#define test3  0x12
#define test4  0X13


void x_minus_15();
void y_minus_15();
void x_plus_15();
void y_plus_15();
void runthecolls();
void set_player_banks();
void gameboy_check();

void slope_exit_vel() {
	switch (tmp8 & 0x07) {
		case SLOPE_22DEG_DOWN:
		case SLOPE_22DEG_UP:
			tmp5 = currplayer_vel_x >> 2;
			break;
		case SLOPE_45DEG_DOWN:
		case SLOPE_45DEG_UP:
			tmp5 = currplayer_vel_x >> 1;
			break;
		case SLOPE_66DEG_DOWN:
		case SLOPE_66DEG_UP:
			tmp5 = (currplayer_vel_x >> 1); 
			tmp5 = (tmp5 >> 1) + tmp5;	
	}
}

void x_movement_coll() {
	if (slope_type && !slope_frames && gamemode != 6) {
	// we we're on an slope and now we aren't, so push the player upwards a bit
		tmp8 = slope_type;
		slope_exit_vel();
		if (slope_type & 1) {
			if (currplayer_gravity) {
				currplayer_vel_y = tmp5 + 0x200;
			} else {
				currplayer_vel_y = (tmp5 + 0x200)^0xFFFF;
			}
		}
	}
	if (slope_frames) {
		slope_frames -= 1;
	}
	
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	// no L/R collision required, since that is accounted for with the death script
	if (high_byte(currplayer_x) > 0x10) {
		bg_coll_floor_spikes(); // check for spikes at the left of the player (fixes standing on spikes)
		if (bg_coll_R()) {
			if (!(options & platformer)) {idx8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);}
			else {currplayer_vel_x = 0; }
		}
	}	
}

extern unsigned char* PARALLAX_CHR;
unsigned char END_LEVEL_TIMER;




void state_game(){
	if ((level >= decode) || twoplayer) no_parallax = 1;
	else no_parallax = 0;
	coin1_timer = 0;
	coin2_timer = 0;
	coin3_timer = 0;
	animating = 0;
	memfill(trail_sprites_visible, 0, sizeof(trail_sprites_visible));
	orbactive = 0;
	mmc3_disable_irq();
	
	outline_color = 0x30;

	lastgcolortype = 0xFF;
	lastbgcolortype = 0xFF;

	set_tile_banks();
	
	ppu_off();

	pal_bg(paletteDefault);
//	pal_spr(paletteDefaultSP);  //unneeded

	crossPRGBankJump8(load_ground,0);

    
	currplayer = 0;
	controllingplayer = &joypad1;
	current_transition_timer_length = 0;
	reset_level();

	END_LEVEL_TIMER = 0;
	kandoframecnt = 0;

	
	iconbank = (icon<<1) + 38;

	pal_col(0x0A,0x0F);   //palette 2 set to 0x0F for mountains
	pal_col(0x0B,color1);   //palette 2 set to player color

	memfill(player_old_posy, 0, sizeof(player_old_posy));
	
	switch (discomode) {
		default: 
			pal_col(0x1D,color3);
			pal_col(0x1E,color1);
			pal_col(0x1F,color2);
			break;
		case 0x01: discorefreshrate = 0x3F; break;
		case 0x02: discorefreshrate = 0x1F; break;
		case 0x04: discorefreshrate = 0x0F; break;
		case 0x08: discorefreshrate = 0x07; break;
		case 0x10: discorefreshrate = 0x03; break;
		
	};

	pal_set_update();

    while (1) {
		newrand();
		if (kandokidshack2 && !(kandoframecnt & 0x0F)) { icon == MAX_ICONS-1 ? icon = 0 : icon++; 	iconbank = (icon<<1) + 38; }
		pal_col(3,outline_color);
		pal_col(7,outline_color);
		pal_set_update();


		if ((kandoframecnt & 0x1F) == 0x10 ) mmc3_set_2kb_chr_bank_1(DECOTYPE[level] + 2);		//DECO
		else if ((kandoframecnt & 0x1F) == 0x00) mmc3_set_2kb_chr_bank_1(DECOTYPE[level]);		//OR ADDITIONAL SPRITES									//

		if ((options & platformer) && !has_practice_point) {
			
			if (famistudio_song_speed == 0x80) music_play(song);
		}		    

		if (((forced_trails == 2) || !(kandoframecnt & 0x1))) {
			if (!(kandoframecnt & 0x01)) {
				if (old_trail_scroll_y >= scroll_y) {
					tmp6 = calculate_linear_scroll_y(sub_scroll_y_ext(scroll_y, old_trail_scroll_y));
				} else {
					tmp6 = calculate_linear_scroll_y(sub_scroll_y_ext(old_trail_scroll_y, scroll_y));
					tmp6 ^= 0xFFFF; tmp6++;
				}
				tmp3 = 7;
				do {
					tmp5 = player_old_posy[tmp3] + tmp6;
					if (high_byte(tmp5) != 0) low_byte(tmp5) = 0;
					(&player_old_posy[1])[tmp3] = tmp5;
					--tmp3;
				} while ((int8_t)tmp3 >= 0);
				player_old_posy[0] = high_byte(player_y[0]);
				old_trail_scroll_y = scroll_y;
			}
		}
		if (discomode && !(kandoframecnt & discorefreshrate)) {

			tmp3 = G_Table[discoframe] + 0x80;
			tmp2 = (tmp3 & 0x3F);  		    
			pal_col(0, tmp2);
			pal_col(1, oneShadeDarker(tmp2)); 
			pal_col(9, oneShadeDarker(tmp2)); 

			tmp3 = 0xC0 + BG_Table[discoframe];
			tmp2 = (tmp3 & 0x3F);  		    
			pal_col(6, tmp2);
			pal_col(5, oneShadeDarker(tmp2)); 
			pal_set_update();

			discoframe++;
			if (discoframe == 12) discoframe = 0;
		}

		kandoframecnt++;
		music_update();
		if (slowmode && (kandoframecnt & 1)) { ppu_wait_nmi(); }
		else {
			ppu_wait_nmi();

			set_tile_banks();
		
			set_player_banks();

			if (!kandodebugmode) {
				// crossPRGBankJump0(mouse_update);
				// pad_poll(0); // read the first controller
			}
			else {
				crossPRGBankJump0(mouse_and_cursor);
			}

			if (mouse.left_press) joypad1.press_a = 1;
			if (mouse.left) joypad1.a = 1;

			if (options & platformer) twoplayer = 0;

			if ((options & oneptwoplayer) && twoplayer) {
				// yo actually wtf is this
				joypad2.hold = joypad1.hold<<1; // read the second controller
				joypad2.press = joypad1.press<<1;
				dual = 1;
			}
			else if (twoplayer) {
				// pad_poll(1); // read the second controller
				dual = 1;
			}
			
			if (!(joypad1.a)) dashing[0] = 0;

			//mouse debug here
			if (kandodebugmode) {
				
				if (mouse.left_press) {
					kandodebug2 = 1;
					//high_byte(currplayer_x) = mouse.x + high_byte(scroll_x);
					target_x_scroll_stop = 0xE000;
					curr_x_scroll_stop = 0xE000;
					high_byte(currplayer_y) = (mouse.y + high_byte(scroll_y)) - 10;
					high_byte(currplayer_x) = mouse.x - 10 < 0 ? mouse.x : mouse.x - 10;
					if (high_byte(currplayer_x) > 226) high_byte(currplayer_x) = 226;
					
				}
				else {
					kandodebug2 = 0;
					target_x_scroll_stop = 0x5000;
					cube_data[0] = 0;
				}
				
			}
			//end mouse debug
			
			if (options & jumpsound) {
				if (joypad1.press_a) {
					sfx_play(sfx_click, 0);
				}
			}



			if (joypad1.press_start || mouse.right_press) {
				joypad1.press = 0;
				mouse.right_press = 0;
				famistudio_music_pause(1);
				famistudio_update();
				color_emphasis(COL_EMP_DARK);
				// ppu_off();
				// mmc3_set_8kb_chr(16);
				// vram_adr(NAMETABLE_B);
				// vram_unrle(pausescreen); 	
				// ppu_on_all();
				while (!(joypad1.press & PAD_START) && !(mouse.right_press)) {
					if (VRAM_UPDATE == 1) {
						ppu_wait_nmi();
					}
					// force re-enable NMI every frame.
					VRAM_UPDATE = 1;
					if ((joypad1.up) && (joypad1.press_b)) {
						kandokidshack3++;
					}

					else if ((controllingplayer->press_b || mouse.left_press) && PRACTICE_ENABLED) {
						mmc3_set_prg_bank_1(GET_BANK(reset_game_vars));
						reset_game_vars();
						has_practice_point = 1;
						joypad1.press = PAD_START;
					}
					if (joypad1.press_select) { 
						gameState = 1; 
						sfx_play(sfx_exit_level,0);
						music_update();
						crossPRGBankJump0(gameboy_check);
						return;
					}
					if ((joypad1.press_right) && DEBUG_MODE) {
						speed == 4 ? speed = 0 : speed++;
					}
					if ((joypad1.press_left) && DEBUG_MODE) {
						gravity_mod == 4 ? gravity_mod = 0 : gravity_mod++;
					}
					if ((joypad1.down) && (joypad1.press_a)) {
						kandokidshack++;
					}
					else if ((joypad1.up) && (joypad1.press_a)) {
						kandokidshack2++;
					}
					else if ((joypad1.press_a) && DEBUG_MODE) {
	#ifdef FLAG_KANDO_FUN_STUFF
						gamemode == 8 ? gamemode = 0 : gamemode++;
	#else
						gamemode == 7 ? gamemode = 0 : gamemode++;
	#endif			
						cube_data[0] = 0;
						ppu_off();
						set_player_banks();
						oam_clear();
						crossPRGBankJump0(drawplayerone);
						mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
						draw_sprites();
						ppu_on_all();
					}
				}
				crossPRGBankJump0(gameboy_check);
				famistudio_music_pause(0);
				if (kandokidshack != 9) kandokidshack = 0;
				if (kandokidshack2 != 7) kandokidshack2 = 0;
				if (kandokidshack3 == 12) DEBUG_MODE = !DEBUG_MODE;
				else if (kandokidshack3 == 20) kandodebugmode ^= 1;
				else kandokidshack3 = 0;
			}
		if (options & debugtoggle) {
			if (joypad1.press_select) //THE BIG DEBUG - DISABLE BEFORE RELEASE
				{ 
					DEBUG_MODE = !DEBUG_MODE; 
					cube_data[0] &= 2; 
					cube_data[1] &= 2; 
				}		
		}
		if ((controllingplayer->press_b) && has_practice_point) crossPRGBankJump0(reset_game_vars);

		if (joypad1.press_up && DEBUG_MODE) {
			currplayer_gravity ^= 0x01;
		}
		
		if (joypad1.press_down && DEBUG_MODE) {
			mini ^= 1;
		}

		if (joypad1.select && DEBUG_MODE) {
		    if (++END_LEVEL_TIMER > 60) {
			END_LEVEL_TIMER = 0;
			gameState = 3;
			//DEBUG_MODE = 0;
			famistudio_music_stop();
		    }
		} else {
		    END_LEVEL_TIMER = 0;
		}

		//if (DEBUG_MODE) color_emphasis(COL_EMP_BLUE);
//		if (DEBUG_MODE) gray_line();

		if (was_on_slope_counter) {
			was_on_slope_counter--;
		} else slope_type = 0;

		crossPRGBankJump0(movement);

		kandotemp3 = 0;

		runthecolls();
		
		kandotemp3 = 1;
		
#ifdef FLAG_KANDO_FUN_STUFF		
		if (bigboi && !(kandoframecnt & 1) ) {

			x_plus_15();

			runthecolls();
			
			x_minus_15();

			y_minus_15();

		
			runthecolls();

			x_plus_15();

			runthecolls();

			x_minus_15();

			y_plus_15();

		}			
			
		else {
			if (longmode) {

				x_plus_15();

				runthecolls();
				
				x_minus_15();

			}

			if (tallmode) {

				y_minus_15();

				runthecolls();

				y_plus_15();

			}
		}
		kandotemp3 = 0;
#endif
		if (invincible_counter) invincible_counter--;

		crossPRGBankJump0(do_the_scroll_thing);

		check_spr_objects();



		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		{	// always store it back for practice mode
			player_x[0] = currplayer_x;
			player_y[0] = currplayer_y;
			player_vel_x[0] = currplayer_vel_x;
			player_vel_y[0] = currplayer_vel_y;
			player_gravity[0] = currplayer_gravity;
		}

		
		if (dual) { 
			currplayer = 1;					//take focus
			if (!(joypad2.a)) dashing[1] = 0;
			if (twoplayer) controllingplayer = &joypad2;		//take controls
			if (dual && (options & platformer) && !twoplayer) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }
			else if (dual && !(options & platformer)) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }

			{	
				currplayer_x = player_x[1];
				currplayer_y = player_y[1];
				currplayer_vel_x = player_vel_x[1];
				currplayer_vel_y = player_vel_y[1];
				currplayer_gravity = player_gravity[1];
			}

			if (controllingplayer->press_up && DEBUG_MODE) currplayer_gravity ^= 0x01;			//DEBUG GRAVITY

			crossPRGBankJump0(movement);

			kandotemp3 = 1;
			runthecolls();
			kandotemp3 = 0;
			
			crossPRGBankJump0(do_the_scroll_thing2);

			currplayer = 0;					//give back focus

			if (twoplayer) controllingplayer = &joypad1;		//give back controls

			{
				player_x[1] = currplayer_x;
				player_y[1] = currplayer_y;
				player_vel_x[1] = currplayer_vel_x;
				player_vel_y[1] = currplayer_vel_y;
				player_gravity[1] = currplayer_gravity;

				currplayer_x = player_x[0];
				currplayer_y = player_y[0];
				currplayer_vel_x = player_vel_x[0];
				currplayer_vel_y = player_vel_y[0];
				currplayer_gravity = player_gravity[0];
			}
		}

	}
   //     check_spr_objects();

  		oam_clear();

		mmc3_set_prg_bank_1(GET_BANK(draw_screen));
		draw_screen(); 
		mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
		draw_sprites();
        
		if (kandodebugmode) { if (mouse_timer) oam_spr(mouse.x, mouse.y - 1, (0xAD), 2); }	
 //       color_emphasis(0);

		if (DEBUG_MODE) gray_line();
		if (!DEBUG_MODE && !kandodebug2) {
		if (high_byte(player_x[0]) > 0x20) {
			if (cube_data[0] & 1 || cube_data[1] & 1) reset_level();
		} else cube_data[0] = cube_data[1] = 0;
	}

        if (gameState != 0x02) return;
	if (mouse_timer) mouse_timer--;

    }
    
}

void runthecolls() {
	if (!invincible_counter) {
		crossPRGBankJump0(x_movement_coll);
	}

	if (!kandotemp3) {
		crossPRGBankJump0(x_movement);
	}	

	crossPRGBankJump0(sprite_collide);

	if (!DEBUG_MODE && !invincible_counter) {
		crossPRGBankJump0(bg_coll_death);
	}
}				

void set_player_banks() {
		if (!retro_mode) {
			iconbank1 = 18; iconbank2 = 22; iconbank3 = iconbank;
		}
		else {
			iconbank1 = 20; iconbank2 = 24; iconbank3 = 16;
		}
		
		if (gamemode == 8) mmc3_set_2kb_chr_bank_0(NINJABANK);
		else if ((mini && gamemode != 0) || (gamemode == 7)) mmc3_set_2kb_chr_bank_0(iconbank2);
		else if (gamemode == 0 || gamemode == 1 || gamemode == 3) mmc3_set_2kb_chr_bank_0(iconbank3);
		else mmc3_set_2kb_chr_bank_0(iconbank1);

}

void set_tile_banks() {
	if (!no_parallax) {
		mmc3_set_1kb_chr_bank_0(spike_set[level] + (parallax_scroll_x & 1));
		mmc3_set_1kb_chr_bank_1(block_set[level] + (parallax_scroll_x & 1));	//tile graphics
		mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
		mmc3_set_1kb_chr_bank_3(saw_set[level] + (parallax_scroll_x & 1));
	}
	else {
		mmc3_set_1kb_chr_bank_0(spike_set[level]);
		mmc3_set_1kb_chr_bank_1(block_set[level]);	//tile graphics
		mmc3_set_1kb_chr_bank_2(SLOPESA);
		mmc3_set_1kb_chr_bank_3(saw_set[level]);
	}
}	

void x_minus_15() {
	high_byte(player_x[0]) -= 15;
	high_byte(currplayer_x) -= 15;	
}
void x_plus_15() {
	high_byte(player_x[0]) += 15;
	high_byte(currplayer_x) += 15;	
}
void y_minus_15() {
	high_byte(player_y[0]) -= 15;
	high_byte(currplayer_y) -= 15;	
}
void y_plus_15() {
	high_byte(player_y[0]) += 15;
	high_byte(currplayer_y) += 15;	
}