#ifndef TANK_H
#define TANK_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "GameMap.h"

class Tank : public sf::RectangleShape  {
public:
	static float speed_pixelPerLoop;
	static float rotateSpeed_degreePerLoop;
	
public:
	setSize(const sf::Vector2f &size);
	setPositionOnGameMap(const GameMap &gameMap);

public:
	moveForward();
	moveBackward();
	rotateLeft();
	rotateRight();
	
public:
	sf::Vector2f getA() const;
	sf::Vector2f getB() const;
	sf::Vector2f getC() const;
	sf::Vector2f getD() const;
};

#endif
