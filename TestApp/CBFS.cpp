#include "CBFS.h"

void CBFS::InsertNodoInWait(node* newNodo, nodeInfo *father)
{
	bool flag = true;
	for (auto i = m_reviewed.begin(); i != m_reviewed.end(); i++)
	{
		if ((*i)->m_reference == newNodo)
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
		m_reviewed.push_back(&temp);
		m_wait.push(&temp);
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

nodeInfo* CBFS::NextNodoInWait()
{
	if (m_wait.empty())
	{
		return NULL;
	}

	nodeInfo* temp = m_wait.front();
	m_wait.pop();

	return temp;
}

CBFS::CBFS()
{
	m_reviewed.reserve(200);
}


CBFS::~CBFS()
{
}
