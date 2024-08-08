// Version number stuff

// uncomment to enable the version number on the title screen
#define FLAG_ENABLE_VER_NUM

// set to 1 if compiling demo/beta builds; else set to 0
#define FLAG_BETA_BUILD 1

// major version number. set if releasing a demo/beta.
#define FLAG_MAJ_VER '5'

// minor version number. disabled if FLAG_BETA_BUILD is set.
#define FLAG_MIN_VER '0'

// Set to 1 to make some code in nesdash.s slightly faster.
// Since the carts are gonna be multiregion and famiclones have
// issues supporting illegal opcodes, this should be disabled
// for physical cart releases
#define USE_ILLEGAL_OPCODES 0

// set to 1 to enable metatile printing
// #define PRINT_METATILES 1


// save file version. increment by 1 if the SRAM memory layout changes.
#define FLAG_SAVE_VER 0x99