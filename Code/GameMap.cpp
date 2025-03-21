#include "GameMap.h"
#include "randomNumber.h"
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Rect.hpp>

GameMap::GameMap() {
	this->renderTexture.create(sf::VideoMode::getDesktopMode().width,
							   sf::VideoMode::getDesktopMode().height);
}

float GameMap::getCellSize() const {
	return cellSize;
}

sf::Vector2i GameMap::getGridSize() const {
	return gridSize;
}

float GameMap::getWallThickness() const {
	return wallThickness;
}

std::vector<sf::Vector3i> GameMap::getWalls() const {
	return Walls;
}

GameMap::setCellSizeAndResetGridSize(const float &cellSize) {
	this->setCellSize(cellSize);
	this->setGridSizeAndResizeAndResetWalls();
}

void GameMap::setCellSize(const float &cellSize) {
	this->cellSize = cellSize;
}

GameMap::setGridSizeAndResizeAndResetWalls() {
	this->setGridSize();
	this->setSizeAndReposition();
	this->setWalls();
}

void GameMap::setGridSize() {
	this->gridSize = sf::Vector2i(
		randomNumberInRange(2, (sf::VideoMode::getDesktopMode().width
		 		   			    - 2 * this->getOutlineThickness())
								/ this->cellSize),
		randomNumberInRange(2, (sf::VideoMode::getDesktopMode().height
					   			- 2 * this->getOutlineThickness())
								/ this->cellSize)
	);
}

void GameMap::setSizeAndReposition() {
	this->setSize();
	this->setPositionToCenter();
}

void GameMap::setSize() {
	RectangleShape::setSize(sf::Vector2f(this->cellSize * this->gridSize.x, this->cellSize * this->gridSize.y));
}

void GameMap::setPositionToCenter() {
	RectangleShape::setPosition(sf::Vector2f(int((sf::VideoMode::getDesktopMode().width - this->getSize().x) / 2),
					  				   			int((sf::VideoMode::getDesktopMode().height - this->getSize().y) / 2)));
}

void GameMap::setWalls() {	
	this->Walls.clear();
	
	std::vector<sf::Vector3i> allPossibleWalls;
	for (int i = 0; i < this->gridSize.x - 1; i++) // add all possible vertical walls
		for (int j = 0; j < this->gridSize.y; j++)
			allPossibleWalls.push_back(sf::Vector3i(i,j,0));

	for (int i = 0; i < this->gridSize.x; i++) // add all possible horizontal walls
		for (int j = 0; j < this->gridSize.y - 1; j++)
			allPossibleWalls.push_back(sf::Vector3i(i,j,1));
			
	bool connected[gridSize.x][gridSize.y][4];
	for (int i = 0; i < gridSize.x; i++)
		for (int j = 0; j < gridSize.y; j++)
			for (int k = 0; k < 4; k++)
				connected[i][j][k] = true;
	for (int i = 0; i < gridSize.x; i++) {
		connected[i][0][0] = false;
		connected[i][gridSize.y - 1][1] = false;
	}
	for (int i = 0; i < gridSize.y; i++) {
		connected[0][i][2] = false;
		connected[gridSize.x - 1][i][3] = false;
	}
	int X[4] = {0,0,-1,1}, Y[4] = {-1,1,0,0}; // UP - DOWN - LEFT - RIGHT
	while(!allPossibleWalls.empty()) {
		int randomIndex = randomNumberInRange(0,allPossibleWalls.size() - 1);
		sf::Vector3i randomWall = allPossibleWalls[randomIndex];
		allPossibleWalls.erase(allPossibleWalls.begin() + randomIndex);
		
		std::vector<sf::Vector2i> BFS;
		
		int cellMark[gridSize.x][gridSize.y];
		for (int i = 0; i < gridSize.x; i++)
			for (int j = 0; j < gridSize.y; j++)
				cellMark[i][j] = 0;
		
		BFS.push_back(sf::Vector2i(randomWall.x, randomWall.y));
		cellMark[randomWall.x][randomWall.y] = 1;
		if (randomWall.z == 0) {
			connected[randomWall.x][randomWall.y][3] = false;
			connected[randomWall.x + 1][randomWall.y][2] = false;
			BFS.push_back(sf::Vector2i(randomWall.x + 1, randomWall.y));
			cellMark[randomWall.x + 1][randomWall.y] = 2;
		}
		else {
			connected[randomWall.x][randomWall.y][1] = false;
			connected[randomWall.x][randomWall.y + 1][0] = false;
			BFS.push_back(sf::Vector2i(randomWall.x, randomWall.y + 1));
			cellMark[randomWall.x][randomWall.y + 1] = 2;
		}
		
		int indexOfLastCellMarked1 = 0, indexOfLastCellMarked2 = 1;
		bool isFork04Broken = false;
		for (int i = 0; i < BFS.size(); i++) { // BFS from both cells in parallel
			int BFSSizeBeforeThisLoop = BFS.size();
			for (int k = 0; k < 4; k++) {
				if (connected[BFS[i].x][BFS[i].y][k] == true) {
					if (cellMark[BFS[i].x + X[k]][BFS[i].y + Y[k]] == 0) {
						BFS.push_back(sf::Vector2i(BFS[i].x + X[k], BFS[i].y + Y[k]));
						cellMark[BFS[i].x + X[k]][BFS[i].y + Y[k]] = cellMark[BFS[i].x][BFS[i].y];
						if (cellMark[BFS[i].x][BFS[i].y] == 1) indexOfLastCellMarked1 = BFS.size() - 1;
						else indexOfLastCellMarked2 = BFS.size() - 1;
					}
					else if (cellMark[BFS[i].x + X[k]][BFS[i].y + Y[k]] != cellMark[BFS[i].x][BFS[i].y]) {
						this->Walls.push_back(randomWall);
						isFork04Broken = true;
						break;
					}
				}
			}
			if (isFork04Broken == true) break;
			if (BFS.size() == BFSSizeBeforeThisLoop &&
				(i == indexOfLastCellMarked1 || i == indexOfLastCellMarked2)) {
				if (randomWall.z == 0) {
					connected[randomWall.x][randomWall.y][3] = true;
					connected[randomWall.x + 1][randomWall.y][2] = true;
				}
				else {
					connected[randomWall.x][randomWall.y][1] = true;
					connected[randomWall.x][randomWall.y + 1][0] = true;
				}
				break;
			}
		}
	}
	this->Walls.resize(randomNumberInRange(0, this->Walls.size()));
	this->display();
}

