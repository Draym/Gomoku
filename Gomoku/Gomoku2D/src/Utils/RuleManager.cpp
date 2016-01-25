#include "Utils\RuleManager.h"

std::vector<Tuple<std::string, Rule, bool> >	RuleManager::rules;
bool											RuleManager::p1 = true;
bool											RuleManager::p2 = true;
std::string										RuleManager::p1IAMethod = "";
std::string										RuleManager::p2IAMethod = "";

void	RuleManager::init()
{
	rules.push_back(Tuple<std::string, Rule, bool>(Name::PriseFinPartie(), Rule::OPT_BREAK_FIVE, true));
	rules.push_back(Tuple<std::string, Rule, bool>(Name::DoubleTrois(), Rule::OPT_DOUBLE_THREE, true));
	rules.push_back(Tuple<std::string, Rule, bool>(Name::FreeStyle(), Rule::OPT_FREESTYLE, true));
}

void	RuleManager::reverse(std::string id)
{
	for (std::size_t i = 0; i < rules.size(); ++i) {
		if (rules[i].first == id)
			rules[i].third = !rules[i].third;
	}
}

std::vector<std::string>	RuleManager::getRules() {
	std::vector<std::string>	result;

	for (std::size_t i = 0; i < rules.size(); ++i) {
		result.push_back(rules[i].first);
	}
	return result;
}

Tuple<std::string, Rule, bool> RuleManager::getRule(std::string id)
{
	for (std::size_t i = 0; i < rules.size(); ++i) {
		if (rules[i].first == id)
			return rules[i];
	}
	return Tuple<std::string, Rule, bool>("", Rule::BASE, false);
}
