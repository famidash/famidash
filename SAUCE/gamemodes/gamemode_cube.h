#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")
void x_movement_coll();
void common_gravity_routine();
void cube_eject();
void cube_movement(void){
// handle y

// gravity[currplayer]
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){

	if ((pad_new[controllingplayer] & PAD_A) && currplayer_vel_y != 0) uint8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);

	fallspeed_big = CUBE_MAX_FALLSPEED;
	fallspeed_mini = MINI_CUBE_MAX_FALLSPEED;
	gravity_big = CUBE_GRAVITY;
	gravity_mini = MINI_CUBE_GRAVITY;
	common_gravity_routine();

	



	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	
	
	if(!currplayer_gravity || (currplayer_gravity && hblocked[currplayer]) || (currplayer_gravity && fblocked[currplayer])){
		if(bg_coll_D()){ // check collision below
			high_byte(currplayer_y) -= eject_D;
			low_byte(currplayer_y) = 0;
			currplayer_vel_y = 0;
			if (fblocked[currplayer]) currplayer_gravity = 0;
		}
	} if (currplayer_gravity || (!currplayer_gravity && hblocked[currplayer]) || (!currplayer_gravity && fblocked[currplayer])) {
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) -= eject_U;
			low_byte(currplayer_y) = 0;
			currplayer_vel_y = 0;
			if (fblocked[currplayer]) currplayer_gravity = 1;			
		}
	}
	

	if (bigboi) {
		Generic.x += 15;

		cube_eject();

		Generic.y -= 15;

		cube_eject();
		
		Generic.x -= 15;
		
		cube_eject();
	}

	else {
		if (longmode) {

			Generic.x += 15;
			
			cube_eject();
		}
		
		if (tallmode) {
			Generic.x = high_byte(currplayer_x);
			Generic.y -= 15;
			
			cube_eject();
		}		
	}	
	// check collision down a little lower than CUBE
	Generic.x = high_byte(currplayer_x); // the rest should be the same
	Generic.y = high_byte(currplayer_y); // the rest should be the same

