#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <numeric>
#include <memory>
#include <mutex>
#include <condition_variable>
#include "NetworkManager.hpp"

class BufferProcessor {
public:
    BufferProcessor();
    ~BufferProcessor();

    void inputData();
    void outputData();

private:
    std::string m_buffer;
    std::unique_ptr<NetworkManager> m_networkManager;
    bool m_isDataReceived;
    std::mutex m_mutex;
    std::condition_variable m_cv;
};