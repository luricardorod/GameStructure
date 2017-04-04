#include "CBFS.h"

void CBFS::InsertNodoInWait(node* newNodo, nodeInfo *father)
{
	bool flag = true;
	for (auto i = m_reviewed.begin(); i != m_reviewed.end(); i++)
	{
		if (i->m_reference == newNodo)
		{
			flag = false;
			break;
		}
	}
	if (flag)
	{
		nodeInfo temp;
		temp.m_father = father;
		temp.m_reference = newNodo;
		m_reviewed.push_back((*father));
	}
}

void CBFS::ClearWait()
{
	while (!m_wait.empty())
	{
		m_wait.pop();
	}
}

bool CBFS::EmptyListWait()
{
	return m_wait.empty();
}

nodeInfo CBFS::NextNodoInWait()
{
	nodeInfo temp;
	if (m_wait.empty())
	{
		temp.m_reference = NULL;
	}
	else
	{
		temp = m_wait.front();
		m_wait.pop();
	}
	return temp;
}

CBFS::CBFS()
{
}


CBFS::~CBFS()
{
}
