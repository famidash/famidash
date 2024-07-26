#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void ship_movement(void){
// handle y

// currplayer_gravity
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){
	if (!dashing[currplayer]) {
			if(!currplayer_gravity){
				if(currplayer_vel_y > SHIP_MAX_FALLSPEED){
					switch (gravity_mod) {
						case 0: currplayer_vel_y += !mini ? -SHIP_GRAVITY : -MINI_SHIP_GRAVITY; break;
						case 1: currplayer_vel_y += !mini ? -SHIP_GRAVITY/3 : -MINI_SHIP_GRAVITY/3; break;
						case 2: currplayer_vel_y += !mini ? -SHIP_GRAVITY/2 : -MINI_SHIP_GRAVITY/2; break;
						case 3: currplayer_vel_y += !mini ? -SHIP_GRAVITY/3*2 : -MINI_SHIP_GRAVITY/3*2; break;
						case 4: currplayer_vel_y += !mini ? -SHIP_GRAVITY*8/6 : -MINI_SHIP_GRAVITY*8/6; break;
					};
				} else {
					switch (gravity_mod) {
						case 0: currplayer_vel_y += !mini ? SHIP_GRAVITY : MINI_SHIP_GRAVITY; break;
						case 1: currplayer_vel_y += !mini ? SHIP_GRAVITY/3 : MINI_SHIP_GRAVITY/3; break;
						case 2: currplayer_vel_y += !mini ? SHIP_GRAVITY/2 : MINI_SHIP_GRAVITY/2; break;
						case 3: currplayer_vel_y += !mini ? SHIP_GRAVITY/3*2 : MINI_SHIP_GRAVITY/3*2; break;
						case 4: currplayer_vel_y += !mini ? SHIP_GRAVITY*8/6 : MINI_SHIP_GRAVITY*8/6; break;
					};
				}
			}
			else{
				if(currplayer_vel_y < -SHIP_MAX_FALLSPEED){
					switch (gravity_mod) {
						case 0: currplayer_vel_y -= !mini ? -SHIP_GRAVITY : -MINI_SHIP_GRAVITY; break;
						case 1: currplayer_vel_y -= !mini ? -SHIP_GRAVITY/3 : -MINI_SHIP_GRAVITY/3; break;
						case 2: currplayer_vel_y -= !mini ? -SHIP_GRAVITY/2 : -MINI_SHIP_GRAVITY/2; break;
						case 3: currplayer_vel_y -= !mini ? -SHIP_GRAVITY/3*2 : -MINI_SHIP_GRAVITY/3*2; break;
						case 4: currplayer_vel_y -= !mini ? -SHIP_GRAVITY*8/6 : -MINI_SHIP_GRAVITY*8/6; break;
					};
				} else {
					switch (gravity_mod) {
						case 0: currplayer_vel_y -= !mini ? SHIP_GRAVITY : MINI_SHIP_GRAVITY; break;
						case 1: currplayer_vel_y -= !mini ? SHIP_GRAVITY/3 : MINI_SHIP_GRAVITY/3; break;
						case 2: currplayer_vel_y -= !mini ? SHIP_GRAVITY/2 : MINI_SHIP_GRAVITY/2; break;
						case 3: currplayer_vel_y -= !mini ? SHIP_GRAVITY/3*2 : MINI_SHIP_GRAVITY/3*2; break;
						case 4: currplayer_vel_y -= !mini ? SHIP_GRAVITY*8/6 : MINI_SHIP_GRAVITY*8/6; break;
					};
				}
			}
		if(currplayer_vel_y > (!mini ? SHIP_MAX_FALLSPEED : MINI_SHIP_MAX_FALLSPEED)) currplayer_vel_y = (!mini ? SHIP_MAX_FALLSPEED : MINI_SHIP_MAX_FALLSPEED);
		if(currplayer_vel_y < (!mini ? -SHIP_MAX_FALLSPEED : -MINI_SHIP_MAX_FALLSPEED)) currplayer_vel_y = (!mini ? -SHIP_MAX_FALLSPEED : -MINI_SHIP_MAX_FALLSPEED);
		currplayer_y += currplayer_vel_y;
	}	
	else if (dashing[currplayer] == 2) { currplayer_vel_y = -currplayer_vel_x; currplayer_y += currplayer_vel_y; }
	else if (dashing[currplayer] == 3) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else if (dashing[currplayer] == 4) { currplayer_vel_y = currplayer_vel_x; currplayer_y -= currplayer_vel_y; }	
	else if (dashing[currplayer] == 5) { currplayer_vel_y = currplayer_vel_x; currplayer_y += currplayer_vel_y; }	
	else currplayer_vel_y = 1;

	Generic.x = high_byte(currplayer_x);
	Generic.y = high_byte(currplayer_y);
	if (mini) {
		if (high_byte(currplayer_vel_y)) Generic.y -= 1;
		else Generic.y += 1;
	}
	
	
	if(high_byte(currplayer_vel_y) & 0x80){
		if(bg_coll_U()){ // check collision above
			high_byte(currplayer_y) = high_byte(currplayer_y) - eject_U - 1;
			currplayer_vel_y = 0;
		}
	}
	else{
		if(bg_coll_D()){ // check collision below
		    high_byte(currplayer_y) = high_byte(currplayer_y) - eject_D + 1;
		    currplayer_vel_y = 0;
		}
	}

	// check collision down a little lower than CUBE
	Generic.y = high_byte(currplayer_y); // the rest should be the same
	

	if(pad[controllingplayer] & PAD_A) {
		if (!mini) {
			if (!currplayer_gravity){
			    currplayer_vel_y -= SHIP_GRAVITY<<1;
				} else {
			    currplayer_vel_y += SHIP_GRAVITY<<1;
			}
		}
		else {
			if (!currplayer_gravity){
			    currplayer_vel_y -= MINI_SHIP_GRAVITY<<1;
				} else {
			    currplayer_vel_y += MINI_SHIP_GRAVITY<<1;
			}
		}
	}	
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
