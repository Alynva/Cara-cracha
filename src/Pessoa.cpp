#include "../include/Pessoa.h"

Textura Pessoa::tex = Textura();

Pessoa::Pessoa():max_speed(10), max_force(.01), direcao(0) {
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

Pessoa::Pessoa(bool ps, int pr, int pcr, int po, int pco, int pc, int pcc, int pb, int pcb, int pba, int pcba, int pca, int pcca, int pt, int pct):
	max_speed(.3),
	max_force(3),
	direcao(0),
	sexo(ps),
	rosto(pr),
	cor_do_rosto(pcr),
	oculos(po),
	cor_do_oculos(pco),
	cabelo(pc),
	cor_do_cabelo(pcc),
	barba(pba),
	cor_da_barba(pcba),
	blusa(pb),
	cor_da_blusa(pcb),
	calca(pca),
	cor_da_calca(pcca),
	tenis(pt),
	cor_do_tenis(pct) {
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


	this->t_braco_e.setPath(this->tex.getPath());
	this->t_braco_e.setRenderer(this->tex.getRenderer());
	this->t_braco_e.setTexture(this->tex.getTexture());

	this->t_braco_d.setPath(this->tex.getPath());
	this->t_braco_d.setRenderer(this->tex.getRenderer());
	this->t_braco_d.setTexture(this->tex.getTexture());


	this->t_cabeca.setPath(this->tex.getPath());
	this->t_cabeca.setRenderer(this->tex.getRenderer());
	this->t_cabeca.setTexture(this->tex.getTexture());


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


	if (this->vel.magSq()) {
		double angle = this->vel.heading();
		
		if (angle < 0 && angle > -GeoA::HALF_PI)
			this->direcao = 0;
		else if (angle == 0)
			this->direcao = 1;
		else if (angle > 0 && angle < GeoA::HALF_PI)
			this->direcao = 2;
		else if (angle == GeoA::HALF_PI)
			this->direcao = 3;
		else if (angle < GeoA::PI && angle > GeoA::HALF_PI)
			this->direcao = 4;
		else if (angle == GeoA::PI)
			this->direcao = 5;
		else if (angle > -GeoA::PI && angle < -GeoA::HALF_PI)
			this->direcao = 6;
		else if (angle == -GeoA::HALF_PI)
			this->direcao = 7;

	}

	this->updateTexPos();

	return this;
}

Pessoa* Pessoa::updateTexPos() {
	// x - 67; y - 20
	int pos_desloc_x = this->pos.x - 14*2;
	int pos_desloc_y = this->pos.y - 60*2;

	switch (this->direcao) {
		case 0:
			this->t_corpo.setSrcrect({0, 0, 25, 56});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 25*2, 56*2});

			this->t_braco_e.setSrcrect({171, 0, 5, 26});
			this->t_braco_e.setFormat({pos_desloc_x - 3*2, pos_desloc_y + 4*2, 5*2, 26*2});

			this->t_braco_d.setSrcrect({165, 117, 11, 33});
			this->t_braco_d.setFormat({pos_desloc_x + 17*2, pos_desloc_y + 6*2, 11*2, 33*2});

			this->t_cabeca.setSrcrect({122, 56, 27, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 24*2, 27*2, 28*2});
			break;
		case 6:
			this->t_corpo.setSrcrect({0, 0, 25, 56});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 25*2, 56*2});

			this->t_braco_e.setSrcrect({171, 0, 5, 26});
			this->t_braco_e.setFormat({pos_desloc_x + 23*2, pos_desloc_y + 4*2, 5*2, 26*2});

			this->t_braco_d.setSrcrect({165, 117, 11, 33});
			this->t_braco_d.setFormat({pos_desloc_x - 3*2, pos_desloc_y + 5*2, 11*2, 33*2});

			this->t_cabeca.setSrcrect({122, 56, 27, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 0*2, pos_desloc_y - 24*2, 27*2, 28*2});
			break;

		case 1:
			this->t_corpo.setSrcrect({25, 0, 20, 53});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 20*2, 53*2});

			//this->t_braco_e.setSrcrect({26, 55, 5, 27});
			this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 3*2, 0, 0});

			this->t_braco_d.setSrcrect({31, 55, 9, 29});
			this->t_braco_d.setFormat({pos_desloc_x + 3*2, pos_desloc_y + 7*2, 9*2, 29*2});

			this->t_cabeca.setSrcrect({117, 28, 27, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 5*2, pos_desloc_y - 24*2, 27*2, 28*2});
			break;
		case 5:
			this->t_corpo.setSrcrect({25, 0, 20, 53});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 20*2, 53*2});

			//this->t_braco_e.setSrcrect({26, 55, 5, 27});
			this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 3*2, 0, 0});

			this->t_braco_d.setSrcrect({31, 55, 9, 29});
			this->t_braco_d.setFormat({pos_desloc_x + 8*2, pos_desloc_y + 7*2, 9*2, 29*2});

			this->t_cabeca.setSrcrect({117, 28, 27, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 1*2, pos_desloc_y - 23*2, 27*2, 28*2});
			break;

		case 2:
			this->t_corpo.setSrcrect({45, 0, 25, 56});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 25*2, 56*2});

			this->t_braco_e.setSrcrect({26, 55, 5, 27});
			this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 3*2, 5*2, 27*2});

			this->t_braco_d.setSrcrect({26, 150, 9, 33});
			this->t_braco_d.setFormat({pos_desloc_x - 4*2, pos_desloc_y + 6*2, 9*2, 33*2});

			this->t_cabeca.setSrcrect({0, 56, 26, 31});
			this->t_cabeca.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 24*2, 26*2, 31*2});
			break;
		case 4:
			this->t_corpo.setSrcrect({45, 0, 25, 56});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 25*2, 56*2});

			this->t_braco_e.setSrcrect({26, 55, 5, 27});
			this->t_braco_e.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 3*2, 5*2, 27*2});

			this->t_braco_d.setSrcrect({26, 150, 9, 33});
			this->t_braco_d.setFormat({pos_desloc_x + 20*2, pos_desloc_y + 6*2, 9*2, 33*2});

			this->t_cabeca.setSrcrect({0, 56, 26, 31});
			this->t_cabeca.setFormat({pos_desloc_x - 0*2, pos_desloc_y - 23*2, 26*2, 31*2});
			break;

		case 3:
			this->t_corpo.setSrcrect({70, 0, 24, 54});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 24*2, 54*2});

			this->t_braco_e.setSrcrect({172, 84, 8, 33});
			this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 8*2, 33*2});

			this->t_braco_d.setSrcrect({35, 150, 8, 33});
			this->t_braco_d.setFormat({pos_desloc_x - 4*2, pos_desloc_y + 2*2, 8*2, 33*2});

			this->t_cabeca.setSrcrect({70, 56, 26, 31});
			this->t_cabeca.setFormat({pos_desloc_x - 1*2, pos_desloc_y - 24*2, 26*2, 31*2});
			break;

		case 7:
			this->t_corpo.setSrcrect({94, 0, 23, 51});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 23*2, 51*2});

			this->t_braco_e.setSrcrect({157, 117, 8, 31});
			this->t_braco_e.setFormat({pos_desloc_x - 5*2, pos_desloc_y + 3*2, 8*2, 31*2});

			this->t_braco_d.setSrcrect({43, 150, 8, 32});
			this->t_braco_d.setFormat({pos_desloc_x + 20*2, pos_desloc_y + 2*2, 8*2, 32*2});

			this->t_cabeca.setSrcrect({96, 56, 26, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 25*2, 26*2, 28*2});
			break;
	}


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

	double angle = this->vel.heading();
	double mag = this->vel.mag();
	if (angle > 0.1 && angle < 0.3) { // O vetor está entre o vetor (0, 0) e (2, 1)
		this->vel.x = 1;
		this->vel.y = 0;
	} else if (angle > 0.5 && angle < 1.4) {
		this->vel.x = 0;
		this->vel.y = 1;
	} else if (angle > 1.6 && angle < 2.5) {
		this->vel.x = 0;
		this->vel.y = 1;
	} else if (angle > 2.7 && angle < 3.0) {
		this->vel.x = -1;
		this->vel.y = 0;
	} else if (angle < -2.4) {
		this->vel.x = -1;
		this->vel.y = 0;
	} else if (angle > -2.5 && angle < -1.6) {
		this->vel.x = 0;
		this->vel.y = -1;
	} else if (angle > -1.4 && angle < -0.5) {
		this->vel.x = 0;
		this->vel.y = -1;
	} else if (angle > -0.3 && angle < -0.9) {
		this->vel.x = 1;
		this->vel.y = 0;
	}
	this->vel.setMag(mag);

	return this;
}

GeoA::Vetor* Pessoa::arrive(const GeoA::Vetor* target) {
	return GeoA::Vetor::sub(&this->pos, target);
}

Pessoa* Pessoa::render() {
	switch (this->cor_do_rosto) {
		case 1:
			SDL_SetTextureColorMod(this->tex.getTexture(), 252, 200, 151);
			break;
		case 2:
			SDL_SetTextureColorMod(this->tex.getTexture(), 199, 144, 99);
			break;
		case 3:
			SDL_SetTextureColorMod(this->tex.getTexture(), 145, 91, 47);
			break;
	}
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	switch (this->direcao) {
		case 4:
		case 5:
		case 6:
			flip = SDL_FLIP_HORIZONTAL;
	}
	this->t_braco_e.render(flip);
	this->t_corpo.render(flip);
	this->t_braco_d.render(flip);
	this->t_cabeca.render(flip);
	//this->t_cabelo.render();
	//this->t_barba.render();
	//this->t_oculos.render();
	//this->t_blusa.render();
	//this->t_calca.render();
	//this->t_tenis.render();


	SDL_SetTextureColorMod(this->tex.getTexture(), 255, 255, 255);

	return this;
}