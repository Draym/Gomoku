#include "Graphic\Interface\HomeGUI.h"

HomeGUI::HomeGUI()
{
	this->local = ELocation::HOME_GUI;
}

HomeGUI::~HomeGUI()
{
}

void	HomeGUI::init()
{
	this->elements.clear();
	this->elements.push_back(new Button(119, 420, 296, 98, ELocation::HOME_GUI, ELocation::MASTER, ETask::SWITCH_SCREEN, "SELECTPLAY", EImage::BUTTON_SINGLEGAME, EImage::BUTTON_SINGLEGAME_FLASH));
	this->elements.push_back(new Button(478, 420, 296, 98, ELocation::HOME_GUI, ELocation::MASTER, ETask::SWITCH_SCREEN, "", EImage::BUTTON_HALLGAME, EImage::BUTTON_HALLGAME_FLASH));
	this->elements.push_back(new Button(807, 10, 74, 74, ELocation::HOME_GUI, ELocation::MASTER, ETask::SWITCH_SCREEN, "OPTION", EImage::BUTTON_OPTION, EImage::BUTTON_OPTION_FLASH));
	this->elements.push_back(new Button(810, 112, 70, 72, ELocation::HOME_GUI, ELocation::MASTER, ETask::SWITCH_MUSIC, "", EImage::BUTTON_MUSIC, EImage::BUTTON_MUSIC_FLASH));
	this->elements.push_back(new ButtonState("buttonMusicHome", 810, 200, 70, 72, ELocation::HOME_GUI, ELocation::MASTER, ETask::ACTIVE_MUSIC, "", EImage::SOUND_ON, EImage::SOUND_OFF));
	this->initElements();
}

void HomeGUI::initOnEnter()
{
}
