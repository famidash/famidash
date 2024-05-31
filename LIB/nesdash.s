; Custom routines implemented specifically for famidash (some are totally not stolen from famitower)
.importzp _gamemode
.importzp _tmp1, _tmp2, _tmp3, _tmp4, _tmp5, _tmp6, _tmp7, _tmp8  ; C-safe temp storage
.import pusha, pushax
.import _scroll_x

.macpack longbranch

.importzp _level_data, _sprite_data
level_data = _level_data
sprite_data = _sprite_data

.define gamemode_count 7

; 1 makes some code slightly faster, 0 makes it work on famiclones
.define use_illegal_opcodes 1

.segment "ZEROPAGE"
	rld_value:		.res 1
	rld_run:		.res 1

.segment "BSS"
	columnBuffer:   .res 15 + 15 + 15 + 15

	current_song_bank:	.res 1
	scroll_count:		.res 1
	auto_fs_updates:	.res 1
	extceil:			.res 1
	rld_load_value:		.res 1
	min_scroll_y:		.res 2

	seam_scroll_y:		.res 2

.export _scroll_count := scroll_count
.export _extceil := extceil
.export _auto_fs_updates := auto_fs_updates
.export _min_scroll_y := min_scroll_y

.export _parallax_scroll_column := parallax_scroll_column
.export _parallax_scroll_column_start := parallax_scroll_column_start
	parallax_scroll_column: .res 1
	parallax_scroll_column_start: .res 1

.segment "CODE"

shiftBy4table:
.byte $00, $10, $20, $30
.byte $40, $50, $60, $70
.byte $80, $90, $A0, $B0
.byte $C0, $D0, $E0, $F0

;void __fastcall__ oam_meta_spr_flipped(unsigned char flip, unsigned char x,unsigned char y,const unsigned char *data);
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
		BVC :+      ;__
		EOR #$FF    ;	If HLIPd, then two's complement
		ADC #($100 - 8)	; Carry is clear
		SEC         ;__
		:           ;
		adc sreg+0
		sta OAM_BUF+3,x
		lda (PTR),y     ;y offset
		INY
		clc
		BIT xargs+0 ;	Check for bit 7 (VFLIP)
		BPL :+      ;__
		EOR #$FF    ;	If VLIPd, then two's complement
		; ADC #($100 - 16)	; Carry is clear, Y is -16'd because of us using 8x16 mode
		SEC         ;__
		:           ;
		adc sreg+1
		sta OAM_BUF+0,x
		lda (PTR),y     ;tile
		iny
		sta OAM_BUF+1,x
		lda (PTR),y     ;attribute
		iny
		EOR xargs+0
		sta OAM_BUF+2,x
		inx
		inx
		inx
		inx
		jmp loop

	end:

		stx SPRID
		rts
.endproc

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

.global _level_list_lo, _level_list_hi, _level_list_bank, _sprite_list_lo, _sprite_list_hi, _sprite_list_bank
.import _song, _speed, _lastgcolortype, _lastbgcolortype
.import _rld_column
.import _level_data_bank, _sprite_data_bank
.export _init_rld
_init_rld:
	; A = level ID

	; Get pointers:
	TAY						;__ Load pointer to tables
	LDA	_sprite_list_lo,y	;
	STA	_sprite_data+0		;__	Get low pointer to sprite data 
	LDA	_sprite_list_hi,y	;
	STA	_sprite_data+1		;__	Get high pointer to sprite data 
	LDA	_sprite_list_bank,y ;	Get sprite data bank
	; CLC						;
	; ADC #<FIRST_SPRITE_BANK	;
	STA	_sprite_data_bank	;__
	LDA	_level_list_lo,y	;
	STA	_level_data+0		;__	Get low pointer to level data 
	LDA	_level_list_hi,y	;
	STA	_level_data+1		;__	Get high pointer to level data 
	LDA	_level_list_bank,y	;	Get level data bank
	STA	_level_data_bank	;__

	JSR mmc3_set_prg_bank_1

	LDY #$00			;-	For both (zp),y addressing and rld_column
	STY _rld_column		;__	Reset scrolling

	; Read header
	LDA	(level_data),y	;
	STA	_song			;	Song number
	incw_check level_data

	LDA	(level_data),y	;
	STA	_gamemode		;	Starting level number
	incw_check level_data

	LDA	(level_data),y	;
	STA	_speed			;	Starting speed
	incw_check level_data

	LDA	(level_data),y	;	Starting BG color
	AND	#$3F			;	Store normal color (pal_col(0, tmp2))
	STA	PAL_BUF+0		;__
	STA	_lastbgcolortype
	SEC					;	A = faded OG color (A - 10)
	SBC #$10			;__
	BPL :+				;
		LDA	#$0F		;	if (faded color invalid) color = $0F (canonical black)
	:					;__
	STA	PAL_BUF+1		;__	Store faded color (pal_col(1, tmp2-0x10 or 0x0F))
	STA	PAL_BUF+9		;__	Store faded color (pal_col(1, tmp2-0x10 or 0x0F))
	incw_check level_data

	LDA	(level_data),y  ;	Starting ground color
	AND	#$3F			;	Store normal color (pal_col(6, tmp2))
	STA	PAL_BUF+6		;__
	STA	_lastgcolortype	;
	SEC					;	A = faded OG color (A - 10)
	SBC #$10			;__
	BPL :+				;
		LDA	#$0F		;	if (faded color invalid) color = $0F (canonical black)
	:					;__
	STA	PAL_BUF+5		;__	Store faded color (pal_col(5, tmp2-0x10 or 0x0F))
	INC <PAL_UPDATE		;__	Yes, we do need to update the palette

	incw_check level_data

	.if use_illegal_opcodes
		lax (level_data),y
	.else
		LDA	(level_data),y
		TAX
	.endif
	EOR #$FF			;
	CLC					;	Level height
	ADC #$01			;
	STA rld_load_value	;__

	LDA	#$01			;- (to automatically shift out 1)
	CPX	#27+1			;	Extceil flag
	ROR					;
	STA	extceil			;__

	@min_scroll_y_calc:
		LDA	#$00			;
		STA	min_scroll_y+1	;__
		
		TXA					;
	@min_scroll_y_loop:
		; SEC done by LDA #$80, and looping
		SBC	#15				;__
		BCC	@min_scroll_y_fin
		INC	min_scroll_y+1
		TAX
		BCS	@min_scroll_y_loop	; = BRA
	@min_scroll_y_fin:
		LDA	shiftBy4table, X
		ORA #$08
		STA min_scroll_y

	incw_check level_data

