; Startup code for cc65 and Shiru's NES library
; based on code by Groepaz/Hitmen <groepaz@gmx.net>, Ullrich von Bassewitz <uz@cc65.org>

;REMOVED initlib
;this called the CONDES function
.include "BUILD_FLAGS.s"

.exportzp _VRAM_UPDATE := VRAM_UPDATE

    .export _exit,__STARTUP__:absolute=1
	.export _PAL_BUF := PAL_BUF, _PAL_UPDATE := PAL_UPDATE, _xargs := xargs
	.import push0,popa,popax,_main

; Linker generated symbols
	.import __C_STACK_START__, __C_STACK_SIZE__
	.import __PAL_BUF_START__, __OAM_BUF_START__, __VRAM_BUF_START__
	.import	__CODE_LOAD__   ,__CODE_RUN__   ,__CODE_SIZE__
	.import	__RODATA_LOAD__ ,__RODATA_RUN__ ,__RODATA_SIZE__

	.import MAPPER, SUBMAPPER, MIRRORING, PRG_BANK_COUNT, CHR_BANK_COUNT, SRAM, TRAINER, CONSOLE_TYPE, PRG_RAM_COUNT, PRG_NVRAM_COUNT, CHR_RAM_COUNT, CHR_NVRAM_COUNT, CPU_PPU_TIMING, HARDWARE_TYPE, MISC_ROMS, DEF_EXP_DEVICE
	.import FIRST_MUSIC_BANK, FIRST_DMC_BANK, _SRAM_VALIDATE

VRAM_BUF=__VRAM_BUF_START__
OAM_BUF=__OAM_BUF_START__
PAL_BUF=__PAL_BUF_START__

.importzp _PAD_STATE, _PAD_STATET ;added
.include "zeropage.inc"




PPU_CTRL	=$2000
PPU_MASK	=$2001
PPU_STATUS	=$2002
PPU_OAM_ADDR=$2003
PPU_OAM_DATA=$2004
PPU_SCROLL	=$2005
PPU_ADDR	=$2006
PPU_DATA	=$2007
PPU_OAM_DMA	=$4014
PPU_FRAMECNT=$4017
DMC_FREQ	=$4010
CTRL_PORT1	=$4016
CTRL_PORT2	=$4017



.segment "ZEROPAGE"

NTSC_MODE: 			.res 1
FRAME_CNT1: 		.res 1
FRAME_CNT2: 		.res 1
VRAM_UPDATE: 		.res 1
NAME_UPD_ADR: 		.res 2
NAME_UPD_ENABLE: 	.res 1
PAL_UPDATE: 		.res 1
PAL_BG_PTR: 		.res 2
PAL_SPR_PTR: 		.res 2
SCROLL_X: 			.res 1
SCROLL_Y: 			.res 1
SCROLL_X1: 			.res 1
SCROLL_Y1: 			.res 1
PAD_STATE: 			.res 2		;one byte per controller
PAD_STATE2: 		.res 2		;one byte per controller
PAD_STATEP: 		.res 2
PAD_STATEP2: 		.res 2
PAD_STATET: 		.res 2
PAD_STATET2: 		.res 2
PPU_CTRL_VAR: 		.res 1
PPU_CTRL_VAR1: 		.res 1
PPU_MASK_VAR: 		.res 1
RAND_SEED: 			.res 4

TEMP: 				.res 11
SPRID:				.res 1

PAD_BUF		=TEMP+1

PTR			=TEMP	;word
LEN			=TEMP+2	;word
NEXTSPR		=TEMP+4
SCRX		=TEMP+5
SCRY		=TEMP+6
SRC			=TEMP+7	;word
DST			=TEMP+9	;word

RLE_LOW		=TEMP
RLE_HIGH	=TEMP+1
RLE_TAG		=TEMP+2
RLE_BYTE	=TEMP+3

VRAM_INDEX:			.res 1
; variables for nesdoug's metatile system
; META_PTR:			.res 2
; META_PTR2:		.res 2
; DATA_PTR:			.res 2
; META_VAR:			.res 1

xargs:				.res 4

;
; NES 2.0 header
;
.segment "HEADER"

    NES2_0_IDENTIFIER = %00001000

    .byte 'N', 'E', 'S', $1A ; ID
    .byte <PRG_BANK_COUNT
    .byte <CHR_BANK_COUNT
    .byte <(MIRRORING | (SRAM << 1) | (TRAINER << 2) | ((MAPPER & $00F) << 4))
    .byte <((MAPPER & $0F0) | CONSOLE_TYPE | NES2_0_IDENTIFIER)
    .byte <(((MAPPER & $F00) >> 8) | SUBMAPPER << 4)
    .byte <(((PRG_BANK_COUNT & $F00) >> 8) | ((CHR_BANK_COUNT & $F00) >> 4))
    .byte <(PRG_RAM_COUNT | (PRG_NVRAM_COUNT << 4))
    .byte <(CHR_RAM_COUNT | (CHR_NVRAM_COUNT << 4))
    .byte <CPU_PPU_TIMING, <HARDWARE_TYPE, <MISC_ROMS, <DEF_EXP_DEVICE

