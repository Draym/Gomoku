#include "Graphic\Interface\Elements\PrintableElement.h"


PrintableElement::PrintableElement(float x, float y, std::string value, int size, sf::Color color, EFont font, bool activated)
	: GuiElement(EGuiElement::PRINTABLE, x, y, (float)(value.size() * size), (float)size, activated)
	, txtVal(value)
	, txtSize(size)
	, txtColor(color)
	, txtFont(font)
	, imgId(EImage::NONE)
{
}

PrintableElement::PrintableElement(std::string id, float x, float y, std::string value, int size, sf::Color color, EFont font, bool activated)
	: GuiElement(EGuiElement::PRINTABLE, id, x, y, (float)(value.size() * size), (float)size, activated)
	, txtVal(value)
	, txtSize(size)
	, txtColor(color)
	, txtFont(font)
	, imgId(EImage::NONE)
{
}

PrintableElement::PrintableElement(float x, float y, float width, float height, EImage imgId, bool activated)
	: GuiElement(EGuiElement::PRINTABLE, x, y, width, height, activated)
	, txtVal("")
	, imgId(imgId)
{
}

PrintableElement::PrintableElement(float x, float y, float width, float height, std::string value, int size, sf::Color color, EFont font, EImage imgId, bool activated)
	: GuiElement(EGuiElement::PRINTABLE, x, y, width, height, activated)
	, txtVal(value)
	, txtSize(size)
	, txtColor(color)
	, txtFont(font)
	, imgId(imgId)
{
}

PrintableElement::~PrintableElement()
{
}

void PrintableElement::init()
{
	if (this->txtVal != "")
	{
		this->text.setFont(ResourceManager::getFont(this->txtFont));
		this->text.setString(this->txtVal);
		this->text.setCharacterSize(this->txtSize);
		this->text.setColor(this->txtColor);
		this->text.setPosition(this->posX, this->posY);
		this->width = this->text.getLocalBounds().width;
	}
	if (this->imgId != EImage::NONE)
	{
		this->image.setTexture(ResourceManager::getImage(this->imgId));
		this->image.setPosition(this->posX, this->posY);
	}
}

void PrintableElement::draw(sf::RenderWindow & screen)
{
	if (this->activated) {
		if (this->txtVal != "") {
			this->text.setPosition(this->posX, this->posY);
			screen.draw(this->text);
		}
		if (this->imgId != EImage::NONE) {
			this->image.setPosition(this->posX, this->posY);
			screen.draw(this->image);
		}
	}
}

void PrintableElement::draw(sf::RenderWindow & screen, float x, float y)
{
	if (this->activated) {
		if (this->txtVal != "") {
			this->text.setPosition(this->posX + x, this->posY + y);
			screen.draw(this->text);
		}
		if (this->imgId != EImage::NONE) {
			this->image.setPosition(this->posX + x, this->posY + y);
			screen.draw(this->image);
		}
	}
}

void PrintableElement::doTask(GenericTask task)
{
	if (task.getTask() == ETask::ADD_TITLE && task.hasParameters()) {
		std::vector<std::string>	param = task.getParameters();

		if (param.size() > 1) {
			this->txtColor = ResourceManager::getColor(ConvertTools::convertToColor(param[0]));
			this->txtVal = param[1];
			this->init();
		}
	}
}

Tuple<ELocation, ELocation, GenericTask> PrintableElement::event(sf::Event event)
{
	return TaskFactory::createEmpty();
}

Tuple<ELocation, ELocation, GenericTask> PrintableElement::isSelected(int x, int y)
{
	return TaskFactory::createEmpty();
}
