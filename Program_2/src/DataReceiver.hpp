#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <memory>

#define STATUS_TAG "[STATUS]: "

class DataReceiver {
public:
    DataReceiver() noexcept;

    DataReceiver(const DataReceiver&) = delete;
    DataReceiver(DataReceiver&&) = delete;
    DataReceiver& operator=(const DataReceiver&) = delete;
    DataReceiver& operator=(DataReceiver&&) = delete;

    ~DataReceiver() noexcept;

private:
    static void handleClient(int clientSocket, const sockaddr_in& clientAddr);
    bool to_createAndBind();
    void to_listen();
    bool to_stop();
private:
    int m_port;
    int m_socket;
    struct sockaddr_in m_addr;
};