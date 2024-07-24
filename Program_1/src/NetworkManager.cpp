#include "NetworkManager.hpp"

NetworkManager::NetworkManager(const char* ip, int port) noexcept
    : m_ip{ip}
    , m_port{port}
    , m_socket{-1}
    , m_serverAddr{}
    , m_amountOfAttempts{3}
{
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket != -1) {
        m_serverAddr.sin_family = AF_INET;
        m_serverAddr.sin_port = htons(m_port);
        inet_pton(AF_INET, m_ip, &m_serverAddr.sin_addr);
    } else {
        std::cerr << STATUS_TAG << "Socket creation error." << std::endl;
    }
}

bool NetworkManager::to_connect() {
    if (connect(m_socket, (struct sockaddr *)&m_serverAddr, sizeof(m_serverAddr)) == -1) {
        std::cerr << STATUS_TAG << "Server connection error." << std::endl;
        return to_reconnect();
    }
    std::cout << STATUS_TAG << "The connection to the server was successful." << std::endl;
    return false;
}

bool NetworkManager::to_reconnect() {
    while(m_amountOfAttempts) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << STATUS_TAG << "Number of connection attempts: " << m_amountOfAttempts-- << std::endl;
        if(!to_disconnect()) {
            return false;
        }
        if(!to_connect() && m_amountOfAttempts == 0) {
            return false;
        }
    }
    std::cout << STATUS_TAG << "Reconnection to the server was successful." << std::endl;
    return true;
}

bool NetworkManager::to_disconnect() {
    if(close(m_socket) == -1) {
        std::cerr << STATUS_TAG << "Failed to disconnect." << std::endl;
        return false;
    }
    m_socket = -1;
    return true;
}

bool NetworkManager::to_send(const std::string& data) {
    if (send(m_socket, data.c_str(), data.size(), 0) == -1) {
        std::cerr << STATUS_TAG << "Error sending data to the server." << std::endl;
        return false;
    }
    return true;
}

NetworkManager::~NetworkManager() noexcept {
    if (m_socket != -1) {
        to_disconnect();
    }
}