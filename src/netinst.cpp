//netinst.cpp

/********************************************************/

#include "netinst.hpp"
#include <iostream>
#include <cstring>
#include <cerrno>

/********************************************************/

netinst::netinst(double tickrate){
	m_tick = (1 / (double) tickrate) * 1000000; // Number of milliseconds for tickrate / 1 second.
	gettimeofday(&m_tstart,NULL); // Get initial time.
}

int netinst::checkStep(){
	timeval tcurrent, diff;
	gettimeofday(&tcurrent,NULL);
	timersub(&tcurrent,&m_tstart,&diff);
	if(diff.tv_sec >= 1 || diff.tv_usec >= m_tick){
		gettimeofday(&m_tstart,NULL); // Get start time of new step.
		return 0;
	}
	
	return 1;
}

int netinst::createSocket(unsigned short int *lport){
	int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sockfd < 0){
		std::cerr << "Error creating socket." << std::endl;
		return -1;
	}
	/// @todo if lport == NULL, try get socket from m_sockfree 
	/// before creating new.

	sockaddr_in lAddr;
	size_t lAddrSz = sizeof(sockaddr_in);
	lAddr.sin_family = AF_INET;
	lAddr.sin_addr.s_addr = INADDR_ANY;
	
	unsigned short int bndport = 0;
	if(lport != NULL){
		/// @todo check if lport is legitimate
		bndport = *lport;
	}
	lAddr.sin_port = htons(bndport);

	std::cerr << "Binding to port: " << bndport << std::endl;
	if(bind(sockfd,(sockaddr *) &lAddr,lAddrSz) < 0){
		std::cerr << "Error binding socket." << std::endl;
		return -1;
	}

	return sockfd;
}

int netinst::joinServer(unsigned short int rport, char *ipv4addr){
	joinreq_t req;
	req.version = 0.0;
	req.type = 5;
	
	/*if(checkConnected(sockfd) >= 0){
		std::cerr << "Error: cannot join, already connected." << std::endl;
		return -1;
	}*/
	
	sockaddr_in sAddr;
	size_t sAddrSz = sizeof(sockaddr);
	sAddr.sin_family = AF_INET;
	sAddr.sin_port = htons(rport);
	if(inet_aton(ipv4addr,&sAddr.sin_addr) == 0){
		std::cerr << "Error: invalid ipv4addr joining server." << std::endl;
		return -1;
	}
	
	int sockfd = createSocket(NULL);
	
	size_t dlen = sizeof(joinreq_t);
	if(sendData(sockfd,(sockaddr *) &sAddr,(void *) &req,dlen) < 0){
		return -1;
	}
	
	joinrep_t rep;
	memset((void*) &rep,0,sizeof(rep));
	if(waitRead(sockfd,10) != 0){
		std::cerr << "Warning: did not receive reply from server" << std::endl;
		return -1;
	}
	else{
		/// @todo Check response source is same as request source
		/// @todo Improve tryRead error checking
		if(tryRead(sockfd,(void *) &rep,sizeof(rep),NULL,0) <= 0){
			std::cerr << "Error with joinrep received" << std::endl;
			//return -1;
		}
	}
	
	if(rep.accept == true){
		std::cout << "Acceped on server" << std::endl;
		sAddr.sin_port = rep.connport;//htons(rep.connport);
		createConnection(sockfd,(sockaddr *) &sAddr);
		return sockfd;
		/// @todo Add error checking for createConnection() call.
	}
	else{
		std::cerr << "Rejected by server" << std::endl;
		return -2;
	}
	
	
}

int netinst::checkListen(int sockfd){
	sockaddr srcAddr;
	joinreq_t req;
	memset((void *) &req,0,sizeof(req));
	if(tryRead(sockfd,(void *) &req,sizeof(req),&srcAddr,sizeof(srcAddr)) <= 0){
		return -1;
	}
	
	int connsock = -1;
	joinrep_t rep;
	memset((void *) &rep,0,sizeof(rep));
	if(m_sockused.size() >= NET_MXCONN){
		std::cerr << "connection rejection: max reached." << std::endl;
		rep.accept = false;
	}
	else{ /// @todo add version checking
		connsock = createSocket(NULL);
		
		sockaddr connAddr;
		size_t connAddrSz = sizeof(connAddr);
		/// @todo Error checking for getsockname()
		getsockname(connsock,&connAddr,(socklen_t *) &connAddrSz);
		sockaddr_in *connAddr_in = (sockaddr_in *) &connAddr;
		rep.accept = true;
		rep.connport = connAddr_in->sin_port;
		rep.connip = connAddr_in->sin_addr.s_addr;
		std::cerr << "connection accepted" << std::endl;
		createConnection(connsock,&srcAddr);
	}
	size_t dlen = sizeof(req);
	if(sendData(sockfd,&srcAddr,(void *) &rep,dlen) <0){
		return -1;
	}

	char blank = 0;
	/// @todo Error checking for sending blank to establish connection.
	//sendData(connsock,&srcAddr,(void *) &blank,1);

	return connsock;
}