void GameMap::setBackgroundColor(const sf::Color &backgroundColor) {
	this->backgroundColor = backgroundColor;
	this->display();
}

void GameMap::setWallThickness(const float &wallThickness) {
	this->wallThickness = wallThickness;
	this->display();
}

void GameMap::setWallColor(const sf::Color &wallColor) {
	this->wallColor = wallColor;
	this->display();
}

void GameMap::display() {
	this->renderTexture.clear(this->backgroundColor);
	this->drawWalls();
	this->renderTexture.display();
	this->setTexture(&renderTexture.getTexture());
	this->setTextureRect(sf::IntRect(sf::Vector2i(0,0), sf::Vector2i(this->getSize())));
}

void GameMap::drawWalls() {
	for (sf::Vector3i wall : this->Walls) {
		if (wall.z == 0) drawVerticalWall(sf::Vector2i(wall.x, wall.y));
		else drawHorizontalWall(sf::Vector2i(wall.x, wall.y));
	}
	drawBorderWall();
}

void GameMap::drawVerticalWall(sf::Vector2i const &positionInGrid) {
	RectangleShape verticalWall;
	verticalWall.setSize(sf::Vector2f(2 * this->wallThickness,
									  this->cellSize + 2 * this->wallThickness));
	verticalWall.setPosition(sf::Vector2f(this->cellSize * (positionInGrid.x + 1) - this->wallThickness,
										  this->cellSize * positionInGrid.y - this->wallThickness));
	verticalWall.setFillColor(this->wallColor);
	this->renderTexture.draw(verticalWall);
}

void GameMap::drawHorizontalWall(sf::Vector2i const &positionInGrid) {
	RectangleShape horizontalWall;
	horizontalWall.setSize(sf::Vector2f(this->cellSize + 2 * this->wallThickness,
										2 * this->wallThickness));
	horizontalWall.setPosition(sf::Vector2f(this->cellSize * positionInGrid.x - this->wallThickness,
											this->cellSize * (positionInGrid.y + 1) - this->wallThickness));
	horizontalWall.setFillColor(this->wallColor);
	this->renderTexture.draw(horizontalWall);
}

void GameMap::drawBorderWall() {
	RectangleShape transparentRectangleShapeWithBorder;
	transparentRectangleShapeWithBorder.setSize(this->getSize());
	transparentRectangleShapeWithBorder.setPosition(sf::Vector2f(0,0));
	transparentRectangleShapeWithBorder.setFillColor(sf::Color::Transparent);
	transparentRectangleShapeWithBorder.setOutlineThickness(-this->wallThickness);
	transparentRectangleShapeWithBorder.setOutlineColor(this->wallColor);
	this->renderTexture.draw(transparentRectangleShapeWithBorder);
}
