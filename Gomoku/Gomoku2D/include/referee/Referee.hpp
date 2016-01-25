#pragma once

#include <map>
#include <utility>
#include <iostream>

#include "..\map\Cell.h"
#include "IReferee.hpp"

#define IN_BOARD(x, y, w, h) ((x) >= 0 && (y) >= 0 && (x) < (w) && (y) < (h))

using namespace std::placeholders;


template<typename T>
class Referee : public IReferee<T>
{
	// typedef std::function<bool(int, int, PlayerId, const T&)> t_fn;
	std::map<Rule, std::pair<bool, t_fn>> rules;
	std::map<PlayerId, int> taken;
	PlayerId winner = PlayerId::None;
	bool _debug = false;

private:
	bool _safe_is(int x, int y, PlayerId player_id, const T& board) const
	{
		int w = board.width(), h = board.height();
		if (IN_BOARD(x, y, w, h) &&
			board(x, y).player_id == player_id)
			return true;
		return false;
	}

	int _count_free_three_link(int x, int y, const CellCoordinate& q, PlayerId player_id, const T& board, bool cross) const
	{
		static const std::vector<CellCoordinate> v{
				{ -1, -1 },
				{ -1, 0 },
				{ -1, 1 },
				{ 0, -1 },
		};
		int count = 0;

		if (cross)
		{
			for (const auto& p : v)
			{
				count += this->_count_free_three_vector(x, y, p, player_id, board, false);
				if (p[0] == q[0] && p[1] == q[1])
					count -= 1;
			}
		}
		return count;
	}

	int _count_free_three_vector(int x, int y, const CellCoordinate& p, PlayerId player_id, const T& board, bool cross = true) const
	{
		/*
		** Labels:
		**  - Target positon: 'x'
		**  - Adjacent piece: 'o'
		**  - Free space: '-'
		*/
		int count = 0, px = p[0], py = p[1];

		// -oxo-
		if (this->_safe_is(x + 1 * px, y + 1 * py, player_id, board) &&
			this->_safe_is(x - 1 * px, y - 1 * py, player_id, board) &&
			this->_safe_is(x + 2 * px, y + 2 * py, PlayerId::None, board) &&
			this->_safe_is(x - 2 * px, y - 2 * py, PlayerId::None, board))
			return (
				1 +
				this->_count_free_three_link(x + 1 * px, y + 1 * py, p, player_id, board, cross) +
				this->_count_free_three_link(x - 1 * px, y - 1 * py, p, player_id, board, cross)
			);
		for (int i = 0; i < 2; i += 1)
		{
			// i = 0; -xoo-
			// i = 1; -oox-
			if (this->_safe_is(x + 1 * px, y + 1 * py, player_id, board) &&
				this->_safe_is(x + 2 * px, y + 2 * py, player_id, board) &&
				this->_safe_is(x + 3 * px, y + 3 * py, PlayerId::None, board) &&
				this->_safe_is(x - 1 * px, y - 1 * py, PlayerId::None, board))
				return (
					1 +
					this->_count_free_three_link(x + 1 * px, y + 1 * py, p, player_id, board, cross) +
					this->_count_free_three_link(x + 2 * px, y + 2 * py, p, player_id, board, cross)
				);
			px *= -1;
			py *= -1;
		}
		for (int i = 0; i < 2; i += 1)
		{
			// i = 0; -x-oo-
			// i = 1; -oo-x-
			if (this->_safe_is(x - 1 * px, y - 1 * py, PlayerId::None, board) &&
				this->_safe_is(x + 1 * px, y + 1 * py, PlayerId::None, board) &&
				this->_safe_is(x + 2 * px, y + 2 * py, player_id, board) &&
				this->_safe_is(x + 3 * px, y + 3 * py, player_id, board) &&
				this->_safe_is(x + 4 * px, y + 4 * py, PlayerId::None, board))
				count += (
					1 +
					this->_count_free_three_link(x + 2 * px, y + 2 * py, p, player_id, board, cross) +
					this->_count_free_three_link(x + 3 * px, y + 3 * py, p, player_id, board, cross)
				);
			// i = 0; -o-xo-
			// i = 1; -ox-o-
			if (this->_safe_is(x - 1 * px, y - 1 * py, PlayerId::None, board) &&
				this->_safe_is(x - 2 * px, y - 2 * py, player_id, board) &&
				this->_safe_is(x - 3 * px, y - 3 * py, PlayerId::None, board) &&
				this->_safe_is(x + 1 * px, y + 1 * py, player_id, board) &&
				this->_safe_is(x + 2 * px, y + 2 * py, PlayerId::None, board))
				return (
					1 +
					this->_count_free_three_link(x - 2 * px, y - 2 * py, p, player_id, board, cross) +
					this->_count_free_three_link(x + 1 * px, y + 1 * py, p, player_id, board, cross)
				);
			// i = 0; -o-ox-
			// i = 1; -xo-o-
			if (this->_safe_is(x - 1 * px, y - 1 * py, player_id, board) &&
				this->_safe_is(x - 2 * px, y - 2 * py, PlayerId::None, board) &&
				this->_safe_is(x - 3 * px, y - 3 * py, player_id, board) &&
				this->_safe_is(x - 4 * px, y - 4 * py, PlayerId::None, board) &&
				this->_safe_is(x + 1 * px, y + 1 * py, PlayerId::None, board))
				return (
					1 +
					this->_count_free_three_link(x - 1 * px, y - 1 * py, p, player_id, board, cross) +
					this->_count_free_three_link(x - 3 * px, y - 3 * py, p, player_id, board, cross)
				);
			px *= -1;
			py *= -1;
		}
		return count;
	}

