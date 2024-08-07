#pragma once
#include <vector>
#include <string>
#include "collection.h"

class GtfsTable : public Collection {
    public:
        std::vector<std::string> fields;

        GtfsTable(std::string filename);
};