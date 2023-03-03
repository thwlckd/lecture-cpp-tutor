#pragma once

#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <process.h>
#include <string>
#include "HeapPrioQ_CS.h"
#include "Event.h"
#include "SimParams.h"

using namespace std;

enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };  // 스레드의 실행 여부를 결정하는 flag

typedef struct ThreadStatusMonitor
{
    int numEventGenerated;
    int numEventProcessed;
    int totalEventGenerated;
    int totalEventProcessed;
    Event eventGenerated[TOTAL_NUM_EVENTS];  // 생성한 Event를 main에서 monitoring 하기 위해 배열로 관리
    Event eventProcessed[TOTAL_NUM_EVENTS];  // 처리한 Event를 main에서 monitoring 하기 위해 배열로 관리
    THREAD_FLAG* pFlagThreadTerminate;
}ThreadStatusMonitor;  // main에서 스레드의 실행 과정 및 결과를 쉽게 monitoring 하기 위한 구조체

typedef struct ThreadParam
{
    CRITICAL_SECTION* pCS_main;
    CRITICAL_SECTION* pCS_thrd_mon;
    HeapPrioQ_CS<int, Event>* pPriQ_Event;  // main에서 생성된 공유자원을 사용하기 위한 HeapPrioQ_CS<int, Event>포인터 생성
    FILE* fout;
    ROLE role;
    int myAddr;
    int maxRound;
    int targetEventGen;
    LARGE_INTEGER QP_freq;  // for calculate elapsed time
    ThreadStatusMonitor* pThrdMon;  // main에 스레드의 경과를 보여주기 위해 ThreadStatusMonitor 포인터를 생성해 관리
}ThreadParam_Event;  // 스레드에 인자로 제공될 파라메터를 구조체 정의해 필요한 정보들을 한번에 관리

#endif