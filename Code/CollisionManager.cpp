#include "CollisionManager.h"
#include <vector>
#include <iostream>

CollisionManager::setGameMap(const GameMap* const gameMap) {
	this->gameMap = gameMap;
	createWalls();
}

CollisionManager::createWalls() {
	std::vector<std::vector<bool>> v1;
	v1.assign(gameMap->getGridSize().x, {0,0,0,0});
	wallsMap.assign(gameMap->getGridSize().y, v1);
	for (int i = 0; i < gameMap->getGridSize().x; i++) wallsMap[0][i][0] = 1;
	for (int i = 0; i < gameMap->getGridSize().x; i++) wallsMap[gameMap->getGridSize().y-1][i][1] = 1;
	for (int i = 0; i < gameMap->getGridSize().y; i++) wallsMap[i][0][2] = 1;
	for (int i = 0; i < gameMap->getGridSize().y; i++) wallsMap[i][gameMap->getGridSize().x-1][3] = 1;
	for (sf::Vector3i wall : gameMap->getWalls()) {
		if (wall.z == 0) {
			wallsMap[wall.y][wall.x][3] = 1;
			wallsMap[wall.y][wall.x+1][2] = 1;
		}
		else {
			wallsMap[wall.y][wall.x][1] = 1;
			wallsMap[wall.y+1][wall.x][0] = 1;
		}
	}
}

float min(std::vector<float> v) {
	float min = 10000;
	for (float x : v) if (x < min) min = x;
	return min;
}

float max(std::vector<float> v) {
	float max = 0;
	for (float x : v) if (x > max) max = x;
	return max;
}

bool CollisionManager::checkTankAndWalls(const Tank &tank) {
	float tXmin = min({tank.getA().x, tank.getB().x, tank.getC().x, tank.getD().x}) - gameMap->getPosition().x,
		  tXmax = max({tank.getA().x, tank.getB().x, tank.getC().x, tank.getD().x}) - gameMap->getPosition().x,
	 	  tYmin = min({tank.getA().y, tank.getB().y, tank.getC().y, tank.getD().y}) - gameMap->getPosition().y,
	 	  tYmax = max({tank.getA().y, tank.getB().y, tank.getC().y, tank.getD().y}) - gameMap->getPosition().y,
		  cS = gameMap->getCellSize(),
		  wT = gameMap->getWallThickness();
	int x1 = tXmin/cS,
		x2 = tXmax/cS,
		y1 = tYmin/cS,
		y2 = tYmax/cS;
	if (x1 == x2) {
		if (tXmin < x1 * cS + wT) x1--;
		else if (tXmax > (x2+1) * cS - wT) x2++;
		if (x1 == -1 || x2 == gameMap->getGridSize().x) return true;
	}
	if (y1 == y2) {
		if (tYmin < y1 * cS + wT) y1--;
		else if (tYmax > (y2+1) * cS - wT) y2++;
		if (y1 == -1 || y2 == gameMap->getGridSize().y) return true;
	}
	if (x1 < x2) {
		if (wallsMap[y2][x2][2]) {
			sf::RectangleShape r;
			r.setSize(sf::Vector2f(2 * wT, cS + 2 * wT));
			r.setPosition(sf::Vector2f(cS * x2 - wT, cS * y2 - wT) + gameMap->getPosition());
			if (checkTankAndRectangleShape(tank, r) == true) return true;
		}
	}
	if (y1 < y2) {
		if (wallsMap[y2][x2][0]) {
			sf::RectangleShape r;
			r.setSize(sf::Vector2f(cS + 2 * wT, 2 * wT));
			r.setPosition(sf::Vector2f(cS * x2 - wT, cS * y2 - wT) + gameMap->getPosition());
			if (checkTankAndRectangleShape(tank, r) == true) return true;
		}
	}
	if (x1 < x2 && y1 < y2) {
		if (wallsMap[y1][x1][3]) {
			sf::RectangleShape r;
			r.setSize(sf::Vector2f(2 * wT, cS + 2 * wT));
			r.setPosition(sf::Vector2f(cS * x2 - wT, cS * y1 - wT) + gameMap->getPosition());
			if (checkTankAndRectangleShape(tank, r) == true) return true;
		}
		if (wallsMap[y1][x1][1]) {
			sf::RectangleShape r;
			r.setSize(sf::Vector2f(cS + 2 * wT, 2 * wT));
			r.setPosition(sf::Vector2f(cS * x1 - wT, cS * y2 - wT) + gameMap->getPosition());
			if (checkTankAndRectangleShape(tank, r) == true) return true;
		}
	}
	return false;
}

const float PI = 3.14159265359;

sf::Vector2f rotateCoordinateSystem(const sf::Vector2f &point, const float &angle) {
	float angleInRadian = angle * PI / 180;
	return sf::Vector2f(point.x * cos(angleInRadian) + point.y * sin(angleInRadian),
						point.y * cos(angleInRadian) - point.x * sin(angleInRadian));
}

bool CollisionManager::checkTankAndRectangleShape(const Tank &tank, const sf::RectangleShape &rectangleShape) {
	sf::Vector2f rotatedPointA = rotateCoordinateSystem(tank.getPosition(), tank.getRotation())
								 - sf::Vector2f(tank.getSize().x / 2, tank.getSize().y / 2);
	sf::RectangleShape rotatedTank;
	rotatedTank.setSize(tank.getSize());
	rotatedTank.setPosition(rotatedPointA);
	
	sf::Vector2f rA = rectangleShape.getPosition(),
				 rB = rectangleShape.getPosition() + sf::Vector2f(rectangleShape.getSize().x, 0),
				 rC = rectangleShape.getPosition() + rectangleShape.getSize(),
				 rD = rectangleShape.getPosition() + sf::Vector2f(0, rectangleShape.getSize().y);
	float alpha = tank.getRotation();
	return (checkPointAndRectangleShape(tank.getA(), rectangleShape)) ||
		   (checkPointAndRectangleShape(tank.getB(), rectangleShape)) ||
		   (checkPointAndRectangleShape(tank.getC(), rectangleShape)) ||
		   (checkPointAndRectangleShape(tank.getD(), rectangleShape)) ||
		   (checkPointAndRectangleShape(rotateCoordinateSystem(rA, alpha), rotatedTank)) ||
		   (checkPointAndRectangleShape(rotateCoordinateSystem(rB, alpha), rotatedTank)) ||
		   (checkPointAndRectangleShape(rotateCoordinateSystem(rC, alpha), rotatedTank)) ||
		   (checkPointAndRectangleShape(rotateCoordinateSystem(rD, alpha), rotatedTank));
}

bool CollisionManager::checkPointAndRectangleShape(const sf::Vector2f &point, const sf::RectangleShape &rectangleShape) {
	return point.x > rectangleShape.getPosition().x &&
		   point.x < rectangleShape.getPosition().x + rectangleShape.getSize().x &&
		   point.y > rectangleShape.getPosition().y &&
		   point.y < rectangleShape.getPosition().y + rectangleShape.getSize().y;
}
