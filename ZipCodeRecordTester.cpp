#include <string>
#include <iostream>
#include <vector>
#include "stdint.h"
#include "ZipCodeRecord.h"


int main(){
    int zipCode = 4000;
    double latlong = 40.0;
    std::string place = "Test City";
    std::string state = "TS";
    std::string county = "Test County";

    std::cout << "Constructor Tests:\n";
    ZipCodeRecord a;
    ZipCodeRecord b(zipCode, latlong, latlong, place, state, county);
    std::cout << "Success!\n\n";
    std::cout << "Getter Tests:\n";
    std::cout << "Get ZipCode: " << (zipCode == b.getZipCode()) << "\n";
    std::cout << "Get Latitude: " << (latlong == b.getLatitude()) << "\n";
    std::cout << "Get Longitude: " << (latlong == b.getLongitude()) << "\n";
    std::cout << "Get Location Name: " << (place == b.getLocationName()) << "\n";
    std::cout << "Get State Code: " << (state == b.getState()) << "\n";
    std::cout << "Get County Name: " << (county == b.getCounty()) << "\n";
    std::cout << "Success!\n\n";
    std::cout << "Setter Tests:\n";
    std::cout << "Set ZipCode: " << (a.setZipCode(zipCode) && zipCode == a.getZipCode()) << "\n";
    std::cout << "Set Latitude: " << (a.setLatitude(latlong) && latlong == a.getLatitude()) << "\n";
    std::cout << "Set Longitude: " << (a.setLongitude(latlong) && latlong == a.getLongitude()) << "\n";
    std::cout << "Set Location Name: " << (a.setLocationName(place) && place == a.getLocationName()) << "\n";
    std::cout << "Set State Code: " << (a.setState(state) && state == a.getState()) << "\n";
    std::cout << "Set County Name: " << (a.setCounty(county) && county == a.getCounty()) << "\n";
}