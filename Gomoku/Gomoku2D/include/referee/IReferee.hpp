#pragma once

#include <functional>

#include "History.h"

enum class Rule : unsigned char
{
	BASE,
	OPT_BREAK_FIVE,
	OPT_DOUBLE_THREE,
	/* Bonus rules */
	OPT_FREESTYLE
};

template<typename T>
class IReferee
{
public:
	typedef std::function<bool(int, int, PlayerId, const T&)> t_fn;

	virtual void clear() = 0;
	virtual void add_rule(Rule rule_id, t_fn fn) = 0;
	virtual void enable_rule(Rule rule_id, bool enable = true) = 0;
	virtual bool is_rule_enabled(Rule rule_id) const = 0;
	virtual bool is_valid(int x, int y, PlayerId player_id, const T& board) const = 0;
	virtual void play(int x, int y, PlayerId player_id, T& board) = 0;
	virtual void play(int x, int y, PlayerId player_id, T& board, GameTurn& turn) = 0;
	virtual void undo(const GameTurn& turn, T& board) = 0;
	virtual void redo(const GameTurn& turn, T& board) = 0;
	virtual void refresh(T& board, bool enable_will_win = true) = 0;
	virtual int get_pieces_taken(PlayerId player_id) const = 0;
	virtual PlayerId get_winner() const = 0;
	virtual void set_debug(bool debug) = 0;
	virtual bool get_debug() const = 0;
};
