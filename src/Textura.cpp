#include "../include/Textura.h"

SDL_Texture* Textura::loadTexture() {
	// Textura final
	SDL_Texture* newTexture = NULL;

	// Carrega imagem a partir de um caminho
	SDL_Surface* loadedSurface = IMG_Load(this->pPath.c_str());
	if (loadedSurface == NULL) {
		SDL_Log("Unable to load image %s. SDL_Image Error: %s", this->pPath.c_str(), IMG_GetError());
	} else {
		// Cria textura dos pixels da superficie
		newTexture = SDL_CreateTextureFromSurface(this->pRenderer, loadedSurface);
		if ( newTexture == NULL) {
			SDL_Log("Unable to create texture from %s. SDL Error: %s", this->pPath.c_str(), SDL_GetError());
		}

		// Deleta a superficie
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}

Textura::Textura(std::string path, SDL_Renderer* renderer, int x, int y, int w, int h):pPath(path) {
	this->pRenderer = renderer;
	this->pTexture = this->loadTexture();
	this->recFormat.x = x;
	this->recFormat.y = y;
	this->recFormat.w = w;
	this->recFormat.h = h;
}

SDL_Point Textura::getSize() const {
	return {this->recFormat.w, this->recFormat.h};
}
void Textura::setSize(int w, int h) {
	this->recFormat.w = w;
	this->recFormat.h = h;
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
	return this->pTexture;
}
bool Textura::render() {
	return SDL_RenderCopy(this->pRenderer, this->pTexture, NULL, &this->recFormat) == 0;
}