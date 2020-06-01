#pragma once

#include "../Pathfinding.h"
#include "GridWorker.h"

#include "imgui.h"
#include "imgui-SFML.h"

enum class EAlgorithms;

class AlgoView
{
public:
	AlgoView();

	virtual bool Execute(const GridWorker& Grid, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);

	virtual void DrawGuiAlgorithm(EAlgorithms& eSelectedAlgo);
	virtual void DrawGuiStatistics();

	void SetStatsStep(float fSteps);
	void SetStatsLength(float fLength);
	void ResetStats();

public:

	// Statistics
	float m_fTime;
	int m_steps;
	float m_fLength;
	sf::Clock m_algoClock;
};