	int _count_free_three(int x, int y, PlayerId player_id, const T& board) const
	{
		static const std::vector<CellCoordinate> v{
			{ -1, -1 },
			{ -1, 0 },
			{ -1, 1 },
			{ 0, -1 },
		};
		int count = 0;

		for (const auto& p : v)
		{
			count += this->_count_free_three_vector(x, y, p, player_id, board);
		}

		return count;
	}

	void _print_winner(PlayerId pid) const
	{
		if (this->_debug)
			std::cout << "The winner is P" << static_cast<int>(pid) << std::endl;
	}

	void _set_breakability(int x1, int y1, T& board) const
	{
		static const std::vector<CellCoordinate> v{
			{ -1, -1 },
			{ -1, 0 },
			{ -1, 1 },
			{ 0, -1 },
		};
		PlayerId pid, opp;
		int w = board.width(), h = board.height();

		if (!IN_BOARD(x1, y1, w, h) || (pid = board(x1, y1).player_id) == PlayerId::None)
			return;
		opp = ~pid;

		for (const auto& p : v)
		{
			int len = 1;
			bool unbreakable = false, breakable_begin = false, breakable_end = false;

			for (int x2 = x1, y2 = y1; board(x2, y2).player_id == pid; len += 1)
			{
				x2 += p[0];
				y2 += p[1];
				if (!IN_BOARD(x2, y2, w, h) || len > 2)
					unbreakable = true;
				else if (board(x2, y2).player_id == pid)
					continue;
				else if (board(x2, y2).player_id == opp)
					breakable_begin = true;
				break;
			}

			for (int x2 = x1, y2 = y1; board(x2, y2).player_id == pid; len += 1)
			{
				x2 -= p[0];
				y2 -= p[1];
				if (!IN_BOARD(x2, y2, w, h) || len > 2)
					unbreakable = true;
				else if (board(x2, y2).player_id == pid)
					continue;
				else if (board(x2, y2).player_id == opp)
					breakable_end = true;
				break;
			}

			if (!unbreakable && (breakable_begin != breakable_end) && len == 2)
			{
				board(x1, y1).breakable = true;
				if (this->_debug)
					std::cout << "Breakable(" << x1 << ", " << y1 << ") = "
						<< static_cast<int>(pid) << std::endl;
				return;
			}
		}
		board(x1, y1).breakable = false;
	}

