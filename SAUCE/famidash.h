// game states
#define MENU 0x01
#define GAME 0x02


#define MAX_ICONS 13 //total icons

// physics defines
#define ORB_HEIGHT_YELLOW_UPSIDE2 -0x580
#define PAD_HEIGHT_BLUE -0x3A0

#define ORB_BALL_HEIGHT_BLUE -0x1A0

#define CUBE_WIDTH 0x0F
#define CUBE_HEIGHT 0x0F

#define MINI_CUBE_WIDTH 0x08
#define MINI_CUBE_HEIGHT 0x07

#define WAVE_WIDTH 0x08
#define WAVE_HEIGHT 0x06

#define MINI_WAVE_WIDTH 0x04
#define MINI_WAVE_HEIGHT 0x06

#define JUMP_VEL -0x590
#define MINI_JUMP_VEL -0x4D0
#define UFO_JUMP_VEL -0x400
#define MINI_UFO_JUMP_VEL -0x380

#define ROBOT_JUMP_VEL -0x2B0
#define MINI_ROBOT_JUMP_VEL -0x2B0

#define CUBE_SPEED_X05 0x23B
#define CUBE_SPEED_X1 0x2C4
#define CUBE_SPEED_X2 0x371
#define CUBE_SPEED_X3 0x429
#define CUBE_SPEED_X4 0x51E

#define ROBOT_JUMP_TIME 18

#define UFO_MAX_FALLSPEED 0x330
#define MINI_UFO_MAX_FALLSPEED 0x350
#define CUBE_MAX_FALLSPEED 0x600
#define BALL_MAX_FALLSPEED 0x570
#define MINI_CUBE_MAX_FALLSPEED 0x410
#define MINI_BALL_MAX_FALLSPEED 0x410

#define CUBE_GRAVITY 0x6B
#define MINI_CUBE_GRAVITY 0x6F

#define UFO_GRAVITY 0x47
#define MINI_UFO_GRAVITY 0x57

#define BALL_GRAVITY 0x6B
#define MINI_BALL_GRAVITY 0x5C

#define SHIP_MAX_FALLSPEED 0x290
#define MINI_SHIP_MAX_FALLSPEED 0x2F0

#define SHIP_GRAVITY 0x30
#define MINI_SHIP_GRAVITY 0x2C

#define COIN_1 0x01
#define COIN_2 0x02
#define COIN_3 0x04

#pragma allow-eager-inline(on)

#pragma bss-name(push, "ZEROPAGE")
// zero-page variables go here

unsigned char tmp1;
unsigned char tmp2;
unsigned char tmp3;
unsigned char tmp4;
unsigned short tmp5;
unsigned short tmp6;
unsigned char tmp7;
unsigned char tmp8;
unsigned char* tmpptr1;
unsigned char* tmpptr2;
long unsigned int tmplong;
unsigned char selectedbgm;
unsigned char selectedsfx;

#pragma zpsym("tmpptr1")
#pragma zpsym("tmpptr2")

unsigned short currplayer_x;
unsigned short currplayer_y;
signed short currplayer_vel_x;
signed short currplayer_vel_y;
unsigned char currplayer_gravity;

unsigned char pad[2];
unsigned char pad_new[2];

unsigned char gamemode;
unsigned char cube_data[2];
unsigned short cube_rotate[2];



unsigned char collision;
unsigned char collision_L;
unsigned char collision_R;
unsigned char collision_U;
unsigned char collision_D;

unsigned short old_x;
unsigned short old_y;

//unsigned char gravity;
unsigned char mini;
unsigned char eject_L; // from the left
unsigned char eject_R; // remember these from the collision sub routine
unsigned char eject_D; // from below
unsigned char eject_U; // from up

unsigned short address;
unsigned char x; // room loader code
unsigned char y;
unsigned short index;
unsigned short index2;
unsigned char temp_x;
unsigned char temp_y;
unsigned char temp_room;
unsigned char dual;


