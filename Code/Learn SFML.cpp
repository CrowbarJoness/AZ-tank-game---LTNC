#include <cstdlib> // srand()
#include <ctime>
#include "Application.h"

int main() {
	srand(time(0));
	
	Application application;
	application.run();
	
	return 0;
}
