#pragma once

#ifndef TA_ENTRY_H
#define TA_ENTRY_H

#include<iostream>
#include<iomanip>
#include"T_Entry.h"

using namespace std;

enum SortingDirection { INCREASING, DECREASING };

template<typename K, typename V>
class TA_Entry
{
public:
    TA_Entry(int n, string nm); // constructor
    ~TA_Entry(); // destructor
    int size() { return num_elements; }
    bool empty() { return num_elements == 0; }
    string getName() { return name; }
    void reserve(int new_capacity);
    void insert(int i, T_Entry<K, V> element);
    void remove(int i);
    T_Entry<K, V>& at(int i);
    void set(int i, T_Entry<K, V>& element);
    T_Entry<K, V>& getMin();
    T_Entry<K, V>& getMax();
    void shuffle();
    int sequential_search(T_Entry<K, V> search_key); // search and return the index; -1 if not found
    int binary_search(T_Entry<K, V> search_key); // search and return the index; -1 if not found
    void selection_sort(SortingDirection sd);
    void quick_sort(SortingDirection sd);
    void fprint(ofstream& fout, int elements_per_line);
    void fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines);
    bool isValidIndex(int i);
    T_Entry<K, V>& operator[](int index) { return t_array[index]; }
protected:
    T_Entry<K, V>* t_array;
    int num_elements;
    int capacity;
    string name;
};

template<typename K, typename V>
TA_Entry<K, V>::TA_Entry(int new_capacity, string nm)  // constructor
{
    capacity = new_capacity;
    t_array = (T_Entry<K, V>*) new T_Entry<K, V>[capacity];
    if (t_array == NULL)
    {
        cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
        exit(-1);
    }
    num_elements = 0;
    name = nm;
}

template<typename K, typename V>
TA_Entry<K, V>::~TA_Entry()  // destructor
{
    if (t_array != NULL)
        delete[] t_array;
}

template<typename K, typename V>
void TA_Entry<K, V>::reserve(int new_capacity)
{
    if (capacity >= new_capacity)
        return;  // new_capacity 이상의 용량이 준비되어 있음
    T_Entry<K, V>* t_newGA = (T_Entry<K, V>*) new T_Entry<K, V>[new_capacity];  // new_capacity 만큼 배열 동적 할당
    if (t_newGA == NULL)
    {
        cout << "Error in creation of dynamic array of size (" << new_capacity << ") !!" << endl;
        exit(-1);
    }
    cout << this->getName() << " expands capacity to " << setw(3) << new_capacity << endl;
    for (int i = 0; i < num_elements; i++)
        t_newGA[i] = t_array[i];  // 새로 할당한 배열에 기존의 값 복사
    delete[] t_array;
    t_array = t_newGA;
    capacity = new_capacity;
}

template<typename K, typename V>
void TA_Entry<K, V>::insert(int i, T_Entry<K, V> element)
{
    if (num_elements >= capacity)
    {
        // 용량이 가득 차면 capacity 2배 증가
        int new_capa;
        new_capa = ((2 * capacity) > 1) ? 2 * capacity : 1;
        reserve(new_capa);
    }
    if (isValidIndex(i))
    {
        for (int j = num_elements - 1; j >= i; j--)
            t_array[j + 1] = t_array[j];  // i보다 큰 인덱스 값들을 뒤로 한칸씩 이동
        t_array[i] = element;  // insert
        num_elements++;
    }
}

template<typename K, typename V>
void TA_Entry<K, V>::remove(int i)
{
    if (isValidIndex(i))
    {
        for (int j = i + 1; j < num_elements; j++)
            t_array[j - 1] = t_array[j];  // i보다 큰 인덱스 값들을 앞으로 한칸씩 이동
        num_elements--;
    }
    if (num_elements < (capacity / 2))
    {
        int new_capacity = capacity / 2;
        T_Entry<K, V>* t_newGA = (T_Entry<K, V>*) new T_Entry<K, V>[new_capacity];
        if (t_newGA == NULL)
        {
            return; // new memory allocation failed.
            // Just return without modification.
        }
        cout << this->getName() << " reduces capacity to " << setw(3) << new_capacity << endl;
        for (int i = 0; i < num_elements; i++)
            t_newGA[i] = t_array[i];
        delete[] t_array;
        t_array = t_newGA;
        capacity = new_capacity;
    }
}

