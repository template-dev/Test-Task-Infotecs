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
            for(auto& ch : msg) {
                if((static_cast<int>(ch) & 1) == 0 ) {

                    m_buffer.push(msg);
                }
            }
        }
    }
}

void BufferProcessor::OutputData() {

}