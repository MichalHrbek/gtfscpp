#pragma once
#include <cstdint>
#include <string>

typedef int32_t Enum;

Enum parse_enum(std::string value) {
    return stol(value);
}