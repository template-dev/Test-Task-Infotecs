#include <thread>
#include "src/BufferProcessor.hpp"

int main(int argc, char* argv[]) {
    std::unique_ptr<BufferProcessor> pBufferProcessor = std::make_unique<BufferProcessor>();
    
    pBufferProcessor->inputData();
    //std::thread input(&BufferProcessor::inputData, pBufferProcessor.get());
    std::thread output(&BufferProcessor::outputData, pBufferProcessor.get());

    //input.join();
    output.join();

    return EXIT_SUCCESS;
}