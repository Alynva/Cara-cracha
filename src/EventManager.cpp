#include "../include/eventmanager.h"
#include <iostream>

using namespace std;

bool abc;
EventManager::EventManager(bool* tFullScreen, bool* mQuit, bool* gPlay, SDL_Point* mWinSize):t_fullscreen(tFullScreen), quit(mQuit), play(gPlay), window_size(mWinSize), mouse_pressed(false) {

}

void EventManager::update() {
	while (SDL_PollEvent(&this->handler)) {
		switch (this->handler.type) {
			case SDL_QUIT:
				*this->quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (handler.button.button == SDL_BUTTON_LEFT)
					this->mouseLeftDown();
				break;
			case SDL_MOUSEBUTTONUP:
				if (handler.button.button == SDL_BUTTON_LEFT)
					this->mouseLeftUp();
				break;
			case SDL_MOUSEMOTION:
				this->mouseMove();
				break;
			case SDL_KEYDOWN:
				if (this->handler.key.keysym.scancode == SDL_SCANCODE_F11)
					*this->t_fullscreen = true;
				break;
			case SDL_WINDOWEVENT:
		        switch (this->handler.window.event) {
			        case SDL_WINDOWEVENT_SHOWN:
//			            SDL_Log("Window %d shown", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_HIDDEN:
//			            SDL_Log("Window %d hidden", this->handler.window.windowID);
			            break;
			        case SDL_WINDOWEVENT_EXPOSED:
//			            SDL_Log("Window %d exposed", this->handler.window.windowID);
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
//			            SDL_Log("Mouse entered window %d",
//			                    this->handler.window.windowID);
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
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

}

void EventManager::mouseLeftDown() {
	this->mouse_pressed = true;

}

void EventManager::mouseLeftUp() {
	this->mouse_pressed = false;

	
}


void EventManager::windowResized(int w, int h) {
	*this->window_size = {w, h};

	if (this->logo) {
		this->logo->setPosition({this->window_size->x / 2 - 204, this->window_size->y / 4 - 79});
	}

	if (this->stacks.getSize()) {
		Node<PilhaInteligente*>* node_stack = this->stacks.peek()->next;
		for (int i = 1; i < this->stacks.getSize(); i++) { // Inicia em 1 pois o primeiro � a pilha que persegue o mouse
			if (i >= 1 && i <= 4)
				node_stack->value->setPosition({w/2 - 385 + 90 * (i-1), 50});
			if (i >= 5 && i <= 8)
				node_stack->value->setPosition({w/2 + 45 + 90 * (i-5), 50});
			if (i >= 9 && i <= 16)
				node_stack->value->setPosition({w/2 - 385 + 100 * (i-9), 200});
			node_stack = node_stack->next;
		}
	}

	if (this->buttons.getSize()) {
		Node<Button*>* node_button = this->buttons.peek();
		for (int i = 0; i < this->buttons.getSize(); i++) {
			string type = node_button->value->getType();
			if (type == "play")
				node_button->value->setPosition({this->window_size->x / 2 - 125, this->window_size->y / 2 - 25});
			else if (type == "project")
				node_button->value->setPosition({this->window_size->x / 2 - 125, this->window_size->y / 2 + 50});
			else if (type == "quit")
				node_button->value->setPosition({this->window_size->x / 2 - 125, this->window_size->y / 2 + 125});

			node_button = node_button->next;
		}
	}
}
