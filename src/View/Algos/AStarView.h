#pragma once

#include "AlgoView.h"
#include "AStar.h"

class AStarView : public AlgoView
{
public:
	AStarView();

	bool Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation) override;

	void DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo) override;
	void DrawGuiStatistics() override;

private:
	
	bool m_bUseDiagonal;
	EHeuristic m_eHeuristic;
	float m_fWeight;
};

