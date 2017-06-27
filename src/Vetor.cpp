#include "../include/GeoA.h"
#include <string> // string
#include <cstring> // strcpy
#include <cmath> // mathematical functions
#include <iostream> // std

char* GeoA::Vetor::toString() const {
	std::string str = "Objeto GeoA::Vetor : [";
	str += std::to_string(this->x);
	str += ",";
	str += std::to_string(this->y);
	str += ",";
	str += std::to_string(this->z);
	str += "]";
	
	char* temp = new char[str.size()+1];
	strcpy(temp, str.c_str());

	return temp;
}
GeoA::Vetor* GeoA::Vetor::set(double px, double py, double pz) {
	this->x = px;
	this->y = py;
	this->z = pz;
	return this;
}
GeoA::Vetor* GeoA::Vetor::set(GeoA::Vetor* pv) {
	this->x = pv->x;
	this->y = pv->y;
	this->z = pv->z;
	return this;
}
GeoA::Vetor* GeoA::Vetor::copy() const {
	return new GeoA::Vetor(this->x, this->y, this->z);
}

GeoA::Vetor* GeoA::Vetor::add(double px, double py, double pz) {
	this->x += px;
	this->y += py;
	this->z += pz;
	return this;
}
GeoA::Vetor* GeoA::Vetor::add(const GeoA::Vetor* pv) {
	this->x += pv->x;
	this->y += pv->y;
	this->z += pv->z;
	return this;
}
GeoA::Vetor* GeoA::Vetor::add(GeoA::Vetor* pv1, GeoA::Vetor* pv2) {
	return new GeoA::Vetor(pv1->x + pv2->y, pv1->y + pv2->y, pv1->z + pv2->z);
}
GeoA::Vetor* GeoA::Vetor::sub(double px, double py, double pz) {
	this->x -= px;
	this->y -= py;
	this->z -= pz;
	return this;
}
GeoA::Vetor* GeoA::Vetor::sub(const GeoA::Vetor* pv) {
	this->x -= pv->x;
	this->y -= pv->y;
	this->z -= pv->z;
	return this;
}
GeoA::Vetor* GeoA::Vetor::sub(const GeoA::Vetor* pv1, const GeoA::Vetor* pv2) {
	double x = pv2->x - pv1->x;
	double y = pv2->y - pv1->y;
	double z = pv2->z - pv1->z;
	return new Vetor(x, y, z);
}
GeoA::Vetor* GeoA::Vetor::mult(double scl) {
	this->x *= scl;
	this->y *= scl;
	this->z *= scl;
	return this;
}
GeoA::Vetor* GeoA::Vetor::div(double scl) {
	this->x /= scl;
	this->y /= scl;
	this->z /= scl;
	return this;
}
double GeoA::Vetor::mag() {
	return sqrt(this->magSq());
}
double GeoA::Vetor::magSq() {
	return (this->x * this->x + this->y * this->y + this->z * this->z);
}

double GeoA::Vetor::dot(GeoA::Vetor* pv1, GeoA::Vetor* pv2) {
	return (pv1->x * pv2->x + pv1->y * pv2->y + pv1->z * pv2->z);
}
GeoA::Vetor* GeoA::Vetor::cross(GeoA::Vetor* pv) const {
	double x = this->y * pv->z - this->z * pv->y;
	double y = this->z * pv->x - this->x * pv->z;
	double z = this->x * pv->y - this->y * pv->x;
	return new GeoA::Vetor(x, y, z);
}
double GeoA::Vetor::dist(const GeoA::Vetor* pv) const {
	GeoA::Vetor* temp = pv->copy()->sub(this);
	return temp->mag();
}
GeoA::Vetor* GeoA::Vetor::normalize() {
	return this->mag() == 0 || this->mag() == 1 ? this : this->div(this->mag());
}
GeoA::Vetor* GeoA::Vetor::limit(double max) {
	double aSq = this->magSq();
	if (aSq > max * max) {
		this->div(sqrt(aSq)); // normalize it
		this->mult(max);
	}
	return this;
}
GeoA::Vetor* GeoA::Vetor::setMag(double mag) {
	return this->normalize()->mult(mag);
}
double GeoA::Vetor::heading() const {
	return atan2(this->y, this->x);
}
GeoA::Vetor* GeoA::Vetor::rotate(double a) {
	double newHeading = this->heading() + a;
	double mag = this->mag();
	this->x = cos(newHeading) * mag;
	this->y = sin(newHeading) * mag;
	return this;
}
double GeoA::Vetor::angleBetween(GeoA::Vetor* pv1, GeoA::Vetor* pv2) {
	return acos(GeoA::Vetor::dot(pv1, pv2) / (pv1->mag() * pv2->mag()));
}

GeoA::Vetor* GeoA::Vetor::lerp(GeoA::Vetor* pv1, GeoA::Vetor* pv2, double amt) {
	Vetor* target = pv1->copy();
	target->x += (pv2->x - pv1->x) * amt;
	target->y += (pv2->y - pv1->y) * amt;
	target->z += (pv2->z - pv1->z) * amt;
	return target;
}
double* GeoA::Vetor::array() const {
	double* data = new double[3];
	data[0] = this->x;
	data[1] = this->y;
	data[2] = this->z;
	return data;
}
bool GeoA::Vetor::equals(GeoA::Vetor* pv1, GeoA::Vetor* pv2) {
	return (pv1->x == pv2->x && pv1->y == pv2->y && pv1->z == pv2->z);
}
GeoA::Vetor* GeoA::Vetor::fromAngle(double angle) {
	return new GeoA::Vetor(cos(angle), sin(angle), 0);
}
GeoA::Vetor* GeoA::Vetor::random2D() {
	return GeoA::Vetor::fromAngle(GeoA::random() * GeoA::PI * 2);;
}
GeoA::Vetor* GeoA::Vetor::random3D() {
	double angle = GeoA::random() * GeoA::PI * 2;
	double vz = GeoA::random() * 2 - 1;
	double vx = sqrt(1 - vz * vz) * cos(angle);
	double vy = sqrt(1 - vz * vz) * sin(angle);
	return new GeoA::Vetor(vx, vy, vz);
}
