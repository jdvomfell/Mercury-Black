#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "GameState.h"
#include "Buttons.h"

#define KEYBIND_FONT_SIZE 15
#define OPTION_FONT_SIZE 70
#define KEYBIND_TITLE_SIZE 60
#define	OPTION_TITLE_SIZE 200

enum Key {
	P_LEFT = 0,
	P_RIGHT,
	P_JUMP,
	P_CROUCH,
	P_ATTACK,
	P_SPECIAL,
	P_BLOCK,
	E_SELECT,
	E_QUICKPAN,
	E_PANL,
	E_PANR,
	E_PANU,
	E_PAND,
	E_LAYERU,
	E_LAYERD,
	E_SAVE,
	E_LOAD,
	E_INSERT,
	E_DELETE,
	E_MODETYPE,
	E_TOOLTYPE,
	O_XFLIP,
	O_YFLIP,
	O_ROTATEC,
	O_ROTATECC,
	O_SCALEU,
	O_SCALED,
	O_PREVOBJECT,
	O_NEXTOBJECT,
	A_PMENU = 29
};

/*
enum InputType
{
	Keyboard,
	Mouse
};

class KeyPress {
	InputType inputType;
	sf::Event::EventType EventType;

};
*/

class Options {

public:

	//Bindings are defined in OptionsMenu.cpp
	
	bool musicToggle = 1;
	bool sfxToggle = 1;
	std::vector<sf::Keyboard::Key> binding;
	std::vector<sf::Text> bindingString;
	std::vector<std::string> oddBalls = { "Escape", "LControl", "LShift",
		"LAlt", "LSystem", "RControl", "RShift", "RAlt", "RSystem", 
		"Menu", "LBracket", "RBracket", "SemiColon", "Comma", "Period", 
		"Quote", "Slash", "BackSlash", "Tilde", "Equal", "Dash", "Space", "Return", "BackSpace", "Tab", "PageUp", "PageDown",
		"End", "Home", "Insert", "Delete",
		"Add", "Subtract", "Multiply", "Divide",
		"Left", "Right", "Up", "Down",
		"Numpad0", "Numpad1", "Numpad2", "Numpad3",
		"Numpad4", "Numpad5", "Numpad6", "Numpad7",
		"Numpad8", "Numpad9", "F1", "F2",
		"F3", "F4", "F5", "F6",
		"F7", "F8", "F9", "F10",
		"F11", "F12", "F13", "F14",
		"F15" };
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
	
	sf::Color hText = sf::Color::Black;
	sf::Color uText = sf::Color(100, 100, 100, 255);

	static OptionsMenu optionsMenu;

	GUI_Handler guiHandler;				//guiHandler.buttons

	TextButton musicToggle;
	TextButton sfxToggle;
	TextButton changeBinding;
	std::vector<TextButton> KeyBind;
	
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

	void save();
	void load();

	void bindingCheck(int keyBinding, int setKey);
	Options options;

	static KeyBind * instance(GameEngine * engine) { keyBind.engine = engine; return &keyBind; }

protected:

	KeyBind() {}

private:

	int selected = -1;
	sf::Keyboard::Key newKey;

	static KeyBind keyBind;

	//std::vector <GUI *> buttons;

	TextButton changeBinding;
	std::vector<TextButton> KeyBindings;

	sf::Text title;
	sf::Text player;
	sf::Text editor;
	sf::Text object;
	sf::Text other;

	GUI_Handler guiHandler;

	TextButton p_left;
	TextButton p_right;
	TextButton p_jump;
	TextButton p_crouch;
	TextButton p_attack;
	TextButton p_special;
	TextButton p_block;

	TextButton e_select;
	TextButton e_deselect;
	TextButton e_zoom;
	TextButton e_quickpan;
	TextButton e_panr;
	TextButton e_panl;
	TextButton e_panu;
	TextButton e_pand;
	TextButton e_layeru;
	TextButton e_layerd;
	TextButton e_showline;
	TextButton e_save;
	TextButton e_load;
	TextButton e_insert;
	TextButton e_delete;
	TextButton e_modetype;
	TextButton e_tooltype;

	TextButton o_xflip;
	TextButton o_yflip;
	TextButton o_rotatec;
	TextButton o_rotatecc;
	TextButton o_scaleu;
	TextButton o_scaled;
	TextButton o_prevobj;
	TextButton o_nextobj;

	TextButton a_pmenu;

	sf::View view;
};

#endif