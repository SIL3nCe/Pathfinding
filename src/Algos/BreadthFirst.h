#pragma once

#include "GridWorker.h"
#include "Utility.h"

class BreadthFirst
{
public:
	bool Execute(const GridWorker& Grid, bool bUseDiagonal, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);

private:
	struct SDatas
	{
		bool bDiscovered = false;
		std::pair<int, int> vParent = { -1, -1 };
	};
};
