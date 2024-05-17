#pragma code-name(push, "XCD_BANK_00")
#pragma data-name(push, "XCD_BANK_00")
#pragma rodata-name(push, "XCD_BANK_00")

const unsigned short speed_table[] = {
	CUBE_SPEED_X1, CUBE_SPEED_X05, CUBE_SPEED_X2, CUBE_SPEED_X3, CUBE_SPEED_X4
};


void x_movement(){
    // handle x

	old_x = currplayer_x;
	if (!spiderwalk) {
		if (!(options & platformer)) {
			currplayer_vel_x = speed_table[speed & 0x7F];
			currplayer_x += currplayer_vel_x;
		} else {
			currplayer_vel_x = speed_table[speed & 0x7F];
			// leave the col calls first so it executes and checks against spike collision
			if (!bg_coll_R() && (pad[currplayer] & PAD_RIGHT)) currplayer_x += currplayer_vel_x;
			if (!bg_coll_L() && pad[currplayer] & PAD_LEFT && currplayer_x > 0x1000) currplayer_x -= currplayer_vel_x;
		}

		if(currplayer_x > 0xf000) { // too far, don't wrap around
		if(old_x >= 0xf000){
		    currplayer_x = 0xf000; // max right
		} else{
		    currplayer_x = 0x0000; // max left
		}
			currplayer_vel_x = 0;
		} 
	}

	else if (spiderwalk & UP_WALK || spiderwalk & DOWN_WALK) {
			currplayer_vel_x = 0;
	}
	else if (spiderwalk & LEFT_WALK) {
			currplayer_vel_x = speed_table[speed & 0x7F];
			currplayer_x -= currplayer_vel_x;
	}


	Generic.x = high_byte(currplayer_x); // this is much faster than passing a pointer to player
	Generic.y = high_byte(currplayer_y);

	if (gamemode == 0x06) { // wave
		if (mini) {
			Generic.width = MINI_WAVE_WIDTH;
			Generic.height = MINI_WAVE_HEIGHT;
		} else {
			Generic.width = WAVE_WIDTH;
			Generic.height = WAVE_HEIGHT;
		}
	} else {
		if (!mini) {
			Generic.width = CUBE_WIDTH;
			Generic.height = CUBE_HEIGHT;
		} else {
			Generic.width = MINI_CUBE_WIDTH;
			Generic.height = MINI_CUBE_HEIGHT;
		}   
	}


	if (currplayer_y < 0x0600){
		cube_data[currplayer] |= 0x01;	//DIE if player goes too high
	}
	

	else if (!(pad[controllingplayer] & PAD_A)) cube_data[currplayer] &= 1;
}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
