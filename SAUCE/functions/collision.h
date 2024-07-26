/* 
	Gets the collision of the current tile
	Implemented in asm
*/
__fastcall__ char bg_collision_sub(void);

/*
	Out:
	A
*/
char bg_coll_sides() {
	switch (collision) {
		case COL_BOTTOM: 
			if (temp_y & 0x08) return 1;		// If Y pos inside block ≥ 8px
			break;	
		case COL_TOP: 
			if (!(temp_y & 0x08)) return 1;		// If Y pos inside block < 8px
			break;	
		case COL_ALL: 
			return 1;		
		case COL_UP_LEFT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			break;
	};
	return 0;
}
/*
	Clobbers:
	tmp2
*/
void bg_coll_spikes() {
	switch (collision) {
		case COL_UP_LEFT_SPIKE:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_UP_RIGHT_SPIKE:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_UP_BOTH_SPIKES:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_DOWN_LEFT_SPIKE:
			if ((temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_DOWN_RIGHT_SPIKE:
			if ((temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_DOWN_BOTH_SPIKES:
			if ((temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_DEATH_LEFT:
			if ((uint8_t)(temp_x & 0x0f) < 0x06) {
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x09) cube_data[currplayer] = 1;
			}
			break;
		case COL_DEATH_RIGHT:
			if ((uint8_t)(temp_x & 0x0f) >= 0x0a) {
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x09) cube_data[currplayer] = 1;
			}
			break;
		case COL_DEATH_TOP:
			if ((uint8_t)(temp_y & 0x0f) < 0x04) {			
				tmp2 = (uint8_t)(temp_x & 0x0f);				// If Y pos inside block < 8px, die
				if (tmp2 >= 0x04 && tmp2 < 0x09) {		// If X pos even insider, die even more
					cube_data[currplayer] = 1;						
				}
			}		
			break;
		case COL_DEATH_BOTTOM:
			if ((uint8_t)(temp_y & 0x0f) > 0x0c) {							// If Y pos inside block ≥ 8px, die
				tmp2 = (uint8_t)(temp_x & 0x0f);				// If Y pos inside block < 8px, die
				if (tmp2 >= 0x04 && tmp2 < 0x09) {		// If X pos even insider, die even more
					cube_data[currplayer] = 1;						
				}
			}								// else nothing
			break;
		case COL_DEATH:	
			tmp2 = (uint8_t)(temp_y & 0x0f);
			if (tmp2 >= 0x04 && tmp2 < 0x0c) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x03 && tmp2 < 0x09) {
					cube_data[currplayer] = 0x01;
				}
			}
			break;
		case COL_LEFT_SPIKE_BLOCK:
		case COL_BOTTOM_LEFT_SPIKE:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
		case COL_RIGHT_SPIKE_BLOCK:
		case COL_BOTTOM_RIGHT_SPIKE:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x0f);
				if (tmp2 >= 0x0a && tmp2 < 0x0d)
					cube_data[currplayer] = 1;											
			}
			break;
		case COL_BOTTOM_SPIKES:
			if (!(temp_y & 0x08)) {
				tmp2 = (uint8_t)(temp_x & 0x07);
				if (tmp2 >= 0x02 && tmp2 < 0x06)
					cube_data[currplayer] = 1;						
			}
			break;
	}
}

