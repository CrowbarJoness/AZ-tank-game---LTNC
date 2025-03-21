#include "Tank.h"
#include "randomNumber.h"
#include <SFML/Window/Keyboard.hpp>
#include "CollisionManager.h"

const float PI = 3.14159265359;
float Tank::speed_pixelPerLoop = 0;
float Tank::rotateSpeed_degreePerLoop = 0;

Tank::setSize(const sf::Vector2f &size) {
	RectangleShape::setSize(size);
	setOrigin(size.x / 2, size.y / 2);
}

Tank::setPositionOnGameMap(const GameMap &gameMap) {
	sf::RectangleShape::setPosition(sf::Vector2f(
		gameMap.getPosition().x + gameMap.getCellSize() * (randomNumberInRange(0, gameMap.getGridSize().x - 1) + 0.5),
		gameMap.getPosition().y + gameMap.getCellSize() * (randomNumberInRange(0, gameMap.getGridSize().y - 1) + 0.5)
	));
}

Tank::moveForward() {
	move(Tank::speed_pixelPerLoop * sin(getRotation() * PI / 180),
		 Tank::speed_pixelPerLoop * -cos(getRotation() * PI / 180));
}

Tank::moveBackward() {
	move(Tank::speed_pixelPerLoop * -sin(getRotation() * PI / 180),
		 Tank::speed_pixelPerLoop * cos(getRotation() * PI / 180));
}

Tank::rotateLeft() {
	rotate(-Tank::rotateSpeed_degreePerLoop);
}

Tank::rotateRight() {
	rotate(Tank::rotateSpeed_degreePerLoop);
}

sf::Vector2f Tank::getA() const {
	return sf::Vector2f(
		getPosition().x + (-getSize().x/2) * cos(getRotation() * PI / 180) - (-getSize().y/2) * sin(getRotation() * PI / 180),
		getPosition().y + (-getSize().y/2) * cos(getRotation() * PI / 180) + (-getSize().x/2) * sin(getRotation() * PI / 180)
	);
}

sf::Vector2f Tank::getB() const {
	return sf::Vector2f(
		getPosition().x + (getSize().x/2) * cos(getRotation() * PI / 180) - (-getSize().y/2) * sin(getRotation() * PI / 180),
		getPosition().y + (-getSize().y/2) * cos(getRotation() * PI / 180) + (getSize().x/2) * sin(getRotation() * PI / 180)
	);
}

sf::Vector2f Tank::getC() const {
	return sf::Vector2f(
		getPosition().x + (getSize().x/2) * cos(getRotation() * PI / 180) - (getSize().y/2) * sin(getRotation() * PI / 180),
		getPosition().y + (getSize().y/2) * cos(getRotation() * PI / 180) + (getSize().x/2) * sin(getRotation() * PI / 180)
	);
}

sf::Vector2f Tank::getD() const {
	return sf::Vector2f(
		getPosition().x + (-getSize().x/2) * cos(getRotation() * PI / 180) - (getSize().y/2) * sin(getRotation() * PI / 180),
		getPosition().y + (getSize().y/2) * cos(getRotation() * PI / 180) + (-getSize().x/2) * sin(getRotation() * PI / 180)
	);
}
