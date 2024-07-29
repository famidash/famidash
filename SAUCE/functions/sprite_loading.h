#pragma data-name(push, "XCD_BANK_00")
#pragma rodata-name(push, "XCD_BANK_00")

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
#define YELLOW_ORB_SMALLER			0x29
#define DECO_START				0x2A
#define LONG_LIGHT				0x2A
#define MEDIUM_LIGHT				0x2B
#define SHORT_LIGHT				0x2C
#define CHAIN					0x2D
#define BG_SPIKE_GROUP1				0x2E
#define BG_SPIKE_GROUP2				0x2F
#define BG_SPIKE_GROUP3				0x30
#define BG_SPIKE_GROUP4				0x31
#define BIG_DIAMOND				0x32
#define RIGHT_HALF_DIAMOND			0x33
#define QUESTION_MARK				0x34
#define EXCLAMATION_MARK			0x35
#define RIGHT_ARROW				0x36
#define BIG_X					0x37
#define SHORT_LIGHT_RIGHT			0x38
#define SHORT_LIGHT_LEFT			0x39
#define LONG_LIGHT_U				0x3A
#define MEDIUM_LIGHT_U				0x3B
#define SHORT_LIGHT_U				0x3C
#define CHAIN_U					0x3D
#define MEDIUM_LIGHT_RIGHT			0x3E
#define MEDIUM_LIGHT_LEFT			0x3F
#define LONG_LIGHT_RIGHT			0x40
#define LONG_LIGHT_LEFT				0x41
#define SHORT_LIGHT_U_8_PIXELS			0x42
#define CHAIN_U_8_PIXELS			0x43
#define DECO_END				0x43
#define BLACK_ORB				0x44
#define DASH_ORB				0x45
#define DASH_GRAVITY_ORB			0x46
#define BG_SPIKE_GROUP2_UP8			0x47
#define DIAMOND_SHIFTED_			0x48
#define PULSE_ORB				0x49
#define MUSIC_NOTE				0x4A
#define SWING_MODE				0x4B
#define DASH_ORB_45DEG_UP			0x4C
#define DASH_GRAVITY_ORB_45DEG_UP		0x4D
#define TELEPORT_PORTAL_ENTER			0x4E
#define TELEPORT_PORTAL_EXIT			0x4F
#define DASH_ORB_45DEG_DOWN			0x50
#define DASH_GRAVITY_ORB_45DEG_DOWN		0x51
#define RED_PAD_DOWN				0x52
#define RED_PAD_UP				0x53
#define SPIDER_ORB_UP				0x54
#define SPIDER_ORB_DOWN				0x55
#define SPIDER_PAD_UP				0x56
#define SPIDER_PAD_DOWN				0x57
#define NINJA_MODE				0x58
#define TELEPORT_SQUARE_ENTER			0x59
#define TELEPORT_SQUARE_EXIT			0x5A
#define DASH_ORB_UPWARDS			0x5B
#define DASH_GRAVITY_ORB_UPWARDS		0x5C
#define DASH_ORB_DOWNWARDS			0x5D
#define DASH_GRAVITY_ORB_DOWNWARDS		0x5E
#define GRAVITY_13_PORTAL			0x5F
#define GRAVITY_12_PORTAL			0x60
#define GRAVITY_23_PORTAL			0x61
#define GRAVITY_2X_PORTAL			0x62
#define GRAVITY_1X_PORTAL			0x63
#define RANDOM_MODE_PORTAL			0x64
#define GREEN_PAD				0x65


#define DEATH_CHANCE				0xDF

#define MASK_SPRITES_ON				0xEE
#define MASK_SPRITES_OFF			0xEF

#define FORCED_TRAILS_ON			0xF0
#define FORCED_TRAILS_OFF			0xF1
#define PLAYER_TRAILS_ON			0xF2
#define PLAYER_TRAILS_OFF			0xF3
#define SLOWMODE_ON				0xF4
#define SLOWMODE_OFF				0xF5

