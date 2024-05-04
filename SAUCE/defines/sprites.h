// a 16x16 pixel metasprite
// cube starts here

const unsigned char Practice_Diamond[]={

	  0,  0,0x57,0,
	0x80
};

const unsigned char * const Practice_Sprites[] = {Practice_Diamond};

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
	
const unsigned char WAVE_0[]={

	 -8,  0,0x37,3,
	  0,  0,0x39,3,
	0x80
};		

const unsigned char WAVE_1[]={

	 -8,  0,0x1B,3,
	  0,  0,0x1D,3,
	0x80
};	
const unsigned char WAVE_2[]={

	 -8,  0,0x17,3,
	  0,  0,0x19,3,
	0x80
};		
	

const unsigned char WAVE_5[]={

	 -8,  0,0x1B,3|OAM_FLIP_V,
	  0,  0,0x1D,3|OAM_FLIP_V,
	0x80
};	

const unsigned char WAVE_6[]={

	 -8,  0,0x37,3|OAM_FLIP_V,
	  0,  0,0x39,3|OAM_FLIP_V,
	0x80
};		



const unsigned char * const WAVE[] = {WAVE_0, WAVE_0, WAVE_1, WAVE_2, WAVE_2, WAVE_5, WAVE_6, WAVE_6};	
const unsigned char WAVE2_0[]={

	 -8,  0,0x37,1,
	  0,  0,0x39,1,
	0x80
};		

const unsigned char WAVE2_1[]={

	 -8,  0,0x1B,1,
	  0,  0,0x1D,1,
	0x80
};	
const unsigned char WAVE2_2[]={

	 -8,  0,0x17,1,
	  0,  0,0x19,1,
	0x80
};		
	

const unsigned char WAVE2_5[]={

	 -8,  0,0x1B,1|OAM_FLIP_V,
	  0,  0,0x1D,1|OAM_FLIP_V,
	0x80
};	

