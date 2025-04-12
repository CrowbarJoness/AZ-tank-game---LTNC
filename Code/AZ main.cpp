#include"INCLUDES.h"

void handlingEvents() {
	while (MainWindow.pollEvent(EventCatcher)) {
		if (EventCatcher.type == Event::Closed) MainWindow.close();
		if (EventCatcher.type == Event::KeyPressed) if (EventCatcher.key.code == 36) MainWindow.close();
		if (EventCatcher.type == Event::MouseButtonPressed) if (EventCatcher.mouseButton.button == Mouse::Left) handlingMouseClick();
	}
}

int main() {
	while (MainWindow.isOpen()) {
		handlingEvents();
		drawing();
	}
}
