#include "AI\AI.hpp"
#include "AI\minMax\MinMax.h"

MinMax::NodeError::NodeError(const std::string& what_arg) : std::runtime_error(what_arg)
{

}

MinMax::NodeError::~NodeError()
{

}

MinMax::Type MinMax::operator~(const MinMax::Type& value)
{
	switch (value)
	{
	case MinMax::Type::MINIMIZER:
		return MinMax::Type::MAXIMIZER;
	case MinMax::Type::MAXIMIZER:
		return MinMax::Type::MINIMIZER;
	default:
		throw MinMax::NodeError("Invalid node type");
	}
}

int MinMax::operator+(const MinMax::Type& value)
{
	switch (value)
	{
	case MinMax::Type::MINIMIZER:
		return std::numeric_limits<int>::min();
	case MinMax::Type::MAXIMIZER:
		return std::numeric_limits<int>::max();
	default:
		throw MinMax::NodeError("Invalid node type");
	}
}

int MinMax::operator-(const MinMax::Type& value)
{
	switch (value)
	{
	case MinMax::Type::MINIMIZER:
		return std::numeric_limits<int>::max();
	case MinMax::Type::MAXIMIZER:
		return std::numeric_limits<int>::min();
	default:
		throw MinMax::NodeError("Invalid node type");
	}
}

MinMax::Node::Node(int depth, PlayerId pid, CellCoordinate pos, Grid<Cell> board, Referee<Grid<Cell>> referee, Type type)
	: _value(0.0)
	, _pid(pid)
	, _pos(pos)
	, _board(board)
	, _referee(referee)
	, _type(type)
{
	// Evaluate value
	this->_referee.play(this->_pos.at(0), this->_pos.at(1), this->_pid, this->_board);
	this->eval(depth);

	// Create nodes
	if (!this->is_best(depth, this->get_value()) && depth > 1)
		this->create_children(depth - 1);
}

MinMax::Node::~Node()
{

}

void MinMax::Node::create_children(int depth)
{
	double best_value = -this->_type;
	std::vector<CellCoordinate> choices = AIFactory<Grid<Cell>>::Heuristic::near_valid(
		this->_referee,
		this->_board,
		~this->_pid,
		Node::heuristic_distance
	);

	for (const CellCoordinate& coord : choices)
	{
		Node child(depth, ~this->_pid, coord, this->_board, this->_referee, ~this->_type);
		double child_value = child.get_value();

		switch (~this->_type)
		{
		case MinMax::Type::MAXIMIZER:
			if (child_value > best_value)
				best_value = child_value;
			break;

		case MinMax::Type::MINIMIZER:
			if (child_value < best_value)
				best_value = child_value;
			break;
		}

		if (child.is_best(depth, child_value))
			break;
	}
	this->_value = best_value;
}

bool MinMax::Node::is_best(int depth, double value)
{
	switch (this->_type)
	{
	case MinMax::Type::MINIMIZER:
		return value <= -depth;
	case MinMax::Type::MAXIMIZER:
		return value >= depth;
	default:
		throw MinMax::NodeError("Invalid node type");
	}
}

double MinMax::Node::get_value() const
{
	return this->_value;
}

void MinMax::Node::eval(int depth)
{
	int coef = (this->_type == MinMax::Type::MAXIMIZER) ? (1) : (-1);

	PlayerId winner = this->_referee.get_winner();
	if (winner == this->_pid)
		this->_value = coef * depth;
	else if (winner == ~this->_pid)
		this->_value = -coef * depth;
	else if (depth == 1)
		this->_value = 0.0;  // TODO: Some evaluation
	else
		this->_value = 0.0;
}
