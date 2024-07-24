#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <chrono>
#include <thread>

#define STATUS_TAG "[STATUS]: "

class NetworkManager {
public:
    NetworkManager(const char* ip, int port) noexcept;

    bool to_connect();
    bool to_reconnect();
    bool to_disconnect();
    bool to_send(const std::string& data);

    NetworkManager(const NetworkManager&) = delete;
    NetworkManager(NetworkManager&&) = delete;
    NetworkManager& operator=(const NetworkManager&) = delete;
    NetworkManager& operator=(NetworkManager&&) = delete;
    
    ~NetworkManager() noexcept;

private:
    const char* m_ip;
    int m_port;
    int m_socket;
    struct sockaddr_in m_serverAddr;
    int m_amountOfAttempts;
};