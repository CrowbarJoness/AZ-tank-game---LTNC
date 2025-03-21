#ifndef COLLISION_MAMAGER_H
#define COLLISION_MAMAGER_H

#include "GameMap.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include "Tank.h"

class CollisionManager {
private:
	const GameMap* gameMap;
	std::vector<std::vector<std::vector<bool>>> wallsMap;
public:
	setGameMap(const GameMap* const gameMap);
private:
	createWalls();
	
public:
	bool checkTankAndWalls(const Tank &tank);

public:
	static bool checkTankAndRectangleShape(const Tank &tank, const sf::RectangleShape &rectangleShape);
private:
	static bool checkPointAndRectangleShape(const sf::Vector2f &point, const sf::RectangleShape &rectangleShape);
	static bool checkPointAndTank(const sf::Vector2f &point, const Tank &tank);
};

#endif
