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
	int insert(T_Entry<K, V>& elem);  // �켱������ ����� ��� ���� (up-heap bubbling)
	T_Entry<K, V>* removeHeapMin();  // 0������ ������ ������ ��ҵ��� �켱������ ���� ���� (donw-heap bubbling)
	T_Entry<K, V>* getHeapMin();  // �켱������ ���� ���� ��Ҹ� ��ȯ
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