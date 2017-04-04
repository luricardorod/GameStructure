#include "CBestFS.h"
//
//
//
//void CBestFS::PathFinding(node * start, node * end, std::vector<nodo*>* path, int euristicType)
//{
//	(*start).m_value = (*start).Evaluateheuristics(&(*end).m_position, euristicType);
//	m_wait.push_front(start);
//	start->m_father = NULL;
//	m_reviewed.push_back(start);
//	path->clear();
//	nodo *temp;
//
//	while (!m_wait.empty())
//	{
//		
//		temp = m_wait.front();
//		m_wait.pop_front();
//		if (temp == end)
//		{
//			break;
//		}
//		for (auto conection = temp->m_conections.begin(); conection != temp->m_conections.end(); conection++)
//		{
//			std::vector<nodo*>::iterator reviewedNodes;
//			reviewedNodes = std::find(m_reviewed.begin(), m_reviewed.end(), (*conection).m_nodo);
//			if (reviewedNodes == m_reviewed.end())
//			{
//				float tempValue = (*conection).m_nodo->Evaluateheuristics(&(*end).m_position, euristicType);
//				std::list<nodo*>::iterator position;
//				bool flag = true;
//				for (position = m_wait.begin(); position != m_wait.end(); position++) {
//					if ((*position) == (*conection).m_nodo)
//					{
//						flag = false;
//						break;
//					}
//					if (tempValue < (*position)->m_value)
//					{
//						break;
//					}
//				}
//				if (position == m_wait.end())
//				{
//					(*conection).m_nodo->m_value = tempValue;
//					(*conection).m_nodo->m_father = temp;
//					m_wait.push_back((*conection).m_nodo);
//				}
//				else if (flag)
//				{
//					(*conection).m_nodo->m_value = tempValue;
//					(*conection).m_nodo->m_father = temp;
//					m_wait.insert(position, (*conection).m_nodo);
//				}
//			}
//		}
//		m_reviewed.push_back(temp);
//	}
//	while (temp != NULL)
//	{
//		path->push_back(temp);
//		temp = temp->m_father;
//	}
//}
//
//CBestFS::CBestFS()
//{
//}
//
//
//CBestFS::~CBestFS()
//{
//}
