#pragma once

#include <map>
#include "Graphic\Sfml.h"
#include "Utils\Exception.h"

enum class EImage {
	NONE = 0,
	HOME_BACKGROUND,
	GAME_BACKGROUND,
	EMPTY_BACKGROUND,
	MENU_BACKGROUND,

	SOUND_ON, SOUND_OFF,
	BUTTON_MUSIC, BUTTON_MUSIC_FLASH,
	BUTTON_SINGLEGAME, BUTTON_SINGLEGAME_FLASH,
	BUTTON_HALLGAME, BUTTON_HALLGAME_FLASH,
	BUTTON_OPTION, BUTTON_OPTION_FLASH,
	BUTTON_PLAY, BUTTON_PLAY_FLASH,
	BUTTON_HOME, BUTTON_HOME_FLASH,
	BUTTON_DROP_DOWN, BUTTON_DROP_DOWN_FLASH,
	CHOICE_FIELD, CHOICE_FIELD_FLASH,
	CHOICE_ON, CHOICE_OFF,
	VERSUS, MENU_EMPTY, MENU_EMPTY2,
	BUTTON_EMPTY, BUTTON_EMPTY_ON, BUTTON_EMPTY_OFF,

	TURN_BLACK, TURN_WHITE,
	BUTTON_NEWGAME, BUTTON_NEWGAME_FLASH,
	BUTTON_UNDO, BUTTON_UNDO_FLASH,
	BUTTON_REDO, BUTTON_REDO_FLASH,
	BUTTON_ABOUT, BUTTON_ABOUT_FLASH,
	P_BLACK, P_BLACK_LUM,
	P_WHITE, P_WHITE_LUM,
	BUTTON_CLOSE, BUTTON_CLOSE_FLASH
};

enum class EFont {
	NINJA,
	KATANA
};

enum class EColor {
	BLACK,
	GREEN,
	RED
};

class ResourceManager
{
public:
	static void			createResources();
	static void			loadImage(EImage id, std::string path);
	static void			loadFont(EFont id, std::string path);
	static void			loadColor(EColor id, int r, int g, int b, int t);
	static sf::Texture&	getImage(EImage id);
	static sf::Font&	getFont(EFont id);
	static sf::Color&	getColor(EColor id);
private:
	static void			loadFonts();
	static void			loadColors();
	static void			loadImages();
	static void			createHomeImages();
	static void			createGameImages();

	static std::map<EImage, sf::Texture>	images;
	static std::map<EFont, sf::Font>		fonts;
	static std::map<EColor, sf::Color>		colors;
};
