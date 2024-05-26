/* 
	Gets the collision of the current tile
	Implemented in asm
*/
__fastcall__ char bg_collision_sub(void);

#define rpt_bg_col_sub() (__asm__("ldx #0\nLDY %v\nLDA %v,Y", collision, is_solid), __A__)

char bg_coll_L(void){
    // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

	tmp1 = Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : (Generic.height - 8));

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	tmp3 = bg_collision_sub();
	switch(tmp3) {
		case COL_BOTTOM:
			if (temp_y & 0x08) return 1;		// If Y pos inside block ≥ 8px
			break;
		case COL_TOP:
			if (!(temp_y & 0x08)) return 1;		// If Y pos inside block < 8px
			break;
		case COL_ALL:
			return 1;
		case COL_DEATH_LEFT:
			if (((temp_x & 0x0f) < 0x04)) cube_data[currplayer] = 1;		// If X pos inside block < 8px, die
			break;
		case COL_DEATH_RIGHT:
			if (((temp_x & 0x0f) >= 0x0c)) cube_data[currplayer] = 1;		// If X pos inside block ≥ 10px, die
			break;
		case COL_DEATH_TOP:
			if (!(temp_y & 0x08)) cube_data[currplayer] = 1;	// If Y pos inside block < 8px, die
			else return 0;										// else nothing
			break;
		case COL_DEATH_BOTTOM:
			if ((temp_y & 0x08)) cube_data[currplayer] = 1;	// If Y pos inside block ≥ 8px, die
			else return 0;									// else nothing
			break;
	}

    
    return 0;
}

char bg_coll_floor_spikes(void){ // used just for checking ground spikes on the floor
	temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

	tmp1 = Generic.y + (mini ? (byte(0x10 - Generic.height) >> 1) : 4);
	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	for (tmp8 = mini; tmp8 < 2; tmp8++) {
		tmp3 = bg_collision_sub();
		if(tmp3 == COL_DEATH_TOP) {
			if (!(temp_y & 0x08)) {								// If Y pos inside block < 8px, die
				tmp2 = temp_x & 0x0f;
				if (tmp2 < 0x0c) {								// If X pos even insider, die even more
					cube_data[currplayer] = 1;						
				}
			}													// else nothing
		} else if (tmp3 == COL_DEATH_BOTTOM) {
			if ((temp_y & 0x08)) {								// If Y pos inside block ≥ 8px, die
				tmp2 = temp_x & 0x0f;
				if (tmp2 < 0x0c) {								// If X pos even insider, die even more
					cube_data[currplayer] = 1;						
				}
			}								// else nothing
		}
		tmp1 = Generic.y + Generic.height - 4;
		storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);
	}

    return 0;
}
char bg_coll_R(void){
    // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x) + Generic.width; // automatically only the low byte

	tmp1 = Generic.y + (byte(0x10 - Generic.height) >> 1) + (mini ? 4 : (Generic.height >> 1));

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	tmp3 = bg_collision_sub();
	switch(tmp3) {
		case COL_BOTTOM:
			if (temp_y & 0x08) return 1;		// If Y pos inside block ≥ 8px
			break;
		case COL_TOP:
			if (!(temp_y & 0x08)) return 1;		// If Y pos inside block < 8px
			break;
		case COL_ALL:
			return 1;		
		case COL_DEATH_LEFT:
			if (((temp_x & 0x0f) < 0x04)) cube_data[currplayer] = 1;		// If X pos inside block < 8px, die
			break;
		case COL_DEATH_RIGHT:
			if (((temp_x & 0x0f) >= 0x0c)) cube_data[currplayer] = 1;		// If X pos inside block ≥ 10px, die
			break;
		case COL_DEATH_TOP:
			if ((temp_x & 0x0f) < 0x06) return 0;	// If X pos inside block < 6px, collide
			if (!(temp_y & 0x08)) cube_data[currplayer] = 1;	// If Y pos inside block < 8px, die
			else return 0;
			break;
		case COL_DEATH_BOTTOM:
			if ((temp_x & 0x0f) < 0x06) return 0;	// If X pos inside block < 6px, collide
			if ((temp_y & 0x08)) cube_data[currplayer] = 1;		// If Y pos inside block ≥ 8px, die
			else return 0;
			break;
	}

    
    return 0;
}


char common_checks(void) {
	switch(tmp3) {
		case COL_DEATH_LEFT:
			if ((temp_x & 0x0f) < 0x06) {
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x09) cube_data[currplayer] = 1;
			}
			break;
		case COL_DEATH_RIGHT:
			if ((temp_x & 0x0f) >= 0x0a) {
				tmp2 = temp_y & 0x0f;
				if (tmp2 >= 0x06 && tmp2 < 0x09) cube_data[currplayer] = 1;
			}
			break;
		case COL_FLOOR_CEIL:
			kandowavewalk = 1;
			return 1;
	}
	return 0;
}

