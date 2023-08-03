//
//  udpserver.cpp
//
//  Created by Parisa Ostadzadeh on 31.08.23.
//
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "udpserver.hpp"

#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <thread>

UdpServer::UdpServer(const char* address, int port) {
    // Create a socket
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock < 0) {
        std::cerr << "Failed to create socket" << std::endl;
    }

    std::memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_addr.S_un.S_addr = inet_addr(address);
    dest_addr.sin_port = htons(port);
}

UdpServer::~UdpServer() {
    std::cout << "Socket closed";
    closesocket(sock);
    WSACleanup();
}

char* UdpServer::getMessage() {
    struct sockaddr_in cliaddr;

    static char buffer[1024];
    int addrlen = sizeof(cliaddr);
    long received_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &addrlen);
    if (received_bytes < 0) {
        std::cerr << "Failed to receive message" << std::endl;
    };
    //buffer[received_bytes] = '\0';
    std::cout << "Message received: " << buffer << std::endl;
    return buffer;
}
