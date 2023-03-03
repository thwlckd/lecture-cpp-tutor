#include "Graph.h"

void Graph::vertices(VrtxList& vrtxLst)
{
	vrtxLst.clear();

	for (int i = 0; i < getNumVertices(); i++)
		vrtxLst.push_back(pVrtxArray[i]);  // VrtxList�� Graph�� ��� vertex�� ������� push_back
}

void Graph::edges(EdgeList& edges)
{
	EdgeItor eItor;
	Graph::Edge e;
	edges.clear();

	for (int i = 0; i < getNumVertices(); i++)
	{
		eItor = pAdjLstArray[i].begin();  // i��° EdgeList�� ù��° ���Ұ��� ����
		while (eItor != pAdjLstArray[i].end())
		{
			e = *eItor;
			edges.push_back(e);  // EdgeList�� Graph�� ��� edge�� ������� push_back
			eItor++;  // i��° EdgeList�� ���� ���ҷ� �̵�
		}
	}
}

void Graph::insertVertex(Vertex& v)
{
	int vID;

	vID = v.getID();
	if (pVrtxArray[vID] == NULL)
	{
		pVrtxArray[vID] = v;  // vID��° index�� vertex ����
	}
}

void Graph::insertEdge(Edge& e)
{
	Vertex vrtx_1, vrtx_2;
	Vertex* pVtx;
	int vID_1, vID_2;
	vrtx_1 = *e.getpVrtx_1(); vID_1 = vrtx_1.getID();
	vrtx_2 = *e.getpVrtx_2(); vID_2 = vrtx_2.getID();

	if (pVrtxArray[vID_1] == NULL)
		pVrtxArray[vID_1] = vrtx_1;  // vID_1��° index�� vrtx_1 ����
	if (pVrtxArray[vID_2] == NULL)
		pVrtxArray[vID_2] = vrtx_2;  // vID_2��° index�� vrtx_2 ����
	e.setpVrtx_1(&pVrtxArray[vID_1]);
	e.setpVrtx_2(&pVrtxArray[vID_2]);
	pAdjLstArray[vID_1].push_back(e);  // EdgeList�� e ����
}

void Graph::fprintGraph(ofstream& fout)
{
	int i, j;
	EdgeItor eItor;
	Graph::Edge e;
	int numOutgoingEdges;

	fout << this->getName() << " with " << this->getNumVertices() << " vertices has following connectivity :" << endl;
	for (i = 0; i < num_vertices; i++)
	{
		fout << " vertex (" << setw(3) << pVrtxArray[i].getName() << ") : ";  // print vertex name
		numOutgoingEdges = pAdjLstArray[i].size();
		eItor = pAdjLstArray[i].begin();
		while (eItor != pAdjLstArray[i].end())
		{
			e = *eItor;
			fout << e << " ";  // print edge
			eItor++;
		}
		fout << endl;
	}
}

void Graph::incidentEdges(Vertex v, EdgeList& edgeLst)
{
	Graph::Edge e;
	EdgeItor eItor;
	int vID = v.getID();

	eItor = pAdjLstArray[vID].begin();  // �ش� adjacent lists�� ù��° ����(edge) ����
	while (eItor != pAdjLstArray[vID].end())
	{
		e = *eItor;
		edgeLst.push_back(e);  // edgeLst�� �ش� edge push_back
		eItor++;  // goto next element(edge) in list
	}
}

bool Graph::isValidVrtxID(int vid)
{
	if ((vid >= 0) && (vid < num_vertices))
		return true;
	else
	{
		cout << "Vertex ID (" << vid << ") is invalid for Graph (" << getName() << ") with num_vertices (" << num_vertices << ")" << endl;
	}
}
