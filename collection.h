#pragma once
#include <vector>
#include <functional>
#include "gtfs_object.h"

class Collection {
    public:
        std::vector<GtfsObject> rows = {};

        Collection() {}        
        Collection(std::vector<GtfsObject> rows) : rows(rows) {}

        Collection where(const std::function<bool(GtfsObject)>& match);
        Collection for_each(const std::function<void(GtfsObject)>& func);
        Collection join(Collection c);
        Collection range(size_t start, size_t end);
        GtfsObject first();
        GtfsObject last();
        GtfsObject get_by_unique_id(std::string field, std::string value);
        Collection get_by_id(std::string field, std::string value);
        size_t size();
        bool empty();

        void print();
};