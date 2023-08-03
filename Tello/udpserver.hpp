//
//  udpserver.hpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 31.08.23.
//

#ifndef udpserver_hpp
#define udpserver_hpp
#include <stdio.h>

#include <WinSock2.h>

///Udp server gets video from the drone.
class UdpServer
{
public:
    UdpServer(const char* address, int port);
    ~UdpServer();
    char* getMessage();
private:
    ///Stores file descriptor for created socket.
    SOCKET sock;
    sockaddr_in dest_addr;
};

#endif /* udpserver_hpp */
