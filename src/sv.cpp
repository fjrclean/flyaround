#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unistd.h> // POSIX only
#include <cstring>
#include <cstdlib>

#include "vector_math.hpp"
#include "camera.hpp"
#include "obj_model.hpp"
#include "netinst.hpp"
#include "game_data.hpp"
#include "entity.hpp"
//#include "luaHandle.hpp"
#include <GLFW/glfw3.h> // For default action key


netinst net(30);

//int fixName(

int checkReceived(unsigned int playerindex, fromplayer_t * rbuf);

int checkConnections(std::vector<player_t> &players);

struct player_t{ // move to game_data.hpp ?
	int sockfd;
	char *name;
	unsigned missed; // number of data 'syncs' missed.
	entity ent;
};
std::vector<player_t> players;

#define SV_TMK 60; // The number of successive ticks a player can send no data before being kicked.

		/**
		* @brief
		*
		* @todo construction argument for which interface to bind to.
		*/
class server{
	public:
	server(unsigned short int lport);
	int listen(std::vector<player_t> &players);
	int getPlayer(player_t &player);
	private:
	netinst m_net(30);
	unsigned short int m_lsockfd; // listen socket fd
};

int main(int argc, char *argv[]){
	
	int opt;
	unsigned short int sport = 9845;
	
	while((opt = getopt(argc,argv,"p:")) != -1){
		switch(opt){
			case 'p': // listen port
			/// @todo check optarg is legitimate port, eg max characters.
			sport = atoi(optarg);
			break;
		}
	}


	/******* DEFINE CONTROLS *******/
		// This should be replaced with definition of actions from lua.
		// If lag compensation if pursued, will need some lua capabilities
		// on client side to perform actions locally.
	actiondef_t actions[6];
	actions[0].id = 1;
	actions[0].GLFW_defkey = GLFW_KEY_A;
	actions[1].id = 2;
	actions[1].GLFW_defkey = GLFW_KEY_D;
	actions[2].id = 3;
	actions[2].GLFW_defkey = GLFW_KEY_W;
	actions[3].id = 4;
	actions[3].GLFW_defkey = GLFW_KEY_S;
	actions[4].id = 5;
	actions[4].GLFW_defkey = GLFW_KEY_SPACE;
	actions[5].id = 6;
	actions[5].GLFW_defkey = GLFW_KEY_LEFT_CONTROL;

	/*******************************/

	int connsock;
	while(1){
		
		if(net.checkStep() == 0){
			
		}
		
		if((connsock = net.checkListen(ssock)) >= 0){
			if(net.waitRead(connsock,1) != 0){
				std::cerr << "Did not receive response from player after connection." << std::endl;
			}
			else{
				player_t player;
				int nameSz = net.tryRead(connsock,(void *) player.name,19,NULL,0);
				player.name[nameSz] = '\0';
				player.sockfd = connsock;
				std::cout << "Name: " << player.name << std::endl;
				players.push_back(player);
			
				// Sending action definitions
				fromserver_t froms;
				froms.entstateN = 0;
				froms.actiondefN = 6;
				net.appendBuffer(connsock,(void*)&froms,sizeof(froms));
				net.appendBuffer(connsock,(void*)actions,sizeof(actions));
				net.sendBuffer(connsock);
			}
		}

		for(int i=0; i<players.size(); i++){
			fromplayer_t rbuf;
			memset((void *) &rbuf,0,sizeof(rbuf));
			size_t rbufSz = sizeof(rbuf);
			if(net.tryRead(players[i].sockfd,(void *) &rbuf,rbufSz,NULL,0) > 0){
				checkReceived(i,&rbuf);
			}
		}
		for(int i=0; i<players.size(); i++){
			
		}
	}
}

server::server(unsigned short int lport){
	m_lsockfd = m_net.createSocket(&lport);

}

int server::listen(std::vector<player_t> &players){
	int sockfd;
	if((sockfd = m_net.checkListen(m_lsockfd)) < 0)
		return 1;
	else{
		player_t player;
		player.sockfd = sockfd;
		player.name = NULL;
		player.missed = 0;
		players.push_back(player);
		return 0;
	}
}

int server::getPlayer(player_t &player){
	fromplayer_t recbuf;
	if(m_net.tryRead(player.sockfd,(void *) &recbuf,sizeof(recbuf),NULL,0) <= 0){
		player.missed += 1;
		return -1;
	}
}

int checkReceived(unsigned int playerindex, fromplayer_t *rbuf){
	if(rbuf->actionPress == GM_LEAVE){
		std::cout << players[playerindex].name << " left game." << std::endl;
		players.erase(players.begin()+playerindex);
	}
	else if(rbuf->actionPress == MV_FORWARD){
		std::cout << players[playerindex].name << " pressed forward." << std::endl;
		players[playerindex].cam.inputPress(GLFW_KEY_W);
	}
	
	if(rbuf->actionRelease == MV_FORWARD){
		std::cout << players[playerindex].name << " released forward." << std::endl;
		players[playerindex].cam.inputRelease(GLFW_KEY_W);
	}

	players[playerindex].cam.setRotation(rbuf->camRotate.x,rbuf->camRotate.y,0);
}
