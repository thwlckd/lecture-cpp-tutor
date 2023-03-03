#pragma once

#ifndef HASHMAP_H
#define HASHMAP_H

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include "Entry.h"
#include "CyclicShiftHashCode.h"
#include "MyVoca.h"

#define DEFAULT_HASH_TABLE_SIZE 101

using namespace std;

template <typename K, typename V>
class HashMap
{
public:
	typedef Entry<const K, V> Entry;  // a (key, value) pair -> Entry
	typedef std::list<Entry> Bucket;  // list of entries -> Bucket
	typedef std::vector<Bucket> BktArray;  // vector of Buckets -> BktArray
	typedef typename BktArray::iterator BItor;  // Bucket iterator
	typedef typename Bucket::iterator EItor;  // Entry iterator
	class Iterator;
	HashMap(int capacity = DEFAULT_HASH_TABLE_SIZE);
	int size() const { return num_entry; }
	bool empty() const { return (num_entry == 0); }
	Iterator find(const K& k);  // find entry with key k
	Iterator insert(const K& k, const V& v);  // insert/replace (k,v)
	void erase(const K& k);  // remove entry with key k
	void erase(const Iterator& p);  // erase entry at p
	Iterator begin();  // hash table에서 비어있지 않은 첫번째 버킷의 첫번째 entry를 iterator가 가르키도록 하여 반환
	Iterator end();  // iterator to end entry of HashMap
	void fprintBucketSizes(ostream& fout);
	void fprintBucket(ostream& fout, BItor bkt);
protected:
	Iterator _find(const K& k);
	Iterator _insert(const Iterator& p, const Entry& e);
	void _erase(const Iterator& p);
	static bool _endOfBkt(const Iterator& p)
	{
		return p.ent == p.bkt->end();
	}
private:
	int num_entry;
	BktArray B;  // bucket array (Hash Table)

public:
	// class Iterator 정의
	class Iterator  // HashMap::Iterator (& position)
	{ 
	private:
		const BktArray* ba;  // vector of Buckets -> BktArray
		BItor bkt;  // Bucket iterator
		EItor ent;  // Entry iterator
	public:
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ba(&a), bkt(b), ent(q) { }
		Iterator() {}
		Entry& operator*() const; // get entry
		bool operator==(const Iterator& p) const;
		bool operator!=(const Iterator& p) const;
		const K& getKey() const { Entry& entry = *ent; return entry.getKey(); } // get key
		const V& getValue() const { Entry& entry = *ent; return entry.getValue(); } // get value
		Iterator& operator++();  // to next entry
		friend class HashMap;  // give HashMap access
	};  // end class Iterator
};  // end of class HashMap

template <typename K, typename V>
HashMap<K, V>::HashMap(int capacity)
	: num_entry(0), B(capacity) { }

template <typename K, typename V>
typename HashMap<K, V>::Iterator HashMap<K, V>::begin()
{
	if (empty())
		return end();
	BItor bkt = B.begin();
	while (bkt->empty())  // 빈 bucket이 나오지 않을 때 까지 반복 -> 첫번째 entry 찾음
		++bkt;
	return Iterator(B, bkt, bkt->begin());
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator HashMap<K, V>::end()
{
	return Iterator(B, B.end());  // end entry: dummy data -> EItor() 처리
}

template <typename K, typename V>
typename HashMap<K, V>::Entry& HashMap<K, V>::Iterator::operator*() const
{
	return *ent;
}

template <typename K, typename V>
bool HashMap<K, V>::Iterator::operator==(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt)  // different ba or bkt
		return false;
	else if (bkt == ba->end())  // both bucket == end
		return true;
	else return (ent == p.ent);  // same ent
}

