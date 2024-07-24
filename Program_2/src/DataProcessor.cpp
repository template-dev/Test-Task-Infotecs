#include "DataProcessor.hpp"

void DataProcessor::processData(const std::string& receivedData) {
    if (receivedData.length() > 2 && std::stoi(receivedData) % 32 == 0)
      std::cout << "Received valid data: " << receivedData << std::endl;
    else
      std::cerr << "Error: Invalid data length or format!" << std::endl;
}