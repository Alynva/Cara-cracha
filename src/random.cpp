#include "GeoA.h"
#include <cstdlib> // srand, rand
#include <ctime> // time

double GeoA::random() {
	srand (static_cast <unsigned> (time(NULL)));
	return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}
double GeoA::random(double X) {
	srand (static_cast <unsigned> (time(NULL)));
	return static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/X));
}
double GeoA::random(double LO, double HI) {
	srand (static_cast <unsigned> (time(NULL)));
	return LO + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(HI-LO)));
}
