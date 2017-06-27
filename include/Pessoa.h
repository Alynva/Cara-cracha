#ifndef PESSOA_H
#define PESSOA_H

#include <iostream>
#include "Carteirinha.h"
#include "GeoA.h"

class Pessoa {
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
		int blusa;
		int cor_da_blusa;
		int calca;
		int cor_da_calca;
		int tenis;
		int cor_do_tenis;
		Carteirinha cart;
		
		Pessoa();
		Pessoa(bool, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int, int);
		
};

Pessoa::Pessoa() {
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
	this->blusa = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cor_da_blusa = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->calca = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cor_da_calca = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->tenis = GeoA::map(GeoA::random(), 0, 1, 1, 4);
	this->cor_do_tenis = GeoA::map(GeoA::random(), 0, 1, 1, 4);

	if (GeoA::random() > 0.05) {
		Carteirinha cart_temp(this->sexo, this->rosto, this->cor_do_rosto, this->oculos, this->cor_do_oculos, this->cabelo, this->cor_do_cabelo, this->chapeu, this->cor_do_chapeu, this->barba, this->cor_da_barba);
		this->cart = cart_temp;
	}
}

Pessoa::Pessoa(bool ps, int pr, int pcr, int po, int pco, int pc, int pcc, int pch, int pcch, int pb, int pcb, int pba, int pcba, int pca, int pcca, int pt, int pct):sexo(ps), rosto(pr), cor_do_rosto(pcr), oculos(po), cor_do_oculos(pco), cabelo(pc), cor_do_cabelo(pcc), chapeu(pch), cor_do_chapeu(pcch), barba(pba), cor_da_barba(pcba), blusa(pb), cor_da_blusa(pcb), calca(pca), cor_da_calca(pcca), tenis(pt), cor_do_tenis(pct) {
}

#endif