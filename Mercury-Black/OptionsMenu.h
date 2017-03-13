#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "GameState.h"
#include "Buttons.h"

#define OPTION_FONT_SIZE 70
#define OPTION_TITLE_SIZE 200

#define MUSIC_T 1
#define SFX_T 2
#define KEYS_T 3

#define P_LEFT 0
#define P_RIGHT 1
#define P_JUMP 2
#define P_CROUCH 3
#define P_ATTACK 4
#define P_SPECIAL 5 
#define P_BLOCK 6

#define E_SELECT 7
#define E_DESELECT 8
#define E_ZOOM 9 
#define E_QUICKPAN 10
#define E_PANR 11
#define E_PANL 12
#define E_PANU 13
#define E_PAND 14 
#define E_LAYERU 15
#define E_LAYERD 16
#define E_SHOWLINE 17
#define E_SAVE 18
#define E_LOAD 19
#define E_INSERT 20
#define E_DELETE 21
#define E_ENTITYTYPE 22
#define E_ENTITYACTION 23

#define O_XFLIP 24
#define O_YFLIP 25
#define O_ROTATEC 26
#define O_ROTATECC 27
#define O_SCALEU 28
#define O_SCALED 29

#define A_BMENU 30
#define A_FMENU 31


class Options {

public:

	//Bindings are defined in OptionsMenu.cpp
	
	bool musicToggle = 1;
	bool sfxToggle = 1;
	std::vector<sf::Keyboard> binding[32];
};

class OptionsMenu : public GameState {

public:
	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	Options * options;

	static OptionsMenu * instance(GameEngine * engine) { optionsMenu.engine = engine; return &optionsMenu;}

protected:
	
	OptionsMenu() {}

private:
	
	sf::Color hText;
	sf::Color uText;

	static OptionsMenu optionsMenu;

	std::vector <GUI *> buttons;

	Button musicToggle;
	Button sfxToggle;
	Button changeBinding;
	std::vector<Button> KeyBind;
	
	sf::Text title;
	
	sf::View view;
};

class KeyBind : public GameState {

public:
	void init();
	void clean();

	void handleEvent();
	void update(const float dt);
	void render(const float dt);

	void bindingCheck(int keyBinding, int setKey);
	Options * options;

	static KeyBind * instance(GameEngine * engine) { keyBind.engine = engine; return &keyBind; }

protected:

	KeyBind() {}

private:

	sf::Color hText;
	sf::Color uText;

	static KeyBind keyBind;

	//std::vector <GUI *> buttons;

	Button changeBinding;
	std::vector<Button> KeyBindings;

	sf::Text title;
/*
	Button p_left;
	Button p_right;
	Button p_jump;
	Button p_crouch;
	Button p_attack;
	Button p_special;
	Button p_block;

	Button e_select;
	Button e_deselect;
	Button e_zoom;
	Button e_quickpan;
	Button e_panr;
	Button e_panl;
	Button e_panu;
	Button e_pand;
	Button e_layeru;
	Button e_layerd;
	Button e_showline;
	Button e_save;
	Button e_load;
	Button e_insert;
	Button e_delete;
	Button e_entitytype;
	Button e_entityaction;

	Button o_xflip;
	Button o_yflip;
	Button o_rotatec;
	Button o_rotatecc;
	Button o_scaleu;
	Button o_scaled;

	Button a_bmenu;
	Button a_fmenu;
	*/

	sf::View view;
};

#endif