//server.cpp

/********************************************************/

#include "server.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>


/********************************************************/

server::server(){
	m_addrsz = sizeof(sockaddr);
	m_ccount = 0;
}

void server::setPort(unsigned short int port){
	m_port = port;
}

int server::startServer(){
	
		// Initialize local socket address
	sockaddr_in *saddr = (sockaddr_in *) malloc(sizeof(sockaddr_in));
	saddr->sin_family = AF_INET;
	saddr->sin_port = htons(m_port);
	saddr->sin_addr.s_addr = INADDR_ANY;
	
		// Convert to general address structure used by functions
	m_saddr = (sockaddr *) saddr;
	
		// Zero socket addr memory for client connections
	memset(m_caddr,0,m_addrsz*GAME_MAX_PLAYERS);
	
		// Create server socket
	if((m_ssock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) < 0){
		std::cout << "Error creating socket: " << errno << std::endl;
		return 1;
	}
	
		// Bind socket to socket address
	if (bind(m_ssock,m_saddr,m_addrsz) < 0){
		std::cout << "Error binding local socket: " << errno << std::endl;
		return 1;
	}
	std::cout << "server started!" << std::endl;
	
	return 0;
	
	
}

int server::getClientCount(){
	// add error checking, eg if server not started
	return m_ccount;
}

int server::checkForConnection(){
	int recvd; // number of bytes read from socket
	//char *recbuf = (char *) malloc(50);
	int rflg = MSG_DONTWAIT;
	struct JoinRequest recbuf;
	size_t recbufs = sizeof(struct JoinRequest);
	memset((void *) &recbuf,0,recbufs);
	
	struct sockaddr caddr;
	socklen_t caddrs = sizeof(caddr);
	
	if((recvd = recvfrom(m_ssock,(void *) &recbuf,recbufs,rflg,&caddr,&caddrs)) == 0){
		return -1; // no connection attempt.
	}
	if(recvd != recbufs){
		return -3; // wrong data format/size.
	}
	std::cout << "Received join request!" << std::endl;
	
	if(m_ccount >= GAME_MAX_PLAYERS){
		return -2; // max connections reached.
	}
	
	unsigned short int connport;
	int connsock; // file descriptor for new connection.
	if(sfd_free.size() > 0){ // if previous connections socket available
		connsock = sfd_free[sfd_free.size()-1];
		sfd_free.pop_back();
		sfd_inuse.push_back(connsock);
		
		struct sockaddr_in connaddr;
		socklen_t connaddrl = sizeof(struct sockaddr);
		if(getsockname(connsock,(struct sockaddr *) &connaddr,&connaddrl) < 0){
			std::cout << "error getting socket port" << std::endl;
			return 1;
		}
		connport = ntohs(connaddr.sin_port);
	}
	else if((connsock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) > 0){
		connport = CONN_PORT_START + m_ccount;
		sockaddr_in *saddr = (sockaddr_in *) malloc(sizeof(sockaddr_in));
		saddr->sin_family = AF_INET;
		saddr->sin_port = htons(connport);
		saddr->sin_addr.s_addr = INADDR_ANY;
		
		if(bind(connsock,(struct sockaddr *) saddr,m_addrsz) < 0){
			return -4; // other failure with socket bind
		}
		m_ccount += 1;
		sfd_inuse.push_back(connsock);
		std::cout << "connsock: " << connsock << std::endl;
	}
	else{
		return -4; // other failure with socket call
	}
	
	struct JoinReply sendbuf;
	size_t sendbufs = sizeof(struct JoinReply);
	memset((void *) &sendbuf,0,sendbufs);
	sendbuf.accepted = true;
	sendbuf.port = connport;
	
	if(sendto(m_ssock,(void *) &sendbuf,sendbufs,0,&caddr,m_addrsz) < 0){
		return -4; // other failure failed send response.
	}
	
	return 0;
}

int server::checkClients(){
	for(int i=0; i<sfd_inuse.size(); i++){
		checkClientSocket(sfd_inuse[i]);
	}
}

int server::checkClientSocket(int fd){
	//std::cout << "checking a connection socket..." << std::endl;
	char *recbuf = (char *) malloc(50);
	int recs;
	
	if((recs = recv(fd,(void *) recbuf,49,MSG_DONTWAIT)) == 0){
		std::cout << "Warning: No data received this step." << std::endl;
		return 1;
	}
	else if(recbuf[0] == 'D'){
		std::cout << "Disconnected!" << std::endl;
			// find file descriptor in sfd_inuse and remove
			for(int i=0; i<sfd_inuse.size(); i++){
				if(sfd_inuse[i] == fd){
					sfd_inuse.erase(sfd_inuse.begin()+i);
					sfd_free.push_back(fd);
					break;
				}
			}
		return 0;
	}
	else if(recs == -1){
		//std::cout << "Error check client: " << errno << std::endl;
		return 1;
	}
	
	free((void *) recbuf);

}

/*int server::receiveClient(){
		// typebuffer to store DType.
		// This will determine how many more bytes to be read
		// for this piece of data.
	//std::cout << "reading received..." << std::endl;
	char *recbuf = (char *) malloc(50);
	int recs;
	
	if((recs = recv(m_ssock,(void *) recbuf,1,MSG_DONTWAIT)) == 0){
		std::cout << "Warning: No data received this step." << std::endl;
		return 1;
	}
	else if(recbuf[0] == 'G'){
		std::cout << "Message!" << std::endl;
		return 0;
	}
	else{
		//std::cout << "Error: " << errno << std::endl;
		return 1;
	}
}*/

/********************************************************/
