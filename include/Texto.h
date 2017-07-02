#ifndef TEXTO
#define TEXTO

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class Texto {

	std::string ttf_path;
	TTF_Font* t_font;
	SDL_Texture* t_texture;
	SDL_Renderer* t_renderer;
	int t_size;
	SDL_Rect rec_format;
	SDL_Rect rec_srcrect;
	SDL_Color t_color;
	
	Texto* loadFont();
	Texto* updateFont();

	public:
		std::string t_text;

		Texto();
		Texto(std::string, SDL_Renderer*, int, SDL_Rect, SDL_Color, std::string, SDL_Rect = {0, 0, 0, 0});
	
		Texto* setPath(std::string);
		//SDL_Renderer* getRenderer() const;
		Texto* setRenderer(SDL_Renderer*);
		//SDL_Texture* getTexture() const;
		//SDL_Point getSize() const;
		Texto* setSize(SDL_Point);
		//SDL_Point getPosition() const;
		Texto* setPosition(SDL_Point);
		Texto* setFormat(SDL_Rect);
		Texto* setSrcrect(SDL_Rect);
		Texto* setColor(SDL_Color);
		Texto* setText(std::string);
		bool render();
};

inline Texto* Texto::loadFont() {
	// Carrega fonte a partir do caminho e tamanho
	this->t_font = TTF_OpenFont(this->ttf_path.c_str(), this->t_size);
	if (this->t_font == NULL) {
		SDL_Log("Unable to load font %s. TTF_OpenFont Error: %s", this->ttf_path.c_str(), TTF_GetError());
	} else {
		this->updateFont();
	}

	return this;
}
inline Texto* Texto::updateFont() {
	// Obtém a largura e altura ocupada pelo texto
	if (TTF_SizeUTF8(this->t_font, this->t_text.c_str(), &this->rec_format.w, &this->rec_format.h))
		SDL_Log("Unable to load get size of %s. TTF_SizeUTF8 Error: %s", this->ttf_path.c_str(), TTF_GetError());

	// Carrega fonte a partir do texto
	SDL_Surface* loadedSurface = TTF_RenderUTF8_Solid(this->t_font, this->t_text.c_str(), this->t_color);
	if (loadedSurface == NULL) {
		SDL_Log("Unable to load surface from %s. TTF_RenderUTF8_Solid Error: %s", this->ttf_path.c_str(), TTF_GetError());
	} else {
		// Cria textura dos pixels da superficie
		this->t_texture = SDL_CreateTextureFromSurface(this->t_renderer, loadedSurface);
		if (this->t_texture == NULL) {
			SDL_Log("Unable to create texture from %s. SDL Error: %s", this->ttf_path.c_str(), SDL_GetError());
		}

		// Deleta a superficie
		SDL_FreeSurface(loadedSurface);
	}

	return this;
}

inline Texto::Texto():
	ttf_path(""),
	t_font(nullptr),
	t_texture(nullptr),
	t_renderer(nullptr),
	t_size(0),
	rec_format({0, 0, 0, 0}),
	rec_srcrect({0, 0, 0, 0}),
	t_color({0, 0, 0}),
	t_text("") {
}
inline Texto::Texto(std::string pp, SDL_Renderer* pr, int ps, SDL_Rect pf, SDL_Color pc, std::string pt, SDL_Rect psr):
	ttf_path(pp),
	t_font(nullptr),
	t_texture(nullptr),
	t_renderer(pr),
	t_size(ps),
	rec_format(pf),
	rec_srcrect(psr),
	t_color(pc),
	t_text(pt) {
	this->loadFont();
}

inline Texto* Texto::setPath(std::string pp) {
	this->ttf_path = pp;
	return this->loadFont();
}

inline Texto* Texto::setRenderer(SDL_Renderer* pr) {
	this->t_renderer = pr;
	return this;
}
inline Texto* Texto::setSize(SDL_Point s) {
	this->rec_format.w = s.x;
	this->rec_format.h = s.y;
	return this->loadFont();
}
inline Texto* Texto::setPosition(SDL_Point p) {
	this->rec_format.x = p.x;
	this->rec_format.y = p.y;
	return this->updateFont();
}
inline Texto* Texto::setFormat(SDL_Rect pf) {
	this->rec_format = pf;
	return this->updateFont();
}
inline Texto* Texto::setSrcrect(SDL_Rect psr) {
	this->rec_srcrect = psr;
	return this->updateFont();
}
inline Texto* Texto::setColor(SDL_Color pc) {
	this->t_color = pc;
	return this->updateFont();
}
inline Texto* Texto::setText(std::string pt) {
	this->t_text = pt;
	return this->updateFont();
}
inline bool Texto::render() {
	return SDL_RenderCopy(this->t_renderer, this->t_texture, NULL, &this->rec_format) == 0;
}

#endif