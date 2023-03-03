#pragma once

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

#define PLUS_INF INT_MAX/2

enum VrtxStatus { UN_VISITED, VISITED, VRTX_NOT_FOUND };
enum EdgeStatus { DISCOVERY, BACK, CROSS, EDGE_UN_VISITED, EDGE_VISITED, EDGE_NOT_FOUND };

class Graph
{
public:
	class Vertex;
	class Edge;
	typedef std::list<Graph::Vertex> VrtxList;
	typedef std::list<Graph::Edge> EdgeList;
	typedef std::list<Vertex>::iterator VrtxItor;
	typedef std::list<Edge>::iterator EdgeItor;

public:
	class Vertex  // Graph::Vertex
	{
		friend ostream& operator<<(ostream& fout, Vertex v)
		{
			fout << v.getName();
			return fout;
		}
	public:
		Vertex()
			: name(), ID(-1)
		{ }
		Vertex(string n, int id) 
			: name(n), ID(id)
		{ }
		Vertex(int id)
			: ID(id)
		{ }
		string getName() { return name; }
		void setName(string c_name) { name = c_name; }
		int getID() { return ID; }
		void setID(int id) { ID = id; }
		void setVrtxStatus(VrtxStatus vs) { vrtxStatus = vs; }
		VrtxStatus getvrtxStatus() { return vrtxStatus; }
		bool operator==(Vertex v) { return ((ID == v.getID()) && (name == v.getName())); }
		bool operator!=(Vertex v) { return ((ID != v.getID()) || (name != v.getName())); }
	private:
		string name;
		int ID;
		VrtxStatus vrtxStatus;
	}; // end class Vertex

public:
	class Edge  // Graph::Edge
	{
		friend ostream& operator<<(ostream& fout, Edge& e)
		{
			fout << "Edge(" << setw(2) << *e.getpVrtx_1() << ", " << setw(2)
				<< *e.getpVrtx_2() << ", " << setw(4) << e.getDistance() << ")";
			return fout;
		}
	public:
		Edge() 
			: pVrtx_1(NULL), pVrtx_2(NULL), distance(PLUS_INF) 
		{ }
		Edge(Vertex& v1, Vertex& v2, int d) 
			:distance(d), pVrtx_1(&v1), pVrtx_2(&v2), edgeStatus(EDGE_UN_VISITED)
		{ }
		void endVertices(VrtxList& vrtxLst)  // edge로 연결된 두 Vertex을 VrtList에 push_back
		{
			vrtxLst.push_back(*pVrtx_1);
			vrtxLst.push_back(*pVrtx_2);
		}
		Vertex opposite(Vertex v)  // Vertex v와 edge로 연결된 인접 Vertex 반환
		{
			if (v == *pVrtx_1)
				return *pVrtx_2;
			else if (v == *pVrtx_2)
				return *pVrtx_1;
			else {
				//cout << "Error in opposite()" << endl;
				return Vertex(NULL);
			}
		}
		Vertex* getpVrtx_1() { return pVrtx_1; }
		Vertex* getpVrtx_2() { return pVrtx_2; }
		int getDistance() { return distance; }
		void setpVrtx_1(Vertex* pV) { pVrtx_1 = pV; }
		void setpVrtx_2(Vertex* pV) { pVrtx_2 = pV; }
		void setDistance(int d) { distance = d; }
		bool operator!=(Edge e) 
		{
			return ((pVrtx_1 != e.getpVrtx_1()) || (pVrtx_2 != e.getpVrtx_2()));
		}
		bool operator==(Edge e) 
		{
			return ((pVrtx_1 == e.getpVrtx_1()) && (pVrtx_2 == e.getpVrtx_2()));
		}
		void setEdgeStatus(EdgeStatus es) { edgeStatus = es; }
		EdgeStatus getEdgeStatus() { return edgeStatus; }
	private:
		Vertex* pVrtx_1;  // edge로 연결된 인접 Vertex1
		Vertex* pVrtx_2;  // edge로 연결된 인접 Vertex2
		int distance;  // distance between Vertex1 and Vertex2
		EdgeStatus edgeStatus;
	}; // end class Edge

public:
	Graph() 
		: name(""), pVrtxArray(NULL), pAdjLstArray(NULL)
	{ }
	Graph(string nm, int num_nodes) 
		: name(nm), pVrtxArray(NULL), pAdjLstArray(NULL)
	{
		num_vertices = num_nodes;
		pVrtxArray = new Graph::Vertex[num_vertices];
		for (int i = 0; i < num_nodes; i++)
			pVrtxArray[i] = NULL;
		pAdjLstArray = new EdgeList[num_vertices];
		for (int i = 0; i < num_vertices; i++)
			pAdjLstArray[i].clear();
	}
	string getName() { return name; }
	void vertices(VrtxList& vrtxLst);  // vrtxLst에 Graph의 모든 Vertex를 순서대로 담아주는 함수
	void edges(EdgeList&);  // vrtxLst에 Graph의 모든 edge를 순서대로 담아주는 함수
	//bool isAdjacentTo(Vertex v, Vertex w);
	void insertVertex(Vertex& v);  // insert vertext to pVrtxArray[v.getID()]
	void insertEdge(Edge& e);  // push_back edge to pAdjLstArray 
	//void eraseEdge(Edge e);
	//void eraseVertex(Vertex v);
	int getNumVertices() { return num_vertices; }
	void incidentEdges(Vertex v, EdgeList& edges);  // vertex의 incidentEdges(인접 edges)를 EdgeList에 저장
	Vertex* getpVrtxArray() { return pVrtxArray; }
	EdgeList* getpAdjLstArray() { return pAdjLstArray; }
	void fprintGraph(ofstream& fout);  // 그래프의 모든 vertex와 인접 egde들 출력
	bool isValidVrtxID(int vid);  // (vid >= 0) && (vid < num_vertices)
private:
	string name;
	Vertex* pVrtxArray;  // vertex 배열의 포인터
	EdgeList* pAdjLstArray;  // 인접 edges 배열(adjacent lists)의 포인터 
	int num_vertices;
};

#endif