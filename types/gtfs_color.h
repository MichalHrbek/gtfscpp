#pragma once
#include <cstdint>
#include <string>

struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color() : r(0), g(0), b(0) {}
    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}
    Color(int32_t rgb) {
        r = (rgb >> 16) & 0xFF;
        g = (rgb >> 8) & 0xFF;
        b = rgb & 0xFF;
    }
};

Color parse_color(std::string value) {
    return Color(stol(value, 0, 16));
}