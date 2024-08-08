#pragma code-name(push, "XCD_BANK_03")
#pragma data-name(push, "XCD_BANK_03") 
#pragma rodata-name(push, "XCD_BANK_03")

#include "defines/bg_charmap.h"
const char TEXT_iamgoingtocommitseveralwarcrimesifcc65doesntstopbeingapieceofshit[] = "YOUR SAVE FILE";

const char TEXT_isfora[] = "IS FOR A";
const char TEXT_new[] = "NEW";
const char TEXT_old[] = "OLD";
const char TEXT_version[] = "VERSION";

const char TEXT_a_createnew[] = "A: CREATE NEW SAVE";
const char TEXT_b_load[] = "B: LOAD ANYWAY";

void savefile_display(){
    multi_vram_buffer_horz(TEXT_iamgoingtocommitseveralwarcrimesifcc65doesntstopbeingapieceofshit, sizeof(TEXT_iamgoingtocommitseveralwarcrimesifcc65doesntstopbeingapieceofshit)-1, NTADR_A(2,4));
}

void state_savefile_validate(){
    // startup
    
    pal_fade_to(4,0);
    ppu_off();
    pal_col(0x00,0x0f);
    set_scroll_x(0);
    vram_adr(NTADR_A(0,0));
    vram_fill(0xFF, 0x3E0);
    vram_adr(NTADR_A(0,30));
    vram_fill(0x00, 0x20);



    // if save file version is incorrect //
    if ((SRAM_VALIDATE[2] != FLAG_SAVE_VER)) {
        savefile_display();
        multi_vram_buffer_horz(TEXT_isfora, sizeof(TEXT_isfora)-1, NTADR_A(17,4));
        multi_vram_buffer_horz("ER", 2, NTADR_A(5,5));
        if (SRAM_VALIDATE[2] > FLAG_SAVE_VER) multi_vram_buffer_horz(TEXT_new, sizeof(TEXT_new)-1, NTADR_A(2,5));
        else {
            one_vram_buffer('N', NTADR_A(25,4));
            multi_vram_buffer_horz(TEXT_old, sizeof(TEXT_old)-1, NTADR_A(2,5));
        }
        multi_vram_buffer_horz(TEXT_version, sizeof(TEXT_version)-1, NTADR_A(8,5));

        multi_vram_buffer_horz(TEXT_a_createnew, sizeof(TEXT_a_createnew)-1, NTADR_A(2,8));
        multi_vram_buffer_horz(TEXT_b_load, sizeof(TEXT_b_load)-1, NTADR_A(2,9));

        ppu_on_all();
        pal_fade_to(0,4);
        do {
            pad_poll_both();
            if (pad_new[0] & PAD_B) break;
            if (pad_new[0] & PAD_A){
                setdefaultoptions();
                break;
            }
        } while (1);

        gameState = 0x01;
        return; 
    }


    // if header is wrong //
    if (SRAM_VALIDATE[0] != 0x13
    || SRAM_VALIDATE[1] != 0x37
    || SRAM_VALIDATE[2] != FLAG_SAVE_VER
    || SRAM_VALIDATE[3] != 0x21) {
        savefile_display();
        multi_vram_buffer_horz("IS MISSING OR", 13, NTADR_A(17,4));
        multi_vram_buffer_horz("CORRUPT", 7, NTADR_A(2,5));

        multi_vram_buffer_horz("A: CREATE NEW SAVE", 18, NTADR_A(2,8));
        multi_vram_buffer_horz("B: LOAD ANYWAY", 14, NTADR_A(2,9));
        
        ppu_on_all();
        pal_fade_to(0,4);
        do {
            pad_poll_both();
            if (pad_new[0] & PAD_B) break;
            if (pad_new[0] & PAD_A){
                setdefaultoptions();
                break;
            }
        } while (1);

        gameState = 0x01;
        return; 
    }
    

    gameState = 0x01;
    return;
}











#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)