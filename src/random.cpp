#include "../include/GeoA.h"
#include <cstdlib> // srand, rand
#include <ctime> // time

#include <iostream>
using namespace std;

void GeoA::randInit() {
	srand(time(NULL));
}

double GeoA::random() {
	return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}
double GeoA::random(double X) {
	return static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/X));
}
double GeoA::random(double LO, double HI) {
	return LO + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(HI-LO)));
}