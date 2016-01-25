#pragma once

#include <vector>
#include "Utils\Exception.h"

enum class ETask {
	NONE,
	SWITCH_SCREEN,
	SWITCH_ACTIVATED,
	UNDO_ACTION,
	REDO_ACTION,
	ACTIVE_RULE,
	ACTIVE_GUI_ELEM,
	ACTIVE_MUSIC,
	SWITCH_MUSIC,
	CHANGE_PLAYER,
	CHANGE_IA_METHOD,
	GIVE_TASK,
	ADD_TITLE
};

class GenericTask
{
public:
	GenericTask();
	GenericTask(ETask type);
	~GenericTask();
public:
	void						addParameter(std::string value);
	bool						hasParameters() const;
	std::vector<std::string>	getParameters() const;
	ETask						getTask() const;
private:
	ETask						type;
	std::vector<std::string>	parameters;
};

