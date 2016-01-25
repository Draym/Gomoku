#pragma once

#include <windows.h>
#include "Utils\Exception.h"

class WindowConfig
{
public:
	static void		init();
	static int		getWindowWidth();
	static int		getWindowHeight();
	static int		getWindowHomeWidth();
	static int		getWindowHomeHeight();
	static int		getWindowGameWidth();
	static int		getWindowGameHeight();
	static float	getGameBoardX();
	static float	getGameBoardY();
	static float	getGameBoardWidth();
	static float	getGameBoardHeight();
	static float	getBoxWidth();
	static float	getBoxHeight();
private:
	static int		windowWidth;
	static int		windowHeight;
	static int		windowHomeWidth;
	static int		windowHomeHeight;
	static int		windowGameWidth;
	static int		windowGameHeight;
	static float	gameBoardX;
	static float	gameBoardY;
	static float	gameBoardWidth;
	static float	gameBoardHeight;
	static float	boxWidth;
	static float	boxHeight;
};

