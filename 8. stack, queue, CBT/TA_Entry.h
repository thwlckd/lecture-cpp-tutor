#pragma once

#ifndef TA_ENTRY
#define TA_ENTRY

#include"T_Entry.h"

using namespace std;

enum SortingDirection { INCREASING, DECREASING };  // 정렬방향. 오름/내림 차순

template<typename K, typename V>
class TA_Entry
{
    //friend ostream& operator<<(ostream& fout, TA_Entry<K, V>& entry);
public:
	TA_Entry(int n, string nm); // constructor
	~TA_Entry(); // destructor
	int size() { return num_elements; }
	bool empty() { return num_elements == 0; }
	string getName() { return name; }
	void reserve(int new_capacity);  // 배열의 용량을 확보해 주는 함수
	void insert(int i, T_Entry<K, V> element);  // 배열의 i번째 인덱스에 값을 넣어주는 함수
	void remove(int i);  // 배열의 i번째 요소를 제거하는 함수
	T_Entry<K, V>& at(int i);  // 배열의 i번째의 값을 반환하는 함수
	void set(int i, T_Entry<K, V>& element);  // 배열의 i번째 요소를 원하는 값으로 바꾸는 함수
	T_Entry<K, V> getMin(int begin, int end);  // 배열중 Key값이 가장 작은 객체를 반환
	T_Entry<K, V> getMax(int begin, int end);  // 배열중 Key값이 가장 큰 객체를 반환
	void shuffle();
	int sequential_search(T_Entry<K, V> search_key);
	int binary_search(T_Entry<K, V> search_key);
	void selection_sort(SortingDirection sd);
	void quick_sort(SortingDirection sd);
	void fprint(ofstream& fout, int elements_per_line);
	void fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines);
	bool isValidIndex(int i);
    T_Entry<K, V>& operator[](int index);

protected:
	T_Entry<K, V>* t_GA;
	int num_elements;
	int capacity;
	string name;
};
/*
template<typename K, typename V>
ostream& operator<<(ostream& fout, TA_Entry<K, V>& entry)
{
    while (count < num_elements)
    {
        for (int i = 0; i < num_elements; i++)
        {
            entry.fprint(fout);
        }
    }
    fout << endl;

    return fout;
}*/

template<typename K, typename V>
TA_Entry<K, V>::TA_Entry(int new_capacity, string nm)
{
	capacity = new_capacity;
	t_GA = (T_Entry<K, V>*) new T_Entry<K, V>[capacity];
	if (t_GA == NULL)
	{
		cout << "Error in creation of dynamic GA of size (" << new_capacity << ") !!" << endl;
		exit(-1);
	}
	num_elements = 0;
	name = nm;
}

template<typename K, typename V>
TA_Entry<K, V>::~TA_Entry()
{
	if (t_GA != NULL)
		delete[] t_GA;
}

template<typename K, typename V>
void TA_Entry<K, V>::reserve(int new_capacity)
{
    if (capacity >= new_capacity)
        return;  // new_capacity 이상의 용량이 준비되어 있음
    T_Entry<K, V>* t_newGA = (T_Entry<K, V>*) new T_Entry<K, V>[new_capacity];  // new_capacity 만큼 배열 동적 할당
    if (t_newGA == NULL)
    {
        cout << "Error in creation of dynamic GA of size (" << new_capacity << ") !!" << endl;
        exit(-1);
    }
    cout << this->getName() << " expands capacity to " << setw(3) << new_capacity << endl;
    for (int i = 0; i < num_elements; i++)
        t_newGA[i] = t_GA[i];  // 새로 할당한 배열에 기존의 값 복사
    delete[] t_GA;
    t_GA = t_newGA;
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
            t_GA[j + 1] = t_GA[j];  // i보다 큰 인덱스 값들을 뒤로 한칸씩 이동
        t_GA[i] = element;  // insert
        num_elements++;
    }
}

template<typename K, typename V>
void TA_Entry<K, V>::remove(int i)
{
    if (isValidIndex(i))
    {
        for (int j = i + 1; j < num_elements; j++)
            t_GA[j - 1] = t_GA[j];  // i보다 큰 인덱스 값들을 앞으로 한칸씩 이동
        num_elements--;
    }
    if (num_elements < (capacity / 2))
    {
        int new_capacity = capacity / 2;
        T_Entry<K, V>* t_newGA = (T_Entry<K, V>*) new T_Entry<K, V>[new_capacity];
        if (t_newGA == NULL)
        {
            return;
        }
        cout << this->getName() << " reduces capacity to " << setw(3) << new_capacity << endl;
        for (int i = 0; i < num_elements; i++)
            t_newGA[i] = t_GA[i];
        delete[] t_GA;
        t_GA = t_newGA;
        capacity = new_capacity;
    }
}

template<typename K, typename V>
T_Entry<K, V>& TA_Entry<K, V>::at(int i)
{
    if (isValidIndex(i))
        return t_GA[i];
}

template<typename K, typename V>
void TA_Entry<K, V>::set(int i, T_Entry<K, V>& element)
{
    if (isValidIndex(i))
        t_GA[i] = element;
}

