#include "ToolBox.h"

#include "PlatformMap.h"
#include "ObjectMap.h"
#include "Water.h"

#define DEFAULT_TEXT_SIZE 15

ToolBox::ToolBox(GameEngine * engine){

	this->engine = engine;

	mode = PLATFORM;
	tool = PLACE;

	/* View */

	toolBoxView.setViewport(sf::FloatRect(0, 0, 0.2f, 1));
	toolBoxView.setSize(toolBoxView.getViewport().width * engine->window.getSize().x, toolBoxView.getViewport().height * engine->window.getSize().y);

	/* Text */

	modeText = sf::Text("", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);
	toolText = sf::Text("", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);
	morphText1 = sf::Text("", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);
	morphText2 = sf::Text("", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);
	morphText3 = sf::Text("", engine->textureManager.slideFont, DEFAULT_TEXT_SIZE);

	modeText.setFillColor(sf::Color::Black);
	toolText.setFillColor(sf::Color::Black);
	morphText1.setFillColor(sf::Color::Black);
	morphText2.setFillColor(sf::Color::Black);
	morphText3.setFillColor(sf::Color::Black);

	modeText.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 20);
	toolText.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 70);
	morphText1.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 200);
	morphText2.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 250);
	morphText3.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 300);
	morphText4.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f + 20, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2.0f + 350);

	/* Tool Box */

	toolBox.setFillColor(sf::Color::White);
	toolBox.setSize(toolBoxView.getSize());
	toolBox.setPosition(toolBoxView.getCenter().x - toolBoxView.getSize().x / 2.0f, toolBoxView.getCenter().y - toolBoxView.getSize().y / 2);
	
	toolBarShade.setFillColor(sf::Color(200, 200, 200, 255));
	toolBarShade.setSize(sf::Vector2f(30.0f, (float)engine->window.getSize().y));
	toolBarShade.setPosition(toolBox.getGlobalBounds().left + toolBox.getLocalBounds().width - 30, toolBox.getGlobalBounds().top);

	/* Buttons */

	boxTool = IconButton(0, 0, engine->textureManager.getTexture("boxTool"), &doNothing);
	freeTool = IconButton(0, 0, engine->textureManager.getTexture("freeTool"), &doNothing);
	groundTool = IconButton(0, 0, engine->textureManager.getTexture("groundTool"), &doNothing);
	eventTool = IconButton(0, 0, engine->textureManager.getTexture("eventTool"), &doNothing);
	objectTool = IconButton(0, 0, engine->textureManager.getTexture("objectTool"), &doNothing);
	waterTool = IconButton(0, 0, engine->textureManager.getTexture("waterTool"), &doNothing);

	boxTool.sprite.setPosition(toolBox.getPosition().x + toolBox.getLocalBounds().width - 30, toolBox.getPosition().y);
	freeTool.sprite.setPosition(toolBox.getPosition().x + toolBox.getLocalBounds().width - 30, toolBox.getPosition().y + 30);
	groundTool.sprite.setPosition(toolBox.getPosition().x + toolBox.getLocalBounds().width - 30, toolBox.getPosition().y + 60);
	eventTool.sprite.setPosition(toolBox.getPosition().x + toolBox.getLocalBounds().width - 30, toolBox.getPosition().y + 120);
	objectTool.sprite.setPosition(toolBox.getPosition().x + toolBox.getLocalBounds().width - 30, toolBox.getPosition().y + 180);
	waterTool.sprite.setPosition(toolBox.getPosition().x + toolBox.getLocalBounds().width - 30, toolBox.getPosition().y + 240);

	//guiHandler.buttons.resize(5);
	//guiHandler.buttons = { &boxTool, &freeTool, &groundTool, &eventTool, &objectTool };

}

void ToolBox::highlightButtons(sf::Vector2i position) {

	engine->window.setView(toolBoxView);
	//guiHandler.isSelected(engine->window.mapPixelToCoords(position));
	boxTool.isSelected(engine->window.mapPixelToCoords(position));
	freeTool.isSelected(engine->window.mapPixelToCoords(position));
	groundTool.isSelected(engine->window.mapPixelToCoords(position));
	eventTool.isSelected(engine->window.mapPixelToCoords(position));
	objectTool.isSelected(engine->window.mapPixelToCoords(position));
	waterTool.isSelected(engine->window.mapPixelToCoords(position));

}

