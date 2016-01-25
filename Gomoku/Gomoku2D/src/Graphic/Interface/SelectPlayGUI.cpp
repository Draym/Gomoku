
#include "Graphic\Interface\SelectPlayGUI.h"

SelectPlayGUI::SelectPlayGUI()
{
	this->local = ELocation::SELECTPLAY_GUI;
}


SelectPlayGUI::~SelectPlayGUI()
{
}

void	SelectPlayGUI::init()
{
	this->elements.clear();
	this->elements.push_back(new Button(40, 480, 53, 56, ELocation::SELECTPLAY_GUI, ELocation::MASTER, ETask::SWITCH_SCREEN, "HOME", EImage::BUTTON_HOME, EImage::BUTTON_HOME_FLASH));
	this->elements.push_back(new Button(809, 480, 50, 55, ELocation::SELECTPLAY_GUI, ELocation::MASTER, ETask::SWITCH_SCREEN, "GAME", EImage::BUTTON_PLAY, EImage::BUTTON_PLAY_FLASH));
	this->elements.push_back(new ButtonState("buttonP1", 115, 250, 150, 49, ELocation::SELECTPLAY_GUI, ELocation::SELECTPLAY, ETask::CHANGE_PLAYER, "P1:true:buttonP1:true:buttonA1:false:A1DownMenu:false", EImage::BUTTON_EMPTY_ON, EImage::BUTTON_EMPTY_OFF));
	this->elements.push_back(new ButtonState("buttonA1", 115, 320, 150, 49, ELocation::SELECTPLAY_GUI, ELocation::SELECTPLAY, ETask::CHANGE_PLAYER, "P1:false:buttonP1:false:buttonA1:true:A1DownMenu:true", EImage::BUTTON_EMPTY_ON, EImage::BUTTON_EMPTY_OFF, false));
	this->elements.push_back(new ButtonState("buttonP2", 580, 320, 150, 49, ELocation::SELECTPLAY_GUI, ELocation::SELECTPLAY, ETask::CHANGE_PLAYER, "P2:true:buttonP2:true:buttonA2:false:A2DownMenu:false", EImage::BUTTON_EMPTY_ON, EImage::BUTTON_EMPTY_OFF));
	this->elements.push_back(new ButtonState("buttonA2", 580, 250, 150, 49, ELocation::SELECTPLAY_GUI, ELocation::SELECTPLAY, ETask::CHANGE_PLAYER, "P2:false:buttonP2:false:buttonA2:true:A2DownMenu:true", EImage::BUTTON_EMPTY_ON, EImage::BUTTON_EMPTY_OFF, false));
	this->elements.push_back(new PrintableElement(350, 240, 150, 143, EImage::VERSUS));
	this->elements.push_back(new PrintableElement(135, 265, "Player", 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	this->elements.push_back(new PrintableElement(135, 335, "Ordinateur", 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	this->elements.push_back(new PrintableElement(600, 265, "Ordinateur", 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
	this->elements.push_back(new PrintableElement(600, 335, "Player", 15, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));

	DropDownMenu *p1DropDownMenu = new DropDownMenu("A1DownMenu", 160, 390, ELocation::SELECTPLAY_GUI, ELocation::MASTER, ETask::CHANGE_IA_METHOD, "A1", false);
	p1DropDownMenu->addChoices(IAManager::getMethodsId());
	p1DropDownMenu->addToHeader(new PrintableElement("title", 3, 6, "IA 1 action: ", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA), true, false);

	DropDownMenu *p2DropDownMenu = new DropDownMenu("A2DownMenu", 620, 390, ELocation::SELECTPLAY_GUI, ELocation::MASTER, ETask::CHANGE_IA_METHOD, "A2", false);
	p2DropDownMenu->addChoices(IAManager::getMethodsId());
	p2DropDownMenu->addToHeader(new PrintableElement("title", 3, 6, "IA 2 action: ", 16, ResourceManager::getColor(EColor::BLACK), EFont::KATANA), true, false);
	this->elements.push_back(p1DropDownMenu);
	this->elements.push_back(p2DropDownMenu);
	this->initElements();
}

void SelectPlayGUI::initOnEnter()
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
}
