#include "Utils\IAManager.h"

std::vector<std::pair<std::string, IAI<Grid<Cell>>::Function>>	IAManager::iaMethods;


void IAManager::init() {
	iaMethods.push_back(std::make_pair("monteCarlo=Easy", AIFactory<Grid<Cell>>::MindGame::play_monteCarlo_easy));
	iaMethods.push_back(std::make_pair("monteCarlo=Medium", AIFactory<Grid<Cell>>::MindGame::play_monteCarlo_medium));
	iaMethods.push_back(std::make_pair("monteCarlo=Hard", AIFactory<Grid<Cell>>::MindGame::play_monteCarlo_hard));
	iaMethods.push_back(std::make_pair("BestChoice", AIFactory<Grid<Cell>>::MindGame::play_best));
	iaMethods.push_back(std::make_pair("RandomChoice", AIFactory<Grid<Cell>>::MindGame::play_random));
}

std::vector<std::string> IAManager::getMethodsId() {
	std::vector<std::string> result;

	for (std::size_t i = 0; i < iaMethods.size(); ++i) {
		result.push_back(iaMethods[i].first);
	}
	return result;
}

IAI<Grid<Cell>>::Function IAManager::getMethod(std::string id) {
	for (std::size_t i = 0; i < iaMethods.size(); ++i) {
		if (iaMethods[i].first == id)
			return iaMethods[i].second;
	}
	return AIFactory<Grid<Cell>>::MindGame::play_monteCarlo_easy;
}
