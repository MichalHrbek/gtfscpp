#pragma once
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

size_t Collection::size() {
    return rows.size();
}

bool Collection::empty() {
    return rows.empty();
}

void print_vector(std::vector<std::string> v) {
    for (size_t i = 0; i < v.size(); i++)
    {
        if (i != 0) std::cout << ',';
        if (v.at(i).find('"') != std::string::npos) std::cout << '"' << v.at(i) << '"'; // Quoted
        else std::cout << v.at(i); // Unquoted
    }
    std::cout << std::endl;
}

void Collection::print() {
    for (size_t i = 0; i < rows.size(); i++)
    {
        if (i == 0 || rows.at(i-1).fields != rows.at(i).fields) print_vector(*rows.at(i).fields);
        print_vector(rows.at(i).values);
    }
    
}