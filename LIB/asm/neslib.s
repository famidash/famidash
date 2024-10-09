;NES hardware-dependent functions by Shiru (shiru@mail.ru)
;with improvements by VEG
;Feel free to do anything you want with this code, consider it Public Domain

;for nesdoug version 1.2, 1/1/2022
;changed nmi to prevent possible incomplete sprite
;added a little bit at the end of _flush_vram_update
;changed the name of flush_vram_update_nmi to flush_vram_update2

;minor change %%, added ldx #0 to functions returning char
;removed sprid from c functions to speed them up

  .import _use_auto_chrswitch

	.export _pal_all,_pal_bg,_pal_spr,_pal_clear
	.export _pal_bright
	.export _ppu_off,_ppu_on_all,_ppu_on_bg,_ppu_on_spr,_ppu_mask,_ppu_system
	.export _oam_clear,_oam_clear_player,__oam_spr,__oam_meta_spr,_oam_clear_two_players
	;.export _oam_hide_rest,_oam_size,_bank_bg,_rand8
	.export _ppu_wait_frame,_ppu_wait_nmi
	.export __scroll,_split,_newrand
	.export _bank_spr
	.export __vram_read,__vram_write
	.export _rand16,_set_rand
	.export __vram_fill,_vram_inc,_vram_unrle
	.export __memcpy,__memfill,_delay
	
	.export _flush_vram_update2, _oam_set, _oam_get

	.segment "NESLIB"

;NMI handler

nmi:
	pha
	txa
	pha
	tya
	pha

	lda <PPU_MASK_VAR	;if rendering is disabled, do not access the VRAM at all
	sta PPU_MASK
	and #%00011000
	bne @renderingOn
	jmp	@skipAll
	
@renderingOn:	
	lda <VRAM_UPDATE ;is the frame complete?
	bne @doUpdate
	jmp @skipAll ;skipUpd

@doUpdate:
	lda #0
	sta <VRAM_UPDATE

	; lda <PPU_MASK_VAR
	; and #%11100111		;	Disable BG and sprites
	; ora #%11100000		;	Enable dark emphasis
	; sta PPU_MASK

  ; If nametables are updating, don't do the palette update this frame
	lda <NAME_UPD_ENABLE
	beq @checkPal
  ; don't run palette switches on the same frame that we flush vram to save time
  lda VRAM_BUF
  cmp #$ff
  beq @checkPal
	  jsr _flush_vram_update2
    jmp @skipUpd
@checkPal:
	lda <PAL_UPDATE		;update palette if needed
	bne @updPal
	jmp @skipUpd

@updPal:

	ldx #0
	stx <PAL_UPDATE

	lda #$3f
	sta PPU_ADDR
	stx PPU_ADDR

  lda #<PAL_BUF-1
  jsr palette_popslide_buffer

@skipUpd:

	lda #0
	sta PPU_ADDR
	sta PPU_ADDR

	lda <SCROLL_X
	sta PPU_SCROLL
	lda <SCROLL_Y
	sta PPU_SCROLL

	lda <PPU_CTRL_VAR
	sta PPU_CTRL

  lda _use_auto_chrswitch
  beq :+
    jsr _set_tile_banks
  :

  lda #0
  sta mmc3IRQTableIndex
  sta mmc3IRQJoever
  jsr irq_parser ; needs to happen inside v-blank... 
                   ; so goes before the music
            ; but, if screen is off this should be skipped
  
  ; Read the raw controller data synced with OAM DMA to prevent
  ; DMC DMA bugs
  jsr oam_and_readjoypad

  ; Calculate the press/release for the controllers
  ; and also update mouse X/Y coords after the timing sensitive parts
  ; of NMI are complete
  jsr calculate_extra_fields

@skipAll:

	inc <FRAME_CNT1
	inc <FRAME_CNT2

	lda auto_fs_updates
	beq :+
	jsr _music_update
	:

	pla
	tay
	pla
	tax
	pla
	rti

;irq: ;OLD IRQ LABEL; NOW FILLED BY mapper_irq.s
;    rti



;void __fastcall__ pal_all(const void *data);

_pal_all:

	sta <PTR
	stx <PTR+1
	ldx #$00
	lda #$20

