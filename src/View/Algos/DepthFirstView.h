#pragma once

#include "AlgoView.h"
#include "DepthFirst.h"

class DepthFirstView : public AlgoView
{
public:
	DepthFirstView();

	bool Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation) override;

	void DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo) override;
	void DrawGuiStatistics() override;

private:

	bool m_bUseDiagonal;
};

