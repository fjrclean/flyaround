//server.cpp

/********************************************************/

#include "client.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <cstdlib>
#include <cerrno>
#include <sys/time.h>

/********************************************************/

int client::connectServer(unsigned short int sport){
	m_addrsz = sizeof(sockaddr);
		
		// Initialize server listen socket address
	sockaddr_in *saddr = (sockaddr_in *) malloc(sizeof(sockaddr_in));
	saddr->sin_family = AF_INET;
	saddr->sin_port = htons(sport);
	saddr->sin_addr.s_addr = INADDR_ANY;
	
		// Convert to general address structure used by functions
	m_saddr = (sockaddr *) saddr;

		// Create client socket
	if((m_csock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP)) < 0){
		std::cout << "Error creating socket: " << errno << std::endl;
		return 1;
	}
	
		// Send connection request to server
	std::cout << "Requesting connection to server..." << std::endl;
	struct JoinRequest req;
	size_t reqs = sizeof(struct JoinRequest);
	req.type = NORMAL; 
	if(sendto(m_csock,(void *) &req,reqs,0,m_saddr,m_addrsz) < 0){
		std::cout << "Error sending connection request: " << errno <<std::endl;
		return 1;
	}
	
		// Wait for response from server
	struct timeval wtime; // wait for WAIT_RESPONSE seconds.
	wtime.tv_sec = WAIT_RESPONSE;
	wtime.tv_usec = 0;
	
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(m_csock,&fds);
	int retval;
	if((retval = select(m_csock+1,&fds,NULL,NULL,&wtime)) < 0){
		std::cout << "Error getting response: " << errno << std::endl;
		return 1;
	}
	else if(retval == 0){
		std::cout << "Server did not respond in time." << std::endl;
		return 1;
	}
	
		// Get data from now readable m_csock. 
		// todo: check if it is from sockaddr
		// request was sent do.
		// ? Create loop to check received data until it is from
		// requestee or hits a check limit.
	struct JoinReply rep;
	size_t reps = sizeof(struct JoinReply);
	memset((void *) &rep,0,reps); // zero reply buffer
	int flgs = 0;
	recv(m_csock,(void *) &rep,reps,flgs); // change to recvfrom()
	
		// check if accepted
	if(rep.accepted == true){
		std::cout << "ACCEPTED on port " << rep.port << std::endl;
		sockaddr_in *connaddr = (sockaddr_in *) malloc(sizeof(sockaddr_in));
		connaddr->sin_family = AF_INET;
		connaddr->sin_port = htons(rep.port);
		connaddr->sin_addr.s_addr = INADDR_ANY;
		// Convert to general address structure used by functions
		m_connaddr = (struct sockaddr *) connaddr;
	}
	else{
		std::cout << "DENIED!" << std::endl;
	}
	
	// todo: check if valid port
	
	
	std::cout << "Connected to server!" << std::endl;
	
	return 0;
	
}

int client::disconnectServer(){
	char sendbuf = 'D';
	int flgs = 0;
	if(sendto(m_csock,(void *) &sendbuf,1,flgs,m_connaddr,m_addrsz) < 0){
		std::cout << "Error sending disconnect: " << errno << std::endl;
		return 1;
	}
}

int client::sendServer(){
	char *sendbuf = (char *) malloc(50);
	sendbuf[0] = 'G';
	sendbuf[1] = '\0';
	
	if (sendto(m_csock,(void *) sendbuf,1,0,m_connaddr,m_addrsz) < 0){
		std::cout << "Error sending from client: " << errno << std::endl;
		return 1;
	}
	
}

/********************************************************/
