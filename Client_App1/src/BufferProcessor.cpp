#include "BufferProcessor.hpp"

void BufferProcessor::InputData() {
    while(true) {
        std::string msg;
        std::cout << "Enter a message, please: ";
        std::getline(std::cin, msg);
        if(msg.size() <= 64 && std::all_of(msg.begin(), msg.end(), ::isdigit)) {
            std::sort(msg.begin(), msg.end(), std::greater<char>());
            for(auto it = msg.begin(); it != msg.end(); ++it) {
                if((static_cast<int>(*it) & 1) == 0 ) {
                    *it = 'K';
                    it = msg.insert(std::next(it), 'B');
                }
            }
            m_buffer.push(msg);
        }
    }
}

void BufferProcessor::OutputData() {
    while(true) {
        if(!m_buffer.empty()) {
            std::string msg = m_buffer.front();
            m_buffer.pop();
            std::cout << "Data: " << msg << std::endl;
            int count = std::accumulate(msg.begin(), msg.end(), 0, [](int acc, char c) {
                if (std::isdigit(c)) {
                    return ++acc;
                }
                return acc;
            });
        } else {
            // Добавим паузу, чтобы избежать избыточного использования CPU
            // Must change for multithreading
            // std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
}