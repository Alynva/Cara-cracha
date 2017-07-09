#include "../include/Textura.h"

Textura::Textura(std::string path, SDL_Renderer* renderer, SDL_Rect format, SDL_Rect *srcrect):
	pPath(path),
	pRenderer(renderer),
	pTexture(this->loadTexture()),
	recFormat(format) {
	if (srcrect)
		this->recSrcrect = *srcrect;
	else
		this->recSrcrect = {0, 0, -1, -1};

}
Textura::~Textura() {
	this->pRenderer = nullptr;
	this->pTexture = nullptr;
}


void Textura::setPath(std::string path) {
	this->pPath = path;
}
std::string Textura::getPath() const {
	return this->pPath;
}
void Textura::setRenderer(SDL_Renderer* renderer) {
	this->pRenderer = renderer;
}
SDL_Renderer* Textura::getRenderer() const {
	return this->pRenderer;
}
void Textura::setTexture(SDL_Texture* texture) {
	this->pTexture = texture;
}
SDL_Texture* Textura::getTexture() const {
	return this->pTexture;
}
void Textura::setSrcrect(SDL_Rect srcrect) {
	this->recSrcrect = srcrect;
}
SDL_Rect Textura::getSrcrect() const {
	return this->recSrcrect;
}
void Textura::setFormat(SDL_Rect format) {
	this->recFormat = format;
}
SDL_Rect Textura::getFormat() const {
	return this->recFormat;
}


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


bool Textura::render(SDL_RendererFlip flip) {
	SDL_Point center = {this->recFormat.x + (this->recFormat.w / 2), this->recFormat.w + (this->recFormat.h / 2)};
	return SDL_RenderCopyEx(this->pRenderer, this->pTexture, (this->recSrcrect.w < 0 || this->recSrcrect.h < 0) ? NULL : &this->recSrcrect, &this->recFormat, 0, &center, flip) == 0;
}