template<typename K, typename V>
T_Entry<K, V> TA_Entry<K, V>::getMin(int begin, int end)
{
    {
        T_Entry<K, V> minValue;
        int index_min;

        minValue = t_GA[begin];
        index_min = begin;
        for (int i = begin + 1; i <= end; i++)
        {
            if (t_GA[i] < minValue)
            {
                minValue = t_GA[i];
                index_min = i;
            }
        }
        return t_GA[index_min];
    }
}

template<typename K, typename V>
T_Entry<K, V> TA_Entry<K, V>::getMax(int begin, int end)
{
    T_Entry<K, V> maxValue;
    int index_max;

    maxValue = t_GA[begin];
    index_max = begin;
    for (int i = begin + 1; i <= end; i++)
    {
        if (t_GA[i] > maxValue)
        {
            maxValue = t_GA[i];
            index_max = i;
        }
    }
    return t_GA[index_max];
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

        // t_GA의 index1과 index2 값 교환
        temp = t_GA[index1];
        t_GA[index1] = t_GA[index2];
        t_GA[index2] = temp;
    }
}

template<typename K, typename V>
int TA_Entry<K, V>::sequential_search(T_Entry<K, V> search_key)
{
    int index;
    for (int index = 0; index < num_elements; index++)
    {
        // 처음부터 끝까지 하나씩 비교
        if (t_GA[index] == search_key)
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
        if (t_GA[mid] == search_key)
            return mid;
        else if (t_GA[mid] > search_key)
            high = mid - 1;  // high range를 다음 탐색 구간으로 설정
        else
            low = mid + 1;  // low range를 다음 탐색 구간으로 설정
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
            minValue = t_GA[i];
            for (int j = i + 1; j < num_elements; j++)
            {
                if (t_GA[j] < minValue)
                {
                    index_min = j;
                    minValue = t_GA[j];
                }
            }
            if (index_min != i)  // if a smaller element is found, then swap
            {
                /* minValue is t_GA[min] */
                t_GA[index_min] = t_GA[i];
                t_GA[i] = minValue;
            }
        }
        else
        {
            // 내림차순 정렬
            index_max = i;
            maxValue = t_GA[i];
            for (int j = i + 1; j < num_elements; j++)
            {
                if (t_GA[j] > maxValue)
                {
                    index_max = j;
                    maxValue = t_GA[j];
                }
            }
            if (index_max != i)  // if a smaller element is found, then swap
            {
                /* maxValue is t_GA[max] */
                t_GA[index_max] = t_GA[i];
                t_GA[i] = maxValue;
            }
        }
    }
}

template<typename K, typename V>
void TA_Entry<K, V>::quick_sort(SortingDirection sd)
{
    _quickSort(this->t_GA, num_elements, 0, num_elements - 1, sd);
}

template<typename K, typename V>
void _quickSort(T_Entry<K, V>* GA, int size, int left, int right, SortingDirection sd)
{
    int pI, newPI; // pivot index
    if (left >= right)
        return;  // 정렬 끝
    else
        pI = (left + right) / 2;  // pI 중간값으로 설정

    newPI = _partition(GA, size, left, right, pI, sd);
    if (left < (newPI - 1))
        _quickSort(GA, size, left, newPI - 1, sd);  // left range
    if ((newPI + 1) < right)
        _quickSort(GA, size, newPI + 1, right, sd);  // right range
}

template<typename K, typename V>
int _partition(T_Entry<K, V>* GA, int size, int left, int right, int pivotIndex, SortingDirection sd)
{
    T_Entry<K, V> pivotValue, temp;
    int newPI;

    /* pivot 우측으로 대피 */
    pivotValue = GA[pivotIndex];
    GA[pivotIndex] = GA[right];
    GA[right] = pivotValue; // Move pivot to GA[right]
    newPI = left; // newPI is the index that points the position
    for (int i = left; i <= (right - 1); i++)
    {
        if (sd == INCREASING) // 오름차순 정렬
        {
            if (GA[i] <= pivotValue)
            {
                temp = GA[i];
                GA[i] = GA[newPI];
                GA[newPI] = temp;
                newPI = newPI + 1;
                // note: all elements in left of index newPI are equal or smaller than pivot_value
            }
        }
        else  // 내림차순 정렬
        {
            if (GA[i] > pivotValue)
            {
                temp = GA[i];
                GA[i] = GA[newPI];
                GA[newPI] = temp;
                newPI = newPI + 1;
                // note: all elements in left of index newPI are greater than pivot_value
            }
        }
    }
    // swap GA[newPI] and GA[right]; Move pivot element to its final place
    temp = GA[newPI];
    GA[newPI] = GA[right];
    GA[right] = temp;
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
            t_arr = t_GA[count];
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
                fout << setw(10) << t_GA[count];
            else
                fout << t_GA[count] << " ";
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
                fout << setw(10) << t_GA[count];
            else
                fout << t_GA[count] << " ";
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

template<typename K, typename V>
T_Entry<K, V>& TA_Entry<K, V>::operator[](int index)
{
    if (isValidIndex(index))
        return t_GA[index];
}

#endif 