pal_copy:

	sta <LEN

	ldy #$00

@0:

	lda (PTR),y
	sta PAL_BUF_RAW,x
	inx
	iny
	dec <LEN
	bne @0

  ldx #32 - 1
@loop:
    ldy PAL_BUF_RAW,x
    lda (PAL_PTR),y
    sta PAL_BUF,x
    dex
    bpl @loop

	inc <PAL_UPDATE

	rts



;void __fastcall__ pal_bg(const void *data);

_pal_bg:

	sta <PTR
	stx <PTR+1
	ldx #$00
	lda #$10
	bne pal_copy ;bra



;void __fastcall__ pal_spr(const void *data);

_pal_spr:

	sta <PTR
	stx <PTR+1
	ldx #$10
	txa
	bne pal_copy ;bra



;void __fastcall__ pal_col(uint8_t index, uint8_t color);

; _pal_col:

; 	sta <PTR
; 	jsr popa
; 	and #$1f
; 	tax
; 	lda <PTR
; 	sta PAL_BUF,x
; 	inc <PAL_UPDATE
; 	rts

; this is faster

;void __fastcall__ _pal_col(uint16_t data);

; __pal_col:
; 	sta PAL_BUF,x
; 	inc <PAL_UPDATE
; 	rts

; and then this is inlined


;void __fastcall__ pal_clear();

_pal_clear:

	lda #$0f
	ldx #0

@1:

	sta PAL_BUF,x
	inx
	cpx #$20
	bne @1
	stx <PAL_UPDATE
	rts



;void __fastcall__ pal_spr_bright(uint8_t bright);

; _pal_spr_bright:

; 	tax
; 	lda palBrightTableL,x
; 	sta <PAL_SPR_PTR
; 	lda palBrightTableH,x	;MSB is never zero
; 	sta <PAL_SPR_PTR+1
; 	sta <PAL_UPDATE
; 	rts



; ;void __fastcall__ pal_bg_bright(uint8_t bright);

; _pal_bg_bright:

; 	tax
; 	lda palBrightTableL,x
; 	sta <PAL_BG_PTR
; 	lda palBrightTableH,x	;MSB is never zero
; 	sta <PAL_BG_PTR+1
; 	sta <PAL_UPDATE
; 	rts



;void __fastcall__ pal_bright(uint8_t bright);

_pal_bright:
  tax
	lda palBrightTableL,x
	sta <PAL_PTR
	lda palBrightTableH,x	;MSB is never zero
	sta <PAL_PTR+1
  ldx #32 - 1
@loop:
    ldy PAL_BUF_RAW, x
    lda (PAL_PTR), y
    sta PAL_BUF,x
    dex
    bpl @loop
	sta <PAL_UPDATE
  rts
	; jsr _pal_spr_bright
	; txa
	; jmp _pal_bg_bright



;void __fastcall__ ppu_off();

_ppu_off:

	lda <PPU_MASK_VAR
	and #%11100111
	sta <PPU_MASK_VAR
	jmp _ppu_wait_nmi



;void __fastcall__ ppu_on_all();

_ppu_on_all:

	lda <PPU_MASK_VAR
	ora #%00011000

ppu_onoff:

	sta <PPU_MASK_VAR
	jmp _ppu_wait_nmi



;void __fastcall__ ppu_on_bg();

_ppu_on_bg:

	lda <PPU_MASK_VAR
	ora #%00001000
	bne ppu_onoff	;bra



;void __fastcall__ ppu_on_spr();

_ppu_on_spr:

	lda <PPU_MASK_VAR
	ora #%00010000
	bne ppu_onoff	;bra



;void __fastcall__ ppu_mask(uint8_t mask);

_ppu_mask:

	sta <PPU_MASK_VAR
	rts



;uint8_t __fastcall__ ppu_system();

_ppu_system:

	lda <NTSC_MODE
	ldx #0
	rts



;void __fastcall__ oam_clear();

_oam_clear:

	ldx #0
	stx SPRID ; automatically sets sprid to zero
	dex
.repeat 64, I
	stx OAM_BUF + (I * 4)
.endrepeat
	rts
	
