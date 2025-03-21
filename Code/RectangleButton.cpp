#include "RectangleButton.h"
#include <SFML/Window/VideoMode.hpp>

RectangleButton::setPositionAtCorner(const sf::Vector2f &position, const std::string &corner) {
	if (corner == "top-left")
		setPositionAtTopLeftCorner(position);
	else if (corner == "top-right")
		setPositionAtTopRightCorner(position);
	else if (corner == "bottom-left")
		setPositionAtBottomLeftCorner(position);
	else if (corner == "bottom-right")
		setPositionAtBottomRightCorner(position);
}

RectangleButton::setPositionAtTopLeftCorner(const sf::Vector2f &position) {
	setPosition(position);
}

RectangleButton::setPositionAtTopRightCorner(const sf::Vector2f &position) {
	setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width
								 - getSize().x
							     - position.x,
							 position.y));
}

RectangleButton::setPositionAtBottomLeftCorner(const sf::Vector2f &position) {
	setPosition(sf::Vector2f(position.x,
							 sf::VideoMode::getDesktopMode().height
						   		 - getSize().y
							     - position.y));
}

RectangleButton::setPositionAtBottomRightCorner(const sf::Vector2f &position) {
	setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width
						     	 - getSize().x
				 		     	 - position.x,
							 sf::VideoMode::getDesktopMode().height
								 - getSize().y
							  	 - position.y));
}

RectangleButton::setTextureFromBackgroundImage(const std::string &backgroundImageLink) {
	texture.loadFromFile(backgroundImageLink);
	setTexture(&texture);
}

bool RectangleButton::isPressed(const sf::Vector2f &mousePosition) const {
	return mousePosition.x >= getPosition().x &&
		   mousePosition.x < getPosition().x + getSize().x &&
		   mousePosition.y >= getPosition().y &&
		   mousePosition.y < getPosition().y + getSize().y;
}
