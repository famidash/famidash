#pragma code-name(push, "XCD_BANK_04")
#pragma data-name(push, "XCD_BANK_04")
#pragma rodata-name(push, "XCD_BANK_04")

void reset_level(void);

/*
	Draws the first player sprite
	Implemented in asm
*/
void __fastcall__ drawplayerone();
void __fastcall__ drawplayertwo();

void draw_sprites(void){
	// dual = 1;
	// twoplayer = 1;
	
	// draw player

	if (!invisible) {
		if (dual) {
			if (kandoframecnt & 0x01) { drawplayertwo(); drawplayerone(); }
			else { drawplayerone(); drawplayertwo(); }
		}
		else drawplayerone();
	}
	// the level sprites

	//	for (index = 0; index < max_loaded_sprites; ++index){		//no flicker
	if (invisblocks) return;

	if (has_practice_point) {
		
		if (long_temp_x > 10) { 
			long_temp_x -= 2;
			oam_meta_spr(long_temp_x, idx16_hi_NOC(practice_player_y, currplayer)-1, Practice_Sprites[0]);
		}
		// else if (long_temp_x < 10) {}
	}

	if (jimsheatballalive[0]) {
		oam_meta_spr(jimsheatballx[0], jimsheatbally[0], Heat_Ball_Sprites[jimsheatballframe[0]]);		
		jimsheatballframe[0] == 20 ? jimsheatballframe[0] = 0 : jimsheatballframe[0]++;
		jimsheatballx[0] == 0xFF ? jimsheatballalive[0] = 0 : jimsheatballx[0]++;
	}
	if (jimsheatballalive[1]) {
		oam_meta_spr(jimsheatballx[1], jimsheatbally[1], Heat_Ball_Sprites[jimsheatballframe[1]]);		
		jimsheatballframe[1] == 20 ? jimsheatballframe[1] = 0 : jimsheatballframe[1]++;
		jimsheatballx[1] == 0xFF ? jimsheatballalive[1] = 0 : jimsheatballx[1]++;
	}

	


	

	// The flickering motherfucker, by jrowe
	shuffle_offset += 11;
	if (shuffle_offset >= max_loaded_sprites) {
		shuffle_offset -= max_loaded_sprites;
	}
	// the level sprites
	for (count = 0; count < max_loaded_sprites; ++count){
		// and every sprite add another number thats also coprime with 16 AND 11
		shuffle_offset += 9;
		if (shuffle_offset >= max_loaded_sprites) {	
			shuffle_offset -= max_loaded_sprites;
		}
		index = shuffle_offset;
		if (index < 0xF0) {
			if (activesprites_type[index] & 0x80) continue;
		}

		temp_y = activesprites_realy[index];
		if (!activesprites_active[index]) continue; 
		temp_x = activesprites_realx[index];
		if (temp_x == 0) temp_x = 1;
		if (temp_x > 0xf0) continue;

#define animation_frame_count tmp1
#define animation_frame tmp2
#define spr_type tmp3
#define needs_reload tmp4
#define animation_ptr tmpptr1
#define animation_data_ptr tmpptr2
		if (activesprites_type[index] > 0x80) {}
		else {
			if (temp_y < 0xf0) {
			needs_reload = 0;
			spr_type = activesprites_type[index];
			animation_ptr = (unsigned char *)animation_frame_list[spr_type & 0x7F];
			// If this sprite has animations, then this pointer will not be null
			if (high_byte(animation_ptr)) {
				// Reduce the frame counter by one to see if we need to move to the next frame
				// If this frame has expired, then move to the next animation frame
				animation_frame_count = uint8_dec(activesprites_anim_frame_count, index);
				if (animation_frame_count >= 0x80) {
					animation_frame = uint8_inc(activesprites_anim_frame, index);
					// if the animation frame is past the length, wrap it around back to zero
					if (animation_frame >= animation_frame_length[spr_type]) {
						activesprites_anim_frame[index] = 0;
						animation_frame = 0;
					}
					// and then set the animation_frame_count to be reloaded
					needs_reload = 1;
				} else {
					animation_frame = activesprites_anim_frame[index];
				}
				
				// Now load the data for this frame of animation
				// The fastest way to convince cc65 to read all of the data is to force
				// it to read all the bytes at once
				tmplong = ((unsigned long int*)animation_ptr)[animation_frame];
				if (needs_reload) {
					uint8_store(activesprites_anim_frame_count, index, low_byte(tmplong));
				}
				// And finally, load the pointer for this animation
				animation_data_ptr = (unsigned char*)high_word(tmplong);
			} else {
				animation_data_ptr =  (unsigned char*)Metasprites[spr_type & 0x7F];
			}
			oam_meta_spr(temp_x, temp_y, animation_data_ptr);
			}
		}
		
	}
	if (forced_trails == 1 || trails == 1 || (gamemode == 6 && trails != 2)) {
		tmp6 = currplayer_vel_x << 1;
		tmp5 = player_x[0] - tmp6;

		tmp1 = 8;

		do {
			oam_meta_spr(high_byte(tmp5), uint8_load(player_old_posy, (uint8_t)(9 - tmp1)), Trail_Circ);
			tmp5 = tmp5 - tmp6;
			tmp1--;
		} while (tmp1 > 0);

	}
	if ((forced_trails == 2 || trails == 2) && !dual && !twoplayer) {

		tmpA = player_x[0];
		tmpB = player_y[0];

		high_byte(player_x[0]) -= 8;
		high_byte(player_y[0]) = player_old_posy[3];

		drawplayerone();
		
		high_byte(player_x[0]) -= 8;
		high_byte(player_y[0]) = player_old_posy[6];

		drawplayerone();
		
		player_x[0] = tmpA;
		player_y[0] = tmpB;
	}
#undef spr_type
#undef animation_ptr
}



#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