;void __fastcall__ oam_clear_player();
.importzp _gamemode
_oam_clear_player:
	ldx #0
	stx SPRID ; automatically sets sprid to zero
	dex
	stx OAM_BUF+0
	stx OAM_BUF+4
	pha
	lda _gamemode
	cmp #4
	beq @more
	cmp #5
	beq @more	
	pla
	rts	
@more:
	pla
	stx OAM_BUF+8
	rts
	
;void __fastcall__ oam_set(uint8_t index);	
;to manually set the position
;a = sprid

_oam_clear_two_players:
	ldx #0
	stx SPRID ; automatically sets sprid to zero
	dex
	stx OAM_BUF+0
	stx OAM_BUF+4
	stx OAM_BUF+8
	stx OAM_BUF+12
	pha
	lda _gamemode
	cmp #4
	beq @more
	cmp #5
	beq @more
	pla
	rts
@more:
	pla
	stx OAM_BUF+16
	stx OAM_BUF+20
	rts
;void __fastcall__ oam_set(uint8_t index);	
;to manually set the position
;a = sprid

_oam_set:
	and #$fc ;strip those low 2 bits, just in case
	sta SPRID
	rts
	
	
;uint8_t __fastcall__ oam_get();	
;returns the sprid

_oam_get:
	lda SPRID
	ldx #0
	rts
	



;void __fastcall__ oam_size(uint8_t size);

;_oam_size:

;	and #1
;	php
;	lda <PPU_CTRL_VAR
;	and #%11011111
;	plp
;	beq :+
;		ora #%00100000
;	:
;	sta <PPU_CTRL_VAR

;	rts



;void __fastcall__ oam_spr(uint8_t x, uint8_t y, uint8_t chrnum, uint8_t attr);
;sprid removed

__oam_spr:
	; a = attr
	; x = chrnum
	; sreg[0] = x
	; sreg[1] = y

	ldy SPRID
	;a = attr
	sta OAM_BUF+2,y

	txa	; tile
	sta OAM_BUF+1,y
	lda sreg+1	; y
	sta OAM_BUF+0,y
	lda sreg+0	; x
	sta OAM_BUF+3,y

	tya
	clc
	adc #4
	sta SPRID
	rts



;void __fastcall__ oam_meta_spr(uint8_t x, uint8_t y,const uint8_t *data);
;sprid removed

__oam_meta_spr:
	; AX = data
	; sreg[0] = x
	; sreg[1] = y

	sta <PTR
	stx <PTR+1

	ldy #0

oam_meta_spr_params_set:	; Put &data into PTR, X and Y into SCRX and SCRY respectively
	
	ldx SPRID

@1:

	lda (PTR),y		;x offset
	cmp #$80
	beq @2
	iny
	clc
	adc sreg+0	; x
	bcc @fuck_yes
	cpx #$00
	beq @fuck_yes	; no idea why I need to do this
	lda #$f8
	iny
	clc
	bcc @hell_yes
	@fuck_yes:
	sta OAM_BUF+3,x
	lda (PTR),y		;y offset
	iny
	clc
	adc sreg+1	; y
	@hell_yes:
	sta OAM_BUF+0,x
	lda (PTR),y		;tile
	iny
	sta OAM_BUF+1,x
	lda (PTR),y		;attribute
	iny
	sta OAM_BUF+2,x
	inx
	inx
	inx
	inx
	jmp @1

@2:

	stx SPRID
	rts



;void __fastcall__ oam_hide_rest();
;sprid removed

;_oam_hide_rest:

;	ldx SPRID
;	lda #240

;@1:

;	sta OAM_BUF,x
;	inx
;	inx
;	inx
;	inx
;	bne @1
;	;x is zero
;	stx SPRID
;	rts



;void __fastcall__ ppu_wait_frame();

_ppu_wait_frame:

	lda #1
	sta <VRAM_UPDATE
	lda <FRAME_CNT1

@1:

	cmp <FRAME_CNT1
	beq @1
	lda <NTSC_MODE
	beq @3

@2:

	lda <FRAME_CNT2
	cmp #5
	beq @2

@3:

	rts



;void __fastcall__ ppu_wait_nmi();

_ppu_wait_nmi:

	lda #1
	sta <VRAM_UPDATE
	lda <FRAME_CNT1
