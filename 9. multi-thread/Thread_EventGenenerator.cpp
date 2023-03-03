#include <Windows.h>
#include "Multi_Thread.h"
#include "HeapPrioQ_CS.h"
#include "Event.h"
#include "SimParams.h"

#define myExitCode 0

unsigned __stdcall Thread_EventGenerator(LPVOID pParam)  // Event ���� ������
{
	ThreadParam_Event* pThrdParam;  // �޾ƿ� ���ڸ� ����ϱ� ���� ThreadParam_Event ������ ����
	HeapPrioQ_CS<int, Event>* pPriQ_Event;
	int myRole;
	THREAD_FLAG* pFlagThreadTerminate;
	int maxRound;
	T_Entry<int, Event> entry_event;
	Event event;
	int event_no = 0;
	int event_priority = 0;
	int event_gen_count = 0;
	int targetEventGen;
	int myAddr = -1;
	int event_handler_addr;

	LARGE_INTEGER QP_freq, t_gen;

	ThreadStatusMonitor* pThrdMon;
	pThrdParam = (ThreadParam_Event*)pParam;  // LPVOID ������ �޾ƿ� pParam�� ThreadParam_Event* ������ �ٲ� ���
	// �޾ƿ� �Ķ���ͷ� ���� thread moitoring ������ �ʱ�ȭ
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)  // main���� THREAD_FLAG�� 2�� ������
				break;  // Event ���� ������ ����
			else 
			{
				Sleep(500);
				continue;
			}
		}
		// set API�� �̿��� event �ʱ�ȭ
		event_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;
		event_priority = targetEventGen - event_gen_count - 1;
		event.setEventNo(event_no);
		event.setEventPri(event_priority);
		event.setEventGenAddr(myAddr);
		event.setEventHandlerAddr(-1);  // event handler is not defined yet !!
		QueryPerformanceCounter(&t_gen);  // insert Event �� Ŭ�ϼ� ����
		event.setEventGenTime(t_gen);  // insert Event �� Ŭ�ϼ� event�� ����
		event.setEventStatus(GENERATED);
		entry_event.setKey(event.getEventPri());  // key: �켱����
		entry_event.setValue(event);  // value: Event

		while (pPriQ_Event->size()== PRI_QUEUE_CAPACITY)  // insert Event
		{
			Sleep(10);
		}
		pPriQ_Event->insert(entry_event);

		EnterCriticalSection(pThrdParam->pCS_thrd_mon);  // EventGenerator thread �Ӱ豸�� ����
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = event;  // ������ Event�� main���� monitoring �ϱ����� ���������� �迭�� ����
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		LeaveCriticalSection(pThrdParam->pCS_thrd_mon);  // EventGenerator thread �Ӱ豸�� ����
		event_gen_count++;
		Sleep(10);
	}

	_endthreadex(myExitCode);  // ������ ����
	return 0;
}