#include "Graphic\Interface\GameGUI.h"


GameGUI::GameGUI()
{
	this->local = ELocation::GAME_GUI;
}


GameGUI::~GameGUI()
{
}

void	GameGUI::init()
{
	this->elements.clear();
	this->elements.push_back(new Button(1018, 59, 128, 34, ELocation::GAME_GUI, ELocation::MASTER, ETask::SWITCH_SCREEN, "HOME", EImage::BUTTON_NEWGAME, EImage::BUTTON_NEWGAME_FLASH));
	this->elements.push_back(new Button(1018, 99, 128, 34, ELocation::GAME_GUI, ELocation::GAME, ETask::UNDO_ACTION, "", EImage::BUTTON_UNDO, EImage::BUTTON_UNDO_FLASH));
	this->elements.push_back(new Button(1018, 139, 128, 34, ELocation::GAME_GUI, ELocation::GAME, ETask::REDO_ACTION, "", EImage::BUTTON_REDO, EImage::BUTTON_REDO_FLASH));
	this->elements.push_back(new Button(1018, 861, 128, 35, ELocation::GAME_GUI, ELocation::GAME, ETask::ACTIVE_GUI_ELEM, "menuAbout:reverse", EImage::BUTTON_ABOUT, EImage::BUTTON_ABOUT_FLASH));
	this->elements.push_back(new Button(30, 680, 70, 72, ELocation::GAME_GUI, ELocation::MASTER, ETask::SWITCH_MUSIC, "", EImage::BUTTON_MUSIC, EImage::BUTTON_MUSIC_FLASH));
	this->elements.push_back(new ButtonState("buttonMusicGame", 30, 770, 70, 72, ELocation::GAME_GUI, ELocation::MASTER, ETask::ACTIVE_MUSIC, "", EImage::SOUND_ON, EImage::SOUND_OFF));

	ComplexElement *menuEndGame = new ComplexElement("menuEndGame", 500, 300, 0, 0, false);
	menuEndGame->addItem(new PrintableElement(0, 0, 280, 330, EImage::MENU_EMPTY));
	menuEndGame->addItem(new PrintableElement(50, 123, "End of the game !", 22, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuEndGame->addItem(new PrintableElement("GamePlayerName1", 40, 190, "", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuEndGame->addItem(new PrintableElement("GamePlayerName2", 40, 250, "", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuEndGame->addItem(new PrintableElement("GamePlayerResult1", 160, 185, "", 20, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuEndGame->addItem(new PrintableElement("GamePlayerResult2", 160, 245, "", 20, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuEndGame->addItem(new Button(245, 4, 31, 24, ELocation::GAME_GUI, ELocation::GAME, ETask::ACTIVE_GUI_ELEM, "menuEndGame:false", EImage::BUTTON_CLOSE, EImage::BUTTON_CLOSE_FLASH));
	this->elements.push_back(menuEndGame);

	ComplexElement *menuAbout = new ComplexElement("menuAbout", 130, 200, 893, 558, false);
	menuAbout->addItem(new PrintableElement(0, 0, 893, 558, EImage::EMPTY_BACKGROUND));
	menuAbout->addItem(new PrintableElement(80, 180, "How to play: ", 20, ResourceManager::getColor(EColor::BLACK), EFont::NINJA));
	menuAbout->addItem(new PrintableElement(50, 220, "Each player has an unlimited number of stone of his color.", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(50, 240, "Players can put 1 stone on a free case each turn.", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(50, 270, "How to win: ", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(80, 290, "- achieve an alignment of 5 stones", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(80, 310, "- take 10 stones to the opponent", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(50, 340, "The alignements can be vertical, horizontal or diagonal.", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(50, 360, "Catches are always done by framing a pair of opposing stone.", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));

	menuAbout->addItem(new PrintableElement(30, 500, "Make by: ", 20, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(120, 503, "Draym /=andres_k=\\", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));

	menuAbout->addItem(new PrintableElement(640, 180, "Help: ", 20, ResourceManager::getColor(EColor::BLACK), EFont::NINJA));
	menuAbout->addItem(new PrintableElement(610, 220, "Pause: ", 20, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(610, 240, "Change players: ", 20, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(610, 260, "Change options: ", 20, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(680, 220, "F1 / F2", 20, ResourceManager::getColor(EColor::RED), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(770, 240, "Pause + F1", 20, ResourceManager::getColor(EColor::RED), EFont::KATANA));
	menuAbout->addItem(new PrintableElement(760, 260, "Pause + F2", 20, ResourceManager::getColor(EColor::RED), EFont::KATANA));

	this->elements.push_back(menuAbout);

	ComplexElement *menuSelect = new ComplexElement("menuSelect", 130, 200, 893, 558, false);
	menuSelect->addItem(new PrintableElement(0, 0, 893, 558, EImage::EMPTY_BACKGROUND));
	menuSelect->addItem(new ButtonState("buttonP1", 115, 250, 150, 49, ELocation::GAME_GUI, ELocation::GAME, ETask::CHANGE_PLAYER, "P1:true:buttonP1:true:buttonA1:false:A1DownMenu:false", EImage::BUTTON_EMPTY_ON, EImage::BUTTON_EMPTY_OFF));
	menuSelect->addItem(new ButtonState("buttonA1", 115, 320, 150, 49, ELocation::GAME_GUI, ELocation::GAME, ETask::CHANGE_PLAYER, "P1:false:buttonP1:false:buttonA1:true:A1DownMenu:true", EImage::BUTTON_EMPTY_ON, EImage::BUTTON_EMPTY_OFF, false));
	menuSelect->addItem(new ButtonState("buttonP2", 580, 320, 150, 49, ELocation::GAME_GUI, ELocation::GAME, ETask::CHANGE_PLAYER, "P2:true:buttonP2:true:buttonA2:false:A2DownMenu:false", EImage::BUTTON_EMPTY_ON, EImage::BUTTON_EMPTY_OFF));
	menuSelect->addItem(new ButtonState("buttonA2", 580, 250, 150, 49, ELocation::GAME_GUI, ELocation::GAME, ETask::CHANGE_PLAYER, "P2:false:buttonP2:false:buttonA2:true:A2DownMenu:true", EImage::BUTTON_EMPTY_ON, EImage::BUTTON_EMPTY_OFF, false));
	menuSelect->addItem(new PrintableElement(350, 240, 150, 143, EImage::VERSUS));
	menuSelect->addItem(new PrintableElement(135, 265, "Player", 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuSelect->addItem(new PrintableElement(135, 335, "Ordinateur", 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuSelect->addItem(new PrintableElement(600, 265, "Ordinateur", 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	menuSelect->addItem(new PrintableElement(600, 335, "Player", 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));

	DropDownMenu *p1DropDownMenu = new DropDownMenu("A1DownMenu", 160, 390, ELocation::SELECTPLAY_GUI, ELocation::MASTER, ETask::CHANGE_IA_METHOD, "A1", false);
	p1DropDownMenu->addChoices(IAManager::getMethodsId());
	p1DropDownMenu->addToHeader(new PrintableElement("title", 3, 6, "IA 1 action: ", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA), true, false);

	DropDownMenu *p2DropDownMenu = new DropDownMenu("A2DownMenu", 620, 390, ELocation::SELECTPLAY_GUI, ELocation::MASTER, ETask::CHANGE_IA_METHOD, "A2", false);
	p2DropDownMenu->addChoices(IAManager::getMethodsId());
	p2DropDownMenu->addToHeader(new PrintableElement("title", 3, 6, "IA 2 action: ", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA), true, false);
	menuSelect->addItem(p1DropDownMenu);
	menuSelect->addItem(p2DropDownMenu);

	this->elements.push_back(menuSelect);

	ComplexElement *menuOption = new ComplexElement("menuOption", 130, 200, 893, 558, false);
	menuOption->addItem(new PrintableElement(0, 0, 893, 558, EImage::EMPTY_BACKGROUND));
	float x = 450;
	float xPrint = 210;
	float y = 220;
	for (std::size_t i = 0; i < RuleManager::rules.size(); ++i) {
		menuOption->addItem(new ButtonState(RuleManager::rules[i].first, x, y, 72, 28, ELocation::GAME_GUI, ELocation::GAME, ETask::ACTIVE_RULE, RuleManager::rules[i].first, EImage::CHOICE_ON, EImage::CHOICE_OFF));
		menuOption->addItem(new PrintableElement(xPrint, y, RuleManager::rules[i].first + ": ", 20, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
		y += 50;
	}

	this->elements.push_back(menuOption);

	this->initElements();
}

void GameGUI::initOnEnter()
{
	this->getElementById("buttonP1")->setActivated(RuleManager::p1);
	this->getElementById("buttonA1")->setActivated(!RuleManager::p1);
	this->getElementById("buttonP2")->setActivated(RuleManager::p2);
	this->getElementById("buttonA2")->setActivated(!RuleManager::p2);

	DropDownMenu *A1Menu = (DropDownMenu*)this->getElementById("A1DownMenu");
	A1Menu->setActivated(!RuleManager::p1);
	A1Menu->changeCurrent(RuleManager::p1IAMethod);
	DropDownMenu *A2Menu = (DropDownMenu*)this->getElementById("A2DownMenu");
	A2Menu->setActivated(!RuleManager::p2);
	A2Menu->changeCurrent(RuleManager::p2IAMethod);

	for (std::size_t i = 0; i < RuleManager::getRules().size(); ++i) {
		this->getElementById(RuleManager::getRules()[i])->setActivated(RuleManager::getRule(RuleManager::getRules()[i]).third);
	}
}
