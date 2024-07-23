#include "NetworkManager.hpp"

NetworkManager::NetworkManager() noexcept
    : m_serverIp{"127.0.0.1"}
    , m_serverPort{1234}
    , m_clientSocket{0}
    , m_serverAddr{}
{
    m_clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_clientSocket != -1) {
        m_serverAddr.sin_family = AF_INET;
        m_serverAddr.sin_port = htons(m_serverPort);
        inet_pton(AF_INET, m_serverIp, &m_serverAddr.sin_addr);
    } else {
        std::cerr << STATUS_TAG << "Socket creation error.\n";
    }
}

bool NetworkManager::to_connect() noexcept {
    if (connect(m_clientSocket, (struct sockaddr *)&m_serverAddr, sizeof(m_serverAddr)) == -1) {
        std::cerr << STATUS_TAG << "Server connection error.\n";
        close(m_clientSocket);
        return false;
    }
    std::cout << STATUS_TAG << "The connection to the server was successful.\n";
    return true;
}

bool NetworkManager::to_reconnect() noexcept {
    to_disconnect();
    to_connect();
    std::cout << STATUS_TAG << "Reconnection to the server was successful.\n";
    return true;
}

bool NetworkManager::to_disconnect() noexcept {
    if(close(m_clientSocket) == -1) {
        std::cerr << STATUS_TAG << "Failed to disconnect." << std::endl;
        return false;
    }
    return true;
}

bool NetworkManager::to_send(const std::string& message) noexcept {
    if (send(m_clientSocket, message.c_str(), message.size(), 0) == -1) {
        std::cerr << STATUS_TAG << "Error sending data to the server.\n";
        return false;
    }
    return true;
}

bool NetworkManager::to_receive() noexcept {
    std::vector<char> buffer(1024);
    int bytesReceived = recv(m_clientSocket, buffer.data(), buffer.size(), 0);
    if (bytesReceived == -1) {
        std::cerr << STATUS_TAG << "Error when receiving data from the server.\n";
        return false;
    } else if (bytesReceived == 0) {
        std::cout << STATUS_TAG << "The server has shut down.\n";
        return false;
    }
    std::string message(buffer.begin(), buffer.begin() + bytesReceived);
    // continue
    return true;
}

NetworkManager::~NetworkManager() noexcept {
    to_disconnect();
}