//	if (currplayer_vel_y != 0){
//		if(pad_new[controllingplayer] & PAD_A) {
//			cube_data[currplayer] |= 2;
//		}
//	}

	if ((gamemode == 0 && currplayer_vel_y == 0 && dashing[currplayer] == 0) || (gamemode == 0 && (kandokidshack == 9 && dashing[currplayer] == 0)) || gamemode == 8){		//cube
		//if(bg_coll_D2()) {
			uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);				
			if (orbed[currplayer]) {
				if (!(pad[controllingplayer] & PAD_A)) orbed[currplayer] = 0;
			}
			if (gamemode == 8 && currplayer_vel_y == 0) ninjajumps[currplayer] = 3; //ninja jump reset
			if(pad[controllingplayer] & PAD_A && (!jblocked[currplayer] && !fblocked[currplayer] && !hblocked[currplayer] && !kandokidshack && gamemode == 0)) {			//no jblock - hold A to buffer jump
				if (!orbed[currplayer]) {
					if (!currplayer_gravity) {
						if (!mini) currplayer_vel_y = JUMP_VEL; // JUMP
						else currplayer_vel_y = MINI_JUMP_VEL; // JUMP
					}
					else {
						if (!mini) currplayer_vel_y = JUMP_VEL^0xFFFF; // JUMP
						else currplayer_vel_y = MINI_JUMP_VEL^0xFFFF; // JUMP
					}
				}
			
			}
			else if(pad_new[controllingplayer] & PAD_A && (jblocked[currplayer] || fblocked[currplayer] || kandokidshack || (gamemode == 8 && ninjajumps[currplayer]))) {		//jblock making you release and press A again to jump
				if (!currplayer_gravity) {
					if (!mini) currplayer_vel_y = JUMP_VEL; // JUMP
					else currplayer_vel_y = MINI_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) currplayer_vel_y = JUMP_VEL^0xFFFF; // JUMP
					else currplayer_vel_y = MINI_JUMP_VEL^0xFFFF; // JUMP
				}
				if (gamemode == 8) { ninjajumps[currplayer]--; }
			
			}
	}
	else if ((gamemode == 4 && !retro_mode && (currplayer_vel_y == 0) && !hblocked[currplayer] && dashing[currplayer] == 0) || (gamemode == 4 && dashing[currplayer] == 0 && kandokidshack == 9)){		//robot
		uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);				
		if(pad_new[controllingplayer] & PAD_A) {
			if (!currplayer_gravity) {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
			}
			robotjumptime[currplayer] = ROBOT_JUMP_TIME;
			robotjumpframe[0] = 1;
		}
	}
	
	else if (gamemode == 4 && retro_mode && (currplayer_vel_y == 0) && !hblocked[currplayer] && dashing[currplayer] == 0){		//jim
		uint8_store(cube_data, currplayer, cube_data[currplayer] & 1);				
		if(pad[controllingplayer] & PAD_A && !jblocked[currplayer]) {
			if (!currplayer_gravity) {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
			}
			robotjumptime[currplayer] = ROBOT_JUMP_TIME;
			robotjumpframe[0] = 1;
		}
		else if(pad_new[controllingplayer] & PAD_A && jblocked[currplayer]) {
			if (!currplayer_gravity) {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL; // JUMP
			}
			else {
				if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				else currplayer_vel_y = MINI_ROBOT_JUMP_VEL^0xFFFF; // JUMP
			}
			robotjumptime[currplayer] = ROBOT_JUMP_TIME;
			robotjumpframe[0] = 1;
		}
	}
	
	else if (gamemode == 4 && robotjumptime[currplayer] && !hblocked[currplayer]) {
			cube_data[currplayer] = 0;
			if (robotjumptime[currplayer]) uint8_dec(robotjumptime, currplayer); 
			if(pad[controllingplayer] & PAD_A && !jblocked[currplayer]) {
				if (robotjumpframe[0]) robotjumpframe[0]++;
				if ( robotjumpframe[0] > 3 ) robotjumpframe[0] = 3;
				if (!currplayer_gravity) {
					if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
					else currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
			}	
			else if(pad_new[controllingplayer] & PAD_A && jblocked[currplayer]) {
				if (robotjumpframe[0]) robotjumpframe[0]++;
				if ( robotjumpframe[0] > 3 ) robotjumpframe[0] = 3;
				if (!currplayer_gravity) {
					if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
					else currplayer_vel_y = ROBOT_JUMP_VEL; // JUMP
				}
				else {
					if (!mini) currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
					else currplayer_vel_y = ROBOT_JUMP_VEL^0xFFFF; // JUMP
				}
			}
			else { robotjumptime[currplayer] = 0; robotjumpframe[0] = 0; }
	}
	else if (gamemode == 4 && currplayer_vel_y != 0){		
			robotjumpframe[0] = 3;
	}
	fblocked[currplayer] = 0;
	hblocked[currplayer] = 0;
	jblocked[currplayer] = 0;
//jim's shit
	if (retro_mode) {
		if (pad_new[currplayer] & PAD_B && !has_practice_point) {
			for (tmp9 = 0; tmp9 < MAX_FIREBALLS; tmp9++) {
				if (!jimsheatballalive[tmp9]) {
					jimsheatballalive[tmp9] = 1;
					if (pad[controllingplayer] & PAD_UP) jimsheatball_vel_y[tmp9] = (JIMSHEATBALL_JUMP_VEL / 4) * 7;
					else jimsheatball_vel_y[tmp9] = JIMSHEATBALL_JUMP_VEL;
					jimsheatballx[tmp9] = high_byte(old_x);
					high_byte(jimsheatbally[tmp9]) = high_byte(player_y[0]);
					jimsheatballframe[tmp9] = 0;
					break;
				}
			}

		}
	}
// done with jims shit	
// jims heat bomb:
	player_x[currplayer] = currplayer_x;
	player_y[currplayer] = currplayer_y;
	player_vel_x[currplayer] = currplayer_vel_x;
	player_vel_y[currplayer] = currplayer_vel_y;
	player_gravity[currplayer] = currplayer_gravity;

	for (tmp9 = 0; tmp9 < MAX_FIREBALLS; tmp9++) {
	
		if (jimsheatballalive[tmp9]) {

				
			currplayer_x = jimsheatballx[tmp9];
			currplayer_y = jimsheatbally[tmp9];
			currplayer_vel_x = jimsheatball_vel_x[tmp9];
			currplayer_vel_y = jimsheatball_vel_y[tmp9];
			currplayer_gravity = 0;

			if(currplayer_vel_y > JIMSHEATBALL_MAX_FALLSPEED){
				currplayer_vel_y += -JIMSHEATBALL_GRAVITY;
			} else currplayer_vel_y += JIMSHEATBALL_GRAVITY;
			currplayer_y += currplayer_vel_y;
			
			Generic.x = high_byte(currplayer_x);
			Generic.y = high_byte(currplayer_y);
			

		//	x_movement_coll();
			if(bg_coll_D()){ // check collision below
			    high_byte(currplayer_y) -= eject_D;
			    low_byte(currplayer_y) = 0;
			    currplayer_vel_y = JIMSHEATBALL_JUMP_VEL;
			}

			if (cube_data[currplayer] & 1) { cube_data[currplayer] &= 2; }
			jimsheatballx[tmp9] = currplayer_x;
			jimsheatbally[tmp9] = currplayer_y;
			jimsheatball_vel_x[tmp9] = currplayer_vel_x;
			jimsheatball_vel_y[tmp9] = currplayer_vel_y;
		}	
	}
	currplayer_x = player_x[currplayer];
	currplayer_y = player_y[currplayer];
	currplayer_vel_x = player_vel_x[currplayer];
	currplayer_vel_y = player_vel_y[currplayer];
	currplayer_gravity = player_gravity[currplayer];
	
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
}	


