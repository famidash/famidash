void state_lvldone(){
    ppu_off();

    pal_bg((char *)paletteMenu);


    mmc3_tmp_prg_bank_1(0);
    vram_adr(NAMETABLE_A);
    vram_unrle(menunametable);

    vram_adr(NAMETABLE_C);
    vram_unrle(leveldone);
    mmc3_pop_prg_bank_1();

    vram_adr(NTADR_A(6,7));
	for(tmp1=0;menutext3[tmp1];++tmp1){
		vram_put(0xA0+menutext3[tmp1]);
	} 
    vram_adr(NTADR_A(6,9));
	for(tmp1=0;menutext4[tmp1];++tmp1){
		vram_put(0xA0+menutext4[tmp1]);
	} 


    vram_adr(NTADR_A(12,9));
    
    switch (coins) {
		case 0x00: {
			break;
		}
		case 0x01: {
			for(tmp1=0;coins1[tmp1];++tmp1){
				vram_put(0xA0+coins1[tmp1]);
			} 
			break;
		}
		case 0x02: {
			for(tmp1=0;coins2[tmp1];++tmp1){
				vram_put(0xA0+coins2[tmp1]);
			} 
			break;
		}
		case 0x03: {
			for(tmp1=0;coins3[tmp1];++tmp1){
				vram_put(0xA0+coins3[tmp1]);
			} 
			break;
		}
		default: break;
         } 


//	one_vram_buffer(0xD0+coins, NTADR_A(12,9));


    scroll_y = 0xEF;
    set_scroll_x(0);
    set_scroll_y(scroll_y);

	mmc3_set_8kb_chr(12);

    

    ppu_on_all();

    pal_fade_to(0, 4);


    famistudio_sfx_play(sfx_level_complete, 0);

    
    for (tmp1 = 0; tmp1 < 255; ++tmp1) {
        ppu_wait_nmi();
        music_update();
    }
    for (tmp1 = 0; tmp1 < 7; ++tmp1) {
        ppu_wait_nmi();
        ppu_wait_nmi();
	music_update();	
        scroll_y -= (0xf0 - scroll_y);
        set_scroll_y(scroll_y);
    }
    pal_col(0,0x17);
    for (tmp1 = 0; tmp1 < 8; ++tmp1) {
        ppu_wait_nmi();
        ppu_wait_nmi();
	music_update();	
        scroll_y >>= 1;
        set_scroll_y(scroll_y);

    }


	while (1){
		ppu_wait_nmi();
		music_update();
		pad = pad_poll(0); // read the first controller
		pad_new = get_pad_new(0);

		if (pad_new & PAD_START){
			pal_bg((char *)paletteDefault);
			pal_spr((char *)paletteDefaultSP);
			// use the second set of tiles for sprites
			// both bg and sprites are set to 0 by default
			bank_spr(1);

			set_vram_buffer(); // do at least once

			ppu_on_all();
			pal_fade_to(4,0);
			gameState = 1;
			return;
		}
	}


 //   pal_bg((char *)paletteDefault);
//    pal_spr((char *)paletteDefaultSP);
    // use the second set of tiles for sprites
	// both bg and sprites are set to 0 by default
//	bank_spr(1);

 //   set_vram_buffer(); // do at least once

 //   ppu_on_all();
 //   pal_fade_to(4,0);
//	gameState = 1;
//	return;

    
//    while (1){
//        ppu_wait_nmi();
//        music_update();

//    }
}