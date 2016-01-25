#include "Graphic\Interface\OptionGUI.h"

OptionGUI::OptionGUI()
{
	this->local = ELocation::HOME_GUI;
}


OptionGUI::~OptionGUI()
{
}

void	OptionGUI::init()
{
	this->elements.clear();
	this->elements.push_back(new Button(809, 488, 53, 56, ELocation::OPTION_GUI, ELocation::MASTER, ETask::SWITCH_SCREEN, "HOME", EImage::BUTTON_HOME, EImage::BUTTON_HOME_FLASH));

	float x = 450;
	float xPrint = 210;
	float y = 220;
	for (std::size_t i = 0; i < RuleManager::rules.size(); ++i) {
		this->elements.push_back(new ButtonState(RuleManager::rules[i].first, x, y, 72, 28, ELocation::OPTION_GUI, ELocation::OPTION, ETask::ACTIVE_RULE, RuleManager::rules[i].first, EImage::CHOICE_ON, EImage::CHOICE_OFF));
		this->elements.push_back(new PrintableElement(xPrint, y, RuleManager::rules[i].first + ": ", 20, ResourceManager::getColor(EColor::BLACK), EFont::KATANA));
		y += 50;
	}
	this->initElements();
}

void OptionGUI::initOnEnter()
{
	for (std::size_t i = 0; i < RuleManager::getRules().size(); ++i) {
		this->getElementById(RuleManager::getRules()[i])->setActivated(RuleManager::getRule(RuleManager::getRules()[i]).third);
	}
}
