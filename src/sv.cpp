#include <cmath>
#include <iostream>
#include <cstdio>
#include <vector>
#include <unistd.h> // POSIX only
#include <cstring>

#include "vector_math.hpp"
#include "camera.hpp"
#include "obj_model.hpp"
#include "netinst.hpp"
#include "game_data.hpp"
//#include "luaHandle.hpp"

netinst net;

struct player_t{
	int sockfd;
	char name[20];
	vector3d position;
	camera cam;
};
std::vector<player_t> players;

//int fixName(

int checkReceived(unsigned int playerindex, fromplayer_t * rbuf);

int main(int argc, char *argv[]){
	unsigned short int sport = 9845;
	int ssock = net.createSocket(&sport);
	
	int connsock;
	while(1){
		if((connsock = net.checkListen(ssock)) >= 0){
			if(net.waitRead(connsock,3) != 0){
				std::cerr << "Did not receive response from player after connection." << std::endl;
			}
			else{
				player_t player;
				int nameSz = net.tryRead(connsock,(void *) player.name,19,NULL,0);
				player.name[nameSz] = '\0';
				player.sockfd = connsock;
				std::cout << "Name: " << player.name << std::endl;
				players.push_back(player);
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
