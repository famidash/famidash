; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)
.importzp _gamemode
.importzp _tmp1, _tmp2, _tmp3, _tmp4, _tmp5, _tmp6, _tmp7, _tmp8  ; C-safe temp storage
.import pusha, pushax, callptr4
.import _scroll_x

.macpack longbranch

.importzp _level_data, _sprite_data
level_data = _level_data
sprite_data = _sprite_data

.define gamemode_count 9

.ifndef _USE_ILLEGAL_OPCODES
.define _USE_ILLEGAL_OPCODES 0
.endif

.define USE_ILLEGAL_OPCODES ::_USE_ILLEGAL_OPCODES

.macro INCW addr
	INC addr
	BNE :+
		INC addr+1
:
.endmacro

.macro incw addr
	INCW addr
.endmacro

.macro incw_check addr
	INC addr
	BNE :+
		jsr incwlvl_checkC000
:
.endmacro

; You get your arguments back in ptr3
.macro crossPRGBankJSR inArgCount, routine, bank
	.ifblank routine
		.error "Have to supply routine and argument count for crossPRGBankJSR"
	.endif

	.ifnblank bank
		LDY bank
	.else
		LDY #^routine
	.endif

	.ifnblank inArgCount
		.if inArgCount >= 2
			STX ptr3+1
		.endif
		.if inArgCount >= 1
			STA ptr3
		.endif
	.endif

	LDA #<routine
	LDX #>routine
	jsr crossPRGBankJump
.endmacro


.segment "ZEROPAGE"
	rld_value:      .res 1
	rld_run:        .res 1

.segment "BSS"
	; column buffer, to be pushed to the collision map
	; 15 metatiles in the top screen 
	; 12 metatiles in the bot screen
	; 3 metatiles in the ground
	columnBuffer:		.res 15 + 12 + 3

	current_song_bank:	.res 1
	scroll_count:		.res 1
	auto_fs_updates:	.res 1
	parallax_scroll_column: .res 1
	parallax_scroll_column_start: .res 1
	hexToDecOutputBuffer: .res 5

.export _scroll_count := scroll_count
.export _auto_fs_updates := auto_fs_updates
.export _parallax_scroll_column := parallax_scroll_column
.export _parallax_scroll_column_start := parallax_scroll_column_start
.export _hexToDecOutputBuffer := hexToDecOutputBuffer
.export _pad = PAD_STATEP
.export _pad_new = PAD_STATET

; Standard for function declaration here:
; C function name
; .segment declaration
; [ <empty line>
; imports ]
; <empty line>
; .export declaration
; the function itself

; void __fastcall__ oam_meta_spr_flipped(uint8_t x,uint8_t y,const void *data);
.segment "XCD_BANK_04"

.export __oam_meta_spr_flipped
.proc __oam_meta_spr_flipped
	; AX = data
	; sreg[0] = x
	; sreg[1] = y
	; xargs[0] = flip
	sta <PTR
	stx <PTR+1

	ldx SPRID
	ldy #0

loop:

	lda (PTR),y     ;x offset
	cmp #$80
	beq end
	iny
	clc
	BIT xargs+0 ;	Check for bit 6 (HFLIP)
	BVC :+		;__
	EOR #$FF	;	If HLIPd, then two's complement
	ADC #($100 - 8)	; Carry is clear
	SEC			;__
	:			;
	adc sreg+0
	sta OAM_BUF+3,x
	lda (PTR),y     ;y offset
	INY
	clc
	BIT xargs+0	;	Check for bit 7 (VFLIP)
	BPL :+		;__
	EOR #$FF	;   If VLIPd, then two's complement
	; ADC #($100 - 16)	; Carry is clear, Y is -16'd because of us using 8x16 mode
	SEC			;__
	:			;
	adc sreg+1
	sta OAM_BUF+0,x
	lda (PTR),y     ;tile
	iny
	sta OAM_BUF+1,x
	lda (PTR),y     ;attribute
	iny
	EOR xargs+0
	sta OAM_BUF+2,x
	.if USE_ILLEGAL_OPCODES
		txa			;	aka X += 4
		axs #<-4	;__
	.else
		inx
		inx
		inx
		inx
	.endif
	jmp loop

end:

	stx SPRID
	rts
.endproc

.segment "RODATA_2"

shiftBy4table:
	.byte $00, $10, $20, $30
	.byte $40, $50, $60, $70
	.byte $80, $90, $A0, $B0
	.byte $C0, $D0, $E0, $F0

.segment "CODE_2"

.export __one_vram_buffer_repeat
.proc __one_vram_buffer_repeat
	; xa = ppu_address
	; sreg[0] = data
	; sreg[1] = len
	ldy VRAM_INDEX
	sta VRAM_BUF, y
	txa
	sta VRAM_BUF+1, y
	; ptr1 lo byte is len, hi byte is character to repeat
	lda sreg+1
	ora #$80 ; set length + repeat byte
	sta VRAM_BUF+2, y
	lda sreg+0
	sta VRAM_BUF+3, y
	lda #$ff ;=NT_UPD_EOF
	sta VRAM_BUF+4, y
	tya
	clc
	adc #4
	sta VRAM_INDEX
	rts
.endproc

; void __fastcall__ init_rld(uint8_t level);
.segment "CODE_2"

.global _level_list_lo, _level_list_hi, _level_list_bank, _sprite_list_lo, _sprite_list_hi, _sprite_list_bank
.import _song, _speed, _lastgcolortype, _lastbgcolortype
.import _rld_column
.import _level_data_bank, _sprite_data_bank
.import _discomode

.export _init_rld
_init_rld:
	; A - the level ID

	; Get pointers:
	TAY						;__ Load pointer to tables
	LDA _sprite_list_lo,y	;
	STA _sprite_data+0		;__	Get low pointer to sprite data 
	LDA _sprite_list_hi,y	;
	STA _sprite_data+1		;__	Get high pointer to sprite data 
	LDA _sprite_list_bank,y	;   Get sprite data bank
	; CLC                     ;
	; ADC #<FIRST_SPRITE_BANK ;
	STA _sprite_data_bank	;__
	LDA _level_list_lo,y	;
	STA _level_data+0		;__	Get low pointer to level data 
	LDA _level_list_hi,y	;
	STA _level_data+1		;__	Get high pointer to level data 
	LDA _level_list_bank,y	;   Get level data bank
	STA _level_data_bank	;__
	
	JSR mmc3_set_prg_bank_1

	LDY #$00			;-  For both (zp),y addressing and rld_column
	STY _rld_column		;__ Reset scrolling

	; Read header
	LDA (level_data),y	;
	STA _song			;   Song number
	incw_check level_data

	LDA (level_data),y	;
	STA _gamemode		;   Starting level number
	incw_check level_data

	LDA (level_data),y	;
	STA _speed			;   Starting speed
	incw_check level_data

	LDA _discomode
	BNE @noset
	LDA (level_data),y	;	Starting BG color
	AND #$3F			;	Store normal color (pal_col(0, tmp2))
	STA PAL_BUF+0		;__ 
	ldx _lastbgcolortype
	cpx #$ff
	bne @noset
	STA _lastbgcolortype
