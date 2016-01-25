#pragma once

#include "Graphic\Screen\WindowGame.h"
#include "Graphic\Screen\WindowHome.h"
#include "Graphic\Screen\WindowOption.h"
#include "Graphic\Screen\WindowSelectPlay.h"
#include "Utils\SoundMixer.h"

class Master : public Observer
{
public:
	Master();
	~Master();
public:
	void			init();
	void			quit();
	void			run();
	void			update();
	void			render();
	void			gestEvent();
	void			switchScreen(EWindows id);
	EWindows		getScreen(std::string value);
public:
	virtual void	update(Tuple<ELocation, ELocation, GenericTask> task);
private:
	std::map<EWindows, AWindow*>	windows;
	EWindows						current;
	sf::RenderWindow				screen;
	ELocation						local;
};

