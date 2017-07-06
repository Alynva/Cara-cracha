#include "../include/Pessoa.h"

Textura Pessoa::tex = Textura();

Pessoa::Pessoa():max_speed(10), max_force(.01) {
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
		Carteirinha cart_temp(this->sexo, this->rosto, this->cor_do_rosto, this->cabelo);
		//this->cart = cart_temp;
	}
}

Pessoa::Pessoa(bool ps, int pr, int pcr, int po, int pco, int pc, int pcc, int pb, int pcb, int pba, int pcba, int pca, int pcca, int pt, int pct):max_speed(.3), max_force(3), sexo(ps), rosto(pr), cor_do_rosto(pcr), oculos(po), cor_do_oculos(pco), cabelo(pc), cor_do_cabelo(pcc), barba(pba), cor_da_barba(pcba), blusa(pb), cor_da_blusa(pcb), calca(pca), cor_da_calca(pcca), tenis(pt), cor_do_tenis(pct) {
}

Pessoa* Pessoa::initTextures(SDL_Renderer* renderer) {
	if (this->tex.getRenderer() == nullptr) {
		this->tex.setPath("../media/avatar/Corpo/std.png");
		this->tex.setRenderer(renderer);
		this->tex.setTexture(this->tex.loadTexture());
	}

	this->t_corpo.setPath(this->tex.getPath());
	this->t_corpo.setRenderer(this->tex.getRenderer());
	this->t_corpo.setTexture(this->tex.getTexture());
	this->t_corpo.setSrcrect({45, 0, 25, 56});
	this->t_corpo.setFormat({0, 0, 25, 56});


	this->t_braco_e.setPath(this->tex.getPath());
	this->t_braco_e.setRenderer(this->tex.getRenderer());
	this->t_braco_e.setTexture(this->tex.getTexture());
	this->t_braco_e.setSrcrect({26, 55, 5, 27});
	this->t_braco_e.setFormat({0, 0, 5, 27});


	this->t_braco_d.setPath(this->tex.getPath());
	this->t_braco_d.setRenderer(this->tex.getRenderer());
	this->t_braco_d.setTexture(this->tex.getTexture());
	this->t_braco_d.setSrcrect({26, 150, 9, 33});
	this->t_braco_d.setFormat({0, 0, 9, 33});


	this->t_cabeca.setPath(this->tex.getPath());
	this->t_cabeca.setRenderer(this->tex.getRenderer());
	this->t_cabeca.setTexture(this->tex.getTexture());
	this->t_cabeca.setSrcrect({0, 56, 26, 31});
	this->t_cabeca.setFormat({0, 0, 26, 31});


	//std::string path_imgs = "../media/avatar/";
	
	//std::string path_corpo = path_imgs+"body/corpo_c"+std::to_string(this->cor_do_rosto)+".png";
	//this->t_corpo = Textura(path_corpo, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);

	//std::string path_rosto = path_imgs+"head/"+std::to_string(this->sexo)+"_t"+std::to_string(this->rosto)+"_c"+std::to_string(this->cor_do_rosto)+".png";
	//this->t_rosto = Textura(path_rosto, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);

	//std::string path_cabelo = path_imgs+"head/cabelo_"+std::to_string(this->sexo)+"_t"+std::to_string(this->cabelo)+"_c"+std::to_string(this->cor_do_cabelo)+".png";
	//this->t_cabelo = Textura(path_cabelo, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//std::string path_barba = this->barba > 0 ? path_imgs+"head/barba_"+std::to_string(this->sexo)+"_t"+std::to_string(this->barba)+"_c"+std::to_string(this->cor_da_barba)+".png" : path_imgs+"0.png";
	//this->t_barba = Textura(path_barba, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//std::string path_oculos = this->oculos > 0 ? path_imgs+"head/oculos_t"+std::to_string(this->oculos)+"_c"+std::to_string(this->cor_do_oculos)+".png" : path_imgs+"0.png";
	//this->t_oculos = Textura(path_oculos, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//std::string path_blusa = path_imgs+"body/blusa_"+std::to_string(this->sexo)+"_t"+std::to_string(this->blusa)+"_c"+std::to_string(this->cor_da_blusa)+".png";
	//std::string path_blusa = path_imgs+"body/blusa_"+std::to_string(this->sexo)+"_t1_c2.png";
	//this->t_blusa = Textura(path_blusa, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//std::string path_calca = path_imgs+"body/calca_"+std::to_string(this->sexo)+"_t"+std::to_string(this->calca)+"_c"+std::to_string(this->cor_da_calca)+".png";
	//std::string path_calca = path_imgs+"body/calca_"+std::to_string(this->sexo)+"_t3_c1.png";
	//this->t_calca = Textura(path_calca, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);
	
	//std::string path_tenis = path_imgs+"body/tenis_"+std::to_string(this->sexo)+"_t"+std::to_string(this->tenis)+"_c"+std::to_string(this->cor_do_tenis)+".png";
	//std::string path_tenis = path_imgs+"body/tenis_"+std::to_string(this->sexo)+"_t1_c3.png";
	//this->t_tenis = Textura(path_tenis, renderer, this->pos.x - 67, this->pos.y - 206, 128, 220);

	//this->cart.initTextures(renderer);

	return this;
}

Pessoa* Pessoa::update() {
	this->pos.add(&this->vel);
	this->vel.add(&this->acc);
	this->acc.mult(0);

	this->updateTexPos();

	return this;
}

Pessoa* Pessoa::updateTexPos() {
	// x - 67; y - 20
	int pos_desloc_x = this->pos.x - 14;
	int pos_desloc_y = this->pos.y - 62;
	this->t_corpo.setPosition({pos_desloc_x, pos_desloc_y});
	this->t_braco_e.setPosition({pos_desloc_x + 21, pos_desloc_y + 3});
	this->t_braco_d.setPosition({pos_desloc_x - 4, pos_desloc_y + 6});
	this->t_cabeca.setPosition({pos_desloc_x - 2, pos_desloc_y - 24});
	//this->t_cabelo.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	//this->t_barba.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	//this->t_oculos.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	//this->t_blusa.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	//this->t_calca.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});
	//this->t_tenis.setPosition({int (this->pos.x - 67), int (this->pos.y - 206)});

	return this;
}

Pessoa* Pessoa::applyForce(const GeoA::Vetor* force) {
	this->acc.add(force);
	
	return this;
}

Pessoa* Pessoa::behaviors() {
	if (this->pos != this->target)
		this->vel = this->arrive(&this->target)->limit(this->max_speed);
	else if (this->vel.mag() > 0)
		this->vel.mult(0);

	return this;
}

GeoA::Vetor* Pessoa::arrive(const GeoA::Vetor* target) {
	return GeoA::Vetor::sub(&this->pos, target);
}

Pessoa* Pessoa::render() {
	this->t_braco_e.render();
	this->t_corpo.render();
	this->t_braco_d.render();
	this->t_cabeca.render();
	//this->t_cabelo.render();
	//this->t_barba.render();
	//this->t_oculos.render();
	//this->t_blusa.render();
	//this->t_calca.render();
	//this->t_tenis.render();

	return this;
}