void ToolBox::clickButtons(sf::Vector2i position) {

	engine->window.setView(toolBoxView);

	if (boxTool.isSelected(engine->window.mapPixelToCoords(position))) {
		mode = PLATFORM;
		tool = BOX_PLACE;
		modeText.setString("Mode: Platform");
		toolText.setString("Tool: Box Place");
	}

	else if (freeTool.isSelected(engine->window.mapPixelToCoords(position))) {
		mode = PLATFORM;
		tool = PLACE;
		modeText.setString("Mode: Platform");
		toolText.setString("Tool: Free Place");
	}

	else if (groundTool.isSelected(engine->window.mapPixelToCoords(position))) {
		mode = PLATFORM;
		tool = GROUND_PLACE;
		modeText.setString("Mode: Platform");
		toolText.setString("Tool: Ground Place");
	}

	else if (objectTool.isSelected(engine->window.mapPixelToCoords(position))) {
		mode = OBJECT;
		tool = PLACE;
		modeText.setString("Mode: Object");
		toolText.setString("Tool: Place");
	}

	else if (eventTool.isSelected(engine->window.mapPixelToCoords(position))) {
		mode = EVENT;
		tool = PLACE;
		modeText.setString("Mode: Event");
		toolText.setString("Tool: Place");
	}

	else if (waterTool.isSelected(engine->window.mapPixelToCoords(position))) {
		mode = WATER;
		tool = PLACE;
		modeText.setString("Mode: Water");
		toolText.setString("Tool: Place");
	}

}

bool ToolBox::contains(sf::Vector2i position) {

	engine->window.setView(toolBoxView);

	return toolBox.getGlobalBounds().contains(engine->window.mapPixelToCoords(position));

}

void ToolBox::update() {

}

void ToolBox::render() {

	engine->window.setView(toolBoxView);

	engine->window.draw(toolBox);
	engine->window.draw(modeText);
	engine->window.draw(toolText);
	engine->window.draw(morphText1);
	engine->window.draw(morphText2);
	engine->window.draw(morphText3);
	engine->window.draw(morphText4);
	engine->window.draw(toolBarShade);
	//guiHandler.draw(&engine->window);
	engine->window.draw(boxTool.sprite);
	engine->window.draw(freeTool.sprite);
	engine->window.draw(groundTool.sprite);
	engine->window.draw(objectTool.sprite);
	engine->window.draw(eventTool.sprite);
	engine->window.draw(waterTool.sprite);

}

void ToolBox::nextMode() {

	if (mode == PLATFORM) {
		mode = OBJECT;
		tool = PLACE;
		modeText.setString("Mode: Object");
		morphText1.setString("Points: N\\A");
	}
	else if (mode == OBJECT) {
		mode = EVENT;
		modeText.setString("Mode: Event");
		morphText1.setString("Points: N\\A");
	}
	else if (mode == EVENT) {
		mode = WATER;
		modeText.setString("Mode: Water");
		morphText1.setString("Points: N\\A");
	}
	else {
		mode = PLATFORM;
		modeText.setString("Mode: Platform");
		morphText1.setString("Points: N\\A");
	}

}

void ToolBox::nextTool() {

	if (mode == PLATFORM) {

		if (tool == PLACE) {
			tool = BOX_PLACE;
			toolText.setString("Tool: Box");
		}
		if (tool == BOX_PLACE) {
			tool = GROUND_PLACE;
			toolText.setString("Tool: Ground");
		}
		else {
			tool = PLACE;
			toolText.setString("Tool: Place");
		}

	}

	else if (mode == OBJECT) {

	}

	else if (mode == WATER) {
		
	}

	else if (mode == EVENT) {

	}

}

Mode ToolBox::getMode() {
	return mode;
}

Tool ToolBox::getTool() {
	return tool;
}

void ToolBox::selectPlatform(sf::ConvexShape * platform) {
	//Position
	morphText1.setString("Coordinate Position:\nX: " + std::to_string(platform->getPosition().x) + "\nY: " + std::to_string(platform->getPosition().y));
	//
	morphText2.setString("");
	//
	morphText3.setString("");
	//
	morphText4.setString("");
}

void ToolBox::selectObject(Object * object) {
	//Position
	morphText1.setString("Coordinate Position:\nX: " + std::to_string(object->position.x) + "\nY: " + std::to_string(object->position.y));
	//Name
	morphText2.setString(object->textureName);
	//Rotation
	morphText3.setString("Rotation: " + std::to_string(object->rotate));
	//Scale
	morphText4.setString("Scale: " + std::to_string(object->scale));
}

void ToolBox::selectWater(Water * water) {
	//Position Top Left
	morphText1.setString("Top Left Position:\nX: " + std::to_string(water->topLeft.x) + "\nY: " + std::to_string(water->topLeft.y));
	//Position Bottom Right
	morphText2.setString("Bottom Right Position:\nX: " + std::to_string(water->bottomRight.x) + "\nY: " + std::to_string(water->bottomRight.y));
	//
	morphText3.setString("");
	//
	morphText4.setString("");
}