#pragma once
#include <vector>
#include <string>
#include <iostream>

class GtfsObject {
    public:
        std::vector<std::string> * fields;
        std::vector<std::string> values;

        GtfsObject(std::vector<std::string> * fields, std::vector<std::string> values) : fields(fields), values(values) {}

        std::string getValue(std::string field);
};

void print_vector(std::vector<std::string> v, std::ostream& stream = std::cout);
void print_value(std::string value, std::ostream& stream = std::cout);

template <typename T>
std::vector<T> concat_vectors(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> ab = a;
    ab.insert(ab.end(), b.begin(), b.end());
    return ab;
}