#define F_BLOCK					0xF6
#define J_BLOCK					0xF7
#define H_BLOCK					0xF8
#define S_BLOCK					0xF9
#define D_BLOCK					0xFA
#define GRAVITY_UP_INVISIBLE_PORTAL		0XFB
#define GRAVITY_DOWN_INVISIBLE_PORTAL		0XFC
#define GRAVITY_PAD_DOWN_INVISIBLE		0XFD
#define GRAVITY_PAD_UP_INVISIBLE		0XFE
#define NOSPRITE				0XFF

extern void load_next_sprite(void);

extern void check_spr_objects(void);

extern char bg_coll_U();
extern char bg_coll_D();

const unsigned char OUTLINES[]={
		0x30,
		0x11,
		0x12,
		0x13,
		0x14,
		0x15,
		0x16,
		0x27,
		0x28,
		0x29,
		0x2A,
		0x2B,
		0x2C,
		0x21,
		0x17,
		0x0F
};



void init_sprites(void){	// required to be in a fixed bank
	// Setting up pointers is already done by init_rld()
	mmc3_set_prg_bank_1(sprite_data_bank);

	for (tmp4 = max_loaded_sprites-1; tmp4 != 0; --tmp4) activesprites_type[tmp4] = 0xFF;

	spr_index = 0;
	do {
		if (sprite_data[0] == TURN_OFF) break;
		load_next_sprite();
		if (activesprites_x_hi[spr_index] != 0) activesprites_active[spr_index] = 0;
		if (activesprites_x_lo[spr_index] == 0xFF) activesprites_active[spr_index] = 0;
	} while (spr_index != 0);
}

#pragma code-name(push, "XCD_BANK_00")