.segment "STARTUP"

start:
_exit:
	lda #%10000000					;	Stolen from initialize_mapper
	sta MMC3_REG_PRG_RAM_PROTECT	;__
    lda $00
    sta $7FFE
    lda $01
    sta $7FFF


    sei
	cld
	ldx #$40
	stx CTRL_PORT2
    ldx #$ff
    txs
    inx
    stx PPU_MASK
    stx DMC_FREQ
    stx PPU_CTRL		;no NMI

initPPU:
    bit PPU_STATUS
@1:
    bit PPU_STATUS
    bpl @1
@2:
    bit PPU_STATUS
    bpl @2

clearPalette:
	lda #$3f
	sta PPU_ADDR
	stx PPU_ADDR
	lda #$0f
	ldx #$20
@1:
	sta PPU_DATA
	dex
	bne @1

clearVRAM:
	txa
	ldy #$20
	sty PPU_ADDR
	sta PPU_ADDR
	ldy #$10
@1:
	sta PPU_DATA
	inx
	bne @1
	dey
	bne @1

clearRAM:
    txa
    ldy <_tmp2
@1:
    sta $00,x
    sta $100,x
    sta $200,x
    sta $300,x
    sta $400,x
    sta $500,x
    sta $600,x
    sta $700,x
	sta $6000,x
	sta $6100,x
    inx
    bne @1

    sty <_tmp2

	lda #4
	jsr _pal_bright
	jsr _pal_clear
	jsr _oam_clear

	jsr initialize_mapper

    ; jsr	zerobss	; Unnecessary, we already zeroed out the entire memory
	jsr	copydata	; Sets all the initial values of variables

    lda #<(__C_STACK_START__+__C_STACK_SIZE__) ;changed
    sta	sp
    lda	#>(__C_STACK_START__+__C_STACK_SIZE__)
    sta	sp+1            ; Set argument stack ptr

	; jsr	initlib	; removed. this called the CONDES function

	lda #%10100000
	sta <PPU_CTRL_VAR
	sta PPU_CTRL		;enable NMI
	lda #%00000110
	sta <PPU_MASK_VAR

waitSync3:
	lda <FRAME_CNT1
@1:
	cmp <FRAME_CNT1
	beq @1

detectNTSC:
	ldx #52				;blargg's code
	ldy #24
@1:
	dex
	bne @1
	dey
	bne @1

	lda PPU_STATUS
	and #$80
	sta <NTSC_MODE

	jsr _ppu_off

	lda #0
	ldx #0
	jsr _set_vram_update

	LDA #<FIRST_MUSIC_BANK-1	; Impossible to get otherwise
	STA current_song_bank		; Forces famistudio init on play

	ldx #<sounds
	ldy #>sounds
	jsr famistudio_sfx_init

	lda $60FC
	beq @fallback
	sta <RAND_SEED
	lda $60FD
	beq @fallback
	sta <RAND_SEED+1
	lda $60FE
	beq @fallback
	sta <RAND_SEED+2
	lda $60FF
	beq @fallback
	sta <RAND_SEED+3
        bne @done
@fallback:
	lda #$FD
	sta <RAND_SEED
	sta <RAND_SEED+1
	sta <RAND_SEED+2
	sta <RAND_SEED+3
@done:
	lda #0
	sta PPU_SCROLL
	sta PPU_SCROLL

	jmp _main			;no parameters

	.include "METATILES/metatiles.s"

	.include "LEVELS/all_level_data.s"
	.include "LEVELS/all_sprite_data.s"
	.include "LEVELS/level_header.s"
	.include "LEVELS/all_level_table.s"
	
	.include "mapper.s"
	.include "neslib.s"
	.include "nesdash.s"
	.include "nesdoug.s"
.segment "DMC_BANK_00"
	.incbin "MUSIC/EXPORTS/music_bank0.dmc"
.segment "DMC_BANK_01"
	.incbin "MUSIC/EXPORTS/music_bank1.dmc"

.segment "BSS"
.export _famistudio_state
_famistudio_state = *
.include "famistudio_ca65.s"
	

.segment "PCM_BANK"
GeometryDashPCMA:
	.incbin "MUSIC/PCM/geometry-dash2.pcm"
	.byte $00

.segment "PCM_BANK_B"
GeometryDashPCMB:
	.incbin "MUSIC/PCM/fire2.pcm"
	.byte $00


; Store music a switchable PRG bank
; .s files, as generated by FamiStudio through the export menu
.segment "MUS_BANK_00"
	.include "MUSIC/EXPORTS/music_1.s"
.segment "MUS_BANK_01"
	.include "MUSIC/EXPORTS/music_2.s"
.segment "MUS_BANK_02"
	.include "MUSIC/EXPORTS/music_3.s"