template<typename K, typename V>
T_Entry<K, V>& TA_Entry<K, V>::at(int i)
{
    if (isValidIndex(i))
        return t_array[i];
}

template<typename K, typename V>
void TA_Entry<K, V>::set(int i, T_Entry<K, V>& element)
{
    if (isValidIndex(i))
        t_array[i] = element;
}

template<typename K, typename V>
T_Entry<K, V>& TA_Entry<K, V>::getMin()
{
    {
        T_Entry<K, V> minValue;
        int index_min;

        minValue = t_array[0];
        index_min = 0;
        for (int i = 1; i <= num_elements; i++)
        {
            if (t_array[i] < minValue)
            {
                minValue = t_array[i];
                index_min = i;
            }
        }
        return t_array[index_min];
    }
}

template<typename K, typename V>
T_Entry<K, V>& TA_Entry<K, V>::getMax()
{
    T_Entry<K, V> maxValue;
    int index_max;

    maxValue = t_array[0];
    index_max = 0;
    for (int i = 1; i <= num_elements; i++)
    {
        if (t_array[i] > maxValue)
        {
            maxValue = t_array[i];
            index_max = i;
        }
    }
    return t_array[index_max];
}

template<typename K, typename V>
void TA_Entry<K, V>::shuffle()
{
    srand(time(0));
    int index1, index2;
    int rand_1, rand_2;
    T_Entry<K, V> temp;

    for (int i = 0; i < num_elements; i++)
    {
        rand_1 = rand();
        rand_2 = rand();
        index1 = ((rand_1 << 15) | rand_2) % num_elements;  // left bitwise 15 -> 30bit bigrand
        rand_1 = rand();
        rand_2 = rand();
        index2 = ((rand_1 << 15) | rand_2) % num_elements;

        // t_array의 index1과 index2 값 교환
        temp = t_array[index1];
        t_array[index1] = t_array[index2];
        t_array[index2] = temp;
    }
}

template<typename K, typename V>
int TA_Entry<K, V>::sequential_search(T_Entry<K, V> search_key)
{
    int index;
    for (int index = 0; index < num_elements; index++)
    {
        // 처음부터 끝까지 하나씩 비교
        if (t_array[index] == search_key)
            return index;
    }
    return -1;
}

template<typename K, typename V>
int TA_Entry<K, V>::binary_search(T_Entry<K, V> search_key)  // 정렬되어 있는 배열을 절반씩 분할해 가며 탐색
{
    int low, mid, high;
    int loop = 1;
    low = 0;
    high = num_elements - 1;
    while (low <= high)
    {
        cout << setw(2) << loop << "-th loop: current search range [" << setw(3) << low << ", " << setw(3) << high << "]" << endl;
        mid = (low + high) / 2;
        if (t_array[mid] == search_key)
            return mid;
        else if (t_array[mid] > search_key)
            high = mid - 1;
        else
            low = mid + 1;
        loop++;
    }
    return -1;
}

template<typename K, typename V>
void TA_Entry<K, V>::selection_sort(SortingDirection sd)
{
    int index_min, index_max;
    T_Entry<K, V> minValue;
    T_Entry<K, V> maxValue;

    for (int i = 0; i < num_elements - 1; i++)
    {
        if (sd == INCREASING)
        {
            // 오름차순 정렬
            index_min = i;
            minValue = t_array[i];
            for (int j = i + 1; j < num_elements; j++)
            {
                if (t_array[j] < minValue)
                {
                    index_min = j;
                    minValue = t_array[j];
                }
            }
            if (index_min != i)  // if a smaller element is found, then swap
            {
                /* minValue is t_array[min] */
                t_array[index_min] = t_array[i];
                t_array[i] = minValue;
            }
        }
        else
        {
            // 내림차순 정렬
            index_max = i;
            maxValue = t_array[i];
            for (int j = i + 1; j < num_elements; j++)
            {
                if (t_array[j] > maxValue)
                {
                    index_max = j;
                    maxValue = t_array[j];
                }
            }
            if (index_max != i)  // if a smaller element is found, then swap
            {
                /* maxValue is t_array[max] */
                t_array[index_max] = t_array[i];
                t_array[i] = maxValue;
            }
        }
    }
}

