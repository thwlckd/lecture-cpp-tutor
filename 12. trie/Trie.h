#pragma once

#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include "TrieNode.h"

#define MAX_STR_LEN 100

using namespace std;

typedef list<MyVoca*> List_String;  // list MyVoca*
typedef list<MyVoca*>::iterator List_String_Iter;  // Iterator of list MyVoca*

enum SearchMode { FULL_MATCH, PREFIX_MATCH };  // FULL_MATCH: equal word, PREFIX_MATCH: word including PREFIX

template <typename E>
class Trie
{
public:
	Trie(string name);
	int size() { return num_keys; }
	void insert(string keyWord, E value);  // insert in trie
	void insertExternalTN(TrieNode<E>* pTN, string keyWord, E value);  // insert at external node(leaf node)
	TrieNode<E>* find(string keyWord);  // call _find()
	void findPrefixMatch(string prefix, List_String& predictWords);  // find words with prefix
	void deletekeyWord(string keyWord);  // delete key node
	void eraseTrie();  // clear trie
	void fprintTrie(ostream& fout);  // print trie with indentation
protected:
	TrieNode<E>* _find(string keyWord, SearchMode sm = FULL_MATCH);  // find key node following SearchMode
	void _traverse(TrieNode<E>* pTN, List_String& list_keywords);  // pTN을 subroot으로 하는 external node들을 list_keywords에 저장하는 함수
private:
	TrieNode<E>* _root;  // _root trie node
	int num_keys;
	string trie_name;
};

template<typename E>
Trie<E>::Trie(string name)
{
	trie_name = name;
	_root = new TrieNode<E>('\0', NULL);
	_root->setKey('\0');
	_root->setPrev(NULL);
	_root->setNext(NULL);
	_root->setParent(NULL);
	_root->setChild(NULL);
	num_keys = 0;
}

template<typename E>
void Trie<E>::insert(string keyWord, E value)
{
	TrieNode<E>* pTN = NULL, * pTN_New = NULL;
	char keyWording[MAX_STR_LEN];
	char* keyPtr = (char*)keyWord.c_str();  // c_str(): 문자열의 첫번째 문자 주소 반환 

	if (keyPtr == NULL)
		return;

	if (_find(keyWord, FULL_MATCH) != NULL)  // trie에 keyword가 value로 이미 존재
	{
		cout << "The given key is already existing; just return !!" << endl;
		return;
	}

	pTN = this->_root;
	// pTN positioning을 위한 반복문
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
			break;  // 동일한 레벨의 next node로 이동(next=NULL) ex) 'abc' -> insert('cat')
		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL))
			pTN = pTN->getNext();  // 동일한 레벨의 next node로 이동(next!=NULL) ex) 'abc', 'xy' -> insert('cat')
		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))
		{
			pTN = pTN->getChild();  // child node로 이동
			keyPtr++;  // 문자열의 다음 단어
		}
		if ((pTN->getKey() > * keyPtr) && (*keyPtr != '\0'))
			break;  // pTN 앞에 insert해야 하는 상황 ex) 'xy' -> insert('abc')
	}

	// keyWord가 기존 value에 포함되는 경우
	if ((pTN->getKey() != '\0') && (*keyPtr == '\0'))
	{
		pTN_New = new TrieNode<E>('\0', value);  // 새로운 노드 생성(for external node)
		pTN_New->setParent(pTN->getParent());
		(pTN->getParent())->setChild(pTN_New);
		pTN_New->setNext(pTN);
		pTN->setPrev(pTN_New);
		//cout << "key (" << keyWord << ") is inserted" << endl;
		this->num_keys++;

		return;
	}

	// pTN의 next node 생성하여 insert 하는 경우
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
	{
		pTN_New = new TrieNode<E>(*keyPtr, NULL);  // new pTN next node
		pTN_New->setParent(pTN->getParent());
		pTN_New->setPrev(pTN);
		pTN->setNext(pTN_New);
		pTN = pTN_New;
		keyPtr++;
		while (*keyPtr != '\0')  // 문자열이 끝날때까지 반복
		{
			pTN_New = new TrieNode<E>(*keyPtr, NULL);  // child node of new pTN next node
			pTN->setChild(pTN_New);
			(pTN->getChild())->setParent(pTN);
			pTN = pTN->getChild();
			keyPtr++;
		}
		if (*keyPtr == '\0')  // 문자열이 끝나면
		{
			insertExternalTN(pTN, keyWord, value);  // external node 생성
			this->num_keys++;

			return;
		}
	}

	// pTN의 previous node 생성하여 insert 하는 경우 (sub-string 사이에 insert)
	else if ((pTN->getKey() > * keyPtr) && (*keyPtr != '\0'))
	{
		pTN_New = new TrieNode<E>(*keyPtr, NULL);  // new pTN previous node
		pTN_New->setNext(pTN);
		pTN_New->setParent(pTN->getParent());
		if (pTN->getPrev() == NULL)
		{
			if (pTN->getParent() != NULL)
				(pTN->getParent())->setChild(pTN_New);
		}
		else
		{
			(pTN->getPrev())->setNext(pTN_New);
		}
		pTN_New->setPrev(pTN->getPrev());
		pTN->setPrev(pTN_New);
		pTN = pTN_New;
		keyPtr++;

		while (*keyPtr != '\0')  // 문자열이 끝날때까지 반복
		{
			pTN_New = new TrieNode<E>(*keyPtr, NULL);  // child node of new pTN previous node
			pTN->setChild(pTN_New);
			(pTN->getChild())->setParent(pTN);
			pTN = pTN->getChild();
			keyPtr++;
		}
		if (*keyPtr == '\0')  // 문자열이 끝나면
		{
			insertExternalTN(pTN, keyWord, value);  // external node 생성
			this->num_keys++;

			return;
		}
	}
}