SetupNextRLEByte:
    LDA	(level_data),y  ;
    bmi single_rle_byte
    STA	rld_run         ;__ Load rld_run, ++level_data
    incw_check level_data     ;__

    LDA	(level_data),y  ;
    STA	rld_value       ;	Load rld_value, ++level_data
    ; JMP incwlvl_checkC000

    INC level_data
    BNE :+
incwlvl_checkC000:  ; clobbers A
        INC level_data+1
        bit level_data+1
        ; since the high byte will only be $Ax or $Bx, when bit 6 is set then its rolled over to $c0
        bvc :+
        pha 
            ; switch banks
            LDA	#$A0            ;	Reset memory-mapped ptr
            STA	level_data+1    ;__
            INC _level_data_bank ;_ Increment bank
            LDA	_level_data_bank
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

.segment "CODE_2"

.export _unrle_next_column
.proc _unrle_next_column

    ; Count up to zero to remove a cmp instruction
    ldx rld_load_value
    ldy #$00
    lda rld_value

    firstLoop:
        sta columnBuffer - ($100 - (15 + 15 + 15 + 12)), x
        dec rld_run
        bmi updateValueRun
        inx 
        bmi firstLoop
        bpl end ; Guaranteed jump
    
    updateValueRun:
        ; if bit 7 of the byte is set, then its a run of length 1
        ; otherwise this is a length < 127 byte and we need to read another
        lda (level_data), y
        bmi singleByteRun
        sta rld_run               ;__ Load rld_run, ++level_data
        incw_check level_data     ;__

        lda (level_data), y       ;
        sta rld_value             ;	Load rld_value, ++level_data
        incw_check level_data

        lda rld_value
        inx 
        bmi firstLoop
        bpl end ; Unconditional
    
    singleByteRun:
        and #$7f
        sta rld_value
        ; y = 0
        sty rld_run
        incw_check level_data
        inx 
        bmi firstLoop
        ; and then fallthrough to copying to the collision map

    end:

		ldx _rld_column
		inx
		.if use_illegal_opcodes
			lda #$0F
			sax _rld_column
		.else
			txa
			and #$0f
			sta _rld_column
		.endif
	rts
.endproc

.export _copy_column_to_collmap
.proc _copy_column_to_collmap
	.if use_illegal_opcodes
		ldx _rld_column
		dex
		lda #$0F
		axs #$00
	.else
		lda _rld_column
		sec
		sbc #$01
		and #$0F
		tax
	.endif
	ldy rld_load_value
	cpy #<-(15+15+12)
	bcs write_collmap1
		.repeat 15, I
			lda columnBuffer + I
			sta collMap0 + I * 16, x
		.endrepeat
	write_collmap1:
	cpy #<-(15+12)
	bcs write_collmap2
		.repeat 15, I
			lda columnBuffer+(15*1) + I
			sta collMap1 + I * 16, x
		.endrepeat
	write_collmap2:
	cpy #<-(12)
	bcs write_collmap3
		.repeat 15, I
			lda columnBuffer+(15*2) + I
			sta collMap2 + I * 16, x
		.endrepeat
	write_collmap3:
		.repeat 12, I
			lda columnBuffer+(15*3) + I
			sta collMap3 + I * 16, x
		.endrepeat
	write_ground:
		.repeat 3, I
			lda ground + I * 16, x
			sta columnBuffer+(15*3)+12+I
		.endrepeat
	rts
.endproc

.global metatiles_top_left, metatiles_top_right, metatiles_bot_left, metatiles_bot_right, metatiles_attr
.import _increase_parallax_scroll_column
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

	SeamValue = ptr3+1

    .export _draw_screen_R_frame0 := frame0
    .export _draw_screen_R_frame1 := frame1
    .export _draw_screen_R_frame2 := frame2
    ; Write architecture:

    ; Frame 0:
    ;	Write 0 updates the upper nametable's left tiles
    ;	Write 1 updates the lower nametable's left tiles
    ; Frame 1:
    ;	Write 0 updates the upper nametable's right tiles
    ;	Write 1 updates the lower nametable's right tiles
    ; Frame 2:
    ;	Attributes 
start:
    
		LDA	_scroll_x           ;__ Highbyte of scroll_x
		LSR                     ;
		LSR                     ;	>> 4
		LSR                     ;
		LSR                     ;__
		STA	tmp4

		LDX scroll_count
		BNE frame2

		LDA	tmp4
		CMP _rld_column         ;	If X == rld column, decompress shit
		BEQ frame0
		RTS
    
	frame2:
        CPX #$01
        BEQ frame1
        JMP attributes

