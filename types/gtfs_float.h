#pragma once
#include <string>

typedef float Float;

Float parse_float(std::string value) {
    return std::stof(value);
}