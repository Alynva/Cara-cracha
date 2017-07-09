#include "../include/Pessoa.h"

Textura Pessoa::tex = Textura();

Pessoa::Pessoa():max_speed(10), max_force(.01), direcao(0) {
	this->target = GeoA::Vetor(0,0,0);

	this->sexo = GeoA::random() > 0.5;

	this->olhos = GeoA::random(1, 3);
	this->cor_do_rosto = GeoA::random(1, 4);
	this->cabelo = GeoA::random(1, 3);
	this->cor_do_cabelo = GeoA::random(1, 7);
	//this->oculos = GeoA::random() > CHANCE_N_OCULOS ? GeoA::random(1, 4) : -1;
	//this->cor_do_oculos = GeoA::random(1, 4);
	//this->barba = GeoA::random() > CHANCE_N_BARBA ? GeoA::random(1, 4) : -1;
	//this->cor_da_barba = this->cor_do_cabelo;
	this->blusa = GeoA::random(1, 2);
	this->cor_da_blusa = GeoA::random(1, 7);
	this->calca = GeoA::random(1, 2);
	this->cor_da_calca = GeoA::random(1, 7);
	this->tenis = GeoA::random(1, 2);
	this->cor_do_tenis = GeoA::random(1, 7);

	if (GeoA::random() > CHANCE_CART_DIF) {
		this->cart = Carteirinha(this->sexo, this->olhos, this->cor_do_rosto, this->cabelo);
	}
}

Pessoa::Pessoa(bool ps, int pol, int pcol, /*int po, int pco, */int pc, int pcc, int pb, int pcb, /*int pba, int pcba, */int pca, int pcca, int pt, int pct):
	max_speed(.3),
	max_force(3),
	direcao(0),
	sexo(ps),
	olhos(pol),
	cor_do_rosto(pcol),
	//oculos(po),
	//cor_do_oculos(pco),
	cabelo(pc),
	cor_do_cabelo(pcc),
	//barba(pba),
	//cor_da_barba(pcba),
	blusa(pb),
	cor_da_blusa(pcb),
	calca(pca),
	cor_da_calca(pcca),
	tenis(pt),
	cor_do_tenis(pct) {
}

