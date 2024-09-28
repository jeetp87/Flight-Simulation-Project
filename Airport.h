#ifndef FP02_AIRPORT_H
#define FP02_AIRPORT_H

#include <iostream>
#include <fstream>

using namespace std;

class Airport{
public:
    Airport(){}//cout<< "Creating blank airport";}
    Airport(Airport & );//Copy constructor
    Airport(string newID){IATA=newID;}
    void Initialize(string newID, string newCity, long double newlong,long double newlat);

    //ostream& operator <<(ostream&);
   // ofstream& operator << (ofstream&);
    //bool operator == (Airport);

    long double GetLat(){return latitude;}
    long double GetLong(){return longitude;}
    string GetCity(){return city;}
    string GetID(){return IATA;}
    void Print(){
        cout<<"Airport ID: "<<IATA<<"\n Airport City: "<<city<<endl;
    }
private:
    long double longitude,latitude;
    string IATA, city;


};
#endif //FP02_AIRPORT_H