void common_gravity_routine(void) {
	if (!dashing[currplayer]) {
		if(!currplayer_gravity ? (currplayer_vel_y > (!mini ? fallspeed_big : fallspeed_mini)) : (currplayer_vel_y < (!mini ? -fallspeed_big : -fallspeed_mini))){
				switch (gravity_mod) {
					case 0: currplayer_vel_y += !mini ? (!currplayer_gravity ? -gravity_big : gravity_big) : (!currplayer_gravity ? -gravity_mini : gravity_mini); break;
					case 1: currplayer_vel_y += !mini ? (!currplayer_gravity ? -gravity_big/3 : gravity_big/3) : (!currplayer_gravity ? -gravity_mini/3 : gravity_mini/3); break;
					case 2: currplayer_vel_y += !mini ? (!currplayer_gravity ? -gravity_big/2 : gravity_big/2) : (!currplayer_gravity ? -gravity_mini/2 : gravity_mini/2); break;
					case 3: currplayer_vel_y += !mini ? (!currplayer_gravity ? -gravity_big/3*2 : gravity_big/3*2) : (!currplayer_gravity ? -gravity_mini/3*2 : gravity_mini/3*2); break;
					case 4: currplayer_vel_y += !mini ? (!currplayer_gravity ? -gravity_big*2 : gravity_big*2) : (!currplayer_gravity ? -gravity_mini*2 : gravity_mini*2); break;
				};
		}
		else {
				switch (gravity_mod) {
					case 0: currplayer_vel_y += !mini ? (currplayer_gravity ? -gravity_big : gravity_big) : (currplayer_gravity ? -gravity_mini : gravity_mini); break;
					case 1: currplayer_vel_y += !mini ? (currplayer_gravity ? -gravity_big/3 : gravity_big/3) : (currplayer_gravity ? -gravity_mini/3 : gravity_mini/3); break;
					case 2: currplayer_vel_y += !mini ? (currplayer_gravity ? -gravity_big/2 : gravity_big/2) : (currplayer_gravity ? -gravity_mini/2 : gravity_mini/2); break;
					case 3: currplayer_vel_y += !mini ? (currplayer_gravity ? -gravity_big/3*2 : gravity_big/3*2) : (currplayer_gravity ? -gravity_mini/3*2 : gravity_mini/3*2); break;
					case 4: currplayer_vel_y += !mini ? (currplayer_gravity ? -gravity_big*2 : gravity_big*2) : (currplayer_gravity ? -gravity_mini*2 : gravity_mini*2); break;
				};
		}
		currplayer_y += currplayer_vel_y;
	}
	
	
	else if (dashing[currplayer] == 2) { currplayer_vel_y = -currplayer_vel_x; currplayer_y += currplayer_vel_y; }
	else if (dashing[currplayer] == 3) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else if (dashing[currplayer] == 4) { currplayer_vel_y = currplayer_vel_x; currplayer_y -= currplayer_vel_y; }	
	else if (dashing[currplayer] == 5) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else currplayer_vel_y = 1;
}


void cube_eject() {
		if(!currplayer_gravity || (currplayer_gravity && hblocked[currplayer]) || (currplayer_gravity && fblocked[currplayer])){
			if(bg_coll_D()){ // check collision below
				high_byte(currplayer_y) -= eject_D;
				low_byte(currplayer_y) = 0;
				currplayer_vel_y = 0;
				if (fblocked[currplayer]) currplayer_gravity = 0;
			}
		} if (currplayer_gravity || (!currplayer_gravity && hblocked[currplayer]) || (!currplayer_gravity && fblocked[currplayer])) {
			if(bg_coll_U()){ // check collision above
				high_byte(currplayer_y) -= eject_U;
				low_byte(currplayer_y) = 0;
				currplayer_vel_y = 0;
				if (fblocked[currplayer]) currplayer_gravity = 1;			
			}
		}	
}		


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
