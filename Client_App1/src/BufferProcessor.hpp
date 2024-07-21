#pragma once

#include <iostream>
#include <queue>
#include <string>
#include <algorithm>

class BufferProcessor {
public:
    void start();

private:
    void InputData();
    void OutputData();

private:
    std::queue<std::string> m_buffer;
};