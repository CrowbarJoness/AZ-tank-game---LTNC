void explode() {
	f(i,Explosions.size()) {
		if (Explosions[i].getSmokeGreyColor() > 200) {
			Explosions.erase(Explosions.begin()+i);
			break;
		}
		else {
			MainWindow.draw(Explosions[i].getBody());
			Explosions[i].increaseSmokeGreyColor();
		}
	}
}

void handlingBullets() {
	bool flag = 0;
	f(i,Tanks.size()) {
		vector<Bullet> Bullets = Tanks[i].getBullets();
		f(j,Bullets.size()) {
			f(k,Tanks.size()) {
				if (Tanks[k].checkBeingShooted(Bullets[j])) {
					if (k != i || (k == i && Bullets[j].getSelfShield() == 0)) {
						Bullets.erase(Bullets.begin()+j);
						Tanks[i].setBullets(Bullets);
						Tanks[k].explode();
						Tanks.erase(Tanks.begin()+k);
						flag = 1; break;
					}
				}
			}
			if (flag) break;
			if (Bullets[j].getExistanceCounter() > BulletExistanceCounterLimit) {
				Bullets.erase(Bullets.begin()+j);
				break;
			}
			Bullets[j].move();
			Bullets[j].increaseExistanceCounter();
		}
		if (flag) break;
		Tanks[i].setBullets(Bullets);
	}
	
	flag = 0;
	f(j,StrayBullets.size()) {
		f(k,Tanks.size()) {
			if (Tanks[k].checkBeingShooted(StrayBullets[j])) {
				StrayBullets.erase(StrayBullets.begin()+j);
				Tanks[k].explode();
				Tanks.erase(Tanks.begin()+k);
				flag = 1; break;
			}
		}
		if (flag) break;
		StrayBullets[j].move();
		StrayBullets[j].increaseExistanceCounter();
	}
	//Break commands here assumes that no two bullets disappear at exactly the same moment
}

bool LastMoment = 0;
int CountSecond;

void checkEndGame() {
	if (Tanks.size() <= 1 && (!LastMoment)) {
		CountSecond = time(0);
		LastMoment = 1;
	}
	if (LastMoment) {
		if (time(0) - CountSecond > 4) {
			LastMoment = 0;
			EndGame = 0;
			setupNewGame();
		}
		else if (time(0) - CountSecond > 3) {
			cout << "";
			EndGame = 1;
		}
	}
}

void drawing() {
	MainWindow.clear(Color::White);
	menu(); if (MenuPage) return; // MenuPage = 0 means we're actually playing
	checkEndGame();
	drawMap();
	f(i,Tanks.size()) Tanks[i].move();
	f(i,Tanks.size()) MainWindow.draw(Tanks[i].getBody());
	handlingBullets();
	f(i,Tanks.size()) f(j,Tanks[i].getBullets().size()) MainWindow.draw(Tanks[i].getBullets()[j].getBody());
	f(i,StrayBullets.size()) MainWindow.draw(StrayBullets[i].getBody());
	explode();
	MainWindow.display();
}
