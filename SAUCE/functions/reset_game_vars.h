#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void reset_game_vars(){
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
	practice_parallax_scroll_x = parallax_scroll_x;
	practice_scroll_x = scroll_x;
	practice_scroll_y = scroll_y;
	practice_bg_color_type = lastbgcolortype;
	practice_g_color_type = lastgcolortype;
//	gnd_palette_transition_timer = 0;		//palete fade code
//	bg_palette_transition_timer = 0;		//palette fade code
}


void restore_practice_state() {
	player_x[0] = practice_player_x[0];
	long_temp_x = high_byte(practice_player_x[0]);
	player_x[1] = practice_player_x[1];
	player_y[0] = practice_player_y[0];
	player_y[1] = practice_player_y[1];
	player_vel_x[0] = practice_player_vel_x[0];
	player_vel_x[1] = practice_player_vel_x[1];
	player_vel_y[0] = practice_player_vel_y[0];
	player_vel_y[1] = practice_player_vel_y[1];
	player_gravity[0] = practice_player_gravity[0];
	player_gravity[1] = practice_player_gravity[1];
	cube_rotate[0] = practice_cube_rotate[0];
	cube_rotate[1] = practice_cube_rotate[1];
	gamemode = practice_player_gamemode;
	mini = practice_mini;
	dual = practice_dual;
	speed = practice_speed;
	parallax_scroll_x = practice_parallax_scroll_x;
	scroll_x = practice_scroll_x - (256 + 16);
	scroll_y = practice_scroll_y;

	__A__ = currplayer<<1;
	__asm__("tay");
	#define quick_ld(to, from) __asm__("lda %v,y\n sta %v\n lda %v+1,y\n sta %v+1", from, to, from, to)
	
	quick_ld(currplayer_x, player_x);
	quick_ld(currplayer_y, player_y);
	quick_ld(currplayer_vel_x, player_vel_x);
	quick_ld(currplayer_vel_y, player_vel_y);

	#undef quick_ld
	currplayer_gravity = player_gravity[currplayer];
}

#pragma code-name(pop)
#pragma data-name(pop)
#pragma rodata-name(pop)