unsigned char * sprite_data;
unsigned char * level_data;

#pragma zpsym("sprite_data")
#pragma zpsym("level_data")

#pragma bss-name(pop)
// other variables go here

#pragma bss-name(push, "SRAM")
unsigned char SRAM_VALIDATE[4];

#define LEVEL_COUNT 0x10
unsigned char coin1_obtained[LEVEL_COUNT];
unsigned char coin2_obtained[LEVEL_COUNT];
unsigned char coin3_obtained[LEVEL_COUNT];

unsigned char LEVELCOMPLETE[LEVEL_COUNT];

unsigned char invisible;
unsigned char PRACTICE_ENABLED = 1;
unsigned char twoplayer;

/* memory optimization */
//unsigned char oneptwoplayer;
//unsigned char jumpsound;
//unsigned char platformer;
//unsigned char musicoff;
//unsigned char sfxoff;
unsigned char options;
#define oneptwoplayer 0x01
#define jumpsound 0x02
#define platformer 0x04

#define sfxoff 0x40
#define musicoff 0x80


unsigned char icon;

unsigned char color1;
unsigned char color2;
unsigned char color3;

unsigned char discomode;

unsigned char trails;

unsigned char decorations;

//unsigned char practice_famistudio_state[0xbf];
unsigned char collisionMap0[240];   // collision map, for a 16*27 tile area
unsigned char collisionMap1[192];

#pragma bss-name(pop)



//extern unsigned char famistudio_state[0xbf];


unsigned char TOTALCOINS;
unsigned long TOTALCOINSTEMP;
unsigned char TOTALATTEMPTSHUNDREDS;
unsigned char TOTALATTEMPTSTHOUSANDS;
unsigned char TOTALCOINSTENS;
unsigned char TOTALCOINSONES;
unsigned char TOTALSTARSONES;
unsigned char TOTALSTARSTENS;


unsigned short player_x[2];
unsigned short player_y[2];
signed short player_vel_x[2];
signed short player_vel_y[2];
unsigned char player_gravity[2];


unsigned char rld_column;
unsigned char spr_index;
unsigned char long_temp_x;

unsigned char speed;
unsigned char shuffle_offset;
unsigned char count;
unsigned char coins;
unsigned char currplayer;
unsigned char kandotemp;
unsigned char kandotemp2[2];
unsigned char kandotemp5;
unsigned char kandoframecnt;
unsigned long attempts;
unsigned char controllingplayer;
unsigned char spiderframe[2];
unsigned char robotframe[2];
unsigned char ballframe;
unsigned char robotjumpframe[2];
unsigned char robotjumptime[2];
unsigned char level;
unsigned char level_data_bank;
unsigned char sprite_data_bank;
unsigned char menuselection;
unsigned char settingvalue;

unsigned char gameState;

unsigned char parallax_scroll_x;
unsigned char invincible_counter;
unsigned long int scroll_x; // gotta love massive levels amirite fellas
unsigned short scroll_y;
unsigned short target_scroll_y;
unsigned char song;
unsigned char auto_fs_updates;

unsigned char dashing[2];

unsigned char has_practice_point = 0;
unsigned short practice_player_x[2];
unsigned short practice_player_y[2];
unsigned char practice_player_gamemode;
unsigned char practice_mini;
unsigned char practice_dual;
unsigned char practice_speed;
unsigned short practice_cube_rotate[2];
signed short practice_player_vel_x[2];
signed short practice_player_vel_y[2];
unsigned char practice_player_gravity[2];
unsigned long int practice_scroll_x;
unsigned short practice_scroll_y;
unsigned char practice_parallax_scroll_column;
unsigned char practice_parallax_scroll_column_start;
unsigned char practice_g_color;
unsigned char practice_bg_color;
unsigned char practice_g_color_type;
unsigned char practice_bg_color_type;

