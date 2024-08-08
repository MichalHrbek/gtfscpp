#include "gtfs_table.h"
#include <iostream>
#include <fstream>
#include <chrono>

std::vector<std::string> parse_line(std::ifstream& stream, size_t reserve = 0) {
    std::vector<std::string> values;
    if (reserve) {
        values.reserve(reserve);
    }
    char ch;
    std::string field = "";
    bool in_quotes = false;
    bool unquote = false;
    while (stream >> std::noskipws >> ch) {
        if (ch == '\r') continue;
        if (ch == '\n') {
            values.push_back(field);
            return values;
        }
        if (ch == '"') {
            if (unquote) {
                field += '"';
                unquote = false;
                in_quotes = true;
            } else if (in_quotes) {
                unquote = true;
                in_quotes = false;
            } else {
                in_quotes = true;
            }
            continue;
        }
        if (unquote) unquote = false;
        if (!in_quotes && ch == ',') {
            values.push_back(field);
            field = "";
            continue;
        }

        field += ch;
    }
    stream.close();
    return values;
}

GtfsTable::GtfsTable(std::string filename) {
    auto t1 = std::chrono::high_resolution_clock::now(); // Start the timer

    std::ifstream fin(filename); 

    if (!fin.is_open()) { 
        std::cerr << "Error opening the file!" << std::endl;
        return;
    }

    fields = parse_line(fin);
    size_t n_fields = fields.size();

    while (fin.is_open()) {
        rows.push_back(GtfsObject(&fields, parse_line(fin, n_fields)));
    }

    // TODO: 0 rows? I don't think this even works, since the last row will have 1 empty string
    if (rows.at(rows.size()-1).values.empty()) {
        rows.pop_back();
    }

    auto t2 = std::chrono::high_resolution_clock::now(); // End the timer
    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << filename << " loaded in " <<  ms_int.count() << "ms\n";
}