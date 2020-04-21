#pragma once

#include "../GridWorker.h"
#include "../Utility.h"

enum class EHeuristic : unsigned int;

class AStar
{
public:
	void Execute(const GridWorker& Grid, bool bUseDiagonal, EHeuristic eHeuristic, float fWeight, std::vector<std::pair<int, int>> & aFinalPath, void(*OnDoingOperation)(EOperations, const std::pair<int, int>&) = DefaultOnDoingOperation);

private:
	float ComputeHeuristic(const std::pair<int, int>& start, const std::pair<int, int>& end, EHeuristic eHeuristic, float fWeight);

private:
	struct SDatas
	{
		bool bClosed;
		bool bQueued;
		float fHeuristic; // h(n)
		float fCost; // g(n)
		float fScore; // f(n)
		std::pair<int, int> vPrevious;
	};
	
	std::vector<std::pair<int, int>> m_aNeighbours;
};
