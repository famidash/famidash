// Custom functions implemented specifically for famidash (some are totally not stolen from famitower)

// replacements for C stack

extern unsigned char xargs[4];
#pragma zpsym("xargs")
#define wxargs ((unsigned short * const)xargs)
#define pxargs ((const void ** const)xargs)

#define storeWordToSreg(word) (__AX__ = word, __EAX__<<=16)
#define storeBytesToSreg(a, b) (__AX__ = (byte(b)<<8)|byte(a), __EAX__<<=16)
#define storeByteToSreg(byte) (__A__ = byte, __asm__("sta sreg+0"))

//set metasprite in OAM buffer (vertically flipped)
//meta sprite is a const unsigned char array, it contains four bytes per sprite
//in order x offset, y offset, tile, attribute
//x=128 is end of a meta sprite
// Note: sprid removed for speed
void __fastcall__ _oam_meta_spr_flipped(unsigned long args);
#define oam_meta_spr_flipped(flip, x, y, data)(xargs[0] = flip, storeBytesToSreg(x, y), __AX__ = (unsigned int)data, _oam_meta_spr_flipped(__EAX__))

/**
 * ======================================================================================================================
 * famistudio_music_play (public)
 * 
 * Plays a song from and loads the music data according to the bank.
 * 
 * [in] song_index : Song index.
 * ======================================================================================================================
 */
void __fastcall__ music_play(unsigned char song);

/**
 * ======================================================================================================================
 * famistudio_update (public)
 * 
 * Main update function, should be called once per frame, ideally at the end of NMI. Will update the tempo, advance
 * the song if needed, update instrument and apply any change to the APU registers.
 * 
 * [in] no input params.
 * ======================================================================================================================
 */
void __fastcall__ music_update (void);

/**
 * ======================================================================================================================
 * famistudio_sfx_play (public)
 * 
 * Plays a sound effect.
 * 
 * [in] sfx_index: Sound effect index (0...127)
 * [in] channel: Offset of sound effect channel, should be FAMISTUDIO_SFX_CH0..FAMISTUDIO_SFX_CH3
 * ======================================================================================================================
 */

void __fastcall__ _sfx_play(unsigned int args);
#define sfx_play(sfx_index, channel) (__AX__ = (unsigned int)(byte(channel))<<8|sfx_index, _sfx_play(__AX__))

/**
 * Update the PPU using the VRAM buffer with a single tile repeated LENGTH number of times.
 * Length must not be greater than 0x7f!
 */
void __fastcall__ _one_vram_buffer_repeat(unsigned long args);
#define one_vram_buffer_horz_repeat(data, len, ppu_address) (storeBytesToSreg(data, len), __A__ = LSB(ppu_address), __AX__<<=8, __AX__ |= MSB(ppu_address)|NT_UPD_HORZ, _one_vram_buffer_repeat(__EAX__))
#define one_vram_buffer_vert_repeat(data, len, ppu_address) (storeBytesToSreg(data, len), __A__ = LSB(ppu_address), __AX__<<=8, __AX__ |= MSB(ppu_address)|NT_UPD_VERT, _one_vram_buffer_repeat(__EAX__))

void __fastcall__ _draw_padded_text(unsigned long args);
#define draw_padded_text(data, len, total_len, ppu_address) (pxargs[0] = data, storeBytesToSreg(total_len, len), __A__ = LSB(ppu_address), __AX__<<=8, __AX__ |= MSB(ppu_address)|NT_UPD_HORZ, _draw_padded_text(__EAX__))

void __fastcall__ playPCM();

extern unsigned char parallax_scroll_column;
extern unsigned char parallax_scroll_column_start;


#define low_word(a) *((unsigned short*)&a)
#define high_word(a) *((unsigned short*)&a+1)

#define vram_adr(a) (POKE(0x2006, MSB(a)), POKE(0x2006, LSB(a)))
#define vram_put(a) POKE(0x2007, a)

#define GET_BANK(sym) (__asm__("ldx #0\nlda #<.bank(%v)", sym), __A__)

// limit stuff to certain amounts
#define byte(x) (((x)&0xFF))
#define word(x) (((x)&0xFFFF))

// add byte with No Overflow Check
#define addNOC_b(a, b) byte(byte(a)+b)
// add word with No Overflow Check beyond the 16 bits
#define addNOC_w(a, b) word(word(a)+b)

// add to the low byte of a word, not overflowing into high
#define addloNOC(a, b) (addNOC_b(a, b))|(a & 0xFF00)

// subtract byte with No Overflow Check
#define subNOC_b(a, b) byte(byte(a)-b)
// subtract word with No Overflow Check beyond the 16 bits
#define subNOC_w(a, b) word(word(a)-b)

// subtract from the low byte of a word, not overflowing into high
#define subloNOC(a, b) (subNOC_b(a, b))|(a & 0xFF00)

// get specific byte from a word array
#define idx16_lo(arr, idx) (*(((char * const)arr)+((idx<<1))))
#define idx16_hi(arr, idx) (*(((char * const)(arr+1))+((idx<<1))))

// same as above but idx < 128
#define idx16_lo_NOC(arr, idx) (__A__ = idx<<1, __asm__("tay\n lda %v, y", arr), __A__)
#define idx16_hi_NOC(arr, idx) (__A__ = idx<<1, __asm__("tay\n lda %v+1, y", arr), __A__)

// store a word's high and low bytes into separate places
#define storeWordSeparately(word, low, high) \
                            (__AX__ = word, \
                            __asm__("STA %v", low), \
                            __asm__("STX %v", high))

extern unsigned char auto_fs_updates;
#define pal_fade_to_withmusic(from, to) (++auto_fs_updates, pal_fade_to(from, to), auto_fs_updates = 0)

// Yes i had to actually fucking use inline asm to get this to run fast
#define store_short_arr_NOC(arr, idx, word) ( \
    __A__ = idx<<1, \
    __asm__("tay"), \
    __A__ = LSB(word), \
    __asm__("sta %v,y", arr), \
    __A__ = MSB(word), \
    __asm__("sta %v+1, y", arr))

// set palette color, index 0..31
// completely inlines and replaces neslib's
extern unsigned char PAL_UPDATE;
extern char PAL_BUF[32];
#pragma zpsym("PAL_UPDATE")
#define pal_col(index, color) do { PAL_BUF[index&0x1F] = (color); ++PAL_UPDATE; } while(0);

#define swapbyte(a, b) do { \
  __A__ = (a); \
  __asm__("pha"); \
  (a) = (b); \
  __asm__("pla"); \
  (b) = __A__; \
} while(0);
