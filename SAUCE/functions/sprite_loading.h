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
#define WAVE_MODE				0X24
#define PINK_PAD_DOWN				0X25
#define PINK_PAD_UP				0X26
#define GREEN_ORB				0X27
#define RED_ORB					0X28
#define GRAVITY_UP_INVISIBLE_PORTAL		0XFB
#define GRAVITY_DOWN_INVISIBLE_PORTAL		0XFC
#define GRAVITY_PAD_DOWN_INVISIBLE		0XFD
#define GRAVITY_PAD_UP_INVISIBLE		0XFE
#define NOSPRITE				0XFF

extern void load_next_sprite(void);

extern void check_spr_objects(void);





void maketmp2(){
    tmp2 = rand8();
    if (color3 == 0x0D || color3 == 0x0E ) color3 = 0x0C;
    if (color3 == 0x1D || color3 == 0x1E || color3 == 0x1F ) color3 = 0x1C;
    if (color3 == 0x2E || color3 == 0x2F ) color3 = 0x2C;			
    if (color3 == 0x3E || color3 == 0x3F ) color3 = 0x2C;			
    return;
}


void init_sprites(void){
    // Setting up pointers is already done by init_rld()
    mmc3_set_prg_bank_1(sprite_data_bank);

    for (tmp4 = max_loaded_sprites-1; tmp4 != 0; --tmp4) activesprites_type[tmp4] = 0xFF;

    spr_index = 0;
    do {
        if (sprite_data[0] == TURN_OFF) break;
        load_next_sprite();
        if (idx16_hi_NOC(activesprites_x, spr_index) != 0) activesprites_active[spr_index] = 0;
    } while (spr_index != 0);
}

__fastcall__ char sprite_height_lookup(){

    #define type tmp4

    switch(type) {
        case YELLOW_ORB:
        case YELLOW_ORB_BIGGER:
        case BLUE_ORB:
        case PINK_ORB:
        case GREEN_ORB:
        case RED_ORB:
            return 0x0f;
            
    }
/*			color fading code
    if ((type >= 0x80) && (type < 0xF0)){                //COLOR TRIGGERS ON LOADING    was type & 0x30 and tmp2 = (type & 0x3f)-10 for spots 0x10-0x70
        if (!discomode) tmp2 = (type & 0x3F);                        
        else { 
            return 0x00;
        }
        tmp3 = (tmp2-0x10 & 0xC0) ? 0x0f : (tmp2-0x10);
        if (type >= 0xC0) {
            original_gnd_palette_idx_0 = 5;
            original_gnd_palette_idx_1 = 6;
            original_gnd_palette_color_0 = PAL_BUF[5];
            original_gnd_palette_color_1 = PAL_BUF[6];
            pal_col(5, tmp3);
            pal_col(6, tmp2);
            lastgcolortype = type;
            gnd_palette_transition_timer = current_transition_timer_length;
        } else {
            original_bg_palette_idx_0 = 0;
            original_bg_palette_idx_1 = 1;
            original_bg_palette_idx_2 = 9;
            original_bg_palette_color_0 = PAL_BUF[0];
            original_bg_palette_color_1 = PAL_BUF[1];
            original_bg_palette_color_2 = PAL_BUF[9];
            pal_col(0, tmp2);
            pal_col(1, tmp3);
            pal_col(9, tmp3);
            lastbgcolortype = type;
            bg_palette_transition_timer = current_transition_timer_length;
        }
        activesprites_type[index] = 0xFF; 
        return 0x00;
    }
//	else if (type >= CUBE_MODE && type <= ROBOT_MODE) return 0x2F;	// Portals
    else if (type == 0xFA) {
		current_transition_timer_length = ((0xb0 - low_byte(Generic2.y)) >> 3) & 0x1e; // force it to be even
		activesprites_type[index] = 0xFF;
    }
*/

    if ((type >= 0x80) && (type < 0xF0)){                //COLOR TRIGGERS ON LOADING    was type & 0x30 and tmp2 = (type & 0x3f)-10 for spots 0x10-0x70
		if (!discomode) tmp2 = (type & 0x3F);                        
		else { 
			return 0x00;
		}
			
		if (type >= 0xC0){
		    pal_col(6, tmp2);
		    if (tmp2-0x10 & 0xC0) { 
			pal_col(5, 0x0f); 
		    } else { 
			pal_col(5, (tmp2-0x10)); 
		    }
			lastgcolortype = type;
		} else {
		    pal_col(0, tmp2);
		    if (tmp2-0x10 & 0xC0) { 
			pal_col(1, 0x0f); 
			pal_col(9, 0x0f); 
		    } else { 
			pal_col(1, (tmp2-0x10)); 
			pal_col(9, (tmp2-0x10)); 
		    }
			lastbgcolortype = type;
		}
		activesprites_type[index] = 0xFF; 
		return 0x00;
    }

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
        case CUBE_MODE:
        case SHIP_MODE:
        case BALL_MODE:
        case ROBOT_MODE:
        case UFO_MODE:
        case SPIDER_MODE:
        case SINGLE_PORTAL:
        case DUAL_PORTAL:
        case GRAVITY_DOWN_PORTAL:
        case GRAVITY_UP_PORTAL:
        case MINI_PORTAL:
        case WAVE_MODE:
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
        case PINK_PAD_UP:
        case PINK_PAD_DOWN:
        case GRAVITY_PAD_DOWN:
        case GRAVITY_PAD_UP:
            return 0x02;
//			return 0x04;
        case LEVEL_END_TRIGGER:
            gameState = 0x03; 
            
    }
    return 0;

    #undef type
}

