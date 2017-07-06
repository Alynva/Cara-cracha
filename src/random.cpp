#include "../include/GeoA.h"
#include <cstdlib> // srand, rand
#include <ctime> // time

void GeoA::randInit() {
	srand(time(NULL));
}

double GeoA::random() {
	return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}
double GeoA::random(double X) {
	return static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/X));
}
int GeoA::random(int LO, int HI) {
	return LO + static_cast <int> (rand()) /( static_cast <int> (RAND_MAX/(HI-LO)));
}
double GeoA::random(double LO, double HI) {
	return LO + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(HI-LO)));
}
int GeoA::randomX(int LO, int HI) {
	double r = LO + static_cast <double> (rand()) /( static_cast <double> (RAND_MAX/(HI-LO)));
	return r > LO && r < HI ? r : GeoA::randomX(LO, HI);
}