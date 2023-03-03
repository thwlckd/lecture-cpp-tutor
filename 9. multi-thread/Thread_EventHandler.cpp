#include <Windows.h>
#include "Multi_Thread.h"
#include "HeapPrioQ_CS.h" 
#include "Event.h"

#define myExitCode 0

unsigned __stdcall Thread_EventHandler(LPVOID pParam)  // Event 처리 스레드
{
	ThreadParam_Event* pThrdParam;  // 받아온 인자를 사용하기 위한 ThreadParam_Event 포인터 생성
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
	pThrdParam = (ThreadParam_Event*)pParam;  // LPVOID 형으로 받아온 pParam을 ThreadParam_Event* 형으로 바꿔 사용
	// 받아온 파라메터로 부터 thread moitoring 변수들 초기화
	myRole = pThrdParam->role; 
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound; 
	QP_freq = pThrdParam->QP_freq;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)  // main에서 THREAD_FLAG를 2로 설정시
			break;  // Event 처리 스레드 종료
		if (!pPriQ_Event->isEmpty())
		{
			pEntry = pPriQ_Event->removeHeapMin();  // remove Event (down-heap bubbling 수행)
			event = pEntry->getValue();
			EnterCriticalSection(pThrdParam->pCS_thrd_mon);  // EventHandler thread 임계구역 시작
			event.setEventHandlerAddr(myAddr);
			QueryPerformanceCounter(&t_proc);  // remove Event 후의 클록수 측정
			event.setEventProcTime(t_proc);
			t_gen = event.getEventGenTime();  // insert Event 전에 측정한 클록수 받아옴
			t_diff = t_proc.QuadPart - t_gen.QuadPart;  // insert~remove동안 발생한 클록수 계산
			elapsed_time = ((double)t_diff / QP_freq.QuadPart); // 발생한 클록수/초당 발생 클록수=경과시간(in second)
			event.setEventElaspsedTime(elapsed_time * 1000); // remove된 Event의 처리시간을 milli-second로 설정
			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event;  // 처리한 Event를 main에서 monitoring 하기위해 처리순으로 배열에 전달
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			LeaveCriticalSection(pThrdParam->pCS_thrd_mon);  // EventHandler thread 임계구역 종료
		}
		Sleep(100 + rand() % 100);
	}

	_endthreadex(myExitCode);  // 스레드 종료
	return 0;
}