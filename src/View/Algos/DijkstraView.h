#pragma once

#include "AlgoView.h"
#include "Dijkstra.h"

class DijkstraView : public AlgoView
{
public:
	DijkstraView();

	bool Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation) override;

	void DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo) override;
	void DrawGuiStatistics() override;

private:
	Dijkstra m_algo;

	// Options
	bool m_bDijkstraUseDiagonal;
};

