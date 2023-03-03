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
	void _traverse(TrieNode<E>* pTN, List_String& list_keywords);  // pTN�� subroot���� �ϴ� external node���� list_keywords�� �����ϴ� �Լ�
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
	char* keyPtr = (char*)keyWord.c_str();  // c_str(): ���ڿ��� ù��° ���� �ּ� ��ȯ 

	if (keyPtr == NULL)
		return;

	if (_find(keyWord, FULL_MATCH) != NULL)  // trie�� keyword�� value�� �̹� ����
	{
		cout << "The given key is already existing; just return !!" << endl;
		return;
	}

	pTN = this->_root;
	// pTN positioning�� ���� �ݺ���
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
			break;  // ������ ������ next node�� �̵�(next=NULL) ex) 'abc' -> insert('cat')
		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL))
			pTN = pTN->getNext();  // ������ ������ next node�� �̵�(next!=NULL) ex) 'abc', 'xy' -> insert('cat')
		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))
		{
			pTN = pTN->getChild();  // child node�� �̵�
			keyPtr++;  // ���ڿ��� ���� �ܾ�
		}
		if ((pTN->getKey() > * keyPtr) && (*keyPtr != '\0'))
			break;  // pTN �տ� insert�ؾ� �ϴ� ��Ȳ ex) 'xy' -> insert('abc')
	}

	// keyWord�� ���� value�� ���ԵǴ� ���
	if ((pTN->getKey() != '\0') && (*keyPtr == '\0'))
	{
		pTN_New = new TrieNode<E>('\0', value);  // ���ο� ��� ����(for external node)
		pTN_New->setParent(pTN->getParent());
		(pTN->getParent())->setChild(pTN_New);
		pTN_New->setNext(pTN);
		pTN->setPrev(pTN_New);
		//cout << "key (" << keyWord << ") is inserted" << endl;
		this->num_keys++;

		return;
	}

	// pTN�� next node �����Ͽ� insert �ϴ� ���
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0'))
	{
		pTN_New = new TrieNode<E>(*keyPtr, NULL);  // new pTN next node
		pTN_New->setParent(pTN->getParent());
		pTN_New->setPrev(pTN);
		pTN->setNext(pTN_New);
		pTN = pTN_New;
		keyPtr++;
		while (*keyPtr != '\0')  // ���ڿ��� ���������� �ݺ�
		{
			pTN_New = new TrieNode<E>(*keyPtr, NULL);  // child node of new pTN next node
			pTN->setChild(pTN_New);
			(pTN->getChild())->setParent(pTN);
			pTN = pTN->getChild();
			keyPtr++;
		}
		if (*keyPtr == '\0')  // ���ڿ��� ������
		{
			insertExternalTN(pTN, keyWord, value);  // external node ����
			this->num_keys++;

			return;
		}
	}

	// pTN�� previous node �����Ͽ� insert �ϴ� ��� (sub-string ���̿� insert)
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

		while (*keyPtr != '\0')  // ���ڿ��� ���������� �ݺ�
		{
			pTN_New = new TrieNode<E>(*keyPtr, NULL);  // child node of new pTN previous node
			pTN->setChild(pTN_New);
			(pTN->getChild())->setParent(pTN);
			pTN = pTN->getChild();
			keyPtr++;
		}
		if (*keyPtr == '\0')  // ���ڿ��� ������
		{
			insertExternalTN(pTN, keyWord, value);  // external node ����
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
	char* keyPtr = (char*)keyStr.c_str();  // c_str(): ���ڿ��� ù��° ���� �ּ� ��ȯ 
	TrieNode<E>* pTN = NULL;
	TrieNode<E>* found = NULL;
	if (keyPtr == NULL)
		return NULL;

	pTN = this->_root;  // star from root
	while ((pTN != NULL) && (*keyPtr != '\0'))  // ���ڿ��� �����ų� external node �� ������ �� ���� �ݺ�
	{
		while ((pTN != NULL) && (pTN->getKey() < *keyPtr))  // ���ϴ� keyStr�� �� Ŭ ���
		{
			if (pTN->getNext() == NULL)  // no key
				return NULL;
			pTN = pTN->getNext();  // next node�� �̵��Ͽ� ��
		}
		if ((pTN != NULL) && (pTN->getKey() > * keyPtr))  // ���ϴ� keyStr�� �� ������� ���� x (start from root)
		{
			return NULL;  // no key
		}
		else if ((pTN == NULL) && (*keyPtr != '\0'))  // ���ϴ� keyStr NULL
		{
			return NULL;
		}
		else if ((pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))  // key node �߰�
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
						return NULL;  //  keyStr�� prefix�� ���� -> no-full-match
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
	pTN = _find(pPrefix, PREFIX_MATCH);  // pPrefix�� �����ϴ� node�� ã�� pTN�� ����
	_traverse(pTN, predictWords);  // pTN�� predictWords�� ����
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
			free(tmp);  // previous node, next node ������ pTN��� �޸� ��ȯ

			break;
		}
		else if (pTN->getPrev() && !(pTN->getNext()))  // pTN has only previous node 
		{
			tmp = pTN;
			(pTN->getPrev())->setNext(NULL);  // pTN�ڸ��� NULL
			free(tmp);  // pTN �ݳ�

			break;
		}
		else if (!(pTN->getPrev()) && pTN->getNext())  // pTN has only next node 
		{
			// pTN�� next node�� pTN�� �θ�� ���� �� previous node NULL ó��
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

	// last node ���� ����
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
		// ��������� pTN�� last node�� �����ϴ� �κ�

		/*if (pTN->getPrev() && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);
		}*/
		if (pTN->getPrev() && !(pTN->getNext()))  // previoud node ������ ���
		{
			pTN_to_be_deleted = pTN;
			(pTN->getPrev())->setNext(NULL);
			pTN = pTN->getPrev();

			free(pTN_to_be_deleted);  // �޸� ��ȯ
		}
		/*else if (!(pTN->getPrev()) && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			(pTN->getNext())->setPrev(NULL);
			pTN = pTN->getNext();
			free(pTN_to_be_deleted);
		}*/
		else  // previous node ���� x
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
			free(pTN_to_be_deleted);  // �޸� ��ȯ 
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