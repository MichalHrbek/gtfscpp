#pragma once
#include <vector>
#include <string>

class GtfsObject {
    public:
        std::vector<std::string> * fields;
        std::vector<std::string> values;

        GtfsObject(std::vector<std::string> * fields, std::vector<std::string> values) : fields(fields), values(values) {}

        std::string getValue(std::string field) {
            for (size_t i = 0; i < fields->size(); i++)
            {
                if (fields->at(i) == field) return values[i];
            }
            return NULL;
        }
};