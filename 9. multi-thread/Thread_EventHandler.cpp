#include <Windows.h>
#include "Multi_Thread.h"
#include "HeapPrioQ_CS.h" 
#include "Event.h"

#define myExitCode 0

unsigned __stdcall Thread_EventHandler(LPVOID pParam)  // Event ó�� ������
{
	ThreadParam_Event* pThrdParam;  // �޾ƿ� ���ڸ� ����ϱ� ���� ThreadParam_Event ������ ����
	HeapPrioQ_CS<int, Event>* pPriQ_Event;
	int myRole, myAddr, maxRound; 
	THREAD_FLAG* pFlagThreadTerminate;
	T_Entry<int, Event>* pEntry;
	Event event;
	int targetEventGen;

	LARGE_INTEGER QP_freq, t_gen, t_proc;
	LONGLONG t_diff; 
	double elapsed_time; 

	ThreadStatusMonitor* pThrdMon;
	pThrdParam = (ThreadParam_Event*)pParam;  // LPVOID ������ �޾ƿ� pParam�� ThreadParam_Event* ������ �ٲ� ���
	// �޾ƿ� �Ķ���ͷ� ���� thread moitoring ������ �ʱ�ȭ
	myRole = pThrdParam->role; 
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound; 
	QP_freq = pThrdParam->QP_freq;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)  // main���� THREAD_FLAG�� 2�� ������
			break;  // Event ó�� ������ ����
		if (!pPriQ_Event->isEmpty())
		{
			pEntry = pPriQ_Event->removeHeapMin();  // remove Event (down-heap bubbling ����)
			event = pEntry->getValue();
			EnterCriticalSection(pThrdParam->pCS_thrd_mon);  // EventHandler thread �Ӱ豸�� ����
			event.setEventHandlerAddr(myAddr);
			QueryPerformanceCounter(&t_proc);  // remove Event ���� Ŭ�ϼ� ����
			event.setEventProcTime(t_proc);
			t_gen = event.getEventGenTime();  // insert Event ���� ������ Ŭ�ϼ� �޾ƿ�
			t_diff = t_proc.QuadPart - t_gen.QuadPart;  // insert~remove���� �߻��� Ŭ�ϼ� ���
			elapsed_time = ((double)t_diff / QP_freq.QuadPart); // �߻��� Ŭ�ϼ�/�ʴ� �߻� Ŭ�ϼ�=����ð�(in second)
			event.setEventElaspsedTime(elapsed_time * 1000); // remove�� Event�� ó���ð��� milli-second�� ����
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event;  // ó���� Event�� main���� monitoring �ϱ����� ó�������� �迭�� ����
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon);  // EventHandler thread �Ӱ豸�� ����
		}
		Sleep(100 + rand() % 100);
	}

	_endthreadex(myExitCode);  // ������ ����
	return 0;
}