// the funny uh uhhhhh um the uhh sprite storidge
// X_lowbyte, X_highbyte, Y_lowbyte, Y_highbyte, object id, unused, unused, unused
#define max_loaded_sprites 16
unsigned short activesprites_x[max_loaded_sprites];
unsigned short activesprites_y[max_loaded_sprites];
unsigned char activesprites_type[max_loaded_sprites];
unsigned char activesprites_anim_frame[max_loaded_sprites];
signed char activesprites_anim_frame_count[max_loaded_sprites];

unsigned char activesprites_realx[max_loaded_sprites];
unsigned char activesprites_realy[max_loaded_sprites];
unsigned char activesprites_active[max_loaded_sprites];



unsigned char DEBUG_MODE = 0;
unsigned char lastgcolortype;
unsigned char lastbgcolortype;
unsigned char iconbank;
unsigned char kandowavewalk;

unsigned char player_old_posy[8];
unsigned char asdftemp;
unsigned char discorefreshrate;
unsigned char whichpcm;

#define UP_WALK 0x01
#define LEFT_WALK 0x02
#define DOWN_WALK 0x04

unsigned char spiderwalk;
/*
unsigned char gnd_palette_transition_timer;
unsigned char original_gnd_palette_idx_0;
unsigned char original_gnd_palette_idx_1;
unsigned char original_gnd_palette_color_0;
unsigned char original_gnd_palette_color_1;

unsigned char bg_palette_transition_timer;
unsigned char original_bg_palette_idx_0;
unsigned char original_bg_palette_idx_1;
unsigned char original_bg_palette_idx_2;
unsigned char original_bg_palette_color_0;
unsigned char original_bg_palette_color_1;
unsigned char original_bg_palette_color_2;

unsigned char current_transition_timer_length;
*/

unsigned char kandowatchesyousleep;	//variable to say whether to go back to main menu or level select

unsigned short songtimer;

//struct player {
//	unsigned short x; // low byte is sub-pixel
//	unsigned short y;
//	signed short vel_x; // speed, signed, low byte is sub-pixel
//	signed short vel_y;
//};

//struct player player = {0x0000,0xb000};

//struct player2 {
//	unsigned short x; // low byte is sub-pixel
//	unsigned short y;
//	signed short vel_x; // speed, signed, low byte is sub-pixel
//	signed short vel_y;
//};

//struct player2 player2 = {0x0000,0xb000};

struct Base {
	unsigned char x;
	unsigned char y;
	unsigned char width;
	unsigned char height;
};

struct Base Generic;
struct Base Generic2;





const unsigned char paletteDefault[16] = {
    0x11,0x0c,0x0f,0x30,	// palette 0, used for level tiles
	0x00,0x01,0x11,0x30,	// palette 1, used for ground
	0x00,0x88,0x14,0x30,	// palette 2, UNUSED
	0x00,0x0f,0x00,0x30 	// palette 3, used for text
};

const unsigned char paletteDefaultSP[16]={
	0x00,0x0f,0x2a,0x21,
	0x00,0x0f,0x24,0x28,
	0x00,0x0f,0x16,0x30,
	0x00,0x0f,0x2a,0x21,
};

const unsigned char paletteMenu[16] = {
	0x17,0x0f,0x10,0x30,
	0x17,0x0f,0x2a,0x28,
	0x17,0x0f,0x17,0x27,
	0x17,0x0f,0x11,0x30
};
const unsigned char paletteSettings[16] = {
	0x17,0x0f,0x10,0x30,
	0x17,0x0f,0x2a,0x28,
	0x17,0x0F,0x16,0x26,
	0x17,0x0f,0x11,0x30
};

const unsigned char splashMenu[16] = {
    0x11,0x0f,0x10,0x30,
    0x11,0x0f,0x2a,0x28,
    0x11,0x0f,0x11,0x27,
    0x11,0x0f,0x11,0x30
};




