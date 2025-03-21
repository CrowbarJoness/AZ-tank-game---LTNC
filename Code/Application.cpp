#include "Application.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>
#include "randomNumber.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>

Application::Application() : threadRunningHandleTanksMovement(handleTanksMovement, this) {
	createmainWindow();
	createCloseButton();
	createGameMap();
	pauseThread = false;
	collisionManager.setGameMap(&gameMap);
}

Application::createmainWindow() {
	mainWindow.create(sf::VideoMode::getDesktopMode(), "", sf::Style::Fullscreen);
	// I just don't want users to resize the window, so I set it as fullscreen.
}
	
Application::createCloseButton() {
	closeButton.setSize(sf::Vector2f(200,200));
	closeButton.setPositionAtCorner(sf::Vector2f(50,50), "top-right");
	closeButton.setOutlineThickness(-2);
	closeButton.setOutlineColor(sf::Color::Black);
	closeButton.setTextureFromBackgroundImage("Images/close button.jpg");
}
	
Application::createGameMap() {
	gameMap.setCellSizeAndResetGridSize(150);
	gameMap.setBackgroundColor(sf::Color(64,0,64));
	gameMap.setWallThickness(5);
	gameMap.setWallColor(sf::Color::Yellow);
	gameMap.setOutlineThickness(10);
	gameMap.setOutlineColor(sf::Color::Black);
}

Application::createTank() {
	tank.setSize(sf::Vector2f(60,80));
	tank.setPositionOnGameMap(gameMap);
	tank.setFillColor(sf::Color::Green);
	tank.setOutlineThickness(-3);
	tank.setOutlineColor(sf::Color::Black);
	Tank::speed_pixelPerLoop = 0.1;
	Tank::rotateSpeed_degreePerLoop = 0.05;
	
	threadRunningHandleTanksMovement.launch();
}

Application::run() {
	createTank();
	while(mainWindow.isOpen()) {
		handleWindowEvents();
		drawThings();
	}
}

Application::handleWindowEvents() {
	sf::Event event;
	while (mainWindow.pollEvent(event)) {
		// This should be in a while loop because there may be several events occur at one.   
        if (event.type == sf::Event::MouseButtonReleased) {
        	if (event.mouseButton.button == sf::Mouse::Left) {
        		if (closeButton.isPressed(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
        			mainWindow.close();
        	}
           	else if (event.mouseButton.button == sf::Mouse::Right) {
           		pauseThread = true;
           		gameMap.setGridSizeAndResizeAndResetWalls();
           		tank.setPositionOnGameMap(gameMap);
           		tank.setRotation(0);
           		collisionManager.setGameMap(&gameMap);
           		pauseThread = false;
           	}
        }
	}
}

Application::drawThings() {
	mainWindow.clear(sf::Color::White);
	mainWindow.draw(gameMap);
	mainWindow.draw(tank);
	mainWindow.draw(closeButton);
	
	mainWindow.display();
	
	/* Cited from SFML tutorial:
    "This clear/draw/display cycle is THE ONLY GOOD WAY to draw things.
	DON'T try other strategies [...].
	Modern graphics hardware and APIs are REALLY made for repeated clear/draw/display cycles
	where everything is completely refreshed at each iteration of the main loop." */
}

void Application::handleTanksMovement() {
	while(mainWindow.isOpen()) {
		if (pauseThread) continue;
		sf::Clock c;
		sf::Vector2f currentPosition = tank.getPosition();
		float currentRotation = tank.getRotation();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			tank.moveForward();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			tank.moveBackward();
		if (collisionManager.checkTankAndWalls(tank))
			tank.setPosition(currentPosition);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			tank.rotateLeft();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			tank.rotateRight();
		if (collisionManager.checkTankAndWalls(tank))
			tank.setRotation(currentRotation);
		while(1) if(c.getElapsedTime().asMicroseconds() > 200) break;
	}
}
