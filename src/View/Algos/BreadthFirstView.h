#pragma once

#include "AlgoView.h"
#include "BreadthFirst.h"

class BreadthFirstView : public AlgoView
{
public:
	BreadthFirstView();

	bool Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation) override;

	void DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo) override;
	void DrawGuiStatistics() override;

private:
	BreadthFirst m_algo;
	
	bool m_bBreadthFirstUseDiagonal;
};

