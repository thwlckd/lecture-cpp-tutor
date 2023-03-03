#include "BFS_Dijkstra.h"

void BreadthFirstSearch::initialize()
{
	Vertex* pVrtx = getGraph().getpVrtxArray();
	VrtxList vrtxLst;
	graph.vertices(vrtxLst);
	int num_vertices = graph.getNumVertices();

	for (int vID = 0; vID < num_vertices; vID++)
		pVrtx[vID].setVrtxStatus(UN_VISITED);  // �ʱ� VrtxStatus: UN_VISITED

	EdgeList edges;
	graph.edges(edges);
	for (EdgeItor pe = edges.begin(); pe != edges.end(); ++pe)
		pe->setEdgeStatus(EDGE_UN_VISITED);  // �ʱ� EdgeStatus: EDGE_UN_VISITED
}

void BreadthFirstSearch::initDistMtrx()
{
	int** ppDistMtrx;
	int* pLeaseCostMtrx;
	int num_nodes;
	Vertex* pVrtxArray;
	EdgeList* pAdjLstArray;
	int curVID, vID;
	num_nodes = getNumVertices();
	pVrtxArray = graph.getpVrtxArray();
	pAdjLstArray = graph.getpAdjLstArray();
	ppDistMtrx = getppDistMtrx();

	for (int i = 0; i < num_nodes; i++)
	{
		curVID = pVrtxArray[i].getID();  // get current vertex ID
		EdgeItor pe = pAdjLstArray[curVID].begin();  // ���� vertex�� adjacent lists ù��° ���� ����
		while (pe != pAdjLstArray[curVID].end())
		{
			vID = (*(*pe).getpVrtx_2()).getID();  // ���� vertex�� edge�� ����� vertex2�� ID �޾ƿ�
			ppDistMtrx[curVID][vID] = (*pe).getDistance();  // ppDistMtrx�� distance ���� ����
			pe++;  // goto next edge
		}
		ppDistMtrx[curVID][curVID] = 0;  // ���� vertex: �Ÿ� 0
	}
}

void BreadthFirstSearch::fprintDistMtrx(ofstream& fout)
{
	int** ppDistMtrx;
	Vertex* pVrtxArray;
	int num_nodes;
	int dist;
	int vID;
	string vName;
	pVrtxArray = graph.getpVrtxArray();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();

	// first line
	fout << "\nDistance Matrix of Graph (" << graph.getName() << ") :" << endl;
	fout << "      |";
	for (int i = 0; i < num_nodes; i++) 
	{
		vName = pVrtxArray[i].getName();  // print vertex name 
		fout << setw(5) << vName;
	}
	fout << endl;
	fout << "------+";
	for (int i = 0; i < num_nodes; i++)
		fout << "-----";
	fout << endl;

	for (int i = 0; i < num_nodes; i++) 
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName << " |";
		for (int j = 0; j < num_nodes; j++) 
		{
			dist = ppDistMtrx[i][j];
			if (dist == PLUS_INF)  // �ΰ��� vertex�� edge�� ������� x
				fout << setw(5) << " +oo";
			else
				fout << setw(5) << dist;  // print distance
		}
		fout << endl;
	}
	fout << endl;
}

enum BFS_PROCESS_STATUS { NOT_SELECTED, SELECTED };  // SELECTED: cloud �ȿ� ���Ե� vertex

