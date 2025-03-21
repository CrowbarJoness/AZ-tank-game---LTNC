#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <vector>
#include <SFML/System/Vector3.hpp>

class GameMap : public sf::RectangleShape {
private:
	float cellSize;
	sf::Vector2i gridSize;
	sf::Color backgroundColor;
	float wallThickness;
	sf::Color wallColor;
	sf::RenderTexture renderTexture;
	std::vector<sf::Vector3i> Walls;
	/* A wall, as a Vector3i, has 3 arguments:
	- Walls[i].z equals to 0 if Walls[i] is a vertical wall, or 1 if it is horizontal.
	  (a wall separate two adjacent cells, so it is either vertical or horizontal)
	- Walls[i].x is the x coordination of the wall.
	  + If Walls[i] is a vertical wall, Walls[i].x has gridSize.x - 1 possible values
	  + If Walls[i] is a horizontal wall, Walls[i].x has gridSize.x possible values
	- Walls[i].y is the y coordination of the wall.
	  + If Walls[i] is a vertical wall, Walls[i].y has gridSize.y possible values
	  + If Walls[i] is a horizontal wall, Walls[i].y has gridSize.y - 1 possible values */

	
public:
	GameMap();
	
public:
	float getCellSize() const;
	sf::Vector2i getGridSize() const;
	float getWallThickness() const;
	std::vector<sf::Vector3i> getWalls() const;
	
public:
	setCellSizeAndResetGridSize(const float &cellSize);
	setGridSizeAndResizeAndResetWalls();
private:
	void setCellSize(const float &cellSize);
	void setGridSize();
	void setSizeAndReposition();
	void setSize();
	void setPositionToCenter();
public: void setWalls();

public:
	void setBackgroundColor(const sf::Color &backgroundColor = sf::Color::White);
	void setWallThickness(const float &wallThickness = 0);
	void setWallColor(const sf::Color &wallColor = sf::Color::White);
		
private: void display();
	void drawWalls();
	void drawVerticalWall(sf::Vector2i const &positionInGrid);
	void drawHorizontalWall(sf::Vector2i const &positionInGrid);
	void drawBorderWall();
};
#endif
