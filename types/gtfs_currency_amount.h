#pragma once
#include <string>

typedef float CurrencyAmount;

CurrencyAmount parse_currency_amount(std::string value) {
    return std::stof(value);
}