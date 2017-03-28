#pragma once
#include "CWalker.h"
#include <queue>
class CBFS :
	public CWalker
{
public:
	void PathFinding(nodo *start, nodo*end, std::vector<nodo*> *path, int euristicType);
	std::queue<nodo*> m_wait;

	CBFS();
	~CBFS();
};

