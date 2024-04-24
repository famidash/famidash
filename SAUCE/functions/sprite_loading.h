//attempt to comment
#define CUBE_MODE 				0X00
#define SHIP_MODE 				0X01
#define BALL_MODE 				0X02
#define UFO_MODE 				0X03
#define ROBOT_MODE 				0X04
#define BLUE_ORB 				0X05
#define PINK_ORB 				0X06
#define COIN1 					0X07
#define GRAVITY_DOWN_PORTAL 			0X08
#define GRAVITY_UP_PORTAL 			0X09
#define YELLOW_PAD_DOWN 			0X0A
#define YELLOW_ORB 				0X0B
#define YELLOW_PAD_UP	 			0X0C
#define GRAVITY_PAD_DOWN 			0X0D
#define GRAVITY_PAD_UP	 			0X0E
#define LEVEL_END_TRIGGER 			0X0F
#define GRAVITY_DOWN_UPWARDS_PORTAL 		0X10
#define GRAVITY_DOWN_DOWNWARDS_PORTAL 		0X11
#define GRAVITY_UP_UPWARDS_PORTAL 		0X12
#define GRAVITY_UP_DOWNWARDS_PORTAL 		0X13
#define SPEED_05_PORTAL		 		0X14
#define SPEED_10_PORTAL		 		0X15
#define SPEED_20_PORTAL		 		0X16
#define SPIDER_MODE		 		0X17
#define MINI_PORTAL		 		0X18
#define GROWTH_PORTAL		 		0X19
#define COIN2					0X1A
#define COIN3					0X1B
#define COINGOTTEN1				0X1C
#define COINGOTTEN2				0X1D
#define COINGOTTEN3				0X1E
#define YELLOW_ORB_BIGGER			0X1F
#define SPEED_30_PORTAL				0X20
#define SPEED_40_PORTAL				0X21
#define DUAL_PORTAL				0X22
#define SINGLE_PORTAL				0X23
#define GRAVITY_UP_INVISIBLE_PORTAL		0XFB
#define GRAVITY_DOWN_INVISIBLE_PORTAL		0XFC
#define GRAVITY_PAD_DOWN_INVISIBLE		0XFD
#define GRAVITY_PAD_UP_INVISIBLE		0XFE
#define NOSPRITE				0XFF

extern void load_next_sprite(void);

extern void check_spr_objects(void);





void init_sprites(void){
	// Setting up pointers is already done by init_rld()
    mmc3_set_prg_bank_1(sprite_data_bank);

	for (tmp4 = max_loaded_sprites-1; tmp4 != 0; --tmp4) activesprites_type[tmp4] = 0xFF;

    spr_index = 0;
    while (spr_index < max_loaded_sprites){
        if (sprite_data[0] == TURN_OFF) break;
        load_next_sprite();
		if (sprite_data[1] != 0) activesprites_active[spr_index] = 0;
    }
}

