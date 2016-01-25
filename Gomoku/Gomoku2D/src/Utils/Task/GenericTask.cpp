#include "Utils\Task\GenericTask.h"


GenericTask::GenericTask() : type(ETask::NONE)
{
}

GenericTask::GenericTask(ETask type) : type(type)
{
}

GenericTask::~GenericTask()
{
}

void GenericTask::addParameter(std::string value)
{
	std::size_t pos = 0;

	while ((pos = value.find(":")) != std::string::npos)
	{
		std::string tmp = value.substr(0, pos);
		value.erase(0, pos + 1);
		this->parameters.push_back(tmp);
	}
	this->parameters.push_back(value);
}

bool GenericTask::hasParameters() const
{
	return (this->parameters.size() > 0 ? true : false);
}

std::vector<std::string>	GenericTask::getParameters() const
{
	return this->parameters;
}

ETask GenericTask::getTask() const
{
	return this->type;
}
