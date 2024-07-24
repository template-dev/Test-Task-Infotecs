#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <numeric>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>
#include "NetworkManager.hpp"

class DataProcessor {
public:
    DataProcessor();
    DataProcessor(const DataProcessor&) = delete;
    DataProcessor(DataProcessor&&) = delete;
    DataProcessor& operator=(const DataProcessor&) = delete;
    DataProcessor& operator=(DataProcessor&&) = delete;
    ~DataProcessor();

    void inputData();
    void outputData();

private:
    std::unique_ptr<NetworkManager> m_networkManager;
    bool m_isDataReceived;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::string m_buffer;
};