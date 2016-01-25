#include "Observer\Observable.h"

Observable::Observable()
{
}

Observable::~Observable()
{
}

void	Observable::notifyObserver(Tuple<ELocation, ELocation, GenericTask> message) {
	for (std::size_t i = 0; i < this->observers.size(); ++i) {
		this->observers[i]->update(message);
	}
}
void	Observable::addObserver(Observer *observer)
{
	this->observers.push_back(observer);
}
