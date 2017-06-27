#include "../include/GeoA.h"

double GeoA::map(double value, double start1, double stop1, double start2, double stop2) {
	return ((value - start1) / (stop1 - start1)) * (stop2 - start2) + start2;
}