	bool _check_base(int x, int y, PlayerId player_id, const T& board) const
	{
		(void)player_id;
		return board.at(x, y).player_id == PlayerId::None;
	}

	bool _check_break_five(int x, int y, PlayerId player_id, const T& board) const
	{
		(void)x, y, player_id, board;
		return true;
	}

	bool _check_double_three(int x, int y, PlayerId player_id, const T& board) const
	{
		int count = 0;
		if (this->_safe_is(x, y, PlayerId::None, board))
		{
			T cboard = board;
			cboard(x, y).player_id = player_id;
			count = this->_count_free_three(x, y, player_id, cboard);
			if (this->_debug && count > 1)
				std::cout << "[Warning] Linked free three count: " << count << std::endl;
		}
		return count < 2;
	}

	bool _check_freestyle(int x, int y, PlayerId player_id, const T& board) const
	{
		(void)x, y, player_id, board;
		return true;
	}

	inline void _take(int x1, int y1, PlayerId pid, T& board, GameTurn& turn)
	{
		static const std::vector<CellCoordinate> v{
			{ -1, -1 },
			{ -1, 0 },
			{ -1, 1 },
			{ 0, -1 },
			{ 0, 1 },
			{ 1, -1 },
			{ 1, 0 },
			{ 1, 1 },
		};
		PlayerId opp = ~pid;
		int w = board.width(), h = board.height();
		
		if (IN_BOARD(x1, y1, w, h))
			for (const auto& p : v)
			{
				int x2 = x1 + 3 * p[0];
				int y2 = y1 + 3 * p[1];
				if (IN_BOARD(x2, y2, w, h) &&
					board(x1, y1).player_id == pid &&
					board(x2, y2).player_id == pid &&
					board(x1 + p[0], y1 + p[1]).player_id == opp &&
					board(x2 - p[0], y2 - p[1]).player_id == opp)
				{
					board(x1 + p[0], y1 + p[1]).player_id = PlayerId::None;
					board(x2 - p[0], y2 - p[1]).player_id = PlayerId::None;
					std::get<1>(turn).push_back(GameAction{ GameActionType::DEL, x1 + p[0], y1 + p[1] });
					std::get<1>(turn).push_back(GameAction{ GameActionType::DEL, x2 - p[0], y2 - p[1] });
					this->taken[pid] += 2;
				}
			}
		if (this->taken[pid] >= 10)
		{
			this->winner = pid;
			this->_print_winner(pid);
		}
	}

	bool _check_winner_on_cell_const(int x1, int y1, PlayerId player_id, const T& board) const
	{
		static const std::vector<CellCoordinate> v{
			{ -1, -1 },
			{ -1, 0 },
			{ -1, 1 },
			{ 0, -1 },
		};
		int w = board.width(), h = board.width();
		
		if (IN_BOARD(x1, y1, w, h) && this->winner == PlayerId::None)
		{
			for (const auto& p : v)
			{
				bool breakable = false;
				int len, x2 = x1, y2 = y1;

				for (len = 0; IN_BOARD(x2, y2, w, h); len += 1)
				{
					if (board(x2, y2).player_id != player_id)
						break;
					breakable = breakable || board(x2, y2).breakable;
					x2 += p[0];
					y2 += p[1];
				}
				for (x2 = x1 - p[0], y2 = y1 - p[1]; IN_BOARD(x2, y2, w, h); len += 1)
				{
					if (board(x2, y2).player_id != player_id)
						break;
					breakable = breakable || board(x2, y2).breakable;
					x2 -= p[0];
					y2 -= p[1];
				}
				if (len == 5 || (len >= 5 && this->rules.at(Rule::OPT_FREESTYLE).first))
				{
					if (this->rules.at(Rule::OPT_BREAK_FIVE).first && breakable)
						return false;
					return true;
				}
			}
		}
		return false;
	}

