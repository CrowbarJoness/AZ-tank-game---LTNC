class KeySet {
public:
	int Left, Right, Up, Down, Shoot;
	KeySet(){}
	KeySet(int Left, int Right, int Up, int Down, int Shoot) {
		this->Left = Left;
		this->Right = Right;
		this->Up = Up;
		this->Down = Down;
		this->Shoot = Shoot;
	}
};

class Explosion {
private:
	CircleShape Body;
	int SmokeGreyColor = 0;
public:
	Explosion() {}
	Explosion(Vector2f Position) {
		Body.setRadius(TankHeight/2);
		Body.setOrigin(TankHeight/2, TankHeight/2);
		Body.setPosition(Position);
		Body.setFillColor(Color::Black);
	}
	CircleShape getBody() {return Body;}
	void increaseSmokeGreyColor() {
		SmokeGreyColor++;
		Body.setFillColor(Color(SmokeGreyColor,SmokeGreyColor,SmokeGreyColor));
	}
	int getSmokeGreyColor() {return SmokeGreyColor;}
};

vector<Explosion> Explosions;

class Bullet {
private:
	CircleShape Body;
	int ExistanceCounter = 0;
	bool SelfShield = 1;
public:
	Bullet() {}
	Bullet(Color FillColor, Vector2f Position, float Rotation) {
		Body.setRadius(BulletRadius);
		Body.setOrigin(BulletRadius, BulletRadius);
		Body.setPosition(Position);
		Body.setRotation(Rotation);
		Body.setFillColor(FillColor);
	}
	CircleShape getBody() {return Body;}
	
	void increaseExistanceCounter() {ExistanceCounter++;}
	int getExistanceCounter() {return ExistanceCounter;}
	
	bool getSelfShield() {return SelfShield;}
	
	void move() {
		Body.move(sin(rad(Body.getRotation()))*BulletSpeed,-cos(rad(Body.getRotation()))*BulletSpeed);
		float x = Body.getPosition().x - HorizontalBorden, y = Body.getPosition().y - VerticalBorden,
			  c = CellSize, w = WallThickness, r = Body.getRadius(), a = Body.getRotation();
		int xg = x/c, yg = y/c;
		if ( (x-r < xg*c + w && Map[xg][yg][3]) || (x+r > (xg+1)*c - w && Map[xg][yg][1]) ) {
	 		Body.setRotation(-a);
	 		SelfShield = 0;
	 	}
		else if ( (y-r < yg*c + w && Map[xg][yg][0]) || (y+r > (yg+1)*c - w && Map[xg][yg][2]) ) {
			Body.setRotation(180-a);
			SelfShield = 0;
		}
		else if ( (x < xg*c + w &&
				   ( (y-r < yg*c && Map[xg][yg-1][3]) ||
				     (y+r > (yg+1)*c && Map[xg][yg+1][3]) ) ) ||
				  (x > (xg+1)*c - w &&
				   ( (y-r < yg*c && Map[xg][yg-1][1]) ||
				     (y+r > (yg+1)*c && Map[xg][yg+1][1]) ) ) ) {
			Body.setRotation(180-a);
			SelfShield = 0;
		}
		else if ( (y < yg*c + w &&
				   ( (x-r < xg*c && Map[xg-1][yg][0]) ||
				     (x+r > (xg+1)*c && Map[xg+1][yg][0]) ) ) ||
				  (y > (yg+1)*c - w &&
				   ( (x-r < xg*c && Map[xg-1][yg][2]) ||
				     (x+r > (xg+1)*c && Map[xg+1][yg][2]) ) ) ) {
			Body.setRotation(-a);
			SelfShield = 0;
		}
		else {
			bool flag = 1;
			if (flag && x-r < xg*c + w) {
				if (distance(x,y,xg*c+w,yg*c) < r && (Map[xg][yg][3] || (yg > 0 && Map[xg][yg-1][3]))) {
					Body.setRotation( vectorDirection(xg*c+w,yg*c,x,y) );
					SelfShield = 0; flag = 0;
				}
				else if (distance(x,y,xg*c+w,(yg+1)*c) < r && (Map[xg][yg][3] || (yg < MapHeight-1 && Map[xg][yg+1][3]))) {
					Body.setRotation( vectorDirection(xg*c+w,(yg+1)*c,x,y) );
					SelfShield = 0; flag = 0;
				}
			}
			if (flag && x+r > (xg+1)*c - w) {
				if (distance(x,y,(xg+1)*c-w,yg*c) < r && (Map[xg][yg][1] || (yg > 0 && Map[xg][yg-1][1]))) {
					Body.setRotation( vectorDirection((xg+1)*c-w,yg*c,x,y) );
					SelfShield = 0; flag = 0;
				}
				else if (distance(x,y,(xg+1)*c-w,(yg+1)*c) < r && (Map[xg][yg][1] || (yg < MapHeight-1 && Map[xg][yg+1][1]))) {
					Body.setRotation( vectorDirection((xg+1)*c-w,(yg+1)*c,x,y) );
					SelfShield = 0; flag = 0;
				}
			}
			if (flag && y-r < yg*c + w) {
				if (distance(x,y,xg*c,yg*c+w) < r && (Map[xg][yg][0] || (xg > 0 && Map[xg-1][yg][0]))) {
					Body.setRotation( vectorDirection(xg*c,yg*c+w,x,y) ); flag = 0;
				}
				else if (distance(x,y,(xg+1)*c,yg*c+w) < r && (Map[xg][yg][0] || (xg < MapWidth-1 && Map[xg+1][yg][0]))) {
					Body.setRotation( vectorDirection((xg+1)*c,yg*c+w,x,y) );
					SelfShield = 0; flag = 0;
				}
			}
			if (flag && y+r > (yg+1)*c - w) {
				if (distance(x,y,xg*c,(yg+1)*c-w) < r && (Map[xg][yg][2] || (xg > 0 && Map[xg-1][yg][2]))) {
					Body.setRotation( vectorDirection(xg*c,(yg+1)*c-w,x,y) );
					SelfShield = 0; flag = 0;
				}
				else if (distance(x,y,(xg+1)*c,(yg+1)*c-w) < r && (Map[xg][yg][2] || (xg < MapWidth-1 && Map[xg+1][yg][2]))) {
					Body.setRotation( vectorDirection((xg+1)*c,(yg+1)*c-w,x,y) );
					SelfShield = 0; flag = 0;
				}
			}
		}
		if (Body.getRotation() != a) {
			WallCollisionSounds.push_back(WallCollisionSound);
			WallCollisionSounds[WallCollisionSounds.size()-1].play();
		}
	}
};

