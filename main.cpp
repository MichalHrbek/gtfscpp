#include <iostream>
#include <string>
#include <ctime>
#include "gtfs_table.h"
#include "timer.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello World" << std::endl;

    GtfsTable stops("gtfs/stops.txt");
    GtfsTable routes("gtfs/routes.txt");
    GtfsTable route_stops("gtfs/route_stops.txt");
    GtfsTable trips("gtfs/trips.txt");
    GtfsTable calendar("gtfs/calendar.txt");
    GtfsTable calendar_dates("gtfs/calendar_dates.txt");
    GtfsTable stop_times("gtfs/stop_times.txt");
    
    std::cout << "Done" << std::endl << std::endl;

    // Example that lists lines passing trough a stop selected by name
    stops.where([](GtfsObject o) {
        return o.getValue("stop_name") == "Počeradská";
    })
    .matching_id(route_stops, "stop_id")
    .matching_id(routes, "route_id")
    .print({"route_short_name", "route_long_name"});

    // Example of joining two tables by an unique id
    auto ts = timer_start();

    stop_times.join_by_unique_id(stops.where([](GtfsObject o) {
        return o.getValue("stop_name") == "Počeradská";
    }), "stop_id").print();
    
    timer_print(timer_end(ts), "Joining took ");

    time_t timestamp;
    time(&timestamp);
    std::cout << std::endl << ctime(&timestamp);

    return 0;
}