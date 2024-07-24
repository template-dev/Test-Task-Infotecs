#include "DataReceiver.hpp"

DataReceiver::DataReceiver() noexcept
    : m_port{12345}
    , m_socket{-1}
    , m_addr{}
{
    to_createAndBind();
    to_listen();
}

bool DataReceiver::to_createAndBind() {
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == -1) {
        std::cerr << STATUS_TAG << "Socket creation error\n";
        return false;
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(m_port);
    m_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_socket, (struct sockaddr *)&m_addr, sizeof(m_addr)) == -1) {
        std::cerr << STATUS_TAG << "Socket binding error\n";
        close(m_socket);
        return false;
    }
    return true;
}

void DataReceiver::to_listen() {
    if (listen(m_socket, 10) == -1) {
        std::cerr << STATUS_TAG << "Socket listening error\n";
        close(m_socket);
        return;
    }

    std::cout << STATUS_TAG << "Waiting for data...\n";

    while (true) {
        struct sockaddr_in clientAddr;
        socklen_t clientAddrLen = sizeof(clientAddr);
        int clientSocket = accept(m_socket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            std::cerr << STATUS_TAG << "Connection acceptance error\n";
            continue;
        }

        std::cout << STATUS_TAG << "A client with an IP has connected: [" << inet_ntoa(clientAddr.sin_addr) << "], port: [" << ntohs(clientAddr.sin_port) << "]" << std::endl;

        std::thread clientThread(handleClient, clientSocket, clientAddr);
        clientThread.detach();
    }
}

bool DataReceiver::to_stop() {
    if(close(m_socket) == -1) {
        std::cerr << STATUS_TAG << "Failed to disconnect." << std::endl;
        return false;
    }
    return true;
}

void DataReceiver::handleClient(int clientSocket, const sockaddr_in& clientAddr) {
    while (true) {
        char buffer[1024];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) {
            if (bytesReceived == 0)
                std::cout << STATUS_TAG << "The client has disconnected [" << inet_ntoa(clientAddr.sin_addr) << "]:[" << ntohs(clientAddr.sin_port) << "]" << std::endl;
            else
                std::cerr << STATUS_TAG << "Error when receiving data from the client [" << inet_ntoa(clientAddr.sin_addr) << "]:[" << ntohs(clientAddr.sin_port) << "]" << std::endl;
            close(clientSocket);
            break;
        }
        std::string data(buffer, bytesReceived);
        std::cout << STATUS_TAG << "A message has been received from the client [" << inet_ntoa(clientAddr.sin_addr) << "]:[" << ntohs(clientAddr.sin_port) << "]" << std::endl;
        int number = std::stoll(data);
        std::cout << "DATA: " << number << std::endl;
        if (data.length() > 2 && number % 32 == 0) {
            std::cout << STATUS_TAG << "Received valid data: " << data << std::endl;
        } else {
            std::cerr << STATUS_TAG << "Error: Invalid data length or format!" << std::endl;
        }
    }
}

DataReceiver::~DataReceiver() noexcept {
    to_stop();
}