#pragma once
#include "CWalker.h"
#include <queue>
class CBFS :
	public CWalker
{
public:

	virtual void InsertNodoInWait(node* newNodo, nodeInfo *father);
	virtual void ClearWait();
	virtual bool EmptyListWait();
	virtual nodeInfo NextNodoInWait();

	std::queue<nodeInfo> m_wait;

	CBFS();
	virtual ~CBFS();
};

