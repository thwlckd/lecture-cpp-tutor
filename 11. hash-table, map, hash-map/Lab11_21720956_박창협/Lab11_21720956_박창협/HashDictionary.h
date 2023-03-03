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

	// class Range 정의
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
	Range findAll(const K& k);  // k를 key 값으로 가지는 entry의 범위 탐색
	Iterator insert(const K& k, const V& v);
}; // end class HashDict

template <typename K, typename V> 
HashDict<K, V>::HashDict(int capacity)
	: HashMap<K, V>(capacity) { }

template <typename K, typename V>
typename HashDict<K, V>::Iterator HashDict<K, V>::insert(const K& k, const V& v) 
{
	Iterator p = this->_find(k); // key 탐색
	Iterator q = this->_insert(p, Entry(k, v));  // 탐색한 p.bkt에 entry 삽입
	return q;
}

template <typename K, typename V>
typename HashDict<K, V>::Range HashDict<K, V>::findAll(const K& k)
{
	Iterator b = this->_find(k);  // look up k
	Iterator p = b;
	while (p != this->end() && (*p).getKey() == k)  // key 값이 다른 entry가 나올 때 까지 반복
	{
		++p;
	}
	return Range(b, p);
}

#endif