#include "Utils\Task\TaskFactory.h"

Tuple<ELocation, ELocation, GenericTask> TaskFactory::createTask(ELocation local, ELocation destination, GenericTask task)
{
	return Tuple<ELocation, ELocation, GenericTask>(local, destination, task);
}

Tuple<ELocation, ELocation, GenericTask> TaskFactory::createEmpty()
{
	return Tuple<ELocation, ELocation, GenericTask>(ELocation::NONE, ELocation::NONE, GenericTask());
}

bool	TaskFactory::isEmpty(Tuple<ELocation, ELocation, GenericTask> task) {
	return (task.first == ELocation::NONE && task.second == ELocation::NONE && task.third.getTask() == ETask::NONE);
}