/*
	Clobbers:
	tmp8
*/
void bg_coll_floor_spikes() { // used just for checking ground spikes on the floor
	temp_x = Generic.x + low_word(scroll_x) + (Generic.width >> 1); // automatically only the low byte

	storeWordSeparately(
		add_scroll_y(
			Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 3),
			scroll_y
		), temp_y, temp_room);

	for (tmp8 = 0; tmp8 < 2; tmp8++) {
		bg_collision_sub();
	
		bg_coll_spikes();
			
		storeWordSeparately(
			add_scroll_y(
				Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 0) + Generic.height - 3, scroll_y
			), temp_y, temp_room);
	}

	// Check middle of cube

	storeWordSeparately(
		add_scroll_y(
			Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 0) + (Generic.height >> 1), scroll_y
		), temp_y, temp_room);

	bg_collision_sub();

	bg_coll_spikes();

	storeWordSeparately(
		add_scroll_y(
			Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 3),
			scroll_y
		), temp_y, temp_room);

	temp_x = Generic.x + low_word(scroll_x) + (Generic.width); // automatically only the low byte

	for (tmp8 = 0; tmp8 < 2; tmp8++) {
		bg_collision_sub();

		bg_coll_spikes();

		storeWordSeparately(
			add_scroll_y(
				Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 0) + Generic.height - 3, scroll_y
			), temp_y, temp_room);
	}

	temp_x -= (Generic.width >> 1); // automatically only the low byte

	storeWordSeparately(
		add_scroll_y(
			Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 3), scroll_y
		), temp_y, temp_room);

	for (tmp8 = 0; tmp8 < 2; tmp8++) {
		bg_collision_sub();
	
		bg_coll_spikes();
			
		storeWordSeparately(
			add_scroll_y(
				Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 0) + Generic.height - 3, scroll_y
			), temp_y, temp_room);
	}
}
/*
	Clobbers:
	tmp2, tmp8
*/
char bg_coll_mini_blocks() {
	
	switch (collision) {
		case COL_UP_LEFT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			break;
		case COL_UP_RIGHT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 < 0x08 && ((uint8_t)(temp_x & 0x0f) >= 0x08)) {
				return 1;
			}
			break;
		case COL_DOWN_LEFT:
		case COL_LEFT_SPIKE_BLOCK:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 >= 0x08 && ((uint8_t)(temp_x & 0x0f) < 0x08)) {
				return 1;
			}
			break;
		case COL_DOWN_RIGHT:
		case COL_RIGHT_SPIKE_BLOCK:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if (tmp2 >= 0x08 && ((uint8_t)(temp_x & 0x0f) >= 0x08)) {
				return 1;
			}
			break;
		case COL_BOTTOM_LEFT_SPIKE:
		case COL_BOTTOM_RIGHT_SPIKE:
		case COL_BOTTOM_SPIKES:
		case COL_BOTTOM:
			tmp2 = temp_y & 0x0f;
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 >= 0x08) {
			if (tmp8 != tmp2) {
				return 1;
			}
			break;
		case COL_TOP:
			tmp2 = temp_y & 0x0f;
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 >= 0x08) {
			if (tmp8 == tmp2) {
				return 1;
			}
			break;
		case COL_LEFT:
			tmp8 = (uint8_t)(temp_y & 0x0f) & 0x0f;	 
			if ((uint8_t)(temp_x & 0x0f) < 0x08) {
				return 1;
			}
			break;
		case COL_RIGHT:
			tmp8 = (uint8_t)(temp_y & 0x0f) & 0x0f;	 
			if ((uint8_t)(temp_x & 0x0f) >= 0x08) {
				return 1;
			}
			break;
		case COL_TOP_LEFT_BOTTOM_RIGHT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if ((uint8_t)(temp_x & 0x0f) < 0x08) {
				if (tmp2 < 0x08) return 1;
			} else {
				if (tmp2 >= 0x08) return 1;
			}
			break;
		case COL_TOP_RIGHT_BOTTOM_LEFT:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			if ((uint8_t)(temp_x & 0x0f) < 0x08) {
				if (tmp2 >= 0x08) return 1;
			} else {
				if (tmp2 < 0x08) return 1;
			}
			break;
	}
	
	return 0;
}

char bg_coll_slope();

/*
	Clobbers:
	Nothing wow

*/
char bg_side_coll_common() {
	tmp1 = Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 0) + (Generic.height >> 1);

	if (mini && (gamemode == CUBE_MODE || gamemode == ROBOT_MODE)) {
		tmp1 += (currplayer ? 2 : -2);
	}
	
	if (slope_frames > 0) { // if we are on a slope, make right_col a little more upwards so it doesn't hit blocks to the side of the slope
		tmp1 -= (currplayer_gravity ? 4 : -4);
	}

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	bg_collision_sub();
	
	if (gamemode == 6) {
		if (bg_coll_slope()) {
			if (!dblocked[currplayer]) {
				cube_data[currplayer] |= 1;
			} 
		}	
		dblocked[currplayer] = 0;
		if (was_on_slope_counter) return 0;
	}

	bg_coll_spikes();

	return bg_coll_sides() || bg_coll_mini_blocks();
}

/*
	Clobbers:
	Nothing l o l
*/
char bg_coll_R() {
    // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x) + Generic.width + (platformer ? 3 : 0); // automatically only the low byte
	return bg_side_coll_common();
}

