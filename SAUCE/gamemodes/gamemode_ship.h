#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void ship_movement(void){
// handle y

// currplayer_gravity
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){
	if(!mini) {
		if(!currplayer_gravity) {
			currplayer_vel_y += SHIP_GRAVITY;
		}
		else {
			currplayer_vel_y -= SHIP_GRAVITY;
		}
		if(currplayer_vel_y > SHIP_MAX_FALLSPEED) currplayer_vel_y = SHIP_MAX_FALLSPEED;
		if(currplayer_vel_y < -SHIP_MAX_FALLSPEED) currplayer_vel_y = -SHIP_MAX_FALLSPEED;

	}
	else {
		if(!currplayer_gravity) {
			currplayer_vel_y += MINI_SHIP_GRAVITY;
		}
		else {
			currplayer_vel_y -= MINI_SHIP_GRAVITY;
		}
		if(currplayer_vel_y > MINI_SHIP_MAX_FALLSPEED) currplayer_vel_y = MINI_SHIP_MAX_FALLSPEED;
		if(currplayer_vel_y < -MINI_SHIP_MAX_FALLSPEED) currplayer_vel_y = -MINI_SHIP_MAX_FALLSPEED;
	}
		
		

	currplayer_y += currplayer_vel_y;
	
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
