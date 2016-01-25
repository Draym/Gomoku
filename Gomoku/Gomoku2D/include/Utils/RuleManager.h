#pragma once

#include <vector>
#include "Utils\Tuple.h"
#include "referee\IReferee.hpp"
#include "Utils\Exception.h"

class RuleManager
{
public:
	class Name {
	public:
		static std::string PriseFinPartie() { return "Prise de fin de partie"; }
		static std::string DoubleTrois() { return "Les Double Trois"; }
		static std::string FreeStyle() { return "Free-style"; }
	};
public:
	static void init();
	static void reverse(std::string id);
	static std::vector<std::string> getRules();
	static Tuple<std::string, Rule, bool> getRule(std::string id);
public:
	static std::vector<Tuple<std::string, Rule, bool> > rules;
	static bool			p1;
	static bool			p2;
	static std::string	p1IAMethod;
	static std::string	p2IAMethod;
};

