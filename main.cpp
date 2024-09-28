//File name: FP03
//Name: Jeetkumar Patel
//Email: jbp6128@psu.edu
//Class&Section: CMPSC 122
//Assignment ID : 15127517
//Due Date: 04/27/2024
//Description:Runs a simulation of a year of flights
//===========
// CMPSC-122
// ==============================
// Final Project - 03
// Student template
// ==============================

// -- Preprocessor directives
#include "definitions.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>

// -- Objects --
#include "Passenger.h"
#include "Airport.h"
#include "Flight.h"

#include "GraphType.h"
#include "QueType.h"

Passenger randomPax(GraphType<string> &theGraph, Airport [], Flight [],dailyResult&);
int findFlightID(string, string, Flight []);
void LoadAirports(Airport (&myAirports)[NUM_AIRPORTS] );
void LoadFlights(Flight [], Airport []);
void LoadGraph(GraphType<string> &graph, Airport (&airports)[NUM_AIRPORTS]);
dailyResult SimDay(GraphType<string> &theGraph, Airport [NUM_AIRPORTS], Flight [NUM_FLIGHTS]);

// ==============================
// Main Program
int main() {
    // Initialize file
    logFile.open("FP-3_LogFile.txt");
    routes.open("Routes.txt");

    // Variables
    Airport airports[NUM_AIRPORTS];
    Flight flights[NUM_FLIGHTS];
    GraphType<string> routeMap;
    dailyResult resultLog[365];

    // Random seed
    srand(time(0));

    // Variables to track sim results

    // ----------------------------------
    // Initialize the Simulation
    // ----------------------------------
    logFile << "Start of Simulation" << endl;
    // Generate Airports
    LoadAirports(airports);

    // Then Add the vertices and load the routeMap
    LoadFlights(flights, airports);
    // if (DEBUG) {cout << "M63: Flight " << 3 << " " << flights[3].GetDistance() << endl; }

    LoadGraph(routeMap, airports);


    // ----------------------------------
    // Daily Simulations
    // ----------------------------------
    logFile << "Days: " << endl;
    for (int day = 0; day < 365; day++){
        resultLog[day] = SimDay(routeMap, airports, flights);
        logFile << day<< " ";
        if (day%30 == 29) {logFile << endl;}
    }
    logFile << endl;

    // ----------------------------------
    // *** Produce Results Report ***
    // ----------------------------------
    // Summary Report must show:
    // Section 1 - Operations info
    // Yearly Passengers served
    // Yearly Empty Seats
    // Yearly Stranded Passengers
    int emptySeats=0,strandedPax=0,passengersServed=146000;
    float yearlyRevenue=0.0f,yearlyOpCosts=0.0f;
    for(int i=0;i<365;i++){
        emptySeats+=resultLog[i].emptySeats;
        strandedPax+=resultLog[i].strandedPax;
        yearlyOpCosts+=resultLog[i].opCosts;
        yearlyRevenue=yearlyRevenue+resultLog[i].revenue;


    }



    // Section 2 - Profitability
    // Yearly Revenue
    // Yearly Operating Cost
    // Yearly Profit (Loss)
    // *** Report all $ results in Millions of dollars with 2 decimals using this notation: $3.14M

    logFile << "----------------------------------------" << endl;
    logFile << "--        Simulation Results          --" << endl;
    logFile << "----------------------------------------" << endl;

    logFile<<"Passengers served: "<<passengersServed-strandedPax<<endl;
    logFile<<"Passengers stranded: "<<strandedPax<<endl;
    logFile<<"Empty Seats: "<<emptySeats<<endl;
   logFile<<fixed<<setprecision(2)<<"The Yearly revenue is: $"<<yearlyRevenue/1e+06<<"M"<<endl;
   logFile<<"The yearly operating costs is : $"<<yearlyOpCosts/1e+06<<"M"<<endl;
   logFile<<"The Yearly profit is: $"<<(yearlyRevenue/1e+06)-(yearlyOpCosts/1e+06)<<endl;




    // Calculate Summary info


    // Output to Report


    logFile.close();

    return 0;
}

// *****************************************
// Functions you can use without modification
// *****************************************
//

// ==============================
// Load Airports
// - or, you can use your own version
// ==============================