@1:

	cmp <FRAME_CNT1
	beq @1
	rts



;void __fastcall__ vram_unrle(const void *data);

_vram_unrle:

	tay
	stx <RLE_HIGH
	lda #0
	sta <RLE_LOW

	lda (RLE_LOW),y
	sta <RLE_TAG
	iny
	bne @1
	inc <RLE_HIGH

@1:

	lda (RLE_LOW),y
	iny
	bne @11
	inc <RLE_HIGH

@11:

	cmp <RLE_TAG
	beq @2
	sta PPU_DATA
	sta <RLE_BYTE
	bne @1

@2:

	lda (RLE_LOW),y
	beq @4
	iny
	bne @21
	inc <RLE_HIGH

@21:

	tax
	lda <RLE_BYTE

@3:

	sta PPU_DATA
	dex
	bne @3
	beq @1

@4:

	rts



;void __fastcall__ _scroll(uint16_t x, uint16_t y);

__scroll:
	; ax = y
	; sreg = x

	sta <TEMP

	txa
	bne @1
	lda <TEMP
	cmp #240
	bcs @1
	sta <SCROLL_Y
	lda #0
	sta <TEMP
	beq @2	;bra

@1:

	sec
	lda <TEMP
	sbc #240
	sta <SCROLL_Y
	lda #2
	sta <TEMP

@2:

	lda sreg
	sta <SCROLL_X
	lda sreg+1
	and #$01
	ora <TEMP
	sta <TEMP
	lda <PPU_CTRL_VAR
	and #$fc
	ora <TEMP
	sta <PPU_CTRL_VAR
	rts



;;void __fastcall__ split(uint16_t x);
;minor changes %%
_split:

;	jsr popax
	sta <SCROLL_X1
	txa
	and #$01
	sta <TEMP
	lda <PPU_CTRL_VAR
	and #$fc
	ora <TEMP
	sta <PPU_CTRL_VAR1

@3:

	bit PPU_STATUS
	bvs @3

@4:

	bit PPU_STATUS
	bvc @4

	lda <SCROLL_X1
	sta PPU_SCROLL
	lda #0
	sta PPU_SCROLL
	lda <PPU_CTRL_VAR1
	sta PPU_CTRL

	rts

.proc palette_popslide_buffer
  tsx
  stx SP_TEMP
  tax
  txs
  ; global bg color
  pla
  tax
  stx PPU_DATA
  ; each palette
.repeat 8, I
  pla
  sta PPU_DATA
  pla
  sta PPU_DATA
  pla
  sta PPU_DATA
  .if I <> 7
  pla
  stx PPU_DATA
  .endif
.endrepeat
  
  ldx SP_TEMP
  txs
  rts
.endproc

;void __fastcall__ bank_spr(uint8_t n);

_bank_spr:

	and #1
	php
	lda <PPU_CTRL_VAR
	and #%11110111
	plp
	beq :+
		ora #%00001000
	:
	sta <PPU_CTRL_VAR

	rts



;void __fastcall__ bank_bg(uint8_t n);

;_bank_bg:

;	and #1
;	php
;	lda <PPU_CTRL_VAR
;	and #%11101111
;	plp
;	beq :+
;		ora #%00010000
;	:
;	sta <PPU_CTRL_VAR

;	rts



;void __fastcall__ vram_read(void *dst, uint16_t size);

__vram_read:

	; ax = size
	; sreg = dst

	sta <TEMP
	stx <TEMP+1

	; jsr popax
	; sta sreg
	; stx sreg+1

	lda PPU_DATA

	ldy #0

@1:

	lda PPU_DATA
	sta (sreg),y
	inc sreg
	bne @2
	inc sreg+1

@2:

	lda <TEMP
	bne @3
	dec <TEMP+1

@3:

	dec <TEMP
	lda <TEMP
	ora <TEMP+1
	bne @1

	rts



;void __fastcall__ vram_write(void *src, uint16_t size);

__vram_write:
	; ax = size
	; sreg = src

	sta <TEMP
	stx <TEMP+1

	; jsr popax
	; sta <sreg
	; stx <sreg+1

	ldy #0

@1:

	lda (sreg),y
	sta PPU_DATA
	inc <sreg
	bne @2
	inc <sreg+1

