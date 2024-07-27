#pragma rodata-name (push, "XCD_BANK_04")

// a 16x16 pixel metasprite

const unsigned char Heat_Ball_1[]={

	  0,  0,0x1D,3,
	0x80
};

const unsigned char Heat_Ball_2[]={

	  0,  0,0x1D,3|OAM_FLIP_H,
	0x80
};

const unsigned char Heat_Ball_3[]={

	  0,  8,0x1D,3|OAM_FLIP_V,
	0x80
};

const unsigned char Heat_Ball_4[]={

	  0,  8,0x1D,3|OAM_FLIP_V|OAM_FLIP_H,
	0x80
};

const unsigned char * const Heat_Ball_Sprites[] = {Heat_Ball_1,Heat_Ball_1,Heat_Ball_1,Heat_Ball_1,Heat_Ball_1,Heat_Ball_2,Heat_Ball_2,Heat_Ball_2,Heat_Ball_2,Heat_Ball_2,Heat_Ball_3,Heat_Ball_3,Heat_Ball_3,Heat_Ball_3,Heat_Ball_3,Heat_Ball_4,Heat_Ball_4,Heat_Ball_4,Heat_Ball_4,Heat_Ball_4};




const unsigned char Explode_1[]={

	  0,  0,0x1D,3,
	  8,  0,0x1D,3|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Explode_2[]={

	  0,  0,0xFB,3,
	  8,  0,0xFB,3|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Explode_3[]={

	  0,  0,0x1F,3,
	  8,  0,0x1F,3|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Explode_4[]={

	  0,  0,0xFD,3,
	  8,  0,0xFD,3|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Explode_5[]={

	  0,  0,0xFF,3,
	  8,  0,0xFF,3|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char * const Explode_Sprites[] = {Explode_1,Explode_1,Explode_1,Explode_1,Explode_2,Explode_2,Explode_2,Explode_2,Explode_3,Explode_3,Explode_3,Explode_3,Explode_4,Explode_4,Explode_4,Explode_4,Explode_5,Explode_5,Explode_5,Explode_5};

const unsigned char ExplodeR_1[]={

	  0,  0,0x1F,3|OAM_FLIP_H,
	  8,  0,0x1F,3,
	0x80
};
const unsigned char * const ExplodeR_Sprites[] = {ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1,ExplodeR_1};


const unsigned char Explode2_1[]={

	  0,  0,0x1D,1,
	  8,  0,0x1D,1|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Explode2_2[]={

	  0,  0,0xFB,1,
	  8,  0,0xFB,1|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Explode2_3[]={

	  0,  0,0x1F,1,
	  8,  0,0x1F,1|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Explode2_4[]={

	  0,  0,0xFD,1,
	  8,  0,0xFD,1|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Explode2_5[]={

	  0,  0,0xFF,1,
	  8,  0,0xFF,1|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char * const Explode_Sprites2[] = {Explode2_1,Explode2_1,Explode2_1,Explode2_1,Explode2_2,Explode2_2,Explode2_2,Explode2_2,Explode2_3,Explode2_3,Explode2_3,Explode2_3,Explode2_4,Explode2_4,Explode2_4,Explode2_4,Explode2_5,Explode2_5,Explode2_5,Explode2_5};

const unsigned char ExplodeR2_1[]={

	  0,  0,0x1D,1,
	  8,  0,0x1F,1,
	0x80
};
const unsigned char * const ExplodeR_Sprites2[] = {ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1,ExplodeR2_1};

const unsigned char Practice_Diamond[]={

	  0,  0,0x57,0,
	0x80
};

const unsigned char * const Practice_Sprites[] = {Practice_Diamond};

const unsigned char Trail_Circ[]={

	  0,  -4,0xF9,3,
	0x80
};

// const unsigned char * const Trail_Circle[] = {Trail_Circ};

const unsigned char Mini_Cube_0[]={

	-4,  -5,0x35,3,
	0x80
};
	
const unsigned char Mini_Cube_1[]={

	-4,  -5,0x37,3,
	0x80
};
	
const unsigned char Mini_Cube_2[]={

	-4,  -5,0x39,3,
	0x80
};

const unsigned char Mini_Cube_3[]={

	-4,  -5,0x3B,3,
	0x80
};//Full 360 mini frames need to be added here - Ficus
	
	
const unsigned char * const MINI_CUBE[] = {Mini_Cube_0, Mini_Cube_1, Mini_Cube_1, Mini_Cube_2, Mini_Cube_2, Mini_Cube_3, Mini_Cube_0, Mini_Cube_0};

const unsigned char Mini_Cube2_0[]={

	-4,  -5,0x35,1,
	0x80
};
	
const unsigned char Mini_Cube2_1[]={

	-4,  -5,0x37,1,
	0x80
};
	
const unsigned char Mini_Cube2_2[]={

	-4,  -5,0x39,1,
	0x80
};

const unsigned char Mini_Cube2_3[]={

	-4,  -5,0x3B,1,
	0x80
};//Full 360 mini frames need to be added here too - Ficus
	
	
const unsigned char * const MINI_CUBE2[] = {Mini_Cube2_0, Mini_Cube2_1, Mini_Cube2_1, Mini_Cube2_2, Mini_Cube2_2, Mini_Cube2_3, Mini_Cube2_0, Mini_Cube2_0};


const unsigned char Mini_Ball[]={

	 -4,  4,0x0B,3|OAM_FLIP_V,
	0x80
};

const unsigned char * const MINI_BALL[]={Mini_Ball, Mini_Ball, Mini_Ball, Mini_Ball, Mini_Ball, Mini_Ball, Mini_Ball, Mini_Ball};
	
const unsigned char WAVE_0[]={//DOWN

	 -8,  0,0x3B,3,
	  0,  0,0x3D,3,
	0x80
};		

const unsigned char WAVE_1[]={//SLIGHT DOWN

	 -8,  0,0x37,3,
	  0,  0,0x39,3,
	0x80
};	
const unsigned char WAVE_2[]={//FLAT

	 -8,  0,0x17,3,
	  0,  0,0x19,3,
	0x80
};	
const unsigned char WAVE_5[]={//SLIGHT UP

	 -8,  0,0x37,3|OAM_FLIP_V,
	  0,  0,0x39,3|OAM_FLIP_V,
	0x80
};	

const unsigned char WAVE_6[]={//UP

	 -8,  0,0x3B,3|OAM_FLIP_V,
	  0,  0,0x3D,3|OAM_FLIP_V,
	0x80
};		



const unsigned char * const WAVE[] = {WAVE_0, WAVE_0, WAVE_1, WAVE_2, WAVE_2, WAVE_5, WAVE_6, WAVE_6};

const unsigned char WAVE2_0[]={//DOWN

	 -8,  0,0x3B,1,
	  0,  0,0x3D,1,
	0x80
};		

const unsigned char WAVE2_1[]={//SLIGHT DOWN

	 -8,  0,0x37,1,
	  0,  0,0x39,1,
	0x80
};	
const unsigned char WAVE2_2[]={//FLAT

	 -8,  0,0x17,1,
	  0,  0,0x19,1,
	0x80
};		
	
const unsigned char WAVE2_5[]={//SLIGHT UP

	 -8,  0,0x37,1|OAM_FLIP_V,
	  0,  0,0x39,1|OAM_FLIP_V,
	0x80
};	

const unsigned char WAVE2_6[]={//UP

	 -8,  0,0x3B,1|OAM_FLIP_V,
	  0,  0,0x3D,1|OAM_FLIP_V,
	0x80
};		



const unsigned char * const WAVE2[] = {WAVE2_0, WAVE2_0, WAVE2_1, WAVE2_2, WAVE2_2, WAVE2_5, WAVE2_6, WAVE2_6};

const unsigned char MINI_WAVE_0[]={

	 -4,  -6,0x11,3|OAM_FLIP_V,
	0x80
};
const unsigned char MINI_WAVE_2[]={

	 -4,  -6,0x0D,3,
	0x80
};
const unsigned char MINI_WAVE_6[]={

	 -4,  -6,0x11,3,
	0x80
};



const unsigned char * const MINI_WAVE[] = {MINI_WAVE_0, MINI_WAVE_0, MINI_WAVE_0, MINI_WAVE_2, MINI_WAVE_2, MINI_WAVE_6, MINI_WAVE_6, MINI_WAVE_6};



const unsigned char MINI_WAVE2_0[]={

	 -4,  -6,0x11,1|OAM_FLIP_V,
	0x80
};
const unsigned char MINI_WAVE2_2[]={

	 -4,  -6,0x0D,1,
	0x80
};
const unsigned char MINI_WAVE2_6[]={

	 -4,  -6,0x11,1,
	0x80
};


const unsigned char * const MINI_WAVE2[] = {MINI_WAVE2_0, MINI_WAVE2_0, MINI_WAVE2_0, MINI_WAVE2_2, MINI_WAVE2_2, MINI_WAVE2_6, MINI_WAVE2_6, MINI_WAVE2_6};


const unsigned char UFO_0[]={

	 -8,  -1,0x3F,3,
	  0,  -1,0x3F,3|OAM_FLIP_H,
	0x80
};	

const unsigned char UFO_U[]={//IDENTICAL TO 0 - Ficus

	 -8,  -1,0x3F,3,
	  0,  -1,0x3F,3|OAM_FLIP_H,
	0x80
};	

const unsigned char UFO_D[]={//IDENTICAL TO 0 - Ficus

	 -8,  -1,0x3F,3,
	  0,  -1,0x3F,3|OAM_FLIP_H,
	0x80
};	



const unsigned char * const UFO[] = {UFO_0, UFO_U, UFO_D};
	
const unsigned char MINI_UFO_0[]={

	 -4,  -5,0x19,3,
	0x80
};		
const unsigned char MINI_UFO_U[]={

	 -4,  -5,0x19,3,
	0x80
};		
const unsigned char MINI_UFO_D[]={

	 -4,  -5,0x19,3,
	0x80
};	

const unsigned char * const MINI_UFO[] = {MINI_UFO_0, MINI_UFO_U, MINI_UFO_D};

const unsigned char Mini_Ball2[]={

	 -4,  4,0x0B,1|OAM_FLIP_V,
	0x80
};

const unsigned char * const MINI_BALL2[]={Mini_Ball2, Mini_Ball2, Mini_Ball2, Mini_Ball2, Mini_Ball2, Mini_Ball2, Mini_Ball2, Mini_Ball2};
	
const unsigned char UFO2_0[]={

	 -8,  -1,0x3F,1,
	  0,  -1,0x3F,1|OAM_FLIP_H,
	0x80
};	

const unsigned char UFO2_U[]={//IDENTICAL TO 0 - Ficus

	 -8,  -1,0x3F,1,
	  0,  -1,0x3F,1|OAM_FLIP_H,
	0x80
};	

const unsigned char UFO2_D[]={//IDENTICAL TO 0 - Ficus

	 -8,  -1,0x3F,1,
	  0,  -1,0x3F,1|OAM_FLIP_H,
	0x80
};	



const unsigned char * const UFO2[] = {UFO2_0, UFO2_U, UFO2_D};
	
const unsigned char MINI_UFO2_0[]={

	 -4,  -5,0x19,1,
	0x80
};		
const unsigned char MINI_UFO2_U[]={

	 -4,  -5,0x19,1|OAM_FLIP_H,
	0x80
};		
const unsigned char MINI_UFO2_D[]={

	 -4,  -5,0x19,1,
	0x80
};	

const unsigned char * const MINI_UFO2[] = {MINI_UFO2_0, MINI_UFO2_U, MINI_UFO2_D};
	
const unsigned char Cube_0[]={

	 -8,  0,0x01,3,
	  0,  0,0x03,3,
	0x80
};
const unsigned char Cube_1[]={

	 -8,  0,0x05,3,
	  0,  0,0x07,3,
	0x80
};
const unsigned char Cube_2[]={

	 -8,  0,0x09,3,
	  0,  0,0x0B,3,
	0x80
};
const unsigned char Cube_3[]={

	 -8,  0,0x0D,3,
	  0,  0,0x0F,3,
	0x80
};
const unsigned char Cube_4[]={

	 -8,  0,0x11,3,
	  0,  0,0x13,3,
	0x80
};
const unsigned char Cube_5[]={

	 -8,  0,0x15,3,
	  0,  0,0x17,3,
	0x80
};//360 Degree rotation stuff - Ficus

const unsigned char Cube_6[]={

     -8,  0,0x19,3,
      0,  0,0x1B,3,
    0x80
};

const unsigned char * const CUBE[] = {Cube_0, Cube_1, Cube_2, Cube_3, Cube_4, Cube_5, Cube_6, Cube_6};
// end cube
	
const unsigned char Cube2_0[]={

	 -8,  0,0x01,1,
	  0,  0,0x03,1,
	0x80
};
const unsigned char Cube2_1[]={

	 -8,  0,0x05,1,
	  0,  0,0x07,1,
	0x80
};
const unsigned char Cube2_2[]={

	 -8,  0,0x09,1,
	  0,  0,0x0B,1,
	0x80
};
const unsigned char Cube2_3[]={

	 -8,  0,0x0D,1,
	  0,  0,0x0F,1,
	0x80
};
const unsigned char Cube2_4[]={

	 -8,  0,0x11,1,
	  0,  0,0x13,1,
	0x80
};
const unsigned char Cube2_5[]={

	 -8,  0,0x15,1,
	  0,  0,0x17,1,
	0x80
};

const unsigned char Cube2_6[]={

     -8,  0,0x19,1,
      0,  0,0x1B,1,
    0x80
};


const unsigned char * const CUBE2[] = {Cube2_0, Cube2_1, Cube2_2, Cube2_3, Cube2_4, Cube2_5, Cube2_6, Cube2_6};
// end cube




// ship starts here
const unsigned char Ship_0[]={

	 -8,  0,0x21,3,
	  0,  0,0x23,3,
	0x80
};
const unsigned char Ship_1[]={

	 -8,  0,0x25,3,
	  0,  0,0x27,3,
	0x80
};
const unsigned char Ship_2[]={

	 -8,  0,0x29,3,
	  0,  0,0x2B,3,
	0x80
};

const unsigned char Ship_5[]={

	 -8,  0,0x2D,3,
	  0,  0,0x2F,3,
	0x80
};
const unsigned char Ship_6[]={

	 -8,  0,0x31,3,
	  0,  0,0x33,3,
	0x80
};


const unsigned char * const SHIP[] = {Ship_0, Ship_0, Ship_1, Ship_2, Ship_2, Ship_5, Ship_6, Ship_6};
// end ship

// swing starts here
const unsigned char Swing_0[]={

	 -8,  0,0x39,3|OAM_FLIP_V,
	  0,  0,0x3B,3|OAM_FLIP_V,
	0x80
};
const unsigned char Swing_1[]={

	 -8,  0,0x35,3|OAM_FLIP_V,
	  0,  0,0x37,3|OAM_FLIP_V,
	0x80
};
const unsigned char Swing_2[]={

	 -8,  0,0x31,3,
	  0,  0,0x33,3,
	0x80
};

const unsigned char Swing_5[]={

	 -8,  0,0x35,3,
	  0,  0,0x37,3,
	0x80
};
const unsigned char Swing_6[]={

	 -8,  0,0x39,3,
	  0,  0,0x3B,3,
	0x80
};


const unsigned char * const SWING[] = {Swing_6, Swing_0, Swing_1, Swing_2, Swing_2, Swing_5, Swing_6, Swing_0};
const unsigned char Swing2_0[]={

	 -8,  0,0x39,1,
	  0,  0,0x3B,1,
	0x80
};
const unsigned char Swing2_1[]={

	 -8,  0,0x35,1,
	  0,  0,0x37,1,
	0x80
};
const unsigned char Swing2_2[]={

	 -8,  0,0x31,1,
	  0,  0,0x33,1,
	0x80
};

const unsigned char Swing2_5[]={

	 -8,  0,0x35,1|OAM_FLIP_V,
	  0,  0,0x37,1|OAM_FLIP_V,
	0x80
};
const unsigned char Swing2_6[]={

	 -8,  0,0x39,1|OAM_FLIP_V,
	  0,  0,0x3B,1|OAM_FLIP_V,
	0x80
};


const unsigned char * const SWING2[] = {Swing2_0, Swing2_0, Swing2_1, Swing2_2, Swing2_2, Swing2_5, Swing2_6, Swing2_6};
// end swing
// mini swing
const unsigned char Mini_Swing_0[]={

	 -4,  -5,0x1B,3,
	0x80
};

const unsigned char Mini_Swing_1[]={

	 -4,  -5,0x1B,3,
	0x80
};

const unsigned char Mini_Swing_2[]={

	 -4,  -5,0x3F,3,
	0x80
};


const unsigned char Mini_Swing_5[]={

	 -4,  -5,0x3D,3,
	0x80
};

const unsigned char Mini_Swing_6[]={

	 -4,  -5,0x3D,3,
	0x80
};


const unsigned char * const MINI_SWING[] = {Mini_Swing_0, Mini_Swing_0, Mini_Swing_1, Mini_Swing_2, Mini_Swing_2, Mini_Swing_5, Mini_Swing_6, Mini_Swing_6};
const unsigned char Mini_Swing2_0[]={

	 -4,  -5,0x1B,1,
	0x80
};

const unsigned char Mini_Swing2_1[]={

	 -4,  -5,0x1B,1,
	0x80
};

const unsigned char Mini_Swing2_2[]={

	 -4,  -5,0x3F,1,
	0x80
};


const unsigned char Mini_Swing2_5[]={

	 -4,  -5,0x3D,1,
	0x80
};

const unsigned char Mini_Swing2_6[]={

	 -4,  -5,0x3D,1,
	0x80
};


const unsigned char * const MINI_SWING2[] = {Mini_Swing2_0, Mini_Swing2_0, Mini_Swing_1, Mini_Swing2_2, Mini_Swing2_2, Mini_Swing2_5, Mini_Swing2_6, Mini_Swing2_6};
// end mini swing

const unsigned char Mini_Ship_0[]={

	 -4,  -5,0x01,3,
	0x80
};

const unsigned char Mini_Ship_1[]={

	 -4,  -5,0x03,3,
	0x80
};

const unsigned char Mini_Ship_2[]={

	 -4,  -5,0x05,3,
	0x80
};


const unsigned char Mini_Ship_5[]={

	 -4,  -5,0x07,3,
	0x80
};

const unsigned char Mini_Ship_6[]={

	 -4,  -5,0x09,3,
	0x80
};


const unsigned char * const MINI_SHIP[] = {Mini_Ship_0, Mini_Ship_0, Mini_Ship_1, Mini_Ship_2, Mini_Ship_2, Mini_Ship_5, Mini_Ship_6, Mini_Ship_6};
// end mini ship



// ship starts here
const unsigned char Ship2_0[]={

	 -8,  0,0x21,1,
	  0,  0,0x23,1,
	0x80
};
const unsigned char Ship2_1[]={

	 -8,  0,0x25,1,
	  0,  0,0x27,1,
	0x80
};
const unsigned char Ship2_2[]={

	 -8,  0,0x29,1,
	  0,  0,0x2B,1,
	0x80
};

const unsigned char Ship2_5[]={

	 -8,  0,0x2D,1,
	  0,  0,0x2F,1,
	0x80
};
const unsigned char Ship2_6[]={

	 -8,  0,0x31,1,
	  0,  0,0x33,1,
	0x80
};


const unsigned char * const SHIP2[] = {Ship2_0, Ship2_0, Ship2_1, Ship2_2, Ship2_2, Ship2_5, Ship2_6, Ship2_6};
// end ship

const unsigned char Mini_Ship2_0[]={

	 -4,  -5,0x01,1,
	0x80
};

const unsigned char Mini_Ship2_1[]={

	 -4,  -5,0x03,1,
	0x80
};

const unsigned char Mini_Ship2_2[]={

	 -4,  -5,0x05,1,
	0x80
};


const unsigned char Mini_Ship2_5[]={

	 -4,  -5,0x07,1,
	0x80
};

const unsigned char Mini_Ship2_6[]={

	 -4,  -5,0x09,1,
	0x80
};


const unsigned char * const MINI_SHIP2[] = {Mini_Ship2_0, Mini_Ship2_0, Mini_Ship2_1, Mini_Ship2_2, Mini_Ship2_2, Mini_Ship2_5, Mini_Ship2_6, Mini_Ship2_6};
// end mini ship




const unsigned char COIN_SPRITE[]={

	  0,  0,0xAF,1,
	  8,  0,0xAF,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_1_SPRITE[]={

	  0,  0,0xB1,1,
	  8,  0,0xB3,1,
	0x80
};
const unsigned char COIN_2_SPRITE[]={

	  0,  0,0xB5,1,
	  8,  0,0xB5,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_3_SPRITE[]={

	  0,  0,0xB3,1|OAM_FLIP_H,
	  8,  0,0xB1,1|OAM_FLIP_H,
	0x80
};


const unsigned char COIN_SPRITE_X[]={

	  0,  0,0xC1,1,
	  8,  0,0xC1,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_1_X[]={

	  0,  0,0xC3,1,
	  8,  0,0xC5,1,
	0x80
};
const unsigned char COIN_2_X[]={

	  0,  0,0xC7,1,
	  8,  0,0xC7,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_3_X[]={

	  0,  0,0xC5,1|OAM_FLIP_H,
	  8,  0,0xC3,1|OAM_FLIP_H,
	0x80
};



const unsigned char Ball_0[]={

	 -8,  0,0x1B,3,
	  0,  0,0x1B,3|OAM_FLIP_H,
	0x80
};
const unsigned char Ball_1[]={

	 -8,  0,0x3F,3,
	  0,  0,0x3F,3|OAM_FLIP_H,
	0x80
};

const unsigned char * const BALL[]={Ball_0, Ball_0, Ball_0, Ball_0, Ball_1, Ball_1, Ball_1, Ball_1};
// ================================================================

const unsigned char Ball2_0[]={

	 -8,  0,0x1B,1,
	  0,  0,0x1B,1|OAM_FLIP_H,
	0x80
};
const unsigned char Ball2_1[]={

	 -8,  0,0x3F,1,
	  0,  0,0x3F,1|OAM_FLIP_H,
	0x80
};

const unsigned char * const BALL2[]={Ball2_0, Ball2_0, Ball2_0, Ball2_0, Ball2_1, Ball2_1, Ball2_1, Ball2_1};
// ================================================================

const unsigned char Robot_0[]={
	
	-12,   1, 0x01,3,
	 -4,   1, 0x03,3,
	  4,   1, 0x05,3,
	0x80
};

const unsigned char Robot_1[]={//Also jumping frame - Ficus
	
	-12,   1, 0xFF,3,//UNUSED - Ficus
	 -4,   1, 0x07,3,
	  4,   1, 0x09,3,
	0x80
};
const unsigned char Robot_1_Alt[]={//Also jumping frame - Ficus
	
	-12,   1, 0x07,3,//UNUSED - Ficus
	 -4,   1, 0x09,3,
	  4,   1, 0xFF,3,
	0x80
};

const unsigned char Robot_2[]={
	
	-12,   1, 0x0B,3,
	 -4,   1, 0x0D,3,
	  4,   1, 0x0F,3,
	0x80
};

const unsigned char Robot_Jump_1[]={//Did 4th walk frame here - Ficus
	
	-12,   1, 0x11,3,//No longer a jet, but the leftmost part of the sprite - Ficus
	 -4,   1, 0x13,3,
	  4,   1, 0x15,3,
	0x80
};


const unsigned char * const ROBOT[]={Robot_0, Robot_0, Robot_0, Robot_0, Robot_0, Robot_1, Robot_1, Robot_1, Robot_1, Robot_1, Robot_0, Robot_0, Robot_0, Robot_0, Robot_0, Robot_2, Robot_2, Robot_2, Robot_2, Robot_2};
const unsigned char * const ROBOT_ALT[]={Robot_0, Robot_0, Robot_0, Robot_0, Robot_0, Robot_1_Alt, Robot_1_Alt, Robot_1_Alt, Robot_1_Alt, Robot_1_Alt, Robot_0, Robot_0, Robot_0, Robot_0, Robot_0, Robot_2, Robot_2, Robot_2, Robot_2, Robot_2};
const unsigned char * const ROBOT_JUMP[]={Robot_Jump_1, Robot_Jump_1, Robot_Jump_1, Robot_Jump_1, Robot_Jump_1};


const unsigned char Mini_Robot_0[]={
	
	-4,   -5, 0x13,3,
	0x80
};

const unsigned char Mini_Robot_1[]={
	
	-4,   -5, 0x15,3,
	0x80
};

const unsigned char Mini_Robot_2[]={
	
	-4,   -5, 0x17,3,
	0x80
};

const unsigned char Mini_Robot_Jump_1[]={
	
	-4,   -5, 0x15,3,
	0x80
};//also mini robot 3rd animation frame - Ficus

const unsigned char * const MINI_ROBOT[]={Mini_Robot_0, Mini_Robot_0, Mini_Robot_0, Mini_Robot_0, Mini_Robot_0, Mini_Robot_1, Mini_Robot_1, Mini_Robot_1, Mini_Robot_1, Mini_Robot_1, Mini_Robot_0, Mini_Robot_0, Mini_Robot_0, Mini_Robot_0, Mini_Robot_0, Mini_Robot_2, Mini_Robot_2, Mini_Robot_2, Mini_Robot_2, Mini_Robot_2};
const unsigned char * const MINI_ROBOT_JUMP[]={Mini_Robot_Jump_1, Mini_Robot_Jump_1, Mini_Robot_Jump_1, Mini_Robot_Jump_1, Mini_Robot_Jump_1};
// ================================================================
const unsigned char Mini_Robot_ALT_0[]={
	
	-4,   -5, 0x35,3,
	0x80
};

const unsigned char Mini_Robot_ALT_1[]={
	
	-4,   -5, 0x37,3,
	0x80
};

const unsigned char Mini_Robot_ALT_2[]={
	
	-4,   -5, 0x39,3,
	0x80
};

const unsigned char Mini_Robot_Jump_ALT_1[]={
	
	-4,   -5, 0x3D,3,
	0x80
};//also mini robot 3rd animation frame - Ficus

const unsigned char * const MINI_ROBOT_ALT[]={Mini_Robot_ALT_0, Mini_Robot_ALT_0, Mini_Robot_ALT_0, Mini_Robot_ALT_0, Mini_Robot_ALT_0, Mini_Robot_ALT_1, Mini_Robot_ALT_1, Mini_Robot_ALT_1, Mini_Robot_ALT_1, Mini_Robot_ALT_1, Mini_Robot_ALT_0, Mini_Robot_ALT_0, Mini_Robot_ALT_0, Mini_Robot_ALT_0, Mini_Robot_ALT_0, Mini_Robot_ALT_2, Mini_Robot_ALT_2, Mini_Robot_ALT_2, Mini_Robot_ALT_2, Mini_Robot_ALT_2};
const unsigned char * const MINI_ROBOT_JUMP_ALT[]={Mini_Robot_Jump_ALT_1, Mini_Robot_Jump_ALT_1, Mini_Robot_Jump_ALT_1, Mini_Robot_Jump_ALT_1, Mini_Robot_Jump_ALT_1};
// ================================================================

const unsigned char Robot2_0[]={
	
	-12,   1, 0x01,1,
	 -4,   1, 0x03,1,
	  4,   1, 0x05,1,
	0x80
};

const unsigned char Robot2_1[]={
	
	-12,   1, 0xFF,1,//UNUSED - Ficus
	 -4,   1, 0x07,1,
	  4,   1, 0x09,1,
	0x80
};

const unsigned char Robot2_2[]={
	
	-12,   1, 0x0B,1,
	 -4,   1, 0x0D,1,
	  4,   1, 0x0F,1,
	0x80
};

const unsigned char Robot_Jump2_1[]={
	
	-8,   1, 0x11,1|OAM_FLIP_V,
	-4,   1, 0x13,1,
	 4,   1, 0x15,1,
	0x80
};

const unsigned char * const ROBOT2[]={Robot2_0, Robot2_0, Robot2_0, Robot2_0, Robot2_0, Robot2_1, Robot2_1, Robot2_1, Robot2_1, Robot2_1, Robot2_0, Robot2_0, Robot2_0, Robot2_0, Robot2_0, Robot2_2, Robot2_2, Robot2_2, Robot2_2, Robot2_2};
const unsigned char * const ROBOT_JUMP2[]={Robot_Jump2_1, Robot_Jump2_1, Robot_Jump2_1, Robot_Jump2_1, Robot_Jump2_1};


const unsigned char Mini_Robot2_0[]={
	
	-4,   -5, 0x13,1,
	0x80
};

const unsigned char Mini_Robot2_1[]={
	
	-4,   -5, 0x15,1,
	0x80
};

const unsigned char Mini_Robot2_2[]={
	
	-4,   -5, 0x17,1,
	0x80
};

const unsigned char Mini_Robot_Jump2_1[]={
	
	-4,   -5, 0x15,1,
	0x80
};


const unsigned char * const MINI_ROBOT2[]={Mini_Robot2_0, Mini_Robot2_0, Mini_Robot2_0, Mini_Robot2_0, Mini_Robot2_0, Mini_Robot2_1, Mini_Robot2_1, Mini_Robot2_1, Mini_Robot2_1, Mini_Robot2_1, Mini_Robot2_0, Mini_Robot2_0, Mini_Robot2_0, Mini_Robot2_0, Mini_Robot2_0, Mini_Robot2_2, Mini_Robot2_2, Mini_Robot2_2, Mini_Robot2_2, Mini_Robot2_2};

const unsigned char * const MINI_ROBOT_JUMP2[]={Mini_Robot_Jump2_1, Mini_Robot_Jump2_1, Mini_Robot_Jump2_1, Mini_Robot_Jump2_1, Mini_Robot_Jump2_1};





// ================================================================

const unsigned char Spider_0[]={
	
	-12,   0, 0x21,3,
	 -4,   0, 0x23,3,
	  4,   0, 0x25,3,
	0x80
};

const unsigned char Spider_1[]={
	
	-12,   0, 0x27,3,
	 -4,   0, 0x29,3,
	  4,   0, 0x2B,3,
	0x80
};

const unsigned char Spider_2[]={
	
	-12,   0, 0x2D,3,
	 -4,   0, 0x2F,3,
	  4,   0, 0x31,3,
	0x80
};
const unsigned char Spider_3[]={
	
//	-12,   0, 0x43,3,
	 -4,   0, 0x33,3,
	  4,   0, 0x35,3,
	0x80
};

const unsigned char * const SPIDER[]={Spider_0, Spider_0, Spider_0, Spider_0, Spider_1, Spider_1, Spider_1, Spider_1, Spider_2, Spider_2, Spider_2, Spider_2, Spider_3, Spider_3, Spider_3, Spider_3};

const unsigned char * const SPIDER_JUMP[]={Spider_3};

// ================================================================

const unsigned char Spider2_0[]={
	
	-12,   0, 0x21,1,
	 -4,   0, 0x23,1,
	  4,   0, 0x25,1,
	0x80
};

const unsigned char Spider2_1[]={
	
	-12,   0, 0x27,1,
	 -4,   0, 0x29,1,
	  4,   0, 0x2B,1,
	0x80
};

const unsigned char Spider2_2[]={
	
	-12,   0, 0x2D,1,
	 -4,   0, 0x2F,1,
	  4,   0, 0x31,1,
	0x80
};
const unsigned char Spider2_3[]={
	
//	-12,   0, 0x43,1,
	 -4,   0, 0x33,1,
	  4,   0, 0x35,1,
	0x80
};

const unsigned char * const SPIDER2[]={Spider2_0, Spider2_0, Spider2_0, Spider2_0, Spider2_1, Spider2_1, Spider2_1, Spider2_1, Spider2_2, Spider2_2, Spider2_2, Spider2_2, Spider2_3, Spider2_3, Spider2_3, Spider2_3};

const unsigned char * const SPIDER_JUMP2[]={Spider2_3};



const unsigned char Mini_Spider_0[]={

	 -4,  -4,0x21,3,
	0x80
};

const unsigned char Mini_Spider_1[]={

	 -4,  -4,0x23,3,
	0x80
};

const unsigned char Mini_Spider_2[]={

	 -4,  -4,0x25,3,
	0x80
};

const unsigned char Mini_Spider_3[]={

	 -4,  -4,0x27,3,
	0x80
};

const unsigned char * const MINI_SPIDER[]={Mini_Spider_0, Mini_Spider_0, Mini_Spider_0, Mini_Spider_0, Mini_Spider_1, Mini_Spider_1, Mini_Spider_1, Mini_Spider_1, Mini_Spider_2, Mini_Spider_2, Mini_Spider_2, Mini_Spider_2, Mini_Spider_3, Mini_Spider_3, Mini_Spider_3, Mini_Spider_3};

const unsigned char * const MINI_SPIDER_JUMP[]={Mini_Spider_3};

const unsigned char Mini_Spider2_0[]={

	 -4,  -4,0x21,1,
	0x80
};

const unsigned char Mini_Spider2_1[]={

	 -4,  -4,0x23,1,
	0x80
};

const unsigned char Mini_Spider2_2[]={

	 -4,  -4,0x25,1,
	0x80
};

const unsigned char Mini_Spider2_3[]={

	 -4,  -4,0x27,1,
	0x80
};

const unsigned char * const MINI_SPIDER2[]={Mini_Spider2_0, Mini_Spider2_0, Mini_Spider2_0, Mini_Spider2_0, Mini_Spider2_1, Mini_Spider2_1, Mini_Spider2_1, Mini_Spider2_1, Mini_Spider2_2, Mini_Spider2_2, Mini_Spider2_2, Mini_Spider2_2, Mini_Spider2_3, Mini_Spider2_3, Mini_Spider2_3, Mini_Spider2_3};

const unsigned char * const MINI_SPIDER_JUMP2[]={Mini_Spider2_3};




const unsigned char Speed_05_Portal[]={
	  0,  0,0xA1,1|OAM_FLIP_V,
	  8,  0,0xA1,1|OAM_FLIP_H,	
	  0,  13,0xA1,1,	
	  8,  13,0xA1,1|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Speed_10_Portal[]={
	  0,  0,0xA1,0,
	  8,  0,0xA1,0|OAM_FLIP_H|OAM_FLIP_V,
	  0,  13,0xA1,0|OAM_FLIP_V,	
	  8,  13,0xA1,0|OAM_FLIP_H,	
	0x80
};
const unsigned char Speed_20_Portal[]={
	  0,  0,0xA9,0,	
	  5,  0,0xA9,0|OAM_FLIP_H|OAM_FLIP_V,	
	  6,  0,0xA9,0,	  
	  11,  0,0xA9,0|OAM_FLIP_H|OAM_FLIP_V,	  
	  0,  13,0xA9,0|OAM_FLIP_V,	
	  5,  13,0xA9,0|OAM_FLIP_H,	
	  6,  13,0xA9,0|OAM_FLIP_V,	
	  11,  13,0xA9,0|OAM_FLIP_H,	
	0x80
};
const unsigned char Speed_30_Portal[]={
	  0,  0,0xA9,1,
	  8,  0,0xAB,1,
	  6,  0,0xA9,1,
	  14,  0,0xAB,1,
	  12,  0,0xA9,1,
	  20,  0,0xAB,1,
	  0,  16,0xA9,1|OAM_FLIP_V,
	  8,  16,0xAB,1|OAM_FLIP_V,
	  6,  16,0xA9,1|OAM_FLIP_V,
	  14,  16,0xAB,1|OAM_FLIP_V,
	  12,	16,0xA9,1|OAM_FLIP_V,
	  20,  16,0xAB,1|OAM_FLIP_V,
	0x80
};

const unsigned char Speed_40_Portal[]={
	  0,  0,0xAD,2,
	  5,  0,0xAD,2,
	  10,  0,0xAD,2,
	  15,  0,0xAD,2,
	  0,  16,0xAD,2|OAM_FLIP_V,
	  5,  16,0xAD,2|OAM_FLIP_V,
	  10,  16,0xAD,2|OAM_FLIP_V,
	  15,  16,0xAD,2|OAM_FLIP_V,
	0x80
};

const unsigned char Mini_Portal[]={
	  0,  0,0x81,1,	
	  8,  0,0x83,1,	
	  -8,  16,0x85,1,	
	  0,  16,0x87,1,
	  8,  16,0x89,1,
	  0,  32,0x81,1|OAM_FLIP_V,
	  8,  32,0x83,1|OAM_FLIP_V,
	0x80
};

const unsigned char Growth_Portal[]={
	  0,  0,0x81,0,	
	  8,  0,0x83,0,	
	  -8,  16,0x85,0,	
	  0,  16,0x87,0,
	  8,  16,0x89,0,
	  0,  32,0x81,0|OAM_FLIP_V,
	  8,  32,0x83,0|OAM_FLIP_V,
	0x80
};

const unsigned char Gravity_2x_Portal[]={
	  0,  0,0x81,3,	
	  8,  0,0x83,3,	
	  -8,  16,0x85,3,	
	  0,  16,0x87,3,
	  8,  16,0x89,3,
	  0,  32,0x81,3|OAM_FLIP_V,
	  8,  32,0x83,3|OAM_FLIP_V,
	0x80
};

const unsigned char Gravity_12_Portal[]={
	  0,  0,0xA3,3,	
	  8,  0,0xA7,3,	
	  -8,  16,0xFF,3,	
	  0,  16,0x97,3,
	  8,  16,0xB7,3,
	  0,  32,0xA3,3|OAM_FLIP_V,
	  8,  32,0xA7,3|OAM_FLIP_V,
	0x80
};
const unsigned char Gravity_1x_Portal[]={
	  8,  0,0xA3,3|OAM_FLIP_H,	
	  0,  0,0xA7,3|OAM_FLIP_H,	
	  //-8,  16,0xFF,3|OAM_FLIP_H,	
	  8,  16,0x97,3|OAM_FLIP_H,
	  0,  16,0xB7,3|OAM_FLIP_H,
	  8,  32,0xA3,3|OAM_FLIP_V|OAM_FLIP_H,
	  0,  32,0xA7,3|OAM_FLIP_V|OAM_FLIP_H,
	0x80
};

const unsigned char Gravity_23_Portal[]={
	  0,  0,0xA3,0,	
	  8,  0,0xA7,0,	
	  -8,  16,0xFF,0,	
	  0,  16,0x97,0,
	  8,  16,0xB7,0,
	  0,  32,0xA3,0|OAM_FLIP_V,
	  8,  32,0xA7,0|OAM_FLIP_V,
	0x80
};

const unsigned char Gravity_13_Portal[]={
	  0,  0,0xA3,1,	
	  8,  0,0xA7,1,	
	  -8,  16,0xFF,1,	
	  0,  16,0x97,1,
	  8,  16,0xB7,1,
	  0,  32,0xA3,1|OAM_FLIP_V,
	  8,  32,0xA7,1|OAM_FLIP_V,
	0x80
};

const unsigned char Teleport_Portal_Enter[]={

	  0,  0,0xD5,0,
	  0, 16,0xDB,0,
	  0, 32,0xD5,0|OAM_FLIP_V,
	  8,  0,0xD7,0,

	  8, 16,0xDD,0,
	  8, 32,0xD7,0|OAM_FLIP_V,
	 16,  0,0xD9,0,
	 16, 16,0xDF,0,

	 16, 32,0xD9,0|OAM_FLIP_V,
	0x80
};
const unsigned char Teleport_Portal_Exit[]={

	 0,  0,0xD9,1|OAM_FLIP_H,
	 0, 16,0xDF,1|OAM_FLIP_H,

	 0, 32,0xD9,1|OAM_FLIP_H|OAM_FLIP_V,
	  8,  0,0xD7,1|OAM_FLIP_H,

	  8, 16,0xDD,1|OAM_FLIP_H,
	  8, 32,0xD7,1|OAM_FLIP_H|OAM_FLIP_V,
	  16,  0,0xD5,1|OAM_FLIP_H,
	  16, 16,0xDB,1|OAM_FLIP_H,
	  16, 32,0xD5,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

const unsigned char Portal_Gamemode_Cube[]={

	  0,  0,0x41,0,
	  0, 16,0x47,0,
	  0, 32,0x41,0|OAM_FLIP_V,
	  8,  0,0x43,0,

	  8, 16,0x49,0,
	  8, 32,0x43,0|OAM_FLIP_V,
	 16,  0,0x45,0,
	 16, 16,0x4B,0,

	 16, 32,0x45,0|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Ship[]={

	  0,  0,0x41,1,
	  0, 16,0x47,1,
	  0, 32,0x41,1|OAM_FLIP_V,
	  8,  0,0x43,1,

	  8, 16,0x49,1,
	  8, 32,0x43,1|OAM_FLIP_V,
	 16,  0,0x45,1,
	 16, 16,0x4B,1,

	 16, 32,0x45,1|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Ball[]={

	  0,  0,0x41,2,
	  0, 16,0x47,2,
	  0, 32,0x41,2|OAM_FLIP_V,
	  8,  0,0x43,2,

	  8, 16,0x49,2,
	  8, 32,0x43,2|OAM_FLIP_V,
	 16,  0,0x45,2,
	 16, 16,0x4B,2,

	 16, 32,0x45,2|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_UFO[]={

	  0,  0,0x61,1,
	  0, 16,0x67,1,
	  0, 32,0x61,1|OAM_FLIP_V,
	  8,  0,0x63,1,

	  8, 16,0x69,1,
	  8, 32,0x63,1|OAM_FLIP_V,
	 16,  0,0x65,1,
	 16, 16,0x6B,1,

	 16, 32,0x65,1|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Robot[]={

	  0,  0,0x61,2,
	  0, 16,0x67,2,
	  0, 32,0x61,2|OAM_FLIP_V,
	  8,  0,0x63,2,

	  8, 16,0x69,2,
	  8, 32,0x63,2|OAM_FLIP_V,
	 16,  0,0x65,2,
	 16, 16,0x6B,2,

	 16, 32,0x65,2|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Spider[]={

	  0,  0,0x41,1,
	  0, 16,0xF3,1,
	  0, 32,0x41,1|OAM_FLIP_V,
	  8,  0,0x43,1,

	  8, 16,0xF5,1,
	  8, 32,0x43,1|OAM_FLIP_V,
	 16,  0,0x45,1,
	 16, 16,0xF7,1,

	 16, 32,0x45,1|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Ninja[]={

	  0,  0,0x41,0,
	  0, 16,0xF3,0,
	  0, 32,0x41,0|OAM_FLIP_V,
	  8,  0,0x43,0,

	  8, 16,0xF5,0,
	  8, 32,0x43,0|OAM_FLIP_V,
	 16,  0,0x45,0,
	 16, 16,0xF7,0,

	 16, 32,0x45,0|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Swing[]={

	  0,  0,0x61,1,
	  0, 16,0xED,1,
	  0, 32,0x61,1|OAM_FLIP_V,
	  8,  0,0x63,1,

	  8, 16,0xEF,1,
	  8, 32,0x63,1|OAM_FLIP_V,
	 16,  0,0x65,1,
	 16, 16,0xF1,1,

	 16, 32,0x65,1|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gamemode_Wave[]={

	  0,  0,0x61,0,
	  0, 16,0x67,0,
	  0, 32,0x61,0|OAM_FLIP_V,
	  8,  0,0x63,0,

	  8, 16,0x69,0,
	  8, 32,0x63,0|OAM_FLIP_V,
	 16,  0,0x65,0,
	 16, 16,0x6B,0,

	 16, 32,0x65,0|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Gravity_Down[]={
	  0,  0,0x6D,0,  
	  0, 16,0x73,0,  
	  0, 32,0x6D,0|OAM_FLIP_V, 
	  8,  0,0x6F,0,  

	  8, 16,0x75,0,
	  8, 32,0x6F,0|OAM_FLIP_V,  
	 16,  0,0x71,0,  
	 16, 16,0x77,0, 

	 16, 32,0x71,0|OAM_FLIP_V, 
	0x80
};
const unsigned char Portal_Gravity_Up[]={

	  0,  0,0x6D,1,  
	  0, 16,0x73,1,  
	  0, 32,0x6D,1|OAM_FLIP_V, 
	  8,  0,0x6F,1,  

	  8, 16,0x75,1,
	  8, 32,0x6F,1|OAM_FLIP_V,  
	 16,  0,0x71,1,  
	 16, 16,0x77,1, 

	 16, 32,0x71,1|OAM_FLIP_V, 
	0x80
};


const unsigned char Portal_Dual[]={

	  0,  0,0x8B,1,
	  8, 0,0x8D,1,
	  16, 0,0x8F,1,
	  0,  16,0x91,1,

	  8, 16,0x93,1,
	  16, 16,0x95,1,
	 0,  32,0x8B,1|OAM_FLIP_V,
	 8, 32,0x8D,1|OAM_FLIP_V,

	 16, 32,0x8F,1|OAM_FLIP_V,
	0x80
};
const unsigned char Portal_Single[]={

	  0,  0,0x8B,0,
	  8, 0,0x8D,0,
	  16, 0,0x8F,0,
	  0,  16,0x91,0,

	  8, 16,0x93,0,
	  16, 16,0x95,0,
	  0,  32,0x8B,0|OAM_FLIP_V,
	  8, 32,0x8D,0|OAM_FLIP_V,

	 16, 32,0x8F,0|OAM_FLIP_V,
	0x80
};

const unsigned char Portal_Gravity_Down_Horizontal_Downwards[]={


	  0,  0,0x4D,0,  
	  8, 0,0x4F,0,  
	  16, 0,0x51,0,
	  24, 0,0x51,0|OAM_FLIP_H,  

	  32, 0,0x4F,0|OAM_FLIP_H,
	 40, 0,0x4D,0|OAM_FLIP_H,  
     8,-16,0x53,0,
	16,-16,0x55,0,
	24,-16,0x55,0|OAM_FLIP_H,
	32,-16,0x53,0|OAM_FLIP_H,

	0x80
};
const unsigned char Portal_Gravity_Down_Horizontal_Upwards[]={


	  0,  0,0x4D,0|OAM_FLIP_V,  
	  8, 0,0x4F,0|OAM_FLIP_V,  
	  16, 0,0x51,0|OAM_FLIP_V,
	  24, 0,0x51,0|OAM_FLIP_V|OAM_FLIP_H,  

	  32, 0,0x4F,0|OAM_FLIP_V|OAM_FLIP_H,
	 40, 0,0x4D,0|OAM_FLIP_V|OAM_FLIP_H,  

	8,16,0x53,0|OAM_FLIP_V,
	16,16,0x55,0|OAM_FLIP_V,
	24,16,0x55,0|OAM_FLIP_V|OAM_FLIP_H,
	32,16,0x53,0|OAM_FLIP_V|OAM_FLIP_H,
	0x80
};
const unsigned char Portal_Gravity_Up_Horizontal_Downwards[]={


	  0,  0,0x4D,1,  
	  8, 0,0x4F,1,  
	  16, 0,0x51,1,
	  24, 0,0x51,1|OAM_FLIP_H,  

	  32, 0,0x4F,1|OAM_FLIP_H,
	 40, 0,0x4D,1|OAM_FLIP_H,  
     8,-16,0x53,1,
	16,-16,0x55,1,
	24,-16,0x55,1|OAM_FLIP_H,
	32,-16,0x53,1|OAM_FLIP_H,

	0x80
};
const unsigned char Portal_Gravity_Up_Horizontal_Upwards[]={

	8,16,0x53,0|OAM_FLIP_V,
	16,16,0x55,0|OAM_FLIP_V,
	24,16,0x55,0|OAM_FLIP_V|OAM_FLIP_H,
	32,16,0x53,0|OAM_FLIP_V|OAM_FLIP_H,

	  0,  0,0x4D,1|OAM_FLIP_V,  
	  8, 0,0x4F,1|OAM_FLIP_V,  
	  16, 0,0x51,1|OAM_FLIP_V,
	  24, 0,0x51,1|OAM_FLIP_V|OAM_FLIP_H,  

	  32, 0,0x4F,1|OAM_FLIP_V|OAM_FLIP_H,
	 40, 0,0x4D,1|OAM_FLIP_V|OAM_FLIP_H,  

	0x80
};




// ================================================================

const unsigned char Dash_Orb[]={

	  0,  0,0xD1,0,
	  8,  0,0xD3,0,
	0x80
};

const unsigned char Black_Orb[]={

	  0,  0,0xA5,0,
	  8,  0,0xA5,0|OAM_FLIP_H,
	0x80
};

const unsigned char Dash_Orb_Upwards[]={

	  0,  0,0xCB,0|OAM_FLIP_H,
	  8,  0,0xCB,0,
	0x80
};
const unsigned char Dash_Gravity_Orb_Upwards[]={

	  0,  0,0xCB,1|OAM_FLIP_H,
	  8,  0,0xCB,1,
	0x80
};

const unsigned char Dash_Orb_Downwards[]={

	  0,  0,0xCB,0|OAM_FLIP_H|OAM_FLIP_V,
	  8,  0,0xCB,0|OAM_FLIP_V,
	0x80
};
const unsigned char Dash_Gravity_Orb_Downwards[]={

	  0,  0,0xCB,1|OAM_FLIP_H|OAM_FLIP_V,
	  8,  0,0xCB,1|OAM_FLIP_V,
	0x80
};

const unsigned char Dash_Gravity_Orb[]={

	  0,  0,0xD1,1,
	  8,  0,0xD3,1,
	0x80
};

const unsigned char Dash_Orb_45Deg_UP[]={

	  0,  0,0xCD,0,
	  8,  0,0xCF,0,
	0x80
};

const unsigned char Dash_Gravity_Orb_45Deg_UP[]={

	  0,  0,0xCD,1,
	  8,  0,0xCF,1,
	0x80
};

const unsigned char Spider_Orb_UP[]={

	  0,  0,0xC9,1,
	  8,  0,0xC9,1|OAM_FLIP_H,
	0x80
};

const unsigned char Spider_Orb_DOWN[]={

	  0,  0,0xC9,1|OAM_FLIP_V,
	  8,  0,0xC9,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Dash_Orb_45Deg_DOWN[]={

	  0,  0,0xCD,0|OAM_FLIP_V,
	  8,  0,0xCF,0|OAM_FLIP_V,
	0x80
};

const unsigned char Dash_Gravity_Orb_45Deg_DOWN[]={

	  0,  0,0xCD,1|OAM_FLIP_V,
	  8,  0,0xCF,1|OAM_FLIP_V,
	0x80
};



const unsigned char Yellow_Jump_Orb[]={

	  0,  0,0x99,1,
	  8,  0,0x9B,1|OAM_FLIP_H,
	0x80
};

const unsigned char Yellow_Jump_Orb2[]={

	  0,  0,0x9B,1,
	  8,  0,0x9D,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Orb3[]={

	  0,  0,0x9D,1,
	  8,  0,0x9F,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Orb4[]={

	  0,  0,0x9F,1,
	  8,  0,0x99,1|OAM_FLIP_H,
	0x80
};

const unsigned char Blue_Jump_Orb[]={

	  0,  0,0x99,0,
	  8,  0,0x9B,0|OAM_FLIP_H,
	0x80
};

const unsigned char Blue_Jump_Orb2[]={

	  0,  0,0x9B,0,
	  8,  0,0x9D,0|OAM_FLIP_H,
	0x80
};
const unsigned char Blue_Jump_Orb3[]={

	  0,  0,0x9D,0,
	  8,  0,0x9F,0|OAM_FLIP_H,
	0x80
};
const unsigned char Blue_Jump_Orb4[]={

	  0,  0,0x9F,0,
	  8,  0,0x99,0|OAM_FLIP_H,
	0x80
};
const unsigned char Pink_Jump_Orb[]={

	  0,  0,0xB9,1,
	  8,  0,0xBB,1|OAM_FLIP_H,
	0x80
};
const unsigned char Pink_Jump_Orb2[]={

	  0,  0,0xBB,1,
	  8,  0,0xBD,1|OAM_FLIP_H,
	0x80
};
const unsigned char Pink_Jump_Orb3[]={

	  0,  0,0xBD,1,
	  8,  0,0xBF,1|OAM_FLIP_H,
	0x80
};
const unsigned char Pink_Jump_Orb4[]={

	  0,  0,0xBF,1,
	  8,  0,0xB9,1|OAM_FLIP_H,
	0x80
};
const unsigned char Green_Jump_Orb[]={

	  0,  0,0xB9,0,
	  8,  0,0xBB,0|OAM_FLIP_H,
	0x80
};
const unsigned char Green_Jump_Orb2[]={

	  0,  0,0xBB,0,
	  8,  0,0xBD,0|OAM_FLIP_H,
	0x80
};
const unsigned char Green_Jump_Orb3[]={

	  0,  0,0xBD,0,
	  8,  0,0xBF,0|OAM_FLIP_H,
	0x80
};
const unsigned char Green_Jump_Orb4[]={

	  0,  0,0xBF,0,
	  8,  0,0xB9,0|OAM_FLIP_H,
	0x80
};

const unsigned char Red_Jump_Orb[]={

	  0,  0,0xB9,2,
	  8,  0,0xBB,2|OAM_FLIP_H,
	0x80
};
const unsigned char Red_Jump_Orb2[]={

	  0,  0,0xBB,2,
	  8,  0,0xBD,2|OAM_FLIP_H,
	0x80
};
const unsigned char Red_Jump_Orb3[]={

	  0,  0,0xBD,2,
	  8,  0,0xBF,2|OAM_FLIP_H,
	0x80
};
const unsigned char Red_Jump_Orb4[]={

	  0,  0,0xBF,2,
	  8,  0,0xB9,2|OAM_FLIP_H,
	0x80
};

const unsigned char Yellow_Jump_Pad[]={

	  0,-8,0x79,1,
	  8,-8,0x7B,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Pad2[]={

	  0,-8,0x7B,1,
	  8,-8,0x7D,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Pad3[]={

	  0,-8,0x7D,1,
	  8,-8,0x7F,1|OAM_FLIP_H,
	0x80
};
const unsigned char Yellow_Jump_Pad4[]={

	  0,-8,0x7F,1,
	  8,-8,0x79,1|OAM_FLIP_H,
	0x80
};

const unsigned char Yellow_Jump_Pad_U[]={

	  0,-0,0x79,1|OAM_FLIP_V,
	  8,-0,0x7B,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Yellow_Jump_Pad_U2[]={

	  0,-0,0x7B,1|OAM_FLIP_V,
	  8,-0,0x7D,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Yellow_Jump_Pad_U3[]={

	  0,-0,0x7D,1|OAM_FLIP_V,
	  8,-0,0x7F,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Yellow_Jump_Pad_U4[]={

	  0,-0,0x7F,1|OAM_FLIP_V,
	  8,-0,0x79,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Pink_Jump_Pad[]={

	  0,-8,0x59,1,
	  8,-8,0x5B,1|OAM_FLIP_H,
	0x80
};
const unsigned char Pink_Jump_Pad2[]={

	  0,-8,0x5B,1,
	  8,-8,0x5D,1|OAM_FLIP_H,
	0x80
};
const unsigned char Pink_Jump_Pad3[]={

	  0,-8,0x5D,1,
	  8,-8,0x5F,1|OAM_FLIP_H,
	0x80
};
const unsigned char Pink_Jump_Pad4[]={

	  0,-8,0x5F,1,
	  8,-8,0x59,1|OAM_FLIP_H,
	0x80
};
const unsigned char Red_Jump_Pad[]={

	  0,-8,0x59,2,
	  8,-8,0x5B,2|OAM_FLIP_H,
	0x80
};
const unsigned char Red_Jump_Pad2[]={

	  0,-8,0x5B,2,
	  8,-8,0x5D,2|OAM_FLIP_H,
	0x80
};
const unsigned char Red_Jump_Pad3[]={

	  0,-8,0x5D,2,
	  8,-8,0x5F,2|OAM_FLIP_H,
	0x80
};
const unsigned char Red_Jump_Pad4[]={

	  0,-8,0x5F,2,
	  8,-8,0x59,2|OAM_FLIP_H,
	0x80
};

const unsigned char Pink_Jump_Pad_U[]={

	  0,-0,0x59,1|OAM_FLIP_V,
	  8,-0,0x5B,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Pink_Jump_Pad_U2[]={

	  0,-0,0x5B,1|OAM_FLIP_V,
	  8,-0,0x5D,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Pink_Jump_Pad_U3[]={

	  0,-0,0x5D,1|OAM_FLIP_V,
	  8,-0,0x5F,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Pink_Jump_Pad_U4[]={

	  0,-0,0x5F,1|OAM_FLIP_V,
	  8,-0,0x59,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

const unsigned char Red_Jump_Pad_U[]={

	  0,-0,0x59,2|OAM_FLIP_V,
	  8,-0,0x5B,2|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Red_Jump_Pad_U2[]={

	  0,-0,0x5B,2|OAM_FLIP_V,
	  8,-0,0x5D,2|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Red_Jump_Pad_U3[]={

	  0,-0,0x5D,2|OAM_FLIP_V,
	  8,-0,0x5F,2|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Red_Jump_Pad_U4[]={

	  0,-0,0x5F,2|OAM_FLIP_V,
	  8,-0,0x59,2|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

const unsigned char Gravity_Pad[]={

	  0,-8,0x79,4,
	  8,-8,0x7B,4|OAM_FLIP_H,
	0x80
};
const unsigned char Gravity_Pad2[]={

	  0,-8,0x7B,4,
	  8,-8,0x7D,4|OAM_FLIP_H,
	0x80
};
const unsigned char Gravity_Pad3[]={

	  0,-8,0x7D,4,
	  8,-8,0x7F,4|OAM_FLIP_H,
	0x80
};
const unsigned char Gravity_Pad4[]={

	  0,-8,0x7F,4,
	  8,-8,0x79,4|OAM_FLIP_H,
	0x80
};

const unsigned char Gravity_Pad_U[]={

	  0, -0,0x79,4|OAM_FLIP_V,
	  8, -0,0x7B,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Gravity_Pad_U2[]={

	  0, -0,0x7B,4|OAM_FLIP_V,
	  8, -0,0x7D,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Gravity_Pad_U3[]={

	  0, -0,0x7D,4|OAM_FLIP_V,
	  8, -0,0x7F,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Gravity_Pad_U4[]={

	  0, -0,0x7F,4|OAM_FLIP_V,
	  8, -0,0x79,4|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

const unsigned char Teleport_Square_Enter[]={

	  0, 0,0xEB,0,
	  8, 0,0xEB,0|OAM_FLIP_H,
	0x80
};

const unsigned char Teleport_Square_Exit[]={

	  0, 0,0xEB,1,
	  8, 0,0xEB,1|OAM_FLIP_H,
	0x80
};
const unsigned char Spider_Pad_Up[]={

	  0, -8,0xE1,1,
	  8, -8,0xE3,1|OAM_FLIP_H,
	0x80
};

const unsigned char Spider_Pad_Up2[]={

	  0, -8,0xE3,1,
	  8, -8,0xE5,1|OAM_FLIP_H,
	0x80
};

const unsigned char Spider_Pad_Up3[]={

	  0, -8,0xE5,1,
	  8, -8,0xE7,1|OAM_FLIP_H,
	0x80
};

const unsigned char Spider_Pad_Up4[]={

	  0, -8,0xE7,1,
	  8, -8,0xE1,1|OAM_FLIP_H,
	0x80
};

const unsigned char Spider_Pad_Down[]={

	  0, -0,0xE1,1|OAM_FLIP_V,
	  8, -0,0xE3,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

const unsigned char Spider_Pad_Down2[]={

	  0, -0,0xE3,1|OAM_FLIP_V,
	  8, -0,0xE5,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Spider_Pad_Down3[]={

	  0, -0,0xE5,1|OAM_FLIP_V,
	  8, -0,0xE7,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};
const unsigned char Spider_Pad_Down4[]={

	  0, -0,0xE7,1|OAM_FLIP_V,
	  8, -0,0xE9,1|OAM_FLIP_H|OAM_FLIP_V,
	0x80
};

const unsigned char Short_Light[]={

	  4, 0,0xCD,3,
	0x80
};	
	

const unsigned char Short_Light_U[]={

	  4, 0,0xCD,3|OAM_FLIP_V,
	0x80
};	


const unsigned char Medium_Light[]={

	  4, 0,0xCF,3,
	  4, -16,0xCB,3,
	0x80
};	


const unsigned char Medium_Light_U[]={

	  4, 0,0xCF,3|OAM_FLIP_V,
	  4, 16,0xCB,3|OAM_FLIP_V,
	0x80
};	

const unsigned char Long_Light[]={

	  4, 0,0xCF,3,
	  4, -16,0xC9,3,
	0x80
};	


const unsigned char Long_Light_U[]={

	  4, 0,0xCF,3|OAM_FLIP_V,
	  4, 16,0xC9,3|OAM_FLIP_V,
	0x80
};	

const unsigned char Short_Light_Left[]={
	 0, -4,0xF3,3,
	 8, -4,0xF1,3,
	0x80
};

const unsigned char Short_Light_Right[]={
	 8, -4,0xF3,3|OAM_FLIP_H,
	 0, -4,0xF1,3|OAM_FLIP_H,
	0x80
};


const unsigned char Medium_Light_Left[]={
	 0, -4,0xF5,3,
	 8, -4,0xF7,3,
	 16, -4,0xF1,3,
	0x80
};

const unsigned char Medium_Light_Right[]={
	 0, -4,0xF1,3|OAM_FLIP_H,
	 8, -4,0xF7,3|OAM_FLIP_H,
	 16, -4,0xF5,3|OAM_FLIP_H,
	0x80
};

const unsigned char Long_Light_Left[]={//now medium upwards chain shifted down 8px
	  4, 8,0xD5,3,
	  4, -8,0xD7,3,
	0x80
};

const unsigned char Long_Light_Right[]={//now upwards lamp shifted down 8px
	  20, 8,0xCD,3,
	0x80
};

const unsigned char Chain[]={

	  4, 0,0xD5,3,
	  4, -16,0xD7,3,
	0x80
};	

const unsigned char Chain_U[]={

	  4, 16,0xD7,3|OAM_FLIP_V,
	  4, 0,0xD5,3|OAM_FLIP_V,
	0x80
};	

const unsigned char BG_Spike_Group1[]={

	  0, -4,0xD9,3,
	  8, -4,0xDB,3,
	0x80
};	
const unsigned char BG_Spike_Group2[]={

	  0, 4,0xD9,3|OAM_FLIP_V,
	  8, 4,0xDB,3|OAM_FLIP_V,
	0x80
};	
const unsigned char BG_Spike_Group3[]={

	  0, -4,0xDD,3,
	  8, -4,0xDF,3,
	0x80
};	
const unsigned char BG_Spike_Group4[]={

	  0, 4,0xDD,3|OAM_FLIP_V,
	  8, 4,0xDF,3|OAM_FLIP_V,
	0x80
};	


const unsigned char Big_Diamond[]={

	  0, 0,0xE1,3,
	  8, 0,0xE1,3|OAM_FLIP_H,
	0x80
};	
const unsigned char Right_Half_Diamond[]={

	  8, 0,0xE1,3|OAM_FLIP_H,
	0x80
};	


const unsigned char Question_Mark[]={

	  4, 0,0xE3,3,
	0x80
};	
const unsigned char Exclamation_Mark[]={

	  4, 0,0xE5,3,
	0x80
};	


const unsigned char Star[]={

	  0, 0,0xE7,3,
	  8, 0,0xE7,3|OAM_FLIP_H,
	0x80
};	

const unsigned char Big_X[]={

	  0, 0,0xED,3,
	  8, 0,0xED,3|OAM_FLIP_H,
	0x80
};	

const unsigned char Diamond_Shifted_Right[]={

	  8, 0,0xE1,3,
	  16, 0,0xE1,3|OAM_FLIP_H,
	0x80
};

const unsigned char Pulsing_Ball[]={

	  4, -4,0xF9,3,
	0x80
};

const unsigned char Music_Note[]={

	  0, 0,0xE9,3,
	  8, 0,0xEB,3,
	0x80
};	
















struct SpriteFrame {
	unsigned short frame_count; // use a two byte length value for alignment
	const unsigned char* ptr;
};

const struct SpriteFrame COIN_SPRITES[]={
	{5, COIN_SPRITE},
	{5, COIN_1_SPRITE},
	{5, COIN_2_SPRITE},
	{5, COIN_3_SPRITE},
};
const struct SpriteFrame COIN_SPRITES_X[]={
	{5, COIN_SPRITE_X},
	{5, COIN_1_X},
	{5, COIN_2_X},
	{5, COIN_3_X},
};

const struct SpriteFrame YELLOW_PAD_SPRITES[]={
	{5, Yellow_Jump_Pad},
	{5, Yellow_Jump_Pad2},
	{5, Yellow_Jump_Pad3},
	{5, Yellow_Jump_Pad4},
};

const struct SpriteFrame YELLOW_PAD_U_SPRITES[]={
	{5, Yellow_Jump_Pad_U},
	{5, Yellow_Jump_Pad_U2},
	{5, Yellow_Jump_Pad_U3},
	{5, Yellow_Jump_Pad_U4},
};
const struct SpriteFrame PINK_PAD_SPRITES[]={
	{5, Pink_Jump_Pad},
	{5, Pink_Jump_Pad2},
	{5, Pink_Jump_Pad3},
	{5, Pink_Jump_Pad4},
};
const struct SpriteFrame SPIDER_PAD_UP_SPRITES[]={
	{5, Spider_Pad_Up},
	{5, Spider_Pad_Up2},
	{5, Spider_Pad_Up3},
	{5, Spider_Pad_Up4},
};
const struct SpriteFrame SPIDER_PAD_DOWN_SPRITES[]={
	{5, Spider_Pad_Down},
	{5, Spider_Pad_Down2},
	{5, Spider_Pad_Down3},
	{5, Spider_Pad_Down4},
};
const struct SpriteFrame RED_PAD_SPRITES[]={
	{5, Red_Jump_Pad},
	{5, Red_Jump_Pad2},
	{5, Red_Jump_Pad3},
	{5, Red_Jump_Pad4},
};
const struct SpriteFrame RED_PAD_U_SPRITES[]={
	{5, Red_Jump_Pad_U},
	{5, Red_Jump_Pad_U2},
	{5, Red_Jump_Pad_U3},
	{5, Red_Jump_Pad_U4},
};

const struct SpriteFrame PINK_PAD_U_SPRITES[]={
	{5, Pink_Jump_Pad_U},
	{5, Pink_Jump_Pad_U2},
	{5, Pink_Jump_Pad_U3},
	{5, Pink_Jump_Pad_U4},
};

const struct SpriteFrame GRAVITY_PAD_SPRITES[]={
	{5, Gravity_Pad},
	{5, Gravity_Pad2},
	{5, Gravity_Pad3},
	{5, Gravity_Pad4},
};

const struct SpriteFrame GRAVITY_PAD_U_SPRITES[]={
	{5, Gravity_Pad_U},
	{5, Gravity_Pad_U2},
	{5, Gravity_Pad_U3},
	{5, Gravity_Pad_U4},
};
const struct SpriteFrame YELLOW_ORB_SPRITES[]={
	{5, Yellow_Jump_Orb},
	{5, Yellow_Jump_Orb2},
	{5, Yellow_Jump_Orb3},
	{5, Yellow_Jump_Orb4},
};
const struct SpriteFrame BLUE_ORB_SPRITES[]={
	{5, Blue_Jump_Orb},
	{5, Blue_Jump_Orb2},
	{5, Blue_Jump_Orb3},
	{5, Blue_Jump_Orb4},
};
const struct SpriteFrame PINK_ORB_SPRITES[]={
	{5, Pink_Jump_Orb},
	{5, Pink_Jump_Orb2},
	{5, Pink_Jump_Orb3},
	{5, Pink_Jump_Orb4},
};

const struct SpriteFrame GREEN_ORB_SPRITES[]={
	{5, Green_Jump_Orb},
	{5, Green_Jump_Orb2},
	{5, Green_Jump_Orb3},
	{5, Green_Jump_Orb4},
};

const struct SpriteFrame RED_ORB_SPRITES[]={
	{5, Red_Jump_Orb},
	{5, Red_Jump_Orb2},
	{5, Red_Jump_Orb3},
	{5, Red_Jump_Orb4},
};

const struct SpriteFrame RANDOM_GAMEMODE_PORTAL[]={
	{10, Portal_Gamemode_Cube},
	{10, Portal_Gamemode_Ship},
	{10, Portal_Gamemode_Ball},
	{10, Portal_Gamemode_UFO},
	{10, Portal_Gamemode_Robot},
	{10, Portal_Gamemode_Spider},
	{10, Portal_Gamemode_Wave},
	{10, Portal_Gamemode_Swing},
};


const unsigned char nometa[] = {0x80};

const unsigned char * const Metasprites[]={
	Portal_Gamemode_Cube,
	Portal_Gamemode_Ship, 
	Portal_Gamemode_Ball, // ball
	Portal_Gamemode_UFO, // ufo
	Portal_Gamemode_Robot, // wave
	Blue_Jump_Orb, // bobot
	Pink_Jump_Orb, 
	COIN_SPRITE, // swing
	Portal_Gravity_Down,
	Portal_Gravity_Up,
	Yellow_Jump_Pad,
	Yellow_Jump_Orb,
	Yellow_Jump_Pad_U,
	Gravity_Pad,
	Gravity_Pad_U,	  //Coin Disappear
	nometa, // end stage trigger

	Portal_Gravity_Down_Horizontal_Downwards,
	Portal_Gravity_Down_Horizontal_Upwards,
	Portal_Gravity_Up_Horizontal_Downwards,
	Portal_Gravity_Up_Horizontal_Upwards,
	Speed_05_Portal,
	Speed_10_Portal,
	Speed_20_Portal,
	Portal_Gamemode_Spider,
	Mini_Portal,
	Growth_Portal,
	COIN_SPRITE, // swing
	COIN_SPRITE, // swing
	COIN_SPRITE_X, // swing
	COIN_SPRITE_X, // swing
	COIN_SPRITE_X, // swing
	Yellow_Jump_Orb, //bigger jump orb

	Speed_30_Portal,
	Speed_40_Portal,
	Portal_Dual,
	Portal_Single,
	Portal_Gamemode_Wave,
	Pink_Jump_Pad,
	Pink_Jump_Pad_U,
	Green_Jump_Orb,
	Red_Jump_Orb,
	Yellow_Jump_Orb, //littler jump orb
	Long_Light,
	Medium_Light,
	Short_Light,
	Chain,
	BG_Spike_Group1,
	BG_Spike_Group2,

	BG_Spike_Group3,
	BG_Spike_Group4,
	Big_Diamond,
	Right_Half_Diamond,
	Question_Mark,
	Exclamation_Mark,
	Star,
	Big_X,
	Short_Light_Right,
	Short_Light_Left,
	Long_Light_U,
	Medium_Light_U,
	Short_Light_U,
	Chain_U,
	Medium_Light_Right,
	Medium_Light_Left,
	
	Long_Light_Right, //short light shifted down 8px
	Long_Light_Left, //chain shifted down 8px
	Short_Light_U,
	Chain_U,
	Black_Orb,
	Dash_Orb,
	Dash_Gravity_Orb,
	BG_Spike_Group2,
	Diamond_Shifted_Right,
	Pulsing_Ball,
	Music_Note,
	Portal_Gamemode_Swing,
	Dash_Orb_45Deg_UP,
	Dash_Gravity_Orb_45Deg_UP,
	Teleport_Portal_Enter,
	Teleport_Portal_Exit,
	Dash_Orb_45Deg_DOWN,
	Dash_Gravity_Orb_45Deg_DOWN,
	Red_Jump_Pad,
	Red_Jump_Pad_U,
	Spider_Orb_UP,
	Spider_Orb_DOWN,
	Spider_Pad_Up,
	Spider_Pad_Down,
	Portal_Gamemode_Ninja,
	Teleport_Square_Enter,
	Teleport_Square_Exit,
	Dash_Orb_Upwards,
	Dash_Gravity_Orb_Upwards,
	Dash_Orb_Downwards,
	Dash_Gravity_Orb_Downwards,
	Gravity_13_Portal,
	Gravity_12_Portal,
	Gravity_23_Portal,
	Gravity_2x_Portal,
	Gravity_1x_Portal,
	Portal_Gamemode_Cube,
	};


// Animation data
const void* const animation_frame_list[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	BLUE_ORB_SPRITES,
	PINK_ORB_SPRITES,
	COIN_SPRITES,
	NULL, // Portal_Gravity_Down,
	NULL, // Portal_Gravity_Up,
	YELLOW_PAD_SPRITES, // Yellow_Jump_Pad,
	YELLOW_ORB_SPRITES, // Yellow_Jump_Orb,
	YELLOW_PAD_U_SPRITES, // Yellow_Jump_Pad_U,
	GRAVITY_PAD_SPRITES, // Gravity_Pad,
	GRAVITY_PAD_U_SPRITES, // Gravity_Pad_U,	  //Coin Disappear
	NULL, // nometa, // end stage trigger
	
	NULL, //horizontal pads
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	COIN_SPRITES,
	COIN_SPRITES,
	COIN_SPRITES_X,
	COIN_SPRITES_X,
	COIN_SPRITES_X,
	YELLOW_ORB_SPRITES,
	
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	PINK_PAD_SPRITES, // Pink_Jump_Pad,	
	PINK_PAD_U_SPRITES, // Pink_Jump_Pad,	
	GREEN_ORB_SPRITES,
	RED_ORB_SPRITES,
	YELLOW_ORB_SPRITES,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,

	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,	
	NULL,
	NULL,
	NULL,
	
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RED_PAD_SPRITES,
	RED_PAD_U_SPRITES,
	NULL,
	NULL,
	SPIDER_PAD_UP_SPRITES,
	SPIDER_PAD_DOWN_SPRITES,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	RANDOM_GAMEMODE_PORTAL,
};

// Number of UNIQUE animation frames
const unsigned char animation_frame_length[] = {
	0,
	0,
	0,
	0,
	0,
	sizeof(BLUE_ORB_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,
	sizeof(PINK_ORB_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,
	sizeof(COIN_SPRITES) / sizeof(struct SpriteFrame), // COIN_SPRITE
	0, // Portal_Gravity_Down,
	0, // Portal_Gravity_Up,
	sizeof(YELLOW_PAD_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,
	sizeof(YELLOW_ORB_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,
	sizeof(YELLOW_PAD_U_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad_U,
	sizeof(GRAVITY_PAD_SPRITES) / sizeof(struct SpriteFrame), // Gravity_Pad,
	sizeof(GRAVITY_PAD_U_SPRITES) / sizeof(struct SpriteFrame), // Gravity_Pad_U,	  //Coin Disappear
	0, // nometa, // end stage trigger
	
	0, //horizontal portals
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(COIN_SPRITES) / sizeof(struct SpriteFrame), // COIN_SPRITE
	sizeof(COIN_SPRITES) / sizeof(struct SpriteFrame), // COIN_SPRITE
	sizeof(COIN_SPRITES_X) / sizeof(struct SpriteFrame), // COIN_SPRITE
	sizeof(COIN_SPRITES_X) / sizeof(struct SpriteFrame), // COIN_SPRITE
	sizeof(COIN_SPRITES_X) / sizeof(struct SpriteFrame), // COIN_SPRITE
	sizeof(YELLOW_ORB_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,

	0,
	0,
	0,
	0,
	0,
	sizeof(PINK_PAD_SPRITES) / sizeof(struct SpriteFrame), // Gravity_Pad,
	sizeof(PINK_PAD_U_SPRITES) / sizeof(struct SpriteFrame), // Gravity_Pad_U,	  //Coin Disappear
	sizeof(GREEN_ORB_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,
	sizeof(RED_ORB_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,	
	sizeof(YELLOW_ORB_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,
	0,
	0,
	0,
	0,
	0,
	0,

	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,

	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(RED_PAD_SPRITES) / sizeof(struct SpriteFrame), // Red_Jump_Pad,
	sizeof(RED_PAD_U_SPRITES) / sizeof(struct SpriteFrame), // Red_Jump_Pad,
	0,
	0,
	sizeof(SPIDER_PAD_UP_SPRITES) / sizeof(struct SpriteFrame), // Red_Jump_Pad,
	sizeof(SPIDER_PAD_DOWN_SPRITES) / sizeof(struct SpriteFrame), // Red_Jump_Pad,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(RANDOM_GAMEMODE_PORTAL) / sizeof(struct SpriteFrame), // Red_Jump_Pad,
};

#pragma rodata-name (pop)