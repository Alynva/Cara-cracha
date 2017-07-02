#ifndef PESSOA_H
#define PESSOA_H

#include "Carteirinha.h"

#define CHANCE_N_OCULOS 0.75 // Chance da pessoa não possuir óculos
#define CHANCE_N_BARBA 0.8 // Chance da pessoa não possuir barba
#define CHANCE_CART_DIF 0.5 // Chance da carteirinha ser de uma pessoa diferente

class Pessoa {

	public:
		GeoA::Vetor pos;
		GeoA::Vetor target;
		GeoA::Vetor vel;
		GeoA::Vetor acc;
		double max_speed;
		double max_force;

		bool sexo;
		Textura t_corpo;
		int rosto;
		int cor_do_rosto;
		Textura t_rosto;
		int oculos;
		int cor_do_oculos;
		Textura t_oculos;
		int cabelo;
		int cor_do_cabelo;
		Textura t_cabelo;
		int barba;
		int cor_da_barba;
		Textura t_barba;
		int blusa;
		int cor_da_blusa;
		Textura t_blusa;
		int calca;
		int cor_da_calca;
		Textura t_calca;
		int tenis;
		int cor_do_tenis;
		Textura t_tenis;
		Carteirinha cart;
		
		Pessoa();
		Pessoa(bool, int, int, int, int, int, int, int, int, int, int, int, int, int, int);

		void initTextures(SDL_Renderer*);
		Pessoa* update();
		Pessoa* updateTexPos();

		Pessoa* applyForce(const GeoA::Vetor*);
		Pessoa* behaviors();
		GeoA::Vetor* arrive(const GeoA::Vetor*);

		Pessoa* render();
};

inline Pessoa::Pessoa():max_speed(10), max_force(.01) {
	this->pos = GeoA::Vetor(GeoA::random(0, 1000), GeoA::random(0, 700), 0);
	this->target = GeoA::Vetor(0,0,0);

	this->sexo = GeoA::random() > 0.5;

	this->rosto = GeoA::random(1, 4);
	this->cor_do_rosto = GeoA::random(1, 4);
	this->oculos = GeoA::random() > CHANCE_N_OCULOS ? GeoA::random(1, 4) : -1;
	this->cor_do_oculos = GeoA::random(1, 4);
	this->cabelo = GeoA::random(1, 4);
	this->cor_do_cabelo = GeoA::random(1, 4);
	this->barba = GeoA::random() > CHANCE_N_BARBA ? GeoA::random(1, 4) : -1;
	this->cor_da_barba = this->cor_do_cabelo;
	this->blusa = GeoA::random(1, 4);
	this->cor_da_blusa = GeoA::random(1, 4);
	this->calca = GeoA::random(1, 4);
	this->cor_da_calca = GeoA::random(1, 4);
	this->tenis = GeoA::random(1, 4);
	this->cor_do_tenis = GeoA::random(1, 4);

	if (GeoA::random() > CHANCE_CART_DIF) {
		Carteirinha cart_temp(this->sexo, this->rosto, this->cor_do_rosto, this->oculos, this->cor_do_oculos, this->cabelo, this->cor_do_cabelo, this->barba, this->cor_da_barba, this->blusa, this->cor_da_blusa);
		this->cart = cart_temp;
	}

	//this->initTextures(nullptr);
}

inline Pessoa::Pessoa(bool ps, int pr, int pcr, int po, int pco, int pc, int pcc, int pb, int pcb, int pba, int pcba, int pca, int pcca, int pt, int pct):max_speed(.3), max_force(3), sexo(ps), rosto(pr), cor_do_rosto(pcr), oculos(po), cor_do_oculos(pco), cabelo(pc), cor_do_cabelo(pcc), barba(pba), cor_da_barba(pcba), blusa(pb), cor_da_blusa(pcb), calca(pca), cor_da_calca(pcca), tenis(pt), cor_do_tenis(pct) {

	//this->initTextures(nullptr);
}

