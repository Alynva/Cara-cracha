#ifndef Cara_cracha
#define Cara_cracha

#include "data_structures.h"
#include "Pessoa.h"

class Cara_cracha {
	public:
		int tela;
		Queue fila<Pessoa*>;

		Cara_cracha();

		Cara_cracha* init() {

			for (int i = 0; i < 10; i++)
				this->fila.enqueue(new Pessoa());

			return &this;

		};

		Cara_cracha* play() {


			return &this;

		}
}

#endif