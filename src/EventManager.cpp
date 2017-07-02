#include "../include/EventManager.h"

EventManager::EventManager(bool* pgq, bool* pgp, bool* pmp, SDL_Point* pws, int* pti, Queue<Pessoa*>* pf, double* pce):
	quit(pgq),
	play(pgp),
	mouse_pressed(pmp),
	window_size(pws),
	tela_id(pti),
	fila(pf),
	catraca_estado(pce) {
}

void EventManager::update() {
	while (SDL_PollEvent(&this->handler)) {
		switch (this->handler.type) {
			case SDL_QUIT:
				*this->quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				this->mouseDown(this->handler.button);
				break;
			case SDL_MOUSEBUTTONUP:
				this->mouseUp();
				break;
			case SDL_MOUSEMOTION:
				this->mouseMove();
				break;
			case SDL_KEYDOWN:
				break;
			case SDL_WINDOWEVENT:
		        switch (this->handler.window.event) {
			        case SDL_WINDOWEVENT_SHOWN:
//			            SDL_Log("Window %d shown", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_EXPOSED:
//			            SDL_Log("Window %d exposed", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_HIDDEN:
//			            SDL_Log("Window %d hidden", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_MOVED:
//			            SDL_Log("Window %d moved to %d,%d",
//			                    this->handler.window.windowID, this->handler.window.data1,
//			                    this->handler.window.data2);
			            break;
			        case SDL_WINDOWEVENT_RESIZED:
//			            SDL_Log("Window %d resized to %dx%d",
//			                    this->handler.window.windowID, this->handler.window.data1,
//			                    this->handler.window.data2);
			        	this->windowResized(this->handler.window.data1, this->handler.window.data2);
			            break;
			        case SDL_WINDOWEVENT_SIZE_CHANGED:
//			            SDL_Log("Window %d size changed to %dx%d",
//			                    this->handler.window.windowID, this->handler.window.data1,
//			                    this->handler.window.data2);
			            break;
			        case SDL_WINDOWEVENT_MINIMIZED:
//			            SDL_Log("Window %d minimized", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_MAXIMIZED:
//			            SDL_Log("Window %d maximized", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_RESTORED:
//			            SDL_Log("Window %d restored", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_ENTER:
//			            SDL_Log("Mouse entered window %d", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_LEAVE:
//			            SDL_Log("Mouse left window %d", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_FOCUS_GAINED:
//			            SDL_Log("Window %d gained keyboard focus",
//			                    this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_FOCUS_LOST:
//			            SDL_Log("Window %d lost keyboard focus",
//			                    this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_CLOSE:
//			            SDL_Log("Window %d closed", this->handler.window.windowID);
			            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
			        case SDL_WINDOWEVENT_TAKE_FOCUS:
//			            SDL_Log("Window %d is offered a focus", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_HIT_TEST:
//			            SDL_Log("Window %d has a special hit test", this->handler.window.windowID);
			            break;
#endif
			        default:
			            SDL_Log("Window %d got unknown event %d",
			                    this->handler.window.windowID, this->handler.window.event);
			            break;
		        }
		        break;
		}
	}
}

void EventManager::mouseMove() {
	
}

void EventManager::mouseDown(SDL_MouseButtonEvent& button) {
	*this->mouse_pressed = true;

	switch (button.button) {
		case SDL_BUTTON_LEFT: // Deixa entrar
			switch (*this->tela_id) {
				case 1:
					*this->tela_id = 2;
					break;
				case 2:
					*this->tela_id = 1;
					Pessoa *t1, *t2;
					fila->dequeue(t1);
					*catraca_estado = 1;
					t2 = new Pessoa();
					t2->pos = GeoA::Vetor(this->window_size->x*0.5 - 139, this->window_size->y*0.5 - 32, 0);
					t2->initTextures(t1->t_corpo.getRenderer());
					fila->enqueue(t2);
					t1 = t2 = nullptr;
					break;
			} 
			break;
		case SDL_BUTTON_RIGHT: // Não deixa entrar
			switch (*this->tela_id) {
				case 1:
					*this->tela_id = 2;
					break;
				case 2:
					*this->tela_id = 1;
					Pessoa* temp;
					fila->dequeue(temp);
					fila->enqueue(temp);
					temp = nullptr;
					break;
			} 
			break;
		case SDL_BUTTON_MIDDLE:
			break;
	}
}

void EventManager::mouseUp() {
	*this->mouse_pressed = false;
}

void EventManager::windowResized(int data1, int data2) {
	*this->window_size = {data1, data2};
}