__fastcall__ char sprite_height_lookup(){

	#define type tmp4

    if (!mini) {
		switch(type) {
			case YELLOW_ORB:
			case YELLOW_ORB_BIGGER:
			case BLUE_ORB:
			case PINK_ORB:
				return 0x0f;
				
		}
	}

    else {
		switch(type) {
			case YELLOW_ORB:
			case BLUE_ORB:
			case PINK_ORB:
				return 0x17;
				
		}
	}

    if ((type >= 0x80) && (type < 0xF0)){                //COLOR TRIGGERS ON LOADING    was type & 0x30 and tmp2 = (type & 0x3f)-10 for spots 0x10-0x70
		tmp2 = (type & 0x3F);                        
		if (type >= 0xC0){
		    pal_col(6, tmp2);
		    if (tmp2-0x10 & 0xC0) { 
			pal_col(5, 0x0f); 
			activesprites_type[index] = 0xFF; 
		    } else { 
			pal_col(5, (tmp2-0x10)); 
			activesprites_type[index] = 0xFF; 
		    }
		} else {
		    pal_col(0, tmp2);
		    if (tmp2-0x10 & 0xC0) { 
			pal_col(1, 0x0f); 
			activesprites_type[index] = 0xFF; 
		    } else { 
			pal_col(1, (tmp2-0x10)); 
			activesprites_type[index] = 0xFF;
		    }
		}
		return 0x00;
    }

	if (type >= CUBE_MODE && type <= ROBOT_MODE) return 0x2F;	// Portals
	else if (type >= COINGOTTEN1 && type <= COINGOTTEN3) return 0x17;	// Coin
	else if (
		(type >= SPEED_05_PORTAL && type <= SPEED_20_PORTAL) || // Speed portals
		(type >= GRAVITY_DOWN_UPWARDS_PORTAL && type <= GRAVITY_UP_DOWNWARDS_PORTAL))	// Gravity portals
		return 0x1F;	

	switch(type) {
		case NOSPRITE:
			return 0;
		case GRAVITY_PAD_DOWN_INVISIBLE:
		case GRAVITY_PAD_UP_INVISIBLE:
			return 0x07;
		case GRAVITY_UP_INVISIBLE_PORTAL:
		case GRAVITY_DOWN_INVISIBLE_PORTAL:
			return 0x0F;
		case SPIDER_MODE:
		case SINGLE_PORTAL:
		case DUAL_PORTAL:
		case GRAVITY_DOWN_PORTAL:
		case GRAVITY_UP_PORTAL:
		case MINI_PORTAL:
		case GROWTH_PORTAL:
			return 0x2f;
		case COIN1:
			if (coin1_obtained[level]) {
				activesprites_type[index] = COINGOTTEN1;
			}
			return 0x17; 
		case COIN2:
			if (coin2_obtained[level]) {
				activesprites_type[index] = COINGOTTEN2;
			}
			return 0x17; 
		case COIN3:
			if (coin3_obtained[level]) {
				activesprites_type[index] = COINGOTTEN3;
			}
			return 0x17; 
		case SPEED_30_PORTAL:
		case SPEED_40_PORTAL:
			return 0x1F;
		case YELLOW_PAD_DOWN:
		case YELLOW_PAD_UP:
			return 0x02;
		case GRAVITY_PAD_DOWN:
		case GRAVITY_PAD_UP:
			return 0x04;
		case LEVEL_END_TRIGGER:
			gameState = 0x03; 
        	pal_fade_to(4,0);


	}
    return 0;

	#undef type
}



