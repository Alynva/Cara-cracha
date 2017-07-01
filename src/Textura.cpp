#include "../include/Textura.h"

SDL_Texture* Textura::loadTexture(std::string path) {
	// Textura final
	SDL_Texture* newTexture = NULL;

	// Carrega imagem a partir de um caminho
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		SDL_Log("Unable to load image %s. SDL_Image Error: %s", path.c_str(), IMG_GetError());
	} else {
		// Cria textura dos pixels da superficie
		newTexture = SDL_CreateTextureFromSurface(this->pRenderer, loadedSurface);
		if ( newTexture == NULL) {
			SDL_Log("Unable to create texture from %s. SDL Error: %s", path.c_str(), SDL_GetError());
		}

		// Deleta a superficie
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

Textura::Textura(std::string path, SDL_Renderer* renderer, int x, int y, int w, int h):pPath(path) {
	this->pRenderer = renderer;
	this->pTextures.enqueue(this->loadTexture(path));
	this->recFormat.x = x;
	this->recFormat.y = y;
	this->recFormat.w = w;
	this->recFormat.h = h;
}

SDL_Point Textura::getSize() const {
	return {this->recFormat.w, this->recFormat.h};
}
void Textura::setSize(int w, int h) {
	this->recFormat.h = h;
	this->recFormat.w = w;
}

SDL_Point Textura::getPosition() const {
	return {this->recFormat.x, this->recFormat.y};
}
void Textura::setPosition(SDL_Point coord) {
	this->recFormat.x = coord.x;
	this->recFormat.y = coord.y;
}
void Textura::setRenderer(SDL_Renderer* renderer) {
	this->pRenderer = renderer;
}
SDL_Renderer* Textura::getRenderer() const {
	return this->pRenderer;
}
SDL_Texture* Textura::getTexture() const {
	return this->pTextures[0];
}
Textura* Textura::render(int index) {
	SDL_Log("front null? %c", this->pTextures.getFront()->value == NULL ? 's' : 'n');
	Queue<SDL_Texture*> temp;
	temp.enqueue(this->loadTexture(this->pPath));
	this->pTextures = temp;
	
	if (index < 0)
		for (int i = 0; i < this->pTextures.getSize(); i++)
			SDL_RenderCopy(this->pRenderer, this->pTextures[i], NULL, &this->recFormat);
	else
		SDL_RenderCopy(this->pRenderer, this->pTextures[index], NULL, &this->recFormat);
	
	return this;
}