inline void Pessoa::initTextures(SDL_Renderer* renderer) {
	string path_imgs = "../media/avatar/";
	
	string path_corpo = path_imgs+"body/corpo_c"+std::to_string(this->cor_do_rosto)+".png";
	this->t_corpo = Textura(path_corpo, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);

	string path_rosto = path_imgs+"head/"+std::to_string(this->sexo)+"_t"+std::to_string(this->rosto)+"_c"+std::to_string(this->cor_do_rosto)+".png";
	this->t_rosto = Textura(path_rosto, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	string path_cabelo = path_imgs+"head/cabelo_"+std::to_string(this->sexo)+"_t"+std::to_string(this->cabelo)+"_c"+std::to_string(this->cor_do_cabelo)+".png";
	this->t_cabelo = Textura(path_cabelo, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	string path_barba = this->barba > 0 ? path_imgs+"head/barba_"+std::to_string(this->sexo)+"_t"+std::to_string(this->barba)+"_c"+std::to_string(this->cor_da_barba)+".png" : path_imgs+"0.png";
	this->t_barba = Textura(path_barba, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	string path_oculos = this->oculos > 0 ? path_imgs+"head/oculos_t"+std::to_string(this->oculos)+"_c"+std::to_string(this->cor_do_oculos)+".png" : path_imgs+"0.png";
	this->t_oculos = Textura(path_oculos, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//string path_blusa = path_imgs+"body/blusa_"+std::to_string(this->sexo)+"_t"+std::to_string(this->blusa)+"_c"+std::to_string(this->cor_da_blusa)+".png";
	string path_blusa = path_imgs+"body/blusa_"+std::to_string(this->sexo)+"_t1_c2.png";
	this->t_blusa = Textura(path_blusa, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//string path_calca = path_imgs+"body/calca_"+std::to_string(this->sexo)+"_t"+std::to_string(this->calca)+"_c"+std::to_string(this->cor_da_calca)+".png";
	string path_calca = path_imgs+"body/calca_"+std::to_string(this->sexo)+"_t3_c1.png";
	this->t_calca = Textura(path_calca, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//string path_tenis = path_imgs+"body/tenis_"+std::to_string(this->sexo)+"_t"+std::to_string(this->tenis)+"_c"+std::to_string(this->cor_do_tenis)+".png";
	string path_tenis = path_imgs+"body/tenis_"+std::to_string(this->sexo)+"_t1_c3.png";
	this->t_tenis = Textura(path_tenis, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);

	this->cart.initTextures(renderer);
}

inline Pessoa* Pessoa::update() {
	this->pos.add(&this->vel);
	this->vel.add(&this->acc);
	this->acc.mult(0);

	this->updateTexPos();

	return this;
}

inline Pessoa* Pessoa::updateTexPos() {
	this->t_corpo.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	this->t_rosto.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	this->t_cabelo.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	this->t_barba.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	this->t_oculos.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	this->t_blusa.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	this->t_calca.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	this->t_tenis.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});

	return this;
}

inline Pessoa* Pessoa::applyForce(const GeoA::Vetor* force) {
	this->acc.add(force);
	
	return this;
}

inline Pessoa* Pessoa::behaviors() {
	if (this->pos != this->target)
		this->vel = this->arrive(&this->target)->limit(this->max_speed);
	else if (this->vel.mag() > 0)
		this->vel.mult(0);

	return this;
}

inline GeoA::Vetor* Pessoa::arrive(const GeoA::Vetor* target) {
	return GeoA::Vetor::sub(&this->pos, target);
}

inline Pessoa* Pessoa::render() {
	this->t_corpo.render();
	this->t_rosto.render();
	this->t_cabelo.render();
	this->t_barba.render();
	this->t_oculos.render();
	this->t_blusa.render();
	this->t_calca.render();
	this->t_tenis.render();

	return this;
}

#endif