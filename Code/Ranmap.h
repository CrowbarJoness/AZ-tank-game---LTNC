const int rm = RAND_MAX;

int ran(int a, int b) {
	while(1) {
		int r = rand();
		if (r < rm-rm%(b+1-a)) return r%(b+1-a)+a;
	}
}

vector<vector<vector<bool>>> dir; // dir[i][j][k] = 1 if cell in col i row j has a wall in dir k
								  /*
								  						  0
								  						3 T 1
								  						  2
								  */
vector<vector<bool>> cell;
int x[4] = {0,1,0,-1}, y[4] = {-1,0,1,0};
int counter;

void dfs(int a, int b) { // float fill
	if(!cell[a][b]) {
		cell[a][b] = 1;
		counter++;
		f(k,4) if(!dir[a][b][k]) dfs(a+x[k],b+y[k]);
	}
}

vector<vector<vector<bool>>> getMap() {
	int m = ran(2,16), n = ran(2,8);
	vector<bool> useless1;
	vector<vector<bool>> useless2;
	useless1.assign(4,0);
	useless2.assign(n,useless1);
	dir.assign(m,useless2);
	useless1.resize(n,0);
	cell.assign(m,useless1);
	f(i,m) dir[i][0][0] = 1;
	f(i,m) dir[i][n-1][2] = 1;
	f(j,n) dir[0][j][3] = 1;
	f(j,n) dir[m-1][j][1] = 1;
	
	vector<vector<int>> Wall;
	/*
	Vetor Wall contains ... walls
	Each element is a set of (i,j,k) representing a wall
	i,j is the position
	k is the direction: k = 0 -> horizontal; k = 1 -> vertical
	In the while loop, randomly pick a wall (by index) -> check if it's valid or not -> delete it
	*/
	f(i,m-1) f(j,n) Wall.push_back({i,j,0});
	f(i,m) f(j,n-1) Wall.push_back({i,j,1});
	int q = ran(0, 2*(m+n));
	int c = Wall.size();
	f(k,q) {
		int p = ran(0,c-1);
		if (Wall[p][2]) {
			dir[Wall[p][0]][Wall[p][1]][2] = 1;
			dir[Wall[p][0]][Wall[p][1]+1][0] = 1;
		}
		else {
			dir[Wall[p][0]][Wall[p][1]][1] = 1;
			dir[Wall[p][0]+1][Wall[p][1]][3] = 1;
		}
		counter = 0;
		cell.assign(m,useless1);
		dfs(0,0);
		if (counter < m*n) {
			if(Wall[p][2]) {
				dir[Wall[p][0]][Wall[p][1]][2] = 0;
				dir[Wall[p][0]][Wall[p][1]+1][0] = 0;
			}
			else {
				dir[Wall[p][0]][Wall[p][1]][1] = 0;
				dir[Wall[p][0]+1][Wall[p][1]][3] = 0;
			}
		}
		Wall.erase(Wall.begin()+p);
		c--;
		if (c == 0) break;
	}
	return dir;
}
