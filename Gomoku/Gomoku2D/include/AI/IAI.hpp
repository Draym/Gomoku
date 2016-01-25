#pragma once

#include <future>

#include "referee\Referee.hpp"

template<typename T>
class IAI
{
public:
	using Function = std::function<CellCoordinate(const IReferee<T>&, const T&, PlayerId)>;

	virtual PlayerId get_playerid() const = 0;
	virtual double get_time_elapsed() const = 0;
	virtual void change_mind(Function fn) = 0;
	virtual CellCoordinate play(const IReferee<T>& referee, const T& board) = 0;
	virtual std::future<CellCoordinate> async_play(const IReferee<T>& referee, const T& board) = 0;
};
