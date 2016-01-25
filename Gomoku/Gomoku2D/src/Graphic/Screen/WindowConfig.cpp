#include "Graphic\Screen\WindowConfig.h"

int	WindowConfig::windowWidth = 1920;
int	WindowConfig::windowHeight = 1080;
int	WindowConfig::windowHomeWidth = 893;
int	WindowConfig::windowHomeHeight = 558;
int	WindowConfig::windowGameWidth = 1152;
int	WindowConfig::windowGameHeight = 930;

float WindowConfig::gameBoardX = 151.0;
float WindowConfig::gameBoardY = 54.0;
float WindowConfig::gameBoardWidth = 849.0;
float WindowConfig::gameBoardHeight = 849.0;
float WindowConfig::boxWidth = 47.0f;
float WindowConfig::boxHeight = 47.0f;

void WindowConfig::init()
{
	windowWidth = GetSystemMetrics(SM_CXSCREEN);
	windowHeight = GetSystemMetrics(SM_CYSCREEN);
}

int WindowConfig::getWindowWidth()
{
	return windowWidth;
}

int WindowConfig::getWindowHeight()
{
	return windowHeight;
}

int WindowConfig::getWindowHomeWidth()
{
	return windowHomeWidth;
}

int WindowConfig::getWindowHomeHeight()
{
	return windowHomeHeight;
}

int WindowConfig::getWindowGameWidth()
{
	return windowGameWidth;
}

int WindowConfig::getWindowGameHeight()
{
	return windowGameHeight;
}

float WindowConfig::getGameBoardX()
{
	return gameBoardX;
}

float WindowConfig::getGameBoardY()
{
	return gameBoardY;
}

float WindowConfig::getGameBoardWidth()
{
	return gameBoardWidth;
}

float WindowConfig::getGameBoardHeight()
{
	return gameBoardHeight;
}

float WindowConfig::getBoxWidth()
{
	return boxWidth;
}

float WindowConfig::getBoxHeight()
{
	return boxHeight;
}
