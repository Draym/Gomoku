#pragma once

#include <string>
#include <stdexcept>
#include <functional>

#include "Grid.hpp"

bool getline_when(std::istream& stream, std::string& line, std::function<bool(std::string const&)> const& assessment)
{
    line.clear();
    while (!assessment(line))
    {
        std::getline(stream, line);
        if (stream.eof() || stream.fail())
            return false;
    }
    return true;
}

template <typename _Counter>
bool getline_when(std::istream& stream, std::string& line, std::function<bool(std::string const&)> const& assessment, _Counter& count)
{
    line.clear();
    do
    {
        std::getline(stream, line);
        if (stream.eof() || stream.fail())
            return false;
        count++;
    }
    while (!assessment(line));
    return true;
}

template <typename _auto>
void read_file(std::istream& stream, _auto& table)
{
    std::size_t line_number = 0;
    std::string line;
    
    while (true)
    {
        if (!getline_when(stream, line, [](std::string const& str) -> bool { return !str.empty(); }, line_number))
        {
            if (stream.eof())
                break;
            else if (stream.fail())
                throw std::runtime_error("Error at line " + std::to_string(line_number) + " : Failure reading line");
        }
        
        if (table.height() != 0 && table.width() != line.size())
            throw std::runtime_error("Error at line " + std::to_string(line_number) + " : Too long line");
        table.resize(line.size(), table.height() + 1);
        for (std::string::size_type i = 0 ; i < line.size() ; i++)
        {
            switch (line[i])
            {
                case '0':
					table(i, table.height() - 1).player_id = PlayerId::None;
					break;
				case '1':
					table(i, table.height() - 1).player_id = PlayerId::P1;
					break;
				case '2':
                    table(i, table.height() - 1).player_id = PlayerId::P2;
                    break;
                default:
                    throw std::runtime_error("Error at line " + std::to_string(line_number) + " : Wrong symbol at position [" + std::to_string(i) + ']');
                    break;
            }
			table(i, table.height() - 1).breakable = 0;
			table(i, table.height() - 1).data = 0;
        }
    }
}