tilewrites:
	frame0:
        ; Switch banks
        LDA	_level_data_bank
        JSR mmc3_set_prg_bank_1

        JSR _unrle_next_column
		JSR _copy_column_to_collmap

		; Seam position:
		; Y ≥	| Y <	| A		| B		|
		; 	0	|  $78	|	0	|	1	|
		;  $78	| $178	|  0/2	|	1	|
		; $178	| $278	|	2	|  1/3	|
		; $278	| $2F0	|	2	|	3	|
		; $10 is added to Y at all F0 boundaries but the edge

		; Get seam position for attributes
		; Seampos = (((Y-$78)>>4)&$FE)<<4 = (Y-78)&$FFE0 
		LDX	_scroll_y+1
		LDA	_scroll_y
		SEC
		SBC	#$78	;
		BCS	:+		;	AX = scroll_y - $78
			DEX		;__
		:
		CPX	#$02	;
		BCS	:+		;	if X == 2 or -1 (aka no seam)
			LDA #$FF;	seam_scroll_y = $FFFF
			TAX		;
		:			;__
		STA	seam_scroll_y
		STX seam_scroll_y

	frame1:

        ; Writing to nesdoug's VRAM buffer starts here
        LDX VRAM_INDEX

        ; In-house replacement of get_ppu_addr, only counts X
        ; Address is big-endian
        LDY _rld_column ;	000xxxx0 - the left tiles of the metatiles
        DEY
        TYA
        AND	#$0F
        ASL         ;__
        LDY scroll_count
        BEQ :+
            ORA	#$01    ;	000xxxx1 - the right tiles of the metatiles
        :
        STA	VRAM_BUF+TileOff0+1,X
        STA	VRAM_BUF+TileOff1+1,X

        lda _scroll_x + 1 ; high byte
        and #%00000001
        eor #%00000001
        asl
        asl
        ora #($20+$80)  ; 0th nametable + NT_UPDATE_VERT
        STA	VRAM_BUF+TileOff0,X
        ORA	#$08        ; 2nd nametable
        STA	VRAM_BUF+TileOff1,X


        ; First part of the update: the tiles
        ; Amount of data in the sequence - 27*2 tiles (8x8 tiles, left sides of the metatiles)
        LDA	#(15*2)
        STA	VRAM_BUF+TileOff0+2,X
        STA	VRAM_BUF+TileOff1+2,X

        ; The sequence itself:
        
        ; Load Y value
        LDA rld_load_value
		SEC
		SBC #$03
        sta CurrentRow
        ; Load max value
        LDA	#15 - 1
        STA	LoopCount
        ; Check if doing a left or right hand write
        LDA	scroll_count
        AND	#1
        beq @LeftWrite
            ; Right side write
            ; Call for upper tiles
            JSR right_tilewriteloop
            jmp @WriteBottomHalf
		@LeftWrite:
            JSR left_tilewriteloop
	@WriteBottomHalf:
        ; Load new max
        LDA	#15 - 1
        STA	LoopCount
        ; Add offset to X
        TXA
        CLC
        ADC #(TileSizeHi-(15*2))
        TAX
        
        LDA	scroll_count
        AND	#1
        beq @LeftWrite2
            JSR right_tilewriteloop
            jmp @RenderParallax
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
        LDA	#$FF
        STA	VRAM_BUF+TileEnd,X

        ; Declare this section as taken
        TXA
        CLC
        ADC #TileEnd
        STA	VRAM_INDEX

        INC scroll_count

        RTS

	right_tilewriteloop:
            ldy CurrentRow
            LDA	columnBuffer - ($100 - (15 + 15 + 15 + 15)),Y
            tay
            ; y is the metatile id
            lda metatiles_top_right, y
            STA	VRAM_BUF+TileOff0+3,X
            lda metatiles_bot_right, y
            STA	VRAM_BUF+TileOff0+4,X
            
            INX
            INX
            inc CurrentRow
            DEC LoopCount
            BPL right_tilewriteloop
        rts
    left_tilewriteloop:
            ldy CurrentRow
            LDA	columnBuffer - ($100 - (15 + 15 + 15 + 15)),Y
            tay
            ; y is the metatile id
            lda metatiles_top_left, y
            STA	VRAM_BUF+TileOff0+3,X
            lda metatiles_bot_left, y
            STA	VRAM_BUF+TileOff0+4,X
            
            INX
            INX
            inc CurrentRow
            DEC LoopCount
            BPL left_tilewriteloop
        rts
        
    RenderParallaxLoop:
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
        rts

attributes:
		NametableAddrHi = tmp1
        ; Attribute write architecture:

        ; | Ad|dr |dat|
        ;	0   1   2
        ; Addr = VRAM address

        ; 1 byte can theoretically be saved by using a vertical
        ; sequence of 2 bytes, but this comes at a cost of 23
        ; cycles per 2 bytes in vblank (80 vs 103), and vlank
        ; time is not to be wasted

        ; Decremented rld_column, very useful
        LDX _rld_column
        DEX
		.if use_illegal_opcodes
			lda #$0f
			sax ptr3
		.else
			TXA
			AND	#$0F
			STA	ptr3
		.endif

		; Seam pos for attributes:
		; <seam_scroll_y & $E0 | >seam_scroll_y & 1 
		LDA seam_scroll_y
		AND #$E0
		STA SeamValue
		LDA seam_scroll_y+1
		AND #$03	; add bit 1 to not use if FFFF
		ORA SeamValue
		STA SeamValue

        ; Get the ptr (I am not bothering with 2 separate loops)
        LDA	#>collMap0
        STA	ptr1+1
        LDA	ptr3
        AND	#$0E
        ; ADC #(<collMap0-1)    ; The low byte is 0
        STA	ptr1

        LDA	#8 - 1
		LDX #0
		STX ptr2+1
        JSR attributeCalc

        ; Last byte has no bottom tiles
        LDA	columnBuffer+7
        AND	#$0F
        STA	columnBuffer+7

        ; Update pointer
		INC ptr1+1

        ; Update new maximum
        LDA	#8+8 - 1
        JSR attributeCalc

		; Last byte has no bottom tiles
        LDA	columnBuffer+15
        AND	#$0F
        STA	columnBuffer+15

        ; Get address hi byte (either left or right side)
        lda _scroll_x + 1 ; high byte
        and #%00000001
        eor #%00000001
        asl
        asl
        ora #$23
        sta NametableAddrHi
        
        LDA	ptr3
        LSR
        ORA	#$C0
        
        ; Store address
        LDX VRAM_INDEX
        addressLoop:
            ; Low byte
            STA	VRAM_BUF+AttrOff0+1,X
            STA	VRAM_BUF+AttrOff1+1,X
            TAY
            ; High byte
            lda NametableAddrHi
            STA	VRAM_BUF+AttrOff0,X
            ORA	#$08
            STA	VRAM_BUF+AttrOff1,X
            TYA

            INX 
            INX
            INX

            CLC
            ADC #$08
            BCC addressLoop
        
        LDY #16

        LDA	VRAM_INDEX
        ADC #AttrEnd-1  ; Carry is set by the ADC : BCC
        STA	VRAM_INDEX  ; State that the block is now occupied
        TAX

        dataLoop:
            LDA	columnBuffer-1,Y
            STA	VRAM_BUF-3+2,X

            DEX
            DEX
            DEX
            DEY
            BNE dataLoop
        
        ; Finish off the routine
        ; X has VRAM_INDEX, mark this block as taken
        LDA	#$FF
        STA	VRAM_BUF+AttrEnd,X
        ; Reset frame counter
        LDA	#$00
        STA	scroll_count
        RTS

	attributeCalc:
		tmp5 = ptr2
		ColumnBufferIdx = ptr2+1
		STA	LoopCount

    	@loop:
            ; Read lower right metatile
            LDY #$11
			.if use_illegal_opcodes
				lax (ptr1),y
			.else
				LDA	(ptr1),Y
				tax
			.endif
            ; Read lower left metatile
			dey
			LDA	(ptr1), Y
			tay
			; Get their attributes
            lda metatiles_attr,x	; Lower right
			ASL
			ASL
			ora metatiles_attr,y	; Lower left
            STA	tmp5

            ; Read upper right metatile
            LDY #$01
            .if use_illegal_opcodes
				lax (ptr1),y
			.else
				LDA	(ptr1),Y
				tax
			.endif
			; Read upper left metatile
			dey
			LDA	(ptr1), Y
			tay
			; Get their attributes
            lda metatiles_attr,x	; Upper right
			ASL
			ASL
			ora metatiles_attr,y	; Upper left

			; Combine
			LDY tmp5	; Y has the lower metatile attrs, will shift by 4
			ORA	shiftBy4table,Y
			LDX ColumnBufferIdx
			STA	columnBuffer,X

            ; Increment pointer
            LDA	ptr1
            ; Last thing affecting carry is the ASL, which
            ; always shifts 0 into it if the metatile data
            ; is valid
            ADC #$20
			CMP SeamValue
			STA	ptr1
			BNE :+
				LDA #2-1	; Carry set by the CMP
				ADC ptr1+1
				STA ptr1+1
				DEC SeamValue	; to not activate it again
			:

            INC ColumnBufferIdx
            DEC LoopCount
            BPL @loop
        RTS


