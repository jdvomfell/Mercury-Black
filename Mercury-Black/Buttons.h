#ifndef BUTTONS_H
#define BUTTONS_H

#include "OptionsMenu.h"
#include "GUI.h"
#include "Buttons.h"
#include "Editor.h"
#include "Game.h"
#include "HitboxEditor.h"
#include "Fade.h"


class Button : public GUI {

public:
    typedef void(*eventFunction)(GameEngine *);

    Button() {}
    Button(std::string name, float x, float y, sf::Color color, int size, sf::Font * font, eventFunction funcPtr);
	// A destructor
    ~Button(){ m_funcPtr = NULL; }        

    // Invokes the registered function
    void interact(GameEngine *);

    private:
        eventFunction m_funcPtr;
};

void changeToGame(GameEngine * engine);
void popState(GameEngine * engine);
void changeToEditor(GameEngine * engine);
void changeToHitboxEditor(GameEngine * engine);
void changeToMainMenu(GameEngine * engine);
//void changeToOptionsMenu(GameEngine * engine);
void quitGame(GameEngine * engine);
void doNothing(GameEngine * engine);
#endif