const unsigned char WAVE2_6[]={

	 -8,  0,0x37,1|OAM_FLIP_V,
	  0,  0,0x39,1|OAM_FLIP_V,
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

	 -4,  -5,0x21,3,
	0x80
};		
const unsigned char MINI_UFO_U[]={

	 -4,  -5,0x21,3|OAM_FLIP_H,
	0x80
};		
const unsigned char MINI_UFO_D[]={

	 -4,  -5,0x21,3,
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

	 -4,  -5,0x21,1,
	0x80
};		
const unsigned char MINI_UFO2_U[]={

	 -4,  -5,0x21,1|OAM_FLIP_H,
	0x80
};		
const unsigned char MINI_UFO2_D[]={

	 -4,  -5,0x21,1,
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

	  0,  0,0xAD,1,
	  8,  0,0xAD,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_1_SPRITE[]={

	  0,  0,0xAF,1,
	  8,  0,0xB1,1,
	0x80
};
const unsigned char COIN_2_SPRITE[]={

	  0,  0,0xB3,1,
	  8,  0,0xB3,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_3_SPRITE[]={

	  0,  0,0xB1,1|OAM_FLIP_H,
	  8,  0,0xAF,1|OAM_FLIP_H,
	0x80
};


const unsigned char COIN_SPRITE_X[]={

	  0,  0,0xB9,1,
	  8,  0,0xB9,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_1_X[]={

	  0,  0,0xBB,1,
	  8,  0,0xBD,1,
	0x80
};
const unsigned char COIN_2_X[]={

	  0,  0,0xBF,1,
	  8,  0,0xBF,1|OAM_FLIP_H,
	0x80
};
const unsigned char COIN_3_X[]={

	  0,  0,0xBD,1|OAM_FLIP_H,
	  8,  0,0xBB,1|OAM_FLIP_H,
	0x80
};



const unsigned char Ball_0[]={

	 -8,  0,0x3B,3,
	  0,  0,0x3B,3|OAM_FLIP_H,
	0x80
};
const unsigned char Ball_1[]={

	 -8,  0,0x3D,3,
	  0,  0,0x3D,3|OAM_FLIP_H,
	0x80
};

const unsigned char * const BALL[]={Ball_0, Ball_0, Ball_0, Ball_0, Ball_1, Ball_1, Ball_1, Ball_1};
// ================================================================

const unsigned char Ball2_0[]={

	 -8,  0,0x3B,1,
	  0,  0,0x3B,1|OAM_FLIP_H,
	0x80
};
const unsigned char Ball2_1[]={

	 -8,  0,0x3D,1,
	  0,  0,0x3D,1|OAM_FLIP_H,
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

	 -4,  -4,0x19,3,
	0x80
};

const unsigned char Mini_Spider_1[]={

	 -4,  -4,0x1B,3,
	0x80
};

const unsigned char Mini_Spider_2[]={

	 -4,  -4,0x1D,3,
	0x80
};

const unsigned char Mini_Spider_3[]={

	 -4,  -4,0x1F,3,
	0x80
};

const unsigned char * const MINI_SPIDER[]={Mini_Spider_0, Mini_Spider_0, Mini_Spider_0, Mini_Spider_0, Mini_Spider_1, Mini_Spider_1, Mini_Spider_1, Mini_Spider_1, Mini_Spider_2, Mini_Spider_2, Mini_Spider_2, Mini_Spider_2, Mini_Spider_3, Mini_Spider_3, Mini_Spider_3, Mini_Spider_3};

const unsigned char * const MINI_SPIDER_JUMP[]={Mini_Spider_3};

const unsigned char Mini_Spider2_0[]={

	 -4,  -4,0x19,1,
	0x80
};

const unsigned char Mini_Spider2_1[]={

	 -4,  -4,0x1B,1,
	0x80
};

const unsigned char Mini_Spider2_2[]={

	 -4,  -4,0x1D,1,
	0x80
};

const unsigned char Mini_Spider2_3[]={

	 -4,  -4,0x1F,1,
	0x80
};

const unsigned char * const MINI_SPIDER2[]={Mini_Spider2_0, Mini_Spider2_0, Mini_Spider2_0, Mini_Spider2_0, Mini_Spider2_1, Mini_Spider2_1, Mini_Spider2_1, Mini_Spider2_1, Mini_Spider2_2, Mini_Spider2_2, Mini_Spider2_2, Mini_Spider2_2, Mini_Spider2_3, Mini_Spider2_3, Mini_Spider2_3, Mini_Spider2_3};

const unsigned char * const MINI_SPIDER_JUMP2[]={Mini_Spider2_3};




const unsigned char Speed_05_Portal[]={
	  0,  0,0xA3,1|OAM_FLIP_H,	
	  8,  0,0xA1,1|OAM_FLIP_H,
	  0,  16,0xA3,1|OAM_FLIP_H|OAM_FLIP_V,	
	  8,  16,0xA1,1|OAM_FLIP_H|OAM_FLIP_V,	
	0x80
};

const unsigned char Speed_10_Portal[]={
	  0,  0,0xA1,0,
	  8,  0,0xA3,0,
	  0,  16,0xA1,0|OAM_FLIP_V,	
	  8,  16,0xA3,0|OAM_FLIP_V,	
	0x80
};
const unsigned char Speed_20_Portal[]={
	  0,  0,0xA5,0,	
	  8,  0,0xA7,0,	
	  8,  0,0xA5,0,
	  16,  0,0xA7,0,	  
	  0,  16,0xA5,0|OAM_FLIP_V,	
	  8,  16,0xA7,0|OAM_FLIP_V,	
	  8,  16,0xA5,0|OAM_FLIP_V,	
	  16,  16,0xA7,0|OAM_FLIP_V,	
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
	  0,  0,0x9F,2,
	  5,  0,0x9F,2,
	  10,  0,0x9F,2,
	  15,  0,0x9F,2,
	  0,  16,0x9F,2|OAM_FLIP_V,
	  5,  16,0x9F,2|OAM_FLIP_V,
	  10,  16,0x9F,2|OAM_FLIP_V,
	  15,  16,0x9F,2|OAM_FLIP_V,
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


	  0,  16,0x4D,0,  
	  8, 16,0x4F,0,  
	  16, 16,0x51,0,
	  24, 16,0x51,0|OAM_FLIP_H,  

	  32, 16,0x4F,0|OAM_FLIP_H,
	 40, 16,0x4D,0|OAM_FLIP_H,  
     8,0,0x53,0,
	16,0,0x55,0,
	24,0,0x55,0|OAM_FLIP_H,
	32,0,0x53,0|OAM_FLIP_H,

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


	  0,  16,0x4D,1,  
	  8, 16,0x4F,1,  
	  16, 16,0x51,1,
	  24, 16,0x51,1|OAM_FLIP_H,  

	  32, 16,0x4F,1|OAM_FLIP_H,
	 40, 16,0x4D,1|OAM_FLIP_H,  
     8,0,0x53,1,
	16,0,0x55,1,
	24,0,0x55,1|OAM_FLIP_H,
	32,0,0x53,1|OAM_FLIP_H,

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

const unsigned char Yellow_Jump_Orb[]={

	  4,  0,0xB7,1,
	0x80
};

const unsigned char Blue_Jump_Orb[]={

	  4,  0,0xB7,4,
	0x80
};
const unsigned char Pink_Jump_Orb[]={

	  4,  0,0xB5,1,
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
	};


// Animation data
const void* animation_frame_list[] = {
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	COIN_SPRITES,
	NULL, // Portal_Gravity_Down,
	NULL, // Portal_Gravity_Up,
	YELLOW_PAD_SPRITES, // Yellow_Jump_Pad,
	NULL, // Yellow_Jump_Orb,
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
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	PINK_PAD_SPRITES, // Pink_Jump_Pad,	
	PINK_PAD_U_SPRITES, // Pink_Jump_Pad,	
};

// Number of UNIQUE animation frames
const unsigned char animation_frame_length[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(COIN_SPRITES) / sizeof(struct SpriteFrame), // COIN_SPRITE
	0, // Portal_Gravity_Down,
	0, // Portal_Gravity_Up,
	sizeof(YELLOW_PAD_SPRITES) / sizeof(struct SpriteFrame), // Yellow_Jump_Pad,
	0, // Yellow_Jump_Orb,
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
	0,
	0,
	0,
	0,
	0,
	0,
	sizeof(PINK_PAD_SPRITES) / sizeof(struct SpriteFrame), // Gravity_Pad,
	sizeof(PINK_PAD_U_SPRITES) / sizeof(struct SpriteFrame), // Gravity_Pad_U,	  //Coin Disappear
};