Pessoa* Pessoa::initTextures(SDL_Renderer* renderer) {
	if (this->tex.getRenderer() == nullptr) {
		this->tex.setPath("../media/avatar/spritesheet.png");
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


	this->t_nariz_boca.setPath(this->tex.getPath());
	this->t_nariz_boca.setRenderer(this->tex.getRenderer());
	this->t_nariz_boca.setTexture(this->tex.getTexture());


	this->t_olhos.setPath(this->tex.getPath());
	this->t_olhos.setRenderer(this->tex.getRenderer());
	this->t_olhos.setTexture(this->tex.getTexture());


	this->t_cabelo.setPath(this->tex.getPath());
	this->t_cabelo.setRenderer(this->tex.getRenderer());
	this->t_cabelo.setTexture(this->tex.getTexture());


	this->t_blusa.setPath(this->tex.getPath());
	this->t_blusa.setRenderer(this->tex.getRenderer());
	this->t_blusa.setTexture(this->tex.getTexture());
	this->t_blusa_b_d.setPath(this->tex.getPath());
	this->t_blusa_b_d.setRenderer(this->tex.getRenderer());
	this->t_blusa_b_d.setTexture(this->tex.getTexture());
	this->t_blusa_b_e.setPath(this->tex.getPath());
	this->t_blusa_b_e.setRenderer(this->tex.getRenderer());
	this->t_blusa_b_e.setTexture(this->tex.getTexture());


	this->t_calca.setPath(this->tex.getPath());
	this->t_calca.setRenderer(this->tex.getRenderer());
	this->t_calca.setTexture(this->tex.getTexture());


	this->t_tenis.setPath(this->tex.getPath());
	this->t_tenis.setRenderer(this->tex.getRenderer());
	this->t_tenis.setTexture(this->tex.getTexture());


	this->cart.initTextures(renderer);

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
	// Deslocamento para que a posição da Pessoa represente o pé renderizado
	int pos_desloc_x = this->pos.x - 14*2;
	int pos_desloc_y = this->pos.y - 60*2;

	switch (this->direcao) { // Adicionando +309 nas coordenadas x pois o novo esprite está diferente
		case 0:
			this->t_corpo.setSrcrect({0+309, 0, 25, 56});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 25*2, 56*2});

			this->t_braco_e.setSrcrect({171+309, 0, 5, 26});
			this->t_braco_e.setFormat({pos_desloc_x - 3*2, pos_desloc_y + 4*2, 5*2, 26*2});

			this->t_braco_d.setSrcrect({165+309, 117, 11, 33});
			this->t_braco_d.setFormat({pos_desloc_x + 17*2, pos_desloc_y + 6*2, 11*2, 33*2});

			this->t_cabeca.setSrcrect({122+309, 56, 27, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 24*2, 27*2, 28*2});

			//this->t_nariz_boca.setSrcrect({0, 0, 0, 0});
			this->t_nariz_boca.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});

			//this->t_olhos.setSrcrect({, });
			this->t_olhos.setFormat({0, 0, 0, 0});

			if (this->sexo) { // É mulher
				switch (this->cabelo) {
					case 1: // Cabelo 6
						this->t_cabelo.setSrcrect({226, 151, 43, 33});
						this->t_cabelo.setFormat({pos_desloc_x - 9*2, pos_desloc_y - 27*2, 43*2, 33*2});
						break;

					case 2: // Cabelo 11
						this->t_cabelo.setSrcrect({0, 67, 33, 33});
						this->t_cabelo.setFormat({pos_desloc_x - 5*2, pos_desloc_y - 28*2, 33*2, 33*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2405
						this->t_blusa.setSrcrect({269, 172, 27, 33});
						this->t_blusa.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 1*2, 27*2, 33*2});

						this->t_blusa_b_d.setSrcrect({296, 167, 10, 18});
						this->t_blusa_b_d.setFormat({pos_desloc_x + 17*2, pos_desloc_y + 5*2, 10*2, 18*2});

						this->t_blusa_b_e.setSrcrect({250, 10, 5, 12});
						this->t_blusa_b_e.setFormat({pos_desloc_x - 3*2, pos_desloc_y + 4*2, 5*2, 12*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2029
						this->t_calca.setSrcrect({306, 183, 21, 23});
						this->t_calca.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 24*2, 21*2, 23*2});
						break;
				}
				switch (this->tenis) {
					case 1: //Tenis 7
						this->t_tenis.setSrcrect({0, 154, 25, 14});
						this->t_tenis.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 43*2, 25*2, 14*2});
						break;
				}
			} else {// Homem
				switch (this->cabelo) {
					case 1: // Cabelo 30
						this->t_cabelo.setSrcrect({155, 67, 32, 40});
						this->t_cabelo.setFormat({pos_desloc_x - 4*2, pos_desloc_y - 35*2, 32*2, 40*2});
						break;

					case 2: // Cabelo 501
						this->t_cabelo.setSrcrect({44, 151, 36, 32});
						this->t_cabelo.setFormat({pos_desloc_x - 8*2, pos_desloc_y - 27*2, 36*2, 32*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2301
						this->t_blusa.setSrcrect({247, 205, 26, 33});
						this->t_blusa.setFormat({pos_desloc_x - 3*2, pos_desloc_y, 26*2, 33*2});

						this->t_blusa_b_d.setSrcrect({186, 185, 10, 15});
						this->t_blusa_b_d.setFormat({pos_desloc_x + 17*2, pos_desloc_y + 4*2, 10*2, 15*2});

						this->t_blusa_b_e.setSrcrect({303, 10, 6, 10});
						this->t_blusa_b_e.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2037
						this->t_calca.setSrcrect({406, 183, 23, 26});
						this->t_calca.setFormat({pos_desloc_x, pos_desloc_y + 24*2, 23*2, 26*2});
				}
				switch (this->tenis) {
					case 1: //Tenis 3
						this->t_tenis.setSrcrect({133, 134, 26, 13});
						this->t_tenis.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 43*2, 26*2, 13*2});
						break;
				}
			}
			break;
		case 6:
			this->t_corpo.setSrcrect({0+309, 0, 25, 56});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 25*2, 56*2});

			this->t_braco_e.setSrcrect({171+309, 0, 5, 26});
			this->t_braco_e.setFormat({pos_desloc_x + 23*2, pos_desloc_y + 4*2, 5*2, 26*2});

			this->t_braco_d.setSrcrect({165+309, 117, 11, 33});
			this->t_braco_d.setFormat({pos_desloc_x - 3*2, pos_desloc_y + 5*2, 11*2, 33*2});

			this->t_cabeca.setSrcrect({122+309, 56, 27, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 0*2, pos_desloc_y - 24*2, 27*2, 28*2});

			//this->t_nariz_boca.setSrcrect({0, 0, 0, 0});
			this->t_nariz_boca.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});

			//this->t_olhos.setSrcrect({, });
			this->t_olhos.setFormat({0, 0, 0, 0});

			if (this->sexo) { // É mulher
				switch (this->cabelo) {
					case 1: // Cabelo 6
						this->t_cabelo.setSrcrect({226, 151, 43, 33});
						this->t_cabelo.setFormat({pos_desloc_x - 9*2, pos_desloc_y - 27*2, 43*2, 33*2});
						break;

					case 2: // Cabelo 11
						this->t_cabelo.setSrcrect({0, 67, 33, 33});
						this->t_cabelo.setFormat({pos_desloc_x - 3*2, pos_desloc_y - 28*2, 33*2, 33*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2405
						this->t_blusa.setSrcrect({269, 172, 27, 33});
						this->t_blusa.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 1*2, 27*2, 33*2});

						this->t_blusa_b_d.setSrcrect({296, 167, 10, 18});
						this->t_blusa_b_d.setFormat({pos_desloc_x - 2*2, pos_desloc_y + 5*2, 10*2, 18*2});

						this->t_blusa_b_e.setSrcrect({250, 10, 5, 12});
						this->t_blusa_b_e.setFormat({pos_desloc_x + 23*2, pos_desloc_y + 4*2, 5*2, 12*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2029
						this->t_calca.setSrcrect({306, 183, 21, 23});
						this->t_calca.setFormat({pos_desloc_x + 3*2, pos_desloc_y + 24*2, 21*2, 23*2});
						break;
				}
				switch (this->tenis) {
					case 1: //Tenis 7
						this->t_tenis.setSrcrect({0, 154, 25, 14});
						this->t_tenis.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 43*2, 25*2, 14*2});
						break;
				}
			} else { // Homem
				switch (this->cabelo) {
					case 1: // Cabelo 30
						this->t_cabelo.setSrcrect({155, 67, 32, 40});
						this->t_cabelo.setFormat({pos_desloc_x - 3*2, pos_desloc_y - 35*2, 32*2, 40*2});
						break;

					case 2: // Cabelo 501
						this->t_cabelo.setSrcrect({44, 151, 36, 32});
						this->t_cabelo.setFormat({pos_desloc_x - 3*2, pos_desloc_y - 27*2, 36*2, 32*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2301
						this->t_blusa.setSrcrect({247, 205, 26, 33});
						this->t_blusa.setFormat({pos_desloc_x + 2*2, pos_desloc_y, 26*2, 33*2});

						this->t_blusa_b_d.setSrcrect({186, 185, 10, 15});
						this->t_blusa_b_d.setFormat({pos_desloc_x - 2*2, pos_desloc_y + 4*2, 10*2, 15*2});

						this->t_blusa_b_e.setSrcrect({303, 10, 6, 10});
						this->t_blusa_b_e.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2037
						this->t_calca.setSrcrect({406, 183, 23, 26});
						this->t_calca.setFormat({pos_desloc_x + 2*2, pos_desloc_y + 24*2, 23*2, 26*2});
				}
				switch (this->tenis) {
					case 1: //Tenis 3
						this->t_tenis.setSrcrect({133, 134, 26, 13});
						this->t_tenis.setFormat({pos_desloc_x - 2*2, pos_desloc_y + 43*2, 26*2, 13*2});
						break;
				}
			}
			break;

		case 1:
			this->t_corpo.setSrcrect({25+309, 0, 20, 53});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 20*2, 53*2});

			//this->t_braco_e.setSrcrect({26+309, 55, 5, 27});
			this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 3*2, 0, 0});

			this->t_braco_d.setSrcrect({31+309, 55, 9, 29});
			this->t_braco_d.setFormat({pos_desloc_x + 3*2, pos_desloc_y + 7*2, 9*2, 29*2});

			this->t_cabeca.setSrcrect({117+309, 28, 27, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 5*2, pos_desloc_y - 24*2, 27*2, 28*2});

			this->t_nariz_boca.setSrcrect({18, 10, 8, 11});
			this->t_nariz_boca.setFormat({pos_desloc_x + 16*2, pos_desloc_y - 12*2, 8*2, 11*2});

			if (this->sexo) { // É mulher
				switch (this->olhos) {
					case 1: // olhos 2
						this->t_olhos.setSrcrect({72, 0, 5, 6});
						this->t_olhos.setFormat({pos_desloc_x + 14*2, pos_desloc_y - 13*2, 5*2, 6*2});
						break;

					case 2: // olhos 6
						this->t_olhos.setSrcrect({196, 0, 5, 5});
						this->t_olhos.setFormat({pos_desloc_x + 14*2, pos_desloc_y - 13*2, 5*2, 5*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 6
						this->t_cabelo.setSrcrect({276, 104, 31, 30});
						this->t_cabelo.setFormat({pos_desloc_x - 7*2, pos_desloc_y - 26*2, 31*2, 30*2});
						break;

					case 2: // Cabelo 11
						this->t_cabelo.setSrcrect({33, 58, 34, 32});
						this->t_cabelo.setFormat({pos_desloc_x - 12*2, pos_desloc_y - 29*2, 34*2, 32*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2405
						this->t_blusa.setSrcrect({144, 205, 22, 31});
						this->t_blusa.setFormat({pos_desloc_x - 3*2, pos_desloc_y, 22*2, 31*2});

						this->t_blusa_b_d.setSrcrect({25, 167, 8, 14});
						this->t_blusa_b_d.setFormat({pos_desloc_x  + 3*2, pos_desloc_y + 7*2, 8*2, 14*2});

						this->t_blusa_b_e.setSrcrect({0, 0, 0, 0});
						this->t_blusa_b_e.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2029
						this->t_calca.setSrcrect({327, 183, 16, 19});
						this->t_calca.setFormat({pos_desloc_x, pos_desloc_y + 26*2, 16*2, 19*2});
						break;
				}
				switch (this->tenis) {
					case 1: //Tenis 7
						this->t_tenis.setSrcrect({25, 154, 19, 10});
						this->t_tenis.setFormat({pos_desloc_x + 2*2, pos_desloc_y + 44*2, 19*2, 10*2});
						break;
				}
			} else { // Homem
				switch (this->olhos) {
					case 1: // olhos 4
						this->t_olhos.setSrcrect({131, 0, 5, 4});
						this->t_olhos.setFormat({pos_desloc_x + 14*2, pos_desloc_y - 12*2, 5*2, 4*2});
						break;

					case 2: // olhos 8
						this->t_olhos.setSrcrect({258, 0, 5, 6});
						this->t_olhos.setFormat({pos_desloc_x + 14*2, pos_desloc_y - 13*2, 5*2, 6*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 30
						this->t_cabelo.setSrcrect({187, 67, 33, 34});
						this->t_cabelo.setFormat({pos_desloc_x - 6*2, pos_desloc_y - 33*2, 33*2, 34*2});
						break;

					case 2: // Cabelo 501
						this->t_cabelo.setSrcrect({80, 151, 34, 30});
						this->t_cabelo.setFormat({pos_desloc_x - 10*2, pos_desloc_y - 27*2, 34*2, 30*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2301
						this->t_blusa.setSrcrect({273, 205, 24, 32});
						this->t_blusa.setFormat({pos_desloc_x - 7*2, pos_desloc_y - 1*2, 24*2, 32*2});

						this->t_blusa_b_d.setSrcrect({196, 185, 8, 8});
						this->t_blusa_b_d.setFormat({pos_desloc_x + 3*2, pos_desloc_y + 7*2, 8*2, 8*2});

						this->t_blusa_b_e.setSrcrect({161, 185, 8, 9});
						this->t_blusa_b_e.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2037
						this->t_calca.setSrcrect({429, 183, 16, 21});
						this->t_calca.setFormat({pos_desloc_x, pos_desloc_y + 28*2, 16*2, 21*2});
				}
				switch (this->tenis) {
					case 1: //Tenis 3
						this->t_tenis.setSrcrect({133, 104, 19, 9});
						this->t_tenis.setFormat({pos_desloc_x + 2*2, pos_desloc_y + 44*2, 19*2, 9*2});
						break;
				}
			}
			break;
		case 5:
			this->t_corpo.setSrcrect({25+309, 0, 20, 53});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 20*2, 53*2});

			//this->t_braco_e.setSrcrect({26+309, 55, 5, 27});
			this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 3*2, 0, 0});

			this->t_braco_d.setSrcrect({31+309, 55, 9, 29});
			this->t_braco_d.setFormat({pos_desloc_x + 8*2, pos_desloc_y + 7*2, 9*2, 29*2});

			this->t_cabeca.setSrcrect({117+309, 28, 27, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 1*2, pos_desloc_y - 23*2, 27*2, 28*2});

			this->t_nariz_boca.setSrcrect({18, 10, 8, 11});
			this->t_nariz_boca.setFormat({pos_desloc_x - 3*2, pos_desloc_y - 11*2, 8*2, 11*2});

			if (this->sexo) { // É mulher
				switch (this->olhos) {
					case 1: // olhos 2
						this->t_olhos.setSrcrect({72, 0, 5, 6});
						this->t_olhos.setFormat({pos_desloc_x + 2*2, pos_desloc_y - 12*2, 5*2, 6*2});
						break;

					case 2: // olhos 6
						this->t_olhos.setSrcrect({196, 0, 5, 5});
						this->t_olhos.setFormat({pos_desloc_x + 2*2, pos_desloc_y - 12*2, 5*2, 5*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 6
						this->t_cabelo.setSrcrect({276, 104, 31, 30});
						this->t_cabelo.setFormat({pos_desloc_x - 3*2, pos_desloc_y - 25*2, 31*2, 30*2});
						break;

					case 2: // Cabelo 11
						this->t_cabelo.setSrcrect({33, 58, 34, 32});
						this->t_cabelo.setFormat({pos_desloc_x - 1*2, pos_desloc_y - 28*2, 34*2, 32*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2405
						this->t_blusa.setSrcrect({144, 205, 22, 31});
						this->t_blusa.setFormat({pos_desloc_x + 1*2, pos_desloc_y, 22*2, 31*2});

						this->t_blusa_b_d.setSrcrect({25, 167, 8, 14});
						this->t_blusa_b_d.setFormat({pos_desloc_x  + 9*2, pos_desloc_y + 7*2, 8*2, 14*2});

						this->t_blusa_b_e.setSrcrect({0, 0, 0, 0});
						this->t_blusa_b_e.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2029
						this->t_calca.setSrcrect({327, 183, 16, 19});
						this->t_calca.setFormat({pos_desloc_x + 4*2, pos_desloc_y + 26*2, 16*2, 19*2});
						break;
				}
				switch (this->tenis) {
					case 1: //Tenis 7
						this->t_tenis.setSrcrect({25, 154, 19, 10});
						this->t_tenis.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 44*2, 19*2, 10*2});
						break;
				}
			} else { // Homem
				switch (this->olhos) {
					case 1: // olhos 4
						this->t_olhos.setSrcrect({131, 0, 5, 4});
						this->t_olhos.setFormat({pos_desloc_x + 2*2, pos_desloc_y - 11*2, 5*2, 4*2});
						break;

					case 2: // olhos 8
						this->t_olhos.setSrcrect({258, 0, 5, 6});
						this->t_olhos.setFormat({pos_desloc_x + 2*2, pos_desloc_y - 12*2, 5*2, 6*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 30
						this->t_cabelo.setSrcrect({187, 67, 33, 34});
						this->t_cabelo.setFormat({pos_desloc_x - 6*2, pos_desloc_y - 32*2, 33*2, 34*2});
						break;

					case 2: // Cabelo 501
						this->t_cabelo.setSrcrect({80, 151, 34, 30});
						this->t_cabelo.setFormat({pos_desloc_x - 3*2, pos_desloc_y - 26*2, 34*2, 30*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2301
						this->t_blusa.setSrcrect({273, 205, 24, 32});
						this->t_blusa.setFormat({pos_desloc_x + 3*2, pos_desloc_y - 1*2, 24*2, 32*2});

						this->t_blusa_b_d.setSrcrect({196, 185, 8, 8});
						this->t_blusa_b_d.setFormat({pos_desloc_x + 9*2, pos_desloc_y + 7*2, 8*2, 8*2});

						this->t_blusa_b_e.setSrcrect({161, 185, 8, 9});
						this->t_blusa_b_e.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2037
						this->t_calca.setSrcrect({429, 183, 16, 21});
						this->t_calca.setFormat({pos_desloc_x + 4*2, pos_desloc_y + 28*2, 16*2, 21*2});
				}
				switch (this->tenis) {
					case 1: //Tenis 3
						this->t_tenis.setSrcrect({133, 104, 19, 9});
						this->t_tenis.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 44*2, 19*2, 9*2});
						break;
				}
			}
			break;

		case 2:
			this->t_corpo.setSrcrect({45+309, 0, 25, 56});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 25*2, 56*2});

			this->t_braco_e.setSrcrect({26+309, 55, 5, 27});
			this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 3*2, 5*2, 27*2});

			this->t_braco_d.setSrcrect({26+309, 150, 9, 33});
			this->t_braco_d.setFormat({pos_desloc_x - 4*2, pos_desloc_y + 6*2, 9*2, 33*2});

			this->t_cabeca.setSrcrect({0+309, 56, 26, 31});
			this->t_cabeca.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 24*2, 26*2, 31*2});

			this->t_nariz_boca.setSrcrect({26, 10, 6, 10});
			this->t_nariz_boca.setFormat({pos_desloc_x + 15*2, pos_desloc_y - 7*2, 6*2, 10*2});

			if (this->sexo) { // É mulher
				switch (this->olhos) {
					case 1: // olhos 2
						this->t_olhos.setSrcrect({77, 0, 10, 9});
						this->t_olhos.setFormat({pos_desloc_x + 11*2, pos_desloc_y - 12*2, 10*2, 9*2});
						break;

					case 2: // olhos 6
						this->t_olhos.setSrcrect({201, 0, 12, 8});
						this->t_olhos.setFormat({pos_desloc_x + 10*2, pos_desloc_y - 13*2, 12*2, 8*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 6
						this->t_cabelo.setSrcrect({0, 184, 48, 36});
						this->t_cabelo.setFormat({pos_desloc_x - 14*2, pos_desloc_y - 29*2, 48*2, 36*2});
						break;

					case 2: // Cabelo 11
						this->t_cabelo.setSrcrect({67, 58, 34, 34});
						this->t_cabelo.setFormat({pos_desloc_x - 8*2, pos_desloc_y - 30*2, 34*2, 34*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2405
						this->t_blusa.setSrcrect({166, 205, 26, 34});
						this->t_blusa.setFormat({pos_desloc_x - 2*2, pos_desloc_y, 26*2, 34*2});

						this->t_blusa_b_d.setSrcrect({144, 185, 9, 19});
						this->t_blusa_b_d.setFormat({pos_desloc_x - 4*2, pos_desloc_y + 4*2, 9*2, 19*2});

						this->t_blusa_b_e.setSrcrect({255, 10, 5, 13});
						this->t_blusa_b_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 5*2, 13*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2029
						this->t_calca.setSrcrect({343, 183, 21, 23});
						this->t_calca.setFormat({pos_desloc_x, pos_desloc_y + 25*2, 21*2, 23*2});
						break;
				}
				switch (this->tenis) {
					case 1: //Tenis 7
						this->t_tenis.setSrcrect({269, 154, 25, 11});
						this->t_tenis.setFormat({pos_desloc_x + 2*2, pos_desloc_y + 46*2, 25*2, 11*2});
						break;
				}
			} else { // Homem
				switch (this->olhos) {
					case 1: // olhos 4
						this->t_olhos.setSrcrect({136, 0, 11, 7});
						this->t_olhos.setFormat({pos_desloc_x + 11*2, pos_desloc_y - 11*2, 11*2, 7*2});
						break;

					case 2: // olhos 8
						this->t_olhos.setSrcrect({263, 0, 12, 11});
						this->t_olhos.setFormat({pos_desloc_x + 10*2, pos_desloc_y - 13*2, 12*2, 11*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 30
						this->t_cabelo.setSrcrect({220, 67, 31, 34});
						this->t_cabelo.setFormat({pos_desloc_x - 6*2, pos_desloc_y - 33*2, 31*2, 34*2});
						break;

					case 2: // Cabelo 501
						this->t_cabelo.setSrcrect({114, 151, 36, 31});
						this->t_cabelo.setFormat({pos_desloc_x - 11*2, pos_desloc_y - 28*2, 36*2, 31*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2301
						this->t_blusa.setSrcrect({0, 237, 29, 36});
						this->t_blusa.setFormat({pos_desloc_x - 6*2, pos_desloc_y - 3*2, 29*2, 36*2});

						this->t_blusa_b_d.setSrcrect({204, 185, 8, 12});
						this->t_blusa_b_d.setFormat({pos_desloc_x - 3*2, pos_desloc_y + 6*2, 8*2, 12*2});

						this->t_blusa_b_e.setSrcrect({0, 20, 5, 10});
						this->t_blusa_b_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 4*2, 5*2, 10*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2037
						this->t_calca.setSrcrect({445, 183, 23, 25});
						this->t_calca.setFormat({pos_desloc_x, pos_desloc_y + 26*2, 23*2, 25*2});
				}
				switch (this->tenis) {
					case 1: //Tenis 3
						this->t_tenis.setSrcrect({159, 134, 25, 14});
						this->t_tenis.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 43*2, 25*2, 14*2});
						break;
				}
			}
			break;
		case 4:
			this->t_corpo.setSrcrect({45+309, 0, 25, 56});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 25*2, 56*2});

			this->t_braco_e.setSrcrect({26+309, 55, 5, 27});
			this->t_braco_e.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 3*2, 5*2, 27*2});

			this->t_braco_d.setSrcrect({26+309, 150, 9, 33});
			this->t_braco_d.setFormat({pos_desloc_x + 20*2, pos_desloc_y + 6*2, 9*2, 33*2});

			this->t_cabeca.setSrcrect({0+309, 56, 26, 31});
			this->t_cabeca.setFormat({pos_desloc_x - 0*2, pos_desloc_y - 23*2, 26*2, 31*2});

			this->t_nariz_boca.setSrcrect({26, 10, 6, 10});
			this->t_nariz_boca.setFormat({pos_desloc_x + 3*2, pos_desloc_y - 6*2, 6*2, 10*2});

			if (this->sexo) { // É mulher
				switch (this->olhos) {
					case 1: // olhos 2
						this->t_olhos.setSrcrect({77, 0, 10, 9});
						this->t_olhos.setFormat({pos_desloc_x + 3*2, pos_desloc_y - 11*2, 10*2, 9*2});
						break;

					case 2: // olhos 6
						this->t_olhos.setSrcrect({201, 0, 12, 8});
						this->t_olhos.setFormat({pos_desloc_x + 2*2, pos_desloc_y - 12*2, 12*2, 8*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 6
						this->t_cabelo.setSrcrect({0, 184, 48, 36});
						this->t_cabelo.setFormat({pos_desloc_x - 10*2, pos_desloc_y - 27*2, 48*2, 36*2});
						break;

					case 2: // Cabelo 11
						this->t_cabelo.setSrcrect({67, 58, 34, 34});
						this->t_cabelo.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 29*2, 34*2, 34*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2405
						this->t_blusa.setSrcrect({166, 205, 26, 34});
						this->t_blusa.setFormat({pos_desloc_x, pos_desloc_y + 1*2, 26*2, 34*2});

						this->t_blusa_b_d.setSrcrect({144, 185, 9, 19});
						this->t_blusa_b_d.setFormat({pos_desloc_x + 19*2, pos_desloc_y + 5*2, 9*2, 19*2});

						this->t_blusa_b_e.setSrcrect({255, 10, 5, 13});
						this->t_blusa_b_e.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 3*2, 5*2, 13*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2029
						this->t_calca.setSrcrect({343, 183, 21, 23});
						this->t_calca.setFormat({pos_desloc_x + 4*2, pos_desloc_y + 25*2, 21*2, 23*2});
						break;
				}
				switch (this->tenis) {
					case 1: //Tenis 7
						this->t_tenis.setSrcrect({269, 154, 25, 11});
						this->t_tenis.setFormat({pos_desloc_x - 2*2, pos_desloc_y + 46*2, 25*2, 11*2});
						break;
				}
			} else { // Homem
				switch (this->olhos) {
					case 1: // olhos 4
						this->t_olhos.setSrcrect({136, 0, 11, 7});
						this->t_olhos.setFormat({pos_desloc_x + 2*2, pos_desloc_y - 10*2, 11*2, 7*2});
						break;

					case 2: // olhos 8
						this->t_olhos.setSrcrect({263, 0, 12, 11});
						this->t_olhos.setFormat({pos_desloc_x + 2*2, pos_desloc_y - 12*2, 12*2, 11*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 30
						this->t_cabelo.setSrcrect({220, 67, 31, 34});
						this->t_cabelo.setFormat({pos_desloc_x - 1*2, pos_desloc_y - 32*2, 31*2, 34*2});
						break;

					case 2: // Cabelo 501
						this->t_cabelo.setSrcrect({114, 151, 36, 31});
						this->t_cabelo.setFormat({pos_desloc_x - 1*2, pos_desloc_y - 27*2, 36*2, 31*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2301
						this->t_blusa.setSrcrect({0, 237, 29, 36});
						this->t_blusa.setFormat({pos_desloc_x + 1*2, pos_desloc_y - 2*2, 29*2, 36*2});

						this->t_blusa_b_d.setSrcrect({204, 185, 8, 12});
						this->t_blusa_b_d.setFormat({pos_desloc_x + 20*2, pos_desloc_y + 7*2, 8*2, 12*2});

						this->t_blusa_b_e.setSrcrect({0, 20, 5, 10});
						this->t_blusa_b_e.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 4*2, 5*2, 10*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2037
						this->t_calca.setSrcrect({445, 183, 23, 25});
						this->t_calca.setFormat({pos_desloc_x + 2*2, pos_desloc_y + 26*2, 23*2, 25*2});
				}
				switch (this->tenis) {
					case 1: //Tenis 3
						this->t_tenis.setSrcrect({159, 134, 25, 14});
						this->t_tenis.setFormat({pos_desloc_x - 1*2, pos_desloc_y + 43*2, 25*2, 14*2});
						break;
				}
			}
			break;

		case 3:
			this->t_corpo.setSrcrect({70+309, 0, 24, 54});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 24*2, 54*2});

			this->t_braco_e.setSrcrect({172+309, 84, 8, 33});
			this->t_braco_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 8*2, 33*2});

			this->t_braco_d.setSrcrect({35+309, 150, 8, 33});
			this->t_braco_d.setFormat({pos_desloc_x - 4*2, pos_desloc_y + 2*2, 8*2, 33*2});

			this->t_cabeca.setSrcrect({70+309, 56, 26, 31});
			this->t_cabeca.setFormat({pos_desloc_x - 1*2, pos_desloc_y - 24*2, 26*2, 31*2});

			this->t_nariz_boca.setSrcrect({32, 10, 6, 6});
			this->t_nariz_boca.setFormat({pos_desloc_x + 9*2, pos_desloc_y - 2*2, 6*2, 6*2});

			if (this->sexo) { // É mulher
				switch (this->olhos) {
					case 1: // olhos 2
						this->t_olhos.setSrcrect({87, 0, 14, 6});
						this->t_olhos.setFormat({pos_desloc_x + 5*2, pos_desloc_y - 9*2, 14*2, 6*2});
						break;

					case 2: // olhos 6
						this->t_olhos.setSrcrect({213, 0, 14, 5});
						this->t_olhos.setFormat({pos_desloc_x + 5*2, pos_desloc_y - 10*2, 14*2, 5*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 6
						this->t_cabelo.setSrcrect({48, 184, 48, 28});
						this->t_cabelo.setFormat({pos_desloc_x - 12*2, pos_desloc_y - 27*2, 48*2, 28*2});
						break;

					case 2: // Cabelo 11
						this->t_cabelo.setSrcrect({101, 67, 28, 33});
						this->t_cabelo.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 29*2, 28*2, 33*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2405
						this->t_blusa.setSrcrect({192, 205, 29, 33});
						this->t_blusa.setFormat({pos_desloc_x - 2*2, pos_desloc_y, 29*2, 33*2});

						this->t_blusa_b_d.setSrcrect({153, 185, 8, 17});
						this->t_blusa_b_d.setFormat({pos_desloc_x - 4*2, pos_desloc_y + 3*2, 8*2, 17*2});

						this->t_blusa_b_e.setSrcrect({297, 134, 8, 18});
						this->t_blusa_b_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 8*2, 18*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2029
						this->t_calca.setSrcrect({364, 183, 21, 19});
						this->t_calca.setFormat({pos_desloc_x + 2*2, pos_desloc_y + 28*2, 21*2, 19*2});
						break;
				}
				switch (this->tenis) {
					case 1: //Tenis 7
						this->t_tenis.setSrcrect({269, 165, 23, 7});
						this->t_tenis.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 49*2, 23*2, 7*2});
						break;
				}
			} else { // Homem
				switch (this->olhos) {
					case 1: // olhos 4
						this->t_olhos.setSrcrect({147, 0, 16, 3});
						this->t_olhos.setFormat({pos_desloc_x + 4*2, pos_desloc_y - 7*2, 16*2, 3*2});
						break;

					case 2: // olhos 8
						this->t_olhos.setSrcrect({275, 0, 16, 6});
						this->t_olhos.setFormat({pos_desloc_x + 4*2, pos_desloc_y - 9*2, 16*2, 6*2});
						break;
				}
				switch (this->cabelo) {
					case 1: // Cabelo 30
						this->t_cabelo.setSrcrect({251, 67, 28, 32});
						this->t_cabelo.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 34*2, 28*2, 32*2});
						break;

					case 2: // Cabelo 501
						this->t_cabelo.setSrcrect({150, 151, 39, 31});
						this->t_cabelo.setFormat({pos_desloc_x - 7*2, pos_desloc_y - 28*2, 39*2, 31*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2301
						this->t_blusa.setSrcrect({29, 237, 26, 31});
						this->t_blusa.setFormat({pos_desloc_x - 1*2, pos_desloc_y, 26*2, 31*2});

						this->t_blusa_b_d.setSrcrect({212, 185, 9, 13});
						this->t_blusa_b_d.setFormat({pos_desloc_x - 5*2, pos_desloc_y + 2*2, 9*2, 13*2});

						this->t_blusa_b_e.setSrcrect({169, 185, 9, 13});
						this->t_blusa_b_e.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 9*2, 13*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2037
						this->t_calca.setSrcrect({297, 208, 23, 21});
						this->t_calca.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 29*2, 23*2, 21*2});
				}
				switch (this->tenis) {
					case 1: //Tenis 3
						this->t_tenis.setSrcrect({276, 134, 21, 11});
						this->t_tenis.setFormat({pos_desloc_x + 2*2, pos_desloc_y + 45*2, 21*2, 11*2});
						break;
				}
			}
			break;

		case 7:
			this->t_corpo.setSrcrect({94+309, 0, 23, 51});
			this->t_corpo.setFormat({pos_desloc_x, pos_desloc_y, 23*2, 51*2});

			this->t_braco_e.setSrcrect({157+309, 117, 8, 31});
			this->t_braco_e.setFormat({pos_desloc_x - 5*2, pos_desloc_y + 3*2, 8*2, 31*2});

			this->t_braco_d.setSrcrect({43+309, 150, 8, 32});
			this->t_braco_d.setFormat({pos_desloc_x + 20*2, pos_desloc_y + 2*2, 8*2, 32*2});

			this->t_cabeca.setSrcrect({96+309, 56, 26, 28});
			this->t_cabeca.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 25*2, 26*2, 28*2});

			//this->t_nariz_boca.setSrcrect({0, 0, 0, 0});
			this->t_nariz_boca.setFormat({pos_desloc_x, pos_desloc_y, 0, 0});

			//this->t_olhos.setSrcrect({, });
			this->t_olhos.setFormat({0, 0, 0, 0});

			if (this->sexo) { // É mulher
				switch (this->cabelo) {
					case 1: // Cabelo 6
						this->t_cabelo.setSrcrect({96, 184, 48, 31});
						this->t_cabelo.setFormat({pos_desloc_x - 13*2, pos_desloc_y - 29*2, 48*2, 31*2});
						break;

					case 2: // Cabelo 11
						this->t_cabelo.setSrcrect({129, 67, 26, 31});
						this->t_cabelo.setFormat({pos_desloc_x - 2*2, pos_desloc_y - 29*2, 26*2, 31*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2405
						this->t_blusa.setSrcrect({221, 205, 26, 30});
						this->t_blusa.setFormat({pos_desloc_x - 2*2, pos_desloc_y, 26*2, 30*2});

						this->t_blusa_b_d.setSrcrect({33, 167, 8, 15});
						this->t_blusa_b_d.setFormat({pos_desloc_x  + 20*2, pos_desloc_y + 2*2, 8*2, 15*2});

						this->t_blusa_b_e.setSrcrect({297, 152, 8, 15});
						this->t_blusa_b_e.setFormat({pos_desloc_x - 5*2, pos_desloc_y + 2*2, 8*2, 15*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2029
						this->t_calca.setSrcrect({385, 183, 21, 19});
						this->t_calca.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 25*2, 21*2, 19*2});
						break;
				}
				switch (this->tenis) {
					case 1: //Tenis 7
						this->t_tenis.setSrcrect({0, 172, 21, 8});
						this->t_tenis.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 47*2, 21*2, 8*2});
						break;
				}
			} else { // Homem
				switch (this->cabelo) {
					case 1: // Cabelo 30
						this->t_cabelo.setSrcrect({279, 67, 28, 37});
						this->t_cabelo.setFormat({pos_desloc_x - 3*2, pos_desloc_y - 35*2, 28*2, 37*2});
						break;

					case 2: // Cabelo 501
						this->t_cabelo.setSrcrect({189, 151, 37, 31});
						this->t_cabelo.setFormat({pos_desloc_x - 8*2, pos_desloc_y - 29*2, 37*2, 31*2});
						break;
				}
				switch (this->blusa) {
					case 1: // Blusa 2301
						this->t_blusa.setSrcrect({55, 237, 23, 29});
						this->t_blusa.setFormat({pos_desloc_x, pos_desloc_y, 23*2, 29*2});

						this->t_blusa_b_d.setSrcrect({221, 185, 8, 11});
						this->t_blusa_b_d.setFormat({pos_desloc_x + 21*2, pos_desloc_y + 2*2, 8*2, 11*2});

						this->t_blusa_b_e.setSrcrect({178, 185, 8, 11});
						this->t_blusa_b_e.setFormat({pos_desloc_x - 6*2, pos_desloc_y + 2*2, 8*2, 11*2});
						break;
				}
				switch (this->calca) {
					case 1: // Calça 2037
						this->t_calca.setSrcrect({320, 208, 23, 21});
						this->t_calca.setFormat({pos_desloc_x, pos_desloc_y + 26*2, 23*2, 21*2});
				}
				switch (this->tenis) {
					case 1: //Tenis 3
						this->t_tenis.setSrcrect({276, 145, 21, 9});
						this->t_tenis.setFormat({pos_desloc_x + 1*2, pos_desloc_y + 43*2, 21*2, 9*2});
						break;
				}
			}
			break;
	}

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
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	switch (this->direcao) {
		case 4:
		case 5:
		case 6:
			flip = SDL_FLIP_HORIZONTAL;
	}

	SDL_Color cor_pele = {255, 255, 255, 255};
	switch (this->cor_do_rosto) {
		case 1:
			cor_pele = {252, 200, 151, 255};
			break;
		case 2:
			cor_pele = {199, 144, 99, 255};
			break;
		case 3:
			cor_pele = {145, 91, 47, 255};
			break;
	}

	SDL_Color cor_cabelo = {255, 255, 255, 255};
	switch (this->cor_do_cabelo) {
		case 1:
			cor_cabelo = {76, 29, 111, 255};
			break;
		case 2:
			cor_cabelo = {51, 51, 51, 255};
			break;
		case 3:
			cor_cabelo = {112, 193, 0, 255};
			break;
		case 4:
			cor_cabelo = {0, 183, 255, 255};
			break;
		case 5:
			cor_cabelo = {246, 255, 0, 255};
			break;
		case 6:
			cor_cabelo = {255, 0, 136, 255};
			break;
	}

	SDL_Color cor_blusa = {255, 255, 255, 255};
	switch (this->cor_da_blusa) {
		case 1:
			cor_blusa = {149, 255, 0, 255};
			break;
		case 2:
			cor_blusa = {59, 255, 0, 255};
			break;
		case 3:
			cor_blusa = {0, 85, 255, 255};
			break;
		case 4:
			cor_blusa = {225, 0, 255, 255};
			break;
		case 5:
			cor_blusa = {255, 0, 85, 255};
			break;
		case 6:
			cor_blusa = {255, 4, 0, 255};
			break;
	}

	SDL_Color cor_calca = {255, 255, 255, 255};
	switch (this->cor_da_calca) {
		case 1:
			cor_calca = {143, 173, 255, 255};
			break;
		case 2:
			cor_calca = {255, 221, 128, 255};
			break;
		case 3:
			cor_calca = {255, 152, 143, 255};
			break;
		case 4:
			cor_calca = {112, 255, 224, 255};
			break;
		case 5:
			cor_calca = {208, 143, 255, 255};
			break;
		case 6:
			cor_calca = {255, 128, 189, 255};
			break;
	}

	SDL_Color cor_tenis = {255, 255, 255, 255};
	switch (this->cor_do_tenis) {
		case 1:
			cor_tenis = {7, 71, 0, 255};
			break;
		case 2:
			cor_tenis = {50, 0, 56, 255};
			break;
		case 3:
			cor_tenis = {65, 66, 0, 255};
			break;
		case 4:
			cor_tenis = {0, 4, 51, 255};
			break;
		case 5:
			cor_tenis = {41, 0, 30, 255};
			break;
		case 6:
			cor_tenis = {87, 0, 22, 255};
			break;
	}

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_pele.r, cor_pele.g, cor_pele.b);

	this->t_braco_e.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_blusa.r, cor_blusa.g, cor_blusa.b);

	this->t_blusa_b_e.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_pele.r, cor_pele.g, cor_pele.b);

	this->t_corpo.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_tenis.r, cor_tenis.g, cor_tenis.b);

	this->t_tenis.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_calca.r, cor_calca.g, cor_calca.b);

	this->t_calca.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_blusa.r, cor_blusa.g, cor_blusa.b);

	this->t_blusa.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_pele.r, cor_pele.g, cor_pele.b);

	this->t_braco_d.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_blusa.r, cor_blusa.g, cor_blusa.b);

	this->t_blusa_b_d.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_pele.r, cor_pele.g, cor_pele.b);

	this->t_cabeca.render(flip);
	this->t_nariz_boca.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), 255, 255, 255);

	this->t_olhos.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), cor_cabelo.r, cor_cabelo.g, cor_cabelo.b);

	this->t_cabelo.render(flip);

	SDL_SetTextureColorMod(this->tex.getTexture(), 255, 255, 255);


	return this;
}