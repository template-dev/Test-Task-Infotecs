#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <numeric>

class BufferProcessor {
public:
    void start();

private:
    void inputData();
    void outputData();

private:
    std::queue<std::string> m_buffer;
};