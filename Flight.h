//
// Created by patel on 4/8/2024.
//

#ifndef FP02_FLIGHT_H
#define FP02_FLIGHT_H
#include <string>
#include <fstream>
#include <cmath>
using namespace std;


#include "Passenger.h"
#include "Airport.h"

const int MAX_PAX_PER_FLIGHT = 37;

class Flight {
public:
    Flight() { cout << "Empty flight"; }

    Flight(Airport, Airport, int);

    void Initialize(Airport, Airport, int);  // Set origin, destination, available seats
    void AddPax(Passenger); // Add a Passenger to PaxList, reduce seats available
    void ResetFlight(); // Clears Passenger list, empties seats
    float GetRevenue(Airport, Airport); // Revenue = TicketCost * number of passengers
    float GetTicketCost(Airport, Airport); // TicketCost = OpCost / 30.0f
    float GetOpCost(Airport, Airport); // Use function from Final Project Part 1
    float GetDistance(Airport, Airport); // Use function from Final Project Part 1
    //******Added a helper function to calculate the distance.
    float calculatingDistance(long double lat1, long double long1,
                              long double lat2, long double long2);
    string GetOrigin() { return origin;}  //*** Added Function
    string GetDest() { return destination;} //*** Added Function
    int GetEmptySeats() {
        if(numPax!=availableSeats){
        return availableSeats-numPax;
        }else{
            return 0;
        }
    } //*** Added Function
    float GetProfit(Airport, Airport); // Profit = Revenue - OpCost
    void Print(Airport, Airport); // Print Flight Origin, Dest, #Pax, available seats, OpCost, Revenue, Profit
    void
    Print(ofstream &, Airport, Airport); // Print Flight Origin, Dest, #Pax, availableSeats, OpCost, Revenue, Profit

private:
    string origin;
    string destination;
    Passenger *PaxList[MAX_PAX_PER_FLIGHT];
    int availableSeats;
    int numPax;


};
#endif //FP02_FLIGHT_H
