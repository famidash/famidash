#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void ball_movement(void){
// handle y

	// currplayer_gravity
	// currplayer_vel_y is signed

	if ((pad_new[controllingplayer] & PAD_A) && currplayer_vel_y != 0) uint8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);

	if (gamemode == 7) {
		max_fallspeed_big = SWING_MAX_FALLSPEED;
		max_fallspeed_mini = MINI_SWING_MAX_FALLSPEED;
		gravity_big = SWING_GRAVITY;
		gravity_mini = MINI_SWING_GRAVITY;

		common_gravity_routine();
	}
	
	else {		


		max_fallspeed_big = BALL_MAX_FALLSPEED;
		max_fallspeed_mini = MINI_BALL_MAX_FALLSPEED;
		gravity_big = BALL_GRAVITY;
		gravity_mini = MINI_BALL_GRAVITY;

		common_gravity_routine();
	}
	
	Generic.x = high_byte(currplayer_x);

	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 1;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}

	if (pad_new[controllingplayer] & PAD_A) uint8_store(cube_data, currplayer, cube_data[currplayer] | 2);	

	if(high_byte(currplayer_vel_y) & 0x80){
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U;
			currplayer_vel_y = 0;
			uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);			//fix for orb
		}
	}
	else{
		if(bg_coll_D()){ // check collision below
		    high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D;
		    currplayer_vel_y = 0;
			uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);		    //fix for orb
		}
	}



	if (gamemode == 2) {
		if ((pad[controllingplayer] & PAD_A) && (kandotemp2[currplayer] == 0) && currplayer_vel_y == 0){
			currplayer_gravity ^= 0x01;
			kandotemp2[currplayer] = 1;
			switch (currplayer_gravity){
				case 0x00: currplayer_vel_y = 0x100; break;
				case 0x01: currplayer_vel_y = -0x100; break;
			}
			bg_coll_floor_spikes();
		}
		if(kandotemp2[currplayer] == 1){
			if (!(pad[controllingplayer] & PAD_A)){
				uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);
				kandotemp2[currplayer] = 0;			
			}
		}
	}
	else {
		if ((pad_new[controllingplayer] & PAD_A)){
			currplayer_gravity ^= 0x01;
			bg_coll_floor_spikes();
		}
	}		

}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
