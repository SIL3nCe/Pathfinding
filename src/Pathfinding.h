#pragma once

#include "GridView.h"

enum class EPathfindingState
{
	GridUse,
	ExecAlgo,
	ExecAllAlgo,
};

enum class EAlgorithms
{
	AStar,
	AStarBidir,
	Dijksta,
	BreadthFirst,

	Max
};

class AlgoView;

class Pathfinding
{
public:
	Pathfinding();
	~Pathfinding();

	void Update(float dt);

	void SetState(EPathfindingState eNewState);

	void Draw(sf::RenderWindow& window);

	void OnKeyPressed(sf::Keyboard::Key eKey);

	void OnMouseClicked(int posX, int posY);
	void OnMouseMoved(int posX, int posY);
	void OnMouseReleased();

	static void OnDoingOperation(EOperations eOperation, const std::pair<int, int>& vCellCoord);
	static void OnDoingOperationCounter(EOperations eOperation, const std::pair<int, int>& vCellCoord);

private:
	bool DrawAStep();
	bool UndrawAStep();
	void DrawGUI();

	float ComputePathLength(const std::vector<std::pair<int, int>>& aPath) const;

private:
	EPathfindingState m_eState;

	GridView m_grid;

	// Algos
	std::vector<AlgoView*> m_aAlgoViews;

	EAlgorithms m_eSelectedAlgo;
	
	static std::vector<SOperation> m_aOperationStack;
	static int m_stepCounter;

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
};
