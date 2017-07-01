/*
# adicionar ao Textura.h:

 includes:

		#include "data_structures.h"

  atributos:

		Queue<SDL_Texture*> pTexture;;

  metodos:

		void render();
		void add(SDL_Texture*);
		void clear();
	

# adicionar ao Textura.cpp:

void Textura::render() {
	for (int i = 0, i < this->queue.getSize() -1, i++){
		SDL_RenderCopy(this->pRenderer[i], this->pTexture[i], NULL, &this->recFormat[i]);
	}
}

void Textura::add(SDL_Texture* pTexture) {
	this->queue.enqueue(pTexture);	
}

void Textura::clear() {
	this->queue.clear();
}

*/
	
