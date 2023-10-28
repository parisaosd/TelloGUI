//
//  udpclient.hpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 05.04.23.
//

#ifndef udpclient_hpp
#define udpclient_hpp

#include <stdio.h>
#include <mutex>

#include <WinSock2.h>


///Udp client sends Udp messages to the drone.
class UdpClient
{
public:
    ///Constructor parameters are address on which drone is listening to commands and its port number.
    UdpClient(const char* address,int port);
    ~UdpClient();
    ///Send message to the drone. Messages are from SDK 2.0 user guide.
    char* send(const char* const message);
private:
    ///Stores file descriptor for created socket.
    SOCKET sock;
    sockaddr_in dest_addr;
    std::mutex _mutex;
};

#endif /* udpclient_hpp */
