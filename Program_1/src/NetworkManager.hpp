#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#define STATUS_TAG "[STATUS]: "

class NetworkManager {
public:
    NetworkManager(const char ip, int port) noexcept;

    bool to_connect() noexcept;
    bool to_reconnect() noexcept;
    bool to_disconnect() noexcept;
    bool to_send(int amount) noexcept;
    bool to_receive() noexcept;

    NetworkManager(const NetworkManager&) = delete;
    NetworkManager(NetworkManager&&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;
    NetworkManager& operator=(NetworkManager&&) = delete;
    
    ~NetworkManager() noexcept;

private:
    const char* m_serverIp;
    int m_serverPort;
    int m_clientSocket;
    struct sockaddr_in m_serverAddr;
    int m_amountOfAttempts;
};