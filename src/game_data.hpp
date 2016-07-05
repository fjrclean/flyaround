// game_data.hpp
// Part of project game_engine/flyaround
// Defintions for data types used across engine.

#ifndef GAME_DATA_HPP
#define GAME_DATA_HPP

/********************************************************/

#include <stdint.h>

#include "vector_math.hpp"

/********************************************************/

// CONSTANTS
#define PLAYER_SPEED 0.001; // change in position per step

// DATA SIZES
#define ACTION_NAME_SIZE 12

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
	uint32_t lastid;
	uint16_t actionPress;
	uint16_t actionRelease;
	struct vector3d camRotate;
	uint8_t nameSz; // Player name follows this struct in same dgram. (eg on set/change). 0 if not present.
	// Receival of name should be confirmed by server.
	// Name should be null terminated.
};

struct fromserver_t{
	uint32_t id;
	uint32_t entstateN;
	uint32_t actiondefN;
	uint32_t playerinfoN;
};

struct entstate_t{
	uint32_t mapID;
	vector3d worldPos;
	vector3d rotation;
};

struct actiondef_t{
	uint16_t id;
	char name[ACTION_NAME_SIZE];
	int GLFW_defkey;
};

struct playerinfo_t{
	uint8_t playerID; // each player has unique id
	bool self; // whether this info refers to the player receiving from server. 
	bool left; // if this player left game. 
		// Any issues with sending bools over network?
	uint16_t mapID; // player entity id
	uint8_t nameSz; // Player name size to follow. Allows server to confirm name changes to client.
};

/*********************************************************/

#endif
