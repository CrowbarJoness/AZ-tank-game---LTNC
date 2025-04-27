void designTankBlueprint();
int initializeGloballyConstantEnvironment() {
	WindowWidth = 1300;
	WindowHeight = 650;
	
	WallThickness = 2;
	CellSize = 75;
	
	TankWidth = 31;
	TankHeight = 41;
	
	BulletRadius = 4.5;
	BulletExistanceCounterLimit = 50000;
	BulletNumberLimit = 3;
	
	srand( time(0) );
	
	MainWindow.create(VideoMode (WindowWidth, WindowHeight), "AZ", Style::Close);
	MainWindow.setPosition (Vector2i(30,30) );
	
	designTankBlueprint();
	
	TextFont.loadFromFile("arial.ttf");
	Sth.setFont(TextFont);
	
	MapBackground.loadFromFile("like.jpg");
	MenuBackground.loadFromFile("AZ menu background.jpg");
	
	InfoButton.loadFromFile("info.jpg");
	BackButton.loadFromFile("go back.jpg");
	HomeButton.loadFromFile("home button.jpg");
	
	ShootSoundBuffer.loadFromFile("Test shoot sound 2.wav");
	ShootSound.setBuffer(ShootSoundBuffer);
	
	WallCollisionSoundBuffer.loadFromFile("Wall collision sound 1.wav");
	WallCollisionSound.setBuffer(WallCollisionSoundBuffer);
	
	ExplosionSoundBuffer.loadFromFile("Explosion sound 1.wav");
	ExplosionSound.setBuffer(ExplosionSoundBuffer);
	
	SomeMusic.openFromFile("Some music.wav");
	SomeMusic.setVolume(10);
	SomeMusic.setLoop(1);
	SomeMusic.play();
	
	return 0;
}
int Initializer = initializeGloballyConstantEnvironment();
// This is an amazing trick to run code outside the main() function (mostly for initialization)

void clearVectors();
void getTanks();
void setupNewGame() {
	Map = getMap();
	MapWidth = Map.size();
	MapHeight = Map[0].size();
	
	HorizontalBorden = (WindowWidth - MapWidth * CellSize) / 2;
	VerticalBorden = (WindowHeight - MapHeight * CellSize) / 2;
	
	SpeedCoefficient = 0.06 + 0.0003*MapWidth*MapHeight; // Need to be tested many times
	// Changing speed to match with MapSize due to delay in drawing big map
	TankSpeed = SpeedCoefficient;
	BulletSpeed = SpeedCoefficient * 1.2;
	
	clearVectors();
	
	getTanks();
}
