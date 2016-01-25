#pragma once

#include "GenericTask.h"
#include "Utils\Tuple.h"

enum class ELocation {
	NONE,
	MASTER,
	HOME, HOME_GUI,
	GAME, GAME_GUI, GAME_CONTROLLER,
	OPTION, OPTION_GUI,
	SELECTPLAY, SELECTPLAY_GUI
};

class TaskFactory
{
public:
	static Tuple<ELocation, ELocation, GenericTask>	createTask(ELocation location, ELocation destination, GenericTask task);
	static Tuple<ELocation, ELocation, GenericTask>	createEmpty();
	static bool										isEmpty(Tuple<ELocation, ELocation, GenericTask> task);
};