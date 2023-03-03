#pragma once

#ifndef HEAP_PRIORITY_QUEUE_CS
#define HEAP_PRIORITY_QUEUE_CS

#include"CompleteBinaryTree.h"

using namespace std;

#include<iostream>
#include<time.h>
#include <Windows.h> 

template<typename K, typename V>
class HeapPrioQ_CS : public CompleteBinaryTree<K, V>
{
public:
	HeapPrioQ_CS(int capa, string nm);
	~HeapPrioQ_CS();
	bool isEmpty() { return size() == 0; }
	bool isFull() { return size() == capacity; }
	int insert(T_Entry<K, V>& elem);  // �켱������ ����� ��� ���� (up-heap bubbling)
	T_Entry<K, V>* removeHeapMin();  // 0������ ������ ������ ��ҵ��� �켱������ ���� ���� (donw-heap bubbling)
	T_Entry<K, V>* getHeapMin();  // �켱������ ���� ���� ��Ҹ� ��ȯ
	void fprint(ostream& fout);
	int size() { return end; }
private:
	CRITICAL_SECTION cs_Q;
};

template<typename K, typename V>
HeapPrioQ_CS<K, V>::HeapPrioQ_CS(int capa, string nm)
	:CompleteBinaryTree(capa, nm)
{ 
	InitializeCriticalSection(&cs_Q);
}

template<typename K, typename V>
HeapPrioQ_CS<K, V>::~HeapPrioQ_CS()
{ 
	DeleteCriticalSection(&cs_Q);
}

template<typename K, typename V>
int HeapPrioQ_CS<K, V>::insert(T_Entry<K, V>& elem)
{
	EnterCriticalSection(&cs_Q);
	int index, parent_index;
	T_Entry<K, V> temp;

	if (isFull())
	{
		cout << this->getName() << " is Full !!" << endl;
		LeaveCriticalSection(&cs_Q);
		return size();
	}
	index = add_at_end(elem);  // CBT�� �������� ��� �߰�

	/* up-heap bubbling */
	while (index != CBT_ROOT)  // �������� �߰��� ���� �θ����� �켱������ ����, �켱������ ���� ��Ұ� ������忡 ��ġ�ϵ��� ����
	{
		parent_index = parentIndex(index);
		if (t_GA[index].getKey() >= t_GA[parent_index].getKey())
			break;
		else  // �߰��� ��Ұ� �θ����� ��Һ��� �켱������ ������
		{
			// �� ����� ��Ҹ� ��ȯ
			temp = t_GA[index];
			t_GA[index] = t_GA[parent_index];
			t_GA[parent_index] = temp;
			index = parent_index;
		}
	}
	LeaveCriticalSection(&cs_Q);
	return size();
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQ_CS<K, V>::removeHeapMin()
{
	EnterCriticalSection(&cs_Q);
	int index_p, index_c, index_rc;
	T_Entry<K, V>* pMinElem;
	T_Entry<K, V> temp, t_p, t_c;
	int HPQ_size = size();
	if (HPQ_size <= 0)
	{
		LeaveCriticalSection(&cs_Q);
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
		t_GA[CBT_ROOT] = t_GA[end];  // CBT�� ������ ��Ҹ� root�� �̵�
		end--;

		/* down-heap bubbling */
		while (hasLeftChild(index_p))
		{
			index_c = leftChildIndex(index_p);
			index_rc = rightChildIndex(index_p);
			if (hasRightChild(index_p) && (t_GA[index_c] > t_GA[index_rc]))  // ������ �ڽĳ���� �켱������ �� ������
				index_c = index_rc;  // ������ �ڽĳ���� ��Ҹ� �ڽĳ��� ����
			t_p = t_GA[index_p];
			t_c = t_GA[index_c];
			if (t_p > t_c)  // root�� �̵��� ��Һ��� �ڽĳ���� ��Ұ� �켱������ �� ������
			{
				// �� ����� ��Ҹ� ��ȯ
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
	LeaveCriticalSection(&cs_Q);
	return pMinElem;
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQ_CS<K, V>::getHeapMin()
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
void HeapPrioQ_CS<K, V>::fprint(ostream& fout)
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