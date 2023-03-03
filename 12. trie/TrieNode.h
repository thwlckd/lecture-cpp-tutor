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
		prev = next = parent = child = NULL;  // 초기값 NULL
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
	TrieNode<E>* prev;  // 현재 노드와 동일한 레벨(깊이)
	TrieNode<E>* next;  // 현재 노드와 동일한 레벨
	TrieNode<E>* parent;  // 현재 노드 위의 레벨
	TrieNode<E>* child;  // 현재 노드 아래의 레벨
};

template<typename E>
void TrieNode<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)
	{
		fout << endl;  // 방문한 노드가 비어있으면 띄어쓰기
		return;
	}
	else
	{
		fout << pTN->key;  // print key
		_fprint(fout, pTN->child, indent + 1);  // 자식노드의 위치에서 들여쓰기를 한채로 print key
		if (pTN->next == NULL)
			return;
		for (int i = 0; i < indent; i++)
			fout << " ";  // 현재 노드의 깊이만큼 들여쓰기
		_fprint(fout, pTN->next, indent);  // 현재노드와 같은 레벨의 다음 노드로 이동해 print key
	}
}

#endif