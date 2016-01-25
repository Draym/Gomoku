#include "Graphic\ResourceManager.h"

std::map<EImage, sf::Texture>	ResourceManager::images;
std::map<EFont, sf::Font>		ResourceManager::fonts;
std::map<EColor, sf::Color>		ResourceManager::colors;

void	ResourceManager::createResources()
{
	loadFonts();
	loadImages();
	loadColors();
}

void	ResourceManager::loadImages()
{
	createHomeImages();
	createGameImages();
}

void	ResourceManager::loadFonts()
{
	loadFont(EFont::NINJA, "Resources/Fonts/lastninja.ttf");
	loadFont(EFont::KATANA, "Resources/Fonts/katana.ttf");
}

void	ResourceManager::loadColors()
{
	loadColor(EColor::BLACK, 0, 0, 0, 255);
	loadColor(EColor::GREEN, 0, 255, 0, 255);
	loadColor(EColor::RED, 255, 0, 0, 255);
}

void	ResourceManager::createHomeImages()
{
	loadImage(EImage::HOME_BACKGROUND, "Resources/Images/Home/background.png");
	loadImage(EImage::SOUND_ON, "Resources/Images/Home/soundOn.png");
	loadImage(EImage::SOUND_OFF, "Resources/Images/Home/soundOff.png");
	loadImage(EImage::BUTTON_MUSIC, "Resources/Images/Home/buttonMusic.png");
	loadImage(EImage::BUTTON_MUSIC_FLASH, "Resources/Images/Home/buttonMusicFlash.png");
	loadImage(EImage::BUTTON_SINGLEGAME, "Resources/Images/Home/buttonSingleGame.png");
	loadImage(EImage::BUTTON_SINGLEGAME_FLASH, "Resources/Images/Home/buttonSingleGameFlash.png");
	loadImage(EImage::BUTTON_HALLGAME, "Resources/Images/Home/buttonHallGame.png");
	loadImage(EImage::BUTTON_HALLGAME_FLASH, "Resources/Images/Home/buttonHallGameFlash.png");
	loadImage(EImage::BUTTON_OPTION, "Resources/Images/Home/buttonOption.png");
	loadImage(EImage::BUTTON_OPTION_FLASH, "Resources/Images/Home/buttonOptionFlash.png");
	loadImage(EImage::EMPTY_BACKGROUND, "Resources/Images/Home/emptyBackground.png");
	loadImage(EImage::CHOICE_ON, "Resources/Images/Home/choiceON.png");
	loadImage(EImage::CHOICE_OFF, "Resources/Images/Home/choiceOFF.png");
	loadImage(EImage::BUTTON_PLAY, "Resources/Images/Home/buttonPlay.png");
	loadImage(EImage::BUTTON_PLAY_FLASH, "Resources/Images/Home/buttonPlayFlash.png");
	loadImage(EImage::BUTTON_HOME, "Resources/Images/Home/buttonHome.png");
	loadImage(EImage::BUTTON_HOME_FLASH, "Resources/Images/Home/buttonHomeFlash.png");
	loadImage(EImage::BUTTON_EMPTY, "Resources/Images/Home/emptyButton.png");
	loadImage(EImage::BUTTON_EMPTY_ON, "Resources/Images/Home/emptyButtonON.png");
	loadImage(EImage::BUTTON_EMPTY_OFF, "Resources/Images/Home/emptyButtonOFF.png");
	loadImage(EImage::VERSUS, "Resources/Images/Home/versus.png");
	loadImage(EImage::MENU_EMPTY, "Resources/Images/Home/menuEmpty.png");
	loadImage(EImage::MENU_EMPTY2, "Resources/Images/Home/menuEmpty2.png");
	loadImage(EImage::BUTTON_CLOSE, "Resources/Images/Home/close.png");
	loadImage(EImage::BUTTON_CLOSE_FLASH, "Resources/Images/Home/closeFlash.png");
	loadImage(EImage::BUTTON_DROP_DOWN, "Resources/Images/Home/menuDown.png");
	loadImage(EImage::BUTTON_DROP_DOWN_FLASH, "Resources/Images/Home/menuDownFlash.png");
	loadImage(EImage::CHOICE_FIELD, "Resources/Images/Home/choiceField.png");
	loadImage(EImage::CHOICE_FIELD_FLASH, "Resources/Images/Home/choiceFieldFlash.png");
}

void	ResourceManager::createGameImages()
{
	loadImage(EImage::GAME_BACKGROUND, "Resources/Images/Game/background.png");
	loadImage(EImage::TURN_BLACK, "Resources/Images/Game/turnBlack.png");
	loadImage(EImage::TURN_WHITE, "Resources/Images/Game/turnWhite.png");
	loadImage(EImage::P_BLACK, "Resources/Images/Game/pBlack.png");
	loadImage(EImage::P_WHITE, "Resources/Images/Game/pWhite.png");
	loadImage(EImage::P_BLACK_LUM, "Resources/Images/Game/pBlackLum.png");
	loadImage(EImage::P_WHITE_LUM, "Resources/Images/Game/pWhiteLum.png");
	loadImage(EImage::BUTTON_NEWGAME, "Resources/Images/Game/newGame.png");
	loadImage(EImage::BUTTON_NEWGAME_FLASH, "Resources/Images/Game/newGameFlash.png");
	loadImage(EImage::BUTTON_UNDO, "Resources/Images/Game/undo.png");
	loadImage(EImage::BUTTON_UNDO_FLASH, "Resources/Images/Game/undoFlash.png");
	loadImage(EImage::BUTTON_REDO, "Resources/Images/Game/redo.png");
	loadImage(EImage::BUTTON_REDO_FLASH, "Resources/Images/Game/redoFlash.png");
	loadImage(EImage::BUTTON_ABOUT, "Resources/Images/Game/about.png");
	loadImage(EImage::BUTTON_ABOUT_FLASH, "Resources/Images/Game/aboutFlash.png");
}

void	ResourceManager::loadImage(EImage id, std::string path)
{
	if (images.find(id) == images.end()) {
		if (!images[id].loadFromFile(path))
			throw Exception("Error", "failed to load " + path, "ResourceManager::loadImage");
	}
}

void	ResourceManager::loadFont(EFont id, std::string path)
{
	if (fonts.find(id) == fonts.end()) {
		if (!fonts[id].loadFromFile(path))
			throw Exception("Error", "failed to load " + path, "ResourceManager::loadFont");
	}
}

void	ResourceManager::loadColor(EColor id, int r, int g, int b, int t)
{
	if (colors.find(id) == colors.end()) {
		colors[id] = sf::Color(r, g, b, t);
	}
}

sf::Texture&	ResourceManager::getImage(EImage id)
{
	if (images.find(id) != images.end()) {
		return images[id];
	}
	else {
		std::cout << "image: " << (int)id << std::endl;
		throw Exception("Error", "unknown image", "ResourceManager::getImage");
	}
}

sf::Font&	ResourceManager::getFont(EFont id)
{
	if (fonts.find(id) != fonts.end()) {
		return fonts[id];
	}
	else {
		throw Exception("Error", "unknown font", "ResourceManager::getFont");
	}
}

sf::Color&	ResourceManager::getColor(EColor id)
{
	if (colors.find(id) != colors.end()) {
		return colors[id];
	}
	else {
		throw Exception("Error", "unknown color", "ResourceManager::getColor");
	}
}