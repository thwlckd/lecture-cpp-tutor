/*
*Lab8_21720956_��â��
*Author : ��â��
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
	ThreadParam_Event thrdParam_EventGen, thrdParam_EventHndlr;  // �������� ���ڷ� ���޵� ����ü �ʱ�ȭ
	HANDLE hThrd_EventGenerator, hThrd_EventHandler;
	CRITICAL_SECTION cs_main;
	CRITICAL_SECTION cs_thrd_mon;
	ThreadStatusMonitor thrdMon;  // �������� �����Ȳ �ľ��� ���� ThreadStatusMonitor ����ü ����
	HANDLE consHndlr;
	THREAD_FLAG eventThreadFlag = RUN;
	int numEventGenerated, numEventProcessed;
	int num_events_in_PrioQ;
	Event eventProcessed[TOTAL_NUM_EVENTS];

	InitializeCriticalSection(&cs_main);  // main�� �Ӱ豸�� ������ ����
	InitializeCriticalSection(&cs_thrd_mon);  // thread�� �Ӱ豸�� ������ ����
	consHndlr = initConsoleHandler();
	QueryPerformanceFrequency(&QP_freq);  // �ʴ� Ŭ���� ����
	srand(time(NULL));
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;
	for (int ev = 0; ev < TOTAL_NUM_EVENTS; ev++)
	{
		thrdMon.eventProcessed[ev].setEventNo(-1);  // mark as not-processed
		thrdMon.eventProcessed[ev].setEventPri(-1);
	}

	/* Thread_EventHandler �ʱ�ȭ */
	thrdMon.numEventProcessed = 0;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.myAddr = 1; // link address
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;  // �ʱ�ȭ�� thrdMon�� �ּҸ� ����
	hThrd_EventHandler = (HANDLE)_beginthreadex(NULL, 0, Thread_EventHandler, &thrdParam_EventHndlr, 0, NULL);  // Thread_EventHandler()�� ���ڷ� thrdParam_EventHndlr�� �ҷ� Event ���� ������ ����
	EnterCriticalSection(&cs_main);  // main �Ӱ豸��1 ����
	printf("Thread_EventGen is created and activated ...\n");
	LeaveCriticalSection(&cs_main);  // main �Ӱ豸��1 ����

	/* Thread_EventGen �ʱ�ȭ */
	thrdMon.numEventGenerated = 0;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.myAddr = 0; // my Address
	thrdParam_EventGen.pCS_main = &cs_main;
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.QP_freq = QP_freq;
	thrdParam_EventGen.pThrdMon = &thrdMon;  // �ʱ�ȭ�� thrdMon�� �ּҸ� ����
	hThrd_EventGenerator = (HANDLE)_beginthreadex(NULL, 0, Thread_EventGenerator, &thrdParam_EventGen, 0, NULL);  // Thread_EventGenerator()�� ���ڷ� thrdParam_EventGen�� �ҷ� Event ó�� ������ ����
	EnterCriticalSection(&cs_main);  // main �Ӱ豸��2 ����
	printf("Thread_EventGen is created and activated ...\n");
	LeaveCriticalSection(&cs_main);  // main �Ӱ豸��2 ����

	/* Event monitoring in main() */
	for (int round = 0; round < MAX_ROUND; round++)
	{
		EnterCriticalSection(&cs_main);  // main �Ӱ豸��3 ����
		system("cls");  // �ܼ� clear
		gotoxy(consHndlr, 0, 0);  // �ܼ� (0,0)���� Ŀ�� �̵�
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n", round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n*****************************\n");

		/* Event ���� monitoring */
		numEventGenerated = thrdMon.numEventGenerated;
		printf("Events generated (current total = %2d)\n ", numEventGenerated);
		for (int ev = 0; ev < numEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev];  // ������ �̺�Ʈ ����
			if (pEvent != NULL)
			{
				cout << *pEvent << " ";  // ������ �̺�Ʈ ���
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

		/* Event ó�� mornitoring */
		numEventProcessed = thrdMon.totalEventProcessed;
		printf("Events processed (current total = %d): \n ", numEventProcessed);
		total_elapsed_time = 0.0;
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev];  // ó���� Event ����
			if (pEvent != NULL)
			{
				pEvent->printEvent_proc();  // ó���� Event ���
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
			// Event ó���ϴµ� �ɸ� �ð� ������ ���
			printf("\nmin_elapsed_time = % 8.2lf[ms]; ", min_elapsed_time);
			cout << *pEv_min_elasped_time << endl;
			printf("max_elapsed_time = %8.2lf[ms]; ", max_elapsed_time);
			cout << *pEv_max_elapsed_time << endl;
			avg_elapsed_time = total_elapsed_time / numEventProcessed;
			printf("avg_elapsed_time = %8.2lf[ms]; \n", avg_elapsed_time);
		}
		if (numEventProcessed >= TOTAL_NUM_EVENTS)  // ��� Event ó����
		{
			eventThreadFlag = TERMINATE;  // ThreadFlag�� 2�� ������ ������ ����
			break;
		}
		LeaveCriticalSection(&cs_main);  // main �Ӱ豸��3 ����
		Sleep(100);
	}

	DWORD nExitCode = NULL;
	WaitForSingleObject(hThrd_EventGenerator, INFINITE);  // hThrd_EventGenerator�� �����尡 ����ɶ����� ���
	EnterCriticalSection(&cs_main);  // main �Ӱ豸��4 ����
	printf("Thread_EventGenerator is terminated !!\n");
	LeaveCriticalSection(&cs_main);  // main �Ӱ豸��4 ����
	GetExitCodeThread(hThrd_EventGenerator, &nExitCode);
	CloseHandle(hThrd_EventGenerator);  // hThrd_EventGenerator �Ҹ�

	WaitForSingleObject(hThrd_EventHandler, INFINITE);
	EnterCriticalSection(&cs_main);  // main �Ӱ豸��5 ����
	printf("Thread_EventHandler is terminated !!\n");
	LeaveCriticalSection(&cs_main);  // main �Ӱ豸��5 ����
	GetExitCodeThread(hThrd_EventHandler, &nExitCode);
	CloseHandle(hThrd_EventHandler);  // hThrd_EventHandler �Ҹ�

	printf("Hit any key to terminate : ");
	_getch();
}
