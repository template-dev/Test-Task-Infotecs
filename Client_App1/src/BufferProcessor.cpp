#include "BufferProcessor.hpp"

BufferProcessor::BufferProcessor() {

}

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

}