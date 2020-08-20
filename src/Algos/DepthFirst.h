#pragma once

#include "GridWorker.h"
#include "Utility.h"

class DepthFirst
{
public:
	static bool Execute(const GridWorker& Grid, bool bUseDiagonal, std::vector<std::pair<int, int>>& aFinalPath, OnDoingOperationFctPtr OnDoingOperation = DefaultOnDoingOperation);

private:
	struct SDatas
	{
		bool bProcessed = false;
		std::pair<int, int> vParent = { -1, -1 };
	};
};
