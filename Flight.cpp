//
// Created by patel on 4/12/2024.
//
#include <iostream>
#include "Airport.h"
#include "Flight.h"
void Flight::Initialize(Airport FlightOrigin, Airport FlightDestination, int availSeats){
    //Pre:Takes in two airports and number of seats available.
    //Post:Initializes the flights origin, destination, and the seats available;

    origin=FlightOrigin.GetID();
    destination=FlightDestination.GetID();
    availableSeats=availSeats;
    numPax=MAX_PAX_PER_FLIGHT-availableSeats;


}
Flight::Flight(Airport orig, Airport dest, int seats){
    //Airport constructor that initializes the values.
    origin=orig.GetID();
    destination=dest.GetID();
    availableSeats=seats;


}

void Flight::AddPax(Passenger newPassenger){
    //Pre:Takes in a passenger
    //Post:Adds to the Pax list and decrements the available seats.
    Passenger* newPtr=&newPassenger;
   PaxList[numPax++]=newPtr;
   availableSeats--;

} // Add a Passenger to PaxList, reduce seats available

void Flight::ResetFlight(){
    //Post:Resets all the flight variable to their initial value
    //A for loop to clear the Paxlist.
    for(int i=0;i<MAX_PAX_PER_FLIGHT;i++){
        PaxList[i]= nullptr;
    }
    //resets the available seats to the max amount
    availableSeats=MAX_PAX_PER_FLIGHT;
    //Sets the number of passengers to 0.
    numPax=0;

} // Clears Passenger list, empties seats

float Flight::GetTicketCost(Airport airportOne, Airport airportTwo) {
    //Pre:Takes in two airports:An origin and a destination.
    //Post::returns the cost of ticket by dividing the operating cost by 30.
    int ticket=GetOpCost( airportOne,  airportTwo)/30.0f;
   return ticket;

}
float Flight::GetRevenue(Airport airportOne, Airport airportTwo){
    //Pre:Takes in two airports:An origin and a destination.
    //Post:Gets the revenue by multiplying the ticket cost by the num of passengers and returns
    //it.

    float revenue=0.0f;
    revenue =GetTicketCost( airportOne,  airportTwo)*numPax;
    return revenue;

} // Revenue = TicketCost * number of passengers
float Flight::GetProfit(Airport airportOne, Airport airportTwo){
    //Pre:Takes in two airports:An origin and a destination.
    //Post:Returns the profit by subtracting the operating cost from
    //the revenue.
    float profit=GetRevenue( airportOne,  airportTwo)-GetOpCost( airportOne,  airportTwo);
    return profit;
} // Profit = Revenue - OpCost

float Flight::GetOpCost(Airport airportOne, Airport airportTwo){
//Pre:Takes in the flights starting and ending places and the daily fuel costs.
    //Post:Calculates the fuel costs and flight ime based on distance.
    //The uses the either distance or flight time to calculate the crew costs.Finally,
    //adds the maintenance and the landiing fee. Sums all the costs to get the total.
    int landingFee;
    float finalCosts,gallon=1.0f,miles=1.8,dailyFuelPrice=4.34;


    //An equation to calculate the fuels cost.
    double fuelCosts= dailyFuelPrice/gallon* (30 +GetDistance
            (airportOne, airportTwo) )/  miles;

    //Set of if statements to set the landing fee to the appropriate cost based
    // on the landing airport
    if(destination=="KPHL"){
        landingFee=200;

    }else if(destination=="KBOS"){
        landingFee=200;
    }else{
        landingFee=100;
    }

    //Calculates the flights time and add 20 minutes for taxi,landning.
    float flightTime=0.33+(GetDistance(airportOne, airportTwo)/310);
    int maintenance=500;

    //Calculates the cost of having the crew.
    float crewCosts=3 * 100 * (flightTime + 1);

    finalCosts=landingFee+crewCosts+maintenance+fuelCosts;

    return finalCosts;

} // Use function from Final Project Part 1
float Flight::calculatingDistance (long double lat1, long double long1,
                           long double lat2,long double long2 ){
    //Pre:Takes in the latitude and longitude of two locations.
    //Post:Converts into radians and then uses and equation to calculate and return the
    //distance in miles.

    //Converts the longitude and latitude into radians.
    lat1= lat1/57.29577951;
    lat2= lat2/57.29577951;
    long1= long1/57.29577951;
    long2= long2/57.29577951;

    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;

    long double distance = pow(sin(dlat / 2), 2) +
                           cos(lat1) * cos(lat2) *
                           pow(sin(dlong / 2), 2);

    distance = 2 * asin(sqrt(distance));


    long double Radius = 3956;

    // Calculate the result
    distance = distance * Radius;
    return distance;
}

float Flight::GetDistance(Airport airportOne,Airport airportTwo){
    //Pre:Takes in two airports:An origin and a destination.
    //Post: A helper function that calculates the distance by calling another funciton
    float lat1=airportOne.GetLat();
    float long1=airportOne.GetLong();
    float lat2=airportTwo.GetLat();
    float long2=airportTwo.GetLong();


    float distance=calculatingDistance(lat1, long1,
                                             lat2, long2);
    return distance;
} // Use function from Final Project Part 1
void Flight::Print (ofstream& outfile,Airport airportOne, Airport airportTwo){
    //Pre:Takes in two airports(An origin and a destination), and an output file.
    //Post:Outputs all flight information to the given output file.

    outfile<<"Flight Origin: "<<origin<<endl ;
    outfile<<"Flight Destination: "<<destination<<endl ;
    outfile<<"Number of passengers : "<<numPax<<endl ;
    outfile<<"Available Seats : "<<availableSeats<<endl ;
    outfile<<"Operating Costs of flight :"<<GetOpCost( airportOne,  airportTwo)<<endl;
    outfile<<"Revenue of flight :"<<GetRevenue( airportOne,  airportTwo)<<endl;
    outfile<<"Profit of flight :"<<GetProfit( airportOne,  airportTwo)<<endl;

} // Print Flight Origin, Dest, #Pax, availableSeats, OpCost, Revenue, Profit
void Flight::Print(Airport airportOne, Airport airportTwo){
    //Pre:Takes in two airports:An origin and a destination.
    //Post:Outputs the flight information to the run terminal.
    cout<<"FLight Origin: "<<origin<<"\n Flight Destination: "<<destination<<endl;
    cout<<"Number of Passengers: "<<numPax<<endl<<" Available Seats: "<<availableSeats<<endl;
    cout<<"Operating Costs of flight :"<<GetOpCost( airportOne,  airportTwo)<<endl;
    cout<<"Revenue of flight :"<<GetRevenue( airportOne,  airportTwo)<<endl;
    cout<<"Profit of flight :"<<GetProfit( airportOne,  airportTwo)<<endl;
} // Print Flight Origin, Dest, #Pax, available seats, OpCost, Revenue, Profit



