#pragma once
#include <vector>
#include <iostream>
#include <functional>
#include <optional>
#include "gtfs_object.h"

class Collection {
    public:
        std::vector<GtfsObject> rows = {};

        Collection() {}
        Collection(std::vector<GtfsObject> rows) : rows(rows) {}

        Collection where(const std::function<bool(GtfsObject)>& match);
        Collection for_each(const std::function<void(GtfsObject)>& func);
        Collection concat(Collection c);
        Collection range(size_t start, size_t end);
        GtfsObject first();
        GtfsObject last();

        Collection select(std::vector<std::string> fields);

        std::optional<GtfsObject> get_by_unique_id(std::string field, std::string value);
        Collection get_by_id(std::string field, std::string value);
        Collection matching_id(Collection c, std::string field);
        Collection join_by_unique_id(Collection c, std::string field);

        bool contains(std::string field, std::string value);
        size_t size();
        bool empty();

        void add(GtfsObject o);

        void print(std::ostream& stream = std::cout);
        void print(const std::vector<std::string>& fields, std::ostream& stream = std::cout);
};