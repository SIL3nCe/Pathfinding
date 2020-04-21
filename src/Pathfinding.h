#pragma once

#include "GridView.h"

#include "Algo/Dijkstra.h"
#include "Algo/BreadthFirst.h"
#include "Algo/AStar.h"

enum class EPathfindingState
{
	GridUse,
	ExecAlgo,
};

enum class EAlgorithms
{
	AStar,
	Dijksta,
	BreadthFirst
};

class Pathfinding
{
public:

	Pathfinding();

	void Update(float dt);

	void Draw(sf::RenderWindow& window);

	void SetState(EPathfindingState eNewState);

	void OnKeyPressed(sf::Keyboard::Key eKey);

	void OnMouseClicked(int posX, int posY);
	void OnMouseMoved(int posX, int posY);
	void OnMouseReleased();

	static void OnDoingOperation(EOperations eOperation, const std::pair<int, int>& vCellCoord);

private:
	bool DrawAStep();
	bool UndrawAStep();
	void DrawGUI();

private:
	EPathfindingState m_eState;

	GridView m_grid;

	// Algos
	EAlgorithms m_eSelectedAlgo;
	Dijkstra m_algo_Dijkstra;
	bool m_bDijkstraUseDiagonal;

	BreadthFirst m_algo_BreadthFirst;
	bool m_bBreadthFirstUseDiagonal;

	AStar m_algo_AStar;
	bool m_bAStarUseDiagonal;
	EHeuristic m_eAStartHeuristic;
	float m_fAStarWeight;

	static std::vector<SOperation> m_aOperationStack;

	// Operation drawing
	int m_currentStep;
	bool m_bRewind;
	bool m_bPause;

	int m_frameBeforeDrawing;
	int m_operationsToDrawPerFrames;
	int m_frameCounter;

	sf::Texture buttonPlay;
	sf::Texture buttonRewind;
	sf::Texture buttonPause;
	sf::Texture buttonNext;
	sf::Texture buttonPrevious;

	// Statistics
	float m_fTime;
	int m_steps;
	float m_fLength;
	sf::Clock m_algoClock;
};
