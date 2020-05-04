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
	AStar m_algo;

	// Options
	bool m_bAStarUseDiagonal;
	EHeuristic m_eAStartHeuristic;
	float m_fAStarWeight;
};

