/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
void __fastcall__ movement(void);
void __fastcall__ movement2(void);

void x_movement_coll() {
	if (slope_frames == 1 && currplayer_vel_y != 0) {
	// we we're on an slope and now we aren't, so push the player upwards a bit
		currplayer_vel_y = -0x380;
	}
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	// no L/R collision required, since that is accounted for with the death script
	if (high_byte(currplayer_x) > 0x10) {
		bg_coll_floor_spikes(); // check for spikes at the left of the player (fixes standing on spikes)
		if (bg_coll_R()) {
			if (!(options & platformer)) {cube_data[currplayer] |= 0x01; }
			else {currplayer_vel_x = 0; }
		}
	}	
}

extern unsigned char* PARALLAX_CHR;
unsigned char END_LEVEL_TIMER;

void state_game(){
	if (level == 0x0E) no_parallax = 1;
	else no_parallax = 0;
	
	outline_color = 0x30;

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
    ppu_off();

//	twoplayer = 1;

//	mini = 1;
    pal_bg(paletteDefault);
    pal_spr(paletteDefaultSP);

    load_ground(0);

//	mmc3_set_8kb_chr(0);
//    mmc3_set_1kb_chr_bank_2(GET_BANK(PARALLAX_CHR));
    
	currplayer = 0;
//	current_transition_timer_length = 0;
	reset_level();

    END_LEVEL_TIMER = 0;
    songtimer = 0;
	kandoframecnt = 0;
//	mmc3_set_2kb_chr_bank_1(18);
	
	iconbank = iconBankTable[icon];

	pal_col(0x0A,0x0F);   //palette 2 set to 0x0F for mountains
	pal_col(0x0B,color1);   //palette 2 set to player color

	for (tmp2 = 0; tmp2 < 8; tmp2++) {
		player_old_posy[tmp2] = 0;
	}
	if (!discomode) {
		pal_col(0x1F,color2);
		pal_col(0x1D,color3);
		pal_col(0x1E,color1);
	}
	else {
		switch (discomode) {
			case 0x02: discorefreshrate = 0x1F; break;
			case 0x04: discorefreshrate = 0x0F; break;
			case 0x08: discorefreshrate = 0x07; break;
			case 0x10: discorefreshrate = 0x03; break;
			case 0x01: discorefreshrate = 0x3F; break;
		};
	}
	

    while (1) {

	pal_col(3,outline_color);
	pal_col(7,outline_color);

	if (retro_mode) { if (gamemode == 0) gamemode = 4; }

	if (level == 0x09 || level == 0x0A || level == 0x0B || level == 0x0C || level == 0x0D || level == 0x0E) {									//
		if ((kandoframecnt & 0x1F) == 0x10 ) mmc3_set_2kb_chr_bank_1(30);		//
		else if ((kandoframecnt & 0x1F) == 0x00) mmc3_set_2kb_chr_bank_1(28);		// DECO PULSE
	}											//
	else {											//
		if ((kandoframecnt & 0x1F) == 0x10 ) mmc3_set_2kb_chr_bank_1(26);		//
		else if ((kandoframecnt & 0x1F) == 0x00) mmc3_set_2kb_chr_bank_1(24);		//
	}											//

	if ((options & platformer) && !has_practice_point) {
		songtimer++;
		if (songtimer > songtime[song] ) { songtimer = 0; music_play(song); }

	}		    

	if (trails || gamemode == 6) {
		if (!(kandoframecnt & 0x03)) {
			player_old_posy[7] = player_old_posy[6];
			player_old_posy[6] = player_old_posy[5];
			player_old_posy[5] = player_old_posy[4];
			player_old_posy[4] = player_old_posy[3];
			player_old_posy[3] = player_old_posy[2];
			player_old_posy[2] = player_old_posy[1];
			player_old_posy[1] = player_old_posy[0];
			player_old_posy[0] = high_byte(player_y[0]);
		}
	}
	    if (discomode && !(kandoframecnt & discorefreshrate)) {
		    maketmp2();
		pal_col(0x1F,tmp2);
		    maketmp2();
		pal_col(0x1E,tmp2);
		    maketmp2();
		pal_col(0x1D,tmp2);

		   tmp3 = rand8();
		   if (tmp3 < 0x80) tmp3 += 0x80;
		   else if (tmp3 >= 0xF0) tmp3 -= 0x80;
		tmp2 = (tmp3 & 0x3F);  		    
		if (tmp3 >= 0xC0){
		    pal_col(6, tmp2);
		    if (tmp2-0x10 & 0xC0) { 
			pal_col(5, 0x0f); 
		    } else { 
			pal_col(5, (tmp2-0x10)); 
		    }
		} else {
		    pal_col(0, tmp2);
		    if (tmp2-0x10 & 0xC0) { 
			pal_col(1, 0x0f); 
			pal_col(9, 0x0f); 
		    } else { 
			pal_col(1, (tmp2-0x10)); 
			pal_col(9, (tmp2-0x10)); 
		    }
		}		    
	    }





		// {	// done in reset_level and after storing player 1
		// 	currplayer_x = player_x[0];
		// 	currplayer_y = player_y[0];
		// 	currplayer_vel_x = player_vel_x[0];
		// 	currplayer_vel_y = player_vel_y[0];
		// 	currplayer_gravity = player_gravity[0];
		// }

		kandoframecnt++;
        ppu_wait_nmi();
	if (!no_parallax) {
		mmc3_set_1kb_chr_bank_0(spike_set[level] + (parallax_scroll_x & 1));
		mmc3_set_1kb_chr_bank_1(block_set[level] + (parallax_scroll_x & 1));	//tile graphics
		mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
		mmc3_set_1kb_chr_bank_3(saw_set[level] + (parallax_scroll_x & 1));
	}
//	else {
  //     mmc3_set_1kb_chr_bank_0(spike_set[level]);
    //    mmc3_set_1kb_chr_bank_1(block_set[level]);	//tile graphics
 //       mmc3_set_1kb_chr_bank_2(parallax_scroll_x);
   //     mmc3_set_1kb_chr_bank_3(saw_set[level]);
	//}
	if (!retro_mode) {
		if ((mini && gamemode != 0) || (gamemode == 7)) mmc3_set_2kb_chr_bank_0(20);
		else if (mini && gamemode == 0) mmc3_set_2kb_chr_bank_0(iconbank);
		else if (gamemode == 0 || gamemode == 1 || gamemode == 3) mmc3_set_2kb_chr_bank_0(iconbank);
		else mmc3_set_2kb_chr_bank_0(16);
	}
	else {
		if (mini && gamemode != 0 || (gamemode == 7)) mmc3_set_2kb_chr_bank_0(22);
		else if (mini && gamemode == 0) mmc3_set_2kb_chr_bank_0(32);
		else if (gamemode == 0 || gamemode == 1 || gamemode == 3) mmc3_set_2kb_chr_bank_0(32);
		else mmc3_set_2kb_chr_bank_0(18);
	}
//	else mmc3_set_2kb_chr_bank_0(28);
//



        music_update();
        

        pad[0] = pad_poll(0); // read the first controller
		pad_new[0] = get_pad_new(0);

		if (!(pad[currplayer] & PAD_A)) dashing[currplayer] = 0;

		if (options & platformer) twoplayer = 0;

		if ((options & oneptwoplayer) && twoplayer) {
			pad[1] = pad[0] << 4; // read the second controller
			pad_new[1] = pad_new[0] << 4;
			dual = 1;
		}
		else if (twoplayer) {
			pad[1] = pad_poll(1); // read the second controller
			pad_new[1] = get_pad_new(1);
			dual = 1;
		}
		
		if (options & jumpsound) {
			if (pad_new[0] & PAD_A) {
				sfx_play(sfx_click, 0);
			}
		}



		if (pad[controllingplayer] & PAD_SELECT && pad_new[controllingplayer] & PAD_UP) currplayer_gravity ^= 0x01;

				if ((pad_new[controllingplayer] & PAD_B) && PRACTICE_ENABLED && has_practice_point) {
			// player_gravity[currplayer] ^= 0x01;			//DEBUG GRAVITY
					if (!has_practice_point) music_play(song_practice);
					practice_player_x[0] = player_x[0];
					long_temp_x = high_byte(player_x[0]);
					practice_player_x[1] = player_x[1];
					practice_player_y[0] = player_y[0];
					practice_player_y[1] = player_y[1];
					practice_player_vel_x[0] = player_vel_x[0];
					practice_player_vel_x[1] = player_vel_x[1];
					practice_player_vel_y[0] = player_vel_y[0];
					practice_player_vel_y[1] = player_vel_y[1];
					practice_player_gravity[0] = player_gravity[0];
					practice_player_gravity[1] = player_gravity[1];
					practice_cube_rotate[0] = cube_rotate[0];
					practice_cube_rotate[1] = cube_rotate[1];
					practice_player_gamemode = gamemode;
					practice_mini = mini;
					practice_dual = dual;
					practice_speed = speed;
					practice_scroll_x = scroll_x;
					practice_scroll_y = scroll_y;
					practice_bg_color_type = lastbgcolortype;
					practice_g_color_type = lastgcolortype;
				//	gnd_palette_transition_timer = 0;		palete fade code
				//	bg_palette_transition_timer = 0;		palette fade code

				//	memcpy(practice_famistudio_state, famistudio_state, sizeof(practice_famistudio_state));	unneeded because of practice music
					has_practice_point = 1;
		}


/* palette fade code
		if (gnd_palette_transition_timer > 0) {
			gnd_palette_transition_timer--;
			swapbyte(PAL_BUF[original_gnd_palette_idx_0], original_gnd_palette_color_0);
			swapbyte(PAL_BUF[original_gnd_palette_idx_1], original_gnd_palette_color_1);
		}
		if (bg_palette_transition_timer > 0) {
			bg_palette_transition_timer--;
			swapbyte(PAL_BUF[original_bg_palette_idx_0], original_bg_palette_color_0);
			swapbyte(PAL_BUF[original_bg_palette_idx_1], original_bg_palette_color_1);
			swapbyte(PAL_BUF[original_bg_palette_idx_2], original_bg_palette_color_2);
		}
*/
		if (pad_new[0] & PAD_START) {
			pad_new[0] = 0;
			famistudio_music_pause(1);
			famistudio_update();
			color_emphasis(COL_EMP_DARK);
			pal_bright(3);
			// ppu_off();
			// mmc3_set_8kb_chr(16);
			// vram_adr(NAMETABLE_B);
			// vram_unrle(pausescreen); 	
			ppu_on_all();
			while (!(pad_new[0] & PAD_START)) {
				
				// ppu_wait_nmi();
				pad[0] = pad_poll(0); // read the second controller
				pad_new[0] = get_pad_new(0);	
				if ((pad_new[controllingplayer] & PAD_B) && PRACTICE_ENABLED) {
			// player_gravity[currplayer] ^= 0x01;			//DEBUG GRAVITY
					if (!has_practice_point) music_play(song_practice);
					practice_player_x[0] = player_x[0];
					long_temp_x = high_byte(player_x[0]);
					practice_player_x[1] = player_x[1];
					practice_player_y[0] = player_y[0];
					practice_player_y[1] = player_y[1];
					practice_player_vel_x[0] = player_vel_x[0];
					practice_player_vel_x[1] = player_vel_x[1];
					practice_player_vel_y[0] = player_vel_y[0];
					practice_player_vel_y[1] = player_vel_y[1];
					practice_player_gravity[0] = player_gravity[0];
					practice_player_gravity[1] = player_gravity[1];
					practice_cube_rotate[0] = cube_rotate[0];
					practice_cube_rotate[1] = cube_rotate[1];
					practice_player_gamemode = gamemode;
					practice_mini = mini;
					practice_dual = dual;
					practice_speed = speed;
					practice_scroll_x = scroll_x;
					practice_scroll_y = scroll_y;
					practice_bg_color_type = lastbgcolortype;
					practice_g_color_type = lastgcolortype;
				//	gnd_palette_transition_timer = 0;		palete fade code
				//	bg_palette_transition_timer = 0;		palette fade code

				//	memcpy(practice_famistudio_state, famistudio_state, sizeof(practice_famistudio_state));	unneeded because of practice music
					has_practice_point = 1;
					pad_new[0] = PAD_START;
		}
				if (pad_new[0] & PAD_SELECT) { gameState = 1; 
					sfx_play(sfx_exit_level,0);
					music_update();
					color_emphasis(COL_EMP_NORMAL);
					return;
				}
			}
			color_emphasis(COL_EMP_NORMAL);
			pal_bright(4);
			famistudio_music_pause(0);
			// ppu_off();
			// mmc3_set_8kb_chr(0);
			// ppu_on_all();
			// famistudio_update();
		}
        if (pad_new[0] & PAD_SELECT) { DEBUG_MODE = !DEBUG_MODE; cube_data[0] &= 2; cube_data[1] &= 2; }

		if (pad_new[0] & PAD_DOWN) {
			mini ^= 1;
		}

        if (pad[0] & PAD_SELECT) {
            if (++END_LEVEL_TIMER > 60) {
                END_LEVEL_TIMER = 0;
                gameState = 3;
                DEBUG_MODE = 0;
                famistudio_music_stop();
            }
        } else {
            END_LEVEL_TIMER = 0;
        }

		//if (DEBUG_MODE) color_emphasis(COL_EMP_BLUE);
//		if (DEBUG_MODE) gray_line();

		mmc3_set_prg_bank_1(GET_BANK(movement));
		
		movement();

		mmc3_set_prg_bank_1(GET_BANK(x_movement_coll));
		x_movement_coll();
		
		mmc3_set_prg_bank_1(GET_BANK(x_movement));
		x_movement();
		
		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		sprite_collide();

		if (!DEBUG_MODE && !invincible_counter) {
			if ((dual && (kandoframecnt & 0x01)) || !dual)
				bg_coll_death();
		}
		if (invincible_counter) invincible_counter--;

		//if (DEBUG_MODE) color_emphasis(COL_EMP_RED);
//		if (DEBUG_MODE) gray_line();
		mmc3_set_prg_bank_1(GET_BANK(do_the_scroll_thing));
		do_the_scroll_thing(); 

		check_spr_objects();



		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		{	// always store it back for practice mode
			player_x[0] = currplayer_x;
			player_y[0] = currplayer_y;
			player_vel_x[0] = currplayer_vel_x;
			player_vel_y[0] = currplayer_vel_y;
			player_gravity[0] = currplayer_gravity;
		}

		if (!DEBUG_MODE) {
			if (cube_data[0] == 1) reset_level();
		}
		
		if (dual) { 
			currplayer = 1;					//take focus
			if (!(pad[currplayer] & PAD_A)) dashing[currplayer] = 0;
			if (twoplayer) controllingplayer = 1;		//take controls
			if (dual && (options & platformer) && !twoplayer) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }
			else if (dual && !(options & platformer)) { player_x[1] = player_x[0]; player_vel_x[1] = player_vel_x[0]; }

			{	
				currplayer_x = player_x[1];
				currplayer_y = player_y[1];
				currplayer_vel_x = player_vel_x[1];
				currplayer_vel_y = player_vel_y[1];
				currplayer_gravity = player_gravity[1];
			}

			if (pad_new[controllingplayer] & PAD_UP) currplayer_gravity ^= 0x01;			//DEBUG GRAVITY

			mmc3_set_prg_bank_1(GET_BANK(movement));
			movement();

			if (!DEBUG_MODE) {
				if (!invincible_counter) bg_coll_death();
			}

			mmc3_set_prg_bank_1(GET_BANK(do_the_scroll_thing2));
			// x_movement();
			x_movement_coll();

			do_the_scroll_thing2();

			mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
			sprite_collide();
	//		if(!DEBUG_MODE && cube_data[1] & 0x01) {
	//			reset_level();
	//		}
			currplayer = 0;					//give back focus
			if (twoplayer) controllingplayer = 0;		//give back controls
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
		// mmc3_set_prg_bank_1(GET_BANK(check_spr_objects));	// it's in a const bank
        check_spr_objects();

//        if (DEBUG_MODE) color_emphasis(COL_EMP_GREEN);
//	if (DEBUG_MODE) gray_line();  
  		oam_clear();

		mmc3_set_prg_bank_1(GET_BANK(draw_screen_R));
        draw_screen_R(); 
		mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
        draw_sprites();
        
 //       color_emphasis(0);
        
        
        if (DEBUG_MODE) gray_line();
		if (!DEBUG_MODE) {
			if (cube_data[1] == 1) reset_level();
		}
        if (gameState != 0x02) return;
    }
}