template<typename E>
void Trie<E>::insertExternalTN(TrieNode<E>* pTN, string keyWord, E value)
{
	TrieNode<E>* pTN_New = NULL;
	pTN_New = new TrieNode<E>('\0', value);  // external node: key = NULL
	pTN->setChild(pTN_New);
	(pTN->getChild())->setParent(pTN);
	pTN_New->setValue(value);
	//cout << "key (" << keyWord << ") is inserted \n";
}

template<typename E>
TrieNode<E>* Trie<E>::find(string keyWord)
{
	TrieNode<E>* pTN = NULL;
	pTN = _find(keyWord, FULL_MATCH);  // find FULL_MATCH node

	return pTN;
}

template<typename E>
TrieNode<E>* Trie<E>::_find(string keyStr, SearchMode sm)
{
	char* keyPtr = (char*)keyStr.c_str();  // c_str(): 문자열의 첫번째 문자 주소 반환 
	TrieNode<E>* pTN = NULL;
	TrieNode<E>* found = NULL;
	if (keyPtr == NULL)
		return NULL;

	pTN = this->_root;  // star from root
	while ((pTN != NULL) && (*keyPtr != '\0'))  // 문자열이 끝나거나 external node 에 도착할 때 까지 반복
	{
		while ((pTN != NULL) && (pTN->getKey() < *keyPtr))  // 비교하는 keyStr이 더 클 경우
		{
			if (pTN->getNext() == NULL)  // no key
				return NULL;
			pTN = pTN->getNext();  // next node로 이동하여 비교
		}
		if ((pTN != NULL) && (pTN->getKey() > * keyPtr))  // 비교하는 keyStr이 더 작을경우 존재 x (start from root)
		{
			return NULL;  // no key
		}
		else if ((pTN == NULL) && (*keyPtr != '\0'))  // 비교하는 keyStr NULL
		{
			return NULL;
		}
		else if ((pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))  // key node 발견
		{
			// for compare next key
			pTN = pTN->getChild();
			keyPtr++;

			if (*keyPtr == '\0')
			{
				if (sm == FULL_MATCH)
				{
					if (pTN->getKey() == '\0')  // full-match
						return pTN;
					else  // (pTN->getKey() != '\0')
						return NULL;  //  keyStr이 prefix로 존재 -> no-full-match
				}
				else if (sm == PREFIX_MATCH)
					return pTN;
			}
			else if ((pTN->getKey() == '\0') && (*keyPtr != '\0'))
			{
				if (pTN->getNext() != NULL)
				{
					pTN = pTN->getNext();  // goto next node
					continue;
				}
				else  // keyStr is not exist
					return NULL;
			}
			else   // ((pTN->getKey() != '\0') && (*keyPtr != '\0'))
				continue;  // compare next key
		}
	}
}

template<typename E>
void Trie<E>::findPrefixMatch(string pPrefix, List_String& predictWords)
{
	TrieNode<E>* pTN = NULL;
	if (pPrefix == "")
		return;
	pTN = _find(pPrefix, PREFIX_MATCH);  // pPrefix를 포함하는 node를 찾아 pTN에 전달
	_traverse(pTN, predictWords);  // pTN을 predictWords에 저장
	//printf("Error in TrieSearch (key: %s) !!\n", keyWord);
}