/*
	Clobbers:
	Nothing lmao
*/
char bg_coll_L() {
    // check 2 points on the left side
	temp_x = Generic.x + low_word(scroll_x) - (platformer ? 3 : 0); // automatically only the low byte
	return bg_side_coll_common();
}


/*
	Clobbers:
	tmp2, tmp3
	Out:
	A, tmp8
*/
char bg_coll_U_D_checks() {
	switch (collision) {
		case COL_ALL: 
			return 1;
		case COL_DEATH_TOP:
			tmp2 = temp_y & 0x0f;	
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 < 0x08) {
			if (tmp8 == tmp2) {
				// if (tmp2 < 0x04) {
				if (!(tmp2 & 0x0C)) {
					// if ((temp_x & 0x0f) >= 0x04 && (temp_x & 0x0f) < 0x0c) {
					if ((temp_x & 0x0f) >= 0x04 && (temp_x & 0x0f) < 0x09) {
						cube_data[currplayer] = 1;
					}
				}
			}
			break;
		case COL_DEATH_BOTTOM:
			tmp2 = temp_y & 0x0f;
			tmp8 = tmp2 & 0x07;	 
			// if (tmp2 >= 0x08) {
			if (tmp8 != tmp2) {
				if (tmp2 >= 0x0c) {
					// if ((temp_x & 0x0f) >= 0x04 && (temp_x & 0x0f) < 0x0c) {
					if ((temp_x & 0x0f) >= 0x04 && (temp_x & 0x0f) < 0x09) {
						cube_data[currplayer] = 1;
					}
				}
			}
			break;
		case COL_FLOOR_CEIL:
			dblocked[currplayer] = 1;
			return 1;
	}

	return 0;
}
#define SLOPE_NONE			0
#define SLOPE_45DEG_UP 		1
#define SLOPE_45DEG_DOWN 	2
#define SLOPE_22DEG_UP 		3
#define SLOPE_22DEG_DOWN 	4
#define SLOPE_66DEG_UP 		5
#define SLOPE_66DEG_DOWN 	6

