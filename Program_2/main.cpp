#include <iostream>
#include <memory>
#include "src/DataReceiver.hpp"

int main(int argc, char* argv[]) {
    std::unique_ptr<DataReceiver> pDataReceiver = std::make_unique<DataReceiver>();
    pDataReceiver->to_start();

    return EXIT_SUCCESS;
}