void BreadthFirstSearch::DijkstraShortestPath(ofstream& fout, Vertex& start, Vertex& target, VrtxList& path)
{
	int** ppDistMtrx;
	int* pLeastCost;  // LeastCost ���
	int num_nodes, num_selected, minID, minCost;
	BFS_PROCESS_STATUS* pBFS_Process_Stat;
	int* pPrev;  // LeastCost ����� ���� ���� ���
	Vertex* pVrtxArray;
	Vertex vrtx, * pPrevVrtx, v;
	Edge e;
	int start_vID, target_vID, curVID, vID;
	EdgeList* pAdjLstArray;

	pVrtxArray = graph.getpVrtxArray();
	pAdjLstArray = graph.getpAdjLstArray();
	start_vID = start.getID();
	target_vID = target.getID();
	num_nodes = getNumVertices();
	ppDistMtrx = getppDistMtrx();
	pLeastCost = new int[num_nodes];
	pPrev = new int[num_nodes];
	pBFS_Process_Stat = new BFS_PROCESS_STATUS[num_nodes];

	// start node�� �������� �ʱ�ȭ
	for (int i = 0; i < num_nodes; i++)
	{
		pLeastCost[i] = ppDistMtrx[start_vID][i];
		pPrev[i] = start_vID;
		pBFS_Process_Stat[i] = NOT_SELECTED;
	}
	pBFS_Process_Stat[start_vID] = SELECTED;
	num_selected = 1;
	path.clear();

	// print first line
	int round = 0;
	int cost;
	string vName;
	fout << "Dijkstra::Least Cost from Vertex (" << start.getName() << ") at each round : " << endl;
	fout << "           |";
	for (int i = 0; i < num_nodes; i++)
	{
		vName = pVrtxArray[i].getName();
		fout << setw(5) << vName;  // print vertex name
	}
	fout << endl;
	fout << "-----------+";
	for (int i = 0; i < num_nodes; i++)
	{
		fout << setw(5) << "-----";
	}
	fout << endl;

	while (num_selected < num_nodes)
	{
		round++;
		fout << "round [" << setw(2) << round << "] |";
		minID = -1;
		minCost = PLUS_INF;

		// ���� cost ���� ���� ��� ã�� cloud�� ����
		for (int i = 0; i < num_nodes; i++)
		{
			if ((pLeastCost[i] < minCost) && (pBFS_Process_Stat[i] != SELECTED))  // select ���� ���� ����� ���� cost�� ���� ���� ��� �湮��
			{
				minID = i;  // set current ID with new minID
				minCost = pLeastCost[i];  // set current Cost with new minCost
			}
		}
		if (minID == -1)
		{
			fout << "Error in Dijkstra() -- found not connected vertex !!" << endl;
			break;
		}
		else  // minID: �����ִ� ��� �� �������� ���� ���� ���
		{
			pBFS_Process_Stat[minID] = SELECTED;
			num_selected++;
			if (minID == target_vID)  // LeastCost ��� �ϼ�
			{
				fout << endl << "reached to the target node (" << pVrtxArray[minID].getName() << ") at Least Cost = " << minCost << endl;
				vID = minID;
				do
				{
					vrtx = pVrtxArray[vID];
					path.push_front(vrtx);  // LeastCost ������ path�� push_front
					vID = pPrev[vID];  // goto previous ������
				} while (vID != start_vID);
				vrtx = pVrtxArray[vID];
				path.push_front(vrtx);  // path�� ù��° ����: start node
				break;
			}
		}

		/* Edge relaxation */
		//int pLS, ppDistMtrx_i;
		for (int i = 0; i < num_nodes; i++)
		{
			//pLS = pLeastCost[i];
			//ppDistMtrx_i = ppDistMtrx[minID][i];
			if ((pBFS_Process_Stat[i] != SELECTED) && (pLeastCost[i] > (pLeastCost[minID] + ppDistMtrx[minID][i])))  // i�� �����ϴ� less cost ������ �߽߰�
			{
				pPrev[i] = minID;
				pLeastCost[i] = pLeastCost[minID] + ppDistMtrx[minID][i];  // less cost ������ ����
			}
		}

		// print LeastCost
		for (int i = 0; i < num_nodes; i++)
		{
			cost = pLeastCost[i];
			if (cost == PLUS_INF)
				fout << "  +oo";
			else
				fout << setw(5) << pLeastCost[i];
		}
		fout << " ==> selected vertex : " << pVrtxArray[minID] << endl;
	}
}