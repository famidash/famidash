extern unsigned char scroll_count;
extern unsigned char* PARALLAX_CHR;

void reset_level(void) {
    // unsigned char i;
    if (!has_practice_point) famistudio_music_stop();
    coins = 0;

    robotjumpframe[0] = 0;
    tmp1 = 30;
    if (!DEBUG_MODE && (cube_data[0] & 1)) {
		update_level_completeness();
		sfx_play(sfx_death, 0);
		while (tmp1 != 0){
			ppu_wait_nmi();
			music_update();
			oam_clear_player();
			
			if (robotjumpframe[0] < 20) {
				if (!retro_mode) oam_meta_spr(high_byte(player_x[0])-2, high_byte(player_y[0])-2, Explode_Sprites[robotjumpframe[0]]);
				else oam_meta_spr(high_byte(player_x[0])-2, high_byte(player_y[0])-2, ExplodeR_Sprites[robotjumpframe[0]]);
				++robotjumpframe[0];
			}
			--tmp1;
        }
    }
    else if (!DEBUG_MODE && (cube_data[1] & 1)) {
		update_level_completeness();
		sfx_play(sfx_death, 0);
		while (tmp1 != 0){
			ppu_wait_nmi();
			music_update();
			oam_clear_player();	
			if (robotjumpframe[0] < 20) {
				if (!retro_mode) oam_meta_spr(high_byte(player_x[1])-2, high_byte(player_y[1])-2, Explode_Sprites2[robotjumpframe[0]]);
				else oam_meta_spr(high_byte(player_x[1])-2, high_byte(player_y[1])-2, ExplodeR_Sprites2[robotjumpframe[0]]);
				
				++robotjumpframe[0];
			}
			--tmp1;
		}
    }
    attempts++;
    pal_fade_to_withmusic(4,0);
    oam_clear();
    ppu_off(); // reset the level when you get to this point, and change this later
    scroll_x = 0;
    scroll_count = 0;
    set_scroll_x(scroll_x);
    scroll_y = 0xEF;
    set_scroll_y(scroll_y);
    init_rld(level);

    if (!(options & platformer)) {
        player_x[0] = 0x0000;
        player_x[1] = 0x0000;
        currplayer_x = 0x0000;
    } else {
        player_x[0] = 0x1110;
        player_x[1] = 0x1110;
        currplayer_x = 0x1110;
    }
    
    player_y[0] = 0xb000;
    player_y[1] = 0xb000;
    currplayer_y = 0xb000;

    outline_color = 0x30;

    jimsheatballalive[0] = 0;
    jimsheatballalive[1] = 0;

    gravity_mod = 0;
    player_gravity[0] = 0x00;
    player_gravity[1] = twoplayer ? 0x00 : 0x01;

    currplayer_gravity = player_gravity[currplayer];

    dual = twoplayer ? 1 : 0x00;
    mini = 0x00;
    player_vel_x[0] = 0;
    player_vel_y[0] = 0;
    player_vel_x[1] = 0;
    player_vel_y[1] = 0;
    disco_sprites = 0;
    target_scroll_y = 0x0180;
    currplayer_vel_x = 0;
    currplayer_vel_y = 0;
    cube_data[0] = 0;
    cube_data[1] = 0;
    cube_rotate[0] = 0;
    cube_rotate[1] = 0;
    forced_trails = 0;
    discoframe = 0;
	for (tmp2 = 0; tmp2 < 9; tmp2++) {
		player_old_posy[tmp2] = 0;
	}

    if (!has_practice_point)    invincible_counter = 8;
    
    unrle_first_screen();
    if (has_practice_point) {
	    tmp3 = practice_bg_color_type;
	    
			tmp2 = (tmp3 & 0x3F);                        
			if (tmp3 >= 0xC0){
			    pal_col(6, tmp2);
				pal_col(5, oneShadeDarker(tmp2)); 
			} else {
			    pal_col(0, tmp2);
				pal_col(1, oneShadeDarker(tmp2)); 
				pal_col(9, oneShadeDarker(tmp2)); 
			}    

	    tmp3 = practice_g_color_type;
	    
			tmp2 = (tmp3 & 0x3F);                        
			if (tmp3 >= 0xC0){
			    pal_col(6, tmp2);
				pal_col(5, oneShadeDarker(tmp2)); 
			} else {
			    pal_col(0, tmp2);
				pal_col(1, oneShadeDarker(tmp2)); 
				pal_col(9, oneShadeDarker(tmp2)); 
			}    
    }
    if (!no_parallax) mmc3_set_1kb_chr_bank_2(parallax_scroll_x + GET_BANK(PARALLAX_CHR));
    ppu_on_all();
    pal_fade_to_withmusic(0,4);
    if (!has_practice_point) {
        music_play(song);
    }
    
}