ParallaxBuffer:
	; Column striped parallax data definition
	; add to the tile for the next row, up to 6.
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

.import _ground
.export _load_ground
.proc _load_ground
	;A = ground num
	ASL						;
	TAX						;
	LDA	#$00				;
	TAY						;	ptr1 = ground[id]
	JSR	mmc3_set_prg_bank_1	;	mmc3_set_prg_bank_1(0)
	LDA	_ground, X			;	Y = 0
	STA	ptr1				;
	LDA	_ground+1, X		;
	STA	ptr1+1				;__
	LDX #<-48				;__	X = idx @ collmap data, count up to 0

	ground_ptr = ground-($100-48)

	; there's a max of 48 bytes of data to fill, 
	; the rle worst case is 96 bytes long,
	; therefore not needing to check for an overflow

	loop:
		LDA	(ptr1),y		;
		bmi single_rle_byte	;	Run
		STA	tmp1			;
		iny					;__

		LDA	(ptr1),y		;	Value
		iny					;__

		STY tmp2
		LDY tmp1
	mult_loop:
		STA	ground_ptr, X
		INX
		BEQ fin
		DEY
		BPL mult_loop
		LDY tmp2
		BNE loop	; Physically cannot be not 0

	single_rle_byte:
		AND	#$7F
		STA	ground_ptr, X
		INY
		INX
		BNE loop

	fin:
		RTS

.endproc

.export __draw_padded_text
; void __fastcall__ draw_padded_text(const void * data, unsigned char len, unsigned char total_len, unsigned int ppu_address)
.proc __draw_padded_text
	; XA = ppu_address
	; sreg[0] = total_len
	; sreg[1] = len
	; xargs[0:1] = data

	.define spaceChr $FE
	.define data xargs+0
	.define total_len sreg+0
	.define len sreg+1

	LDY VRAM_INDEX
	STA	VRAM_BUF, Y	;
	TXA					;	vram pointer
	STA	VRAM_BUF+1, Y	;__
	LDA	total_len		;	total length
	STA	VRAM_BUF+2, Y	;__

	SEC					;   Total padding
	SBC len				;__
	LSR					;	Get left offset
	STA	tmp1			;__
	ADC #$00			;	Get right offset
	TAY					;__

	LDA	total_len
	ADC	VRAM_INDEX		;	Carry is guaranteed to be clear by LSR : ADC #$00
	; If carry is still set, we have big problems
	; BCS some shit to do
	TAX
    ADC #$03
    STA	VRAM_INDEX

	LDA	#$FF			;	Finish off the write
	STA	VRAM_BUF+3, X	;__

	CPY #$00	; Had to do this, very sorry
	BEQ main_data

	LDA	#spaceChr

	pad_loop_right:
		STA	VRAM_BUF+2, X
		DEX
		DEY
		BNE pad_loop_right
		
	main_data:
		LDY len
		DEY

	main_data_loop:
		LDA	(<data), Y
		STA	VRAM_BUF+2, X
		DEX
		DEY
		BPL main_data_loop

	LDY tmp1	;	Pad left amount
	BEQ fin		;__

	LDA	#spaceChr

	pad_loop_left:
		STA	VRAM_BUF+2, X
		DEX
		DEY
		BNE pad_loop_left

	fin:
		RTS

.endproc


;void __fastcall__ movement(void);
.pushseg
.segment "XCD_BANK_01"

.import _cube_movement, _ship_movement, _ball_movement, _ufo_movement, _robot_movement, _spider_movement, _wave_movement
.export _movement
.proc _movement
	LDX _gamemode
	CPX #gamemode_count
	BPL end
	LDA	jump_table_lo, X
	STA	<PTR
	LDA	jump_table_hi, X
	STA	<PTR+1
	JMP (PTR)

	end:
		RTS

	jump_table_lo:
		.byte <_cube_movement, <_ship_movement, <_ball_movement, <_ufo_movement, <_cube_movement, <_spider_movement, <_wave_movement
	jump_table_hi:
		.byte >_cube_movement, >_ship_movement, >_ball_movement, >_ufo_movement, >_cube_movement, >_spider_movement, >_wave_movement
.endproc
.popseg

;void __fastcall__ music_play(unsigned char song);
.import _options, FIRST_MUSIC_BANK
.export _music_play
.proc _music_play  
    bit _options ; sets N flag to bit 7 of _options without affecting a  
    bpl musicon
    rts  
musicon:  
    LDY #$00  
    tsx
bank_loop:
    PHA
    SEC
    SBC music_counts, Y
    BCC found_bank
    INY
    TXS ;Act as if no PHA happened
    BCS bank_loop  ; BRA