#define yellow_orb 0x00 << 3
#define yellow_pad 0x01 << 3
#define pink_orb   0x02 << 3
#define pink_pad   0x03 << 3
#define red_orb    0x04 << 3
#define ylw_bigger 0x05 << 3

const short heights[] = {
//  cube   ship   ball    ufo   robot  spider  wave  unused
    0x590, 0x590, 0x5E0, 0x590, 0x590, 0x590, 0x000, 0x000, // yellow orb
    0x7A0, 0x500, 0x600, 0x500, 0x7A0, 0x500, 0x000, 0x000, // yellow pad
    0x450, 0x590, 0x500, 0x590, 0x590, 0x590, 0x000, 0x000, // pink orb
    0x4A0, 0x4A0, 0x4A0, 0x500, 0x4A0, 0x4A0, 0x000, 0x000, // pink pad
    0xA50, 0x500, 0x500, 0x500, 0x7A0, 0x500, 0x000, 0x000, // red orb
    0x590, 0x590, 0x4C0, 0x590, 0x590, 0x590, 0x000, 0x000, // yellow orb bigger
};

const short mini_heights[] = {
	//  cube   ship   ball   ufo   robot  spider   wave  unused
	0x4D0, 0x4D0, 0x410, 0x4D0, 0x4D0, 0x4D0, 0x000, 0x000, // yellow orb
	0x5B0, 0x500, 0x4C0, 0x500, 0x7A0, 0x500, 0x000, 0x000, // yellow pad
	0x350, 0x4D0, 0x500, 0x4D0, 0x4D0, 0x4D0, 0x000, 0x000, // pink orb
	0x350, 0x4A0, 0x4A0, 0x500, 0x4A0, 0x4A0, 0x000, 0x000, // pink pad
	0x750, 0x500, 0x500, 0x500, 0x7A0, 0x500, 0x000, 0x000, // red orb
	0x590, 0x590, 0x570, 0x590, 0x590, 0x590, 0x000, 0x000, // yellow orb bigger	
};



#pragma code-name(push, "XCD_BANK_00")
#pragma data-name(push, "XCD_BANK_00")
#pragma rodata-name(push, "XCD_BANK_00")

#define table_offset tmp3
#define collided tmp4

// Load the player velocity from the height table
static unsigned int __fastcall__ sprite_gamemode_y_adjust() {
    __A__ = (gamemode | table_offset) & 0x7f;
    __asm__("asl");
    __asm__("tay");
    if (mini) {
        __AX__ = (asm ("lda %v,y", mini_heights),asm ("ldx %v+1,y", mini_heights),__AX__);
    } else {
        __AX__ = (asm ("lda %v,y", heights),asm ("ldx %v+1,y", heights),__AX__);
    }
    // Use y here for the conditional, otherwise the compiler overwrites A
    __asm__("ldy %v", currplayer_gravity), __asm__("bne %g", jumpNoGravityAdjust);
        __AX__ ^= 0xffff;
jumpNoGravityAdjust:
    return __AX__;
}

