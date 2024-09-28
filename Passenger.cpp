//
// Created by patel on 4/8/2024.
//
#include "Passenger.h"
#include <iostream>
#include <string>

using namespace std;

Passenger::Passenger(){
    //Constructor that makes a aew passenger,and assigns ID using GetNextID
    ID= GetNextID();
}
Passenger::Passenger(int PassengerID, std::string PassengerOrigin, std::string PassengerDestination){
    //Constructor
    //Pre:Takes in a passengers Id, their starting location , and their ending location.
    //Post:Initializes it to the private variables
    ID=PassengerID;
    origin=PassengerOrigin;
    destination=PassengerDestination;
}  // ID, origin, destination
void Passenger::Initialize(int PassID, string PassOrigin, string PassDestination){
    //Pre:takes in a passengers ID, origin and destination
    //Post:Initializes the variables to the private members of the class.
    ID=PassID;
    origin=PassOrigin;
    destination=PassDestination;
} // ID, origin, destination

