#ifndef KEYPOLL_H
#define KEYPOLL_H

#include <string>
#include <vector>
#include <map> // FIXME: I should feel very bad for using C++ -flibit

#include "SDL.h"

#define KEYBOARD_UP SDLK_UP
#define KEYBOARD_DOWN SDLK_DOWN
#define KEYBOARD_LEFT SDLK_LEFT
#define KEYBOARD_RIGHT SDLK_RIGHT
#define KEYBOARD_ENTER SDLK_RETURN
#define KEYBOARD_SPACE SDLK_SPACE

#define KEYBOARD_w SDLK_w
#define KEYBOARD_s SDLK_s
#define KEYBOARD_a SDLK_a
#define KEYBOARD_d SDLK_d
#define KEYBOARD_m SDLK_m

#define KEYBOARD_v SDLK_v
#define KEYBOARD_z SDLK_z

#define KEYBOARD_BACKSPACE = SDLK_BACKSPACE

class KeyPoll
{
public:
	std::map<SDLKey, bool> keymap;

	bool isActive;

	bool resetWindow;

	bool escapeWasPressedPreviously;
	bool quitProgram;
	bool toggleFullscreen;

	int sensitivity;

	void setSensitivity(int _value);

	KeyPoll();

	void enabletextentry();

	void disabletextentry();

	void Poll();

	bool isDown(SDLKey key);

	bool isUp(SDLKey key);

/*
	bool isDown(std::vector<SDL_GameControllerButton> buttons);
	bool isDown(SDL_GameControllerButton button);
	bool controllerButtonDown();
*/
	bool controllerWantsLeft(bool includeVert);
	bool controllerWantsRight(bool includeVert);

	int leftbutton, rightbutton, middlebutton;
	int mx, my;

	bool textentrymode;
	int keyentered, keybufferlen;
	bool pressedbackspace;
	std::string keybuffer;

	bool linealreadyemptykludge;

private:
/*
	std::map<SDL_JoystickID, SDL_GameController*> controllers;
	std::map<SDL_GameControllerButton, bool> buttonmap;
*/
	int xVel, yVel;
	bool useFullscreenSpaces;
	Uint32 wasFullscreen;
};

extern KeyPoll key;

#endif /* KEYPOLL_H */
