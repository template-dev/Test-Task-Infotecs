#include "DataProcessor.hpp"

DataProcessor::DataProcessor()
    : m_networkManager{std::make_unique<NetworkManager>("127.0.0.1", 12345)}
    , m_buffer{}
    , m_isDataReceived{false}
    , m_mutex{}
    , m_cv{}
{
    m_networkManager->to_connect();
}

void DataProcessor::inputData() {
    while(true) {
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
            std::unique_lock<std::mutex> lock(m_mutex);
            std::cout << "Message: " << newString << std::endl;
            m_buffer = newString;
            m_isDataReceived = true;
            m_cv.notify_all();
        }
    }
}

void DataProcessor::outputData() {
    while(true) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] { return m_isDataReceived; });
        if(!m_buffer.empty()) {
            std::string msg = m_buffer;
            m_buffer  = "";
            m_isDataReceived = false;
            std::cout << "Data: " << msg << std::endl;
            lock.unlock();
            int count = std::accumulate(msg.begin(), msg.end(), 0, [](int acc, char c) {
                if (std::isdigit(c)) {
                    return ++acc;
                }
                return acc;
            });
            std::cout << "Count: " << count << std::endl;
            m_networkManager->to_send(std::to_string(count));
        }
    }
}

DataProcessor::~DataProcessor() {
    m_isDataReceived = true;
    m_cv.notify_all();
    m_networkManager->to_disconnect();
}