/*
	Clobbers:
	tmp4, tmp7
	Out:
	A, tmp8
*/
char bg_coll_slope() {	
	switch (collision) {
		case COL_SLOPE_SUPPORT:
			if (slope_type) {
				if (pad[controllingplayer] & PAD_A && gamemode != 6) {
					slope_frames = 0;
					slope_type = 0;
				} else {
					slope_frames = (gamemode == 6 ? 3 : 1); //signal BG_COLL_R to not check stuff
					was_on_slope_counter = (gamemode == 6 ? 6 : 2);
				}
				return 1;
			}
			else return 0;
			
		case COL_SLOPE_RD45:
			tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = temp_y & 0x0f;
			slope_type = SLOPE_45DEG_UP;

			break;
		case COL_SLOPE_LD45:
			if (gamemode == 6) break;
			tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0f - (0x10 - (temp_x & 0x0f))
			tmp4 = (-(temp_y & 0X0f) >> 1);

			slope_type = SLOPE_45DEG_DOWN;
			break;			

		case COL_SLOPE_RU45:
			if (currplayer_gravity) {
				tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
				tmp4 = temp_y & 0x0f;
				slope_type = SLOPE_45DEG_UP;
			}
			break;
		case COL_SLOPE_LU45:
			if (currplayer_gravity) {
				if (gamemode == 6) break;
				tmp7 = (temp_x & 0x0f) ^ 0x0f;	// = 0x0f - (0x10 - (temp_x & 0x0f))
				tmp4 = (-(temp_y & 0X0f) >> 1);
			}
			slope_type = SLOPE_45DEG_DOWN;
			break;			

		case COL_SLOPE_RD22_TOP:
			tmp7 = ((temp_x >> 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0e) | 0x1;

			slope_type = SLOPE_22DEG_UP;
			break;	
			
		case COL_SLOPE_RD22_BOT:
			tmp7 = ((temp_x >> 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = (temp_y) & 0x0f;
		
			slope_type = SLOPE_22DEG_UP;
			break;
		case COL_SLOPE_LD22_TOP:
			tmp7 = ((temp_x >> 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = 0;

			slope_type = SLOPE_22DEG_DOWN;
			slope_frames = (gamemode == 6 ? 3 : 1); //signal BG_COLL_R to not check stuff
			was_on_slope_counter = (gamemode == 6 ? 6 : 2);			
			break;	
	
		case COL_SLOPE_LD22_BOT:
			tmp7 = ((temp_x >> 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = 0;
		
			slope_type = SLOPE_22DEG_DOWN;
			slope_frames = (gamemode == 6 ? 3 : 1); //signal BG_COLL_R to not check stuff
			was_on_slope_counter = (gamemode == 6 ? 6 : 2);			
			break;
		case COL_SLOPE_RD66_TOP:
			if ((temp_x & 0x0f) < 0x08) return 0;
			tmp7 = (((temp_x & 0x07) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f);
			slope_type = SLOPE_66DEG_UP;

			break;	
		case COL_SLOPE_RD66_BOT:
			if ((temp_x & 0x0f) >= 0x08) return 1;
			tmp7 = (((temp_x & 0x0f) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = ((temp_y) & 0x0f);

			slope_type = SLOPE_66DEG_UP;
			break;	
		case COL_SLOPE_LD66_BOT:
			if ((temp_x & 0x0f) >= 0x08) return 1;
			tmp7 = (((temp_x & 0x07) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = 0;
			slope_type = SLOPE_66DEG_DOWN;
			slope_frames = (gamemode == 6 ? 3 : 1); //signal BG_COLL_R to not check stuff
			was_on_slope_counter = (gamemode == 6 ? 6 : 2);	
			break;	
		case COL_SLOPE_LD66_TOP:
			if ((temp_x & 0x0f) < 0x08) return 0;
			tmp7 = (((temp_x & 0x0f) << 1) & 0x0f) ^ 0x0f;	// = 0x0F - (temp_x & 0x0F)
			tmp4 = 0;

			slope_type = SLOPE_66DEG_DOWN;
			slope_frames = (gamemode == 6 ? 3 : 1); //signal BG_COLL_R to not check stuff
			was_on_slope_counter = (gamemode == 6 ? 6 : 2);	
			break;			

		default:
			return 0;
	}

	if ((uint8_t)(tmp4 + 3) >= tmp7) {
		tmp8 = tmp4 - tmp7 + (mini ? 2 : ((slope_type == SLOPE_66DEG_UP) ? 1 : 0));
		if (pad[controllingplayer] & PAD_A && gamemode != 6) {
			slope_frames = 0;
			slope_type = 0;
		} else {
			slope_frames = (gamemode == 6 ? 3 : 1); //signal BG_COLL_R to not check stuff
			was_on_slope_counter = (gamemode == 6 ? 6 : 2);
		}
		return 1;
	} else if (!was_on_slope_counter) {
		slope_type = 0;
	}
	
	return 0;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp2, tmp8
*/
char bg_coll_return_D () {
	tmp1 = bg_coll_U_D_checks() || bg_coll_mini_blocks();
	eject_D = tmp8;
	return tmp1;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp2, tmp8
*/
char bg_coll_return_U () {
	tmp1 = bg_coll_U_D_checks() || bg_coll_mini_blocks();
	eject_U = tmp8 | 0xf8;
	return tmp1;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp4, tmp7, tmp8
*/
char bg_coll_return_slope_D () {
	tmp1 = bg_coll_slope();
	eject_D = tmp8;
	return tmp1;
}

/*
	Clobbers:
	tmp1
	Recursively clobbers:
	tmp4, tmp7, tmp8
*/
char bg_coll_return_slope_U () {
	tmp1 = bg_coll_slope();
	eject_U = tmp8 | 0xf0;
	return tmp1;
}

/*
	Clobbers:
	tmp2, tmp4
	Recursively clobbers:
	tmp1, tmp2, tmp4, tmp7, tmp8
*/

#define COLL_CHECK_BOTTOM \
			tmp8 = (temp_y) & 0x0f; \
			bg_collision_sub(); \
			bg_coll_spikes(); \
			if (bg_coll_return_D()) return 1; 

#define COLL_CHECK_BOTTOM_NO_SPIKE \
			tmp8 = (temp_y) & 0x0f; \
			bg_collision_sub(); \
			if (bg_coll_return_D()) return 1; 

#define COLL_CHECK_TOP \
			tmp8 = (temp_y) & 0x0f; \
			bg_collision_sub(); \
			bg_coll_spikes(); \
			if (bg_coll_return_U()) return 1; 

#define COLL_CHECK_TOP_NO_SPIKE \
			tmp8 = (temp_y) & 0x0f; \
			bg_collision_sub(); \
			if (bg_coll_return_U()) return 1; 
			


char bg_coll_U() {
	
	// Slopes

	if (high_byte(currplayer_x) >= 0x10) {
		storeWordSeparately(
			add_scroll_y(
				Generic.y + 2 + (mini ? byte(0x10 - Generic.height) >> 1 : 0),
				scroll_y
			), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		for (tmp2 = 0; tmp2 < 2; tmp2++) {
			bg_collision_sub(); // do again but this time in the center of the cube

			// Clobbers 1, 4, 7, 8
			if(bg_coll_return_slope_U()) return 1;
			
			temp_x += Generic.width; // automatically only the low byte
		}			
	}

	if (currplayer_vel_y > 0x00) return 0;

	if (!slope_frames) {
		temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte
		
		storeWordSeparately(
			add_scroll_y(
				Generic.y + (mini ? byte(0x10 - Generic.height) >> 1 : 0),
				scroll_y
			), temp_y, temp_room);
		
		COLL_CHECK_TOP_NO_SPIKE
		
		temp_x += Generic.width >> 1; // automatically only the low byte

		COLL_CHECK_TOP

		temp_x += 0x10 - (Generic.width >> 1); // automatically only the low byte

		COLL_CHECK_TOP
	}
	return 0;
	
}

/*
	Clobbers:
	tmp2, tmp4
	Recursively clobbers:
	tmp1, tmp2, tmp4, tmp7, tmp8
*/
char bg_coll_D() {

	// Slopes
	if (high_byte(currplayer_x) >= 0x10) {
		storeWordSeparately(
			add_scroll_y(
				Generic.y + Generic.height - 2 + (mini ? byte(0x10 - Generic.height) >> 1 : 0), scroll_y
			), temp_y, temp_room);
		temp_x = Generic.x + low_word(scroll_x); // middle of the cube

		for (tmp2 = 0; tmp2 < 2; tmp2++) {
			bg_collision_sub(); // do again but this time in the center of the cube
			
			// Clobbers 1, 4, 7, 8
			if(bg_coll_return_slope_D()) return 1;
			temp_x += Generic.width; // automatically only the low byte
		}			
	}
	
	if (currplayer_vel_y < 0x00) return 0;

	if (!slope_frames) {
		// check 2 points on the right side
		temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

		storeWordSeparately(
			add_scroll_y(
				Generic.y + Generic.height + (mini ? byte(0x10 - Generic.height) >> 1 : 0),
				scroll_y
			), temp_y, temp_room);

		COLL_CHECK_BOTTOM_NO_SPIKE
		
		temp_x += Generic.width >> 1; // automatically only the low byte

		COLL_CHECK_BOTTOM

		temp_x += 0x10 - (Generic.width >> 1); // automatically only the low byte

		COLL_CHECK_BOTTOM
	}

	return 0;
}

/*
	Clobbers:
	tmp2
*/
void bg_coll_death() {


	// middle point collision to kill, since hitboxes don't exist

	temp_x = Generic.x + low_word(scroll_x) + (Generic.width >> 1)-1; // automatically only the low byte

	storeWordSeparately(
		add_scroll_y(
			Generic.y + (Generic.width >> 1),
			scroll_y
		), temp_y, temp_room);

	bg_collision_sub();
	

	if(!currplayer_gravity && collision == COL_BOTTOM) { }
	else if(currplayer_gravity && collision == COL_TOP) { }

	else if(collision >= COL_UP_LEFT && collision <= COL_TOP_RIGHT_BOTTOM_LEFT) {
		if (bg_coll_mini_blocks()) cube_data[currplayer] = 0x01; 
	}
	else {
		if (collision == COL_ALL && gamemode != 0x06) {  // wave
			if (currplayer_gravity) {
				if (currplayer_vel_y > 0) {
					cube_data[currplayer] = 0x01; 
				}
			} else {
				if (currplayer_vel_y < 0) {
					cube_data[currplayer] = 0x01; 
				}
			}

		}
		
	}

//	if(!DEBUG_MODE && cube_data[0] & 0x01) {
//		reset_level();
//	}
}

