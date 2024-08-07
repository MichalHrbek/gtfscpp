#pragma once
#include <cstdint>
#include <string>

struct Time
{
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

    Time() : hours(0), minutes(0), seconds(0) {}
    Time(uint8_t hours, uint8_t minutes, uint8_t seconds) : hours(hours), minutes(minutes), seconds(seconds) {}
};

Time parse_time(std::string value) {
    if (value.at(1) == ':') return Time(stoi(value.substr(0,1)), stoi(value.substr(2,2)), stoi(value.substr(5,2))); // H:MM:SS
    return Time(stoi(value.substr(0,2)), stoi(value.substr(3,2)), stoi(value.substr(6,2))); // HH:MM:SS
}