int netinst::sendData(int sockfd, sockaddr *destaddr, void *data, size_t datlen){
	if(checkConnected(sockfd) >= 0){
		std::cerr << "Error: cannot send non-buffer data on connected socket." << std::endl;
		return -1;
	}
	
	if(datlen > NET_SBUFSZ){
		std::cerr << "Error: Sending data too big for single dgram" << std::endl;
		return -1;
	}
	
	int flgs = 0;
	socklen_t dAddrSz = sizeof(*destaddr);
	int i = sendto(sockfd,data,datlen,flgs,destaddr,dAddrSz);
	if(i < 0){
		std::cerr << "Error on sendto." << std::endl;
		return -1;
	}
	
	return 0;
}

int netinst::appendBuffer(int sockfd, void *data, size_t datlen){
	int index;
	if((index = checkConnected(sockfd)) < 0){
		std::cerr << "Socket buffer cannot be appended, not connected." << std::endl;
		return -1;
	}
	
	/// @todo buffer size checking
	
	int flgs = MSG_MORE;
	sockaddr destaddr = m_sockused[index].raddr;
	socklen_t dAddrSz = sizeof(destaddr);
	if(sendto(sockfd,data,datlen,flgs,&destaddr,dAddrSz) < 0)
		return -1;
	m_sockused[index].sendbufused += datlen;
	/// @todo sendto() error checking
	
	return 0;
}

int netinst::sendBuffer(int sockfd){
	int index;
	if((index = checkConnected(sockfd)) < 0){
		std::cerr << "Socket buffer cannot be appended, not connected." << std::endl;
		return -1;
	}
	
	/// @todo buffer size checking
	
	int flgs = 0;
	sockaddr destaddr = m_sockused[index].raddr;
	socklen_t dAddrSz = sizeof(destaddr);
	sendto(sockfd,NULL,0,flgs,&destaddr,dAddrSz);
	/// @todo sendto() error checking
	
	return 0;

}

int netinst::waitRead(int sockfd, int seconds){
	fd_set rfds;
	struct timeval tv;
	
	FD_ZERO(&rfds);
	FD_SET(sockfd,&rfds);
	
	tv.tv_sec = seconds;
	tv.tv_usec = 0;
	
	int i;
	if((i = select(sockfd+1,&rfds,NULL,NULL,&tv)) < 0){
		std::cerr << "Error waiting for read with select()" << std::endl;
		return -1;
	}
	if(i == 0){
		return 1;
	}
	
	return 0;
}

int netinst::tryRead(int sockfd, void *recbuf, size_t buflen, sockaddr *addrbuf, size_t ablen){
	int flgs = MSG_DONTWAIT | MSG_TRUNC;// | MSG_WAITALL;
	sockaddr srcAddr;
	socklen_t srcAddrSz = sizeof(srcAddr);
	int i;
	if((i = recvfrom(sockfd,recbuf,buflen,flgs,&srcAddr,&srcAddrSz)) < 0){
		//std::cerr << "Error: recvfrom: " << errno << std::endl;
		return -1;
	}
	/// @todo add nuanced error checking for < 0 for different errno
	
	if(addrbuf != NULL){
		if(ablen < srcAddrSz){
			std::cerr << "addrbuf len too small." << std::endl;
		}
		else
			*addrbuf = srcAddr;
	}
	
	/*if(i == 0){
		//nothing to read
		return 1;
	}*/
	if(i > buflen){
		std::cerr << "Error: recieve buffer too small" << std::endl;
		return -2;
	}
	
	int j;
	if((j = checkConnected(sockfd)) >= 0){
		sockaddr_in *srcAddrIn = (sockaddr_in *) &srcAddr;
		
		/*if(m_sockused[i].raddr != srcAddr){
			std::cerr << "Error: received data from wrong address on connection." << std::endl;
			return -1;
		}*/ /// @todo fix srcAddr vs connection raddr comparison
	}
	
	return i;
}

// private

int netinst::checkConnected(int sockfd){
	if(m_sockused.size() == 0)
		return -2; // not connected
	
	for(int i=0; i<m_sockused.size(); i++){
		if(m_sockused[i].sockfd == sockfd)
			return i; // connected
	}
	
	return -2; // not connected
}

int netinst::createConnection(int sockfd, sockaddr *remAddr){
	if(m_sockused.size() >= NET_MXCONN){
		std::cerr << "Cannot create connection, max reached." << std::endl;
		return -1;
	}
	
	/// @todo check sockfd not already part of connection.
	
	/// @todo accessing struct member from conversion without memory allocation?
	//sockaddr_in = (structaddr_in) *remAddr;
	//inet_ntoa(r
	
	conn_t c;
	c.sockfd = sockfd;
	c.raddr = *remAddr;
	c.sendbufused = 0;
	m_sockused.push_back(c);
	
	return 0;
}

int netinst::leaveConnection(int sockfd){
	for(int i=0; i<m_sockused.size(); i++){
		if(m_sockused[i].sockfd == sockfd){
			m_sockused.erase(m_sockused.begin()+i);
			m_sockfree.push_back(sockfd);
			return 0;
		}
	}
	return 1;
}

/********************************************************/
