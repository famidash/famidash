#pragma code-name(push, "XCD_BANK_02")
#pragma data-name(push, "XCD_BANK_02")
#pragma rodata-name(push, "XCD_BANK_02")


void do_the_scroll_thing(){
	if (currplayer_x > 0x5000){ // change x scroll
		tmp1 = MSB(currplayer_x - 0x5000);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(currplayer_x) = high_byte(currplayer_x) - tmp1;
	}
	else if (currplayer_x < 0x0200){ // change x scroll
		tmp1 = MSB(currplayer_x + 0x0200);
		scroll_x = scroll_x - tmp1;
		if (tmp1) {
			if (tmp1 > parallax_scroll_x) {	// sorta yoda notation
				parallax_scroll_x += 144;
			}
			parallax_scroll_x -= tmp1 - 1;
		}
		high_byte(currplayer_x) = high_byte(currplayer_x) + tmp1;
	}
	if (gamemode != 5) {
		if (!dual) {
			if (currplayer_y < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
				tmp1 = MSB(0x4000 - currplayer_y);
				scroll_y -= tmp1;
				high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
			}
			while (scroll_y < 0x08) {
				++scroll_y;
				--high_byte(currplayer_y);
			}

			
			if (currplayer_y > 0xA000){ // change y scroll (upward)
				tmp1 = MSB(currplayer_y - 0xA000);
				scroll_y += tmp1;
				if (scroll_y <= 0xEF) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
			}
			if (scroll_y > 0xEF) scroll_y = 0xEF;
		}
		else {
			if (currplayer_y < 0x0700 && (scroll_y > 0x08)){ // change y scroll (upward)
				tmp1 = MSB(0x0700 - currplayer_y);
				scroll_y -= tmp1;
				high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
			}
			while (scroll_y < 0x08) {
				++scroll_y;
				--high_byte(currplayer_y);
			}

			
			if (currplayer_y > 0xF000){ // change y scroll (upward)
				tmp1 = MSB(currplayer_y - 0xF000);
				scroll_y += tmp1;
				if (scroll_y <= 0xEF) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
			}
			if (scroll_y > 0xEF) scroll_y = 0xEF;
		}

	}
/*
	else {			//ship stuff
			if (target_scroll_y > 0x0120) {
				target_scroll_y--;
				target_scroll_y--;
				++scroll_y; --high_byte(currplayer_y);
				++scroll_y; --high_byte(currplayer_y);
			}
			if (target_scroll_y < 0x110) {
				target_scroll_y++;
				target_scroll_y++;
				--scroll_y; ++high_byte(currplayer_y);
				--scroll_y; ++high_byte(currplayer_y);
			}
			while (scroll_y < 0x08) {
				++scroll_y;
				--high_byte(currplayer_y);
			}
			while (scroll_y > 0xEF) {
				--scroll_y;
				++high_byte(currplayer_y);
			}


	}
*/
    set_scroll_x(scroll_x);
    set_scroll_y(scroll_y);
}
void do_the_scroll_thing2(){

    
	if (currplayer_x > 0x5000){ // change x scroll
		tmp1 = MSB(currplayer_x - 0x5000);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(currplayer_x) = high_byte(currplayer_x) - tmp1;
	}


	if (!dual) {
		if (currplayer_y < 0x4000 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x4000 - currplayer_y);
			scroll_y -= tmp1;
			high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(currplayer_y);
		}

		
		if (currplayer_y > 0xA000){ // change y scroll (upward)
			tmp1 = MSB(currplayer_y - 0xA000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}
	else {
		if (currplayer_y < 0x0700 && (scroll_y > 0x08)){ // change y scroll (upward)
			tmp1 = MSB(0x0700 - currplayer_y);
			scroll_y -= tmp1;
			high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
		}
		while (scroll_y < 0x08) {
			++scroll_y;
			--high_byte(currplayer_y);
		}

		
		if (currplayer_y > 0xF000){ // change y scroll (upward)
			tmp1 = MSB(currplayer_y - 0xF000);
			scroll_y += tmp1;
			if (scroll_y <= 0xEF) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
		}
		if (scroll_y > 0xEF) scroll_y = 0xEF;
	}


    set_scroll_x(scroll_x);
 //   set_scroll_y(scroll_y);

}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
