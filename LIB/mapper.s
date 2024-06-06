;
; MMC3 Mapper registers, for use with the functions below
; 
.define MMC3_REG_BANK_SELECT $8000
.define MMC3_REG_BANK_DATA $8001
MMC3_REG_MIRRORING = $a000
.define MMC3_REG_PRG_RAM_PROTECT $a001
.define MMC3_REG_IRQ_LATCH $c000
.define MMC3_REG_IRQ_RELOAD $c001
.define MMC3_REG_IRQ_DISABLE $e000
.define MMC3_REG_IRQ_ENABLE $e001

; .define MMC3_MIRRORING_VERTICAL 0
; .define MMC3_MIRRORING_HORIZONTAL 1
; _MMC3_MIRRORING_VERTICAL = 0
; _MMC3_MIRRORING_HORIZONTAL = 1
; .export _MMC3_MIRRORING_VERTICAL, _MMC3_MIRRORING_HORIZONTAL, MMC3_REG_MIRRORING

.define MMC3_REG_SEL_2KB_CHR_0 %00000000
.define MMC3_REG_SEL_2KB_CHR_1 %00000001 
.define MMC3_REG_SEL_1KB_CHR_0 %00000010
.define MMC3_REG_SEL_1KB_CHR_1 %00000011
.define MMC3_REG_SEL_1KB_CHR_2 %00000100 
.define MMC3_REG_SEL_1KB_CHR_3 %00000101
.define MMC3_REG_SEL_PRG_BANK_0 %00000110
.define MMC3_REG_SEL_PRG_BANK_1 %00000111

.define MMC3_REG_SEL_CHR_MODE_A %00000000
.define MMC3_REG_SEL_CHR_MODE_B %10000000
.define MMC3_REG_SEL_PRG2_C000 %00000000
.define MMC3_REG_SEL_PRG2_8000 %01000000

.import DMC_BANK

; Values for which banks to load
.define MMC3_REG_CONTROL_DEFAULT #%11100

.segment "ZEROPAGE"
    ; Used to track whether a register write was interrupted, so we can try again if needed.
    ; alexmush comment:
    ; not anymore, just used for the PRG mode
    mmc3ChrInversionSetting: .res 1
.segment "BSS"
    mmc3PRG1Bank: .res 1    ;because famistudio updates

.segment "CODE_2"
    _mmc3_pop_prg_bank_1:
        LDA #MMC3_REG_SEL_PRG_BANK_1
        ora mmc3ChrInversionSetting
        sta MMC3_REG_BANK_SELECT
        LDA mmc3PRG1Bank
        STA MMC3_REG_BANK_DATA
        rts
    .export _mmc3_pop_prg_bank_1
    mmc3_set_prg_bank_1:
    _mmc3_set_prg_bank_1:
        STA mmc3PRG1Bank
    mmc3_tmp_prg_bank_1:    ; ONLY MEANT FOR USE WITH NMI-RELATED TEMPORARY BANKSWITCHING
        PHA
        lda #MMC3_REG_SEL_PRG_BANK_1
    mmc3_internal_set_bank:
        ora mmc3ChrInversionSetting
        sta MMC3_REG_BANK_SELECT
        PLA
        sta MMC3_REG_BANK_DATA
        rts
    .export _mmc3_set_prg_bank_1

    ; Store mirroring value to mmc3 register
    mmc3_set_prg_bank_0:
    _mmc3_set_prg_bank_0:
        PHA
        lda #MMC3_REG_SEL_PRG_BANK_0
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_prg_bank_0

    mmc3_set_2kb_chr_bank_0:
    _mmc3_set_2kb_chr_bank_0:
        PHA
        lda #MMC3_REG_SEL_2KB_CHR_0
        BEQ mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_2kb_chr_bank_0

    mmc3_set_2kb_chr_bank_1:
    _mmc3_set_2kb_chr_bank_1:
        PHA
        lda #MMC3_REG_SEL_2KB_CHR_1
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_2kb_chr_bank_1

    mmc3_set_1kb_chr_bank_0:
    _mmc3_set_1kb_chr_bank_0:
        PHA
        lda #MMC3_REG_SEL_1KB_CHR_0
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_1kb_chr_bank_0

    mmc3_set_1kb_chr_bank_1:
    _mmc3_set_1kb_chr_bank_1:
        PHA
        lda #MMC3_REG_SEL_1KB_CHR_1
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_1kb_chr_bank_1

    mmc3_set_1kb_chr_bank_2:
    _mmc3_set_1kb_chr_bank_2:
        PHA
        lda #MMC3_REG_SEL_1KB_CHR_2
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_1kb_chr_bank_2

    mmc3_set_1kb_chr_bank_3:
    _mmc3_set_1kb_chr_bank_3:
        PHA
        lda #MMC3_REG_SEL_1KB_CHR_3
        BNE mmc3_internal_set_bank  ; BRA
    .export _mmc3_set_1kb_chr_bank_3

    .macro mmc3_set_mirroring
        sta MMC3_REG_MIRRORING
    .endmacro

    initialize_mapper:
        ; lda #(MMC3_REG_SEL_CHR_MODE_A | MMC3_REG_SEL_PRG2_8000)
        lda #(MMC3_REG_SEL_CHR_MODE_B | MMC3_REG_SEL_PRG2_8000)
        sta mmc3ChrInversionSetting

        lda #%10000000
        sta MMC3_REG_PRG_RAM_PROTECT

        lda #<DMC_BANK          ; Sample bank
        jsr mmc3_set_prg_bank_0
        lda #1
        sta MMC3_REG_MIRRORING  ; Set mirroring to horizontal
        jmp mmc3_set_prg_bank_1
