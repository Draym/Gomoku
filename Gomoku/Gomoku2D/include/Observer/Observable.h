#pragma once

#include <vector>
#include "Observer.h"

class Observable
{
public:
	Observable();
	virtual ~Observable();
public:
	void	addObserver(Observer *observer);
	void	notifyObserver(Tuple<ELocation, ELocation, GenericTask> message);
private:
	std::vector<Observer*>	observers;
};