static void sprite_gamemode_main() {
    if (gamemode == BALL_MODE) kandotemp2[currplayer] = 1;
    if (cube_data[currplayer] == 2) {
        cube_data[currplayer] = 0;
        if (collided == BLUE_ORB) {
            currplayer_gravity ^= 0x01;
            if (gamemode != BALL_MODE) {
                currplayer_vel_y = (!currplayer_gravity) ? PAD_HEIGHT_BLUE^0xFFFF : PAD_HEIGHT_BLUE;
            } else {
                currplayer_vel_y = (!currplayer_gravity) ? ORB_BALL_HEIGHT_BLUE^0xFFFF : ORB_BALL_HEIGHT_BLUE;
            }
        } else if (collided == GREEN_ORB) {
            currplayer_gravity ^= 0x01;
            if (currplayer_gravity && currplayer_vel_y < 0x530) currplayer_vel_y = 0x530;
            else if (!currplayer_gravity && currplayer_vel_y > -0x530) currplayer_vel_y = -0x530;
        } else {
            currplayer_vel_y = sprite_gamemode_y_adjust();
        }
    }
}

static void sprite_gamemode_controller_check() {
    if (pad_new[controllingplayer] & PAD_A) {	
        cube_data[currplayer] &= 0x01;
        if (collided == BLUE_ORB) {
            currplayer_gravity ^= 0x01;
            currplayer_vel_y = (!currplayer_gravity) ? PAD_HEIGHT_BLUE^0xFFFF : PAD_HEIGHT_BLUE;
        } else if (collided == GREEN_ORB) {
            currplayer_gravity ^= 0x01;
            if (currplayer_gravity && currplayer_vel_y < 0x530) currplayer_vel_y = 0x530;
            else if (!currplayer_gravity && currplayer_vel_y > -0x530) currplayer_vel_y = -0x530;
        } else {
            currplayer_vel_y = sprite_gamemode_y_adjust();
        }
    }
}

