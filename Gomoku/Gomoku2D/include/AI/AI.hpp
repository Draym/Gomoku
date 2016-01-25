#pragma once

#include <chrono>
#include <cstdint>

#include "IAI.hpp"
#include "AI\minMax\MinMax.h"
#include "AI\monteCarlo\MonteCarlo.h"

template<typename T>
class AIFactory
{
public:
	class Heuristic
	{
	public:
		static inline int distance(int x1, int y1, int x2, int y2)
		{
			int dx = std::abs(x1 - x2);
			int dy = std::abs(y1 - y2);

			return std::max(dx, dy);
		}
		static std::vector<CellCoordinate> all_valid(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			std::vector<CellCoordinate> choices;
			int w = board.width(), h = board.height();

			for (int i = 0; i < w; i += 1)
				for (int j = 0; j < h; j += 1)
				{
					// Worst heuristic ever, FTM
					if (referee.is_valid(i, j, pid, board))
						choices.push_back({ i, j });
				}

			return choices;
		}

		static std::vector<CellCoordinate> near_valid(const IReferee<T>& referee, const T& board, PlayerId pid, int max_distance)
		{
			std::vector<CellCoordinate> choices, valid;
			int w = board.width(), h = board.height();

			for (int i = 0; i < w; i += 1)
				for (int j = 0; j < h; j += 1)
				{
					if (referee.is_valid(i, j, pid, board))
					{
						bool done = false;
						valid.push_back({ i, j });
						for (int i2 = 0; !done && i2 < w; i2 += 1)
							for (int j2 = 0; !done && j2 < h; j2 += 1)
							{
								if (board(i2, j2).player_id != PlayerId::None &&
									distance(i, j, i2, j2) <= max_distance)
									done = true;
							}
						if (done)
							choices.push_back({ i, j });
					}
				}

			if (choices.size() == 0)
				return valid;
			else
				return choices;
		}
	};

	class MindGame
	{
	public:
		static CellCoordinate pick_first(const std::vector<CellCoordinate>& coord)
		{
			for (const auto& p : coord)
				return p;
			return { -1, -1 };
		}

		static CellCoordinate pick_random(const std::vector<CellCoordinate>& coord)
		{
			std::size_t size = coord.size();

			if (size == 0)
				return { -1, -1 };
			return coord[rand() % size];
		}

		static CellCoordinate pick_best(const std::vector<CellCoordinate>& coord, PlayerId pid, const T& board)
		{
			int xloose = -1, yloose = -1,
				x_will_win = -1, y_will_win = -1,
				x_will_loose = -1, y_will_loose = -1;

			for (const CellCoordinate& pos : coord)
			{
				const Cell& cell = board(pos.at(0), pos.at(1));

				switch (pid)
				{
				case PlayerId::P1:
					if (cell.p1_win)
						return pos;
					else if (cell.p2_win && xloose == -1 && yloose == -1)
					{
						xloose = pos.at(0);
						yloose = pos.at(1);
					}
					else if (cell.p1_will_win && x_will_win == -1 && y_will_win == -1)
					{
						x_will_win = pos.at(0);
						y_will_win = pos.at(1);
					}
					else if (cell.p2_will_win && x_will_loose == -1 && y_will_loose == -1)
					{
						x_will_loose = pos.at(0);
						y_will_loose = pos.at(1);
					}
					break;
				case PlayerId::P2:
					if (cell.p2_win)
						return pos;
					else if (cell.p1_win && xloose == -1 && yloose == -1)
					{
						xloose = pos.at(0);
						yloose = pos.at(1);
					}
					else if (cell.p2_will_win && x_will_win == -1 && y_will_win == -1)
					{
						x_will_win = pos.at(0);
						y_will_win = pos.at(1);
					}
					else if (cell.p1_will_win && x_will_loose == -1 && y_will_loose == -1)
					{
						x_will_loose = pos.at(0);
						y_will_loose = pos.at(1);
					}
					break;
				default:
					return { -1, -1 };
				}
			}

			if (xloose != -1 && yloose != -1)
				return { xloose, yloose };
			else if (x_will_win != -1 && y_will_win != -1)
				return { x_will_win, y_will_win };
			else if (x_will_loose != -1 && y_will_loose != -1)
				return { x_will_loose, y_will_loose };
			else
				return pick_random(coord);
		}

		static CellCoordinate play_first(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			return pick_first(Heuristic::all_valid(referee, board, pid));
		}

		static CellCoordinate play_random(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			return pick_random(Heuristic::all_valid(referee, board, pid));
		}

		static CellCoordinate play_best(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			return pick_best(Heuristic::all_valid(referee, board, pid), pid, board);
		}

		static CellCoordinate play_near_d1_best(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			return pick_best(Heuristic::near_valid(referee, board, pid, 1), pid, board);
		}

		static CellCoordinate play_near_d2_best(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			return pick_best(Heuristic::near_valid(referee, board, pid, 2), pid, board);
		}

		static CellCoordinate play_minmax(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			static constexpr int depth = 3;
			std::vector<CellCoordinate> choices = Heuristic::near_valid(referee, board, pid, 1);
			if (choices.size() > 64)
				return pick_best(choices, pid, board);
			MinMax::Node node(
				depth,
				pid,
				choices[0],
				static_cast<const Grid<Cell>&>(board),
				static_cast<const Referee<Grid<Cell>>&>(referee)
			);
			std::size_t index = 0, i = 0;
			double best_value = node.get_value();

			for (const CellCoordinate& coord : choices)
			{
				MinMax::Node alt_node(
					depth,
					pid,
					coord,
					static_cast<const Grid<Cell>&>(board),
					static_cast<const Referee<Grid<Cell>>&>(referee)
				);
				if (alt_node.get_value() > best_value)
				{
					best_value = alt_node.get_value();
					index = i;
				}
				if (alt_node.is_best(depth, best_value))
					break;
				i += 1;
			}
			return choices.at(index);
		}