#pragma code-name(push, "XCD_BANK_00")
#pragma data-name(push, "XCD_BANK_00")
#pragma rodata-name(push, "XCD_BANK_00")
void sprite_collide_lookup(){
    // portals
    if (tmp4 == NOSPRITE) { }
    
    else if (tmp4 <= 4) { gamemode = tmp4; robotjumptime[currplayer] = 0; }			//game mode portals
    else if (tmp4 == SPIDER_MODE) gamemode = 0x05; 			//game mode portals
    
    
    else if (tmp4 == YELLOW_ORB) {		//yellow orb
		if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
			if (cube_data[currplayer] == 2) {					
				cube_data[currplayer] &= 0x01;
				if (!mini) { if (player_gravity[currplayer]) player_vel_y[currplayer] = ORB_HEIGHT_YELLOW^0xFFFF; else player_vel_y[currplayer] = ORB_HEIGHT_YELLOW; }
				else { if (player_gravity[currplayer]) player_vel_y[currplayer] = ORB_HEIGHT_YELLOW_UPSIDE^0xFFFF; else player_vel_y[currplayer] = ORB_HEIGHT_YELLOW_MINI; }
			}
		}
		else if (gamemode == SHIP_MODE || gamemode == UFO_MODE) {
			if (pad_new[controllingplayer] & PAD_A) {	
				cube_data[currplayer] &= 0x01;
				if (player_gravity[currplayer]) player_vel_y[currplayer] = ORB_HEIGHT_YELLOW^0xFFFF; else player_vel_y[currplayer] = ORB_HEIGHT_YELLOW;
			}
		}
    }    
    else if (tmp4 == YELLOW_ORB_BIGGER) {		//yellow orb
	if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
		if (cube_data[currplayer] == 2) {					
			cube_data[currplayer] &= 0x01;
			if (!mini) { if (player_gravity[currplayer]) player_vel_y[currplayer] = ORB_HEIGHT_YELLOW^0xFFFF; else player_vel_y[currplayer] = ORB_HEIGHT_YELLOW; }
			else { if (player_gravity[currplayer]) player_vel_y[currplayer] = ORB_HEIGHT_YELLOW_UPSIDE2^0xFFFF; else player_vel_y[currplayer] = ORB_HEIGHT_YELLOW_UPSIDE2; }
		}
	}
	else if (gamemode == SHIP_MODE || gamemode == UFO_MODE) {
		if (pad_new[controllingplayer] & PAD_A) {	
			cube_data[currplayer] &= 0x01;
			if (player_gravity[currplayer]) player_vel_y[currplayer] = ORB_HEIGHT_YELLOW^0xFFFF; else player_vel_y[currplayer] = ORB_HEIGHT_YELLOW;
		}
	}
    }
    else if (tmp4 == COIN1 || tmp4 == COINGOTTEN1) {					//COIN
	    coins = coins | COIN_1;
//	    famistudio_sfx_play(sfx_click, 0);			//test sfx
	activesprites_type[index] = 0xFF;		//make COIN disappear here
    }

    else if (tmp4 == COIN2 || tmp4 == COINGOTTEN2) {					//COIN
	    coins = coins | COIN_2;
//	    famistudio_sfx_play(sfx_click, 0);			//test sfx
	activesprites_type[index] = 0xFF;		//make COIN disappear here
    }

    else if (tmp4 == COIN3 || tmp4 == COINGOTTEN3) {					//COIN
	    coins = coins | COIN_3;
//	    famistudio_sfx_play(sfx_click, 0);			//test sfx
	activesprites_type[index] = 0xFF;		//make COIN disappear here
    }

    else if (tmp4 == BLUE_ORB)  {				//blue orb
	if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE || gamemode == SPIDER_MODE) {
		if (cube_data[currplayer] == 2) {			
			cube_data[currplayer] &= 0x01;
			player_gravity[currplayer] ^= 0x01;
			if (gamemode != BALL_MODE) {
				if (!player_gravity[currplayer]) player_vel_y[currplayer] = PAD_HEIGHT_BLUE^0xFFFF;
				else player_vel_y[currplayer] = PAD_HEIGHT_BLUE;
			} else {
				if (!player_gravity[currplayer]) player_vel_y[currplayer] = ORB_BALL_HEIGHT_BLUE^0xFFFF;
				else player_vel_y[currplayer] = ORB_BALL_HEIGHT_BLUE;
			}
		}
	}
	else if (gamemode == SHIP_MODE || gamemode == UFO_MODE) {
		if (pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] &= 0x01;
			player_gravity[currplayer] ^= 0x01;
			if (!player_gravity[currplayer]) player_vel_y[currplayer] = PAD_HEIGHT_BLUE^0xFFFF;
			else player_vel_y[currplayer] = PAD_HEIGHT_BLUE;
		}
	} 
    }

	else if (tmp4 == SPEED_05_PORTAL) speed = 1;
	else if (tmp4 == SPEED_10_PORTAL) speed = 0;
	else if (tmp4 == SPEED_20_PORTAL) speed = 2;
	else if (tmp4 == SPEED_30_PORTAL) speed = 3;
	else if (tmp4 == SPEED_40_PORTAL) speed = 4;

    else if (tmp4 == PINK_ORB) {
	if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
		if (cube_data[currplayer] == 2) {					
			cube_data[currplayer] &= 0x01;
			if (player_gravity[currplayer]) player_vel_y[currplayer] = PAD_HEIGHT_PINK^0xFFFF; else player_vel_y[currplayer] = PAD_HEIGHT_PINK;
		}
	}
	else if (gamemode == SHIP_MODE || gamemode == UFO_MODE) {
		if (pad_new[controllingplayer] & PAD_A) {	
			cube_data[currplayer] &= 0x01;
			if (player_gravity[currplayer]) player_vel_y[currplayer] = PAD_HEIGHT_PINK^0xFFFF; else player_vel_y[currplayer] = PAD_HEIGHT_PINK;
		}
	}
    }
    else if (tmp4 == GRAVITY_DOWN_PORTAL || tmp4 == GRAVITY_DOWN_UPWARDS_PORTAL || tmp4 == GRAVITY_DOWN_DOWNWARDS_PORTAL || tmp4 == GRAVITY_DOWN_INVISIBLE_PORTAL) { 
	if (player_gravity[currplayer]) {
	    player_gravity[currplayer] = 0; 
	 //   if (player_vel_y[currplayer] > -0x0200) player_vel_y[currplayer] = -0x0200; 
	   // else 
		   if (player_vel_y[currplayer] < -0x0290) player_vel_y[currplayer] = -0x0290; 
	if (mini && tmp4 == GRAVITY_DOWN_PORTAL)  high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - eject_D - 3;
	}
    }
    else if (tmp4 == GRAVITY_UP_PORTAL || tmp4 == GRAVITY_UP_UPWARDS_PORTAL || tmp4 == GRAVITY_UP_DOWNWARDS_PORTAL || tmp4 == GRAVITY_UP_INVISIBLE_PORTAL ) { 
	if (!player_gravity[currplayer]) {
	    player_gravity[currplayer] = 1; 
	    //if (player_vel_y[currplayer] < 0x0200) player_vel_y[currplayer] = 0x0200; 
//	    else
		    if (player_vel_y[currplayer] > 0x0290) player_vel_y[currplayer] = 0x0290; 
	if (mini && tmp4 == GRAVITY_UP_PORTAL)  high_byte(player_y[currplayer]) = high_byte(player_y[currplayer]) - eject_U + 3;
	}
    }

    else if (tmp4 == YELLOW_PAD_DOWN || tmp4 == YELLOW_PAD_UP) {				//yellow pads
		if (gamemode == BALL_MODE) {
			if (!mini) {
				if (player_gravity[currplayer]) player_vel_y[currplayer] = PAD_HEIGHT_BALL_YELLOW^0xFFFF;
				else player_vel_y[currplayer] = PAD_HEIGHT_BALL_YELLOW;
			}
			else {
				if (player_gravity[currplayer]) player_vel_y[currplayer] = PAD_HEIGHT_YELLOW_MINI^0xFFFF;
				else player_vel_y[currplayer] = PAD_HEIGHT_YELLOW_MINI;
			}
		} else {
			if (!mini) {
				if (player_gravity[currplayer]) player_vel_y[currplayer] = PAD_HEIGHT_YELLOW^0xFFFF;
				else player_vel_y[currplayer] = PAD_HEIGHT_YELLOW;
			}
			else {
				if (player_gravity[currplayer]) player_vel_y[currplayer] = PAD_HEIGHT_YELLOW_MINI^0xFFFF;
				else player_vel_y[currplayer] = PAD_HEIGHT_YELLOW_MINI;
			}
		}
    } 
    else if (tmp4 == GRAVITY_PAD_DOWN || tmp4 == GRAVITY_PAD_DOWN_INVISIBLE) {			//gravity pads bottom
	    if (!player_gravity[currplayer]) { 
			player_gravity[currplayer] = 0x01;				//flip gravity
			player_vel_y[currplayer] = PAD_HEIGHT_BLUE;	
		}
    }
    else if (tmp4 == GRAVITY_PAD_UP || tmp4 == GRAVITY_PAD_UP_INVISIBLE) {			//gravity pads top
	    if (player_gravity[currplayer]) { 
			player_gravity[currplayer] = 0x00;				//flip gravity
			player_vel_y[currplayer] = PAD_HEIGHT_BLUE^0xFFFF;	
	    }
    }
