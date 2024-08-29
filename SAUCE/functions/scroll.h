#pragma code-name(push, "XCD_BANK_02")
#pragma data-name(push, "XCD_BANK_02")
#pragma rodata-name(push, "XCD_BANK_02")

extern unsigned short min_scroll_y;

// TODO: compensated increments

void do_the_scroll_thing(){
	if (high_byte(currplayer_x) > MSB(0x5000)){ // change x scroll
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


	
	
	
	
//	if (gamemode != 5) {
		if (!dual) {
			if (currplayer_y < 0x4000 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
				tmp1 = MSB(0x4000 - currplayer_y);
				scroll_y -= tmp1;
				high_byte(currplayer_y) = high_byte(currplayer_y) + tmp1;
			}
			while (scroll_y < min_scroll_y) {
				++scroll_y;
				--high_byte(currplayer_y);
			}

			
			if (high_byte(currplayer_y) >= MSB(0xA000)){ // change y scroll (upward)
				tmp1 = MSB(currplayer_y - 0xA000);
				scroll_y = add_scroll_y(tmp1, scroll_y);
				if (high_byte(scroll_y) < MSB(0x300)) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
			}
			if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
		}
		else {
			if (currplayer_y < 0x0700 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
				tmp1 = MSB(0x0700 - currplayer_y);
				scroll_y = sub_scroll_y(tmp1, scroll_y);
				high_byte(currplayer_y) += tmp1;
			}
			while (scroll_y < min_scroll_y) {
				++scroll_y;
				--high_byte(currplayer_y);
			}

			
			if (high_byte(currplayer_y) >= MSB(0xF000)){ // change y scroll (upward)
				tmp1 = MSB(currplayer_y - 0xF000);
				scroll_y = add_scroll_y(tmp1, scroll_y);
				if (high_byte(scroll_y) < MSB(0x300)) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
			}
			if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
		}

//	}
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

    
	if (currplayer_x > curr_x_scroll_stop){ // change x scroll
		tmp1 = MSB(currplayer_x - curr_x_scroll_stop);
		scroll_x += tmp1;
		parallax_scroll_x += tmp1 ? tmp1 - 1 : 0;
		if (parallax_scroll_x >= 144) {
			parallax_scroll_x -= 144;
		}
		high_byte(currplayer_x) = high_byte(currplayer_x) - tmp1;
	}


	if (!dual) {
		if (currplayer_y < 0x4000 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
			tmp1 = MSB(0x4000 - currplayer_y);
			scroll_y = sub_scroll_y(tmp1, scroll_y);
			high_byte(currplayer_y) += tmp1;
		}
		while (scroll_y < min_scroll_y) {
			++scroll_y;
			--high_byte(currplayer_y);
		}

		
		if (high_byte(currplayer_y) >= MSB(0xA000)){ // change y scroll (upward)
			tmp1 = MSB(currplayer_y - 0xA000);
			scroll_y = add_scroll_y(tmp1, scroll_y);
			if (high_byte(scroll_y) < MSB(0x300)) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
		}
		if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
	}
	else {
		// TODO: boundary according to extceil flag
		if (currplayer_y < 0x0700 && (scroll_y > min_scroll_y)){ // change y scroll (upward)
			tmp1 = MSB(0x0700 - currplayer_y);
			scroll_y = sub_scroll_y(tmp1, scroll_y);
			high_byte(currplayer_y) += tmp1;
		}
		// TODO: boundary according to extceil flag
		while (scroll_y < min_scroll_y) {
			++scroll_y;
			--high_byte(currplayer_y);
		}

		
		if (high_byte(currplayer_y) >= MSB(0xF000)){ // change y scroll (upward)
			tmp1 = MSB(currplayer_y - 0xF000);
			scroll_y = add_scroll_y(tmp1, scroll_y);
			if (high_byte(scroll_y) < MSB(0x300)) high_byte(currplayer_y) = high_byte(currplayer_y) - tmp1;
		}
		if (high_byte(scroll_y) >= MSB(0x300)) scroll_y = 0x2EF; // 2F0 overflows into 300 (add_scroll_y)
	}


    set_scroll_x(scroll_x);
 //   set_scroll_y(scroll_y);

}

#pragma code-name(pop)
#pragma data-name(pop) 
#pragma rodata-name(pop)
