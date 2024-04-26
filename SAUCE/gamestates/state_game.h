/*
	Calls the movement routine of the current gamemode
	Implemented in asm
*/
void __fastcall__ movement(void);
void __fastcall__ movement2(void);

extern unsigned char* PARALLAX_CHR;
unsigned char END_LEVEL_TIMER;

void state_game(){
	ppu_off();

//	twoplayer = 1;

//	mini = 1;
    pal_bg((char *)paletteDefault);
    pal_spr((char *)paletteDefaultSP);

    load_ground(0);

	mmc3_set_8kb_chr(0);
    mmc3_set_1kb_chr_bank_2(GET_BANK(PARALLAX_CHR));
    
	reset_level();

    END_LEVEL_TIMER = 0;

	player_gravity[0] = 0;
	if (twoplayer) player_gravity[1] = 0x00;
	else player_gravity[1] = 0x01;		
	kandoframecnt = 0;
	cube_data[0] = 0;
	cube_data[1] = 0;
    player_x[0] = 0x0000;
    player_y[0] = 0xb000;
    player_x[1] = 0x0000;
    player_y[1] = 0xb000;
    while (1) {
	currplayer = 0;
	kandoframecnt++;
        ppu_wait_nmi();
        mmc3_set_1kb_chr_bank_0((parallax_scroll_x & 1) * 8 + 0);
        mmc3_set_1kb_chr_bank_1((parallax_scroll_x & 1) * 8 + 1);
        mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
        mmc3_set_1kb_chr_bank_3((parallax_scroll_x & 1) * 8 + 3);
        music_update();
        

        pad[0] = pad_poll(0); // read the first controller
	pad_new[0] = get_pad_new(0);

	if (twoplayer) {
		pad[1] = pad_poll(1); // read the second controller
		pad_new[1] = get_pad_new(1);
		dual = 1;
	}
        //if (pad_new & PAD_A) famistudio_sfx_play(sfx_click, 0);

	if (pad_new[controllingplayer] & PAD_UP) player_gravity[currplayer] ^= 0x01;


	if ((pad_new[controllingplayer] & PAD_B) && PRACTICE_ENABLED) {
		// player_gravity[currplayer] ^= 0x01;			//DEBUG GRAVITY
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
		practice_player_gamemode = gamemode;
		practice_mini = mini;
		practice_dual = dual;
		practice_speed = speed;
		practice_scroll_x = scroll_x;
		practice_scroll_y = scroll_y;
		memcpy(practice_famistudio_state, famistudio_state, sizeof(practice_famistudio_state));
		// practice_parallax_scroll_column = parallax_scroll_column;
		// practice_parallax_scroll_column_start = parallax_scroll_column_start;
		has_practice_point = 1;
	}

	if (pad_new[0] & PAD_START) {
		pad_new[0] = 0;
		famistudio_music_pause(1);
		famistudio_update();
		while (!(pad_new[0] & PAD_START)) {
			ppu_wait_nmi();
			pad[0] = pad_poll(0); // read the second controller
			pad_new[0] = get_pad_new(0);	
			if (pad_new[0] & PAD_SELECT) { 
				gameState = 1; 
				famistudio_sfx_play(sfx_exit_level, 0); 
				return; 
			}
		}
		famistudio_music_pause(0);
		//famistudio_update();
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

    if (DEBUG_MODE) color_emphasis(COL_EMP_BLUE);
	
	mmc3_set_prg_bank_1(0);
    
	x_movement();
	
	mmc3_set_prg_bank_1(GET_BANK(movement));	
	
	movement();


	if (!DEBUG_MODE) {
		if (!invincible_counter) bg_coll_death();
		else invincible_counter--;
        }

        if (DEBUG_MODE) color_emphasis(COL_EMP_RED);
	mmc3_set_prg_bank_1(GET_BANK(do_the_scroll_thing));
        do_the_scroll_thing(); 

	mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
//        check_spr_objects();
	if (!DEBUG_MODE) {
		if (cube_data[0] == 1) reset_level();
		if (cube_data[1] == 1) reset_level();
	}
       sprite_collide();
	if (dual) { 
		currplayer = 1;					//take focus
		if (twoplayer) controllingplayer = 1;		//take controls
		player_x[1] = player_x[0];
		if (pad_new[controllingplayer] & PAD_UP) player_gravity[currplayer] ^= 0x01;			//DEBUG GRAVITY

		mmc3_set_prg_bank_1(GET_BANK(movement));
		movement();
		if (!DEBUG_MODE) {
			if (!invincible_counter) bg_coll_death();
			else invincible_counter--;
		}
		mmc3_set_prg_bank_1(GET_BANK(do_the_scroll_thing));
//		x_movement();
		do_the_scroll_thing2(); 
		mmc3_set_prg_bank_1(GET_BANK(sprite_collide));
		sprite_collide();
		currplayer = 0;					//give back focus
		if (twoplayer) controllingplayer = 0;		//give back controls
	}
	mmc3_set_prg_bank_1(0);
        check_spr_objects();

        if (DEBUG_MODE) color_emphasis(COL_EMP_GREEN);
  
  oam_clear();

	// mmc3_set_prg_bank_1(GET_BANK(draw_screen_R));	
        draw_screen_R(); 
	mmc3_set_prg_bank_1(GET_BANK(draw_sprites));	
        draw_sprites();
        
        color_emphasis(0);
        
        
  //       if (DEBUG_MODE) gray_line();
        if (gameState != 0x02) return;
    }
}