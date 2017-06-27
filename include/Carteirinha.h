#ifndef CARTEIRINHA_H
#define CARTEIRINHA_H

#include "GeoA.h"

class Carteirinha {
	public:
		bool sexo;
		int rosto;
		int cor_do_rosto;
		int oculos;
		int cor_do_oculos;
		int cabelo;
		int cor_do_cabelo;
		int chapeu;
		int cor_do_chapeu;
		int barba;
		int cor_da_barba;
		
		Carteirinha();
		Carteirinha(bool, int, int, int, int, int, int, int, int, int, int);
		
};

Carteirinha::Carteirinha() {
	/*
	this->sexo = GeoA::random() > 0.5;

	this->rosto = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cor_do_rosto = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->oculos = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cor_do_oculos = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cabelo = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cor_do_cabelo = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->chapeu = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cor_do_chapeu = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->barba = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cor_da_barba = GeoA::map(GeoA::random(), 0, 1, 1, 4);
*/
}

Carteirinha::Carteirinha(bool ps, int pr, int pcr, int po, int pco, int pc, int pcc, int pch, int pcch, int pb, int pcb):sexo(ps), rosto(pr), cor_do_rosto(pcr), oculos(po), cor_do_oculos(pco), cabelo(pc), cor_do_cabelo(pcc), chapeu(pch), cor_do_chapeu(pcch), barba(pb), cor_da_barba(pcb) {

}

#endif