@2:

	lda <TEMP
	bne @3
	dec <TEMP+1

@3:

	dec <TEMP
	lda <TEMP
	ora <TEMP+1
	bne @1

	rts

;uint8_t __fastcall__ pad_poll(uint8_t pad);

; _pad_poll:

; 	tay
; 	ldx #3

; @padPollPort:

; 	lda #1
; 	sta CTRL_PORT1
; 	sta <PAD_BUF-1,x
; 	lda #0
; 	sta CTRL_PORT1
; 	lda #8
; 	sta <TEMP

; @padPollLoop:

; 	lda CTRL_PORT1,y
; 	lsr a
; 	rol <PAD_BUF-1,x
; 	bcc @padPollLoop

; 	dex
; 	bne @padPollPort

; 	lda <PAD_BUF
; 	cmp <PAD_BUF+1
; 	beq @done
; 	cmp <PAD_BUF+2
; 	beq @done
; 	lda <PAD_BUF+1

; @done:

; 	sta <PAD_STATE,y
; 	tax
; 	eor <PAD_STATEP,y
; 	and <PAD_STATE ,y
; 	sta <PAD_STATET,y
; 	txa
; 	sta <PAD_STATEP,y
	
; 	ldx #0
; 	rts



; ;uint8_t __fastcall__ pad_trigger(uint8_t pad);

; _pad_trigger:

; 	pha
; 	jsr _pad_poll
; 	pla
; 	tax
; 	lda <PAD_STATET,x
; 	ldx #0
; 	rts



; ;uint8_t __fastcall__ pad_state(uint8_t pad);

; _pad_state:

; 	tax
; 	lda <PAD_STATE,x
; 	ldx #0
; 	rts



;uint8_t __fastcall__ rand8();
;Galois random generator, found somewhere
;out: A random number 0..255


_newrand:
	ldy #8
	lda RAND_SEED+0
:
	asl
	rol RAND_SEED+1
	rol RAND_SEED+2
	rol RAND_SEED+3
	bcc :+
	eor #$C5
:
	dey
	bne :--
	sta RAND_SEED+0
	cmp #0
	rts

rand1:

	lda <RAND_SEED
	asl a
	bcc @1
	eor #$cf

@1:

	sta <RAND_SEED
	rts

rand2:

	lda <RAND_SEED+1
	asl a
	bcc @1
	eor #$d7

@1:

	sta <RAND_SEED+1
	rts

;_rand8:

;	jsr rand1
;	jsr rand2
;	adc <RAND_SEED
;	ldx #0
;	rts



;uint16_t __fastcall__ rand16();

_rand16:

	jsr rand1
	tax
	jsr rand2

	rts


;void __fastcall__ set_rand(uint8_t seed);

_set_rand:

	sta <RAND_SEED
	stx <RAND_SEED+1

	rts


;void __fastcall__ flush_vram_update(void *buf);

_flush_vram_update:

	; sta <NAME_UPD_ADR+0
	; stx <NAME_UPD_ADR+1

_flush_vram_update2: ;minor changes %

	ldy #0

@updName:

	lda VRAM_BUF,y
	iny
	cmp #$40				;is it a non-sequental write?
	bcs @updNotSeq
	sta PPU_ADDR
	lda VRAM_BUF,y
	iny
	sta PPU_ADDR
	lda VRAM_BUF,y
	iny
	sta PPU_DATA
	jmp @updName

@updNotSeq:

	tax
	lda <PPU_CTRL_VAR
	cpx #$80				;is it a horizontal or vertical sequence?
	bcc @updHorzSeq
	cpx #$ff				;is it end of the update?
	beq @updDone

@updVertSeq:

	ora #$04
	bne @updNameSeq			;bra

@updHorzSeq:

	and #$fb

@updNameSeq:

	sta PPU_CTRL

	txa
	and #$3f
	sta PPU_ADDR
	lda VRAM_BUF,y
	iny
	sta PPU_ADDR
	lda VRAM_BUF,y
	bmi @updRepeatedByte
	iny
	tax

@updNameLoop:

	lda VRAM_BUF,y
	iny
	sta PPU_DATA
	dex
	bne @updNameLoop

	lda <PPU_CTRL_VAR
	sta PPU_CTRL

	jmp @updName

