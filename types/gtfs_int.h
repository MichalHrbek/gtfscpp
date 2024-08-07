#pragma once
#include <cstdint>
#include <string>

typedef int32_t Int;

Int parse_int(std::string value) {
    return stol(value);
}