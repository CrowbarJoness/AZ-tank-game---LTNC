RenderWindow MainWindow; Event EventCatcher;

float WindowWidth, WindowHeight,
	  HorizontalBorden, VerticalBorden,
	  WallThickness, CellSize,
	  SpeedCoefficient,
	  TankWidth, TankHeight,
	  TankSpeed,
	  BulletRadius,
	  BulletSpeed;

int MapWidth, MapHeight,
	NumberOfTanks,
	BulletExistanceCounterLimit,
	BulletNumberLimit;

vector<vector<vector<bool>>> Map;

Texture Decoration, MapBackground, MenuBackground, InfoButton, BackButton, HomeButton;

vector<Vector2i> TanksStartCell;

SoundBuffer ShootSoundBuffer, WallCollisionSoundBuffer, ExplosionSoundBuffer;
Sound ShootSound, WallCollisionSound, ExplosionSound;
vector<Sound> ShootSounds, WallCollisionSounds, ExplosionSounds;
Music SomeMusic;

RenderTexture TextClipboard; Font TextFont; Text Sth; RectangleShape TextRect;

bool EndGame = 0; int MenuPage = 1;
