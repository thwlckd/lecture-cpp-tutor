#include <Windows.h>
#include "Multi_Thread.h"
#include "HeapPrioQ_CS.h"
#include "Event.h"
#include "SimParams.h"

#define myExitCode 0

unsigned __stdcall Thread_EventGenerator(LPVOID pParam)  // Event 생성 스레드
{
	ThreadParam_Event* pThrdParam;  // 받아온 인자를 사용하기 위한 ThreadParam_Event 포인터 생성
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
	pThrdParam = (ThreadParam_Event*)pParam;  // LPVOID 형으로 받아온 pParam을 ThreadParam_Event* 형으로 바꿔 사용
	// 받아온 파라메터로 부터 thread moitoring 변수들 초기화
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
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)  // main에서 THREAD_FLAG를 2로 설정시
				break;  // Event 생성 스레드 종료
			else 
			{
				Sleep(500);
				continue;
			}
		}
		// set API를 이용한 event 초기화
		event_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;
		event_priority = targetEventGen - event_gen_count - 1;
		event.setEventNo(event_no);
		event.setEventPri(event_priority);
		event.setEventGenAddr(myAddr);
		event.setEventHandlerAddr(-1);  // event handler is not defined yet !!
		QueryPerformanceCounter(&t_gen);  // insert Event 전 클록수 측정
		event.setEventGenTime(t_gen);  // insert Event 전 클록수 event에 전달
		event.setEventStatus(GENERATED);
		entry_event.setKey(event.getEventPri());  // key: 우선순위
		entry_event.setValue(event);  // value: Event

		while (pPriQ_Event->size()== PRI_QUEUE_CAPACITY)  // insert Event
		{
			Sleep(10);
		}
		pPriQ_Event->insert(entry_event);

		EnterCriticalSection(pThrdParam->pCS_thrd_mon);  // EventGenerator thread 임계구역 시작
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = event;  // 생성한 Event를 main에서 monitoring 하기위해 생성순으로 배열에 전달
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		LeaveCriticalSection(pThrdParam->pCS_thrd_mon);  // EventGenerator thread 임계구역 종료
		event_gen_count++;
		Sleep(10);
	}

	_endthreadex(myExitCode);  // 스레드 종료
	return 0;
}