found_bank:
    TYA
    PHA
    ; No CLC needed as we jumped here with a BCC
    ADC #<FIRST_MUSIC_BANK
    JSR mmc3_tmp_prg_bank_1
    PLA
    CMP current_song_bank
    BEQ :+
    ;If different bank than before reinitalize FS
        STA	current_song_bank
        TAY
        LDX music_data_locations_lo, Y
        LDA	music_data_locations_hi, Y
        TAY
        LDA	#$01
        JSR famistudio_init
    :
    PLA
    JSR famistudio_music_play
    
    JMP _mmc3_pop_prg_bank_1

; Tables currently generated manually

music_data_locations_lo:
.byte <music_data_famidash_music1, <music_data_famidash_music2, <music_data_famidash_music3,  <music_data_famidash_music4
music_data_locations_hi:
.byte >music_data_famidash_music1, >music_data_famidash_music2, >music_data_famidash_music3, >music_data_famidash_music4
music_counts:
.byte 2, 3, 3, $FF  ;last bank is marked with an FF to always stop bank picking
.endproc

; void __fastcall__ sfx_play(unsigned char sfx_index, unsigned char channel);
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

; void __fastcall__ music_update (void);
.export _music_update
.proc _music_update
    LDA	current_song_bank
    CLC
    ADC #<FIRST_MUSIC_BANK
    JSR mmc3_tmp_prg_bank_1

    JSR famistudio_update
    JMP _mmc3_pop_prg_bank_1
.endproc
; Because i JMPed, the routine is over


;void load_next_sprite(void){
;    mmc3_tmp_prg_bank_1(SPR_BANK_00);
;    if (sprite_data[spr_index<<3] == TURN_OFF) return;
;    tmp3 = sprite_data[(spr_index<<3)+0];  low_byte(activesprites_x[spr_index % max_loaded_sprites]) = tmp3; 
;    tmp3 = sprite_data[(spr_index<<3)+1]; high_byte(activesprites_x[spr_index % max_loaded_sprites]) = tmp3; 
;    tmp3 = sprite_data[(spr_index<<3)+2];  low_byte(activesprites_y[spr_index % max_loaded_sprites]) = tmp3;
;    tmp3 = sprite_data[(spr_index<<3)+3]; high_byte(activesprites_y[spr_index % max_loaded_sprites]) = tmp3;
;    tmp3 = sprite_data[(spr_index<<3)+4]; activesprites_type[spr_index % max_loaded_sprites] = tmp3;
;    // unused byte 5
;    // unused byte 6 
;    // unused byte 7
;
;
;    tmp3 = activesprites_x[spr_index]; activesprites_realx[spr_index % max_loaded_sprites] = tmp3;
;    tmp3 = activesprites_y[spr_index]; activesprites_realy[spr_index % max_loaded_sprites] = tmp3;
;
;    //gray_line();
;    mmc3_pop_prg_bank_1();
;    ++spr_index;
;}

.import _activesprites_x, _activesprites_y, _activesprites_type
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
    lda _spr_index
    asl
    tax

    ; Now read the data into the sprite
    
    ldy #0
    lda (_sprite_data),y
    cmp #$ff
    beq @Exit
    iny
    
    ; X - 2 bytes
    sta _activesprites_x,x
    lda (_sprite_data),y
    iny
    sta _activesprites_x+1,x

    ; Y - 2 bytes
    lda (_sprite_data),y
    iny
    sta _activesprites_y,x
    lda (_sprite_data),y
    iny
    sta _activesprites_y+1,x

    ; id - 1 byte
    ; Since its 1 byte, we want to divide the "pre multiplied" offset by 2
    txa
    lsr
    tax
    lda (_sprite_data),y
    ;   no iny, as we ain't using y anymore
    sta _activesprites_type,x

    ; Increment to the next sprite index - 
    ; Add the 5 back to the pointer
    LDA	#$05
    CLC
    ADC _sprite_data
    STA	_sprite_data
    BCC :+
        INC _sprite_data+1
    :

    ; Copy the low bytes for the active sprite here as well.
    ; Note we couldn't write this eariler when x was multiplied by 2
    txa
    asl
    tay
    lda _activesprites_x,y
    sta _activesprites_realx,x
    lda _activesprites_y,y
    sta _activesprites_realy,x

    ; Increment the _spr_index and and it with #$0F
    INX
    TXA
    AND	#$0F
    STA	_spr_index

@Exit:
    pla
    jmp mmc3_set_prg_bank_1
.endproc



; char get_position(void){
;     tmp5 -= scroll_x;
;     if (high_byte(tmp5) == 0xff) {
;         load_next_sprite();
;         return 0;
;     }
;     tmp6 -= scroll_y;
;     temp_x = tmp5 & 0x00ff;
;     temp_y = tmp6 & 0x00ff;
;     if (high_byte(tmp5)) return 0;
;     if (high_byte(tmp6)) return 0;
;     return 1;
; }
; void check_spr_objects(void){
;     for (index = 0; index < max_loaded_sprites; ++index){
;         activesprites_active[index] = 0;
;         low_byte(tmp5) = low_byte(activesprites_x[index]);
;         high_byte(tmp5) = high_byte(activesprites_x[index]);
;         low_byte(tmp6) = low_byte(activesprites_y[index]);
;         high_byte(tmp6) = high_byte(activesprites_y[index]);
;         activesprites_active[index] = get_position();
;         activesprites_realx[index] = temp_x;
;         activesprites_realy[index] = temp_y;
;     }
; }

.import _activesprites_active, _scroll_x, _scroll_y
.export _check_spr_objects := check_spr_objects
.proc check_spr_objects
    ; for each sprite we want to check to see if its active
    ; if it is, update its realx/y position
    ; if its not, attempt to load another sprite
    ldx #16 - 1

check_sprite_loop:
        ; X is the current sprite object, y is the premultiplied index for two byte fields
        txa
        asl
        tay
        ; Load two byte X coord to see if we went offscreen
        lda _activesprites_x, y
        sec
        sbc _scroll_x
        lda _activesprites_x+1, y
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
        lda _activesprites_y, y
        clc ; NOTICE: intentionally subtract 1 extra to position them on the screen better
        sbc _scroll_y
        sta _activesprites_realy, x
        lda _activesprites_y+1, y
        sbc _scroll_y+1
        bne sprite_offscreen

        ; totally onscreen so finish updating its scroll position
        lda _activesprites_x, y
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

.pushseg
.segment "XCD_BANK_00"

.define CUBE_GRAVITY $6B
.define MINI_CUBE_GRAVITY $6F

