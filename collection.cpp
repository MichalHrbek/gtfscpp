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

Collection Collection::concat(Collection c) {
    return Collection(concat_vectors(rows, c.rows));
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

// This is probably useless
Collection Collection::select(std::vector<std::string> fields) {
    std::vector<GtfsObject> result;
    result.reserve(rows.size());
    size_t nfields = fields.size();
    for (GtfsObject o : rows) {
        std::vector<std::string> new_values;
        new_values.reserve(nfields);
        for (size_t i = 0; i < fields.size(); i++)
        {
            new_values.push_back(o.getValue(fields.at(i)));
        }
        result.push_back(GtfsObject(&fields, new_values));
    }
    return result;
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

// The id is unique in c, doesn't have to be unique in this
Collection Collection::join_by_unique_id(Collection c, std::string field) {
    std::vector<GtfsObject> result;
    result.reserve(rows.size());
    std::vector<std::string>* l_fields = nullptr;
    std::vector<std::string>* r_fields = nullptr;
    std::vector<std::string>* result_fields = nullptr;

    for (GtfsObject i : rows) {
        for (GtfsObject j : c.rows) {
            if (i.getValue(field) == j.getValue(field)) {
                if (!result_fields || l_fields != i.fields || r_fields != j.fields) {
                    l_fields = i.fields;
                    r_fields = j.fields;
                    static std::vector<std::string> joined_fields = concat_vectors(*l_fields, *r_fields);
                    result_fields = &joined_fields;
                }
                result.push_back(GtfsObject(result_fields, concat_vectors(i.values, j.values)));
            }
        }
    }

    return Collection(result);
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

void Collection::print(std::ostream& stream) {
    for (size_t i = 0; i < rows.size(); i++)
    {
        if (i == 0 || rows.at(i-1).fields != rows.at(i).fields) print_vector(*rows.at(i).fields, stream);
        print_vector(rows.at(i).values, stream);
    }
}

void Collection::print(const std::vector<std::string>& fields, std::ostream& stream) {
    print_vector(fields, stream);
    for (GtfsObject o : rows) {
        for (size_t i = 0; i < fields.size(); i++)
        {
            if (i != 0) stream << ',';
            print_value(o.getValue(fields.at(i)), stream);
        }
        stream << std::endl;
    }
}