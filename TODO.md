* Generated from doxygen using @todo commands in source
* Do not manually add to this file, it will be overwritten!
* This file will be generated with the default make target

Todo List
=========

Member [cinput::addAction](#classcinput_1a5d9268cc46ece13257617019b36d3ad8) (uint16\_t num, char \*name, int GLFW\_defkey)  
Add check for existing mappings in config files

Member [cinput::inputPressed](#classcinput_1ab0f749d8a3bcbb341a2923aba117a383) (int GLFW\_key)  
Better way to find element than for loop? map::find can only find key, not element??

Setting actionPress should be bitwise to allow multiple presses in single [fromplayer\_t](#structfromplayer__t)

Member [cinput::inputReleased](#classcinput_1a0979acd575c69fc31f5ae5db2c249868) (int GLFW\_key)  
Better way to find element than for loop? map::find can only find key, not element??

Setting actionRelease should be bitwise to allow multiple releases in single [fromplayer\_t](#structfromplayer__t)

Member [cinput::mapAction](#classcinput_1ade9614dde31e1d2efc42c6322c7d1c7b) (uint16\_t num, int GLFW\_key)  
Allow multiple inputs to be mapped to single action.

Class [entity](#classentity)  
change to proper mathematics library for vectors. GNU Scientific library?

Member [entity::rotate](#classentity_1ac89126ae768246b41e798745212259f4) (double x, double y, double z)  
change to proper matrix rotation using glm. Using cos, sin, tan method from obsolete camera class for now, with no z axis rotation. Can this be added?

Class [netinst](#classnetinst)  
Replace std::cerr output with calls to a logging class.

Add members to clear receive & send buffers of a socket.

add clear commenting to all class members

will sending data as structs cause problems when using different compilers with different padding?

Member [netinst::appendBuffer](#classnetinst_1a4a94106bf08e12411e524cbcc6b8f977) (int sockfd, void \*data, size\_t datlen)  
buffer size checking

sendto() error checking

Member [netinst::checkListen](#classnetinst_1afaaacd7ed2368bc775da79b4c4931cf8) (int sockfd)  
callback paramter giving details of request which returns accept or reject?

add version checking

Error checking for getsockname()

Error checking for sending blank to establish connection.

Member [netinst::createSocket](#classnetinst_1a309484369e35c1a58449d5dcbf2c5002) (unsigned short int \*lport)  
if lport == NULL, try get socket from m\_sockfree before creating new.

check if lport is legitimate

Member [netinst::joinServer](#classnetinst_1aff70ea4f3cddb1e8bbaf710c5ee61e7c) (unsigned short int rport, char \*ipv4addr)  
Clear local sockfd receive buffer before reading response

Check response source is same as request source

Improve tryRead error checking

Add error checking for createConnection() call.

Member [netinst::sendBuffer](#classnetinst_1a0c3dae11b2e1d2d03ed6d10db806b8cb) (int sockfd)  
buffer size checking

sendto() error checking

Member [netinst::tryRead](#classnetinst_1a127902e80a80f00898f9cf6b0ebee452) (int sockfd, void \*recbuf, size\_t buflen, sockaddr \*addrbuf, size\_t ablen)  
add nuanced error checking for \< 0 for different errno

fix srcAddr vs connection raddr comparison

Class [objModel](#classobjModel)  
Change m\_shapes & m\_materials vectors to static, so obj instances that use the same obj files do not load duplicates. Each [objModel](#classobjModel) object can contain the instances specific properties, eg offset from origin.


