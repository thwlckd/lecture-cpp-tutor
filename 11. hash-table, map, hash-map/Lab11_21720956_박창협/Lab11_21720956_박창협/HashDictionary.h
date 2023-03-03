#pragma once

#ifndef HASH_DICTIONARY_H
#define HASH_DICTIONARY_H

#include "HashMap.h"
#include "Entry.h"

#define HASH_TABLE_SIZE 101

template <typename K, typename V>
class HashDict : public HashMap<K, V>
{
public: 
	typedef typename HashMap<K, V>::Iterator Iterator;
	typedef typename HashMap<K, V>::Entry Entry;

	// class Range ����
	class Range  // iterator range
	{ 
	private:
		Iterator _begin;  // front of range
		Iterator _end;  // end of range
	public:
		Range() {}
		Range(const Iterator& b, const Iterator& e)
			: _begin(b), _end(e) { }
		Iterator& begin() { return _begin; }
		Iterator& end() { return _end; }
	}; // end class Range

public:
	HashDict(int capacity = HASH_TABLE_SIZE);
	Range findAll(const K& k);  // k�� key ������ ������ entry�� ���� Ž��
	Iterator insert(const K& k, const V& v);
}; // end class HashDict

template <typename K, typename V> 
HashDict<K, V>::HashDict(int capacity)
	: HashMap<K, V>(capacity) { }

template <typename K, typename V>
typename HashDict<K, V>::Iterator HashDict<K, V>::insert(const K& k, const V& v) 
{
	Iterator p = this->_find(k); // key Ž��
	Iterator q = this->_insert(p, Entry(k, v));  // Ž���� p.bkt�� entry ����
	return q;
}

template <typename K, typename V>
typename HashDict<K, V>::Range HashDict<K, V>::findAll(const K& k)
{
	Iterator b = this->_find(k);  // look up k
	Iterator p = b;
	while (p != this->end() && (*p).getKey() == k)  // key ���� �ٸ� entry�� ���� �� ���� �ݺ�
	{
		++p;
	}
	return Range(b, p);
}

#endif