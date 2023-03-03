#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <thread>
#include <process.h>

using namespace std;

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };

#define MAX_EVENT_PRIORITY 100
#define NUM_EVENT_GENERATORS 10

class Event
{
    friend ostream& operator<<(ostream& fout, const Event& e);
public:
    Event() {} // default constructor
    Event(int event_id, int event_pri, int srcAddr); //constructor
    void printEvent_proc();  // 처리된 Event를 보여주는 함수
    void setEventHandlerAddr(int evtHndlerAddr) { event_handler_addr = evtHndlerAddr; }
    void setEventGenAddr(int genAddr) { event_gen_addr = genAddr; }
    void setEventNo(int evtNo) { event_no = evtNo; }
    void setEventPri(int pri) { event_pri = pri; }
    void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; }
    void setEventGenTime(LARGE_INTEGER t_gen) { t_event_gen = t_gen; }
    void setEventProcTime(LARGE_INTEGER t_proc) { t_event_proc = t_proc; }
    LARGE_INTEGER getEventGenTime() { return t_event_gen; }
    LARGE_INTEGER getEventProcTime() { return t_event_proc; }
    void setEventElaspsedTime(double t_elapsed_ms) { t_elapsed_time_ms = t_elapsed_ms; }
    double getEventElapsedTime() { return t_elapsed_time_ms; }
    int getEventPri() { return event_pri; }
    int getEventNo() { return event_no; }
    bool operator>(Event& e) { return (event_pri > e.event_pri); }
    bool operator<(Event& e) { return (event_pri < e.event_pri); }
private:
    int event_no;
    int event_gen_addr;
    int event_handler_addr;
    int event_pri; // event_priority
    LARGE_INTEGER t_event_gen;
    LARGE_INTEGER t_event_proc;
    double t_elapsed_time_ms;
    EventStatus eventStatus;
};

Event* genRandEvent(int evt_no);
unsigned __stdcall Thread_EventGenerator(LPVOID pParam);
unsigned __stdcall Thread_EventHandler(LPVOID pParam);

#endif