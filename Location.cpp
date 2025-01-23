#include "Location.h"

std::string LocationToString(Location location) {
    switch (location) {
    case Location::HOME:    return "Home";
    case Location::OFFICE:  return "Office";
    case Location::AIRPORT: return "Airport";
    case Location::BAR:     return "Bar";
    case Location::RESTAURANT: return "Restaurant";
    case Location::WALMART:   return "Store";
    case Location::OUTSIDE: return "Outside";
    case Location::PARK: return "Park";
    case Location::GYM: return "Gym";
    default:                 return "Unknown";
    }
}
