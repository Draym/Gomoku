#include "Graphic\Screen\AWindow.h"

AWindow::AWindow(UserInterface *gui) : gui(gui)
{
}

AWindow::~AWindow()
{
}

void AWindow::reset()
{
}

void AWindow::update()
{
	this->gui->update();
}

void AWindow::render(sf::RenderWindow & screen)
{
	screen.draw(this->background);
	this->gui->render(screen);
}

void AWindow::event(sf::Event event)
{
	if (event.type == sf::Event::MouseButtonReleased) {
		this->gui->isSelected(event.mouseButton.x, event.mouseButton.y);
	}
	else if (event.type == sf::Event::MouseMoved) {
		this->gui->isOnFocus(event.mouseMove.x, event.mouseMove.y);
	}
	else {
		this->gui->event(event);
	}
}

UserInterface* AWindow::getUserInterface()
{
	return this->gui;
}