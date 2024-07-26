#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")


void spider_movement(void){
// handle y

// currplayer_gravity
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){
	if (!dashing[currplayer]) {

		if(!currplayer_gravity){
			if(currplayer_vel_y > CUBE_MAX_FALLSPEED){
					switch (gravity_mod) {
						case 0: currplayer_vel_y += !mini ? -CUBE_GRAVITY : -MINI_CUBE_GRAVITY; break;
						case 1: currplayer_vel_y += !mini ? -CUBE_GRAVITY/3 : -MINI_CUBE_GRAVITY/3; break;
						case 2: currplayer_vel_y += !mini ? -CUBE_GRAVITY/2 : -MINI_CUBE_GRAVITY/2; break;
						case 3: currplayer_vel_y += !mini ? -CUBE_GRAVITY/3*2 : -MINI_CUBE_GRAVITY/3*2; break;
						case 4: currplayer_vel_y += !mini ? -CUBE_GRAVITY*2 : -MINI_CUBE_GRAVITY*2; break;
					};
				} else {
					switch (gravity_mod) {
						case 0: currplayer_vel_y += !mini ? CUBE_GRAVITY : MINI_CUBE_GRAVITY; break;
						case 1: currplayer_vel_y += !mini ? CUBE_GRAVITY/3 : MINI_CUBE_GRAVITY/3; break;
						case 2: currplayer_vel_y += !mini ? CUBE_GRAVITY/2 : MINI_CUBE_GRAVITY/2; break;
						case 3: currplayer_vel_y += !mini ? CUBE_GRAVITY/3*2 : MINI_CUBE_GRAVITY/3*2; break;
						case 4: currplayer_vel_y += !mini ? CUBE_GRAVITY*2 : MINI_CUBE_GRAVITY*2; break;
					};
				}
		}
		else{
			if(currplayer_vel_y < -CUBE_MAX_FALLSPEED){
				switch (gravity_mod) {
					case 0: currplayer_vel_y -= !mini ? -CUBE_GRAVITY : -MINI_CUBE_GRAVITY; break;
					case 1: currplayer_vel_y -= !mini ? -CUBE_GRAVITY/3 : -MINI_CUBE_GRAVITY/3; break;
					case 2: currplayer_vel_y -= !mini ? -CUBE_GRAVITY/2 : -MINI_CUBE_GRAVITY/2; break;
					case 3: currplayer_vel_y -= !mini ? -CUBE_GRAVITY/3*2 : -MINI_CUBE_GRAVITY/3*2; break;
					case 4: currplayer_vel_y -= !mini ? -CUBE_GRAVITY*2 : -MINI_CUBE_GRAVITY*2; break;
				};
			} else {
				switch (gravity_mod) {
					case 0: currplayer_vel_y -= !mini ? CUBE_GRAVITY : MINI_CUBE_GRAVITY; break;
					case 1: currplayer_vel_y -= !mini ? CUBE_GRAVITY/3 : MINI_CUBE_GRAVITY/3; break;
					case 2: currplayer_vel_y -= !mini ? CUBE_GRAVITY/2 : MINI_CUBE_GRAVITY/2; break;
					case 3: currplayer_vel_y -= !mini ? CUBE_GRAVITY/3*2 : MINI_CUBE_GRAVITY/3*2; break;
					case 4: currplayer_vel_y -= !mini ? CUBE_GRAVITY*2 : MINI_CUBE_GRAVITY*2; break;
				};
			}
		}
	
		currplayer_y += currplayer_vel_y;
	}
	else if (dashing[currplayer] == 2) { currplayer_vel_y = -currplayer_vel_x; currplayer_y += currplayer_vel_y; }
	else if (dashing[currplayer] == 3) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else if (dashing[currplayer] == 4) { currplayer_vel_y = currplayer_vel_x; currplayer_y -= currplayer_vel_y; }	
	else if (dashing[currplayer] == 5) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else currplayer_vel_y = 1;

	Generic.x = high_byte(currplayer_x);
	
	// this literally offsets the collision down 1 pixel for the vel reset to happen every frame instead of each other frame
	if (currplayer_gravity) {
		Generic.y = high_byte(currplayer_y) - 2;
	} else {
		Generic.y = high_byte(currplayer_y) + 1;
	}
	
	if(!currplayer_gravity){
		if(bg_coll_D()){ // check collision below
			high_byte(currplayer_y) -= eject_D;
			currplayer_vel_y = 0;

			if(pad_new[controllingplayer] & PAD_A) {
				currplayer_gravity = 1;
				do {
					high_byte(currplayer_y) -= 0x08;
					Generic.y = high_byte(currplayer_y); // the rest should be the same
				} while (!bg_coll_U());
				high_byte(currplayer_y) -= eject_U;
				currplayer_vel_y = 0;
			}
		}
	} else {
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) -= eject_U + 1;
			currplayer_vel_y = 0;

			if(pad_new[controllingplayer] & PAD_A) {
				currplayer_gravity = 0;
				do {
					high_byte(currplayer_y) += 0x08;
					Generic.y = high_byte(currplayer_y); // the rest should be the same
				} while (!bg_coll_D());

				high_byte(currplayer_y) -= eject_D;
				
				currplayer_vel_y = 0;


			}
		} 
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same

	if (currplayer_vel_y != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			uint8_store(cube_data, currplayer, cube_data[currplayer] | 0x02);
		}
	}
}	
/*
void spider_movement2(void){
// handle y

// currplayer_gravity
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){

	if(!mini){
		if(currplayer_gravity){
			if(currplayer_vel_y > CUBE_MAX_FALLSPEED){
				currplayer_vel_y = CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y += CUBE_GRAVITY;
		}
		else{
			if(currplayer_vel_y < -CUBE_MAX_FALLSPEED){
				currplayer_vel_y = -CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y -= CUBE_GRAVITY;
		}
	}
	else {
		if(currplayer_gravity){
			if(currplayer_vel_y > MINI_CUBE_MAX_FALLSPEED){
				currplayer_vel_y = MINI_CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y += MINI_CUBE_GRAVITY;
		}
		else{
			if(currplayer_vel_y < -MINI_CUBE_MAX_FALLSPEED){
				currplayer_vel_y = -MINI_CUBE_MAX_FALLSPEED;
			} else currplayer_vel_y -= MINI_CUBE_GRAVITY;
		}
	}		
	currplayer_y += currplayer_vel_y;
	currplayer_x = currplayer_x;
	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	
		if(currplayer_gravity){
			if(bg_coll_D() && !bg_coll_R()){ // check collision below
			    high_byte(currplayer_y) -= eject_D;
			}
			if(bg_coll_D())    currplayer_vel_y = 0;
			
		}
		if(!currplayer_gravity){
			if(bg_coll_U() && !bg_coll_R()){ // check collision above
				high_byte(currplayer_y) -= eject_U;
			}
			if(bg_coll_U())    currplayer_vel_y = 0;
		}

	

	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same

	if (currplayer_vel_y != 0){
		if(pad_new[controllingplayer] & PAD_A) {
			cube_data2 = 2;
		}
	}
	if ( currplayer_vel_y == 0 || currplayer_vel_y == CUBE_MAX_FALLSPEED || currplayer_vel_y == -CUBE_MAX_FALLSPEED ) {
		if (!twoplayer) {
			if (!currplayer_gravity) {
				if(pad_new[controllingplayer] & PAD_A) {
		//			currplayer_gravity = 1;
					cube_data2 = 0;
					while (!bg_coll_U()) {
						if (!mini) currplayer_y -= 0x700;
						else currplayer_y -= 0x400;
						Generic.y = high_byte(currplayer_y); // the rest should be the same
					}
					high_byte(currplayer_y) -= eject_U;
					currplayer_vel_y = 0;
					
				}
			}
			
			else {
				if(pad_new[controllingplayer] & PAD_A) {
		//			currplayer_gravity = 0;
					cube_data2 = 0;
					while (!bg_coll_D()) {
						if (!mini) currplayer_y += 0x700;
						else currplayer_y += 0x400;					
						Generic.y = high_byte(currplayer_y); // the rest should be the same
					}
					high_byte(currplayer_y) -= eject_D;
					currplayer_vel_y = 0;


				}
			}
		}
		else {
			if (!currplayer_gravity) {
				if(pad_new[controllingplayer] & PAD_A) {
		//			currplayer_gravity = 1;
					cube_data2 = 0;
					while (!bg_coll_U()) {
						if (!mini) currplayer_y -= 0x700;
						else currplayer_y -= 0x400;
						Generic.y = high_byte(currplayer_y); // the rest should be the same
					}
					high_byte(currplayer_y) -= eject_U;
					currplayer_vel_y = 0;
					
				}
			}
			
			else {
				if(pad_new[controllingplayer] & PAD_A) {
		//			currplayer_gravity = 0;
					cube_data2 = 0;
					while (!bg_coll_D()) {
						if (!mini) currplayer_y += 0x700;
						else currplayer_y += 0x400;					
						Generic.y = high_byte(currplayer_y); // the rest should be the same
					}
					high_byte(currplayer_y) -= eject_D;
					currplayer_vel_y = 0;


				}
			}
		}			
	}
}	
*/
#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