@noset:
	TAX
	lda _discomode
	bne @nostore
	LDA palBrightTable3, X
	STA PAL_BUF+1		;__	Store faded color (pal_col(1, oneShadeDarker(tmp2))
	STA PAL_BUF+9		;__	Store faded color (pal_col(1, oneShadeDarker(tmp2))
@nostore:
	txa
	incw_check level_data

	LDA (level_data),y	;	Starting ground color
	AND #$3F			;	Store normal color (pal_col(6, tmp2))
	STA PAL_BUF+6		;__ 
	ldx _lastgcolortype
	cpx #$ff
	bne @noset2
	STA	_lastgcolortype
@noset2:
	TAX
	LDA palBrightTable3, X
	STA PAL_BUF+5		;__	Store faded color (pal_col(5, oneShadeDarker(tmp2)))
	incw_check level_data

	INC <PAL_UPDATE		;__ Yes, we do need to update the palette

SetupNextRLEByte:
    LDA (level_data),y	;
    bmi single_rle_byte	;	Load rld_run, ++level_data
    STA rld_run			;__ 
    incw_check level_data	;__

    LDA (level_data),y	;
    STA rld_value		;   Load rld_value, ++level_data
    ; JMP incwlvl_checkC000

    INC level_data
    BNE :+
incwlvl_checkC000:  ; clobbers nothing
		INC level_data+1
		bit level_data+1
		; since the high byte will only be $Ax or $Bx, when bit 6 is set then its rolled over to $c0
		bvc :+
		pha 
			; switch banks
			LDA #$A0            ;   Reset memory-mapped ptr
			STA level_data+1    ;__
			INC _level_data_bank ;_ Increment bank
			LDA _level_data_bank
			jsr mmc3_set_prg_bank_1 ;__ Switch the bank
		pla
	:   
	RTS
single_rle_byte:
	and #$7f
	sta rld_value
	lda #0
	sta rld_run
	incw_check level_data
	rts

; void unrle_next_column();
.segment "CODE_2"

.export _unrle_next_column
.proc _unrle_next_column

	; Count up to zero to remove a cmp instruction
	ldx #<-27
	ldy #$00
	lda rld_value

	@FirstLoop:
		sta columnBuffer - ($100 - 27), x
		dec rld_run
		bmi @UpdateValueRun
		inx 
		bmi @FirstLoop
		bpl @End ; Guaranteed jump
	
	@UpdateValueRun:
		; if bit 7 of the byte is set, then its a run of length 1
		; otherwise this is a length < 127 byte and we need to read another
		lda (level_data), y
		bmi @SingleByteRun
		sta rld_run               ;__ Load rld_run, ++level_data
		incw_check level_data     ;__

		lda (level_data), y       ;
		sta rld_value             ;   Load rld_value, ++level_data
		incw_check level_data

		lda rld_value
		inx 
		bmi @FirstLoop
		bpl @End ; Unconditional
	
	@SingleByteRun:
		and #$7f
		sta rld_value
		; y = 0
		sty rld_run
		incw_check level_data
		inx 
		bmi @FirstLoop
		; and then fallthrough to copying to the collision map

	@End:
	ldx _rld_column
	inx
	.if USE_ILLEGAL_OPCODES
		lda #$0F
		sax _rld_column
	.else
		txa
		and #$0F
		sta _rld_column
	.endif
	rts
.endproc

; void __fastcall__ dummy_unrle_columns(uint16_t columns);
.segment "CODE_2"

.import umul8x16r24m

.export _dummy_unrle_columns
.proc _dummy_unrle_columns
	lastType = tmp1	; 0 = group of bytes, FF = single byte
	mulIn0 = ptr3
	mulIn1 = ptr1
	mulRes0 = ptr1
	mulRes1 = ptr1+1
	mulRes2 = sreg
	start:
		; Multiply columns by level height
		sta mulIn0
		stx mulIn0+1
		and #$0F
		sta _rld_column
		lda #27
		sta mulIn1
		jsr umul8x16r24m
		; result now in ptr1:sreg[0],
		; y = 0 

		inc mulRes1		;	increment for beq ending condition
		inc mulRes2		;__

		lda mulRes0
		clc				;	Subtract 1 extra, rld_run after all
		sbc rld_run		;__
		sta mulRes0
		bcs loop
		
		dec mulRes1
		bne loop
		
		dec mulRes2
		beq end_early
		
	loop:
		lda (level_data),y	; either single-run value or run
		bmi single_byte

		incw_check level_data
		sta rld_run
		lda (level_data),y	; value
		tax
		incw_check level_data

		lda mulRes0
		clc	; subtract 1 extra
		sbc rld_run
		sta mulRes0
		bcs loop

		dec mulRes1
		bne loop
	
		dec mulRes2
		bne loop	; = BRA

	end_multi:
		stx rld_value
		; the remaining rld_run is 2's complement of (mulRes0 - 1)
	end_early:
		lda mulRes0
		eor #$FF
		sta rld_run
		rts


	single_byte:
		incw_check level_data

		dec mulRes0
		ldx mulRes0
		inx	; less bytes then cpx #$ff
		bne loop
		dec mulRes1
		bne loop
		dec mulRes2
		bne loop

	end_single:
		and #$7F
		sta rld_value
		sty rld_run	; y is still 0
		rts

; 6654 cycles elapsed @ $8A columns in
.endproc




.segment "XCD_BANK_01"

.proc writeToCollisionMap
	; We have 27 writes to make to the collision map, thats 27 * 6 bytes for an unrolled loop.
	; roughly twice the size for much more perf. ill probably make it back to loop
	ldx _rld_column
	.if USE_ILLEGAL_OPCODES
		dex
		lda #$0F
		axs #0
	.else
		dex
		txa
		and #$0F
		tax
	.endif
	.repeat 15, I
		lda columnBuffer + I
		sta collMap0 + I * 16, x
	.endrepeat
	.repeat 12, I
		lda columnBuffer+15 + I
		sta collMap1 + I * 16, x
	.endrepeat
	.repeat 3, I
		lda ground + I * 16, x
		sta columnBuffer+15+12+I
	.endrepeat
.endproc

; void draw_screen_R();
.segment "XCD_BANK_01"

.global metatiles_top_left, metatiles_top_right, metatiles_bot_left, metatiles_bot_right, metatiles_attr
.import _increase_parallax_scroll_column
.import _no_parallax, _invisblocks

.export _draw_screen_R
.proc _draw_screen_R

	TileSizeHi  = (15*2)+2+1
	TileSizeLo  = (15*2)+2+1

	TileOff0    = 0
	TileOff1    = 0+TileSizeHi
	TileEnd     = 0+TileSizeHi+TileSizeLo

	AttrSizeHi  = 8*3
	AttrSizeLo  = 8*3

	AttrOff0    = 0
	AttrOff1    = 0+AttrSizeHi
	AttrEnd     = 0+AttrSizeHi+AttrSizeLo

	CurrentRow = tmp1
	LoopCount = tmp2

	.export _draw_screen_R_frame0 := frame0
	.export _draw_screen_R_frame1 := frame1
	.export _draw_screen_R_frame2 := attributes
	; Write architecture:

	; Frame 0:
	;   Write 0 updates the upper nametable's left tiles
	;   Write 1 updates the lower nametable's left tiles
	; Frame 1:
	;   Write 0 updates the upper nametable's right tiles
	;   Write 1 updates the lower nametable's right tiles
	; Frame 2:
	;   Attributes 

	start:
		
		LDA _scroll_x			;__ Highbyte of scroll_x
		LSR						;
		LSR						;   >> 4
		LSR						;
		LSR						;__
		STA tmp4

		LDX scroll_count
		BNE frame2

		LDA tmp4
		CMP _rld_column			;   If X == rld column, decompress shit
		BEQ frame0

		TXA	; It would've branched if it was not 0
		RTS
    
	frame2:
		CPX #$01
		BEQ frame1
		JMP attributes

	frame0:
		; Switch banks
		crossPRGBankJSR ,_unrle_next_column,_level_data_bank
		JSR writeToCollisionMap

	frame1:

			; Writing to nesdoug's VRAM buffer starts here
			LDX VRAM_INDEX

			; In-house replacement of get_ppu_addr, only counts X
			; Address is big-endian
			LDY _rld_column ;   000xxxx0 - the left tiles of the metatiles
			DEY
			TYA
			AND #$0F
			ASL         ;__
			LDY scroll_count
			BEQ :+
				ORA #$01    ;   000xxxx1 - the right tiles of the metatiles
			:
			STA VRAM_BUF+TileOff0+1,X
			STA VRAM_BUF+TileOff1+1,X

			lda _scroll_x + 1 ; high byte
			and #%00000001
			eor #%00000001
			asl
			asl
			ora #($20+$80)  ; 0th nametable + NT_UPDATE_VERT
			STA VRAM_BUF+TileOff0,X
			ORA #$08        ; 2nd nametable
			STA VRAM_BUF+TileOff1,X


			; First part of the update: the tiles
			; Amount of data in the sequence - 27*2 tiles (8x8 tiles, left sides of the metatiles)
			LDA #(15*2)
			STA VRAM_BUF+TileOff0+2,X
			STA VRAM_BUF+TileOff1+2,X

			; The sequence itself:
			
			; Load Y value
			LDY #$00
			sty CurrentRow
			; Load max value
			LDA #15 - 1
			STA LoopCount
			; Check if doing a left or right hand write
			LDA scroll_count
			AND #1
			beq @LeftWrite
				; Right side write
				; Call for upper tiles
				JSR right_tilewriteloop
				BMI @WriteBottomHalf	; The loop keeps looping via a BPL, therefore a BMI = BRA
			@LeftWrite:
				JSR left_tilewriteloop
		@WriteBottomHalf:
			; Load new max
			LDA #15 - 1
			STA LoopCount
			; Add offset to X
			.if USE_ILLEGAL_OPCODES
				TXA
				AXS #<-(TileSizeHi-(15*2))
			.else
				TXA
				CLC
				ADC #(TileSizeHi-(15*2))
				TAX
			.endif
			
			LDA scroll_count
			AND #1
			beq @LeftWrite2
				JSR right_tilewriteloop
				BMI @RenderParallax	; The loop keeps looping via a BPL, therefore a BMI = BRA
			@LeftWrite2:
				; Call for lower tiles
				JSR left_tilewriteloop
		@RenderParallax:

			ParallaxBufferStart = tmp1
			ParallaxExtent = tmp3
			; Loop through the vram writes and find any $00 tiles and replace them with parallax
			; Calculate the end of the parallax column offset
			ldy parallax_scroll_column
			lda ParallaxBufferOffset, y
			sta ParallaxBufferStart
			clc
			adc #9
			sta ParallaxExtent

			lda ParallaxBufferStart
			clc
			adc parallax_scroll_column_start
			tay

			ldx #TileOff0 + TileSizeHi - 1 - (2+1)
			stx LoopCount
			ldx #TileOff0
			jsr RenderParallaxLoop

			ldx #TileSizeLo - 1 - (2+1)
			stx LoopCount
			ldx #TileOff1
			jsr RenderParallaxLoop
			
			; move to the next scroll column for next frame
			jsr _increase_parallax_scroll_column

			; Demarkate end of write
			LDX VRAM_INDEX
			LDA #$FF
			STA VRAM_BUF+TileEnd,X

			; Declare this section as taken
			.if USE_ILLEGAL_OPCODES
				; A is already #$FF
				AXS #<-TileEnd
				STX VRAM_INDEX
			.else
				TXA
				CLC
				ADC #TileEnd
				STA	VRAM_INDEX
			.endif

			INC scroll_count

			LDA #1
			LDX #0
			RTS

	attributes:
		NametableAddrHi = tmp1
		; Attribute write architecture:

		; | Ad|dr |dat|
		;   0   1   2
		; Addr = VRAM address

		; 1 byte can theoretically be saved by using a vertical
		; sequence of 2 bytes, but this comes at a cost of 23
		; cycles per 2 bytes in vblank (80 vs 103), and vlank
		; time is not to be wasted

		; Decremented rld_column, very useful
		LDX _rld_column
		DEX
		.if USE_ILLEGAL_OPCODES
			LDA #$0F
			SAX ptr3
		.else
			TXA
			AND #$0F
			STA ptr3
		.endif

		; Get the ptr (I am not bothering with 2 separate loops)
		LDA #>collMap0
		STA ptr1+1
		LDA ptr3
		AND #$0E
		; ADC #<(collMap0-1) ; the low byte is 0
		STA ptr1

		LDA #8 - 1
		LDX #0
		STX ptr2+1
		JSR attributeSetup

		INC ptr1+1

		; Update new maximum
		LDA #8 - 1
		JSR attributeSetup

		; Get address hi byte (either left or right side)
		lda _scroll_x + 1 ; high byte
		and #%00000001
		eor #%00000001
		asl
		asl
		ora #$23
		sta NametableAddrHi
		
		LDA ptr3
		LSR
		ORA #$C0
		
		; Store address
		LDX VRAM_INDEX
		CLC
		addressLoop:
			; Low byte
			STA VRAM_BUF+AttrOff0+1,X
			STA VRAM_BUF+AttrOff1+1,X
			TAY
			; High byte
			lda NametableAddrHi
			STA VRAM_BUF+AttrOff0,X
			ORA #$08
			STA VRAM_BUF+AttrOff1,X
			TYA

			INX 
			INX
			INX

			; C is cleared by BCC
			ADC #$08
			BCC addressLoop
		
		LDY #16

		LDA VRAM_INDEX
		ADC #AttrEnd-1  ; Carry is set by the ADC : BCC
		STA VRAM_INDEX  ; State that the block is now occupied
		TAX

		dataLoop:
			LDA columnBuffer-1,Y
			STA VRAM_BUF-3+2,X

			.if USE_ILLEGAL_OPCODES
				TXA
				AXS #3
			.else
				DEX
				DEX
				DEX
			.endif
			DEY
			BNE dataLoop
		
		; Finish off the routine
		; X has the original VRAM_INDEX, mark this block as taken
		LDA #$FF
		STA VRAM_BUF+AttrEnd,X
		; Reset frame counter
		LDX #$00
		STX scroll_count

		LDA #$01
		RTS

	attributeSetup:
		STA LoopCount

		attributeLoop1:
			; Read lower right metatile
			LDY #$11
			.if USE_ILLEGAL_OPCODES
				lax (ptr1),y
			.else
				LDA	(ptr1),Y
				tax
			.endif
			; Read lower left metatile
			dey
			LDA (ptr1), Y
			tay
			; Get their attributes
			lda metatiles_attr,x	; Lower right
			ASL
			ASL
			ora metatiles_attr,y	; Lower left
			STA ptr2

			; Read upper right metatile
			LDY #$01
			.if USE_ILLEGAL_OPCODES
				lax (ptr1),y
			.else
				LDA	(ptr1),Y
				tax
			.endif
			; Read upper left metatile
			dey
			LDA (ptr1), Y
			tay
			; Get their attributes
			lda metatiles_attr,x	; Upper right
			ASL
			ASL
			ora metatiles_attr,y	; Upper left

			; Combine
			LDY ptr2	; Y has the lower metatile attrs, will shift by 4
			ORA shiftBy4table,Y
			LDX ptr2+1
			STA columnBuffer,X

			; Increment pointer
			LDA ptr1
			; Last thing affecting carry is the ASL, which
			; always shifts 0 into it if the metatile data
			; is valid
			ADC #$20
			STA ptr1
			; BCC :+
			; 	INC ptr1+1
			; :

			INC ptr2+1
			DEC LoopCount
			BPL attributeLoop1
		RTS

	right_tilewriteloop:
			ldy CurrentRow
			lda _invisblocks
			beq @norm
			lda #0
			beq @done
			@norm:
			LDA columnBuffer,Y
			@done:
			tay
			; y is the metatile id
			lda metatiles_top_right, y
			STA VRAM_BUF+TileOff0+3,X
			lda metatiles_bot_right, y
			STA VRAM_BUF+TileOff0+4,X
			
			INX
			INX
			inc CurrentRow
			DEC LoopCount
			BPL right_tilewriteloop
		rts
	left_tilewriteloop:
			ldy CurrentRow
			lda _invisblocks
			beq @norm2
			lda #0
			beq @done2
			@norm2:
			LDA columnBuffer,Y
			@done2:
			tay
			; y is the metatile id
			lda metatiles_top_left, y
			STA VRAM_BUF+TileOff0+3,X
			lda metatiles_bot_left, y
			STA VRAM_BUF+TileOff0+4,X
			
			INX
			INX
			inc CurrentRow
			DEC LoopCount
			BPL left_tilewriteloop
		rts
		
	RenderParallaxLoop:
		lda _no_parallax
		bne @nopar
			lda VRAM_BUF+TileOff0+3,x
			bne :+
				; empty tile, so replace it with the parallax for this
				lda ParallaxBuffer, y
				sta VRAM_BUF+TileOff0+3,x
			:
			iny
			cpy ParallaxExtent
			bne :+
				ldy ParallaxBufferStart
			:
			inx
			dec LoopCount
			bpl RenderParallaxLoop
	@nopar:
			rts

; Column striped parallax data definition
; add to the tile for the next row, up to 6.
ParallaxBuffer:
	ParallaxBufferOffset:
		.byte ParallaxBufferCol0 - ParallaxBuffer
		.byte ParallaxBufferCol1 - ParallaxBuffer
		.byte ParallaxBufferCol2 - ParallaxBuffer
		.byte ParallaxBufferCol3 - ParallaxBuffer
		.byte ParallaxBufferCol4 - ParallaxBuffer
		.byte ParallaxBufferCol5 - ParallaxBuffer
	ParallaxBufferCol0:
		.byte $80, $90, $a0, $b0, $86, $96, $a6, $b6, $8c
	ParallaxBufferCol1:
		.byte $81, $91, $a1, $b1, $87, $97, $a7, $b7, $8d
	ParallaxBufferCol2:
		.byte $82, $92, $a2, $b2, $88, $98, $a8, $b8, $8e
	ParallaxBufferCol3:
		.byte $83, $93, $a3, $b3, $89, $99, $a9, $b9, $9c
	ParallaxBufferCol4:
		.byte $84, $94, $a4, $b4, $8a, $9a, $aa, $ba, $9d
	ParallaxBufferCol5:
		.byte $85, $95, $a5, $b5, $8b, $9b, $ab, $bb, $9e

.endproc

; void __fastcall__ load_ground(uint8_t id);
.segment "LVL_BANK_00"

.import _ground

.export _load_ground
.proc _load_ground
	;A = ground num
	ASL						;
	TAX						;
	LDA	#$00				;
	TAY						;	ptr1 = ground[id]
	JSR	mmc3_set_prg_bank_1	;	mmc3_set_prg_bank_1(0)
	LDA _ground, X			;	Y = 0
	STA ptr1				;
	LDA _ground+1, X		;
	STA ptr1+1				;__
	LDX #<-48				;__	X = idx @ collmap data, count up to 0

	ground_ptr = ground-($100-48)

	; there's a max of 48 bytes of data to fill, 
	; the rle worst case is 96 bytes long,
	; therefore not needing to check for an overflow

	loop:
		LDA (ptr1),y		;
		bmi single_rle_byte	;	Run
		STA tmp1			;
		iny					;__

		LDA (ptr1),y		;	Value
		iny					;__

		STY tmp2
		LDY tmp1
	mult_loop:
		STA ground_ptr, X
		INX
		BEQ fin
		DEY
		BPL mult_loop
		LDY tmp2
		BNE loop	; Physically cannot be not 0

	single_rle_byte:
		AND #$7F
		STA ground_ptr, X
		INY
		INX
		BNE loop

	fin:
		RTS

.endproc

; void __fastcall__ draw_padded_text(const void * data, uint8_t len, uint8_t total_len, uintptr_t ppu_address)
.segment "CODE_2"

.export __draw_padded_text
.proc __draw_padded_text
	; XA = ppu_address
	; sreg[0] = total_len
	; sreg[1] = len
	; xargs[0:1] = data

	spaceChr = $FE
	data = xargs+0
	total_len = sreg+0
	len = sreg+1

	LDY VRAM_INDEX
	STA VRAM_BUF, Y	;
	TXA					;	vram pointer
	STA VRAM_BUF+1, Y	;__
	LDA total_len		;	total length
	STA VRAM_BUF+2, Y	;__

	SEC					;	Total padding
	SBC len				;__
	LSR					;	Get left offset
	STA tmp1			;__
	ADC #$00			;	Get right offset
	TAY					;__

	LDA total_len
	ADC	VRAM_INDEX		;	Carry is guaranteed to be clear by LSR : ADC #$00
	; If carry is still set, we have big problems
	; BCS some shit to do
	TAX
	ADC #$03
	STA VRAM_INDEX

	LDA #$FF			;	Finish off the write
	STA VRAM_BUF+3, X	;__

	CPY #$00	; Had to do this, very sorry
	BEQ main_data

	LDA #spaceChr

	pad_loop_right:
		STA VRAM_BUF+2, X
		DEX
		DEY
		BNE pad_loop_right
		
	main_data:
		LDY len
		DEY

	main_data_loop:
		LDA (<data), Y
		STA VRAM_BUF+2, X
		DEX
		DEY
		BPL main_data_loop

	LDY tmp1	;	Pad left amount
	BEQ fin		;__

	LDA #spaceChr

	pad_loop_left:
		STA VRAM_BUF+2, X
		DEX
		DEY
		BNE pad_loop_left

	fin:
		RTS

.endproc


; void movement();
.segment "XCD_BANK_01"

.import _cube_movement, _ship_movement, _ball_movement, _ufo_movement, _robot_movement, _spider_movement, _wave_movement
.import _retro_mode

.export _movement
.proc _movement
	LDX _gamemode
	CPX #<gamemode_count
	BCS end
	lda _retro_mode
	beq @no1
	lda _gamemode
	cmp #1
	bne	@no1
		; LDA #<_ufo_movement
		; STA <PTR
		; LDA #>_ufo_movement
		; STA <PTR+1
		; JMP (PTR)	
		JMP _ufo_movement
	
	@no1:
		LDA jump_table_hi, X
		PHA
		LDA jump_table_lo, X
		PHA

	end:
		RTS     ; break or use the RTS trick

	jump_table_lo:
		.byte <(_cube_movement-1), <(_ship_movement-1), <(_ball_movement-1), <(_ufo_movement-1), <(_cube_movement-1), <(_spider_movement-1), <(_wave_movement-1), <(_ball_movement-1), <(_cube_movement-1)
	jump_table_hi:
		.byte >(_cube_movement-1), >(_ship_movement-1), >(_ball_movement-1), >(_ufo_movement-1), >(_cube_movement-1), >(_spider_movement-1), >(_wave_movement-1), >(_ball_movement-1), >(_cube_movement-1)

.endproc

; void __fastcall__ music_play(uint8_t song);
.segment "CODE_2"

.import _options, FIRST_MUSIC_BANK

.export _music_play
.proc _music_play  

	; CONFIGURATION:
	; If the following value is set and valid, it will be used
	; as the pointer to famistudio_init in all banks. If it
	; isn't, then music_pointers_lo, hi and song count tables
	; are needed for proper operation.
	constInitPtr = $A000

	.ifndef constInitPtr
		constInitPtr = 0
	.endif
	useConstInitPtr = (constInitPtr >= $6000)

    bit _options ; sets N flag to bit 7 of _options without affecting A  
    bpl musicon
    rts  
musicon:  
    LDY #<FIRST_MUSIC_BANK
    tsx
bank_loop:
    PHA
    SEC
    SBC music_counts-FIRST_MUSIC_BANK, Y
    BCC found_bank
    INY
    TXS ;Act as if no PHA happened
    BCS bank_loop  ; BRA
found_bank:
    TYA
    JSR mmc3_tmp_prg_bank_1
    CPY current_song_bank
    BEQ :+
    ;If different bank than before reinitalize FS
        STY	current_song_bank
		.if useConstInitPtr
			LDX #<constInitPtr
			LDY #>constInitPtr
		.else
			LDX music_data_locations_lo-FIRST_MUSIC_BANK, Y
			LDA	music_data_locations_hi-FIRST_MUSIC_BANK, Y
			TAY
		.endif
        LDA #$01
        JSR famistudio_init
    :
    PLA
    JSR famistudio_music_play
    
    JMP _mmc3_pop_prg_bank_1

; Tables currently generated manually

.if .not(useConstInitPtr)
music_data_locations_lo:
	.out "shit"
	.byte <music_data_famidash_music1, <music_data_famidash_music2, <music_data_famidash_music3, <music_data_famidash_music4, <music_data_famidash_music5
music_data_locations_hi:
	.byte >music_data_famidash_music1, >music_data_famidash_music2, >music_data_famidash_music3, >music_data_famidash_music4, >music_data_famidash_music5
.endif
music_counts:
	.byte 2, 2, 3, 5, $FF  ;last bank is marked with an FF to always stop bank picking
.endproc

.segment "CODE_2"

.proc famistudio_dpcm_bank_callback
	clc
	adc #<FIRST_DMC_BANK
	jmp mmc3_set_prg_bank_0
.endproc


; void __fastcall__ sfx_play(uint8_t sfx_index, uint8_t channel);
.segment "CODE_2"

.import _options

.export __sfx_play
.proc __sfx_play  
    ; x = sfx
	; a = channel

    bit _options ; bit 6 is copied to the overflow flag  
    bvc play  
    rts  
play:    
    jmp famistudio_sfx_play  
.endproc

; void music_update();
.segment "CODE_2"

.export _music_update
.proc _music_update
    LDA current_song_bank
    JSR mmc3_tmp_prg_bank_1
    JSR famistudio_update
    JMP _mmc3_pop_prg_bank_1
.endproc
; Because i JMPed, the routine is over


; void load_next_sprite();
.segment "CODE_2"

.import _activesprites_x_lo, _activesprites_x_hi
.import _activesprites_y_lo, _activesprites_y_hi
.import _activesprites_type, _activesprites_activated
.import _activesprites_realx, _activesprites_realy

.export _load_next_sprite := load_next_sprite
.proc load_next_sprite
.import _spr_index
SpriteData = ptr1
SpriteOffset = ptr2

    lda mmc3PRG1Bank
    pha

    lda _sprite_data_bank
    jsr mmc3_set_prg_bank_1

    ; And also keep the "max sprite id" number in x
    ; This is premultiplied by two for the word sized x/y fields which come first
    ldx _spr_index

    ; Now read the data into the sprite
    
    ldy #0
    lda (_sprite_data),y
    cmp #$ff
    beq @Exit
    iny
    
    ; X - 2 bytes
    sta _activesprites_x_lo,x
	sta _activesprites_realx,x
    lda (_sprite_data),y
    iny
    sta _activesprites_x_hi,x

    ; Y - 2 bytes
    lda (_sprite_data),y
    iny
    sta _activesprites_y_lo,x
	sta _activesprites_realy,x
    lda (_sprite_data),y
    iny
    sta _activesprites_y_hi,x

    ; id - 1 byte
    lda (_sprite_data),y
    ;   no iny, as we ain't using y anymore
    sta _activesprites_type,x
    
    lda #0
    sta _activesprites_activated,x

    ; Increment to the next sprite index - 
    ; Add the 5 back to the pointer
    LDA #$05
    CLC
    ADC _sprite_data
    STA _sprite_data
    BCC :+
        INC _sprite_data+1
    :

    ; Increment the _spr_index and and it with #$0F
    INX
	.if USE_ILLEGAL_OPCODES
		LDA #$0F
		SAX _spr_index
	.else
		TXA
		AND #$0F
		STA _spr_index
	.endif

@Exit:
    pla
    jmp mmc3_set_prg_bank_1
.endproc


; void check_spr_objects();
.segment "CODE_2"

.import _activesprites_active, _scroll_x, _scroll_y

.export _check_spr_objects := check_spr_objects
.proc check_spr_objects
    ; for each sprite we want to check to see if its active
    ; if it is, update its realx/y position
    ; if its not, attempt to load another sprite
    ldx #16 - 1

check_sprite_loop:
        ; X is the current sprite object
        ; Load two byte X coord to see if we went offscreen
        lda _activesprites_x_lo, x
        sec
        sbc _scroll_x
        lda _activesprites_x_hi, x
        sbc _scroll_x+1
        bpl sprite_alive
            txa
            pha
                jsr load_next_sprite
            pla
            tax
            lda #0
            jmp write_active
    sprite_alive:
        ; Sprite is still alive, so check to see if its on screen
        bne sprite_offscreen
        ; sprite is alive AND onscreen x, so now check the Y position
        lda _activesprites_y_lo, x
        clc ; NOTICE: intentionally subtract 1 extra to position them on the screen better
        sbc _scroll_y
        sta _activesprites_realy, x
        lda _activesprites_y_hi, x
        sbc _scroll_y+1
        bne sprite_offscreen

        ; totally onscreen so finish updating its scroll position
        lda _activesprites_x_lo, x
        sec
        sbc _scroll_x
        sta _activesprites_realx, x

        lda #1
        bne write_active ; unconditional
sprite_offscreen:
        lda #0
write_active:
        sta _activesprites_active, x
        dex
        bpl check_sprite_loop
    rts
.endproc

.segment "XCD_BANK_04"

.define CUBE_GRAVITY $6B
.define MINI_CUBE_GRAVITY $6F

.import _player_x, _player_y, _player_gravity, _player_vel_x, _player_vel_y
.import _ballframe, _robotframe, _robotjumpframe, _spiderframe, _retro_mode, _icon
.importzp _cube_rotate, _mini
.import _CUBE, _SHIP, _BALL, _ROBOT, _ROBOT_ALT, _UFO, _SPIDER, _WAVE, _SWING
.import _MINI_CUBE, _MINI_SHIP, _MINI_BALL, _MINI_ROBOT, _MINI_ROBOT_ALT, _MINI_UFO, _MINI_SPIDER, _MINI_WAVE, _MINI_SWING
.importzp _cube_data, _slope_frames, _slope_type
drawcube_rounding_table:
	.byte 0, <-1, <-2, 3, 2, 1
	.byte 0, <-1, <-2, 3, 2, 1	; doubling it simplifies the routine
	.byte <-24

drawcube_sprite_table:
	; Bits 6-7: FLIP
	; Bits 0-2: actual idx
	.define NOFLIP $00
	.define H_FLIP $40
	.define V_FLIP $80
	.define HVFLIP $C0
	.byte NOFLIP|0, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, V_FLIP|5, V_FLIP|4, V_FLIP|3, V_FLIP|2, V_FLIP|1
	.byte HVFLIP|0, HVFLIP|1, HVFLIP|2, HVFLIP|3, HVFLIP|4, HVFLIP|5
	.byte HVFLIP|6, H_FLIP|5, H_FLIP|4, H_FLIP|3, H_FLIP|2, H_FLIP|1
	.undef NOFLIP
	.undef H_FLIP
	.undef V_FLIP
	.undef HVFLIP

drawcube_sprite_way:
	; Bits 6-7: FLIP
	; Bits 0-2: actual idx
	.define NOFLIP $00
	.define H_FLIP $40
	.define V_FLIP $80
	.define HVFLIP $C0
	.byte NOFLIP|0, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, H_FLIP|5, H_FLIP|4, H_FLIP|3, H_FLIP|2, H_FLIP|1
	.byte H_FLIP|0, HVFLIP|1, HVFLIP|2, HVFLIP|3, HVFLIP|4, HVFLIP|5
	.byte V_FLIP|6, V_FLIP|5, V_FLIP|4, V_FLIP|3, V_FLIP|2, V_FLIP|1
	.undef NOFLIP
	.undef H_FLIP
	.undef V_FLIP
	.undef HVFLIP

drawcube_sprite_none:
	; Bits 6-7: FLIP
	; Bits 0-2: actual idx
	.define NOFLIP $00
	.define H_FLIP $40
	.define V_FLIP $80
	.define HVFLIP $C0
	.byte NOFLIP|0, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.byte NOFLIP|6, NOFLIP|1, NOFLIP|2, NOFLIP|3, NOFLIP|4, NOFLIP|5
	.undef NOFLIP
	.undef H_FLIP
	.undef V_FLIP
	.undef HVFLIP


drawplayer_center_offsets:
	;		Cub	Shp	Bal	UFO	RBT	SPI	Wav
	.byte	8,	8,	8,	8,	12,	12,	8,	8,	8,	8; normal size
	.byte	4,	12,	4,	12,	12,	12,	12,	12,	12,	12; mini 

; void drawplayerone();
.segment "XCD_BANK_04"

.export _drawplayerone
.proc _drawplayerone

    LDX _cube_data
    LDA _slope_frames
    ORA _slope_type
    BEQ :+
        TXA
        ORA #%10000000
        BNE @skipClearBit
    :
        TXA
        AND #%01111111
    @skipClearBit:
    sta _cube_data

	LDA _player_gravity+0
	BEQ :+
		LDA #$80
	: STA xargs+0

	LDX _player_y+1		;
	DEX					;	The Y of oam_meta_spr is high_byte(player_y[0])-1
	STX sreg+1			;__

	; Set up base pointer for jump tables
	LDA _mini       ;
	BEQ :+          ;   Add 8 if mini mode 
		LDA #gamemode_count
	:               ;__
	CLC             ;   Actual gamemode itself
	ADC _gamemode   ;__
	PHA
	LDX _retro_mode
	BEQ :+
		ADC #gamemode_count*2	; ain't no way the last one overflowed
	:
	TAX
	LDA sprite_table_table_lo, X
	STA ptr1		;__	Get low byte of table ptr
	LDA sprite_table_table_hi, X
	STA ptr1+1		;__ Get high byte of table ptr
	PLA				;	Get pure gamemode number
	TAX				;__

	LDY _player_x+1     ;__ temp_x = high_byte(player_x[0]);
	; The condition if is temp_x == 0 or is > 0xfc,
	; this can be expressed as (temp_x - 1) > 0xfb
	DEY					;
	CPY #$FC            ;
	BCC :+              ;	if(temp_x-1 > 0xfb) temp_x = 1;
		LDY #$00        ;
	:                   ;__
	TYA
	SEC		; I decremented the Y, this is getting back at it
	ADC drawplayer_center_offsets, X
	STA sreg+0			;__ The X of oam_meta_spr is temp_x

	; The switch 
	LDX _gamemode
	DEX			;	case 0x01: ship shit
	jeq ship	;__
	DEX			;	case 0x02: ball shit
	jeq ball	;__
	DEX			;	case 0x03: ufo shit
	jeq ufo		;__
	DEX			;	case 0x04: robot shit
	jeq robot	;__
	DEX			;	case 0x05: spider shit
	jeq spider	;__
	dex			;	case 0x06: wave shit
	jeq	wave	;__	
	dex			;	case 0x07: swing shit
	jeq	ship	;__
	dex			;	case 0x08: NINJA
	jeq	cube	;__
	
	; default: cube
    cube:
		; C code:
			; 		if (player_vel_y[0] == 0) cube_rotate[0] = round to the nearest 90°;
			; 		else cube_rotate[0] += player_gravity[0] ? -CUBE_GRAVITY : CUBE_GRAVITY;
			; 		cap the mf at 0..23
		@rounding_table = drawcube_rounding_table

        BIT _cube_data
        BMI @round
		LDA _player_vel_y+1		;	if player_vel_y == 0
		ORA _player_vel_y+0		;
		BNE @no_round		    ;__
        @round:	    
			STA	_cube_rotate+0	;__ low_byte = 0
			.if USE_ILLEGAL_OPCODES
				LAX _cube_rotate+1	;	LAX abs is apparently stable
			.else
				LDA _cube_rotate+1
				TAX
			.endif
			SEC					;
			SBC #12				;
			BCC :+				;	Limit table idx to 0..12
				TAX				;	
				CLC				;
			:					;__
			LDA _cube_rotate+1	;	Round the cube rotation
			ADC @rounding_table, X
            STA _cube_rotate+1
			BIT _cube_data
            BPL :+
                LDY _slope_type
                CLC
                ADC rounding_slope_table-1, y
            : 
            TAX
            JMP @fin_nold

		@no_round:
		LDA _cube_rotate
		CLC

		LDX _player_gravity+0
		BNE @subtract

			ADC #<CUBE_GRAVITY      ;
			STA _cube_rotate        ;
			BCC @fin				;   cube_rotate[0] += CUBE_GRAVITY;
				LDX _cube_rotate+1	;
				INX					;__
				CPX #24				;
				BCC :+				;	Cap at 24
					LDX #00			;
				: STX _cube_rotate+1;__
				JMP @fin_nold

		@subtract:
			SBC #<CUBE_GRAVITY-1	; 	
			STA _cube_rotate		;
			BCS @fin				;	cube_rotate[0] -= CUBE_GRAVITY;
				DEC _cube_rotate+1	;
				BPL @fin			;__
				LDA #23				;	Cap at 0
				STA _cube_rotate+1	;__

		@fin:
			LDX _cube_rotate+1
        @fin_nold:
			LDA _gamemode
			cmp #8
			beq @noflip

			LDA _icon
			cmp #$13
			beq @noflip
			cmp #2
			bne	@norm
			LDA drawcube_sprite_way, X
			jmp @don
		@norm:
			LDA drawcube_sprite_table, X
			jmp @don
		@noflip:
			LDA drawcube_sprite_none, X
			;jmp @don
			
		@don:
			TAX
			AND #$C0
			STA xargs+0	; flip setting
			TXA
			AND #$07
			TAY
			JMP fin

	ship:
		; C code:
			; 		cube_rotate[0] = 0x0400 - player_vel_y[0];
			; 		if (high_byte(cube_rotate) >= 0x08) {
			; 			cube_rotate[0]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			; 		}
		TXA						;(X = 0 as per JEQ)
		TAY						;
		sec						;
		sbc _player_vel_y		;	cube_rotate[0] = 0x0400 - player_vel_y[0];
		sta _cube_rotate		;	(Mostly generated by cc65 lmao)
		lda #$04				;
		sbc _player_vel_y+1		;
		; A has high byte of _cube_rotate
		CMP	#$08				;	if (high_byte(cube_rotate) >= 0x08) {
		BCC :++					;__
			CMP #$80			;	if (high_byte(cube_rotate) < 0x80)
			BCC	:+				;__
				LDY #$07		;	cube_rotate[0] = 0x07FF
				DEX				;__
			:					;__	else 0x0000 (Y and X still remain at 0)
			STX _cube_rotate	;__	Store low byte
			TYA					;
		:						;	Store high byte
		STA	_cube_rotate+1		;__
		
		; Frame index is high byte of _cube_rotate if gravity is 0, 
		;* and 7-high byte if gravity isn't 0
		LDX _player_gravity+0
		BEQ :+
			; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
			EOR #$FF
			CLC
			ADC #$08
		:
		TAY
		JMP fin

	ball:
		; C code:
			; if (!mini) {
			;	[calls to oam] 
			; 			ballframe++;
			; 			if (ballframe > 7) { ballframe = 0; }
			;	}
		LDA _options
		and #$04  ;platformer
		beq	@ball2
		lda _player_vel_x
		bne @ball2
		lda #0
		ldy #0
		beq @donball
	@ball2:
		LDA _ballframe	;	Load index
		TAY				;__
		CLC				;	ballframe++;
		ADC #$01		;__
		AND #$07		;__	if (ballframe > 7) { ballframe = 0; }
		STA _ballframe	;__
	@donball:
		JMP fin

	ufo:
		; Real C code:
			; 		if (!player_gravity[0]) {
			; 			if (player_vel_y[0] == 0) kandotemp3[0] = 0;
			; 			else if (player_vel_y[0] > 0) kandotemp3[0] = 1;
			; 			else if (player_vel_y[0] < 0) kandotemp3[0] = 2;
			; 		}
			; 		else {
			; 			if (player_vel_y[0] == 0) kandotemp3[0] = 0;
			; 			else if (player_vel_y[0] > 0) kandotemp3[0] = 1;
			; 			else if (player_vel_y[0] < 0) kandotemp3[0] = 2;
			; 		}
			;	kandotemp3[0] used as index
		; Modified pseudo C code:
			;	kandotemp3[0] = 1;
			;	if (0 < highbyte < $80) {}	// do nothing with it
			;	else if ($80 ≤ highbyte ≤ $FF) {
			;		kandotemp3[0] = 2;
			;	} else if (highbyte == $00) {
			;		if (lowbyte == 0) kandotemp3[0] = 0;
			; 	}
		LDY #$1				;__	kandotemp3[0] = 1;
		LDA _player_vel_y+1	;__
		BEQ :+				;__	else if (highbyte == $00) { // later }
		BPL @go	    		;__	if (0 < highbyte < $80) {}	// do nothing with it
			INY				;__	else if ($80 ≤ highbyte ≤ $FF) { kandotemp3[0] = 2; }
			JMP fin			;__
		:
		ORA _player_vel_y	;	if (player_vel_y == 0)
		BNE @go				;__
		DEY					;	kandotemp3[0] = 0;
	@go:
		JMP fin				;__
	robot:
		; C code:
			;	if (player_vel_y[0] == 0) {
			;		[index from ROBOT/MINI_ROBOT using robotframe[0]]
			; 		robotframe[0]++;
			; 		if (robotframe[0] > 19) { robotframe[0] = 0; }	
			;	} else {
			;		[index from ROBOT_JUMP/MINI_ROBOT_JUMP using robotjumpframe[0]]
			; 	}
			LDA _player_vel_y+1	;
			ORA _player_vel_y	;	if (player_vel_y[0] == 0) {
			BNE @jump			;__
			LDA _options
			and #$04
			beq	@cont1
			LDA _player_vel_x
			bne @cont1
			lda #0
			sta _robotframe
			ldy #0
			jmp @fini
			
		@cont1:
			LDA #0
			LDY _robotframe	;	[load robotframe[0] into Y]
			SEC				;	robotframe[0]++; (A is 0, so set the carry and bam)
			ADC _robotframe	;__
			CMP #20			;
			BCC @hur			;	if (robotframe[0] > 19) { robotframe[0] = 0; }	
				LDA #$00	;__
			@hur:				;
			STA _robotframe	;__
		@fini:
			JMP fin
		@jump:				;	} else {
			LDA #20			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
			CLC				;	ROBOT_JUMP[X] = ROBOT[X+20]
			ADC _robotjumpframe
			TAY				;__
			JMP fin
	spider:
		; C code:
			;	if (player_vel_y[0] == 0 ) {
			;		[index from SPIDER/MINI_SPIDER using spiderframe[0]]
			; 		spiderframe[0]++;
			; 		if (spiderframe[0] > 15) { spiderframe[0] = 0; }	
			;	} else {
			;		[use SPIDER_JUMP/MINI_SPIDER_JUMP[0]]
			; 	}
		LDA _player_vel_y+1	;
		ORA _player_vel_y	;	if (player_vel_y[0] == 0) {
		BNE @jump			;
			LDA _options
			and #$04
			beq	@cont1
			LDA _player_vel_x
			bne @cont1
			lda #0
			sta _spiderframe
			ldy #0
			jmp fin
			
		@cont1:
			LDA #0
			LDY _spiderframe	;	[load spiderframe[0] into Y]
			SEC				;	spiderframe[0]++; (A is 0, so set the carry and bam)
			ADC _spiderframe ;__
			AND #$0F        ;   if (spiderframe[0] > 15) spiderframe[0] = 0;
			STA _spiderframe;__
			JMP fin
		@jump:				;	} else { SPIDER_JUMP[0] = SPIDER[8]
			LDY #8			; ! This is the sizeof SPIDER / MINI_SPIDER, change it as needed
			JMP fin

	wave:
		; C code:
			; 		cube_rotate[0] = 0x0400 - player_vel_y[0];
			; 		if (high_byte(cube_rotate) >= 0x08) {
			; 			cube_rotate[0]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			; 		}
		TXA						;(X = 0 as per JEQ)
		TAY						;
		sec						;
		sbc _player_vel_y		;	cube_rotate[0] = 0x0400 - player_vel_y[0];
		sta _cube_rotate		;	(Mostly generated by cc65 lmao)
		lda #$04				;
		sbc _player_vel_y+1		;
		; A has high byte of _cube_rotate
		CMP	#$08				;	if (high_byte(cube_rotate) >= 0x08) {
		BCC :++					;__
			CMP #$80			;	if (high_byte(cube_rotate) < 0x80)
			BCC	:+				;__
				LDY #$07		;	cube_rotate[0] = 0x07FF
				DEX				;__
			:					;__	else 0x0000 (Y and X still remain at 0)
			STX _cube_rotate	;__	Store low byte
			TYA					;
		:						;	Store high byte
		STA	_cube_rotate+1		;__
		
        ; Fix for speed greater than x3 being mirrored
        LDY _player_vel_x+1
        CPY #$04
        BCC :+
            ; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
            LDY _mini
            BNE :+
			EOR #$FF
			CLC
			ADC #$08
        :

        ; Frame index is high byte of _cube_rotate if gravity is 0, 
		;* and 7-high byte if gravity isn't 0
		LDX _player_gravity+0
		BEQ :+
			; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
			EOR #$FF
			CLC
			ADC #$08
		:
		TAY
		JMP fin



	fin:
    common:
		TYA					;
		ASL					;	Double da index cuz it's a table of shorts
		TAY					;__

		; ; CENTERING DEBUGGING ONLY
		; lda <FRAME_CNT1
		; and #$01
		; beq :+
		; 	lda #$40
		; : eor xargs+0
		; sta xargs+0


		LDA (ptr1), Y		;	Load low byte
		PHA					;__
		INY					;
		LDA (ptr1), Y		;	Load high byte
		TAX					;__
		PLA
		JMP __oam_meta_spr_flipped ;__	oam_meta_spr(temp_x, high_byte(player_y[0])-1, [whatever the fuck we set here]);

    sprite_table_table_lo:
        .byte <_CUBE, <_SHIP, <_BALL, <_UFO, <_ROBOT, <_SPIDER, <_WAVE, <_SWING, <_CUBE
        .byte <_MINI_CUBE, <_MINI_SHIP, <_MINI_BALL, <_MINI_UFO, <_MINI_ROBOT, <_MINI_SPIDER, <_MINI_WAVE, <_MINI_SWING, <_MINI_CUBE
    sprite_table_table_lo2:
        .byte <_CUBE, <_SHIP, <_BALL, <_UFO, <_ROBOT_ALT, <_SPIDER, <_WAVE, <_SWING, <_CUBE
        .byte <_MINI_CUBE, <_MINI_SHIP, <_MINI_BALL, <_MINI_UFO, <_MINI_ROBOT, <_MINI_SPIDER, <_MINI_WAVE, <_MINI_SWING, <_MINI_CUBE
    sprite_table_table_hi:
        .byte >_CUBE, >_SHIP, >_BALL, >_UFO, >_ROBOT, >_SPIDER, >_WAVE, >_SWING, >_CUBE
        .byte >_MINI_CUBE, >_MINI_SHIP, >_MINI_BALL, >_MINI_UFO, >_MINI_ROBOT, >_MINI_SPIDER, >_MINI_WAVE, >_MINI_SWING, >_MINI_CUBE
    sprite_table_table_hi2:
        .byte >_CUBE, >_SHIP, >_BALL, >_UFO, >_ROBOT_ALT, >_SPIDER, >_WAVE, >_SWING, >_CUBE
        .byte >_MINI_CUBE, >_MINI_SHIP, >_MINI_BALL, >_MINI_UFO, >_MINI_ROBOT, >_MINI_SPIDER, >_MINI_WAVE, >_MINI_SWING, >_MINI_CUBE

    rounding_slope_table:
        .byte $03, $09, $09, $09, $0a, $00, $00, $00, $00, $09, $0a, $09
.endproc
drawplayer_common := _drawplayerone::common

; void drawplayertwo();
.segment "XCD_BANK_04"

.import _CUBE2, _SHIP2, _BALL2, _ROBOT2, _UFO2, _SPIDER2, _WAVE2, _SWING2
.import _MINI_CUBE2, _MINI_SHIP2, _MINI_BALL2, _MINI_ROBOT2, _MINI_UFO2, _MINI_SPIDER2, _MINI_WAVE2, _MINI_SWING2

.export _drawplayertwo
.proc _drawplayertwo

	LDA _player_gravity+1
	BEQ :+
		LDA #$80
	: STA xargs+0	; flip

	LDX _player_y+3		;
	DEX					;	The Y of oam_meta_spr is high_byte(player_y[1])-1
	STX sreg+1			;__

	; Set up base pointer for jump tables
	LDA _mini       ;
	BEQ :+          ;   Add 8 if mini mode 
		LDA #gamemode_count
	:               ;__
	CLC             ;   Actual gamemode itself
	ADC _gamemode   ;__
	PHA
	LDX _retro_mode
	BEQ :+
		ADC #gamemode_count*2	; ain't no way the last one overflowed
	:
	TAX
	LDA sprite_table_table_lo, X
	STA ptr1		;__	Get low byte of table ptr
	LDA sprite_table_table_hi, X
	STA ptr1+1		;__ Get high byte of table ptr
	PLA				;	Get pure gamemode number
	TAX				;__

	LDY _player_x+3     ;__ temp_x = high_byte(player_x[1]);
	; The condition if is temp_x == 0 or is > 0xfc,
	; this can be expressed as (temp_x - 1) > 0xfb
	DEY					;
	CPY #$FC            ;
	BCC :+              ;	if(temp_x-1 > 0xfb) temp_x = 1;
		LDY #$00        ;
	:                   ;__
	TYA
	SEC		; I decremented the Y, this is getting back at it
	ADC drawplayer_center_offsets, X
	STA sreg+0			;__ The X of oam_meta_spr is temp_x

	; The switch 
	LDX _gamemode
	DEX			;	case 0x01: ship shit
	jeq ship	;__
	DEX			;	case 0x02: ball shit
	jeq ball	;__
	DEX			;	case 0x03: ufo shit
	jeq ufo		;__
	DEX			;	case 0x04: robot shit
	jeq robot	;__
	DEX			;	case 0x05: spider shit
	jeq spider	;__
	dex			;	case 0x06: wave shit
	jeq	wave	;__	
	dex			;	case 0x07: swing shit
	jeq	ship	;__
	dex			;	case 0x08: NINJA
	jeq	cube	;__

    ; default: cube
    cube:
        ; C code:
			; 		if (player_vel_y[1] == 0) cube_rotate[1] = round to the nearest 90°;
			; 		else cube_rotate[1] += player_gravity[1] ? -CUBE_GRAVITY : CUBE_GRAVITY;
			; 		cap the mf at 0..23
		@rounding_table = drawcube_rounding_table

		LDA _player_vel_y+3		;	if player_vel_y == 0
		ORA _player_vel_y+2		;
		BNE @no_round			;__
			STA	_cube_rotate+2	;__ low_byte = 0
			.if USE_ILLEGAL_OPCODES
				LAX _cube_rotate+3	;	LAX abs is apparently stable
			.else
				LDA _cube_rotate+3	;
				TAX
			.endif
			SEC					;
			SBC #12				;
			BCC :+				;	Limit table idx to 0..12
				TAX				;	
				CLC				;
			:					;__
			LDA _cube_rotate+3	;	Round the cube rotation
			ADC @rounding_table, X
			STA _cube_rotate+3	;
			TAX					;__
			JMP @fin_nold

		@no_round:
		LDA _cube_rotate+2
		CLC

		LDX _player_gravity+1
		BNE @subtract

			ADC #<CUBE_GRAVITY      ;
			STA _cube_rotate+2		;
			BCC @fin				;   cube_rotate[0] += CUBE_GRAVITY;
				LDX _cube_rotate+3	;
				INX					;__
				CPX #24				;
				BCC :+				;	Cap at 24
					LDX #00			;
				: STX _cube_rotate+3;__
				JMP @fin_nold

		@subtract:
			SBC #<CUBE_GRAVITY-1	; 	
			STA _cube_rotate+2		;
			BCS @fin				;	cube_rotate[0] -= CUBE_GRAVITY;
				DEC _cube_rotate+3	;
				BPL @fin			;__
				LDA #23				;	Cap at 0
				STA _cube_rotate+3	;__

		@fin:
			LDX _cube_rotate+3
        @fin_nold:
			LDA _icon
			cmp #2
			bne	@norm
			LDA drawcube_sprite_way, X
			jmp @don
		@norm:
			LDA drawcube_sprite_table, X
		@don:
			TAX
			AND #$C0
			STA xargs+0
			TXA
			AND #$07
			TAY
			JMP drawplayer_common

	ship:
		; C code:
			; 		cube_rotate[1] = 0x0400 - player_vel_y[1];
			; 		if (high_byte(cube_rotate) >= 0x08) {
			; 			cube_rotate[1]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			; 		}
		TXA						;(X = 0 as per JEQ)
		TAY						;
		sec						;
		sbc _player_vel_y+2		;	cube_rotate[1] = 0x0400 - player_vel_y[1];
		sta _cube_rotate+2		;	(Mostly generated by cc65 lmao)
		lda #$04				;
		sbc _player_vel_y+3		;
		; A has high byte of _cube_rotate
		CMP	#$08				;	if (high_byte(cube_rotate) >= 0x08) {
		BCC :++					;__
			CMP #$80			;	if (high_byte(cube_rotate) < 0x80)
			BCC	:+				;__
				LDY #$07		;	cube_rotate[1] = 0x07FF
				DEX				;__
			:					;__	else 0x0000 (Y and X still remain at 0)
			STX _cube_rotate+2	;__	Store low byte
			TYA					;
		:						;	Store high byte
		STA	_cube_rotate+3		;__
		
		; Frame index is high byte of _cube_rotate if gravity is 0, 
		;* and 7-high byte if gravity isn't 0
		LDX _player_gravity+1
		BEQ :+
			; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
			EOR #$FF
			CLC
			ADC #$08
		:
		TAY
		JMP drawplayer_common
	ball:
		; C code:
			; if (!mini) {
			;	[calls to oam] 
			; 			ballframe++;
			; 			if (ballframe > 7) { ballframe = 0; }
			;	}
		; LDA _ballframe	;	Load index
		; TAY				;__
		; CLC				;	ballframe++;
		; ADC #$01			;__
		; AND #$07			;__	if (ballframe > 7) { ballframe = 0; }
		; STA _ballframe	;__
		lda _options
		and #$04
		beq	@continue
		lda _player_vel_x
		bne @continue
		lda #0
		ldy #0
		jmp drawplayer_common
	@continue:
		LDY _ballframe
		JMP drawplayer_common
	ufo:
		; Real C code:
			; 		if (!player_gravity[1]) {
			; 			if (player_vel_y[1] == 0) kandotemp3[1] = 0;
			; 			else if (player_vel_y[1] > 0) kandotemp3[1] = 1;
			; 			else if (player_vel_y[1] < 0) kandotemp3[1] = 2;
			; 		}
			; 		else {
			; 			if (player_vel_y[1] == 0) kandotemp3[1] = 0;
			; 			else if (player_vel_y[1] > 0) kandotemp3[1] = 1;
			; 			else if (player_vel_y[1] < 0) kandotemp3[1] = 2;
			; 		}
			;	kandotemp3[1] used as index
		; Modified pseudo C code:
			;	kandotemp3[1] = 1;
			;	if (0 < highbyte < $80) {}	// do nothing with it
			;	else if ($80 ≤ highbyte ≤ $FF) {
			;		kandotemp3[1] = 2;
			;	} else if (highbyte == $00) {
			;		if (lowbyte == 0) kandotemp3[1] = 0;
			; 	}

		LDY #$1				;__	kandotemp3[1] = 1;
		LDA _player_vel_y+3	;__
		BEQ :+				;__	else if (highbyte == $00) { // later }
		BPL @fin		    ;__	if (0 < highbyte < $80) {}	// do nothing with it
			INY				;__	else if ($80 ≤ highbyte ≤ $FF) { kandotemp3[1] = 2; }
			JMP drawplayer_common	    ;__
		:
		ORA _player_vel_y+2	;	if (lowbyte == 0) kandotemp3[1] = 0;
		BNE @fin			;
			DEY				;	kandotemp3[1] = 0;
		@fin:
			JMP drawplayer_common    	;__
	robot:
		; C code:
			;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
			;		[index from ROBOT/MINI_ROBOT using robotframe[1]]
			; 		robotframe[1]++;
			; 		if (robotframe[1] > 19) { robotframe[1] = 0; }	
			;	} else {
			;		[index from ROBOT_JUMP/MINI_ROBOT_JUMP using robotjumpframe[1]]
			; 	}
		LDA _player_vel_y+3	;
		ORA _player_vel_y+2	;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
			LDA _options
			and #$04
			beq	@cont1
			LDA _player_vel_x+2
			bne @cont1
			lda #0
			sta _robotframe
			ldy #0
			jmp @fini
			
		@cont1:
			LDA #0
			LDY _robotframe	;	[load robotframe[0] into Y]
			SEC				;	robotframe[0]++; (A is 0, so set the carry and bam)
			ADC _robotframe	;__
			CMP #20			;
			BCC @hur			;	if (robotframe[0] > 19) { robotframe[0] = 0; }	
				LDA #$00	;__
			@hur:				;
			STA _robotframe	;__
		@fini:
			JMP drawplayer_common
		@jump:				;	} else {
			LDA #20			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
			CLC				;	ROBOT_JUMP[X] = ROBOT[X+20]
			ADC _robotjumpframe+1
			TAY				;__
			JMP drawplayer_common
	spider:
		; C code:
			;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
			;		[index from SPIDER/MINI_SPIDER using spiderframe[1]]
			; 		spiderframe[1]++;
			; 		if (spiderframe[1] > 15) { spiderframe[1] = 0; }	
			;	} else {
			;		[use SPIDER_JUMP/MINI_SPIDER_JUMP[0]]
			; 	}
		LDA _player_vel_y+3	;
		ORA _player_vel_y+2	;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
		BNE @jump	    	;__
			LDA _options
			and #$04
			beq	@cont1
			LDA _player_vel_x
			bne @cont1
			lda #0
			sta _spiderframe
			ldy #0
			jmp drawplayer_common
			
		@cont1:
			LDA #0
			LDY _spiderframe+1;	[load spiderframe[1] into Y] 
			SEC				;	spiderframe[1]++; (A is 0, so set the carry and bam)
			ADC _spiderframe+1;__
			AND #$0F        ;   if (spiderframe[1] > 15) spiderframe[1] = 0;
			STA _spiderframe+1;__
			JMP drawplayer_common
		@jump:				;	} else { SPIDER_JUMP[0] = SPIDER[8]
			LDY #8			; ! This is the sizeof SPIDER / MINI_SPIDER, change it as needed
			JMP drawplayer_common
	wave:
		; C code:
			; 		cube_rotate[1] = 0x0400 - player_vel_y[1];
			; 		if (high_byte(cube_rotate) >= 0x08) {
			; 			cube_rotate[1]= high_byte(cube_rotate) >= 0x80 ? 0x0000 : 0x07FF;
			; 		}
		TXA						;(X = 0 as per JEQ)
		TAY						;
		sec						;
		sbc _player_vel_y+2		;	cube_rotate[1] = 0x0400 - player_vel_y[1];
		sta _cube_rotate+2		;	(Mostly generated by cc65 lmao)
		lda #$04				;
		sbc _player_vel_y+3		;
		; A has high byte of _cube_rotate
		CMP	#$08				;	if (high_byte(cube_rotate) >= 0x08) {
		BCC :++					;__
			CMP #$80			;	if (high_byte(cube_rotate) < 0x80)
			BCC	:+				;__
				LDY #$07		;	cube_rotate[1] = 0x07FF
				DEX				;__
			:					;__	else 0x0000 (Y and X still remain at 0)
			STX _cube_rotate+2	;__	Store low byte
			TYA					;
		:						;	Store high byte
		STA	_cube_rotate+3		;__
		
        ; Fix for speed greater than x3 being mirrored
        LDY _player_vel_x+1
        CPY #$04
        BCC :+
            ; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
            LDY _mini
            BNE :+
			EOR #$FF
			CLC
			ADC #$08
        :
		; Frame index is high byte of _cube_rotate if gravity is 0, 
		;* and 7-high byte if gravity isn't 0
		LDX _player_gravity+1
		BEQ :+
			; 7 - A = -A + 7
			; -A = (A ^ 0xFF) + 1
			; 7 - A = (A ^ 0xFF) + 8
			EOR #$FF
			CLC
			ADC #$08
		:
		TAY
		JMP drawplayer_common
	sprite_table_table_lo:
		.byte <_CUBE2, <_SHIP2, <_BALL2, <_UFO2, <_ROBOT2, <_SPIDER2, <_WAVE2, <_SWING2, <_CUBE2
		.byte <_MINI_CUBE2, <_MINI_SHIP2, <_MINI_BALL2, <_MINI_UFO2, <_MINI_ROBOT2, <_MINI_SPIDER2, <_MINI_WAVE2, <_MINI_SWING2, <_MINI_CUBE2
    sprite_table_table_lo2:
        .byte <_CUBE2, <_SHIP2, <_BALL2, <_UFO2, <_ROBOT_ALT, <_SPIDER,2 <_WAVE2, <_SWING2, <_CUBE2
        .byte <_MINI_CUBE2, <_MINI_SHIP2, <_MINI_BALL2, <_MINI_UFO2, <_MINI_ROBOT2, <_MINI_SPIDER2, <_MINI_WAVE2, <_MINI_SWING2, <_MINI_CUBE2
	sprite_table_table_hi:
		.byte >_CUBE2, >_SHIP2, >_BALL2, >_UFO2, >_ROBOT2, >_SPIDER2, >_WAVE2, >_SWING2, <_CUBE2
		.byte >_MINI_CUBE2, >_MINI_SHIP2, >_MINI_BALL2, >_MINI_UFO2, >_MINI_ROBOT2, >_MINI_SPIDER2, >_MINI_WAVE2, >_MINI_SWING2, <_MINI_CUBE2
    sprite_table_table_hi2:
        .byte >_CUBE2, >_SHIP2, >_BALL2, >_UFO2, >_ROBOT_ALT, >_SPIDER2, >_WAVE2, >_SWING2, <_CUBE2
        .byte >_MINI_CUBE2, >_MINI_SHIP2, >_MINI_BALL2, >_MINI_UFO2, >_MINI_ROBOT2, >_MINI_SPIDER2, >_MINI_WAVE2, >_MINI_SWING2, <_MINI_CUBE2
.endproc

; char bg_collision_sub();
.segment "CODE_2"

.importzp _temp_x, _temp_y, _temp_room, _collision

.export _bg_collision_sub
.proc _bg_collision_sub
    ; Returns collision block indexed by
	; temp_x for X
	; temp_room and y for Y
    LDA _temp_y     ;
    CMP #$F0        ;   if(temp_y >= 0xf0) return 0;
    BCS Return0		;__
    AND #$F0        ;	temp_y & 0xF0
    STA tmp1        ;__
	LDA _temp_x		;
	LSR				;
	LSR				;	temp_x >> 4
	LSR				;
	LSR				;__
	ORA tmp1		;	coordinates = (temp_x >> 4) + ((temp_y) & 0xf0);
	TAY				;__

	LDA _temp_room	;	tmp3 = temp_room&1;
	AND #$01		;__
	ORA #>collMap0
	STA ptr1+1
	LDA #$00
	STA ptr1

	.if USE_ILLEGAL_OPCODES
		LAX (ptr1),Y
	.else
		LDA (ptr1),Y
		TAX
	.endif
	LDA metatiles_coll,X	;	return is_solid[collision];
	STA _collision	;
	RTS				;__

	Return0:
	LDA #$00
	sta _collision
	RTS

.endproc

.segment "CODE_2"

.export crossPRGBankJump
.proc crossPRGBankJump
	; AX = address of function
	; Y = bank of function
	STA ptr4
	STX ptr4+1
	LDA mmc3PRG1Bank
	PHA
	TYA
	JSR mmc3_set_prg_bank_1
	LDA ptr3
	LDX ptr3+1
	JSR callptr4
	STA ptr3
	STX ptr3+1
	PLA
	JMP mmc3_set_prg_bank_1
.endproc

; void __fastcall__ playPCM(uint8_t sample);
.segment "XCD_BANK_01"

.export _playPCM
.proc _playPCM
PCM_ptr = ptr1
    ; A = Sample
	tay
	lda SampleRate, y
    sta tmp1
	ldx Bank, y

    ;enable DMC but disable DPCM
    lda #%00000000
    sta FAMISTUDIO_APU_DMC_FREQ
    lda #%00001011
    sta FAMISTUDIO_APU_SND_CHN
    lda #0
	sta PCM_ptr
    sta FAMISTUDIO_APU_DMC_LEN
    lda #%00011011
    sta FAMISTUDIO_APU_SND_CHN
    ; mute sqs+noi
    lda #$30
    sta FAMISTUDIO_APU_NOISE_VOL
    lda #%00110000
    sta FAMISTUDIO_APU_PL1_VOL
    sta FAMISTUDIO_APU_PL2_VOL
    ;init pcm
;    lda #<GeometryDashPCM
 ;   sta PCM_ptr
 ;   ldx #<.bank(GeometryDashPCM)
 	ldy #0

    ;play pcm
@RestartPtr:
    lda #>$C000
    sta PCM_ptr+1
@LoadBank:
    txa
    jsr mmc3_set_prg_bank_0
    inx
@LoadSample:
    lda tmp1	; 3
	sec			; 2
@Delay:
	sbc #1		;	5n cycles
	bcs @Delay	;__
	; 	beq	@noburn	; 2/3
	; 7x jsr BurnCycles	; 26
	; @noburn:
	; 	php			;
	; 	plp			;
	; 	php			;	17
	; 	plp			;
	; 	bit PCM_ptr	;__
	;	old code: if smp == 0 - 22 cycles, if not - 204 cycles
	;	new: 
	
    lda (PCM_ptr),y
    beq @DoneWithPCM
    sta $4011
    iny
    bne @LoadSample
    inc PCM_ptr+1
    lda PCM_ptr+1
    cmp #>($c000+$2000)
    bcc @LoadSample
    jmp @RestartPtr
@DoneWithPCM:
    lda #%00011111
    sta FAMISTUDIO_APU_SND_CHN
    lda #<FIRST_DMC_BANK
	jmp mmc3_set_prg_bank_0

; BurnCycles:	; 6 for JSR
;     php	;	7
;     plp	;__
;     php	;	7
;     plp	;__
;     rts	;	6

Bank:
    .byte <.bank(GeometryDashPCMA)
    .byte <.bank(GeometryDashPCMB)

SampleRate:
	.byte 3		;(22-5+1)/5-1
	.byte 39	;(204-5+1)/5-1
.endproc


; uint16_t hexToDec (uint16_t input)
.segment "CODE_2"

.export _hexToDec
.proc _hexToDec
	; AX = input
	; hexToDecOutputBuffer = output
	; AX = duplicate output

	; Step 1. loop over X and add 256
	start:
		INX			; for BEQ ending condition
		STX tmp1
		LDY #0		; for storing when overflows
		STY hexToDecOutputBuffer+2
		STY hexToDecOutputBuffer+3
		STY hexToDecOutputBuffer+4
	
	clr_x_loop:
		LDX #0
	loop:
		SEC
		SBC #10
		BCS :+
			DEC tmp1
			BEQ end
		:
		INX
		CPX #10
		BNE loop	; carry is always clear

		INC hexToDecOutputBuffer+2
		CPX hexToDecOutputBuffer+2	; if 10 == out[2]
		BNE clr_x_loop
		STY hexToDecOutputBuffer+2

		INC hexToDecOutputBuffer+3
		CPX hexToDecOutputBuffer+3	; if 10 == out[3]
		BNE clr_x_loop
		STY hexToDecOutputBuffer+3

		INC hexToDecOutputBuffer+4
		BNE clr_x_loop	; BRA

	end:
		; Carry is clear
		ADC #10
		STA hexToDecOutputBuffer+0
		STX hexToDecOutputBuffer+1
		RTS
.endproc



; void printDecimal (uintptr_t vram_adr, uint16_t value, uint8_t digits, uint8_t zeroChr, uint8_t spaceChr)
.segment "CODE_2"

.export __printDecimal
.proc __printDecimal
	; XA = vram_adr
	; sreg = value
	; xargs[0] = digits
	; xargs[1] = zeroChr
	; xargs[2] = spaceChr
	value = sreg
	digits = xargs+0
	zeroChr = xargs+1
	spaceChr = xargs+2

	start:
		LDY VRAM_INDEX
		STA VRAM_BUF, Y		;
		TXA					;	VRAM pointer
		STA VRAM_BUF+1, Y	;__
		LDA digits			;	Length
		STA VRAM_BUF+2, Y	;__
		CLC					;
		ADC VRAM_INDEX		;	Update VRAM index
		ADC #3				;__
		PHA					;
		TAY					;
		LDA #$FF			;	Mark section as taken
		STA VRAM_BUF, Y		;__

		LDA value			;
		LDX value+1			;	Convert to decimal
		JSR _hexToDec		;__

		LDY VRAM_INDEX

		LDX digits
		DEX
		BEQ numberLoop

	spaceLoop:
		LDA hexToDecOutputBuffer, X
		BNE numberStart
		LDA spaceChr
		STA VRAM_BUF+3, Y
		INY
		DEX
		BNE spaceLoop

		; Fallthrough on the last digit
	numberLoop:
		LDA hexToDecOutputBuffer, X
	numberStart:
		CLC
		ADC zeroChr
		STA VRAM_BUF+3, Y
		INY
		DEX
		BPL numberLoop

	end:
		PLA
		STA VRAM_INDEX
		RTS

.endproc

; void pad_poll_both();
.segment "CODE_2"

.export _pad_poll_both
.proc _pad_poll_both
	LDA #0
	jsr _pad_poll
	; returns 0 in X, but LDA #1 is faster anyway
	LDA #1
	jsr _pad_poll
	; returns 0 in X, return nothing
	txa
	rts
.endproc


; void update_level_completeness();
.segment "CODE_2"

.import _level, _has_practice_point
.import _level_completeness_normal

.export _update_level_completeness
.proc _update_level_completeness
	levelsInTable = $40

	levelLengthLo = ptr1+0
	levelLengthMd = ptr1+1
	levelLengthHi = tmp1

	percentage = tmp2

	start:
		LDY	_level
		LDA	_level_lengths_lo, Y
		STA levelLengthLo
		.if MID_LEVEL_LENGTHS_ENABLED
			LDA _level_lengths_md, Y
			STA levelLengthMd
		.endif
		.if HIGH_LEVEL_LENGTHS_ENABLED
			LDA _level_lengths_hi, Y
			STA levelLengthHi
		.endif

		LDY #$FF
		.if MID_LEVEL_LENGTHS_ENABLED
			STY percentage
		.endif

		LDA _scroll_x+3
		STA sreg+1
		LDA _scroll_x+2
		STA sreg+0
		LDX _scroll_x+1
		.if MID_LEVEL_LENGTHS_ENABLED
			LDY _scroll_x+0
		.else
			LDA _scroll_x+0
		.endif

		; Adjust for BEQ ending condition
		INC sreg+1
		.if !HIGH_LEVEL_LENGTHS_ENABLED
			INC sreg+0
		.endif
		.if !MID_LEVEL_LENGTHS_ENABLED
			INX
		.endif

	loop_sec:
		.if MID_LEVEL_LENGTHS_ENABLED
			TYA
		.endif
		SEC
	loop:
		.if MID_LEVEL_LENGTHS_ENABLED
			INC percentage
		.else
			INY
		.endif
		SBC	levelLengthLo
		BCS loop

		.if MID_LEVEL_LENGTHS_ENABLED
			TAY
			TXA
			SBC levelLengthMd
			TAX
			BCS loop_sec
		.else
			DEX
			BNE loop_sec
		.endif

		.if HIGH_LEVEL_LENGTHS_ENABLED
			LDA sreg+0
			SBC levelLengthHi
			STA sreg+0
			BCS loop_sec
		.else
			DEC	sreg+0
			BNE loop_sec
		.endif

		DEC sreg+1
		BNE loop_sec

	fin:

		.if MID_LEVEL_LENGTHS_ENABLED
			LDY percentage
		.endif

		CPY #99			;
		BCC :+			;	Cap at 99
			LDY #99		;	100% is reserved for complete levels only
		:				;__

		LDA _has_practice_point	;
		BEQ :+					;
			LDA #levelsInTable	;	Calculate whether to store 
		:						;	the new completeness in the
		CLC						;	normal or practice table
		ADC _level				;
		TAX						;__

		TYA						;
		CMP _level_completeness_normal, X
		BCC :+					;	Update value if bigger than last one
			STA _level_completeness_normal, X
		:						;__
		RTS

.endproc

; [not used in C]
.segment "CODE_2"

.import	__DATA_LOAD__,	__DATA_RUN__,	__DATA_SIZE__,	__DATA_LOAD_BANK__
.import	__SFX_LOAD__,	__SFX_RUN__,	__SFX_SIZE__,	__SFX_LOAD_BANK__

.global copydata
.proc copydata

	seg_count = 2

	current_area = tmp1
	current_bank = tmp2

	src = sreg
	dest = xargs+0

	start:
		lda	#0
		sta	current_bank
		ldy	#<seg_count

	loop:
		lda	load_lo-1,	y
		sta	src+0
		lda	load_hi-1,	y
		sta	src+1
		
		lda	run_lo-1,	y
		sta	dest+0
		lda	run_hi-1,	y
		sta	dest+1

		lda	bank-1,	y
		beq	@no_bankswitch
			cmp	current_bank
			beq	@no_bankswitch
				jsr	mmc3_tmp_prg_bank_1	; only allowed because this is run on init
				sta	current_bank
		@no_bankswitch:

		lda	size_lo-1,	y
		ldx	size_hi-1,	y
		sty	current_area
		jsr	__memcpy

		ldy	current_area
		dey
		bne	loop

	rts

load_lo:
	.byte	<__DATA_LOAD__,	<__SFX_LOAD__
load_hi:
	.byte	>__DATA_LOAD__,	>__SFX_LOAD__

run_lo:
	.byte	<__DATA_RUN__,	<__SFX_RUN__
run_hi:
	.byte	>__DATA_RUN__,	>__SFX_RUN__

size_lo:
	.byte	<__DATA_SIZE__,	<__SFX_SIZE__
size_hi:
	.byte	>__DATA_SIZE__,	>__SFX_SIZE__

bank:
	.byte	<__DATA_LOAD_BANK__,	<__SFX_LOAD_BANK__

.endproc