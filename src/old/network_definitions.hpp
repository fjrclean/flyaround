//network_definitions.hpp
//Part of project game_engine/flyaround
// Provides definitions for how gamestate information & events are
// sent between clients & servers.

#ifndef NETWORK_DEFINITIONS_HPP
#define NETWORK_DEFINITIONS_HPP

/********************************************************/


/*********************************************************/

#define GAME_MAX_PLAYERS 16
	// Maximum number of data read from socket per step.
#define MAX_RECEIVE 50;

	// Each connected client connection has it's own socket
	// on server. This is the first port to be used for these
	// sockets, up to not including CONN_PORT_START + GAME_MAX_PLAYERS.
	// Server should reuse ports in this range when one client
	// disconnects and another joins.
#define CONN_PORT_START 8015

	// Maximum time to wait for a response in seconds.
#define WAIT_RESPONSE 10;

// Identifier for type of data that will follow.
enum DType{
	GAME_STATE,
	CLIENT_JOIN,
	CLIENT_STATE,
	MESSAGE_START,
	MESSAGE_END,
	CLIENT_LEAVE
};

enum JoinType{
	NORMAL,
	SPECTATOR
};

#define SPORT 7645
#define CPORT 7643

/*********************************************************/

// All data for a frame/step should be sent in a single send call.
// This ensures each peer only requires 1 read per frame, and will
// always receive important data (eg gamestate) before other (eg chat).
// A single datagram (from single send) will have a max. So important 
// data should always be first placed in bugger, and other 
// data if it can fit.
// If other data cannot fit, send it next step/frame.

struct PlayerState{
	double xPos, yPos, zPos;
};

struct GameState{
	DType type;
	PlayerState players[GAME_MAX_PLAYERS];
};

struct PlayerEvents{
	DType type;
	//actions, yes or no
	bool mvForward;
	bool mvBackward;
	bool mvLeft;
	bool mvRight;
};

struct JoinRequest{
		// 0 for normal, 1 for spectator.
	int type;
		// account details, server privileges, etc
};

struct JoinReply{
	bool accepted; //
	unsigned short int port; // connect to if accepted.
	unsigned int clientid;
};

/*********************************************************/

#endif