	bool _check_winner_on_cell(int x, int y, PlayerId player_id, const T& board, bool set_winner = true)
	{
		bool res = this->_check_winner_on_cell_const(x, y, player_id, board);

		if (res && set_winner)
		{
			this->_print_winner(player_id);
			this->winner = player_id;
		}

		return res;
	}

	void _find_winner(T& board)
	{
		if (this->winner == PlayerId::None)
		{
			int w = board.width(), h = board.height();

			if (this->rules[Rule::OPT_BREAK_FIVE].first)
				for (int x = 0; x < w; x += 1)
					for (int y = 0; y < h; y += 1)
						_set_breakability(x, y, board);

			for (int x = 0; this->winner == PlayerId::None && x < w; x += 1)
				for (int y = 0; this->winner == PlayerId::None && y < h; y += 1)
					if (board(x, y).player_id != PlayerId::None)
						this->_check_winner_on_cell(x, y, board(x, y).player_id, board);
		}
	}

	bool _will_win_from(int x, int y, PlayerId pid, T& board) const
	{
		static const std::vector<CellCoordinate> v{
			{ -1, -1 },
			{ -1, 0 },
			{ -1, 1 },
			{ 0, -1 },
		};
		int w = board.width(), h = board.height();

		for (const auto& p : v)
		{
			int len = 1;
			bool empty_begin = false, empty_end = false;

			for (int xi = x, yi = y; board(xi, yi).player_id == pid; len += 1)
			{
				xi += p[0];
				yi += p[1];
				if (!IN_BOARD(xi, yi, w, h))
					break;
				else if (board(xi, yi).player_id == pid)
					continue;
				else if (board(xi, yi).player_id == PlayerId::None)
					empty_begin = true;
				break;
			}

			for (int xi = x, yi = y; board(xi, yi).player_id == pid; len += 1)
			{
				xi -= p[0];
				yi -= p[1];
				if (!IN_BOARD(xi, yi, w, h))
					break;
				else if (board(xi, yi).player_id == pid)
					continue;
				else if (board(xi, yi).player_id == PlayerId::None)
					empty_end = true;
				break;
			}

			if (len == 4 && empty_begin && empty_end)
				return true;
		}
		return false;
	}

public:
	Referee()
	{
		this->clear();
		this->add_rule(Rule::BASE, std::bind(&Referee::_check_base, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		this->add_rule(Rule::OPT_BREAK_FIVE, std::bind(&Referee::_check_break_five, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		this->add_rule(Rule::OPT_DOUBLE_THREE, std::bind(&Referee::_check_double_three, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
		this->add_rule(Rule::OPT_FREESTYLE, std::bind(&Referee::_check_freestyle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
	}

	virtual ~Referee()
	{

	}

	void clear()
	{
		this->winner = PlayerId::None;
		this->taken[PlayerId::None] = 0;
		this->taken[PlayerId::P1] = 0;
		this->taken[PlayerId::P2] = 0;
	}

	void add_rule(Rule rule_id, t_fn fn) override final
	{
		this->rules[rule_id] = std::pair<bool, t_fn>(true, fn);
	}

	void enable_rule(Rule rule_id, bool enable = true) override final
	{
		this->rules[rule_id].first = enable;
	}

	bool is_rule_enabled(Rule rule_id) const override final
	{
		return this->rules.at(rule_id).first;
	}

	bool is_valid(int x, int y, PlayerId player_id, const T& board) const override final
	{
		for (const auto& rule : this->rules)
			if (rule.second.first && !rule.second.second(x, y, player_id, board))
				return false;
		return true;
	}

	void play(int x, int y, PlayerId player_id, T& board)
	{
		GameTurn null;
		play(x, y, player_id, board, null);
	}

	void play(int x, int y, PlayerId player_id, T& board, GameTurn& turn)
	{
		(void)turn;
		board(x, y).player_id = player_id;
		std::get<0>(turn) = player_id;
		std::get<1>(turn).push_back(GameAction{ GameActionType::ADD, x, y });
		if (player_id != PlayerId::None)
		{
			this->_take(x, y, player_id, board, turn);
			this->_find_winner(board);
		}
	}

	void undo(const GameTurn& turn, T&board)
	{
		PlayerId pid = std::get<0>(turn), opp = ~pid;
		
		for (const GameAction& action : std::get<1>(turn))
		{
			switch (std::get<0>(action))
			{
			case GameActionType::ADD:
				board(std::get<1>(action), std::get<2>(action)).player_id = PlayerId::None;
				break;
			case GameActionType::DEL:
				board(std::get<1>(action), std::get<2>(action)).player_id = opp;
				this->taken[pid] -= 1;
				break;
			}
		}
		this->winner = PlayerId::None;
	}

	void redo(const GameTurn& turn, T& board)
	{
		PlayerId pid = std::get<0>(turn);
		int x = -1, y = -1;

		for (const GameAction& action : std::get<1>(turn))
		{
			switch (std::get<0>(action))
			{
			case GameActionType::ADD:
				x = std::get<1>(action);
				y = std::get<2>(action);
				board(x, y).player_id = pid;
				break;
			case GameActionType::DEL:
				board(std::get<1>(action), std::get<2>(action)).player_id = PlayerId::None;
				this->taken[pid] += 1;
				if (this->taken[pid] >= 10)
				{
					this->winner = pid;
					this->_print_winner(pid);
				}
				break;
			}
		}
		this->_find_winner(board);
	}

	void refresh(T& board, bool enable_will_win = true)
	{
		bool d = this->_debug,
			breakfive = this->rules[Rule::OPT_BREAK_FIVE].first;
			// freestyle = this->rules[Rule::OPT_FREESTYLE].first;
		PlayerId old_winner = this->winner;
		int w = board.width(), h = board.height();
		this->rules[Rule::OPT_BREAK_FIVE].first = false;
		// this->rules[Rule::OPT_FREESTYLE].first = false;

		this->_debug = false;
		for (int x = 0; x < w; x += 1)
			for (int y = 0; y < h; y += 1)
			{
				if (board(x, y).player_id != PlayerId::None)
				{
					board(x, y).p1_win = false;
					board(x, y).p2_win = false;
					board(x, y).p1_will_win = false;
					board(x, y).p2_will_win = false;
					continue;
				}
				PlayerId old = board(x, y).player_id;

				if (this->is_valid(x, y, PlayerId::P1, board))
				{
					GameTurn simulation;
					this->play(x, y, PlayerId::P1, board, simulation);
					board(x, y).p1_win = this->get_winner() == PlayerId::P1;
					if (!board(x, y).p1_win && enable_will_win)
						board(x, y).p1_will_win = this->_will_win_from(x, y, PlayerId::P1, board);
					this->undo(simulation, board);
				}
				else
				{
					board(x, y).p1_win = false;
					board(x, y).p1_will_win = false;
				}
				board(x, y).player_id = old;

				if (this->is_valid(x, y, PlayerId::P2, board))
				{
					GameTurn simulation;
					this->play(x, y, PlayerId::P2, board, simulation);
					board(x, y).p2_win = this->get_winner() == PlayerId::P2;
					if (!board(x, y).p2_win && enable_will_win)
						board(x, y).p2_will_win = this->_will_win_from(x, y, PlayerId::P2, board);
					this->undo(simulation, board);
				}
				else
				{
					board(x, y).p2_win = false;
					board(x, y).p2_will_win = false;
				}
				board(x, y).player_id = old;
			}
		this->_debug = d;
		this->winner = old_winner;
		this->rules[Rule::OPT_BREAK_FIVE].first = breakfive;
		// this->rules[Rule::OPT_FREESTYLE].first = freestyle;
	}

	int get_pieces_taken(PlayerId player_id) const
	{
		return this->taken.at(player_id);
	}

	PlayerId get_winner() const
	{
		return this->winner;
	}

	void set_debug(bool debug)
	{
		this->_debug = debug;
	}

	bool get_debug() const
	{
		return this->_debug;
	}
};
