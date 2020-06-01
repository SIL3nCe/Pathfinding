#pragma once

#include "GridWorker.h"
#include "Utility.h"

enum class EHeuristic : unsigned int;

class BeamSearch
{
public:
	bool Execute(const GridWorker& Grid, bool bUseDiagonal, EHeuristic eHeuristic, float fWeight, int beamWidth, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);

private:
	float ComputeHeuristic(const std::pair<int, int>& start, const std::pair<int, int>& end, EHeuristic eHeuristic, float fWeight);

private:
	struct SDatas
	{
		bool bClosed = false;
		bool bQueued = false;
		float fHeuristic = -1.0f; // h(n)
		float fCost = static_cast<float>(UINT_MAX - 1); // g(n)
		float fScore = static_cast<float>(UINT_MAX - 1); // f(n)
		std::pair<int, int> vPrevious = { -1, -1 };
	};

	std::vector<std::pair<int, int>> m_aNeighbours;
};
