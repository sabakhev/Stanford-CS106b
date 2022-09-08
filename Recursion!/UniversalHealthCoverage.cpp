/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */

bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result){
	if(cities.isEmpty()){
		return true;
	}
	if(locations.isEmpty() || numHospitals == 0) {
		return false;
	}
	Set <string> hospital = locations[locations.size() - 1];
	locations.remove(locations.size() - 1);
	Vector< Set<string> > locationsCopy = locations;
	result.add(hospital);
	if(canOfferUniversalCoverage(cities - hospital, locationsCopy, numHospitals - 1, result)){
		return true;
	}
	if(!result.isEmpty()){
		result.remove(result.size() - 1);
	}
	if(canOfferUniversalCoverage(cities, locations, numHospitals, result)){
		return true;
	}
	result.clear();
	return false;
}


int main() {
    return 0;
}

