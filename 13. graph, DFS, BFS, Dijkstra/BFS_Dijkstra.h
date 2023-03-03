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
	int** ppDistMtrx;  // distance matrix: 두개의 vertex 사이 거리정보 저장

protected:
	void initialize();  // 초기 VrtxStatus: UN_VISITED, EdgeStatus: EDGE_UN_VISITED 로 초기화
	bool isValidvID(int vid) { return graph.isValidVrtxID(vid); }
	int getNumVertices() { return graph.getNumVertices(); }

public:
	BreadthFirstSearch(Graph& g)
		:graph(g) 
	{
		int num_nodes;
		num_nodes = g.getNumVertices();

		// DistMtrx 초기화: 2차원 배열 생성
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx = new int* [num_nodes];
		for (int i = 0; i < num_nodes; i++)
			ppDistMtrx[i] = new int[num_nodes];
		for (int i = 0; i < num_nodes; i++)
			for (int j = 0; j < num_nodes; j++)
				ppDistMtrx[i][j] = PLUS_INF;  // distance 초기값: PLUS_INF
	}
	void initDistMtrx();  // distance matrix 초기화
	void fprintDistMtrx(ofstream& fout);  // distance matix 출력
	//void DijkstraShortestPathTree(ofstream& fout, Vertex& s, int* pPrev);
	void DijkstraShortestPath(ofstream& fout, Vertex& s, Vertex& t, VrtxList& path);  // from s to t의 최단경로: path에 저장
	Graph& getGraph() { return graph; }
	int** getppDistMtrx() { return ppDistMtrx; }
};
#endif