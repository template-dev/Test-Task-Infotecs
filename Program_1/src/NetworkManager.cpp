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
    return false;
}

bool NetworkManager::to_disconnect() noexcept {
    return false;
}

bool NetworkManager::to_send() noexcept {
    return false;
}

bool NetworkManager::to_receive() noexcept {
    return false;
}

NetworkManager::~NetworkManager() noexcept {
    if(close(m_clientSocket) == -1) {
        std::cerr << "Failed to close socket." << std::endl;
    }
}