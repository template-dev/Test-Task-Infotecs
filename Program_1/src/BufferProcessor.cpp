#include "BufferProcessor.hpp"

BufferProcessor::BufferProcessor()
    : m_buffer{}
    //, m_networkManager{std::make_unique<NetworkManager>("127.0.0.1", 1234)}
    , m_isDataReceived{false}
    , m_mutex{}
    , m_cv{}
{}

void BufferProcessor::inputData() {
    /*std::unique_ptr<NetworkManager> m_networkManager;
    if(!m_networkManager->to_connect()) {
        m_networkManager->to_reconnect();
    }*/
    while(true) {
        std::lock_guard<std::mutex> lock(m_mutex);
        std::string msg;
        std::cout << "Enter a message, please: ";
        std::getline(std::cin, msg);
        if(!msg.empty() && msg.length() <= 64 && std::all_of(msg.begin(), msg.end(), ::isdigit)) {
            std::sort(msg.begin(), msg.end(), std::greater<char>());
            std::string newString;
            for(const char& ch : msg) {
                if((ch & 1) == 0) {
                    newString += "KB";
                }
                else {
                    newString += ch;
                }
            }
            std::cout << newString << std::endl;
            m_buffer = newString;
            m_cv.notify_all();
        }
    }
}

void BufferProcessor::outputData() {
    while(true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] { return m_isDataReceived; });
        if(!m_buffer.empty()) {
            std::string msg = m_buffer;
            m_buffer  = "";
            lock.unlock();
            std::cout << "Data: " << msg << std::endl;
            int count = std::accumulate(msg.begin(), msg.end(), 0, [](int acc, char c) {
                if (std::isdigit(c)) {
                    return ++acc;
                }
                return acc;
            });
            std::cout << "Count: " << count << std::endl;
            //m_networkManager->to_send(count);
        }
    }
}

BufferProcessor::~BufferProcessor() {
    m_isDataReceived = true;
    m_cv.notify_all();
}