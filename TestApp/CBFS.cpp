#include "CBFS.h"



void CBFS::PathFinding(nodo * start, nodo * end, std::vector<nodo*>* path, int euristicType)
{
	(*start).m_reference = start;
	m_wait.push((*start));
	start->m_father = NULL;
	m_reviewed.push_back(start);
	path->clear();
	nodo temp;
	while (!m_wait.empty())
	{
		
		temp = m_wait.back();
		m_wait.pop();
		if (temp.m_reference == end)
		{
			break;
		}
		for (auto conection = temp.m_conections.begin(); conection != temp.m_conections.end(); conection++)
		{
			std::vector<nodo*>::iterator reviewedNodes;
			reviewedNodes = std::find(m_reviewed.begin(), m_reviewed.end(), (*conection).m_nodo);
			if (reviewedNodes == m_reviewed.end())
			{
				nodo newNodo = ((*(*conection).m_nodo));
				newNodo.m_reference = (*conection).m_nodo;
				newNodo.m_father = &temp;
				m_wait.push(newNodo);
			}
		}
		m_reviewed.push_back(temp.m_reference);
	}
	while (temp.m_father != NULL)
	{
		path->push_back(temp.m_reference);
		temp = temp.m_father;
	}
}

CBFS::CBFS()
{
}


CBFS::~CBFS()
{
}
