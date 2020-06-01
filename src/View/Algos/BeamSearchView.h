#pragma once

#include "AlgoView.h"
#include "BeamSearch.h"

class BeamSearchView : public AlgoView
{
public:
	BeamSearchView();

	bool Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation) override;

	void DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo) override;
	void DrawGuiStatistics() override;

private:
	BeamSearch m_algo;

	bool m_bUseDiagonal;
	EHeuristic m_eHeuristic;
	float m_fWeight;
	int m_beamWidth;
};

