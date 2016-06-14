// server.hpp
// Part of project game_engine/flyaround
// Provides a game server instance, which can be connected to be a game client instance.
// Inspired by quake3 engine networking, specifically the use of "snapshots"
// - http://fabiensanglard.net/quake3/network.php

#ifndef SERVER_HPP
#define SERVER_HPP

/********************************************************/

#include <vector>
#include <string>
//#include <thread>
#include "network_definitions.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>

/*********************************************************/

		/**
		*@brief
		*
		*/
class server{

	public:
	
	server();
	
	void setPort(unsigned short int listenport);
	
	int startServer();
	
		/**
		* @brief Returns the number of clients currently connected.
		*
		* @return 0 or greater player account;
		* -1 if server socket has not been created;
		*/
	int getClientCount();
	
		/**
		* @brief Check for connection on listen socket.
		* 
		* @return id of new connection socket on success;
		* -1 on no connection; -2 failure, max players reached;
		* -3 wrong data format/size; -4 other failure;
		*/
		/// ? Only one check for connection per step, as it *should*
		/// take a controlled amount of time.
		/// All networking calls should be designed towards taking a
		/// controlled amount of time while doing their job properly.
	int checkForConnection();
	
	int checkClients();
	
		/**
		* @brief Check for data in a local socket
		* belonging to client connection of socket 
		* descriptor passed.
		*
		* A server instance should maintain all client
		* socket fds contiguously in the m_csocks array from 
		* low to high. eg if 5 clients are connected, their socket 
		* fds should be contained in m_csocks[0-4].
		*
		* @return data type identifier, eg player_events or chat message.
		*/
	int checkClientSocket(int clientid);
	
		/**
		* @brief Get PlayerEvents struct from local socket
		* belonging to client connection of id parsed.
		*
		* @return return 0 on success, places struct in parsed pointer; 
		* 1 if no data was received; 2 if data is incorrect;
		*/
	int receiveClientEvents(unsigned int clientid, struct PlayerEvents *);
	
		/**
		* @brief Get next message from local socket that handles
		* chat. 
		*
		* @return 0 on success, places message in parsed pointer - this 
		* must be allocated to atleast MAX_RECEIVE; 1 if no data received;
		* 2 if next message is longer than MAX_RECEIVE;
		*/
	int receiveClientMessage(unsigned int clientid, char *message);
	
		/**
		* @brief Send struct GameState to each established client.
		*/
	int pushGameState(struct GameState *);
	
	int pushChatMessage(std::string from, std::string message);
	
	private:
		/**
		@brief thread entry method to handle connection with client
		*
		*/
	int getClientMessage(unsigned int fd);
	
	int getClientState(unsigned int fd);
	unsigned short int m_port;
		/// socket addresses for each client connection
	sockaddr m_caddr[GAME_MAX_PLAYERS];
		/// socket file descriptors for each client connection
		/// obsolete
	//int m_csocks[GAME_MAX_PLAYERS];
		/// socket file descriptors currently in use
		/// by a client connection.
	std::vector<int> sfd_inuse;
		/// socket file descriptors free for new
		/// connections. (socket already created).
	std::vector<int> sfd_free;
		/// local server socket address
	sockaddr *m_saddr;
		/// local server socket file descriptor
	int m_ssock;
		/// number of players currently connected
	unsigned int m_ccount;
		/// size of sockaddr structure
	size_t m_addrsz;


};

/*********************************************************/

#endif