char sprite_height_lookup(){

	#define type tmp4
/*
	//	color fading code
	if ((type >= 0x80) && (type < 0xF0)){                //COLOR TRIGGERS ON LOADING    was type & 0x30 and tmp2 = (type & 0x3f)-10 for spots 0x10-0x70
		if (!discomode) tmp2 = (type & 0x3F);                        
		else { 
			return 0x00;
		}
		tmp3 = oneShadeDarker(tmp2);
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
	else if (type == 0xFA) {
				current_transition_timer_length = ((0xb0 - low_byte(Generic2.y)) >> 3) & 0x1e; // force it to be even
				activesprites_type[index] = 0xFF;
	}
	*/
	if (type == DEATH_CHANCE) { 
		tmp7 = (newrand() & 15) + 1;
		for (tmp2 = 0; tmp2 < tmp7; tmp2++) {
			newrand();
		};

		if (!(newrand() & 63)) { cube_data[currplayer] |= 1; } activesprites_type[index] = 0xFF; return 0; 
	} else
	if ((type >= 0xB0) && (type <= 0xBF)) {
					outline_color = uint8_load(OUTLINES, type & 0x0F);
					activesprites_type[index] = 0xFF; 
					return 0x00;
	}

	else if ((type >= 0x80) && (type < 0xED)){                //COLOR TRIGGERS ON LOADING    was type & 0x30 and tmp2 = (type & 0x3f)-10 for spots 0x10-0x70
				if (discomode) return 0;
					
				tmp2 = (type & 0x3F);                        
				
						
				if (type >= 0xC0){
					pal_col(6, tmp2);
					pal_col(5, oneShadeDarker(tmp2)); 
					lastgcolortype = type;
				} else {
					pal_col(0, tmp2);
					pal_col(1, oneShadeDarker(tmp2)); 
					pal_col(9, oneShadeDarker(tmp2)); 
					lastbgcolortype = type;
				}
				activesprites_type[index] = 0xFF; 
				return 0;
	}
	else if (type == MASK_SPRITES_ON) { disco_sprites = 1; activesprites_type[index] = 0xFF; return 0; }
	
	else if (type == MASK_SPRITES_OFF) { disco_sprites = 0; activesprites_type[index] = 0xFF; return 0; }
	else if (type == SLOWMODE_ON) { slowmode = 1; activesprites_type[index] = 0xFF; return 0; }
	else if (type == SLOWMODE_OFF) { slowmode = 0; activesprites_type[index] = 0xFF; return 0; }
	else if (type >= COINGOTTEN1 && type <= COINGOTTEN3) return 0x17;	// Coin
	else if (type >= SPEED_05_PORTAL && type <= SPEED_20_PORTAL) // Speed portals
		return 0x1F;
	else if (type >= CUBE_MODE && type <= ROBOT_MODE) // Player portals
		return 0x2F;	
	else if ((type >= 0x2A && type <= 0x43) || (type >= 0x47 && type <= 0x4A)) {    // Decorations
		if (twoplayer || !decorations) activesprites_type[index] = 0xFF; 
				return 0;
	}

	switch(type) {
		case NOSPRITE:
			activesprites_x_lo[index] = 0xFF; return 0;
		case FORCED_TRAILS_ON:
			forced_trails = 1;
			activesprites_type[index] = 0xFF;
			return 0x00;
		case FORCED_TRAILS_OFF:
			forced_trails = 0;
			activesprites_type[index] = 0xFF;
			return 0x00;
		case GRAVITY_PAD_DOWN_INVISIBLE:
		case GRAVITY_PAD_UP_INVISIBLE:
			return 0x07;

		case TELEPORT_SQUARE_EXIT:
			teleport_output = activesprites_realy[index];
			//intentional leak
		case YELLOW_ORB:
		case YELLOW_ORB_BIGGER:
		case YELLOW_ORB_SMALLER:
		case BLUE_ORB:
		case PINK_ORB:
		case GREEN_ORB:
		case BLACK_ORB:
		case DASH_ORB:
		case DASH_GRAVITY_ORB:
		case DASH_ORB_UPWARDS:
		case DASH_GRAVITY_ORB_UPWARDS:
		case DASH_ORB_DOWNWARDS:
		case DASH_GRAVITY_ORB_DOWNWARDS:
		case DASH_ORB_45DEG_UP:
		case DASH_GRAVITY_ORB_45DEG_UP:
		case DASH_ORB_45DEG_DOWN:
		case DASH_GRAVITY_ORB_45DEG_DOWN:
		case RED_ORB:
		case D_BLOCK:
		case S_BLOCK:
		case H_BLOCK:
		case J_BLOCK:
		case F_BLOCK:
		case SPIDER_ORB_UP:
		case SPIDER_ORB_DOWN:
		case TELEPORT_SQUARE_ENTER:
			return 0x0f;

		case GRAVITY_UP_INVISIBLE_PORTAL:
		case GRAVITY_DOWN_INVISIBLE_PORTAL:
		case GRAVITY_DOWN_UPWARDS_PORTAL:
		case GRAVITY_UP_UPWARDS_PORTAL:
		case YELLOW_PAD_DOWN:
		case YELLOW_PAD_UP:
		case PINK_PAD_UP:
		case PINK_PAD_DOWN:
		case GREEN_PAD:
		case RED_PAD_UP:
		case RED_PAD_DOWN:
		case GRAVITY_PAD_DOWN:
		case GRAVITY_PAD_UP:
			return 0x02;
		case SPIDER_PAD_UP:
		case SPIDER_PAD_DOWN:
			return 0x01;
//            return 0x0F;

		case TELEPORT_PORTAL_EXIT:
			teleport_output = activesprites_realy[index] + 0x10;
			//intentional leak
		case SPIDER_MODE:
		case SINGLE_PORTAL:
		case DUAL_PORTAL:
		case GRAVITY_DOWN_PORTAL:
		case GRAVITY_UP_PORTAL:
		case MINI_PORTAL:
		case WAVE_MODE:
		case SWING_MODE:
		case NINJA_MODE:
		case RANDOM_MODE_PORTAL:
		case GROWTH_PORTAL:
		case GRAVITY_13_PORTAL:
		case GRAVITY_12_PORTAL:
		case GRAVITY_23_PORTAL:
		case GRAVITY_2X_PORTAL:
		case GRAVITY_1X_PORTAL:
		case TELEPORT_PORTAL_ENTER:
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
		case GRAVITY_DOWN_DOWNWARDS_PORTAL:
		case GRAVITY_UP_DOWNWARDS_PORTAL:
			return 0x1F;
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
#define black_orb  0x06 << 3
#define ylw_smaller 0x07 << 3
#define red_pad 0x08 << 3

const short heights[] = {
//  cube    ship    ball     ufo    robot   spider  wave   unused
	0x590,  0x590,  0x4A0,  0x590,  0x590,  0x590,  0x000, 0x000, // yellow orb
	0x7C0,  0x390,  0x550,  0x500,  0x7A0,  0x500,  0x000, 0x000, // yellow pad
	0x3D0,  0x590,  0x3C0,  0x590,  0x450,  0x590,  0x000, 0x000, // pink orb
	0x530,  0x510,  0x38A,  0x510,  0x510,  0x510,  0x000, 0x000, // pink pad
	0x850,  0x700,  0x600,  0x950,  0x950,  0x500,  0x000, 0x000, // red orb
	0x590,  0x590,  0x4C0,  0x590,  0x590,  0x590,  0x000, 0x000, // yellow orb bigger
       -0x990, -0x990, -0x970, -0x990, -0x990, -0x990,  0x000, 0x000, // black orb
	0x540,  0x540,  0x472,  0x4B0,  0x770,  0x4B0,  0x000, 0x000, // yellow orb smaller
	0x950,  0x700,  0x600,  0x950,  0x950,  0x500,  0x000, 0x000, // red pad	
};

const short mini_heights[] = {
//  cube    ship    ball     ufo    robot   spider  wave   unused
	0x4D0,  0x4D0,  0x410,  0x4D0,  0x4D0,  0x4D0,  0x000, 0x000, // yellow orb
	0x5B0,  0x500,  0x4C0,  0x500,  0x5B0,  0x500,  0x000, 0x000, // yellow pad
	0x350,  0x4D0,  0x500,  0x4D0,  0x350,  0x4D0,  0x000, 0x000, // pink orb
	0x350,  0x4A0,  0x4A0,  0x500,  0x350,  0x4A0,  0x000, 0x000, // pink pad
	0x950,  0x700,  0x600,  0x950,  0x950,  0x500,  0x000, 0x000, // red orb
	0x590,  0x590,  0x560,  0x590,  0x590,  0x590,  0x000, 0x000, // yellow orb bigger
   -0x1190,-0x1190,-0x1170,-0x1190,-0x1190,-0x1190, 0x000, 0x000, // black orb
	0x540,  0x540,  0x472,  0x4B0,  0x770,  0x4B0,  0x000, 0x000, // yellow orb smaller
	0x950,  0x700,  0x600,  0x950,  0x950,  0x500,  0x000, 0x000, // red pad	
};

#define table_offset tmp3
#define collided tmp4

// Load the player velocity from the height table
static unsigned int __fastcall__ sprite_gamemode_y_adjust() {
	__A__ = (gamemode | table_offset) << 1;
	__asm__("tay");
	if (mini) {
		__AX__ = (__asm__ ("lda %v,y", mini_heights), __asm__ ("ldx %v+1,y", mini_heights),__AX__);
	} else {
		__AX__ = (__asm__ ("lda %v,y", heights),__asm__ ("ldx %v+1,y", heights),__AX__);
	}
	// Use y here for the conditional, otherwise the compiler overwrites A
	__asm__("ldy %v", currplayer_gravity); 
	do_if_zero({__AX__ ^= 0xffff; __AX__ += 1;});
	return __AX__;
}

static void sprite_gamemode_main() {
	if (pad[controllingplayer] & PAD_A) {	
		if (gamemode == BALL_MODE) kandotemp2[currplayer] = 1;
		if (cube_data[currplayer] & 2 || pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] &= 1;

			switch (collided) {
			case BLUE_ORB:
				currplayer_gravity ^= 0x01;
				if (gamemode != BALL_MODE) {
					currplayer_vel_y = (!currplayer_gravity) ? PAD_HEIGHT_BLUE^0xFFFF : PAD_HEIGHT_BLUE;
				} else {
					currplayer_vel_y = (!currplayer_gravity) ? ORB_BALL_HEIGHT_BLUE^0xFFFF : ORB_BALL_HEIGHT_BLUE;
				}
				break;
			case GREEN_ORB:
				currplayer_gravity ^= 0x01;
				if (currplayer_gravity && currplayer_vel_y < 0x530) currplayer_vel_y = 0x530;
				else if (!currplayer_gravity && currplayer_vel_y > -0x530) currplayer_vel_y = -0x530;
				break;
			case DASH_GRAVITY_ORB:
				if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
				//intentional leak
			case DASH_ORB:
				currplayer_vel_y = 0;
				dashing[currplayer] = 1;
				break;
			case DASH_GRAVITY_ORB_45DEG_UP:
				if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
				//intentional leak
			case DASH_ORB_45DEG_UP:
				currplayer_vel_y = -currplayer_vel_x;
				dashing[currplayer] = 2;
				break;
			case DASH_GRAVITY_ORB_45DEG_DOWN:
				if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
				//intentional leak
			case DASH_ORB_45DEG_DOWN:
				currplayer_vel_y = currplayer_vel_x;
				dashing[currplayer] = 3;
				break;
			case DASH_GRAVITY_ORB_UPWARDS:
				if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
				//intentional leak
			case DASH_ORB_UPWARDS:
				currplayer_vel_y = currplayer_vel_x;
				currplayer_vel_x = 0;
				dashing[currplayer] = 4;
				break;
			case DASH_GRAVITY_ORB_DOWNWARDS:
				if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
				//intentional leak
			case DASH_ORB_DOWNWARDS:
				currplayer_vel_y = -currplayer_vel_x;
				currplayer_vel_x = 0;
				dashing[currplayer] = 5;
				break;
			default:
				currplayer_vel_y = sprite_gamemode_y_adjust();
				//break;
			};
		activesprites_activated[index]++;				
		}
	}
}

static void sprite_gamemode_controller_check() {
	if (pad_new[controllingplayer] & PAD_A) {	
		uint8_store(cube_data, currplayer, cube_data[currplayer] & 0x01);
		switch (collided) {
		case BLUE_ORB:
			currplayer_gravity ^= 0x01;
			currplayer_vel_y = (!currplayer_gravity) ? PAD_HEIGHT_BLUE^0xFFFF : PAD_HEIGHT_BLUE;
			break;
		case GREEN_ORB:
			currplayer_gravity ^= 0x01;
			if (currplayer_gravity && currplayer_vel_y < 0x530) currplayer_vel_y = 0x530;
			else if (!currplayer_gravity && currplayer_vel_y > -0x530) currplayer_vel_y = -0x530;
			break;
		case DASH_GRAVITY_ORB:
			if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
			//intentional leak
		case DASH_ORB:
			currplayer_vel_y = 0;
			dashing[currplayer] = 1;
			break;
		case DASH_GRAVITY_ORB_45DEG_UP:
			if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
			//intentional leak
		case DASH_ORB_45DEG_UP:
			currplayer_vel_y = -currplayer_vel_x;
			dashing[currplayer] = 2;
			break;	
		case DASH_GRAVITY_ORB_45DEG_DOWN:
			if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
			//intentional leak
		case DASH_ORB_45DEG_DOWN:
			currplayer_vel_y = currplayer_vel_x;
			dashing[currplayer] = 3;
			break;		
		case DASH_GRAVITY_ORB_UPWARDS:
			if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
			//intentional leak
		case DASH_ORB_UPWARDS:
			currplayer_vel_y = currplayer_vel_x;
			currplayer_vel_x = 0;
			dashing[currplayer] = 4;
			break;	
		case DASH_GRAVITY_ORB_DOWNWARDS:
			if (!dashing[currplayer]) currplayer_gravity ^= 0x01;	//reverse gravity
			//intentional leak
		case DASH_ORB_DOWNWARDS:
			currplayer_vel_y = -currplayer_vel_x;
			currplayer_vel_x = 0;
			dashing[currplayer] = 5;
			break;
		default:
			currplayer_vel_y = sprite_gamemode_y_adjust();
			//break;
		};
	activesprites_activated[index]++;	
	}
}

void sprite_collide_lookup() {

	if (!activesprites_activated[index]) {
	switch (collided) {

	case TELEPORT_PORTAL_EXIT:
	case TELEPORT_SQUARE_EXIT:
	case NOSPRITE:
		return;
	
	// Portal game mode switches
	case S_BLOCK: dashing[currplayer] = 0; return;
	case H_BLOCK: hblocked[currplayer] = 1; return;
	case J_BLOCK: jblocked[currplayer] = 1; return;
	case D_BLOCK: dblocked[currplayer] = 1; return;
	case F_BLOCK: fblocked[currplayer] = 1; return;
	case GRAVITY_1X_PORTAL: gravity_mod = 0; return;
	case GRAVITY_13_PORTAL: gravity_mod = 1; return;
	case GRAVITY_12_PORTAL: gravity_mod = 2; return;
	case GRAVITY_23_PORTAL: gravity_mod = 3; return;
	case GRAVITY_2X_PORTAL: gravity_mod = 4; return;
	case CUBE_MODE:
		if (retro_mode) gamemode = 4;
		else gamemode = 0;
		return;    

	case SHIP_MODE:
	case BALL_MODE:
	case UFO_MODE:
		target_scroll_y = uint16SepArrLoad(activesprites_y, index) - 0x10; //unused now
//		target_scroll_y -= 0x10;
	case ROBOT_MODE:
		gamemode = collided;
		//robotjumptime[currplayer] = 0;
		return;
	case TELEPORT_SQUARE_ENTER:
		if (cube_data[currplayer] & 2 || pad_new[controllingplayer] & PAD_A) {
			currplayer_vel_y = 0;
			orbed[currplayer] = 1;
			cube_data[currplayer] &= 1;
	case TELEPORT_PORTAL_ENTER:
			high_byte(currplayer_y) = teleport_output;
			activesprites_activated[index]++;
		}
		return;
	case SPIDER_MODE:
		gamemode = 5;
		return;
	case WAVE_MODE:
		gamemode = 6;
		return;
	case SWING_MODE:
		gamemode = 7;
		return;
	case NINJA_MODE:
		gamemode = 8;
		return;
	case RANDOM_MODE_PORTAL:
		gamemode = rand8() & 7;
		activesprites_activated[index]++;
		return;
	case MINI_PORTAL:
		mini = 1;
		return;
	case GROWTH_PORTAL:
		mini = 0;
		return;
	case GREEN_PAD:
		currplayer_gravity ^= 1;
		activesprites_activated[index]++;
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
			if (currplayer_vel_y < -0x0290) currplayer_vel_y = -0x0290; 
		}
		activesprites_activated[index]++;
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
		activesprites_activated[index]++;		
		return;

	// collided with coin
	case COIN1:
	case COINGOTTEN1:
		if (!has_practice_point) {
			coins |= COIN_1;
	        sfx_play(sfx_coin, 0);
			activesprites_type[index] = 0xFF;
		}
		return;
	case COIN2:
	case COINGOTTEN2:
		if (!has_practice_point) {
			coins |= COIN_2;
	       sfx_play(sfx_coin, 0);
			activesprites_type[index] = 0xFF;
		}
		return;
	case COIN3:
	case COINGOTTEN3:
		if (!has_practice_point) {
			coins |= COIN_3;
	        sfx_play(sfx_coin, 0);
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

	case SPIDER_ORB_UP:
		if (cube_data[currplayer] & 2 || pad_new[controllingplayer] & PAD_A) {
			cube_data[currplayer] &= 1;
	case SPIDER_PAD_UP:
			high_byte(currplayer_y) -= eject_D;
			currplayer_vel_y = 0;
			currplayer_gravity = 1;
			do {
				high_byte(currplayer_y) -= 0x04;
				Generic.y = high_byte(currplayer_y); // the rest should be the same
			} while (!bg_coll_U());
			high_byte(currplayer_y) -= eject_U;
			currplayer_vel_y = 0;	
			orbed[currplayer] = 1;
			activesprites_activated[index]++;
		}
		return;
	case SPIDER_ORB_DOWN:
		if (cube_data[currplayer] & 2 || pad_new[controllingplayer] & PAD_A) {	
			cube_data[currplayer] &= 1;
	case SPIDER_PAD_DOWN:
			high_byte(currplayer_y) -= eject_U + 1;
			currplayer_vel_y = 0;
			currplayer_gravity = 0;
			do {
				high_byte(currplayer_y) += 0x04;
				Generic.y = high_byte(currplayer_y); // the rest should be the same
			} while (!bg_coll_D());

			high_byte(currplayer_y) -= eject_D;
			
			currplayer_vel_y = 0;
			orbed[currplayer] = 1;
			activesprites_activated[index]++;
		}
		return;

	// collided with a pad
	case YELLOW_PAD_DOWN:
	case YELLOW_PAD_UP:
		table_offset = yellow_pad;
		currplayer_vel_y = sprite_gamemode_y_adjust();
		//activesprites_activated[index]++;		
		return;
	case PINK_PAD_DOWN:
	case PINK_PAD_UP:
		table_offset = pink_pad;
		currplayer_vel_y = sprite_gamemode_y_adjust();
		//activesprites_activated[index]++;		
		return;
	case RED_PAD_DOWN:
	case RED_PAD_UP:
		table_offset = red_pad;
		currplayer_vel_y = sprite_gamemode_y_adjust();
		//activesprites_activated[index]++;		
		return;

	case GRAVITY_PAD_DOWN:
	case GRAVITY_PAD_DOWN_INVISIBLE:
		if (!currplayer_gravity) { 
			currplayer_gravity = 0x01;				//flip gravity
			currplayer_vel_y = PAD_HEIGHT_BLUE;	
		}
		//activesprites_activated[index]++;		
		return;
	
	case GRAVITY_PAD_UP:
	case GRAVITY_PAD_UP_INVISIBLE:
		if (currplayer_gravity) { 
			currplayer_gravity = 0x00;				//flip gravity
			currplayer_vel_y = PAD_HEIGHT_BLUE^0xFFFF;	
		}
		//activesprites_activated[index]++;		
		return;

	// collided with an orb



	case YELLOW_ORB:
		table_offset = 0;
		//intentional leak
	case DASH_ORB:
	case DASH_GRAVITY_ORB:
	case DASH_ORB_UPWARDS:
	case DASH_GRAVITY_ORB_UPWARDS:
	case DASH_ORB_DOWNWARDS:
	case DASH_GRAVITY_ORB_DOWNWARDS:
	case DASH_ORB_45DEG_UP:
	case DASH_GRAVITY_ORB_45DEG_UP:
	case DASH_ORB_45DEG_DOWN:
	case DASH_GRAVITY_ORB_45DEG_DOWN:
	case BLUE_ORB:
		break;

	case YELLOW_ORB_BIGGER:
		table_offset = ylw_bigger;
		break;
	case YELLOW_ORB_SMALLER:
		table_offset = ylw_smaller;
		break;

	case PINK_ORB:
		table_offset = pink_orb;
		break;

	case BLACK_ORB:
		table_offset = black_orb;
		break;

	case RED_ORB:
		table_offset = red_orb;
		break;
	
	case GREEN_ORB:
		table_offset = red_orb;
		break;
	default:
		return;
	};
	
	if (gamemode == CUBE_MODE || gamemode == BALL_MODE || gamemode == ROBOT_MODE) {
		sprite_gamemode_main();
	} else {
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

	Generic.width = mini ? MINI_CUBE_WIDTH : CUBE_WIDTH;
	Generic.height = mini ? MINI_CUBE_HEIGHT : CUBE_HEIGHT;

	Generic2.width = 0x0f;

	for (index = 0; index < max_loaded_sprites; ++index){
		tmp3 = activesprites_active[index];
		if (tmp3){
			tmp4 = activesprites_type[index];

			Generic2.x = activesprites_realx[index];
			Generic2.y = activesprites_realy[index];

			tmp2 = sprite_height_lookup();	// uses tmp4
			Generic2.height = tmp2;


			
			if (check_collision()) {
				sprite_collide_lookup();
			}
		}
	}

	Generic.height = mini ? MINI_CUBE_HEIGHT : CUBE_HEIGHT;
}


#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
