const float pi = 3.1415925;

float rad(float degree) {return degree*pi/180;}

float abso(float x) {return (x < 0) ? -x : x;}

float distance(float x1, float y1, float x2, float y2) { return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));}
float distance(float xP, float yP, float x1, float y1, float x2, float y2) {
	float a = y1-y2, b = x2-x1, c = x1*y2-x2*y1;
	return abso(a*xP+b*yP+c)/sqrt(a*a+b*b);
}

float vectorDirection(float x1, float y1, float x2, float y2) {
	float radAngle = acos((y1-y2)/distance(x1,y1,x2,y2));
	if (x1 > x2) radAngle*=-1;
	return radAngle*180/pi;
}

bool checkPoint(float x, float y) {
	x-=HorizontalBorden; y-=VerticalBorden;
	int xg = x/CellSize, yg = y/CellSize;
	if ((x < xg*CellSize + WallThickness && Map[xg][yg][3]) ||
		(x > (xg+1)*CellSize - WallThickness && Map[xg][yg][1]) ||
		(y < yg*CellSize + WallThickness && Map[xg][yg][0]) ||
		(y > (yg+1)*CellSize - WallThickness && Map[xg][yg][2]) )
		return 0;
	return 1;
}

bool checkEdge(float x1, float y1, float x2, float y2) {
	x1-=HorizontalBorden; y1-=VerticalBorden; x2-=HorizontalBorden; y2-=VerticalBorden;
	float a,b;
	if (x1 != x2) {
		a = (y1-y2)/(x1-x2); // Line equation d: y = a*x + b
		b = (x1*y2-x2*y1)/(x1-x2);
	}
	int x1g = x1/CellSize, x2g = x2/CellSize;
	if (x1g != x2g) {
		int xg = max(x1g,x2g);
		int yg1 = (a*(xg*CellSize-2)+b)/CellSize, yg2 = (a*(xg*CellSize+2)+b)/CellSize;
		// Check intersections between line d and line x = ... (Wall)
		if ((min(x1,x2) <= xg*CellSize-2 && max(x1,x2) >= xg*CellSize-2 && Map[xg-1][yg1][1]) ||
			(min(x1,x2) <= xg*CellSize+2 && max(x1,x2) >= xg*CellSize+2 && Map[xg][yg2][3]) ) return 0;
	}
	int y1g = y1/CellSize, y2g = y2/CellSize;                      
	if (y1g != y2g) {
		int yg = max(y1g,y2g);
		int xg1,xg2;
		if (x1 == x2) { xg1 = x1/CellSize; xg2 = x2/CellSize; }
		else { xg1 = (((yg*CellSize-2)-b)/a)/CellSize; xg2 = (((yg*CellSize+2)-b)/a)/CellSize; }
		// Check intersections between line d and line y = ... (Wall)
		if ((min(y1,y2) <= yg*CellSize-2 && max(y1,y2) >= yg*CellSize-2 && Map[xg1][yg-1][2]) ||
			(min(y1,y2) <= yg*CellSize+2 && max(y1,y2) >= yg*CellSize+2 && Map[xg2][yg][0]) ) return 0;
	}
	return 1;
}