void LoadAirports(Airport (&myAirports)[NUM_AIRPORTS] ) {
    logFile << "-- Loading Airports -- " ;

    Airport* readAirport;
    ifstream airportFile;
    string readLine;
    string readICAO;
    string readCity;
    long double latitude, longitude;

// Initialize all airports
    airportFile.open("airports.txt");
    if (!airportFile) { logFile << "*** Airport File not opened" << endl; }
    int airportCount;
// Read in State information
    for (airportCount = 0; airportCount < NUM_AIRPORTS; airportCount++) {
// Read each airport from the file
        getline(airportFile, readLine);
        readICAO = readLine.substr(0, 4);
        readCity = readLine.substr(5, readLine.length() - 5);
        airportFile >> latitude;
        airportFile >> longitude;
        getline(airportFile, readLine); // throw away remainder

// Create a corresponding airport object
        myAirports[airportCount].Initialize(readICAO, readCity, latitude, longitude);
        // cout << "M99: Read Airport " << myAirports[airportCount].GetCity() << endl;
    }
    logFile << airportCount << " Airports read ";

    airportFile.close();
    logFile << "-- Airports Loaded -- " << endl;
}


// ==============================
// findFlightID
// Given two airport identifiers,
// Return the index in the flight array
// ==============================
int findFlightID(string orig, string dest, Flight flight[NUM_FLIGHTS]){
    for (int i = 0; i<NUM_FLIGHTS; i++){
        if (orig == flight[i].GetOrigin() && dest == flight[i].GetDest()){
            if (DEBUG) cout<< "M293: Flight found " << orig << " --> " << dest << endl;
                return i;
        }
    }
    // You should never see this message when running your program!
    if (DEBUG) cout << "M300: *** Flight not found " << orig << " --> " << dest << endl;
    return 0;
}

// *****************************************
// You will need to modify all the functions
// below this line.
// *****************************************

// ==============================
// Load Graph
// ==============================
void LoadGraph(GraphType<string> &theGraph, Airport (&airports)[NUM_AIRPORTS]){
    logFile << "-- Loading Graph -- " ;

    // *** Load the Vertices into theGraph
    for(int i=0;i<NUM_AIRPORTS;i++) {
        theGraph.AddVertex(airports[i].GetID());
    }


    // *** Load the Edges into theGraph
    string start,end;
    for(int i=0;i<19;i++){
        routes>>start>>end;
        theGraph.AddEdge(start,end,1);
    }


    logFile << "-- Graph Loaded -- " << endl;
}

// ==============================
// Load Flights
// ==============================
void LoadFlights(Flight flights[NUM_FLIGHTS-1], Airport airports[NUM_AIRPORTS]){
    logFile << "-- Loading Flights -- " ;

    //*** Load all flight info into the flights variable.
    // You may find it useful to work from the existing airports array
    string start,end;
    for(int i=0;i<NUM_FLIGHTS;i++){

        Airport tempOrigin,tempDest;
        routes>>start>>end;
        for(int x=0;x<NUM_AIRPORTS;x++){
            if(airports[x].GetID()==start){
            tempOrigin=airports[x];
            }else if(airports[x].GetID()==end){
            tempDest=airports[x];

            }
        }
        flights[i].Initialize(tempOrigin,tempDest,37);
    }

    logFile << "-- Flights Loaded -- " << endl;
}

// ==============================
// SimDay
// ==============================

dailyResult SimDay(GraphType<string> &theGraph, Airport airports[NUM_AIRPORTS], Flight flights[NUM_FLIGHTS]){
    //Pre:takes in a graph, an airports array, and a flights array
    //Post:Runs a simulations for the day by creating 400 passengers and adds the revenue and costs
    //to a daily results object.
    // Run a day of simulations
    dailyResult today;
    Passenger newPax;

    // Initialize totals for today
    today.revenue = 0;
    today.opCosts = 0;
    today.strandedPax = 0;
    today.emptySeats = 0;

    // Reset Flights for today
    for(int i=0;i<NUM_FLIGHTS;i++){
        flights[i].ResetFlight();

    }


    // *** Create Passengers and assign to flights
    // Using randomPax()
    // Note: you need a way to pass & track info about stranded passengers
    // ***
    //For loop that makes the 400 passengers a day
    for(int i=0;i<PAX_PER_DAY;i++) {
        randomPax(theGraph, airports, flights, today);
    }

    // Calculate today's result
    Airport tempOrigin,tempDest;
    for (int i = 0; i< NUM_FLIGHTS; i++){
        //A for loop to find the origin and destinations airports to find revenue and opCosts
        for(int x=0;x<NUM_AIRPORTS;x++) {
            if (flights[i].GetOrigin() == airports[x].GetID()) {
            tempOrigin=airports[x];
            }else if(flights[i].GetDest()==airports[x].GetID()){
                tempDest=airports[x];
            }
        }
        // Add Revenue
        today.revenue += flights[i].GetRevenue(tempOrigin,tempDest);


        // Add opCosts
        today.opCosts += flights[i].GetOpCost(tempOrigin,tempDest);


        // Add Empty Seats
        today.emptySeats += flights[i].GetEmptySeats();
    }


    return today;
}


