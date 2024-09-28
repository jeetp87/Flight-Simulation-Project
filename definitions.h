//
// Created by patel on 4/20/2024.
//

#ifndef FP02_DEFINITIONS_H
#define FP02_DEFINITIONS_H
#include <fstream>
using namespace std;

const int NUM_AIRPORTS = 10;
const int NUM_FLIGHTS = 19;
ofstream logFile;  // As a Global, so we can use in many functions
ifstream routes;
const int PAX_PER_DAY = 400;
bool DEBUG = true;


struct dailyResult{
    float revenue;
    float opCosts;
    int strandedPax;
    int emptySeats;
};
#endif //FP02_DEFINITIONS_H
