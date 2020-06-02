#pragma once

#include "GridWorker.h"
#include "Utility.h"

enum class EHeuristic : unsigned int;

class AStar
{
public:
	static bool Execute(const GridWorker& Grid, bool bUseDiagonal, EHeuristic eHeuristic, float fWeight, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);
	static bool ExecuteBidirectional(const GridWorker& Grid, bool bUseDiagonal, EHeuristic eHeuristic, float fWeight, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);

private:
	static float ComputeHeuristic(const std::pair<int, int>& start, const std::pair<int, int>& end, EHeuristic eHeuristic, float fWeight);

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

	struct SDatasBidir
	{
		bool bClosed = false;
		bool bQueued = false;
		bool bQueuedByStart = false;
		float fHeuristic = -1.0f; // h(n)
		float fCost = static_cast<float>(UINT_MAX - 1); // g(n)
		float fScore = static_cast<float>(UINT_MAX - 1); // f(n)
		std::pair<int, int> vPrevious = { -1, -1 };
	};
};
