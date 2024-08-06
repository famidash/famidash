sfx_death = 0
sfx_click = 1
sfx_level_complete = 2
sfx_coin = 3
sfx_orbs = 4
sfx_diamonds = 5
sfx_exit_level = 6
sfx_start_level = 7
sfx_select = 0xFF
sfx_max = 9

.if SFX_STRINGS
sfx_strings:
.asciiz "death"
.asciiz "click"
.asciiz "LEVEL COMPLETE!"
.asciiz "coin"
.asciiz "orbs"
.asciiz "diamonds"
.asciiz "exit level"
.asciiz "start level"
.asciiz "select"
.endif
