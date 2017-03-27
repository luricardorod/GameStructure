#pragma once
#include "CWalker.h"
#include <list>
class CBestFS :
	public CWalker
{
public:
	void PathFinding(nodo *start, nodo*end, std::vector<nodo*> *path, int euristicType);
	std::list<nodo*> m_wait;
	CBestFS();
	~CBestFS();
};

