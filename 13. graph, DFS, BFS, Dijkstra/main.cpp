/*
*Lab13_21720956_박창협
*Author : 박창협
*Programed on December. 04. 2020
*class Graph, BFS(Dijkstra 알고리즘)
*/

#include "Graph.h"
#include "BFS_Dijkstra.h"

#define NUM_NODES 7
#define NUM_EDGES 26

void main()
{
	ofstream fout; fout.open("output.txt"); if (fout.fail())
	{
		cout << "Failed to open output.txt file !!" << endl;
		exit;
	}

	Vertex v[NUM_NODES] = // 7 nodes
	{ Vertex("SF", 0), Vertex("LA", 1), Vertex("DLS", 2), Vertex("CHG", 3), Vertex("MIA", 4), Vertex("NY", 5), Vertex("BOS", 6) };
	Graph::Edge edges[NUM_EDGES] =
	{
		Edge(v[0], v[1], 337), Edge(v[1], v[0], 337),
		Edge(v[0], v[2], 1464), Edge(v[2], v[0], 1464),
		Edge(v[0], v[3], 1846), Edge(v[3], v[0], 1846),
		Edge(v[0], v[6], 2704), Edge(v[6], v[0], 2704),
		Edge(v[1], v[2], 1235), Edge(v[2], v[1], 1235),
		Edge(v[1], v[4], 2342), Edge(v[4], v[1], 2342),
		Edge(v[2], v[3], 802), Edge(v[3], v[2], 802),
		Edge(v[2], v[4], 1121), Edge(v[4], v[2], 1121),
		Edge(v[3], v[5], 740), Edge(v[5], v[3], 740),
		Edge(v[3], v[6], 867), Edge(v[6], v[3], 867),
		Edge(v[5], v[4], 1090), Edge(v[4], v[5], 1090),
		Edge(v[5], v[6], 187), Edge(v[6], v[5], 187),
		Edge(v[4], v[6], 1258), Edge(v[6], v[4], 1258),
	};

	int test_start = 1;
	int test_end = 6;
	Graph simpleGraph("GRAPH_SIMPLE_USA_7_NODES", NUM_NODES);

	fout << "Inserting vertices .." << endl;
	for (int i = 0; i < NUM_NODES; i++) 
	{
		simpleGraph.insertVertex(v[i]);
	}
	VrtxList vtxLst;
	simpleGraph.vertices(vtxLst);  // set vtxLst
	int count = 0;

	fout << "Inserted vertices: ";
	for (VrtxItor vItor = vtxLst.begin(); vItor != vtxLst.end(); ++vItor) 
	{
		fout << *vItor << ", ";  // print VrtxList
	}
	fout << endl;

	fout << "Inserting edges .." << endl;
	for (int i = 0; i < NUM_EDGES; i++)
	{
		simpleGraph.insertEdge(edges[i]);
	}

	fout << "Inserted edges: " << endl;
	count = 0;
	EdgeList egLst;
	simpleGraph.edges(egLst);
	for (EdgeItor p = egLst.begin(); p != egLst.end(); ++p)
	{
		count++;
		fout << *p << ", ";  // print EdgeList
		if (count % 5 == 0)
			fout << endl;
	}
	fout << endl;

	fout << "Print out Graph based on Adjacency List .." << endl;
	simpleGraph.fprintGraph(fout);  // print graph

	BreadthFirstSearch bfsGraph(simpleGraph);
	fout << "\nTesting Breadth First Search with Dijkstra Algorithm" << endl; 
	bfsGraph.initDistMtrx();  // simpleGraph로 DistMtrx 초기화
	bfsGraph.fprintDistMtrx(fout);  // print distance matix

	VrtxList path;
	path.clear();
	fout << "\nDijkstra Shortest Path Finding from " << v[test_start].getName() << " to " << v[test_end].getName() << " .... " << endl;
	bfsGraph.DijkstraShortestPath(fout, v[test_start], v[test_end], path);  // from test_start to test_end 최단경로: path에 저장
	fout << "Path found by DijkstraShortestPath from " << v[test_start] << " to " << v[test_end] << " : ";
	for (VrtxItor vItor = path.begin(); vItor != path.end(); ++vItor)
		fout << *vItor << " -> ";  // 최단경로 경유지 출력
	fout << endl;
	fout.close();
}