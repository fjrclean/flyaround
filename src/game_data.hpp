// game_data.hpp
// Part of project game_engine/flyaround
// Defintions for data types used across engine.

#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

/********************************************************/

#include "vector_math.hpp"

/********************************************************/

// CONSTANTS
#define PLAYER_SPEED 0.001; // change in position per step

/********************************************************/

// DATA STRUCTS

enum action{
	NOTHING,
	GM_LEAVE,
	MV_FORWARD,
	MV_BACK,
	MV_LEFT,
	MV_RIGHT,
	MV_JUMP
};

struct fromplayer_t{
	uint16_t actionPress;
	uint16_t actionRelease;
	struct vector3d camRotate;
};

struct fromserver_t{
	
};

/*********************************************************/

#endif
