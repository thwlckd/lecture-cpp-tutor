#pragma once

#ifndef HEAP_PRIORITY_QUEUE
#define HEAP_PRIORITY_QUEUE

#include"CompleteBinaryTree.h"

using namespace std;

#include<iostream>
#include<time.h>
#include <Windows.h> 

template<typename K, typename V>
class HeapPrioQueue : public CompleteBinaryTree<K, V>
{
public:
	HeapPrioQueue(int capa, string nm);
	~HeapPrioQueue();
	bool isEmpty() { return size() == 0; }
	bool isFull() { return size() == capacity; }
	int insert(T_Entry<K, V>& elem);  // 우선순위를 고려해 요소 삽입 (up-heap bubbling)
	T_Entry<K, V>* removeHeapMin();  // 0순위를 제거후 나머지 요소들을 우선순위에 따라 정렬 (donw-heap bubbling)
	T_Entry<K, V>* getHeapMin();  // 우선순위가 가장 높은 요소를 반환
	void fprint(ofstream& fout);
	int size() { return end; }
private:
};

template<typename K, typename V>
HeapPrioQueue<K, V>::HeapPrioQueue(int capa, string nm)
	:CompleteBinaryTree(capa, nm)
{ }

template<typename K, typename V>
HeapPrioQueue<K, V>::~HeapPrioQueue()
{ }

template<typename K, typename V>
int HeapPrioQueue<K, V>::insert(T_Entry<K, V>& elem)
{
	int index, parent_index;
	T_Entry<K, V> temp;

	if (isFull())
	{
		cout << this->getName() << " is Full !!" << endl;
		return size();
	}		
	index = add_at_end(elem);  // CBT의 마지막에 요소 추가

	/* up-heap bubbling */
	while (index != CBT_ROOT)  // 마지막에 추가한 노드와 부모노드의 우선순위를 비교해, 우선순위가 높은 요소가 상위노드에 위치하도록 변경
	{
		parent_index = parentIndex(index);
		if (t_GA[index].getKey() >= t_GA[parent_index].getKey())
			break;
		else  // 추가한 요소가 부모노드의 요소보다 우선순위가 높으면
		{
			// 두 노드의 요소를 교환
			temp = t_GA[index];
			t_GA[index] = t_GA[parent_index];
			t_GA[parent_index] = temp;
			index = parent_index;
		}
	}
	return size();
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::removeHeapMin()
{
	int index_p, index_c, index_rc;
	T_Entry<K, V>* pMinElem;
	T_Entry<K, V> temp, t_p, t_c;
	int HPQ_size = size();
	if (HPQ_size <= 0)
	{
		return NULL;
	}

	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = getRootElement();
	if (HPQ_size == 1)
	{
		removeCBTEnd();
	}
	else
	{
		index_p = CBT_ROOT;
		t_GA[CBT_ROOT] = t_GA[end];  // CBT의 마지막 요소를 root로 이동
		end--;

		/* down-heap bubbling */
		while (hasLeftChild(index_p))
		{
			index_c = leftChildIndex(index_p);
			index_rc = rightChildIndex(index_p);
			if (hasRightChild(index_p) && (t_GA[index_c] > t_GA[index_rc]))  // 오른쪽 자식노드의 우선순위가 더 높으면
				index_c = index_rc;  // 오른쪽 자식노드의 요소를 자식노드로 설정
			t_p = t_GA[index_p];
			t_c = t_GA[index_c];
			if (t_p > t_c)  // root로 이동한 요소보다 자식노드의 요소가 우선순위가 더 높으면
			{
				// 두 노드의 요소를 교환
				temp = t_GA[index_p];
				t_GA[index_p] = t_GA[index_c];
				t_GA[index_c] = temp;
				index_p = index_c;
			}
			else
			{
				break;
			} 
				
		} // end while
	}

	return pMinElem;
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::getHeapMin()
{
	T_Entry<K, V>* pMinElem;
	if (size() <= 0)
	{
		return NULL;
	}
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = getRootElement();
	return pMinElem;
}

template<typename K, typename V>
void HeapPrioQueue<K, V>::fprint(ofstream& fout)
{
	if (size() <= 0)
	{
		fout << "HeapPriorityQueue is Empty !!" << endl;
		return;
	}
	else
		CompleteBinaryTree::fprintCBT(fout);
}

#endif