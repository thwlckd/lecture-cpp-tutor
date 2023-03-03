#pragma once

#ifndef T_ENTRY_H
#define T_ENTRY_H

#include<iostream>
#include<iomanip>

using namespace std;

template<typename K, typename V>
class T_Entry
{
    // friend ostream& operator<<(ostream& fout, const T_Entry<K, V>& entry);
public:
    T_Entry(K key, V value) { _key = key; _value = value; }
    T_Entry() {} // default constructor
    ~T_Entry() {}
    void setKey(const K& key) { _key = key; }
    void setValue(const V& value) { _value = value; }
    K getKey() const { return _key; }
    V getValue() const { return _value; }
    bool operator>(const T_Entry& right) { return (_key > right.getKey()); }
    bool operator>=(const T_Entry& right) { return (_key >= right.getKey()); }
    bool operator<(const T_Entry& right) { return (_key < right.getKey()); }
    bool operator<=(const T_Entry& right) { return (_key <= right.getKey()); }
    bool operator==(const T_Entry& right) { return ((_key == right.getKey()) && (_value == right.getValue())); }
    T_Entry& operator=(const T_Entry& right);
    void fprint(ostream& fout);
private:
    K _key;
    V _value;
};

/*
template<typename K, typename V>
ostream& operator<<(ostream& fout, const T_Entry<K, V>& entry)
{
    fout << "(" << entry.getKey() << ", " << entry.getValue() << ")";
    return fout;
}
*/

template<typename K, typename V>
T_Entry<K, V>& T_Entry<K, V>::operator=(const T_Entry& right)
{
    _key = right._key;
    _value = right._value;

    return *this;
}

template<typename K, typename V>
void T_Entry<K, V>::fprint(ostream& fout)
{
    string key_type_name = typeid(K).name();
    if (key_type_name == "class Time")
        fout << "(Key:" << this->getKey() << ", " << *(this->getValue()) << ")";
    else
        fout << "(Key:" << setw(10) << this->getKey() << ", " << *(this->getValue()) << ")";
}

#endif
