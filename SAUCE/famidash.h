#define MENUBANK 60
#define MENUICONBANK 64
#define LEVELCOMPLETEBANK 68

#define SPIKESA 0
#define SPIKESB 2
#define BLOCKSA 4
#define BLOCKSB 6
#define BLOCKSC 8
#define SAWBLADESA 10
#define SLOPESA 12

// game states
#define MENU 0x01
#define GAME 0x02


#define MAX_ICONS 14 //total icons

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
#define MINI_CUBE_MAX_FALLSPEED 0x600

#define CUBE_GRAVITY 0x6B
#define MINI_CUBE_GRAVITY 0x6F

#define UFO_GRAVITY 0x47
#define MINI_UFO_GRAVITY 0x57

#define BALL_GRAVITY 0x5D
#define BALL_MAX_FALLSPEED 0x600
#define MINI_BALL_GRAVITY 0x57
#define MINI_BALL_MAX_FALLSPEED 0x600

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

uint8_t tmp1;
uint8_t tmp2;
uint8_t tmp3;
uint8_t tmp4;
uint16_t tmp5;
uint16_t tmp6;
uint8_t tmp7;
uint8_t tmp8;
uint8_t tmp9;
uint8_t* tmpptr1;
uint8_t* tmpptr2;
uint32_t tmplong;
uint8_t selectedbgm;
uint8_t selectedsfx;

#pragma zpsym("tmpptr1")
#pragma zpsym("tmpptr2")

uint16_t currplayer_x;
uint16_t currplayer_y;
int16_t currplayer_vel_x;
int16_t currplayer_vel_y;
uint8_t currplayer_gravity;

uint8_t pad[2];
uint8_t pad_new[2];

uint8_t gamemode;
uint8_t cube_data[2];
uint16_t cube_rotate[2];

uint8_t collision;
uint8_t collision_L;
uint8_t collision_R;
uint8_t collision_U;
uint8_t collision_D;

uint16_t old_x;
uint16_t old_y;

uint8_t mini;
uint8_t eject_L; // from the left
uint8_t eject_R; // remember these from the collision sub routine
uint8_t eject_D; // from below
uint8_t eject_U; // from up

uintptr_t address;
uint8_t x; // room loader code
uint8_t y;
uint8_t index;
uint8_t temp_x;
uint8_t temp_y;
uint8_t temp_room;
uint8_t dual;
int8_t slope_frames;

uint8_t slope_type;
uint8_t was_on_slope_counter;
uint8_t * sprite_data;
uint8_t * level_data;

#pragma zpsym("sprite_data")
#pragma zpsym("level_data")

#pragma bss-name(pop)
// other variables go here

#pragma bss-name(push, "SRAM")
uint8_t SRAM_VALIDATE[4];

#define LEVEL_COUNT 0x10
uint8_t coin1_obtained[LEVEL_COUNT];
uint8_t coin2_obtained[LEVEL_COUNT];
uint8_t coin3_obtained[LEVEL_COUNT];

uint8_t LEVELCOMPLETE[LEVEL_COUNT];

uint8_t invisible;
uint8_t PRACTICE_ENABLED = 1;
uint8_t twoplayer;

/* memory optimization */
//uint8_t oneptwoplayer;
//uint8_t jumpsound;
//uint8_t platformer;
//uint8_t musicoff;
//uint8_t sfxoff;
uint8_t options;
#define oneptwoplayer 0x01
#define jumpsound 0x02
#define platformer 0x04

#define sfxoff 0x40
#define musicoff 0x80


uint8_t icon;

uint8_t color1;
uint8_t color2;
uint8_t color3;

uint8_t discomode;

uint8_t trails;

uint8_t decorations;

uint8_t retro_mode;
uint8_t achievements[20];
//uint8_t practice_famistudio_state[0xbf];
uint8_t collisionMap0[240];   // collision map, for a 16*27 tile area
uint8_t collisionMap1[192];

#pragma bss-name(pop)



//extern uint8_t famistudio_state[0xbf];


uint8_t TOTALCOINS;
uint32_t TOTALCOINSTEMP;
uint8_t TOTALATTEMPTSHUNDREDS;
uint8_t TOTALATTEMPTSTHOUSANDS;
uint8_t TOTALCOINSTENS;
uint8_t TOTALCOINSONES;
uint8_t TOTALSTARS;
uint8_t TOTALSTARSONES;
uint8_t TOTALSTARSTENS;


uint16_t player_x[2];
uint16_t player_y[2];
int16_t player_vel_x[2];
int16_t player_vel_y[2];
uint8_t player_gravity[2];


uint8_t rld_column;
uint8_t spr_index;
uint8_t long_temp_x;

uint8_t speed;
uint8_t shuffle_offset;
uint8_t count;
uint8_t coins;
uint8_t currplayer;
uint8_t kandotemp;
uint8_t kandotemp2[2];
uint8_t kandotemp5;
uint8_t kandoframecnt;
uint32_t attempts;
uint8_t controllingplayer;
uint8_t spiderframe[2];
uint8_t robotframe[2];
uint8_t ballframe;
uint8_t robotjumpframe[2];
uint8_t robotjumptime[2];
uint8_t level;
uint8_t level_data_bank;
uint8_t sprite_data_bank;
uint8_t menuselection;
uint8_t settingvalue;

