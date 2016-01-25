#pragma once

#include <limits>
#include <memory>
#include <stdexcept>

#include "map\Grid.hpp"
#include "referee\Referee.hpp"

namespace MinMax
{

	enum class Type 
	{
		MINIMIZER, // Player
		MAXIMIZER  // A.I.
	};

	Type operator~(const Type& value);
	int operator+(const Type& value);
	int operator-(const Type& value);

	class NodeError : public std::runtime_error
	{
	public:
		NodeError(const std::string& what_arg);
		virtual ~NodeError();
	};

	class Node
	{
		static const int heuristic_distance = 1;

		// Node value
		double _value;
		PlayerId _pid;
		CellCoordinate _pos;
		Grid<Cell> _board;
		Referee<Grid<Cell>> _referee;
		Type _type;

		// Alpha-Beta pruning
		int a = std::numeric_limits<int>::min(); // Best option explored for Maximizer
		int b = std::numeric_limits<int>::max(); // Best option explored for Minimizer

		std::vector<std::unique_ptr<Node*>> children;

	public:
		Node(int depth, PlayerId pid, CellCoordinate pos, Grid<Cell> board, Referee<Grid<Cell>> ref, Type type = Type::MAXIMIZER);
		virtual ~Node();

		void create_children(int depth);
		bool is_best(int depth, double value);
		double get_value() const;
		void eval(int depth);
	};
};