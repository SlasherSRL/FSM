#pragma once
#include <string>

enum class Location
{
    HOME,
    OFFICE,
    AIRPORT,
    RESTAURANT,
    WALMART,
    OUTSIDE,
    PARK,
    BAR,
    GYM
};
std::string LocationToString(Location location);