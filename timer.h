#pragma once
#include <chrono>
#include <iostream>

std::chrono::_V2::system_clock::time_point timer_start() {
    return std::chrono::high_resolution_clock::now();
}

std::chrono::milliseconds timer_end(std::chrono::_V2::system_clock::time_point t1) {
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
}

void timer_print(std::chrono::milliseconds dur, std::string text = "") {
    std::cout << text <<  dur.count() << "ms\n";
}