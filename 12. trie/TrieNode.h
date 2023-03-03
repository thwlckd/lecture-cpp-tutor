#pragma once

#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <iostream>
#include <string>
#include <list>
#include "MyVoca.h"

//#define VALUE_INTERNAL_NODE ""

using namespace std;

typedef list<MyVoca*> STL_list;

template <typename E>
class TrieNode
{
public:
	TrieNode() {}
	TrieNode(char k, E v) 
		: key(k), value(v)
	{
		prev = next = parent = child = NULL;  // �ʱⰪ NULL
	}
	void setKey(char k) { key = k; }
	void setValue(E v) { value = v; }
	void setNext(TrieNode<E>* nxt) { next = nxt; }
	void setPrev(TrieNode<E>* pv) { prev = pv; }
	void setParent(TrieNode<E>* pr) { parent = pr; }
	void setChild(TrieNode<E>* chld) { child = chld; }
	char getKey() { return key; }
	E getValue() { return value; }
	TrieNode<E>* getPrev() { return prev; }
	TrieNode<E>* getNext() { return next; }
	TrieNode<E>* getParent() { return parent; }
	TrieNode<E>* getChild() { return child; }
	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent);
private:
	char key;
	E value;
	TrieNode<E>* prev;  // ���� ���� ������ ����(����)
	TrieNode<E>* next;  // ���� ���� ������ ����
	TrieNode<E>* parent;  // ���� ��� ���� ����
	TrieNode<E>* child;  // ���� ��� �Ʒ��� ����
};

template<typename E>
void TrieNode<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)
	{
		fout << endl;  // �湮�� ��尡 ��������� ����
		return;
	}
	else
	{
		fout << pTN->key;  // print key
		_fprint(fout, pTN->child, indent + 1);  // �ڽĳ���� ��ġ���� �鿩���⸦ ��ä�� print key
		if (pTN->next == NULL)
			return;
		for (int i = 0; i < indent; i++)
			fout << " ";  // ���� ����� ���̸�ŭ �鿩����
		_fprint(fout, pTN->next, indent);  // ������� ���� ������ ���� ���� �̵��� print key
	}
}

#endif