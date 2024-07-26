
.ifndef __METATILE_P_INC
__METATILE_P_INC = 1

.ifndef _PRINT_METATILES
.define _PRINT_METATILES 0
.endif

.global metatiles_top_left
.global metatiles_top_right
.global metatiles_bot_left
.global metatiles_bot_right
.global metatiles_attr
.global metatiles_coll


METATILES_COUNT .set 0

PAL_0 = (0)
PAL_1 = (1)
PAL_2 = (2)
PAL_3 = (3)


COL_UP_BOTH_SPIKES = $32
COL_UP_RIGHT_SPIKE = $31
COL_UP_LEFT_SPIKE = $30
COL_BOTTOM_SPIKES = $2f
COL_BOTTOM_RIGHT_SPIKE = $2e
COL_BOTTOM_LEFT_SPIKE = $2d
COL_RIGHT_SPIKE_BLOCK = $2c
COL_LEFT_SPIKE_BLOCK = $2b
COL_DOWN_BOTH_SPIKES = $2a
COL_DOWN_RIGHT_SPIKE = $29
COL_DOWN_LEFT_SPIKE = $28

COL_TOP_RIGHT_BOTTOM_LEFT = $27
COL_TOP_LEFT_BOTTOM_RIGHT = $26
COL_RIGHT = $25
COL_LEFT = $24
COL_DOWN_RIGHT = $23
COL_DOWN_LEFT = $22
COL_UP_RIGHT = $21
COL_UP_LEFT = $20

COL_SLOPE_LU45 = $16
COL_SLOPE_RU45 = $15
COL_SLOPE_LD66_BOT = $14
COL_SLOPE_RD66_BOT = $13
COL_SLOPE_LD66_TOP = $12
COL_SLOPE_RD66_TOP = $11
COL_SLOPE_LD22_BOT = $10
COL_SLOPE_RD22_BOT = $0f
COL_SLOPE_LD22_TOP = $0e
COL_SLOPE_RD22_TOP = $0d
COL_SLOPE_LD45 = $0c
COL_SLOPE_RD45 = $0b

COL_SLOPE_SUPPORT = $0a

COL_FLOOR_CEIL = $09
COL_DEATH = $08
COL_ALL   = $07
COL_BOTTOM   = $06
COL_TOP   = $05
COL_DEATH_BOTTOM   = $04
COL_DEATH_TOP   = $03
COL_DEATH_LEFT   = $02
COL_DEATH_RIGHT   = $01
COL_NONE  = 0


.macro MetatileReserve name
.ident( .sprintf("METATILE_%s", name) ) = METATILES_COUNT
METATILES_COUNT .set METATILES_COUNT + 1
.endmacro

.macro Metatile name, tl, tr, bl, br, at, cl

.ident(.sprintf("METATILE_%d_TL", (METATILES_COUNT))) = (<tl)
.ident(.sprintf("METATILE_%d_TR", (METATILES_COUNT))) = (<tr)
.ident(.sprintf("METATILE_%d_BL", (METATILES_COUNT))) = (<bl)
.ident(.sprintf("METATILE_%d_BR", (METATILES_COUNT))) = (<br)
.ident(.sprintf("METATILE_%d_AT", (METATILES_COUNT))) = (<at)
.ident(.sprintf("METATILE_%d_CL", (METATILES_COUNT))) = (<cl)

.if _PRINT_METATILES
	.out .sprintf("METATILE_%s = $%02x", name, METATILES_COUNT)
.endif
MetatileReserve .sprintf("%s", name)

.endmacro

.endif