void sprite_collide_lookup() {
    switch (collided) {
    // Portal game mode switches
    case CUBE_MODE:
    case SHIP_MODE:
    case BALL_MODE:
    case UFO_MODE:
    case ROBOT_MODE:
        gamemode = collided;
        robotjumptime[currplayer] = 0;
        // fallthrough
    case NOSPRITE:
        return;
    case SPIDER_MODE:
        gamemode = 5;
        return;
    case WAVE_MODE:
        gamemode = 6;
        return;
    case MINI_PORTAL:
        mini = 1;
        return;
    case GROWTH_PORTAL:
        mini = 0;
        return;
    case DUAL_PORTAL:
        dual = 1;
        if (twoplayer) { player_gravity[1] = player_gravity[0] ^ 1; }
        else { player_x[1] = player_x[0]; player_y[1] = player_y[0]; player_gravity[1] = player_gravity[0] ^ 1; }
        return;
    case SINGLE_PORTAL:
        if (!twoplayer) dual = 0;
        else { player_gravity[1] = player_gravity[0]; }
        return;

    // collided with non game mode portals 

    case GRAVITY_DOWN_PORTAL:
    case GRAVITY_DOWN_UPWARDS_PORTAL:
    case GRAVITY_DOWN_DOWNWARDS_PORTAL:
    case GRAVITY_DOWN_INVISIBLE_PORTAL:  
        if (currplayer_gravity) {
            currplayer_gravity = 0; 
        //   if (currplayer_vel_y > -0x0200) currplayer_vel_y = -0x0200; 
        // else 
            if (currplayer_vel_y < -0x0290) currplayer_vel_y = -0x0290; 
        }
        return;
    case GRAVITY_UP_PORTAL:
    case GRAVITY_UP_UPWARDS_PORTAL:
    case GRAVITY_UP_DOWNWARDS_PORTAL:
    case GRAVITY_UP_INVISIBLE_PORTAL:
        if (!currplayer_gravity) {
            currplayer_gravity = 1; 
            //if (currplayer_vel_y < 0x0200) currplayer_vel_y = 0x0200; 
    //	    else
                if (currplayer_vel_y > 0x0290) currplayer_vel_y = 0x0290; 
        }
        return;

    // collided with coin
    case COIN1:
    case COINGOTTEN1:
        if (!has_practice_point) {
            coins |= COIN_1;
//	        sfx_play(sfx_click, 0);
            activesprites_type[index] = 0xFF;
        }
        return;
    case COIN2:
    case COINGOTTEN2:
        if (!has_practice_point) {
            coins |= COIN_2;
//	        sfx_play(sfx_click, 0);
            activesprites_type[index] = 0xFF;
        }
        return;
    case COIN3:
    case COINGOTTEN3:
        if (!has_practice_point) {
            coins |= COIN_3;
//	        sfx_play(sfx_click, 0);
            activesprites_type[index] = 0xFF;
        }
        return;

    // collided with speed trigger
    case SPEED_05_PORTAL:
        speed = 1;
        return;
    case SPEED_10_PORTAL:
        speed = 0;
        return;
    case SPEED_20_PORTAL:
        speed = 2;
        return;
    case SPEED_30_PORTAL:
        speed = 3;
        return;
    case SPEED_40_PORTAL:
        speed = 4;
        return;

    // collided with a pad
    case YELLOW_PAD_DOWN:
    case YELLOW_PAD_UP:
        table_offset = yellow_pad;
        currplayer_vel_y = sprite_gamemode_y_adjust();
        return;
    case PINK_PAD_DOWN:
    case PINK_PAD_UP:
        table_offset = pink_pad;
        currplayer_vel_y = sprite_gamemode_y_adjust();
        return;

    case GRAVITY_PAD_DOWN:
    case GRAVITY_PAD_DOWN_INVISIBLE:
        if (!currplayer_gravity) { 
            currplayer_gravity = 0x01;				//flip gravity
            currplayer_vel_y = PAD_HEIGHT_BLUE;	
        }
        return;
    
    case GRAVITY_PAD_UP:
    case GRAVITY_PAD_UP_INVISIBLE:
        if (currplayer_gravity) { 
            currplayer_gravity = 0x00;				//flip gravity
            currplayer_vel_y = PAD_HEIGHT_BLUE^0xFFFF;	
        }
        return;

    // collided with an orb
    case YELLOW_ORB:
        table_offset = 0;
        if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
            sprite_gamemode_main();
        } else if (gamemode == SHIP_MODE || gamemode == UFO_MODE) {
            sprite_gamemode_controller_check();
        }
        return;

    case YELLOW_ORB_BIGGER:
        table_offset = ylw_bigger;
        if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
            sprite_gamemode_main();
        } else if (gamemode == SHIP_MODE || gamemode == UFO_MODE) {
            sprite_gamemode_controller_check();
        }
        return;

    case BLUE_ORB:
        if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE || gamemode == SPIDER_MODE) {
            sprite_gamemode_main();
        } else if (gamemode == SHIP_MODE || gamemode == UFO_MODE || gamemode == WAVE_MODE) {
            sprite_gamemode_controller_check();
        }
        return;

    case PINK_ORB:
        table_offset = pink_orb;
        if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
            sprite_gamemode_main();
        } else if (gamemode == SHIP_MODE || gamemode == UFO_MODE || gamemode == WAVE_MODE) {
            sprite_gamemode_controller_check();
        }
        return;

    case RED_ORB:
        table_offset = red_orb;
        if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
            sprite_gamemode_main();
        } else if (gamemode == SHIP_MODE || gamemode == UFO_MODE || gamemode == WAVE_MODE) {
            sprite_gamemode_controller_check();
        }
        return;
    
    case GREEN_ORB:
        table_offset = red_orb;
        if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
            sprite_gamemode_main();
        } else if (gamemode == SHIP_MODE || gamemode == UFO_MODE || gamemode == WAVE_MODE) {
            sprite_gamemode_controller_check();
        }
        return;
    }
}

#undef table_offset
#undef collided

void sprite_collide(){

    Generic.x = high_byte(currplayer_x) + 1;
    Generic.y = high_byte(currplayer_y);

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

            Generic2.x = activesprites_realx[index];
            Generic2.y = activesprites_realy[index];

            tmp2 = sprite_height_lookup();	// uses tmp4
            Generic2.height = tmp2;


            
            if (check_collision(&Generic, &Generic2)) {
                sprite_collide_lookup();
            }
        }
    }
    if (!mini) {
        Generic.height = CUBE_HEIGHT;
    }
    
    else {
        Generic.height = MINI_CUBE_HEIGHT;
    }    
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
