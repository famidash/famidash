.include "metadata_macro.inc"

RIFFChunkStart "auth"
.asciiz "Famidash"
.asciiz "Originals by 9 people, covers by 7 people"
.byte $C0, $A9
.asciiz " TFDSoft 2023-2024, [include more shit about OG composers here]"
.asciiz "alexmush"

RIFFChunkStart "plst"
.byte song_menu_theme, song_stereo_madness, song_back_on_track, song_polargeist
.byte song_dry_out, song_base_after_base, song_cant_let_go, song_jumper
.byte song_time_machine, song_cycles, song_xstep, song_clutterfunk
.byte song_theory_of_everything, song_electroman_adventures, song_custom_endgame, song_practice

.repeat sfx_max+2, n
.byte song_max+n
.endrepeat


RIFFChunkStart "psfx"
.repeat sfx_max+2, n
.byte song_max+n
.endrepeat

RIFFChunkStart "tlbl"
.asciiz "Time Machine"
.asciiz "Clutterfunk"
.asciiz "Decode ~ Endgame"
.asciiz "Practice ~ Stay Inside Me"
.asciiz "Menu Theme"
.asciiz "Polargeist"
.asciiz "Jumper"
.asciiz "Electroman Adventures"
.asciiz "Stereo Madness"
.asciiz "Back On Track"
.asciiz "Base After Base"
.asciiz "Cycles"
.asciiz "Dry Out"
.asciiz "Cant Let Go ~ Can't Let Go"
.asciiz "xStep"
.asciiz "Theory Of Everything"

.asciiz "Death SFX"
.asciiz "Click SFX"
.asciiz "LEVEL COMPLETE! SFX"
.asciiz "Coin SFX"
.asciiz "Chest Open SFX"
.asciiz "Orbs SFX"
.asciiz "Diamonds SFX"
.asciiz "Exit Level SFX"
.asciiz "Start Level SFX"
.asciiz "Invalid SFX"
.asciiz "Achievement Get SFX"

.asciiz "Geometry Dash Voice Clip"
.asciiz "FIRE IN THE HOLE! Voice Clip"

RIFFChunkStart "taut"
AutMeta "Waterflame", "Zenith302, Vikrinox, alexmush"
AutMeta "Waterflame", "Zenith302, aquamarine.gay, Vikrinox"
AutMeta "Waterflame", "Vikrinox"
AutMeta "OcularNebula", "UserSniper"
AutMeta "RobTop", "Zenith302"
AutMeta "Step", "UserSniper, Zenith302, Vikrinox"
AutMeta "Waterflame", "zukinnyk, UserSniper, Zenith302"
AutMeta "Waterflame", "UserSniper, alexmush"
AutMeta "ForeverBound", "Zenith302, UserSniper"
AutMeta "DJVI", "aquamarine.gay"
AutMeta "DJVI", "Zenith302, UserSniper, Vikrinox, alexmush"
AutMeta "DJVI", "aquamarine.gay, alexmush"
AutMeta "DJVI", "UserSniper"
AutMeta "DJVI", "UserSniper, alexmush"
AutMeta "DJVI", "Vikrinox, alexmush"
AutMeta "Dj-Nate", "leejh20, UserSniper, Vikrinox, Zenith302"

.repeat sfx_max
.asciiz "UserSniper"
.endrepeat

.asciiz "VA: MDK"
.asciiz "VA: Joe"

; TODO: PAL Timings, by flag
RIFFChunkStart "time"
.dword 96369+500, 96702+500, 78862+500, (239817*2)
.dword (29954*2), 90877+500, 86584+500, 88115+500
.dword 85852+500, 82707+500, 84986+500, 85585+500
.dword 81409+500, 80710+500, 82041+500, 88697+500

.dword 1000, 1000, 4000, 1000
.dword 1000, 1000, 1000, 1000
.dword 1000, 1000, 1000

.dword 2000, 2000

RIFFChunkStart "fade"
.dword 0, 0, 0, $FFFFFFFF
.dword $FFFFFFFF, 0, 0, 0
.dword 0, 0, 0, 0
.dword 0, 0, 0, 0

.repeat sfx_max+2
.dword 0
.endrepeat

EndNSFERIFFList