uint8_t gameState;

uint8_t parallax_scroll_x;
uint8_t invincible_counter;
uint32_t scroll_x; // gotta love massive levels amirite fellas
uint16_t scroll_y;
uint16_t target_scroll_y;
uint8_t song;

uint8_t dashing[2];

uint8_t has_practice_point = 0;
uint16_t practice_player_x[2];
uint16_t practice_player_y[2];
uint8_t practice_player_gamemode;
uint8_t practice_mini;
uint8_t practice_dual;
uint8_t practice_speed;
uint16_t practice_cube_rotate[2];
int16_t practice_player_vel_x[2];
int16_t practice_player_vel_y[2];
uint8_t practice_player_gravity[2];
uint32_t practice_scroll_x;
uint16_t practice_scroll_y;
uint8_t practice_parallax_scroll_column;
uint8_t practice_parallax_scroll_column_start;
uint8_t practice_g_color;
uint8_t practice_bg_color;
uint8_t practice_g_color_type;
uint8_t practice_bg_color_type;

// the funny uh uhhhhh um the uhh sprite storidge
// X_lowbyte, X_highbyte, Y_lowbyte, Y_highbyte, object id, unused, unused, unused
#define max_loaded_sprites 16
uint16_t activesprites_x[max_loaded_sprites];
uint16_t activesprites_y[max_loaded_sprites];
uint8_t activesprites_type[max_loaded_sprites];
uint8_t activesprites_anim_frame[max_loaded_sprites];
int8_t activesprites_anim_frame_count[max_loaded_sprites];

uint8_t activesprites_realx[max_loaded_sprites];
uint8_t activesprites_realy[max_loaded_sprites];
uint8_t activesprites_active[max_loaded_sprites];



uint8_t DEBUG_MODE = 0;
uint8_t lastgcolortype;
uint8_t lastbgcolortype;
uint8_t iconbank;
uint8_t kandowavewalk;

uint8_t player_old_posy[8];
uint8_t discorefreshrate;
uint8_t no_parallax;
uint8_t outline_color;
/*
uint8_t gnd_palette_transition_timer;
uint8_t original_gnd_palette_idx_0;
uint8_t original_gnd_palette_idx_1;
uint8_t original_gnd_palette_color_0;
uint8_t original_gnd_palette_color_1;

uint8_t bg_palette_transition_timer;
uint8_t original_bg_palette_idx_0;
uint8_t original_bg_palette_idx_1;
uint8_t original_bg_palette_idx_2;
uint8_t original_bg_palette_color_0;
uint8_t original_bg_palette_color_1;
uint8_t original_bg_palette_color_2;

uint8_t current_transition_timer_length;
*/

uint8_t kandowatchesyousleep;	//variable to say whether to go back to main menu or level select

uint16_t songtimer;

//struct player {
//	uint16_t x; // low byte is sub-pixel
//	uint16_t y;
//	int16_t vel_x; // speed, signed, low byte is sub-pixel
//	int16_t vel_y;
//};

//struct player player = {0x0000,0xb000};

//struct player2 {
//	uint16_t x; // low byte is sub-pixel
//	uint16_t y;
//	int16_t vel_x; // speed, signed, low byte is sub-pixel
//	int16_t vel_y;
//};

//struct player2 player2 = {0x0000,0xb000};

struct Base {
	uint8_t x;
	uint8_t y;
	uint8_t width;
	uint8_t height;
};

struct Base Generic;
struct Base Generic2;





const uint8_t paletteDefault[16] = {
    0x11,0x01,0x0F,0x30,	// palette 0, used for level tiles
	0x00,0x01,0x11,0x30,	// palette 1, used for ground
	0x00,0x01,0x0F,0x2A,	// palette 2, used for decorations
	0x00,0x0F,0x00,0x30 	// palette 3, used for text
};

const uint8_t paletteDefaultSP[16]={
	0x00,0x0f,0x2a,0x21,
	0x00,0x0f,0x24,0x28,
	0x00,0x0f,0x16,0x30,
	0x00,0x0f,0x2a,0x21,
};

const uint8_t paletteMenu[16] = {
	0x17,0x0f,0x10,0x30,
	0x17,0x0f,0x2a,0x28,
	0x17,0x0f,0x17,0x27,
	0x17,0x0f,0x11,0x30
};
const uint8_t paletteSettings[16] = {
	0x17,0x0f,0x10,0x30,
	0x17,0x0f,0x2a,0x28,
	0x17,0x0F,0x16,0x26,
	0x17,0x0f,0x11,0x30
};

const uint8_t splashMenu[16] = {
    0x11,0x0F,0x11,0x30,
    0x11,0x0F,0x2A,0x28,
    0x11,0x0F,0x11,0x27,
    0x11,0x0F,0x11,0x30
};

const uint8_t iconBankTable[] = {
	14, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52, 54, 56, 58
};

