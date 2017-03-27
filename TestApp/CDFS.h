#pragma once
#include "CWalker.h"
#include <stack>
class CDFS :
	public CWalker
{
public:
	void PathFinding(nodo *start, nodo*end, std::vector<nodo*> *path, int euristicType);
	std::stack<nodo*> m_wait;

	CDFS();
	~CDFS();
};

