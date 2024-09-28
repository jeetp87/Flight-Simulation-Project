//
// Created by patel on 4/8/2024.
//

#ifndef FP02_PASSENGER_H
#define FP02_PASSENGER_H

#include <string>
#include <iostream>

using namespace std;
static int nextID=1000;

class Passenger {
public:
    Passenger();  // New passenger, assigning ID using GetNextID
    Passenger(int, string, string);  // ID, origin, destination
    void Initialize(int, string, string); // ID, origin, destination
    int GetID() {return ID;}
    string GetOrigin(){ return origin;}
    string GetDest() {return destination;}

private:
    int ID=nextID;  // A unique ID number for the passenger
    string origin; //Airport identifier
    string destination; // Airport identifier
    int GetNextID(){
        //Post: Assigns ID's sequentially, starting with 1001
        nextID++;
        ID=nextID;
        return ID;
    }
};



#endif //FP02_PASSENGER_H
