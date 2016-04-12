#include "Subject.h"

void Subject::addObserver(Observer* observer)
{
	this->observers.insert(observer);
}

void Subject::removeObserver(Observer* observer)
{
	this->observers.erase(observer);
}
