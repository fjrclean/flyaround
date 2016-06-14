// client.hpp
// Part of project game_engine/flyaround
// Provides a game client, which can be connect to a server instance.

#ifndef CLIENT_HPP
#define CLIENT_HPP

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
class client{

	public:
	
	//client();
		
	int connectServer(unsigned short int sport);

	int disconnectServer();
	
		/**
		* @brief Check for packets in local socket,
		* take action depending on the type of data received.
		*/
	int sendServer();
	
	private:
	
		/// socket file descriptor for this client.
	int m_csock;
		/// address of server listen port.
	sockaddr *m_saddr;
		/// address of server connection.
	sockaddr *m_connaddr;
		/// size of sockaddr structure
	size_t m_addrsz;


};

/*********************************************************/

#endif
