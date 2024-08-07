#include "collection.h"
#include <iostream>
#include <cassert>

Collection Collection::where(const std::function<bool(GtfsObject)>& match) {
    std::vector<GtfsObject> matching = {};
    for (GtfsObject o : rows) {
        if (match(o)) {
            matching.push_back(o);
        }
    }
    return matching;
}

Collection Collection::for_each(const std::function<void(GtfsObject)>& func) {
    for (GtfsObject o : rows) {
        func(o);
    }
    return *this;
}

Collection Collection::join(Collection c) {
    std::vector<GtfsObject> AB = {};
    AB.reserve( rows.size() + c.rows.size() );
    AB.insert( AB.end(), rows.begin(), rows.end() );
    AB.insert( AB.end(), c.rows.begin(), c.rows.end() );
    return AB;
}

Collection Collection::range(size_t start, size_t end) {
    assert(end >= start);
    std::vector<GtfsObject> c(rows.begin()+start, rows.begin()+end+1);
    return c;
}

GtfsObject Collection::first() {
    return rows.at(0);
}

GtfsObject Collection::last() {
    return rows.at(rows.size()-1);
}

std::optional<GtfsObject> Collection::get_by_unique_id(std::string field, std::string value) {
    for (GtfsObject o : rows) {
        if (o.getValue(field) == value) return o;
    }
    return {};
}
Collection Collection::get_by_id(std::string field, std::string value) {
    return where([field,value](GtfsObject o) {return o.getValue(field) == value;});
}

Collection Collection::matching_id(Collection c, std::string field) {
    return c.where([this, field](GtfsObject o) {
        return contains(field, o.getValue(field));
    });
}

bool Collection::contains(std::string field, std::string value) {
    for (GtfsObject o : rows) {
        if (o.getValue(field) == value) return true;
    }
    return false;
}

size_t Collection::size() {
    return rows.size();
}

bool Collection::empty() {
    return rows.empty();
}

void Collection::add(GtfsObject o) {
    rows.push_back(o);
}

void Collection::print() {
    for (size_t i = 0; i < rows.size(); i++)
    {
        if (i == 0 || rows.at(i-1).fields != rows.at(i).fields) print_vector(*rows.at(i).fields);
        print_vector(rows.at(i).values);
    }
}

void Collection::print(std::vector<std::string> fields) {
    print_vector(fields);
    for (GtfsObject o : rows) {
        for (size_t i = 0; i < fields.size(); i++)
        {
            if (i != 0) std::cout << ',';
            print_value(o.getValue(fields.at(i)));
        }
        std::cout << std::endl;
    }
}