.segment "MUS_BANK_03"
	.include "MUSIC/EXPORTS/music_4.s"
.segment "MUS_BANK_04"
	.include "MUSIC/EXPORTS/music_5.s"

.segment "SFX"
	.include "MUSIC/EXPORTS/sfx.s"

.segment "COLLMAP0"
	collMap0:		.res 16*15
.segment "COLLMAP1"
	collMap1:		.res 16*12
	ground:			.res 16*3

.segment "VECTORS"

    .word nmi	;$fffa vblank nmi
    .word start	;$fffc reset
   	.word irq	;$fffe irq / brk



.segment "GAMECHR"
.export _GAME_CHR
_GAME_CHR:
 ;   .incbin "GRAPHICS/famidash.chr" ; 8kb		//default (0)
 ;   .incbin "GRAPHICS/famidash-parallax.chr" ; 4kb	//default (8)
 ;   .incbin "GRAPHICS/famidash2.chr" ; 8kb		//theory of everything (12)
 ;   .incbin "GRAPHICS/famidash-parallax2.chr" ; 4kb	//theory of everything (20)
   
    .incbin "GRAPHICS/SpikesA.chr" ; (0)
    .incbin "GRAPHICS/SpikesB.chr" ; (2)
    .incbin "GRAPHICS/BlocksA.chr" ; (4)
    .incbin "GRAPHICS/BlocksB.chr" ; (6)
    .incbin "GRAPHICS/BlocksC.chr" ; (8)
    .incbin "GRAPHICS/BlocksD.chr" ; (10)
    .incbin "GRAPHICS/SawbladesA.chr" ; (12)
    .incbin "GRAPHICS/slopesA.chr" ; (14)
    .incbin "GRAPHICS/slopesA.chr" ; ()
   
    .incbin "GRAPHICS/bankicon00.chr" ; 1kb (16)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankgamemodesA.chr" ; 1kb (18)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankgamemodesAretro.chr" ; 1kb (20)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankgamemodesB.chr" ; 1kb (22)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankgamemodesBretro.chr" ; 1kb (24)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankmain.chr" ; 1kb (26) 
    .incbin "GRAPHICS/bankblank.chr" ; 1kb
    .incbin "GRAPHICS/bankmain.chr" ; 1kb (28) 
    .incbin "GRAPHICS/bankblank2.chr" ; 1kb
    .incbin "GRAPHICS/bankmain.chr" ; 1kb (30) 
    .incbin "GRAPHICS/bankblankcloud.chr" ; 1kb
    .incbin "GRAPHICS/bankmain.chr" ; 1kb (32) 
    .incbin "GRAPHICS/bankblankcloud2.chr" ; 1kb
    .incbin "GRAPHICS/bankmain.chr" ; 1kb (34) 
    .incbin "GRAPHICS/bankblankfingerdash.chr" ; 1kb
    .incbin "GRAPHICS/bankmain.chr" ; 1kb (36) 
    .incbin "GRAPHICS/bankblankfingerdash2.chr" ; 1kb

    .incbin "GRAPHICS/so_retro_v2.chr" ; 1kb (38) 
    .incbin "GRAPHICS/bankportals.chr" ; 1kb

    .incbin "GRAPHICS/bankicon01.chr" ; 1kb (40) 
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon02.chr" ; 1kb (42)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon03.chr" ; 1kb (44)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon04.chr" ; 1kb (46)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon05.chr" ; 1kb (48)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon06.chr" ; 1kb (50)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon07.chr" ; 1kb (52)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon08.chr" ; 1kb (54)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon09.chr" ; 1kb (56)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon0A.chr" ; 1kb (58)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon0B.chr" ; 1kb (60)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon0C.chr" ; 1kb (62)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon0D.chr" ; 1kb (64)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon0E.chr" ; 1kb (66)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "GRAPHICS/bankicon0F.chr" ; 1kb (68)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest1.chr" ; 1kb (70)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest2.chr" ; 1kb (72)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest3.chr" ; 1kb (74)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest4.chr" ; 1kb (76)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest5.chr" ; 1kb (78)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest6.chr" ; 1kb (80)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest7.chr" ; 1kb (82)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest8.chr" ; 1kb (84)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contest9.chr" ; 1kb (86)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contestA.chr" ; 1kb (88)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb
    .incbin "fan icon collection/CONTEST WINNERS/contestB.chr" ; 1kb (90)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb




    .incbin "GRAPHICS/banktriangle.chr" ; 1kb (92)
    .incbin "GRAPHICS/bankportals.chr" ; 1kb


    .incbin "GRAPHICS/menus.chr"    ; 4kb (94)
    .incbin "GRAPHICS/menuicons.chr"    ; 4kb (98)
    .incbin "GRAPHICS/levelcomplete.chr"    ; 4kb (102)

.segment "PARALLAXCHR"
.export _PARALLAX_CHR
_PARALLAX_CHR:
	.incbin "GRAPHICS/parallax.chr" ; 144kb