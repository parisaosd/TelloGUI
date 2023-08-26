//
//  udpclient.cpp
//  TestMessage
//
//  Created by Parisa Ostadzadeh on 05.04.23.
//
#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "udpclient.hpp"

#include <iostream>
#include <cstring>
#include <cstdio>
#include <sys/types.h>
#include <thread>

UdpClient::UdpClient(const char* address,int port) {
    //Redirect logging from console to a file
    //freopen("UdpClientLog.txt", "w", stdout);
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
UdpClient::~UdpClient() {
    std::cout << "Socket closed";
    closesocket(sock);
    WSACleanup();
}
/// To send commands/messages to the drone
char* UdpClient::send(const char* const message) {
    size_t message_len = std::strlen(message);
    long sent_bytes = sendto(sock, message, message_len, 0, reinterpret_cast<sockaddr*>(&dest_addr), sizeof(dest_addr));
    if (sent_bytes < 0) {
        std::cerr << "Failed to send message" << std::endl;
    }
    std::cout << "Message sent: " << message << std::endl;
    static char buffer[1024];
    int addrlen = sizeof(dest_addr);
    long received_bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&dest_addr, &addrlen);
    if (received_bytes < 0) {
        std::cerr << "Failed to receive message" << std::endl;
    };
    buffer[received_bytes] = '\0';
    std::cout << "Message received: " << buffer << std::endl;
    return buffer;
}