@updRepeatedByte:
	and #$7f
	tax
	iny
	lda VRAM_BUF,y
	iny
@updRepeatedByteLoop:
	sta PPU_DATA
	dex
	bne @updRepeatedByteLoop
	
	lda <PPU_CTRL_VAR
	sta PPU_CTRL

	jmp @updName


@updDone:
;changed to automatically clear these
.ifdef VRAM_BUF
	ldx #$ff
	stx VRAM_BUF
	inx ;x=0
	stx VRAM_INDEX
.endif
	rts
	
	
	
;void __fastcall__ vram_adr(uintptr_t adr);

; _vram_adr:

; 	stx PPU_ADDR
; 	sta PPU_ADDR

; 	rts



;void __fastcall__ vram_put(uint8_t n);

; _vram_put:

; 	sta PPU_DATA

; 	rts



;void __fastcall__ vram_fill(uint8_t n, uint16_t len);

__vram_fill:
	; a = n
	; x = hi(len)
	; sreg[0] = lo(len) 

	; sta <LEN
	; stx <LEN+1
	; jsr popa
	; ldx <LEN+1
	cpx #0
	beq @2
	ldy #0

@1:

	sta PPU_DATA
	dey
	bne @1
	dex
	bne @1

@2:

	ldx sreg
	beq @4

@3:

	sta PPU_DATA
	dex
	bne @3

@4:

	rts



;void __fastcall__ vram_inc(uint8_t n);

_vram_inc:

	ora #0
	beq @1
	lda #$04

@1:

	sta <TEMP
	lda <PPU_CTRL_VAR
	and #$fb
	ora <TEMP
	sta <PPU_CTRL_VAR
	sta PPU_CTRL

	rts



;void __fastcall__ memcpy(void *dst, void *src, uint16_t len);

__memcpy:

	; AX = len
	; sreg = src
	; xargs[0:1] = dst

	sta <LEN
	stx <LEN+1

	ldx #0

@1:

	lda <LEN+1
	beq @2
	jsr @3
	dec <LEN+1
	inc sreg+1
	inc xargs+1
	jmp @1

@2:

	ldx <LEN
	beq @5

@3:

	ldy #0

@4:

	lda (sreg),y
	sta (xargs),y
	iny
	dex
	bne @4

@5:

	rts



;void __fastcall__ memfill(void *dst, uint8_t value, uint16_t len);

__memfill:

	; A = value
	; sreg = len
	; xargs[0:1] = dst

	ldx #0

@hi_loop:

	cpx sreg+1	; x is always 0 at this point
	beq @lo_start
	jsr @fill_start
	dec sreg+1
	inc xargs+1
	jmp @hi_loop

@lo_start:

	ldx sreg
	beq @end

@fill_start:

	ldy #0

@fill_loop:

	sta (xargs),y
	iny
	dex
	bne @fill_loop

@end:

	rts



;void __fastcall__ delay(uint8_t frames);

_delay:

	tax

@1:

	jsr _ppu_wait_nmi
	dex
	bne @1

	rts



palBrightTableL:

	.byte <palBrightTable0,<palBrightTable1,<palBrightTable2
	.byte <palBrightTable3,<palBrightTable4,<palBrightTable5
	.byte <palBrightTable6,<palBrightTable7,<palBrightTable8

palBrightTableH:

	.byte >palBrightTable0,>palBrightTable1,>palBrightTable2
	.byte >palBrightTable3,>palBrightTable4,>palBrightTable5
	.byte >palBrightTable6,>palBrightTable7,>palBrightTable8

palBrightTable0:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f	;black
palBrightTable1:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable2:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable3:
	.byte $0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f,$0f
palBrightTable4:
	.byte $00,$01,$02,$03,$04,$05,$06,$07,$08,$09,$0a,$0b,$0c,$0d,$0e,$0f	;normal colors
palBrightTable5:
	.byte $10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$1a,$1b,$1c,$1d,$1e,$1f
palBrightTable6:
	.byte $10,$21,$22,$23,$24,$25,$26,$27,$28,$29,$2a,$2b,$2c,$2d,$2e,$2f	;$10 because $20 is the same as $30