		static CellCoordinate play_monteCarlo_easy(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			return monteCarloEasy(
				static_cast<const Referee<Grid<Cell>>&>(referee),
				static_cast<const Grid<Cell>&>(board),
				pid
				);
		}

		static CellCoordinate play_monteCarlo_medium(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			return monteCarloMedium(
				static_cast<const Referee<Grid<Cell>>&>(referee),
				static_cast<const Grid<Cell>&>(board),
				pid
				);
		}

		static CellCoordinate play_monteCarlo_hard(const IReferee<T>& referee, const T& board, PlayerId pid)
		{
			return monteCarloHard(
				static_cast<const Referee<Grid<Cell>>&>(referee),
				static_cast<const Grid<Cell>&>(board),
				pid
				);
		}

	};

	class AI : public IAI<T>
	{
		using Clock = std::chrono::high_resolution_clock;
		using TimeElapsed = std::chrono::microseconds;

		PlayerId _pid;
		Function _fn;
		int64_t _delta;

	public:
		AI(PlayerId pid, Function fn) : _pid(pid), _fn(fn), _delta(0)
		{

		}

		virtual ~AI()
		{

		}

		virtual PlayerId get_playerid() const final
		{
			return this->_pid;
		}

		virtual double get_time_elapsed() const final
		{
			return 1.0 * this->_delta / 1000000.0;
		}

		virtual void change_mind(Function fn) final
		{
			this->_fn = fn;
		}

		virtual CellCoordinate play(const IReferee<T>& referee, const T& board) final
		{
			CellCoordinate coord;
			std::chrono::time_point<Clock> a, b;

			a = Clock::now();
			coord = this->_fn(referee, board, this->_pid);
			b = Clock::now();

			auto delta = std::chrono::duration_cast<TimeElapsed>(b - a);
			this->_delta = delta.count();
			return coord;
		}

		virtual std::future<CellCoordinate> async_play(const IReferee<T>& referee, const T& board) final
		{
			return std::async(
				std::launch::async,
				[&]() { return this->play(referee, board); }
			);
		}
	};

	class AsyncAI : public AI
	{
		bool _played = false;
		std::future<CellCoordinate> _result;

	public:
		AsyncAI(PlayerId pid, Function fn) : AI(pid, fn)
		{

		}

		virtual ~AsyncAI()
		{

		}

		virtual void play_async(const IReferee<T>& referee, const T& board) final
		{
			this->_played = true;
			this->_result = this->async_play(referee, board);
		}

		virtual bool is_playing() const final
		{
			return this->_result.valid() && this->_result.wait_for(std::chrono::seconds(0)) != std::future_status::ready;
		}

		virtual bool has_played() const final
		{
			return this->_played;
		}

		virtual CellCoordinate get_result() final
		{
			this->_played = false;
			return this->_result.get();
		}
	};

	class DummyAI : public AI
	{
	public:
		DummyAI(PlayerId pid) : AI(pid, &MindGame::play_first)
		{

		}

		virtual ~DummyAI()
		{

		}
	};

	class AsyncDummyAI : public AsyncAI
	{
	public:
		AsyncDummyAI(PlayerId pid) : AsyncAI(pid, &MindGame::play_first)
		{

		}

		virtual ~AsyncDummyAI()
		{

		}
	};

	class RandomAI : public AI
	{
	public:
		RandomAI(PlayerId pid) : AI(pid, &MindGame::play_random)
		{

		}

		virtual ~RandomAI()
		{

		}
	};

	class AsyncRandomAI : public AsyncAI
	{
	public:
		AsyncRandomAI(PlayerId pid) : AsyncAI(pid, &MindGame::play_random)
		{

		}

		virtual ~AsyncRandomAI()
		{

		}
	};

	class BestRandomAI : public AI
	{
	public:
		BestRandomAI(PlayerId pid) : AI(pid, &MindGame::play_best)
		{

		}

		virtual ~BestRandomAI()
		{

		}
	};

	class AsyncBestRandomAI : public AsyncAI
	{
	public:
		AsyncBestRandomAI(PlayerId pid) : AsyncAI(pid, &MindGame::play_best)
		{

		}

		virtual ~AsyncBestRandomAI()
		{

		}
	};

	class NearBestRandomAI : public AI
	{
	public:
		NearBestRandomAI(PlayerId pid) : AI(pid, &MindGame::play_near_d1_best)
		{

		}

		virtual ~NearBestRandomAI()
		{

		}
	};

	class AsyncNearBestRandomAI : public AsyncAI
	{
	public:
		AsyncNearBestRandomAI(PlayerId pid) : AsyncAI(pid, &MindGame::play_near_d1_best)
		{

		}

		virtual ~AsyncNearBestRandomAI()
		{

		}
	};

	class MinMaxAI : public AI
	{
	public:
		MinMaxAI(PlayerId pid) : AI(pid, &MindGame::play_minmax)
		{

		}

		virtual ~MinMaxAI()
		{

		}
	};

	class AsyncMinMaxAI : public AsyncAI
	{
	public:
		AsyncMinMaxAI(PlayerId pid) : AsyncAI(pid, &MindGame::play_minmax)
		{

		}

		virtual ~AsyncMinMaxAI()
		{

		}
	};

};

