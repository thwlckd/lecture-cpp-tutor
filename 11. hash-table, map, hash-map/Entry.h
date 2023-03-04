#pragma once

#ifndef ENTRY_H
#define ENTRY_H

using namespace std;

template <typename K, typename V>
class Entry // a (key, value) pair
{
public: // public functions
	Entry(const K& k = K(), const V& v = V()) // constructor
		: _key(k), _value(v) { }
	~Entry() {}
	const K& getKey() const { return _key; } // get key
	const V& getValue() const { return _value; } // get value
	void setKey(const K& k) { _key = k; } // set key
	void setValue(const V& v) { _value = v; } // set value
private: // private data
	K _key; // key
	V _value; // value
};

#endif