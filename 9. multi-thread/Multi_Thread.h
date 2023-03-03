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
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };  // �������� ���� ���θ� �����ϴ� flag

typedef struct ThreadStatusMonitor
{
    int numEventGenerated;
    int numEventProcessed;
    int totalEventGenerated;
    int totalEventProcessed;
    Event eventGenerated[TOTAL_NUM_EVENTS];  // ������ Event�� main���� monitoring �ϱ� ���� �迭�� ����
    Event eventProcessed[TOTAL_NUM_EVENTS];  // ó���� Event�� main���� monitoring �ϱ� ���� �迭�� ����
    THREAD_FLAG* pFlagThreadTerminate;
}ThreadStatusMonitor;  // main���� �������� ���� ���� �� ����� ���� monitoring �ϱ� ���� ����ü

typedef struct ThreadParam
{
    CRITICAL_SECTION* pCS_main;
    CRITICAL_SECTION* pCS_thrd_mon;
    HeapPrioQ_CS<int, Event>* pPriQ_Event;  // main���� ������ �����ڿ��� ����ϱ� ���� HeapPrioQ_CS<int, Event>������ ����
    FILE* fout;
    ROLE role;
    int myAddr;
    int maxRound;
    int targetEventGen;
    LARGE_INTEGER QP_freq;  // for calculate elapsed time
    ThreadStatusMonitor* pThrdMon;  // main�� �������� ����� �����ֱ� ���� ThreadStatusMonitor �����͸� ������ ����
}ThreadParam_Event;  // �����忡 ���ڷ� ������ �Ķ���͸� ����ü ������ �ʿ��� �������� �ѹ��� ����

#endif