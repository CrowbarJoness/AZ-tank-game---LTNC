#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "RectangleButton.h"
#include "GameMap.h"
#include "Tank.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Thread.hpp>
#include "CollisionManager.h"

class Application {
private:
	sf::RenderWindow mainWindow;
	RectangleButton closeButton;
	GameMap gameMap;
	Tank tank;
	sf::Thread threadRunningHandleTanksMovement;
	bool pauseThread;
	CollisionManager collisionManager;
public: std::vector<int> v;

public:
	Application();
private:
	createmainWindow();
	createCloseButton();
	createGameMap();
	createTank();
	
public:
	run();
private:
	handleWindowEvents();
	drawThings();
	
private:
	void handleTanksMovement();
};

#endif