template<typename E>
void Trie<E>::fprintTrie(ostream& fout)
{
	TrieNode<E>* pTN;
	int indent = 0;

	fout << "trie ( " << this->trie_name << ") with " << this->num_keys << " trie_nodes\n";
	if (this->num_keys == 0)
	{
		fout << "Empty trie !" << endl;
		return;
	}
	pTN = this->_root;
	pTN->_fprint(fout, pTN, indent);
}

template<typename E>
void Trie<E>::deletekeyWord(string keyWord)
{
	TrieNode<E>* pTN = NULL, * _root;
	TrieNode<E>* tmp = NULL;
	int trie_val;

	_root = this->_root;
	if (NULL == _root || "" == keyWord)
		return;
	pTN = _find(keyWord, FULL_MATCH);
	if (pTN == NULL)
	{
		cout << "Key [" << keyWord << "] not found in trie" << endl;
		return;
	}
	while (1)
	{
		if (pTN == NULL)
			break;
		if (pTN->getPrev() && pTN->getNext())  // pTN has both previous and next node
		{
			tmp = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			free(tmp);  // previous node, next node 연결후 pTN노드 메모리 반환

			break;
		}
		else if (pTN->getPrev() && !(pTN->getNext()))  // pTN has only previous node 
		{
			tmp = pTN;
			(pTN->getPrev())->setNext(NULL);  // pTN자리에 NULL
			free(tmp);  // pTN 반납

			break;
		}
		else if (!(pTN->getPrev()) && pTN->getNext())  // pTN has only next node 
		{
			// pTN의 next node를 pTN의 부모와 연결 및 previous node NULL 처리
			tmp = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			pTN = pTN->getNext();
			pTN->setPrev(NULL);
			free(tmp);

			break;
		}
		else  // pTN hasn't both previous and next node 
		{
			tmp = pTN;
			pTN = pTN->getParent();
			if (pTN != NULL)
				pTN->setChild(NULL);
			free(tmp);
			if ((pTN == _root) && (pTN->getNext() == NULL) && (pTN->getPrev() == NULL))
			{
				cout << "Now, the trie is empty !!" << endl;
				break;
			}
		}
	}
	this->num_keys--;
}

template<typename E>
void Trie<E>::eraseTrie()
{
	TrieNode<E>* pTN;
	TrieNode<E>* pTN_to_be_deleted = NULL;

	if (this->_root == NULL)
		return;
	pTN = this->_root;

	// last node 부터 제거
	while (pTN != NULL)
	{
		while ((pTN != NULL) && (pTN->getNext()))
			pTN = pTN->getNext();
		while (pTN->getChild())
		{
			if (pTN->getNext())
				break;
			pTN = pTN->getChild();
		}
		if (pTN->getNext())
			continue;
		// 여기까지가 pTN을 last node로 설정하는 부분

		/*if (pTN->getPrev() && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);
		}*/
		if (pTN->getPrev() && !(pTN->getNext()))  // previoud node 존재할 경우
		{
			pTN_to_be_deleted = pTN;
			(pTN->getPrev())->setNext(NULL);
			pTN = pTN->getPrev();

			free(pTN_to_be_deleted);  // 메모리 반환
		}
		/*else if (!(pTN->getPrev()) && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			(pTN->getNext())->setPrev(NULL);
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);
		}*/
		else  // previous node 존재 x
		{
			pTN_to_be_deleted = pTN;
			if (pTN == this->_root)
			{
				this->num_keys = 0;
				return;
			}
			if (pTN->getParent() != NULL)
			{
				pTN = pTN->getParent();
				pTN->setChild(NULL);
			}
			else
			{
				pTN = pTN->getPrev();
			}
			free(pTN_to_be_deleted);  // 메모리 반환 
		}
	}
}

template<typename E>
void Trie<E>::_traverse(TrieNode<E>* pTN, List_String& list_keywords)
{
	if (pTN == NULL)
		return;
	if (pTN->getChild() == NULL)  // pTN has no child
	{
		list_keywords.push_back(pTN->getValue());  // insert element in list
	}
	else  // pTN has child
	{
		_traverse(pTN->getChild(), list_keywords);  // insert childe node value as element in list
	}
	if (pTN->getNext() != NULL)  // pTN has next node
	{
		_traverse(pTN->getNext(), list_keywords);  // insert next node value as element in list
	}
}

#endif