#include "gtfs_object.h"
#include <iostream>

std::string GtfsObject::getValue(std::string field) {
    for (size_t i = 0; i < fields->size(); i++)
    {
        if (fields->at(i) == field) return values[i];
    }
    return NULL;
}

void print_value(std::string value) {
    if (value.find('"') != std::string::npos) std::cout << '"' << value << '"'; // Quoted
    else std::cout << value; // Unquoted
}

void print_vector(std::vector<std::string> v) {
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i != 0) std::cout << ',';
        print_value(v.at(i));
    }
    std::cout << std::endl;
}