template <typename K, typename V>
bool HashMap<K, V>::Iterator::operator!=(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt)  // different ba or bkt
		return true;
	else if (bkt == ba->end())  // both bucket == end
		return false;
	else return (ent != p.ent);  // different ent
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator& HashMap<K, V>::Iterator::operator++()
{
	++ent;  // next entry in bucket
	if (_endOfBkt(*this))  // if end of bkt
	{
		++bkt;  // go to next bucket
		while (bkt != ba->end() && bkt->empty())  // 빈 bucket이 나오지 않을 때 까지 반복 -> 첫번째 entry 찾음
			++bkt;
		if (bkt == ba->end())  // end of bucket array
			return *this;
		ent = bkt->begin();  // 첫번째 entry
	}
	return *this;
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator HashMap<K, V>::_find(const K& k)
{
	CyclicShiftHashCode hash;
	int i = hash(k) % B.size();  // hash code mod N(bkt size)
	BItor bkt = B.begin() + i;  // i번째 bkt
	Iterator p(B, bkt, bkt->begin());  // i번째 bkt부터 탐색을 위한 iterator 생성
	while (!_endOfBkt(p) && (*p).getKey() != k)  // key 탐색 loop
		++p.ent;
	return p;
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k);
	if (_endOfBkt(p))  // bkt에 key 값 존재x
		return end();
	else  // bkt에 key 값 존재
		return p;
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::_insert(const Iterator& p, const Entry& e)
{
	EItor ins = p.bkt->insert(p.ent, e);  // bkt에 entry insert
	num_entry++;
	return Iterator(B, p.bkt, ins);
}

template <typename K, typename V>
typename HashMap<K, V>::Iterator
HashMap<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k);
	if (_endOfBkt(p))  // bkt에 key 값 존재x
		return _insert(p, Entry(k, v));  // end of bucket에 새로운 entry 삽입
	else // bkt에 key 값 존재
	{
		p.ent->setValue(v);  // entry 값 변경
		return p;
	}
}

template <typename K, typename V>
void HashMap<K, V>::_erase(const Iterator& p)
{
	p.bkt->erase(p.ent);  // bkt에서 entry 삭제
	num_entry--;
}

template <typename K, typename V>
void HashMap<K, V>::erase(const Iterator& p)
{
	_erase(p);
}

template <typename K, typename V>
void HashMap<K, V>::erase(const K& k)
{
	Iterator p = _find(k);
	if (_endOfBkt(p))  // bkt에 key 값 존재 x
		//throw NonexistentElement("Erase of nonexistent");  // 삭제할 entry 존재 x -> error
		cout << "error";
	_erase(p);  // else remove entry
}

template <typename K, typename V>
void HashMap<K, V>::fprintBucket(ostream& fout, BItor bkt)
{
	Iterator p(B, bkt, bkt->begin());
	MyVoca* pVoca;
	while (p.ent != bkt->end())
	{
		pVoca = p.getValue();
		fout << *pVoca << endl;
		++p.ent;
	}
}

template <typename K, typename V>
void HashMap<K, V>::fprintBucketSizes(ostream& fout)
{
	int bkt_size;
	int max_ent, min_ent, total;
	int num_bkts, max_bkt = 0;
	double avg = 0.0;
	max_ent = min_ent = B[0].size();
	total = 0;
	num_bkts = B.size();

	for (int bkt = 0; bkt < num_bkts; bkt++)
	{
		bkt_size = B[bkt].size();  // bkt size 측정
		fout << "Bucket[" << setw(3) << bkt << "] : " << bkt_size << " entries" << endl;
		if (bkt_size > max_ent)  // new max_bkt_size
		{
			max_ent = bkt_size;
			max_bkt = bkt;
		}
		if (bkt_size < min_ent)  // new min_bkt_size
			min_ent = bkt_size;
		total += bkt_size;
	}
	avg = total / num_bkts;
	fout.precision(2);
	fout << "\nMax_ent(" << setw(2) << max_ent << "), min_ent(" << setw(2) << min_ent << "), avg (" << setw(5) << avg << ")" << endl;
	//fout << "Bucket with maximum (" << max_ent << ") entries : " << endl;
	//BItor bkt = B.begin() + max_bkt;
	//fprintBucket(fout, bkt);  // max_bkt_ent 출력
}
#endif