//    else if (tmp4 == 0x0F) {
//        gameState = 0x03; 
//        pal_fade_to(4,0); 
//    }
    else if (tmp4 == MINI_PORTAL) mini = 1;
    else if (tmp4 == GROWTH_PORTAL) mini = 0;
    else if (tmp4 == DUAL_PORTAL) {
	    
	   dual = 1;
	    if (twoplayer) { player_gravity[1] = player_gravity[0] ^ 1; }
	else { player_x[1] = player_x[0]; player_y[1] = player_y[0]; player_gravity[1] = player_gravity[0] ^ 1; }
    }
    else if (tmp4 == SINGLE_PORTAL) {
	    if (!twoplayer) dual = 0;
	    else { player_gravity[1] = player_gravity[0]; }
    }
}



void sprite_collide(){

    Generic.x = high_byte(player_x[currplayer]) + 1;
    Generic.y = high_byte(player_y[currplayer]);

	if (!mini) {
    Generic.width = CUBE_WIDTH;
    Generic.height = CUBE_HEIGHT;
	}
	
	else {
    Generic.width = MINI_CUBE_WIDTH;
    Generic.height = MINI_CUBE_HEIGHT;
	}    
    Generic2.width = 0x0f;
    for (index = 0; index < max_loaded_sprites; ++index){
        tmp3 = activesprites_active[index];
        if (tmp3){
            tmp4 = activesprites_type[index];
            tmp2 = sprite_height_lookup();	// uses tmp4
            Generic2.height = tmp2;

            Generic2.x = activesprites_realx[index];
            Generic2.y = activesprites_realy[index];
            
            if (check_collision(&Generic, &Generic2)) {
                sprite_collide_lookup();
            }
        }
    }
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
