#include <iostream>
#include <string>
#include "gtfs_table.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello World" << std::endl;

    // GtfsTable stop_times("gtfs/stop_times.txt");
    GtfsTable stops("gtfs/stops.txt");
    GtfsTable routes("gtfs/routes.txt");
    GtfsTable trips("gtfs/routes.txt");
    
    std::cout << "Done" << std::endl;



    /*table.where([](GtfsObject o) {
        return o.getValue("route_id") == "L145";
    })
    .range(0,5)
    .print();*/

    return 0;
}