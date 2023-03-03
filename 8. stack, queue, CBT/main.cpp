/*
*Lab8_21720956_박창협
*Author : 박창협
*Programed on October. 28. 2020
* Template class TA_Entry<Key, Value> for Students
*/

#include <iostream>
#include <fstream>
#include "Event.h"
#include "HeapPrioQ.h"
#include <string>
#include <stdlib.h>
#include<time.h>
#include <Windows.h> 

using namespace std;

#define INITIAL_CBT_CAPA 100
#define TEST_HEAP_PRIO_Q_EVENT
#define NUM_EVENTS 15

void main()
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt file for results !!" << endl;
		exit;
	}

	Event *pE;  // 시간측정을 위한 Event 포인터
	pE = new Event;
	LARGE_INTEGER time;
	LARGE_INTEGER freq;
	LONGLONG t_diff;
	double elapsed_time;
	double t[NUM_EVENTS];
	double sum=0;

	Event events[NUM_EVENTS] =
	{
		//Event(int evt_no, int evt_pri, string title, int gen_addr)
		Event(0, 14, "evt_00", 0), Event(1, 13, "evt_01", 1), Event(2, 12, "evt_02", 2),
		Event(3, 11, "evt_03", 3), Event(4, 10, "evt_04", 4), Event(5, 9, "evt_05", 5),
		Event(6, 8, "evt_06", 6), Event(7, 7, "evt_07", 7), Event(8, 6, "evt_08", 8),
		Event(9, 5, "evt_09", 9), Event(10, 4, "evt_10", 10), Event(11, 3, "evt_11", 11),
		Event(12, 2, "evt_12", 12), Event(13, 1, "evt_13", 13), Event(14, 0, "evt_14", 14)
	};

	HeapPrioQueue<int, Event*> HeapPriQ_Event(INITIAL_CBT_CAPA, string("Event_Heap_Priority_Queue"));
	T_Entry<int, Event*> entry_event, * pEntry_Event;
	QueryPerformanceFrequency(&freq);  // 초당 클럭수 측정
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		entry_event.setKey(events[i].getEventPri());  // key 세팅
		entry_event.setValue(&events[i]);  // value 세팅
		pE = &events[i];
		QueryPerformanceCounter(&time);  // 요소 삽입 전 클록수 측정
		pE->set_before_t(time);
		HeapPriQ_Event.insert(entry_event);  // 세팅된 event를 큐에 삽입
		fout << "Insert " << events[i];  // 삽입한 event 출력
		fout << " ==> Size of Heap Priority Queue : " << setw(3) << HeapPriQ_Event.size() << endl;  // 현재 큐의 사이즈(event 개수) 출력
	}
	fout << "Final status of insertions : " << endl;
	HeapPriQ_Event.fprintCBT_byLevel(fout);  // CBT 형태로 구성된 PriQ를 출력
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		fout << "\nCurrent top priority in Heap Priority Queue : ";
		pEntry_Event = HeapPriQ_Event.getHeapMin();  // 우선순위가 가장 높은 event 받아옴
		pE = pEntry_Event->getValue();
		fout << *pEntry_Event << endl;
		pEntry_Event = HeapPriQ_Event.removeHeapMin();  // 우선순위가 가장 높은 event 제거
		QueryPerformanceCounter(&time);  // 요소 삽입 전 클록수 측정
		pE->set_after_t(time);
		t_diff = pE->get_after_t().QuadPart - pE->get_before_t().QuadPart;
		pE->set_elapsed_time(((double)t_diff / freq.QuadPart));
		fout << "Remove " << *pEntry_Event;
		fout << " ==> " << HeapPriQ_Event.size() << " elements remains." << endl;  // 현재 큐의 사이즈 출력
		HeapPriQ_Event.fprintCBT_byLevel(fout);  // CBT 형태로 구성된 PriQ를 출력
		t[i] = pE->get_elapsed_time() * 1000;  // ms 단위 처리시간 저장
		sum += t[i];
		fout << "processed time: " << pE->get_elapsed_time() * 1000 << "ms";
		fout << endl;
	}
	fout << "\nelapsed time min = " << t[0] << "\nelapsed time max = " << t[NUM_EVENTS - 1] << "\nelapsed time avg = " << sum / NUM_EVENTS;

	fout.close();
}
