#include <thread>
#include "DataProcessor.hpp"

int main(int argc, char* argv[]) {
    std::unique_ptr<DataProcessor> pDataProcessor = std::make_unique<DataProcessor>();
    std::thread input(&DataProcessor::inputData, pDataProcessor.get());
    std::thread output(&DataProcessor::outputData, pDataProcessor.get());
    input.join();
    output.join();

    return EXIT_SUCCESS;
}