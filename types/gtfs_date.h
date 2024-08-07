#pragma once
#include <cstdint>
#include <string>

struct Date
{
    uint16_t year;
    uint8_t month;
    uint8_t day;

    Date() : year(0), month(0), day(0) {}
    Date(uint16_t year, uint8_t month, uint8_t day) : year(year), month(month), day(day) {}
};

Date parse_date(std::string value) {
    return Date(stoi(value.substr(0,4)), stoi(value.substr(4,2)), stoi(value.substr(6,2)));
}