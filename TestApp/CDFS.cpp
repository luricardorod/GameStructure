#include "CDFS.h"


//
//void CDFS::PathFinding(nodo * start, nodo * end, std::vector<nodo*>* path, int euristicType)
//{
//	m_wait.push(start);
//	start->m_father = NULL;
//	m_reviewed.push_back(start);
//	path->clear();
//	nodo *temp;
//	while (!m_wait.empty())
//	{
//		
//		temp = m_wait.top();
//		m_wait.pop();
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
//				(*conection).m_nodo->m_father = temp;
//				m_wait.push((*conection).m_nodo);
//				m_reviewed.push_back((*conection).m_nodo);
//
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
//CDFS::CDFS()
//{
//}
//
//
//CDFS::~CDFS()
//{
//}
