// netinst.hpp
// Part of project game_engine/flyaround
// Provides a "Network Instance" to listen for & make connections,
// and receive & send on these connections. Keeps track of
// connections in the form of local sockets and (if connected) their
// remote addresses.
// Does not implement higher-level features such as reliability,
// which is done through the "snapshot" system. Only understands
// special data structures for managing connections & general
// data buffers, no "game specific" data.

#ifndef NETINST_HPP
#define NETINST_HPP

/*********************************************************/

#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>

#include <sys/time.h>

/*********************************************************/

#define NET_MXCONN 16 // maximum connections at once
#define NET_SBUFSZ 1400 // size of send buffer in bytes?

/*********************************************************/

struct joinreq_t{
	int type;
	float version;
};

struct joinrep_t{
	bool accept; // if accepted
	unsigned short int connport; // port to connect to
	uint32_t connip; // ip to connect to in network byte order
};

struct conn_t{
	int sockfd; // local socket fd
		// remote IPv4 address
	char *remIPv4; // human readable
	sockaddr raddr; // socket usable
	char *sendbuf[NET_SBUFSZ];
	size_t sendbufused;
};

/*********************************************************/

		/**
		* @brief
		*
		* @todo Replace std::cerr output with calls to
		* a logging class.
		*
		* @todo Add members to clear receive & send buffers
		* of a socket.
		*
		* @todo add clear commenting to all class members
		*
		* @todo will sending data as structs cause problems
		* when using different compilers with different padding?
		*/
class netinst{

	public:
		/**
		*
		* @param tick The number of steps per second when using
		* checkStep().
		*/
	netinst(double tickrate);
	
		/**
		* @brief Used to perform an action a consistent number
		* of times per second.
		*
		* @return 0 minimum time for step has past, new step may
		* be run; 1 not time for new step; -1 error;
		*/
	int checkStep();
		/**
		* @brief Creates local socket & binds to address.
		* Should be used to create listening socket on
		* server which is then parsed to checkListen. OR
		* socket on client which is passed to joinServer().
		* Used internally to create sockets for each 
		* client connection.
		*
		* @param lport - if NULL, socket not bound to local
		* address. System will automatically bind if sockfd
		* parsed to joinServer(), sendBuffer() or sendDatae().
		*
		* @return success returns socket file descriptor
		* as positive int; -1 failure, check log
		* for details.
		*/
	int createSocket(unsigned short int *lport);
	
		/**
		* @brief Checks for at most one joinreq_t struct
		* on socket per call. Based on request and info
		* such as NET_MXCONN, ipbans etc accepts or rejects
		* connection, sending joinrep_t struct.
		* If accept, calls createSocket() or uses existing.
		*
		* An existing "free" socket is used if it's 
		* previous client has disconnected. This is done
		* using m_sockfree & m_sockused vectors.
		*
		* @todo callback paramter giving details of request
		* which returns accept or reject?
		*
		* @return on accept, positive int file descriptor
		* of new connection; -1 failure, check
		* log for details; -2 reject, log has details;
		* -3 socket not bound to local address.
		*/
	int checkListen(int sockfd);
	
		/**
		* @brief Sends joinreq_t to address, waits for reply.
		* If accepted, creates connection to replied address,
		* using parsed sockfd. 
		*
		* @todo Clear local sockfd receive buffer before 
		* reading response
		*
		* @return positive int sockfd on accept; -2 on reject, check log;
		* -1 failure, check log;
		*/
	int joinServer(unsigned short int rport, char *ipv4addr);
	
		/**
		* @brief Leaves a "connection" - moving the sockfd
		* from m_sockused to m_sockfree. Communication 
		* between client/server about disconnect occurs
		* at higher level.
		*
		* @return 0 on success; 1 if sockfd was not part of
		* connection; -1 on failure, check log.
		*/
	int leaveConnection(int sockfd);
	
		/**
		* @brief Appends data to a connected sockets buffer.
		* Allows arbitrary amount of data to be sent in
		* single datagram, so long as total size under
		* NET_SBUFSZ. Uses the MSG_MORE flag with sendto().
		*
		* @return 0 on success; -1 on failure (eg socket 
		* does not exist/not connected), check log;
		* positive non-zero indicates not enough room for
		* datlen, with number returned the room free.
		*/
	int appendBuffer(int sockfd, void *data, size_t datlen);
	
		/**
		* @brief Send the buffer for a connected socket.
		* Uses sendto() without MSG_MORE flag.
		*
		* @return 0 on success; -1 on failure, check log.
		*/
	int sendBuffer(int sockfd);
	
		/**
		* @brief Send data on unconnected socket.
		* 
		* @return 0 on success; -1 on failure (eg socket
		* does not exist/is connected), check log;
		*/
 	int sendData(int sockfd, sockaddr *destaddr, void *data, size_t datlen);
		/**
		* @brief Get ips of connected socket.
		*
		* @return
		*/
	int getIPv4(int sockfd, void *remote, size_t remlen, void *local, size_t loclen);

		/**
		* @brief Waits until a socket is readable
		* Uses select() to wait for reading on socket.
		*
		* @param seconds - the maximum time to wait.
		*
		* @return 0 on readable; 1 on not readable;
		* -1 failure, check log;
		*/
	int waitRead(int sockfd, int seconds);
	
		/**
		* @brief Reads from socket, returning immeditately.
		* If socket is connected, checks to see if received
		* data is from remote connection. If not, error 
		* returned.
		*
		* @param recbuf should be as bif as NET_SBUFSZ;
		*
		* @addrbuf sockaddr of source is placed here if not NULL.
		*
		* @ablen size of addrbuf. If addrbuf is NULL, this is ignored.
		*
		* @return positive int amount read (0 if nothing to read);
		* -1 failure, check log; -2 recbuf too small.
		*/
	int tryRead(int sockfd, void *recbuf, size_t buflen, sockaddr *addrbuf, size_t ablen);

	private:
	std::vector<conn_t> m_sockused;
	std::vector<int> m_sockfree;

	timeval m_tstart; // start time of current step;
	long int m_tick; // Duration of each step
	
		/**
		* @brief Check if a socket is connected
		* to a remote address.
		*
		* @return m_sockused index of connection
		* if connected; -2 if unconnected;
		* -1 on error, check log;
		*/
	int checkConnected(int sockfd);
	
		/**
		* @brief Add a socket (new or from free pool)
		* to the connections pool.
		*
		* @return 0 on success;
		* -1 on failure (eg NET_MXCONN reached),
		* check log.
		*/
	int createConnection(int sockfd, sockaddr *remAddr);

};

/*********************************************************/

#endif
