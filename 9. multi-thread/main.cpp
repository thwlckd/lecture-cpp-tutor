/*
*Lab8_21720956_박창협
*Author : 박창협
*Programed on November. 05. 2020
*Simulation of Priority-based Event Processing with Multi-thread and Heap Priority Queue 
*/

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "Multi_Thread.h"
#include "HeapPrioQ_CS.h"
#include "Event.h"
#include "ConsoleDisplay.h"
#include "SimParams.h"
#include <time.h>
#include <conio.h>
#include "main.h"

void main()
{
	LARGE_INTEGER QP_freq, t_before, t_after;
	LONGLONG t_diff;
	double elapsed_time, min_elapsed_time, max_elapsed_time;
	double avg_elapsed_time, total_elapsed_time;
	HeapPrioQ_CS<int, Event> heapPriQ_Event(PRI_QUEUE_CAPACITY, string("HeapPriorityQueue_Event"));
	Event* pEvent, * pEv_min_elasped_time = NULL, * pEv_max_elapsed_time = NULL;
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;  // 스레드의 인자로 전달될 구조체 초기화
	HANDLE hThrd_EventGenerator, hThrd_EventHandler;
	CRITICAL_SECTION cs_main;
	CRITICAL_SECTION cs_thrd_mon;
	ThreadStatusMonitor thrdMon;  // 스레드의 진행상황 파악을 위한 ThreadStatusMonitor 구조체 정의
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int numEventGenerated, numEventProcessed;
	int num_events_in_PrioQ;
	Event eventProcessed[TOTAL_NUM_EVENTS];

	InitializeCriticalSection(&cs_main);  // main의 임계구역 세마포 생성
	InitializeCriticalSection(&cs_thrd_mon);  // thread의 임계구역 세마포 생성
	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&QP_freq);  // 초당 클럭수 측정
	srand(time(NULL));
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].setEventNo(-1);  // mark as not-processed
		thrdMon.eventProcessed[ev].setEventPri(-1);
	}

	/* Thread_EventHandler 초기화 */
	thrdMon.numEventProcessed = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1; // link address
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;  // 초기화된 thrdMon의 주소를 전달
	hThrd_EventHandler = (HANDLE)_beginthreadex(NULL, 0, Thread_EventHandler, &thrdParam_EventHndlr, 0, NULL);  // Thread_EventHandler()의 인자로 thrdParam_EventHndlr를 불러 Event 생성 스레드 시작
	EnterCriticalSection(&cs_main);  // main 임계구역1 시작
	printf("Thread_EventGen is created and activated ...\n");
	LeaveCriticalSection(&cs_main);  // main 임계구역1 종료

	/* Thread_EventGen 초기화 */
	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0; // my Address
	thrdParam_EventGen.pCS_main = &cs_main;
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.QP_freq = QP_freq;
	thrdParam_EventGen.pThrdMon = &thrdMon;  // 초기화된 thrdMon의 주소를 전달
	hThrd_EventGenerator = (HANDLE)_beginthreadex(NULL, 0, Thread_EventGenerator, &thrdParam_EventGen, 0, NULL);  // Thread_EventGenerator()의 인자로 thrdParam_EventGen를 불러 Event 처리 스레드 시작
	EnterCriticalSection(&cs_main);  // main 임계구역2 시작
	printf("Thread_EventGen is created and activated ...\n");
	LeaveCriticalSection(&cs_main);  // main 임계구역2 종료

	/* Event monitoring in main() */
	for (int round = 0; round < MAX_ROUND; round++)
	{
		EnterCriticalSection(&cs_main);  // main 임계구역3 시작
		system("cls");  // 콘솔 clear
		gotoxy(consHndlr, 0, 0);  // 콘솔 (0,0)으로 커서 이동
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n", round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n*****************************\n");

		/* Event 생성 monitoring */
		numEventGenerated = thrdMon.numEventGenerated;
		printf("Events generated (current total = %2d)\n ", numEventGenerated);
		for (int ev = 0; ev < numEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev];  // 생성된 이벤트 전달
			if (pEvent != NULL)
			{
				cout << *pEvent << " ";  // 생성된 이벤트 출력
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
		}
		printf("\n");
		printf("\n*****************************\n");
		num_events_in_PrioQ = heapPriQ_Event.size();
		printf("Events currently in Priority_Queue (%d) :\n", num_events_in_PrioQ);
		heapPriQ_Event.fprint(cout);
		printf("\n\n*****************************\n");

		/* Event 처리 mornitoring */
		numEventProcessed = thrdMon.totalEventProcessed;
		printf("Events processed (current total = %d): \n ", numEventProcessed);
		total_elapsed_time = 0.0;
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev];  // 처리된 Event 전달
			if (pEvent != NULL)
			{
				pEvent->printEvent_proc();  // 처리된 Event 출력
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
			if (ev == 0)
			{
				min_elapsed_time = max_elapsed_time = total_elapsed_time = pEvent->getEventElapsedTime();  // in milli-second
				pEv_min_elasped_time = pEv_max_elapsed_time = pEvent;
			}
			else
			{
				if (min_elapsed_time > pEvent->getEventElapsedTime())
				{
					min_elapsed_time = pEvent->getEventElapsedTime();
					pEv_min_elasped_time = pEvent;
				}
				if (max_elapsed_time < pEvent->getEventElapsedTime())
				{
					max_elapsed_time = pEvent->getEventElapsedTime();
					pEv_max_elapsed_time = pEvent;
				}
				total_elapsed_time += pEvent->getEventElapsedTime();
			}
		}
		if (numEventProcessed > 0)
		{
			// Event 처리하는데 걸린 시간 데이터 출력
			printf("\nmin_elapsed_time = % 8.2lf[ms]; ", min_elapsed_time);
			cout << *pEv_min_elasped_time << endl;
			printf("max_elapsed_time = %8.2lf[ms]; ", max_elapsed_time);
			cout << *pEv_max_elapsed_time << endl;
			avg_elapsed_time = total_elapsed_time / numEventProcessed;
			printf("avg_elapsed_time = %8.2lf[ms]; \n", avg_elapsed_time);
		}
		if (numEventProcessed >= TOTAL_NUM_EVENTS)  // 모든 Event 처리시
		{
			eventThreadFlag = TERMINATE;  // ThreadFlag를 2로 설정해 스레드 종료
			break;
		}
		LeaveCriticalSection(&cs_main);  // main 임계구역3 종료
		Sleep(100);
	}

	DWORD nExitCode = NULL;
	WaitForSingleObject(hThrd_EventGenerator, INFINITE);  // hThrd_EventGenerator의 스레드가 종료될때까지 대기
	EnterCriticalSection(&cs_main);  // main 임계구역4 시작
	printf("Thread_EventGenerator is terminated !!\n");
	LeaveCriticalSection(&cs_main);  // main 임계구역4 종료
	GetExitCodeThread(hThrd_EventGenerator, &nExitCode);
	CloseHandle(hThrd_EventGenerator);  // hThrd_EventGenerator 소멸

	WaitForSingleObject(hThrd_EventHandler, INFINITE);
	EnterCriticalSection(&cs_main);  // main 임계구역5 시작
	printf("Thread_EventHandler is terminated !!\n");
	LeaveCriticalSection(&cs_main);  // main 임계구역5 종료
	GetExitCodeThread(hThrd_EventHandler, &nExitCode);
	CloseHandle(hThrd_EventHandler);  // hThrd_EventHandler 소멸

	printf("Hit any key to terminate : ");
	_getch();
}
