#include <memory>
#include "src/BufferProcessor.hpp"

int main(int argc, char* argv[]) {
    std::unique_ptr<BufferProcessor> pBufferProcessor = std::make_unique<BufferProcessor>();
    pBufferProcessor->start();

    return EXIT_SUCCESS;
}