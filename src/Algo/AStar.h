#pragma once

#include "../GridWorker.h"
#include "../Utility.h"

enum class EHeuristic : unsigned int;

class AStar
{
public:
	std::vector<std::pair<int, int>>& Execute(const GridWorker& Grid, bool bUseDiagonal, EHeuristic eHeuristic, float fWeight, void(*OnDoingOperation)(EOperations, const std::pair<int, int>&) = DefaultOnDoingOperation);

private:
	float ComputeHeuristic(const std::pair<int, int>& start, const std::pair<int, int>& end, EHeuristic eHeuristic, float fWeight);

private:
	struct SDatas
	{
		bool bClosed;
		int heuristique;
		float cost;
		std::pair<int, int> vPrevious;
	};
	
	std::vector<std::pair<int, int>> m_aNeighbours;

	std::vector<std::pair<int, int>> m_aFinalPath;
};
