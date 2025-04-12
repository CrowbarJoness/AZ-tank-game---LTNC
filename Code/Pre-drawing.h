void drawMap () {
	RectangleShape HorizontalWall (Vector2f (CellSize, WallThickness) ),
				   VerticalWall (Vector2f (WallThickness, CellSize) );
	HorizontalWall.setFillColor (Color::Black);
	VerticalWall.setFillColor (Color::Black);
	RectangleShape ground (Vector2f (MapWidth * CellSize, MapHeight * CellSize) );
	ground.setFillColor(Color(255,255,255,200));
	ground.setOutlineThickness (WallThickness);
	ground.setOutlineColor (Color::Black);
	ground.setPosition (HorizontalBorden, VerticalBorden);
	ground.setTexture(&MapBackground);
	MainWindow.draw (ground);
	f(i,MapWidth) f(j,MapHeight) {
		if (Map[i][j][0]) {
			HorizontalWall.setPosition (HorizontalBorden + i * CellSize, VerticalBorden + j * CellSize);
			MainWindow.draw (HorizontalWall);
		}
		if (Map[i][j][1]) {
			VerticalWall.setPosition (HorizontalBorden + (i+1) * CellSize - WallThickness, VerticalBorden + j * CellSize);
			MainWindow.draw (VerticalWall);
		}
		if (Map[i][j][2]) {
			HorizontalWall.setPosition (HorizontalBorden + i * CellSize, VerticalBorden + (j+1) * CellSize - WallThickness);
			MainWindow.draw (HorizontalWall);
		}
		if (Map[i][j][3]) {
			VerticalWall.setPosition (HorizontalBorden + i * CellSize, VerticalBorden + j * CellSize);
			MainWindow.draw (VerticalWall);
		}
	}
	RectangleShape HomeRect(Vector2f(30,30));
	HomeRect.setPosition(10,10);
	HomeRect.setFillColor(Color(255,255,255));
	HomeRect.setOutlineThickness(-2);
	HomeRect.setOutlineColor(Color(0,0,0));
	HomeRect.setTexture(&HomeButton);
	MainWindow.draw(HomeRect);
}

void designTankBlueprint() {
	RenderTexture TankBlueprint;
	TankBlueprint.create(WindowWidth, WindowHeight);
	
	RectangleShape Rectangle1( Vector2f(31,41) );
	Rectangle1.setFillColor (Color::White);
	Rectangle1.setPosition(0,0);
	TankBlueprint.draw(Rectangle1);
	
	RectangleShape Rectangle2( Vector2f (19,19) );
	Rectangle2.setFillColor (Color::White);
	Rectangle2.setOutlineThickness(-2);
	Rectangle2.setOutlineColor(Color::Black);
	Rectangle2.setPosition(6,11);
	TankBlueprint.draw(Rectangle2);
	
	RectangleShape Rectangle3 (Vector2f (5, 20) );
	Rectangle3.setFillColor (Color::White);
	Rectangle3.setOutlineThickness(-1);
	Rectangle3.setOutlineColor(Color::Black);
	Rectangle3.setPosition(13,0);
	TankBlueprint.draw(Rectangle3);
	
	RectangleShape Rectangle4 (Vector2f (7, 7) );
	Rectangle4.setFillColor (Color::White);
	Rectangle4.setOutlineThickness(-1);
	Rectangle4.setOutlineColor(Color::Black);
	Rectangle4.setPosition(12,0);
	TankBlueprint.draw(Rectangle4);
	
	TankBlueprint.display();
	Decoration = TankBlueprint.getTexture();
}
