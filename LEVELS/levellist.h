// LEVEL ORDERING =============================================
// 
// NOTE: DO *NOT* PUT LEVEL DATA HERE.
// Level order is defined here, and consists of 3 tables. The 
// first table specifies the level data pointers, the second -
// sprite data pointers, and the third one - the ROM bank of 
// the level data. Here is an example:
//
// const unsigned char * const your_moms_house[] = {
//    level_name_1_, 
//    level_name_2_,
//    level_name_3_
//  };
//
// const unsigned char * const your_moms_sprites[] = {
//    level_name_1_SP,
//    level_name_2_SP,
//    level_name_3_SP,
// };
//
// const unsigned char your_moms_bank_account[] = {
//    0, // Level data starts in bank 0,
//    1,
//    2,
// }
// ============================================================
// go wild

#define	EASY 0
#define	NORMAL 1
#define	HARD 2
#define	HARDER 3
#define	INSANE 4
#define	DEMON 5
#define	DANGER 6


#define SPIKESA 0
#define SPIKESB 2
#define BLOCKSA 4
#define BLOCKSB 6
#define BLOCKSC 8
#define BLOCKSD 10
#define SAWBLADESA 12

const uint8_t difficulty_pal_A[] ={
	0x21,	// easy
	0x2A,	// normal
	0x28,	// hard
	0x16,	// harder
	0x24,	// insane
	0x16,	// demon
	0x13,	// danger
};

const uint8_t difficulty_pal_B[] ={
	0x06,	// easy
	0x30,	// normal
	0x30,	// hard
	0x30,	// harder
	0x06,	// insane
	0x30,	// demon
	0x21,	// danger
};

const unsigned short songtime[] = {	//for looping in practice mode
	5160, //stereo madness
	4900, //back on track
	5465, //polargeist
	4940, //dryout
	15000, //base after base
	4900, //cant let go
	5285, //jumper
	15000, //time machine
	5240, //cycles
	15000, //xstep
	15000, //clutterfunk
	15000, //TOE
	15000, //Electroman
	15000, //decode
	15000, //t1
	15000, //t2
	14000, //t3
	14000, //t4
	14000, //danger
};

const unsigned char spike_set[] = {
	SPIKESA, //stereo madness
	SPIKESA, //back on track
	SPIKESA, //polargeist
	SPIKESA, //dryout
	SPIKESA, //base after base
	SPIKESA, //cant let go
	SPIKESA, //jumper
	SPIKESA, //time machine
	SPIKESA, //cycles
	SPIKESB, //xstep
	SPIKESB, //clutterfunk
	SPIKESB, //theory of everything
	SPIKESB, //electroman
	SPIKESB, //decode
	SPIKESB, //test1
	SPIKESB, //test2
	SPIKESB, //test3
	SPIKESB, //test4
	SAWBLADESA, //danger
};

const unsigned char block_set[] = {
	BLOCKSA, //stereo madness
	BLOCKSA, //back on track
	BLOCKSA, //polargeist
	BLOCKSA, //dryout
	BLOCKSA, //base after base
	BLOCKSA, //cant let go
	BLOCKSA, //jumper
	BLOCKSA, //time machine
	BLOCKSA, //cycles
	BLOCKSC, //xstep
	BLOCKSD, //clutterfunk
	BLOCKSB, //theory of everything
	BLOCKSB, //electroman
	BLOCKSB, //decode
	BLOCKSC, //test1
	BLOCKSB, //test2
	BLOCKSA, //test3
	BLOCKSA, //test4
	SAWBLADESA, //danger
};

const unsigned char saw_set[] = {
	SAWBLADESA, //stereo madness
	SAWBLADESA, //back on track
	SAWBLADESA, //polargeist
	SAWBLADESA, //dryout
	SAWBLADESA, //base after base
	SAWBLADESA, //cant let go
	SAWBLADESA, //jumper
	SAWBLADESA, //time machine
	SAWBLADESA, //cycles
	SAWBLADESA, //xstep
	SAWBLADESA, //clutterfunk
	SAWBLADESA, //theory of everything
	SAWBLADESA, //electroman
	SAWBLADESA, //decode
	SAWBLADESA, //test1
	SAWBLADESA, //test2
	SAWBLADESA, //test3
	SAWBLADESA, //test4
	SAWBLADESA, //danger
};


const unsigned char difficulty_list[] = {
    EASY,
    EASY,
    NORMAL,
    NORMAL,
    HARD,
    HARD,
    HARDER,
    HARDER,
    HARDER,
    INSANE,
    INSANE,
    INSANE,
    INSANE,
    DEMON,
    DEMON,
    DEMON,
    DEMON,
    DEMON,
DANGER,
};

const unsigned char stars_list[] = {
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	8,
	9,
	10,
	11,
	12,
	10,
	10,
	0,
	0,
	0,
	0,
	69,
};
const unsigned char colors_list[] = {
	0x12,
	0x14,
	0x15,
	0x16,
	0x17,
	0x28,
	0x2A,
	0x2C,
	0x11,
	0x12,
	0x14,
	0x15,
	0x16,
	0x15,
	0x05,
	0x06,
	0x07,
	0x08,
	0x0F,
};
// exported from export_levels.py

extern const unsigned char level_list_lo[];
extern const unsigned char level_list_hi[];
extern const unsigned char level_list_bank[];
extern const unsigned char sprite_list_lo[];
extern const unsigned char sprite_list_hi[];
extern const unsigned char sprite_list_bank[];