char bg_coll_U(void){
	if (currplayer_vel_y > 0) return 0;
	
	temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

	tmp1 = Generic.y + (mini ? byte(0x10 - Generic.height) >> 1 : 0);
	
	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);
	eject_U = (temp_y) | 0xf0;	 
	
	
	for (tmp1 = 0; tmp1 < 2; tmp1++) {
		tmp3 = bg_collision_sub();
		switch (tmp3){
			case COL_ALL:
				return 1;
			case COL_TOP:
			case COL_DEATH_TOP:
				tmp2 = temp_y & 0x0f;	
				eject_U = (temp_y) | 0xf8;	 
				if (tmp2 < 0x08) {
					if (tmp3 == COL_DEATH_TOP) {
						if (tmp2 < 0x04) {
							tmp2 = temp_x & 0x0f;
					
							if (tmp2 >= 0x04 && tmp2 < 0x0c) {
								cube_data[currplayer] = 1;
							} else return 0;
						} else {
							return 0;
						}
					}
					return 1;
				}
				break;
			case COL_BOTTOM:
			case COL_DEATH_BOTTOM:
				tmp2 = temp_y & 0x0f;
				eject_U = (temp_y) | 0xf8;	 
				if (tmp2 >= 0x08) {
					if (tmp3 == COL_DEATH_BOTTOM) {
						if (tmp2 >= 0x0c) {
							tmp2 = temp_x & 0x0f;
					
							if (tmp2 >= 0x04 && tmp2 < 0x0c) {
								cube_data[currplayer] = 1;
							} else return 0;
						} else {
							return 0;
						}
					}
					return 1;
				}
				break;
		} 
		if (common_checks()) return 1;

		temp_x += Generic.width; // automatically only the low byte
	}	
	return 0;
	
}

char bg_coll_D(void){
	if (currplayer_vel_y < 0) return 0;
	 // check 2 points on the right side
	temp_x = Generic.x + low_word(scroll_x); // automatically only the low byte

	tmp1 = Generic.y + Generic.height + (mini ? byte(0x10 - Generic.height) >> 1 : 0);

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);
	eject_D = (temp_y) & 0x0f;

	for (tmp1 = 0; tmp1 < 2; tmp1++) {
		tmp3 = bg_collision_sub();
		switch (tmp3) {
			case COL_ALL:
				return 1;
			case COL_TOP:
			case COL_DEATH_TOP:
				tmp2 = temp_y & 0x0f;	
				eject_D = (temp_y) & 0x07;
				if (tmp2 < 0x08) {
					if (tmp3 == COL_DEATH_TOP) {
						if (tmp2 < 0x04) {
							tmp2 = temp_x & 0x0f;
					
							if (tmp2 >= 0x04 && tmp2 < 0x0c) {
								cube_data[currplayer] = 1;
							} else return 0;
						} else {
							return 0;
						}
					}
					return 1;
				}
				break;
			case COL_BOTTOM:
			case COL_DEATH_BOTTOM:
				tmp2 = temp_y & 0x0f;
				eject_D = (temp_y) & 0x07;
				if (tmp2 >= 0x08) {
					if (tmp3 == COL_DEATH_BOTTOM) {
						if (tmp2 >= 0x0c) {
							if (high_byte(currplayer_x) < 0x10) return 0;
							tmp2 = temp_x & 0x0f;
					
							if (tmp2 >= 0x04 && tmp2 < 0x0c) {
								cube_data[currplayer] = 1;
							} else return 0;
						} else {
							return 0;
						}
					}
					return 1;
				}
				break;
		} 
		if (common_checks()) return 1;

		temp_x += Generic.width; // automatically only the low byte
	}	
	return 0;
}


void bg_coll_death(void) {


	// middle point collision to kill, since hitboxes don't exist

	temp_x = Generic.x + low_word(scroll_x) + (Generic.width >> 1)-1; // automatically only the low byte

	tmp1 = Generic.y + (Generic.width >> 1);

	storeWordSeparately(add_scroll_y(tmp1, scroll_y), temp_y, temp_room);

	tmp3 = bg_collision_sub();
	if (tmp3 == COL_DEATH_TOP) {
		tmp2 = temp_y & 0x0f;	
		eject_D = (temp_y) & 0x07;
		if (tmp2 < 0x04) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 > 0x06 && tmp2 < 0x0a)
				cube_data[currplayer] = 1;
		}
	} else if (tmp3 == COL_DEATH_BOTTOM) {
		tmp2 = temp_y & 0x0f;
		eject_D = (temp_y) & 0x07;
		if (tmp2 >= 0x0c) {
			tmp2 = temp_x & 0x0f;
			if (tmp2 > 0x06 && tmp2 < 0x0a)
				cube_data[currplayer] = 1;
		}
	}
	else if(!currplayer_gravity && tmp3 == COL_BOTTOM) { }
	else if(currplayer_gravity && tmp3 == COL_TOP) { }
	else if(tmp3 == COL_DEATH_RIGHT || tmp3 == COL_DEATH_LEFT) { }
	else {
		if (tmp3 == COL_ALL && gamemode != 0x06) {  // wave
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
		else if(tmp3 == COL_DEATH) cube_data[currplayer] = 0x01;
	}

	if(!DEBUG_MODE && cube_data[0] & 0x01) {
		reset_level();
	}
}