vector<Bullet> StrayBullets; // Contains bullets of dead tanks

class Tank {
private:
	RectangleShape Body;
	KeySet Keys;
	float beta, delta;
	vector<Bullet> Bullets;
	bool checkShooted = 0;
public:
	Tank() {}
	Tank (Color FillColor, Vector2i StartCell, KeySet Keys) {
		Body.setSize(Vector2f(TankWidth, TankHeight));
		Body.setOrigin(TankWidth/2, TankHeight/2);
		Body.setPosition(StartCell.x * CellSize + CellSize / 2 + HorizontalBorden,
		                 StartCell.y * CellSize + CellSize / 2 + VerticalBorden);
		Body.setRotation(ran(0, 359));
		Body.setFillColor(FillColor);
		Body.setOutlineThickness(-1);
		Body.setOutlineColor(Color::Black);
		Body.setTexture(&Decoration);
		Body.setTextureRect(IntRect(0,0,TankWidth,TankHeight));
		
		beta = atan(TankWidth/TankHeight);
		delta = sqrt(TankWidth * TankWidth + TankHeight * TankHeight) / 2;
		
		this->Keys = Keys;
		
	}
	RectangleShape getBody() {return Body;}
	
	KeySet getKeys() {return Keys;}
	
	vector<Bullet> getBullets() {return Bullets;}
	void setBullets(vector<Bullet> Bullets) {this->Bullets = Bullets;}
	
	float alpha() {return Body.getRotation();}
	float xO() {return Body.getPosition().x;}
	float yO() {return Body.getPosition().y;}
	float xA() {return xO()+delta*sin(rad(alpha())-beta);}
	float yA() {return yO()-delta*cos(rad(alpha())-beta);}
	float xB() {return xO()+delta*sin(rad(alpha())+beta);}
	float yB() {return yO()-delta*cos(rad(alpha())+beta);}
	float xC() {return xO()+delta*sin(rad(alpha())+pi-beta);}
	float yC() {return yO()-delta*cos(rad(alpha())+pi-beta);}
	float xD() {return xO()+delta*sin(rad(alpha())+pi+beta);}
	float yD() {return yO()-delta*cos(rad(alpha())+pi+beta);}
	
	bool checkAll() {
		if ((!checkPoint(xA(),yA())) ||
			(!checkPoint(xB(),yB())) ||
			(!checkPoint(xC(),yC())) ||
			(!checkPoint(xD(),yD())) ||
			(!checkEdge(xA(),yA(),xB(),yB())) ||
			(!checkEdge(xB(),yB(),xC(),yC())) ||
			(!checkEdge(xC(),yC(),xD(),yD())) ||
			(!checkEdge(xD(),yD(),xA(),yA())) )
			return 0;
		return 1;
	}
	
