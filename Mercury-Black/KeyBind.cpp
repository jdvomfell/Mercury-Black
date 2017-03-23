#include "OptionsMenu.h"
#include<fstream>
KeyBind KeyBind::keyBind;

void KeyBind::init() {

	sf::Color hText = sf::Color::Black;
	sf::Color uText = sf::Color(100, 100, 100, 255);

	load();

	title = sf::Text("Key Bindings:", engine->textureManager.font, KEYBIND_TITLE_SIZE);
	title.setFillColor(sf::Color::Black);
	title.setOutlineThickness(5);
	title.setOutlineColor(uText);
	title.setPosition(20, 0);
	//title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

	player = sf::Text("Player:", engine->textureManager.slideFont, KEYBIND_FONT_SIZE);
	player.setFillColor(sf::Color::Black);
	player.setPosition(20, 120);

	p_left = TextButton("Run Left", 20, 140, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	p_right = TextButton("Run Right", 20, 160, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	p_jump = TextButton("Jump", 20, 180, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	p_crouch = TextButton("Crouch", 20, 200, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	p_attack = TextButton("Attack", 20, 220, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	p_special = TextButton("Special", 20, 240, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	p_block = TextButton("Block", 20, 260, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);

	editor = sf::Text("Editor:", engine->textureManager.slideFont, KEYBIND_FONT_SIZE);
	editor.setFillColor(sf::Color::Black);
	editor.setPosition(20, 320);

	e_select = TextButton("Select", 20, 340, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_quickpan = TextButton("Quickpan", 20, 360, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_panl = TextButton("Pan Left", 20, 380, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_panr = TextButton("Pan Right", 20, 400, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_panu = TextButton("Pan Up", 20, 420, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_pand = TextButton("Pan Down", 20, 440, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_layeru = TextButton("Move Layer Closer", 20, 460, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_layerd = TextButton("Move Layer Farther", 20, 480, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_save = TextButton("Editor Save", 20, 500, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_load = TextButton("Editor Load", 20, 520, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_insert = TextButton("Editor Insert", 20, 540, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_delete = TextButton("Delete", 20, 560, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_modetype = TextButton("Next Mode", 20, 580, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	e_tooltype = TextButton("Next Tool", 20, 600, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	
	object = sf::Text("Object:", engine->textureManager.slideFont, KEYBIND_FONT_SIZE);
	object.setFillColor(sf::Color::Black);
	object.setPosition(300, 120);

	o_xflip = TextButton("X-Flip", 300, 140, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	o_yflip= TextButton("Y-Flip", 300, 160, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	o_rotatec = TextButton("Rotate Right", 300, 180, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	o_rotatecc = TextButton("Rotate Left", 300, 200, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	o_scaleu = TextButton("Scale Up", 300, 220, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	o_scaled = TextButton("Scale Down", 300, 240, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	o_prevobj = TextButton("Next Object", 300, 260, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	o_nextobj= TextButton("Previous Object", 300, 280, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);

	other = sf::Text("Menu Select:", engine->textureManager.slideFont, KEYBIND_FONT_SIZE);
	other.setFillColor(sf::Color::Black);
	other.setPosition(300, 320);

	a_pmenu = TextButton("Pause", 300, 340, KEYBIND_FONT_SIZE, &engine->textureManager.slideFont, &doNothing);
	
	options.binding.resize(32);
	options.bindingString.resize(32);

	for (int i = 0; i < 32; i++) {
		if (options.binding[i] >= 0 && options.binding[i] < 26) {
			options.bindingString[i] = sf::Text((char) ((char) options.binding[i]+'A'), engine->textureManager.slideFont, KEYBIND_FONT_SIZE);
		}
		else if (options.binding[i] >= 26 && options.binding[i] < 36) {
			options.bindingString[i] = sf::Text((char)((char) options.binding[i] + '0'), engine->textureManager.slideFont, KEYBIND_FONT_SIZE);
		}
		else if (options.binding[i] >= 36 && options.binding[i] < sf::Keyboard::KeyCount) {
			options.bindingString[i] = sf::Text(options.oddBalls[options.binding[i]], engine->textureManager.slideFont, KEYBIND_FONT_SIZE);
		}
	}
	
	for (int i = 0; i <= A_PMENU; i++) {
		if (i >= A_PMENU) {
			options.bindingString[i].setPosition(300, 340 + 20 * (i-A_PMENU));
			continue;
		}
		else if (i >= O_XFLIP) {
			options.bindingString[i].setPosition(300, 140 + 20 * (i-O_XFLIP));
			continue;
		}
		else if (i >= E_SELECT) {
			options.bindingString[i].setPosition(20, 340 + 20 * (i-E_SELECT));
			continue;
		}
		else
			options.bindingString[i].setPosition(20, 140 + 20 * i);

	}

	guiHandler.buttons.resize(32);
	guiHandler.buttons = { &p_left,
				&p_right,
				&p_jump,
				&p_crouch,
				&p_attack,
				&p_special,
				&p_block,

				&e_select,
				&e_deselect,
				&e_zoom,
				&e_quickpan,
				&e_panr,
				&e_panl,
				&e_panu,
				&e_pand,
				&e_layeru,
				&e_layerd,
				&e_showline,
				&e_save,
				&e_load,
				&e_insert,
				&e_delete,
				&e_modetype,
				&e_tooltype,

				&o_xflip,
				&o_yflip,
				&o_rotatec,
				&o_rotatecc,
				&o_scaleu,
				&o_scaled,

				&a_pmenu };
			
	view = engine->window.getDefaultView();
	engine->window.setView(view);

	//title.setPosition(view.getCenter().x, view.getCenter().y - (view.getSize().y / 5));

	changeBinding.text.setPosition(view.getCenter().x + (view.getSize().x / 2) * 1 / 3, title.getPosition().y + (view.getSize().y / 2) * 2 / 3);

}

void KeyBind::clean() {

}

void KeyBind::handleEvent() {

	sf::Event event;


	if (engine->window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::MouseMoved:

			guiHandler.isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)));

			break;

		case sf::Event::MouseButtonPressed:

			if (event.mouseButton.button == sf::Mouse::Left) {
				for (size_t i = 0; i < guiHandler.buttons.size(); i++) {
					if (guiHandler.buttons[i]->isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
						selected = i;
				}
			}
			break;

		case sf::Event::KeyPressed:

			if (event.key.code == sf::Keyboard::Escape)
				engine->popState();
			
			else if (selected != -1) {
				options.binding[selected] = event.key.code;
				save();

			}
			break;

		case sf::Event::Closed:
			engine->quit();
			break;

		}

	}
}
void KeyBind::load() {
	std::ifstream ifstream;
	std::string KeybindFilename = "keybind";
	int readinKey;
	int i = 0;

	if (!ifstream.is_open()) {
		printf("Cannot Open Keybinding File (Possibly No File To Load)\n");
		return;
	}

	clean();

	while (ifstream >> readinKey) {

		if (ifstream.eof() || i >= options.binding.size())
			return;

		options.binding[i] = (sf::Keyboard::Key) readinKey;
		i++;
	}

	ifstream.close();
}

void KeyBind::save() {
	std::ofstream ofstream;
	
	std::string KeybindFilename = "keybind.dat";
	ofstream.open(KeybindFilename, std::ios::out | std::ios::binary);

	for (int i = 0; i < options.binding.size(); i++) {
		printf("%s\n", options.bindingString[i]);

		ofstream
			<< options.binding[i] << std::endl;
	}

	printf("Successfully saved keybindings.\n");

	ofstream.close();

}

void KeyBind::update(const float dt) {

}

void KeyBind::render(const float dt) {

	engine->window.clear(sf::Color(248, 240, 225));

	guiHandler.draw(&engine->window);

	engine->window.draw(title);
	engine->window.draw(player);
	engine->window.draw(editor);
	engine->window.draw(object);
	engine->window.draw(other);
}

void KeyBind::bindingCheck(int keyBinding, int setKey)
{

	if (setKey < sf::Keyboard::KeyCount && setKey >= 0) {
		return;
	}

}