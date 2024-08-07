#!/bin/sh
g++ -fdiagnostics-color=always -g main.cpp collection.cpp gtfs_table.cpp gtfs_object.cpp -o main
./main