palBrightTable7:
	.byte $30,$31,$32,$33,$34,$35,$36,$37,$38,$39,$3a,$3b,$3c,$3d,$3e,$3f
palBrightTable8:
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30	;white
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30
	.byte $30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30,$30

.repeat 9, I
.export .ident(.sprintf("palBrightTable%d", I))
.endrepeat


; Quick macros to reserve a value and export it for usage in C
.macro RESERVE name, size
  .export .ident(.sprintf("_%s", .string(name))) = .ident(.string(name)) 
  .ident(.string(name)): .res size
.endmacro
.macro RESERVE_ZP name, size
  .exportzp .ident(.sprintf("_%s", .string(name))) = .ident(.string(name)) 
  .ident(.string(name)): .res size
.endmacro


.pushseg

.segment "ZEROPAGE"

; NOTE: These must be zero page and adjacent; the code relies on joypad1_down following mouse.
RESERVE_ZP mouse, 4
  kMouseZero = 0
  kMouseButtons = 1
  kMouseY = 2
  kMouseX = 3
RESERVE_ZP joypad1, 3
; Overlay the second joypad with the mouse memory.
; If the mouse isn't detected, then we copy data to the joypad struct.
joypad2 = mouse + 1
.exportzp _joypad2 := joypad2

; Store a pointer to the current controlling player's joypad
; for fast access
RESERVE_ZP controllingplayer, 2

; Bitmask indicating which $4016/7 bit the mouse is on.
; Must be in ZP for now for timing reasons
RESERVE_ZP mouse_mask, 1

.if 0
.segment "BSS"
; NOTE: These variables are not page-sensitive and can be absolute.
advance_sensitivity: .res 1  ; Bool.
.endif

.segment "OAMALIGN"

MOUSE_PORT = CTRL_PORT2
CONTROLLER_PORT = CTRL_PORT1


.proc oam_and_readjoypad
  ; save the previous controller state for calcuating the previous results
  lda joypad1
  sta TEMP + 3

  ; and do the same for the controller 2
  lda joypad2
  sta TEMP + 4

  ; Save the previous mouse state so we can calculate the next frames press/release
  lda mouse + kMouseY
  sta TEMP + 0
  lda mouse + kMouseX
  sta TEMP + 1
  lda mouse + kMouseButtons
  sta TEMP + 2

  ; Strobe the joypads.
  LDX #$00
  LDY #$01
  STY mouse
  STY CTRL_PORT1

 .if 0
  ; Clock official mouse sensitivity. NOTE: This can be removed if not needed.
  LDA advance_sensitivity
  BEQ :+
  LDA MOUSE_PORT
  STX advance_sensitivity
 :
 .endif

  STX CTRL_PORT1

  LDA #>OAM_BUF
  STA PPU_OAM_DMA
 
  ; Desync cycles: 432, 576, 672, 848, 432*2-4 (860)

  ; DMC DMA:         ; PUT GET PUT GET        ; Starts: 0

 :
  LDA mouse_mask     ; get put get*     *576  ; Starts: 4, 158, 312, 466, [620]
  AND MOUSE_PORT   ; put get put GET
  CMP #$01           ; put get
  ROL mouse,X        ; put get put get* PUT GET  *432
  BCC :-             ; put get (put)

  INX                ; put get
  CPX #$04           ; put get
  STY mouse,X        ; put get put GET
  BNE :-             ; put get (put)

 :
  LDA CONTROLLER_PORT ; put get put GET        ; Starts: 619
  AND #$03           ; put get*         *672
  CMP #$01           ; put get
  ROL joypad1 ; put get put get put    ; This can desync, but we finish before it matters.
  BCC :-             ; get put (get)

 .if 0 ; TODO support SNES extra buttons 
  STY joypad1+1 ; get put get
  NOP                ; put get
 :
  LDA CONTROLLER_PORT ; put get* put GET *848  ; Starts: 751, [879]
  AND #$03           ; put get
  CMP #$01           ; put get
  ROL joypad1+1 ; put get put get put    ; This can desync, but we finish before it matters.
  BCC :-             ; get* put (get)   *860

  ; NEXT: 878
 .endif ; CONTROLLER_SIZE = 2

  rts