	void shoot() {
		if (Bullets.size() < BulletNumberLimit && !EndGame) {
			Bullets.push_back(Bullet(Body.getFillColor(),
							  Vector2f( Body.getPosition().x + (TankHeight/2 - BulletRadius) * sin( rad(Body.getRotation()) ),
									    Body.getPosition().y - (TankHeight/2 - BulletRadius) * cos( rad(Body.getRotation()) ) ),
							  Body.getRotation()));
			ShootSounds.push_back(ShootSound);
			ShootSounds[ShootSounds.size()-1].play();
		}
	}
	
	void move() {
		Vector2f Position = Body.getPosition();
		float Rotation = Body.getRotation();
		bool flag = 0;
		if (Keyboard::isKeyPressed(Keyboard::Key(Keys.Left))) {
			Body.rotate(-SpeedCoefficient);
			flag = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key(Keys.Right))) {
			Body.rotate(SpeedCoefficient);
			flag = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key(Keys.Up))) {
			Body.move(sin(rad(Body.getRotation()))*TankSpeed,-cos(rad(Body.getRotation()))*TankSpeed);
			flag = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::Key(Keys.Down))) {
			Body.move(-sin(rad(Body.getRotation()))*TankSpeed,cos(rad(Body.getRotation()))*TankSpeed);
			flag = 1;
		}
		if (!checkAll()) {
			Body.setPosition(Position);
			Body.setRotation(Rotation);
		}
		if (Keyboard::isKeyPressed(Keyboard::Key(Keys.Shoot))) {
			if (!checkShooted) {
				shoot();
				checkShooted = 1;
			}
		}
		else checkShooted = 0;
	}
	
	bool checkBeingShooted(Bullet K) {
		float x = K.getBody().getPosition().x, y = K.getBody().getPosition().y, r = K.getBody().getRadius();
		if (((distance(x,y,xA(),yA(),xB(),yB()) < r || distance(x,y,xC(),yC(),xD(),yD()) < r) &&
			 distance(x,y,xA(),yA(),xD(),yD()) <= TankWidth && distance(x,y,xB(),yB(),xC(),yC()) <= TankWidth) ||
			((distance(x,y,xA(),yA(),xD(),yD()) < r || distance(x,y,xB(),yB(),xC(),yC()) < r) &&
			 distance(x,y,xA(),yA(),xB(),yB()) <= TankHeight && distance(x,y,xC(),yC(),xD(),yD()) <= TankHeight) ||
			(distance(x,y,xA(),yA()) < r || distance(x,y,xB(),yB()) < r || distance(x,y,xC(),yC()) < r || distance(x,y,xD(),yD()) < r) ) 
			return 1;
		return 0;
	}
	
	void explode() {
		Explosions.push_back(Explosion(Body.getPosition()));
		f(i,Bullets.size()) StrayBullets.push_back(Bullets[i]);
		ExplosionSounds.push_back(ExplosionSound);
		ExplosionSounds[ExplosionSounds.size()-1].play();
	}
};

vector<Tank> Tanks;

void clearVectors() {
	Tanks.clear();
	TanksStartCell.clear();
	StrayBullets.clear();
	Explosions.clear();
	ShootSounds.clear();
	WallCollisionSounds.clear();
	ExplosionSounds.clear();
}

void getTanksStartCell() {
	set<pair<int,int>> Useless2;
	while (Useless2.size() < NumberOfTanks)
		Useless2.insert(pair<int,int>({ran(0, MapWidth-1), ran(0, MapHeight-1)}));
	//Using set prevent tanks from sponding at the same cell
	all(Useless2) TanksStartCell.push_back(Vector2i(sth.first, sth.second));
}

void getTanks() {
	getTanksStartCell();
	if (NumberOfTanks == 2) {
		Tanks.push_back(Tank(Color(0,255,0), TanksStartCell[0], KeySet(71,72,73,74,63)));// Arrows, End
		Tanks.push_back(Tank(Color(255,0,0), TanksStartCell[1], KeySet(0,3,22,18,4)));// ADWSE
	}
	else if (NumberOfTanks == 3) {
		Tanks.push_back(Tank(Color(0,255,0), TanksStartCell[0], KeySet(71,72,73,74,63)));
		Tanks.push_back(Tank(Color(255,0,0), TanksStartCell[1], KeySet(0,3,22,18,4)));
		Tanks.push_back(Tank(Color(0,0,255), TanksStartCell[2], KeySet(7,10,20,9,8)));// HKUJI
	}
	else if (NumberOfTanks == 4) {
		Tanks.push_back(Tank(Color(0,255,0), TanksStartCell[0], KeySet(71,72,73,74,63)));
		Tanks.push_back(Tank(Color(255,0,0), TanksStartCell[1], KeySet(0,3,22,18,4)));
		Tanks.push_back(Tank(Color(0,0,255), TanksStartCell[2], KeySet(5,7,19,6,24)));// FHTGY
		Tanks.push_back(Tank(Color(255,255,0), TanksStartCell[3], KeySet(9,11,8,10,14)));// JLIKO
	}
}