// ==============================
// randomPax
// Generate a random passenger
// ==============================

Passenger randomPax(GraphType<string> &theGraph, Airport airports[NUM_AIRPORTS], Flight flights[NUM_FLIGHTS],dailyResult& newLog){
    //Pre:Takes in a graph, an array of airports, and an array of flights, and a dailyResult struct
    //Post:Returns a passenger who take two hops from an origin. All are randomly created, the passenger
    //is the assigned to the flights.The function does not allow for round trips and manages stranded
    // passengers.

    // Generates a random passenger, assuming:
    // Sequential ID
    // Random choice of origin
    // Destination within 2 hops (Adjacents to adjacents)


    // Choose a random origin
    int chosenIndex = (rand()%NUM_AIRPORTS);
    Airport chosenAirport = airports[chosenIndex];

//Array to store airports
    Airport airportArray[NUM_FLIGHTS-1];
    int counter=0,counterTwo=0;

    // Choose the first flight
    // Which flights available from there?
    //Loops through the flights array to find the possible first hops
    for(int i=0;i< NUM_FLIGHTS;i++){
        if(flights[i].GetOrigin()==chosenAirport.GetID()) {
            airportArray[counter] = flights[i].GetDest();
            counter++;
        }
    }

    // Randomly select a city for the first hop:
    //Randomly selects the first hop from the array
    int firstDestSelector=rand()%counter+0;
    Airport firstDestination=airportArray[firstDestSelector];


    // Randomly choose to hop to another adjacent city
    //Loops through the flights array to find the possible second hops

    for(int i=0;i< NUM_FLIGHTS;i++){
        if(flights[i].GetOrigin()==firstDestination.GetID()) {
            airportArray[counterTwo] = flights[i].GetDest();
            counterTwo++;
        }
    }
    //Randomly chooses the second hop from the array
    int secondSelector=rand()%counterTwo+0;
    Airport secondDest =airportArray[secondSelector];
    // Do not allow round-trip.
    // If second hop brings you back to origin,
    // then assume passenger is only taking the first hop.



    // Initialize the passenger
    Passenger newPax ;
    newPax.Initialize(newPax.GetID(),chosenAirport.GetID(),secondDest.GetID());

    // Try to assign to flights
    // Use try/catch to see if there is a seat, or if passenger is stranded



    try{
//loop to assign the passenger to the first hop flight
        for(int i=0;i<NUM_FLIGHTS;i++){
            if(flights[i].GetOrigin()==chosenAirport.GetID()&&flights[i].GetDest()==firstDestination.GetID()){
                if(flights[i].GetEmptySeats()>0){
                    flights[i].AddPax(newPax);
                }else {
                    //if passenger is stranded it increments stranded pax in the dailyresults object
                    throw newLog.strandedPax++;
                }
            }
        }
        //loop to assign the passenger to the appropriate second hop flight
        for(int i=0;i<NUM_FLIGHTS;i++){
            if(flights[i].GetOrigin()==firstDestination.GetID()&&flights[i].GetDest()==secondDest.GetID()){
                if(flights[i].GetEmptySeats()>0){
                    flights[i].AddPax(newPax);
                }else {
                    //if passenger is stranded it increments stranded pax in the dailyresults object

                    throw newLog.strandedPax++;
                }
            }

        }
    }//catches the exception
    catch(int strandedPassengers){
        //cout<<"Passenger is stranded :"<<strandedPassengers<<endl;
    }



    return newPax;
}
