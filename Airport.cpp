//
// Created by patel on 4/16/2024.
//
#include "Airport.h"
#include <iostream>
Airport::Airport(Airport& airportOriginal) {
    //Pre:Takes in an airport
    //Post:Sets the taken in airports info to the current airports.
    IATA=airportOriginal.GetID();
    city=airportOriginal.GetCity();
    longitude=airportOriginal.GetLong();
    latitude=airportOriginal.GetLat();
}//copy constructor
void Airport::Initialize(string newID, string newCity, long double newLat, long double newLong){
    //Takes in an airport ID and  city. Also takes in the airports latitude and longitude.
    IATA = newID;
    city = newCity;
    latitude = newLat;
    longitude = newLong;
}