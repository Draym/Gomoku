#pragma once

#include "Utils\Task\GenericTask.h"
#include "Utils\Task\TaskFactory.h"

class Observer
{
public:
	virtual void	update(Tuple<ELocation, ELocation, GenericTask> message) = 0;
};