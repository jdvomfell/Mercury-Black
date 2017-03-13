#include "OptionsMenu.h"
#include  <iostream>

void KeyBind::init() {

	hText = sf::Color::Black;
	uText = sf::Color(100, 100, 100, 255);

	title = sf::Text("Key Bindings", engine->textureManager.font, OPTION_TITLE_SIZE);
	title.setFillColor(sf::Color::Black);
	title.setOutlineThickness(5);
	title.setOutlineColor(uText);
	title.setOrigin(title.getGlobalBounds().width / 2, title.getGlobalBounds().height / 2);

/*	p_left = Button("Run Left", 0, 0, uText, OPTION_FONT_SIZE, &engine->textureManager.font, &doNothing);
	p_left.text.setPosition(view.getCenter().x - (view.getSize().x / 2) * 1 / 3, title.getPosition().y + (view.getSize().y / 2) * 2 / 3);

	buttons.resize(32);
	buttons = { &p_left,
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
				&e_entitytype,
				&e_entityaction,

				&o_xflip,
				&o_yflip,
				&o_rotatec,
				&o_rotatecc,
				&o_scaleu,
				&o_scaled,

				&a_bmenu,
				&a_fmenu };
	*/			
	view = engine->window.getDefaultView();
	engine->window.setView(view);

	title.setPosition(view.getCenter().x, view.getCenter().y - (view.getSize().y / 5));

	changeBinding.text.setPosition(view.getCenter().x + (view.getSize().x / 2) * 1 / 3, title.getPosition().y + (view.getSize().y / 2) * 2 / 3);

}

void KeyBind::clean() {

}

void KeyBind::handleEvent() {

	sf::Event event;

	if (engine->window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::MouseMoved:

			for (size_t i = 0; i < buttons.size(); i++) {

				if (buttons[i]->isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y))))
					buttons[i]->text.setFillColor(hText);
				else
					buttons[i]->text.setFillColor(uText);

			}
			break;

		case sf::Event::MouseButtonPressed:

			if (event.mouseButton.button == sf::Mouse::Left) {

				for (size_t i = 0; i < buttons.size(); i++) {

					if (buttons[i]->isSelected(engine->window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y))))
						buttons[i]->interact(engine);

				}

			}
			break;


		case sf::Event::Closed:
			engine->quit();
			break;

		}

	}
}

void KeyBind::update(const float dt) {

}

void KeyBind::render(const float dt) {

	for (size_t i = 0; i < buttons.size(); i++)
		engine->window.draw(buttons[i]->text);
	engine->window.draw(title);
}

void KeyBind::bindingCheck(int keyBinding, int setKey)
{

	if (setKey < sf::Keyboard::KeyCount && setKey >= 0) {

	}

}