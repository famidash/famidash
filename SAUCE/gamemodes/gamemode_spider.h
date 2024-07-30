#pragma code-name(push, "XCD_BANK_01")
#pragma data-name(push, "XCD_BANK_01")
#pragma rodata-name(push, "XCD_BANK_01")

void cube_vel_stuff();
void common_gravity_routine();
void spider_movement(void){
// handle y

// currplayer_gravity
	// currplayer_vel_y is signed
	//if(currplayer_vel_y < 0x400){
	fallspeed_big = CUBE_MAX_FALLSPEED;
	fallspeed_mini = MINI_CUBE_MAX_FALLSPEED;
	gravity_big = CUBE_GRAVITY;
	gravity_mini = MINI_CUBE_GRAVITY;

	common_gravity_routine();

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
					if (!dual) {
						if (currplayer_y < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
							tmp1 = MSB(0x4000 - currplayer_y);
							scroll_y -= tmp1;
							high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
						}
						while (scroll_y < 0x08) {
							++scroll_y;
							--high_byte(currplayer_y);
						}

						
						if (currplayer_y > 0xA000){ // change y scroll (upward)
							tmp1 = MSB(currplayer_y - 0xA000);
							scroll_y += tmp1;
							if (scroll_y <= 0xEF) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
						}
						if (scroll_y > 0xEF) scroll_y = 0xEF;
					}
					else {
						if (currplayer_y < 0x0700 && (scroll_y > 0x08)){ // change y scroll (upward)
							tmp1 = MSB(0x0700 - currplayer_y);
							scroll_y -= tmp1;
							high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
						}
						while (scroll_y < 0x08) {
							++scroll_y;
							--high_byte(currplayer_y);
						}

						
						if (currplayer_y > 0xF000){ // change y scroll (upward)
							tmp1 = MSB(currplayer_y - 0xF000);
							scroll_y += tmp1;
							if (scroll_y <= 0xEF) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
						}
						if (scroll_y > 0xEF) scroll_y = 0xEF;
					}
					set_scroll_y(scroll_y);
					if (currplayer_y < 0x0600 && scroll_y == 0x08){
						uint8_store(cube_data, currplayer, cube_data[currplayer] | 0x01);	//DIE if player goes too high
						break;
					}
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
					if (!dual) {
						if (currplayer_y < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
							tmp1 = MSB(0x4000 - currplayer_y);
							scroll_y -= tmp1;
							high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
						}
						while (scroll_y < 0x08) {
							++scroll_y;
							--high_byte(currplayer_y);
						}

						
						if (currplayer_y > 0xA000){ // change y scroll (upward)
							tmp1 = MSB(currplayer_y - 0xA000);
							scroll_y += tmp1;
							if (scroll_y <= 0xEF) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
						}
						if (scroll_y > 0xEF) scroll_y = 0xEF;
					}
					else {
						if (currplayer_y < 0x0700 && (scroll_y > 0x08)){ // change y scroll (upward)
							tmp1 = MSB(0x0700 - currplayer_y);
							scroll_y -= tmp1;
							high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
						}
						while (scroll_y < 0x08) {
							++scroll_y;
							--high_byte(currplayer_y);
						}

						
						if (currplayer_y > 0xF000){ // change y scroll (upward)
							tmp1 = MSB(currplayer_y - 0xF000);
							scroll_y += tmp1;
							if (scroll_y <= 0xEF) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
						}
						if (scroll_y > 0xEF) scroll_y = 0xEF;
					}
					set_scroll_y(scroll_y);
					
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
