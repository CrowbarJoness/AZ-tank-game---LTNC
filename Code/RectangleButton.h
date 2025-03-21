#ifndef RECTANGLE_BUTTON_H
#define RECTANGLE_BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>

class RectangleButton : public sf::RectangleShape {
private:
	sf::Texture texture;

public:
	setPositionAtCorner(const sf::Vector2f &position, const std::string &corner);
private:
	setPositionAtTopLeftCorner(const sf::Vector2f &position);
	setPositionAtTopRightCorner(const sf::Vector2f &position);
	setPositionAtBottomLeftCorner(const sf::Vector2f &position);
	setPositionAtBottomRightCorner(const sf::Vector2f &position);

public:
	setTextureFromBackgroundImage(const std::string &backgroundImageLink);
	
public:
	bool isPressed(const sf::Vector2f &mousePosition) const;
	
};
#endif