.endproc

.segment "STARTUP"

.proc calculate_extra_fields
  ; calculate the press/release state for the controller buttons

  ; Pressed
  lda TEMP+3
  eor #%11111111
  and joypad1
  sta joypad1 + 1

  ; Released
  lda joypad1
  eor #%11111111
  and TEMP+3
  sta joypad1 + 2

  ; Check the report to see if we have a snes mouse plugged in
  lda mouse + kMouseButtons
  and #$0f
  cmp #$01
  beq snes_mouse_detected
    ; treat this as a standard NES controller instead and
    ; calculate the press/release for it
    lda mouse + kMouseZero
    sta joypad2
    ; Pressed
    lda TEMP+4
    eor #%11111111
    and joypad2
    sta joypad2 + 1

    ; Released
    lda joypad2
    eor #%11111111
    and TEMP+4
    sta joypad2 + 2

    ; no snes mouse, so leave the first field empty
    lda #0
    sta mouse + kMouseZero
    rts
snes_mouse_detected:

  ; convert the X/Y displacement into X/Y positions on the screen
  ldx #1
loop:
    lda mouse + kMouseY,x
    bpl :+
      ; subtract the negative number instead
      and #$7f
      sta mouse + kMouseZero ; reuse this value as a temp value
      lda TEMP,x
      sec 
      sbc mouse + kMouseZero
      ; check if we underflowed
      bcc wrappednegative
      ; check the lower bounds
      cmp MouseBoundsMin,x
      bcs setvalue ; didn't wrap so set the value now
    wrappednegative:
      lda MouseBoundsMin,x
      jmp setvalue
    :
    ; add the positive number
    clc
    adc TEMP,x
    ; check if we wrapped, set to the max bounds if we did
    bcs wrapped
    ; check the upper bounds
    cmp MouseBoundsMax,x
    bcc setvalue ; didn't wrap so set the value
wrapped:
    lda MouseBoundsMax,x
setvalue:
    sta mouse + kMouseY,x
    dex
    bpl loop
  ; calculate newly pressed buttons and shift it into byte zero
  lda TEMP+2
  eor #%11000000
  and mouse + kMouseButtons
  rol
  ror mouse + kMouseZero
  rol
  ror mouse + kMouseZero
  
  ; calculate newly released buttons
  lda mouse + kMouseButtons
  eor #%11000000
  and TEMP+2
  rol
  ror mouse + kMouseZero
  rol
  ror mouse + kMouseZero

  ; Set the connected bit
  sec
  ror mouse + kMouseZero

  rts

MOUSE_Y_MINIMUM = 1
MOUSE_X_MINIMUM = 1
MOUSE_Y_MAXIMUM = 239
MOUSE_X_MAXIMUM = 255

MouseBoundsMin:
  .byte MOUSE_Y_MINIMUM, MOUSE_X_MINIMUM
MouseBoundsMax:
  .byte MOUSE_Y_MAXIMUM, MOUSE_X_MAXIMUM
.endproc

.popseg

SLOPESA = 14
.import _spike_set, _block_set, _saw_set
.import _no_parallax, _parallax_scroll_x, _level
.export _set_tile_banks
.proc _set_tile_banks
	; inlined into ASM so we can call it from NMI
	ldx _level
	; if no parallax is 1, then it will maybe add an offset to the chr
	; other wise it will add 0 (effectively disabling it without branching)
	lda _no_parallax
  eor #1
	and _parallax_scroll_x
	sta CHRBANK_TEMP
	clc
	lda _spike_set,x
	adc CHRBANK_TEMP
	jsr _mmc3_set_1kb_chr_bank_0
	lda _block_set,x
	adc CHRBANK_TEMP
	jsr _mmc3_set_1kb_chr_bank_1
	lda _saw_set,x
	adc CHRBANK_TEMP
	jsr _mmc3_set_1kb_chr_bank_3
	; and then decide on the last bank
	lda _no_parallax
	beq :+
		lda #SLOPESA
		jmp _mmc3_set_1kb_chr_bank_2
	:
	lda _parallax_scroll_x
	adc #<.bank(_PARALLAX_CHR)
	jmp _mmc3_set_1kb_chr_bank_2
.endproc