.import _player_x, _player_y, _player_gravity, _player_vel_x, _player_vel_y
.import _ballframe, _robotframe, _robotjumpframe, _spiderframe, _mario_mode, _icon
.importzp _cube_rotate, _mini
.import _CUBE, _SHIP, _BALL, _ROBOT, _ROBOT_ALT, _UFO, _SPIDER, _WAVE
.import _MINI_CUBE, _MINI_SHIP, _MINI_BALL, _MINI_ROBOT, _MINI_UFO, _MINI_SPIDER, _MINI_WAVE

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


drawplayer_center_offsets:
	;		Cub	Shp	Bal	UFO	RBT	SPI	Wav
	.byte	8,	8,	8,	8,	12,	12,	8	; normal size
	.byte	4,	12,	4,	12,	12,	12,	12	; mini 

.export _drawplayerone

.proc _drawplayerone

	LDA	_player_gravity+0
	BEQ :+
		LDA	#$80
	: STA	xargs+0

	LDX _player_y+1		;
	DEX					;	The Y of oam_meta_spr is high_byte(player_y[0])-1
	STX sreg+1			;__

	; Set up base pointer for jump tables
	LDA	_mini		;
	BEQ :+			;	Add 7 if mini mode 
		LDA	#gamemode_count
	:				;__
	CLC				;	Actual gamemode itself
	ADC _gamemode	;__
	LDX	_mario_mode	;
	beq :+			;	Other table if mario mode
		; There is no way this overflowed
		ADC #gamemode_count*2
	:				;__
	TAX				;	Set up base pointer for jump tables
    LDA sprite_table_table_lo, X
    STA ptr1        ;__
    LDA sprite_table_table_hi, X
    STA ptr1+1      ;__ Get high byte of table ptr

    LDY _player_x+1     ;__ temp_x = high_byte(player_x[0]);
	; The condition if is temp_x == 0 or is > 0xfc,
	; this can be expressed as (temp_x - 1) > 0xfb
	DEY					;
	CPY #$FC			;
	BCC :+				;	if(temp_x-1 > 0xfb) temp_x = 1;
		LDY #$00		;
	:					;__
	TYA
	SEC		; I decremented the Y, this is getting back at it
	ADC drawplayer_center_offsets, X
	STA	sreg+0			;__ The X of oam_meta_spr is temp_x

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
	dex
	jeq	wave

	; default: cube
	cube:
		; C code:
			; 		if (player_vel_y[0] == 0) cube_rotate[0] = round to the nearest 90°;
			; 		else cube_rotate[0] += player_gravity[0] ? -CUBE_GRAVITY : CUBE_GRAVITY;
			; 		cap the mf at 0..23
		@rounding_table = drawcube_rounding_table

		LDA	_player_vel_y+1		;	if player_vel_y == 0
		ORA	_player_vel_y+0		;
		BNE @no_round			;__
			STA	_cube_rotate+0	;__ low_byte = 0
			.if use_illegal_opcodes
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
			LDA	_cube_rotate+1	;	Round the cube rotation
			ADC @rounding_table, X
			STA	_cube_rotate+1	;
			TAX                 ;__
			JMP @fin_nold

		@no_round:
		LDA	_cube_rotate
		CLC

		LDX _player_gravity+0
		BNE @subtract

			ADC #<CUBE_GRAVITY      ;
			STA	_cube_rotate        ;
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
			STA	_cube_rotate		;
			BCS @fin				;	cube_rotate[0] -= CUBE_GRAVITY;
				DEC _cube_rotate+1	;
				BPL @fin			;__
				LDA	#23				;	Cap at 0
				STA	_cube_rotate+1	;__

		@fin:
			LDX _cube_rotate+1
		@fin_nold:
			LDA	_icon
			cmp #2
			bne	@norm
			LDA	drawcube_sprite_way, X
			jmp @don
		@norm:
			LDA	drawcube_sprite_table, X
		@don:
			TAX
			AND	#$C0
			STA	xargs+0	; flip setting
			TXA
			AND	#$07
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
		LDA	_options
		and #$04  ;platformer
		beq	@ball2
		lda _player_vel_x
		bne @ball2
		lda #0
		ldy #0
		beq @donball
	@ball2:
		LDA	_ballframe	;	Load index
		TAY				;__
		CLC				;	ballframe++;
		ADC #$01		;__
		AND	#$07		;__	if (ballframe > 7) { ballframe = 0; }
		STA	_ballframe	;__
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
		LDA	_player_vel_y+1	;__
		BEQ :+				;__	else if (highbyte == $00) { // later }
		BPL @go	    		;__	if (0 < highbyte < $80) {}	// do nothing with it
			INY				;__	else if ($80 ≤ highbyte ≤ $FF) { kandotemp3[0] = 2; }
			JMP fin			;__
		:
		ORA	_player_vel_y	;	if (player_vel_y == 0)
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
			LDA	_player_vel_y+1	;
			ORA	_player_vel_y	;	if (player_vel_y[0] == 0) {
			BNE @jump			;__
			LDA	_options
			and #$04
			beq	@cont1
			LDA	_player_vel_x
			bne @cont1
			lda #0
			sta _robotframe
			ldy #0
			jmp @fini
			
		@cont1:
			LDA	#0
			LDY _robotframe	;	[load robotframe[0] into Y]
			SEC				;	robotframe[0]++; (A is 0, so set the carry and bam)
			ADC _robotframe	;__
			CMP #20			;
			BCC @hur			;	if (robotframe[0] > 19) { robotframe[0] = 0; }	
				LDA	#$00	;__
			@hur:				;
			STA	_robotframe	;__
		@fini:
			JMP fin
		@jump:				;	} else {
			LDA	#20			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
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
		LDA	_player_vel_y+1	;
		ORA	_player_vel_y	;	if (player_vel_y[0] == 0) {
		BNE @jump			;
			LDA	_options
			and #$04
			beq	@cont1
			LDA	_player_vel_x
			bne @cont1
			lda #0
			sta _spiderframe
			ldy #0
			jmp fin
			
		@cont1:
			LDA	#0
			LDY _spiderframe	;	[load spiderframe[0] into Y]
			SEC				;	spiderframe[0]++; (A is 0, so set the carry and bam)
			ADC _spiderframe ;__
			AND	#$0F        ;   if (spiderframe[0] > 15) spiderframe[0] = 0;
			STA	_spiderframe;__
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


		LDA	(ptr1), Y		;	Load low byte
		PHA					;__
		INY					;
		LDA	(ptr1), Y		;	Load high byte
		TAX					;__
		PLA
		JMP __oam_meta_spr_flipped ;__	oam_meta_spr(temp_x, high_byte(player_y[0])-1, [whatever the fuck we set here]);

	sprite_table_table_lo:
		.byte <_CUBE, <_SHIP, <_BALL, <_UFO, <_ROBOT, <_SPIDER, <_WAVE
		.byte <_MINI_CUBE, <_MINI_SHIP, <_MINI_BALL, <_MINI_UFO, <_MINI_ROBOT, <_MINI_SPIDER, <_MINI_WAVE
	sprite_table_table_hi:
		.byte >_CUBE, >_SHIP, >_BALL, >_UFO, >_ROBOT, >_SPIDER, >_WAVE
		.byte >_MINI_CUBE, >_MINI_SHIP, >_MINI_BALL, >_MINI_UFO, >_MINI_ROBOT, >_MINI_SPIDER, >_MINI_WAVE
	sprite_table_table_lo2:
		.byte <_CUBE, <_SHIP, <_BALL, <_UFO, <_ROBOT_ALT, <_SPIDER, <_WAVE
		.byte <_MINI_CUBE, <_MINI_SHIP, <_MINI_BALL, <_MINI_UFO, <_MINI_ROBOT, <_MINI_SPIDER, <_MINI_WAVE
	sprite_table_table_hi2:
		.byte >_CUBE, >_SHIP, >_BALL, >_UFO, >_ROBOT_ALT, >_SPIDER, >_WAVE
		.byte >_MINI_CUBE, >_MINI_SHIP, >_MINI_BALL, >_MINI_UFO, >_MINI_ROBOT, >_MINI_SPIDER, >_MINI_WAVE
.endproc
drawplayer_common := _drawplayerone::common

.import _CUBE2, _SHIP2, _BALL2, _ROBOT2, _UFO2, _SPIDER2, _WAVE2
.import _MINI_CUBE2, _MINI_SHIP2, _MINI_BALL2, _MINI_ROBOT2, _MINI_UFO2, _MINI_SPIDER2, _MINI_WAVE2
.export _drawplayertwo

.proc _drawplayertwo

	LDA	_player_gravity+1
	BEQ :+
		LDA	#$80
	: STA	xargs+0	; flip

	LDX _player_y+3		;
	DEX					;	The Y of oam_meta_spr is high_byte(player_y[1])-1
	STX sreg+1			;__

	; Set up base pointer for jump tables
	LDA	_mini		;
	BEQ :+			;	Add 7 if mini mode 
		LDA	#gamemode_count
	:				;__
	CLC				;	Actual gamemode itself
	ADC _gamemode	;__
	TAX				;	Get low byte of table ptr
	LDA	sprite_table_table_lo, X
	STA	ptr1		;__
	LDA	sprite_table_table_hi, X
	STA	ptr1+1		;__	Get high byte of table ptr

	LDY _player_x+3     ;__ temp_x = high_byte(player_x[1]);
	; The condition if is temp_x == 0 or is > 0xfc,
	; this can be expressed as (temp_x - 1) > 0xfb
	DEY					;
	CPY #$FC			;
	BCC :+				;	if(temp_x-1 > 0xfb) temp_x = 1;
		LDY #$00		;
	:					;__
	TYA
	SEC		; I decremented the Y, this is getting back at it
	ADC drawplayer_center_offsets, X
	STA	sreg+0			;__ The X of oam_meta_spr is temp_x

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
	DEX			;	case 0x05: spider shit
	jeq wave	;__

	; default: cube
	cube:
		; C code:
			; 		if (player_vel_y[1] == 0) cube_rotate[1] = round to the nearest 90°;
			; 		else cube_rotate[1] += player_gravity[1] ? -CUBE_GRAVITY : CUBE_GRAVITY;
			; 		cap the mf at 0..23
		@rounding_table = drawcube_rounding_table

		LDA	_player_vel_y+3		;	if player_vel_y == 0
		ORA	_player_vel_y+2		;
		BNE @no_round			;__
			STA	_cube_rotate+2	;__ low_byte = 0
			.if use_illegal_opcodes
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
			LDA	_cube_rotate+3	;	Round the cube rotation
			ADC @rounding_table, X
			STA	_cube_rotate+3	;
			TAX					;__
			JMP @fin_nold

		@no_round:
		LDA	_cube_rotate+2
		CLC

		LDX _player_gravity+1
		BNE @subtract

			ADC #<CUBE_GRAVITY      ;
			STA	_cube_rotate+2		;
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
			STA	_cube_rotate+2		;
			BCS @fin				;	cube_rotate[0] -= CUBE_GRAVITY;
				DEC _cube_rotate+3	;
				BPL @fin			;__
				LDA	#23				;	Cap at 0
				STA	_cube_rotate+3	;__

		@fin:
			LDX _cube_rotate+3
		@fin_nold:
			LDA	_icon
			cmp #2
			bne	@norm
			LDA	drawcube_sprite_way, X
			jmp @don
		@norm:
			LDA	drawcube_sprite_table, X
		@don:
			TAX
			AND	#$C0
			STA	xargs+0
			TXA
			AND	#$07
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
		; LDA	_ballframe	;	Load index
		; TAY				;__
		; CLC				;	ballframe++;
		; ADC #$01			;__
		; AND	#$07			;__	if (ballframe > 7) { ballframe = 0; }
		; STA	_ballframe	;__
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
		LDA	_player_vel_y+3	;__
		BEQ :+				;__	else if (highbyte == $00) { // later }
		BPL @fin		    ;__	if (0 < highbyte < $80) {}	// do nothing with it
			INY				;__	else if ($80 ≤ highbyte ≤ $FF) { kandotemp3[1] = 2; }
			JMP drawplayer_common	    ;__
		:
		ORA	_player_vel_y+2	;	if (lowbyte == 0) kandotemp3[1] = 0;
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
		LDA	_player_vel_y+3	;
		ORA	_player_vel_y+2	;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
			LDA	_options
			and #$04
			beq	@cont1
			LDA	_player_vel_x+2
			bne @cont1
			lda #0
			sta _robotframe
			ldy #0
			jmp @fini
			
		@cont1:
			LDA	#0
			LDY _robotframe	;	[load robotframe[0] into Y]
			SEC				;	robotframe[0]++; (A is 0, so set the carry and bam)
			ADC _robotframe	;__
			CMP #20			;
			BCC @hur			;	if (robotframe[0] > 19) { robotframe[0] = 0; }	
				LDA	#$00	;__
			@hur:				;
			STA	_robotframe	;__
		@fini:
			JMP drawplayer_common
		@jump:				;	} else {
			LDA	#20			; ! This is the sizeof ROBOT / MINI_ROBOT, change it as needed
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
		LDA	_player_vel_y+3	;
		ORA	_player_vel_y+2	;	if (player_vel_y[1] == 0 || player_vel_y[1] == CUBE_GRAVITY) {
		BNE @jump	    	;__
			LDA	_options
			and #$04
			beq	@cont1
			LDA	_player_vel_x
			bne @cont1
			lda #0
			sta _spiderframe
			ldy #0
			jmp drawplayer_common
			
		@cont1:
			LDA	#0
			LDY _spiderframe+1;	[load spiderframe[1] into Y] 
			SEC				;	spiderframe[1]++; (A is 0, so set the carry and bam)
			ADC _spiderframe+1;__
			AND	#$0F        ;	if (spiderframe[1] > 15) spiderframe[1] = 0;
			STA	_spiderframe+1;__
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
		.byte <_CUBE2, <_SHIP2, <_BALL2, <_UFO2, <_ROBOT2, <_SPIDER2, <_WAVE2
		.byte <_MINI_CUBE2, <_MINI_SHIP2, <_MINI_BALL2, <_MINI_UFO2, <_MINI_ROBOT2, <_MINI_SPIDER2, <_MINI_WAVE2
	sprite_table_table_hi:
		.byte >_CUBE2, >_SHIP2, >_BALL2, >_UFO2, >_ROBOT2, >_SPIDER2, >_WAVE2
		.byte >_MINI_CUBE2, >_MINI_SHIP2, >_MINI_BALL2, >_MINI_UFO2, >_MINI_ROBOT2, >_MINI_SPIDER2, >_MINI_WAVE2
	sprite_table_table_lo2:
		.byte <_CUBE, <_SHIP, <_BALL, <_UFO, <_ROBOT_ALT, <_SPIDER, <_WAVE
		.byte <_MINI_CUBE, <_MINI_SHIP, <_MINI_BALL, <_MINI_UFO, <_MINI_ROBOT, <_MINI_SPIDER, <_MINI_WAVE
	sprite_table_table_hi2:
		.byte >_CUBE, >_SHIP, >_BALL, >_UFO, >_ROBOT_ALT, >_SPIDER, >_WAVE
		.byte >_MINI_CUBE, >_MINI_SHIP, >_MINI_BALL, >_MINI_UFO, >_MINI_ROBOT, >_MINI_SPIDER, >_MINI_WAVE
.endproc
.popseg

.pushseg 
.segment "CODE"

.importzp _temp_x, _temp_y, _temp_room, _collision
.export _bg_collision_sub
.proc _bg_collision_sub
    ; C code:
        ; if(temp_y >= 0xf0) return 0;
        ; coordinates = (temp_x >> 4) + ((temp_y) & 0xf0);
        ; // we just need 4 bits each from x and y
        ; tmp3 = temp_room&1; //high byte
        ; if (tmp3 && coordinates >= 0xc0) return COL_ALL;
        ; if (tmp3 == 0)
        ;     collision = collisionMap0[coordinates];
        ; else
        ;     collision = collisionMap1[coordinates];
        ; return is_solid[collision];
    LDA	#(<collMap0)
    STA	ptr1
    LDA	_temp_y     ;
    CMP #$F0        ;	if(temp_y >= 0xf0) return 0;
    BCS Return0	    ;__
    AND	#$F0        ;	temp_y & 0xF0
    STA	tmp1        ;__
	LDA	_temp_x		;
	LSR				;
	LSR				;	temp_x >> 4
	LSR				;
	LSR				;__
	ORA	tmp1		;	coordinates = (temp_x >> 4) + ((temp_y) & 0xf0);
	TAY				;__

	LDA	_temp_room	;	tmp3 = temp_room&1;
	AND	#$01		;__
	ORA	#(>collMap2);
    STA	ptr1+1      ;
	LDA	(ptr1),Y	; collision = collisionMap0[coordinates];
	STA	_collision	;__
    TAY             ;
	LDA	_is_solid,Y	;	return is_solid[collision];
	RTS				;__

	Return0:
	LDA	#$00
	RTS

.endproc

.export _playPCM
.proc _playPCM
PCM_ptr = _tmp6
    ; select PCM
	tay
    sta tmp1
	ldx Bank,y

    ;enable DMC but disable DPCM
    lda #%00000000
    sta $4010
    lda #%00001011
    sta $4015
    lda #0
    sta $4013
    lda #%00011011
    sta $4015
    ; mute sqs+noi
    lda #$30
    sta $400c
    lda #%00110000
    sta $4000
    sta $4004
    ;init pcm
	; lda #<GeometryDashPCM
	; sta PCM_ptr
	; ldx #<.bank(GeometryDashPCM)
 	ldy #0

    ;play pcm
@RestartPtr:
    lda #>$a000
    sta PCM_ptr+1
@LoadBank:
    txa
    jsr mmc3_tmp_prg_bank_1
    inx
@LoadSample:
    lda tmp1
    beq	@noburn
    jsr BurnCycles
    jsr BurnCycles
    jsr BurnCycles
    jsr BurnCycles
    jsr BurnCycles
    jsr BurnCycles
    jsr BurnCycles
@noburn:
    php
    plp
    lda #00
    lda #00
    lda #00
    lda #00
    lda #00
	
    lda (PCM_ptr),y
    beq @DoneWithPCM
    sta $4011
    iny
    bne @LoadSample
    inc PCM_ptr+1
    lda PCM_ptr+1
    cmp #>($a000+$2000)
    bcc @LoadSample
    jmp @RestartPtr
@DoneWithPCM:
    jsr _mmc3_pop_prg_bank_1
    lda #%00011111
    sta $4015
    rts

BurnCycles:
    php
    plp
    php
    plp
    rts

Bank:
    .byte <.bank(GeometryDashPCMA)
    .byte <.bank(GeometryDashPCMB)
.endproc

.popseg