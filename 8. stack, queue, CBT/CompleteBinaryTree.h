#pragma once

#ifndef COMPLETE_BINARY_TREE
#define COMPLETE_BINARY_TREE

#include"TA_Entry.h"

using namespace std;

#define CBT_ROOT 1

template<typename K, typename V>
class CompleteBinaryTree : public TA_Entry<K, V>
{
public:
	CompleteBinaryTree(int capa, string nm);
	int add_at_end(T_Entry<K, V>& elem);  // CBT의 마지막에 요소 추가
	T_Entry<K, V>& getEndElement() { return t_GA[end]; }
	T_Entry<K, V>& getRootElement() { return t_GA[CBT_ROOT]; }
	int getEndIndex() { return end; }
	void removeCBTEnd();  // CBT의 마지막 객체 제거
	void fprintCBT(ofstream& fout);  // 완전이진트리의 값을 차례대로 출력
	void fprintCBT_byLevel(ofstream& fout);  // _printCBT_byLevel() 호출

	void set_elapsed_time(double t) { elapsed_time = t; }
	double get_elapsed_time() { return elapsed_time; }

protected:
	void _printCBT_byLevel(ofstream& fout, int p, int level);  // 값을 완전이진트리의 형태로 출력  
	int parentIndex(int index) { return index / 2; }
	int leftChildIndex(int index) { return index * 2; }
	int rightChildIndex(int index) { return (index * 2 + 1); }
	bool hasLeftChild(int index) { return ((index * 2) <= end); }
	bool hasRightChild(int index) { return ((index * 2 + 1) <= end); }
	int end;

	double elapsed_time;
};

template<typename K, typename V>
CompleteBinaryTree<K, V>::CompleteBinaryTree(int capa, string nm)
	:TA_Entry<K, V>(capa + 1, nm)
{
	end = 0;
}

template<typename K, typename V>
int CompleteBinaryTree<K, V>::add_at_end(T_Entry<K, V>& elem)
{
	if (end >= capacity)
	{
		cout << this->getName() << " is FULL now !!" << endl;
		return end;
	}
	end++;
	t_GA[end] = elem;  // 마지막에 요소 추가
	return end;
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT(ofstream& fout)
{
	if (end <= 0)
	{
		fout << this->getName() << " is empty now !!" << endl;
		return;
	}
	int count = 0;
	for (int i = 1; i <= end; i++)
	{
		fout << setw(3) << t_GA[i] << endl;
		//if ((((count + 1) % 10) == 0) && (i != end))
		//fout << endl;
		count++;
	}
}


template<typename K, typename V>
void CompleteBinaryTree<K, V>::_printCBT_byLevel(ofstream& fout, int index, int level)
{
	int index_child;
	if (hasRightChild(index))
	{
		index_child = rightChildIndex(index);
		_printCBT_byLevel(fout, index_child, level + 1);
	}
	for (int i = 0; i < level; i++)
		fout << "     ";
	t_GA[index].fprint(fout);
	fout << endl;
	if (hasLeftChild(index))
	{
		index_child = leftChildIndex(index);
		_printCBT_byLevel(fout, index_child, level + 1);
	}
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::fprintCBT_byLevel(ofstream& fout)
{
	if (end <= 0)
	{
		fout << "CBT is EMPTY now !!" << endl;
		return;
	}
	_printCBT_byLevel(fout, CBT_ROOT, 0);
}

template<typename K, typename V>
void CompleteBinaryTree<K, V>::removeCBTEnd()
{
	end--;
	num_elements--;
}

#endif