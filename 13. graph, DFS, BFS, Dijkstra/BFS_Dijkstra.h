#pragma once

#ifndef BFS_DIJKSTRA_H
#define BFS_DIJKSTRA_H

#include "Graph.h"

using namespace std;

typedef Graph::Vertex Vertex;
typedef Graph::Edge Edge;
typedef std::list<Graph::Vertex> VrtxList;
typedef std::list<Graph::Edge> EdgeList;
typedef std::list<Graph::Vertex>::iterator VrtxItor;
typedef std::list<Graph::Edge>::iterator EdgeItor;

class BreadthFirstSearch
{
protected:
	Graph& graph;  // class Graph
	bool done;  // flag of search done
	int** ppDistMtrx;  // distance matrix: �ΰ��� vertex ���� �Ÿ����� ����

protected:
	void initialize();  // �ʱ� VrtxStatus: UN_VISITED, EdgeStatus: EDGE_UN_VISITED �� �ʱ�ȭ
	bool isValidvID(int vid) { return graph.isValidVrtxID(vid); }
	int getNumVertices() { return graph.getNumVertices(); }

public:
	BreadthFirstSearch(Graph& g)
		:graph(g) 
	{
		int num_nodes;
		num_nodes = g.getNumVertices();

		// DistMtrx �ʱ�ȭ: 2���� �迭 ����
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx = new int* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx[i] = new int[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			for (int j = 0; j < num_nodes; j++)
				ppDistMtrx[i][j] = PLUS_INF;  // distance �ʱⰪ: PLUS_INF
	}
	void initDistMtrx();  // distance matrix �ʱ�ȭ
	void fprintDistMtrx(ofstream& fout);  // distance matix ���
	//void DijkstraShortestPathTree(ofstream& fout, Vertex& s, int* pPrev);
	void DijkstraShortestPath(ofstream& fout, Vertex& s, Vertex& t, VrtxList& path);  // from s to t�� �ִܰ��: path�� ����
	Graph& getGraph() { return graph; }
	int** getppDistMtrx() { return ppDistMtrx; }
};
#endif