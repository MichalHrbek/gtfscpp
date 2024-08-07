#pragma once
#include <vector>
#include <string>

class GtfsObject {
    public:
        std::vector<std::string> * fields;
        std::vector<std::string> values;

        GtfsObject(std::vector<std::string> * fields, std::vector<std::string> values) : fields(fields), values(values) {}

        std::string getValue(std::string field);
};

void print_vector(std::vector<std::string> v);
void print_value(std::string value);