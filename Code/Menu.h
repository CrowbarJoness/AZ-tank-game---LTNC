void handlingMouseClick() {
	if (MenuPage == 0) {
		if (EventCatcher.mouseButton.x >= 10 &&
			EventCatcher.mouseButton.x < 10+30 &&
			EventCatcher.mouseButton.y >= 10 &&
			EventCatcher.mouseButton.y < 10+30) MenuPage = 1;
	}
	else if (MenuPage == 1) {
		if (EventCatcher.mouseButton.x >= 100 &&
			EventCatcher.mouseButton.x < 100+300 &&
			EventCatcher.mouseButton.y >= 400 &&
			EventCatcher.mouseButton.y < 400+100) MenuPage = 2;
		if (EventCatcher.mouseButton.x >= 500 &&
			EventCatcher.mouseButton.x < 500+300 &&
			EventCatcher.mouseButton.y >= 400 &&
			EventCatcher.mouseButton.y < 400+100) MenuPage = 3;
		if (EventCatcher.mouseButton.x >= 900 &&
			EventCatcher.mouseButton.x < 900+300 &&
			EventCatcher.mouseButton.y >= 400 &&
			EventCatcher.mouseButton.y < 400+100) MenuPage = 4;
		if (EventCatcher.mouseButton.x >= 1300-20-50 &&
			EventCatcher.mouseButton.x < 1300-20 &&
			EventCatcher.mouseButton.y >= 20 &&
			EventCatcher.mouseButton.y < 20+50) MenuPage = 5;
	}
	else {
		if (MenuPage != 5 &&
			EventCatcher.mouseButton.x >= 1300-20-120 &&
			EventCatcher.mouseButton.x < 1300-20 &&
			EventCatcher.mouseButton.y >= 650-20-100 &&
			EventCatcher.mouseButton.y < 650-20) {
			NumberOfTanks = MenuPage;
			MenuPage = 0;
			setupNewGame();
		}
		if (EventCatcher.mouseButton.x >= 20 &&
			EventCatcher.mouseButton.x < 20+320 &&
			EventCatcher.mouseButton.y >= 650-20-100 &&
			EventCatcher.mouseButton.y < 650-20) MenuPage = 1;
	}
}

void drawMenu() {
	RectangleShape MenuBackgroundRect( Vector2f(WindowWidth,WindowHeight) );
	MenuBackgroundRect.setTexture(&MenuBackground);
	MainWindow.draw(MenuBackgroundRect);
	
	Sth.setString("The AZ Tank Game");
	Sth.setCharacterSize(100);
	Sth.setPosition(200,0);
	Sth.setFillColor(Color(255,165,0)); //Orange
	Sth.setOutlineThickness(2);
	Sth.setOutlineColor(Color(165,42,42)); //Brown
	MainWindow.draw(Sth);
	
	Sth.setString("or something like that...");
	Sth.setStyle(Text::Italic);
	Sth.setCharacterSize(30);
	Sth.setPosition(500,120);
	Sth.setFillColor(Color(70,130,180)); //A blue color
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	RectangleShape Button( Vector2f(300,100) );
	
	Button.setPosition(100,400);
	Button.setFillColor(Color(255,0,0));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(128,0,0));
	MainWindow.draw(Button);
	Sth.setString("2P");
	Sth.setStyle(Text::Bold);
	Sth.setCharacterSize(80);
	Sth.setPosition(200,400);
	Sth.setFillColor(Color(0,255,255));
	Sth.setOutlineThickness(2);
	Sth.setOutlineColor(Color(0,0,0));
	MainWindow.draw(Sth);
	
	Button.setPosition(500,400);
	Button.setFillColor(Color(0,255,0));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,128,0));
	MainWindow.draw(Button);
	Sth.setString("3P");
	Sth.setStyle(Text::Bold);
	Sth.setCharacterSize(80);
	Sth.setPosition(600,400);
	Sth.setFillColor(Color(255,0,255));
	Sth.setOutlineThickness(2);
	Sth.setOutlineColor(Color(0,0,0));
	MainWindow.draw(Sth);
	
	Button.setPosition(900,400);
	Button.setFillColor(Color(0,0,255));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,128));
	MainWindow.draw(Button);
	Sth.setString("4P");
	Sth.setStyle(Text::Bold);
	Sth.setCharacterSize(80);
	Sth.setPosition(1000,400);
	Sth.setFillColor(Color(255,255,0));
	Sth.setOutlineThickness(2);
	Sth.setOutlineColor(Color(0,0,0));
	MainWindow.draw(Sth);
	
	Button.setSize(Vector2f(50,50));
	Button.setPosition(1300-20-50,20);
	Button.setFillColor(Color(255,255,255));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,0));
	Button.setTexture(&InfoButton);
	MainWindow.draw(Button);
	
	MainWindow.display();
}