template<typename K, typename V>
void TA_Entry<K, V>::quick_sort(SortingDirection sd)
{
    _quickSort(this->t_array, num_elements, 0, num_elements - 1, sd);
}

template<typename K, typename V>
void _quickSort(T_Entry<K, V>* array, int size, int left, int right, SortingDirection sd)
{
    int pI, newPI; // pivot index
    if (left >= right)
        return;  // 정렬 끝
    else
        pI = (left + right) / 2;  // pI 중간값으로 설정

    newPI = _partition(array, size, left, right, pI, sd);
    if (left < (newPI - 1))
        _quickSort(array, size, left, newPI - 1, sd);  // left range
    if ((newPI + 1) < right)
        _quickSort(array, size, newPI + 1, right, sd);  // right range
}

template<typename K, typename V>
int _partition(T_Entry<K, V>* array, int size, int left, int right, int pivotIndex, SortingDirection sd)
{
    T_Entry<K, V> pivotValue, temp;
    int newPI;
    
    /* pivotIndex 우측으로 대피 */
    pivotValue = array[pivotIndex];
    array[pivotIndex] = array[right];
    array[right] = pivotValue; // Move pivot to array[right]
    newPI = left; // newPI is the index that points the position
    for (int i = left; i <= (right - 1); i++)
    {
        if (sd == INCREASING) // 오름차순 정렬
        {
            if (array[i] <= pivotValue)
            {
                temp = array[i];
                array[i] = array[newPI];
                array[newPI] = temp;
                newPI = newPI + 1;
                // note: all elements in left of index newPI are equal or smaller than pivot_value
            }
        }
        else  // 내림차순 정렬
        {
            if (array[i] > pivotValue)
            {
                temp = array[i];
                array[i] = array[newPI];
                array[newPI] = temp;
                newPI = newPI + 1;
                // note: all elements in left of index newPI are greater than pivot_value
            }
        }
    }
    // swap array[newPI] and array[right]; Move pivot element to its final place
    temp = array[newPI];
    array[newPI] = array[right];
    array[right] = temp;
    return newPI;
}

template<typename K, typename V>
void TA_Entry<K, V>::fprint(ofstream& fout, int elements_per_line)
{
    T_Entry<K, V> t_arr;
    int count = 0;
    while (count < num_elements)
    {
        for (int i = 0; i < elements_per_line; i++)
        {
            t_arr = t_array[count];
            t_arr.fprint(fout);
            count++;
            if (count % elements_per_line == 0)
                fout << endl;
        }
    }
    fout << endl;
}

template<typename K, typename V>
void TA_Entry<K, V>::fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines)
{
    string T_type;
    int last_block_start;
    int count = 0;
    T_type = typeid(TA_Entry<K, V>).name();  // TA_Entry<K, V>의 type 이름을 저장
    for (int i = 0; i < num_sample_lines; i++)
    {
        for (int j = 0; j < elements_per_line; j++)
        {
            if (count >= num_elements)
            {
                fout << endl;
                return;
            }
            if ((T_type == string("int")) || (T_type == string("double")) ||
                (T_type == string("class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > ")))
                fout << setw(10) << t_array[count];
            else
                fout << t_array[count] << " ";
            count++;
        }
        fout << endl;
    }
    if (count < (num_elements - elements_per_line * num_sample_lines))
        count = num_elements - elements_per_line * num_sample_lines;
    fout << " . . . . . " << endl;
    for (int i = 0; i < num_sample_lines; i++)
    {
        for (int j = 0; j < elements_per_line; j++)
        {
            if (count >= num_elements)
            {
                fout << endl;
                return;
            }
            if ((T_type == string("int")) || (T_type == string("double")) ||
                (T_type == string("class std::basic_string<char, struct std::char_traits<char>, class std::allocator<char> > ")))
                fout << setw(10) << t_array[count];
            else
                fout << t_array[count] << " ";
            count++;
        }
        fout << endl;
    }
    fout << endl;
}

template<typename K, typename V>
bool TA_Entry<K, V>::isValidIndex(int i)
{
    if ((i < 0) || (i > num_elements))
        return false;
    else
        return true;
}

#endif