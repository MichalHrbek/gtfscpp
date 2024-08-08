#include "gtfs_object.h"
#include <iostream>

std::string GtfsObject::getValue(std::string field) {
    for (size_t i = 0; i < fields->size(); i++)
    {
        if (fields->at(i) == field) return values[i];
    }
    return NULL;
}

void print_value(std::string value, std::ostream& stream) {
    if (value.find('"') != std::string::npos) stream << '"' << value << '"'; // Quoted
    else stream << value; // Unquoted
}

void print_vector(std::vector<std::string> v, std::ostream& stream) {
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i != 0) stream << ',';
        print_value(v.at(i));
    }
    stream << std::endl;
}