void drawPage2() {
	RectangleShape MenuBackgroundRect( Vector2f(WindowWidth,WindowHeight) );
	MenuBackgroundRect.setTexture(&MenuBackground);
	MainWindow.draw(MenuBackgroundRect);
	
	RectangleShape TankRect( Vector2f(TankWidth,TankHeight) );
	
	TankRect.setPosition(100,100);
	TankRect.setFillColor(Color(0,255,0));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: Arrows");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,100);
	Sth.setFillColor(Color(0,255,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: End");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,100);
	Sth.setFillColor(Color(0,255,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	TankRect.setPosition(100,200);
	TankRect.setFillColor(Color(255,0,0));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: ADWS");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,200);
	Sth.setFillColor(Color(255,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: E");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,200);
	Sth.setFillColor(Color(255,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	RectangleShape Button( Vector2f(120,100) );
	Button.setPosition(1300-20-120,650-20-100);
	Button.setFillColor(Color(128,128,0));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,0));
	MainWindow.draw(Button);
	Sth.setString("OK");
	Sth.setStyle(Text::Bold);
	Sth.setCharacterSize(80);
	Sth.setPosition(1300-20-120,650-20-100);
	Sth.setFillColor(Color(0,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	Button.setSize( Vector2f(320,100) );
	Button.setPosition(20,650-20-100);
	Button.setFillColor(Color(255,255,255));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,0));
	Button.setTexture(&BackButton);
	MainWindow.draw(Button);
	
	MainWindow.display();
}

void drawPage3() {
	RectangleShape MenuBackgroundRect( Vector2f(WindowWidth,WindowHeight) );
	MenuBackgroundRect.setTexture(&MenuBackground);
	MainWindow.draw(MenuBackgroundRect);
	
	RectangleShape TankRect( Vector2f(TankWidth,TankHeight) );
	
	TankRect.setPosition(100,100);
	TankRect.setFillColor(Color(0,255,0));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: Arrows");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,100);
	Sth.setFillColor(Color(0,255,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: End");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,100);
	Sth.setFillColor(Color(0,255,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	TankRect.setPosition(100,200);
	TankRect.setFillColor(Color(255,0,0));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: ADWS");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,200);
	Sth.setFillColor(Color(255,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: E");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,200);
	Sth.setFillColor(Color(255,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	TankRect.setPosition(100,300);
	TankRect.setFillColor(Color(0,0,255));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: HKUJ");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,300);
	Sth.setFillColor(Color(0,0,255));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: I");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,300);
	Sth.setFillColor(Color(0,0,255));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	RectangleShape Button( Vector2f(120,100) );
	Button.setPosition(1300-20-120,650-20-100);
	Button.setFillColor(Color(128,128,0));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,0));
	MainWindow.draw(Button);
	Sth.setString("OK");
	Sth.setStyle(Text::Bold);
	Sth.setCharacterSize(80);
	Sth.setPosition(1300-20-120,650-20-100);
	Sth.setFillColor(Color(0,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	Button.setSize( Vector2f(320,100) );
	Button.setPosition(20,650-20-100);
	Button.setFillColor(Color(255,255,255));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,0));
	Button.setTexture(&BackButton);
	MainWindow.draw(Button);
	
	MainWindow.display();
}

void drawPage4() {
	RectangleShape MenuBackgroundRect( Vector2f(WindowWidth,WindowHeight) );
	MenuBackgroundRect.setTexture(&MenuBackground);
	MainWindow.draw(MenuBackgroundRect);
	
	RectangleShape TankRect( Vector2f(TankWidth,TankHeight) );
	
	TankRect.setPosition(100,100);
	TankRect.setFillColor(Color(0,255,0));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: Arrows");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,100);
	Sth.setFillColor(Color(0,255,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: End");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,100);
	Sth.setFillColor(Color(0,255,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	TankRect.setPosition(100,200);
	TankRect.setFillColor(Color(255,0,0));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: ADWS");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,200);
	Sth.setFillColor(Color(255,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: E");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,200);
	Sth.setFillColor(Color(255,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	TankRect.setPosition(100,300);
	TankRect.setFillColor(Color(0,0,255));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: FHTG");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,300);
	Sth.setFillColor(Color(0,0,255));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: Y");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,300);
	Sth.setFillColor(Color(0,0,255));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	TankRect.setPosition(100,400);
	TankRect.setFillColor(Color(255,255,0));
	TankRect.setOutlineThickness(-1);
	TankRect.setOutlineColor(Color(0,0,0));
	TankRect.setTexture(&Decoration);
	TankRect.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
	MainWindow.draw(TankRect);
	Sth.setString("Move: JLIK");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+100,400);
	Sth.setFillColor(Color(255,255,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("Shoot: O");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(TankHeight);
	Sth.setPosition(100+400,400);
	Sth.setFillColor(Color(255,255,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	RectangleShape Button( Vector2f(120,100) );
	Button.setPosition(1300-20-120,650-20-100);
	Button.setFillColor(Color(128,128,0));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,0));
	MainWindow.draw(Button);
	Sth.setString("OK");
	Sth.setStyle(Text::Bold);
	Sth.setCharacterSize(80);
	Sth.setPosition(1300-20-120,650-20-100);
	Sth.setFillColor(Color(0,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	Button.setSize( Vector2f(320,100) );
	Button.setPosition(20,650-20-100);
	Button.setFillColor(Color(255,255,255));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,0));
	Button.setTexture(&BackButton);
	MainWindow.draw(Button);
	
	Sth.setString("*Using two keyboards is highly suggested for 4P mode.");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(30);
	Sth.setPosition(100,30);
	Sth.setFillColor(Color(47,79,79));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	MainWindow.display();
}

void drawInfo() {
	RectangleShape MenuBackgroundRect( Vector2f(WindowWidth,WindowHeight) );
	MenuBackgroundRect.setTexture(&MenuBackground);
	MainWindow.draw(MenuBackgroundRect);
	
	RectangleShape Button( Vector2f(320,100) );
	Button.setPosition(20,650-20-100);
	Button.setFillColor(Color(255,255,255));
	Button.setOutlineThickness(-2);
	Button.setOutlineColor(Color(0,0,0));
	Button.setTexture(&BackButton);
	MainWindow.draw(Button);
	
	Sth.setString("\nThis is a stupid version of AZ tank trouble, the legendary game being extremely famous\nfor a while on the Y8 online game platform.\n\n... I don't think it's necessary to explain how to play the game, it's just too simple.\n\nDeveloper: Crowbar Jones\nEmail: crowbarjones30102006@gmail.com\n\nI sincerely apologize for using images without cited sources :).\nMeanwhile, I have created all the sounds, except the music of course.");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(30);
	Sth.setPosition(0,0);
	Sth.setFillColor(Color(255,215,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("OBVIOUSLY, THERE IS STILL A LOT TO DO WITH THIS GAME.");
	Sth.setStyle(Text::Bold | Text::Underlined);
	Sth.setCharacterSize(40);
	Sth.setPosition(0,400);
	Sth.setFillColor(Color(255,0,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	Sth.setString("I'll update more features in the near future.");
	Sth.setStyle(Text::Regular);
	Sth.setCharacterSize(30);
	Sth.setPosition(0,450);
	Sth.setFillColor(Color(255,215,0));
	Sth.setOutlineThickness(0);
	MainWindow.draw(Sth);
	
	MainWindow.display();
}

void menu() {
	if (MenuPage == 1) drawMenu();
	else if (MenuPage == 2) drawPage2();
	else if (MenuPage == 3) drawPage3();
	else if (MenuPage == 4) drawPage4();
	else if (MenuPage == 5) drawInfo();
}
